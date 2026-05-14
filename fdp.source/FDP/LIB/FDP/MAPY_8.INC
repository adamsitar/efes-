procedure _SYM_update(sym_fir, sym_map: string;  sym_set: TSetSymType;
                      tline,lprior,lcolor, fprior,fcolor, eprior,ecolor: word
                     );

    var   SymF        : file;
          FirF        : text;

          ftC,ftL,ftM : long;
          head_size   : long;

          Mark13  : TMark13;
          Zd,Zs   : TZdZs;
          Ts      : int;
          vet     : ch255;

          s,t,N   : string;
          sir,dlz : string[10];
          res,p,i : int;
          b       : bool;

    begin
      FSplit(sym_fir, sDir,sName,sExt); s:= sName;
      sym_fir:= pathDATA+sName+firExt;
      if (Exists(sym_fir)<>0) then Exit;

      FSplit(sym_map, sDir,sName,sExt);
      if sym_map='' then sym_map:= s;

      s:= FindFile(PathToMaps,sym_map+ext_MAP);
      if s='' then
         begin
           s:= PathToMaps+'SYM';
           _mkdir(s);
           sym_map:= s+'\'+sym_map+ext_MAP
         end
      else begin
             sym_map:= s;
             ftC:= _GetFTime(MAPscfg); ftL:= _GetFTime(sym_fir); ftM:= _GetFTime(sym_map);
             if (is_ParamStr(psINIT_SYM)='') and (ftC<=ftM) and (ftL<=ftM) then Exit
           end;


      write('Updating '+sym_map+'...  ');
      mapy_vytvor_subor(sym_map, tline,lprior,lcolor, fprior,fcolor, eprior,ecolor);
      mapy_vytvor_GP   (sym_map, gr_Mark13, 0,0,0);

      Assign(FirF,sym_fir); Reset(FirF);
      Assign(SymF,sym_map); Reset(SymF,1);

      Mark13.pocet:= 0;
      head_size:= FileSize(SymF);
      Seek(SymF,head_size);
      BlockWrite(SymF,Mark13.pocet,SizeOf(Mark13.pocet),res);

     { suradnice a popis symbolu
     } while (not Eof(FirF)) do
        begin
          readln(FirF,s); s:= uni_str(cut_(s));
          if (s='') or (s[1]='"') or (s[1]=';') then continue;

          t:= GetStr(s,pos_kod,odd_body+[' ']); t:= cut_(t);
          StrPCopy(vet,t);

          t:= getstr(s,pos_zs, odd_body); t:= cut_(t);
          if not decode_l4_ZemSur(t, zd.st,zd.mn,zd.se, zs.st,zs.mn,zs.se) then
             begin
               sir:= GetStr(t,1,[' ']); Zs.st:= scis(sir,1,2); Zs.mn:= scis(sir,3,2); Zs.se:= scis(sir,5,2);
               dlz:= GetStr(t,2,[' ']); Zd.st:= scis(dlz,1,2); Zd.mn:= scis(dlz,3,2); Zd.se:= scis(dlz,5,2)
             end;

          t:= cut_(getstr(s,pos_typ,odd_body));
          b:= true;
          if (t<>'') and (t[1]=prizn_not_kr) then
             begin
               b:= false;
               t:= copy(t,2,length(t)-1)
             end;
          Ts:= get_OBtyp(t);
          if (not MARKED_SYM) or (t<>'') then
            if ((Ts<>sym_NONE) or (b)) and ((sym_set=[]) or (Ts in sym_set)) then
               begin
                 if not b then Ts:= -Ts;

                 RW_Mark13(1, SymF, Zd,Zs, Ts, vet);
                 inc(Mark13.pocet)
               end
        end;

      Seek(SymF,head_size);
      BlockWrite(SymF,Mark13.pocet,SizeOf(Mark13.pocet),res);
      Close(SymF);

      Close(FirF);

      writeln ('Done.')
    end;


procedure SYM_update;

    var   fT : text;
          s,t,u,v, fn : string;
          ssym  : TSetSymType;
          sym   : TSymType;
          i,j,p : int;

    begin
      fillchar(SYMpalette,sizeof(SYMpalette),SYMsCl);

    { nacitanie farieb pre symboly
    } if Exists(MAPscfg)=0 then
         begin
           SYMpalette[sym_CLet]     := read_cfg_word(MAPscfg,prizn_CLet,SYMpalette[sym_CLet]);
           SYMpalette[sym_MLet]     := read_cfg_word(MAPscfg,prizn_MLet,SYMpalette[sym_MLet]);
           SYMpalette[sym_ALet]     := read_cfg_word(MAPscfg,prizn_ALet,SYMpalette[sym_ALet]);

           SYMpalette[sym_OB]       := read_cfg_word(MAPscfg,prizn_OB,SYMpalette[sym_OB]);
           SYMpalette[sym_SECTOR]   := read_cfg_word(MAPscfg,prizn_SECTOR,SYMpalette[sym_SECTOR]);
           SYMpalette[sym_REPORT]   := read_cfg_word(MAPscfg,prizn_REPORT,SYMpalette[sym_REPORT]);
           SYMpalette[sym_REP1]     := read_cfg_word(MAPscfg,prizn_REP1,SYMpalette[sym_REP1]);
           SYMpalette[sym_REP2]     := read_cfg_word(MAPscfg,prizn_REP2,SYMpalette[sym_REP2]);
           SYMpalette[sym_NDB1]     := read_cfg_word(MAPscfg,prizn_NDB1,SYMpalette[sym_NDB1]);
           SYMpalette[sym_NDB2]     := read_cfg_word(MAPscfg,prizn_NDB2,SYMpalette[sym_NDB2]);
           SYMpalette[sym_VOR]      := read_cfg_word(MAPscfg,prizn_VOR,SYMpalette[sym_VOR]);
           SYMpalette[sym_VOR_DME1] := read_cfg_word(MAPscfg,prizn_VOR_DME1,SYMpalette[sym_VOR_DME1]);
           SYMpalette[sym_VOR_DME2] := read_cfg_word(MAPscfg,prizn_VOR_DME2,SYMpalette[sym_VOR_DME2])
         end;

    { aktualizacia symbolov
    } if Exists(MAPscfg)=0 then
         begin
           Assign(fT,MAPscfg);
           Reset(fT);
           while (not Eof(fT)) do
             begin
               readln(fT,s); s:= cut_(uni_str(s));
               if pos(cfg_MAPY_SYMBOLY,s)<>1 then continue;

               fn:= cut_(getstr(getstr(s,1,[';']),2,['=']));
               t:= cut_(getstr(s,2,[';']));
               p:= getstritems(t,[icao_NXIT]);
               if p>0 then for i:= 1 to p do
                 begin
                  { povolena mnozina symbolov }
                   u:= getstr(t,i,[icao_NXIT]);
                   v:= getstr(u,2,[icao_NXT]);
                   ssym:= [];
                   for j:= 1 to getstritems(v,[',']) do ssym:= ssym + [get_OBtyp (uni_str(getstr(v,j,[','])))];
                   _SYM_update(fn,getstr(u,1,[icao_NXT]),ssym,$FFFF,map_MARK,cl_MARK, 0,0, 0,0)
                 end
               else _SYM_update(fn,'',[],$FFFF,map_MARK,cl_MARK, 0,0, 0,0)
             end;
           Close(fT)
         end
    end;


procedure MAP_update;
    begin
      cl_FIRf    := read_cfg_word(MAPscfg,cfg_cl_FIRf, cl_FIRf);
      cl_FIR     := read_cfg_word(MAPscfg,cfg_cl_FIR , cl_FIR);

      cl_ACCf    := read_cfg_word(MAPscfg,cfg_cl_ACCf, cl_ACCf);
      GrPrim.cl_ACC := read_cfg_word(MAPscfg,cfg_cl_ACC , cl_ACC);
      cl_ACCsecf := read_cfg_word(MAPscfg,cfg_cl_ACCsecf, cl_ACCsecf);
      cl_ACCsec  := read_cfg_word(MAPscfg,cfg_cl_ACCsec,  cl_ACCsec);

      cl_APPf    := read_cfg_word(MAPscfg,cfg_cl_APPf, cl_APPf);
      cl_APP     := read_cfg_word(MAPscfg,cfg_cl_APP , cl_APP);
      cl_APPsecf := read_cfg_word(MAPscfg,cfg_cl_APPsecf, cl_APPsecf);
      cl_APPsec  := read_cfg_word(MAPscfg,cfg_cl_APPsec,  cl_APPsec);

      cl_AWYf    := read_cfg_word(MAPscfg,cfg_cl_AWYf, cl_AWYf);
      cl_AWY     := read_cfg_word(MAPscfg,cfg_cl_AWY , cl_AWY);
      cl_AWY_    := read_cfg_word(MAPscfg,cfg_cl_AWY_, cl_AWY_);
      cl_ILS_    := read_cfg_word(MAPscfg,cfg_cl_ILS_, cl_ILS_);


      cl_TMAf    := read_cfg_word(MAPscfg,cfg_cl_TMAf, cl_TMAf);
      cl_TMA     := read_cfg_word(MAPscfg,cfg_cl_TMA,  cl_TMA);

      cl_CTRf    := read_cfg_word(MAPscfg,cfg_cl_CTRf, cl_CTRf);
      cl_CTR     := read_cfg_word(MAPscfg,cfg_cl_CTR , cl_CTR);

      cl_ZAMa    := read_cfg_word(MAPscfg,cfg_cl_ZAMa, cl_ZAMa);
      cl_ZAMp    := read_cfg_word(MAPscfg,cfg_cl_ZAMp, cl_ZAMp);

      cl_Rf      := read_cfg_word(MAPscfg,cfg_cl_Rf  , cl_Rf);
      cl_R       := read_cfg_word(MAPscfg,cfg_cl_R   , cl_R);

      cl_TSAa    := read_cfg_word(MAPscfg,cfg_cl_TSAa, cl_TSAa);
      cl_TSAp    := read_cfg_word(MAPscfg,cfg_cl_TSAp, cl_TSAp);

      cl_PRSa    := read_cfg_word(MAPscfg,cfg_cl_PRSa, cl_PRSa);
      cl_PRSp    := read_cfg_word(MAPscfg,cfg_cl_PRSp, cl_PRSp);


      cl_PAV0    := read_cfg_word(MAPscfg,cfg_cl_PAV0, cl_PAV0);
      cl_PAV1    := read_cfg_word(MAPscfg,cfg_cl_PAV1, cl_PAV1);

      cl_LDM0    := read_cfg_word(MAPscfg,cfg_cl_LDM0, cl_LDM0);
      cl_LDM1    := read_cfg_word(MAPscfg,cfg_cl_LDM1, cl_LDM1);
      cl_LDM2    := read_cfg_word(MAPscfg,cfg_cl_LDM2, cl_LDM2);

      cl_MARK    := read_cfg_word(MAPscfg,cfg_cl_MARK, cl_MARK);
      cl_DESC    := read_cfg_word(MAPscfg,cfg_cl_DESC, cl_DESC);

      cl_GRP_act_:= read_cfg_word(MAPscfg,cfg_cl_GRP_act_, cl_GRP_act_)
    end;
