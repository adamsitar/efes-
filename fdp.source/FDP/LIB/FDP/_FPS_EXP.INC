{$IFDEF DB_DBASE}

 const DBFdesc_sta_fplc_items = 11;
       DBFdesc_sta_fplc : array[0..DBFdesc_sta_fplc_items-1] of TDBFfdesc =
       ((name:tit_fps_N;      typ:dbfCISLO;  dlz:kod_fps_NMB),
        (name:tit_fps_FLO;    typ:dbfSTRING; dlz:kod_fps_FLO),
        (name:tit_fps_FLIGHT; typ:dbfSTRING; dlz:kod_7a),
        (name:tit_fps_TYPE;   typ:dbfSTRING; dlz:kod_9),
        (name:tit_fps_DEP;    typ:dbfSTRING; dlz:kod_AP+kod_TIME),
        (name:tit_fps_DEST;   typ:dbfSTRING; dlz:kod_AP+kod_TIME),
        (name:tit_fps_IN;     typ:dbfSTRING; dlz:kod_NDB+kod_TIME+1),
        (name:tit_fps_EXI;    typ:dbfSTRING; dlz:kod_NDB+kod_TIME+1),
        (name:tit_fps_REG;    typ:dbfSTRING; dlz:kod_fps_REG),
        (name:tit_fps_OPR;    typ:dbfSTRING; dlz:kod_fps_OPR),
        (name:tit_fps_KM ;    typ:dbfCISLO;  dlz:kod_fps_KM)
       );


 type  p_rec_fps = ^type_rec_fps;
       type_rec_fps = record
         ind : int;
         fps : PFPS;
       end;

 procedure code_dbf_sta_fplc(p: p_rec_fps; buff: PDBF_buff; size: int{; polia: PDBFfdescs}); far;
     var   is  : bool;
           s   : string;
           pos : int;
     begin
       pos:= 0;

       code_dbf_CISLO  (p^.ind, buff, pos, DBFdesc_sta_fplc[0].dlz,size);
       code_dbf_STRING (cut_3(strpas(p^.fps^.flo),kod_FPS_FLO), buff, pos, DBFdesc_sta_fplc[1].dlz,size);
       code_dbf_STRING (p^.fps^.fdr.idn, buff, pos, DBFdesc_sta_fplc[2].dlz,size);
       code_dbf_STRING (p^.fps^.fdr.typ, buff, pos, DBFdesc_sta_fplc[3].dlz,size);

       with p^.fps^.fdr do
         begin
           is:= (dep.h<>0) or (arr.h<>0) or (dep.m<>0) or (arr.m<>0);

           if is then s:= code_l4_utc(dep.h,dep.m) else s:= '';
           code_dbf_STRING (dep.kod+s, buff, pos, DBFdesc_sta_fplc[4].dlz,size);

           if is then s:= code_l4_utc(arr.h,arr.m) else s:= '';
           code_dbf_STRING (arr.kod+s, buff, pos, DBFdesc_sta_fplc[5].dlz,size);

           if eet.kod<>'' then s:= rightchar(eet.kod,kod_NDB,' ')+code_l4_utc(eet.h,eet.m) else s:= '';
           code_dbf_STRING (s, buff, pos, DBFdesc_sta_fplc[6].dlz,size);

           if exi.kod<>'' then s:= rightchar(exi.kod,kod_NDB,' ')+code_l4_utc(exi.h,exi.m) else s:= '';
           code_dbf_STRING (s, buff, pos, DBFdesc_sta_fplc[7].dlz,size);
         end;

       code_dbf_STRING (cut_3(strpas(p^.fps^.reg),kod_FPS_REG), buff, pos, DBFdesc_sta_fplc[8].dlz,size);
       code_dbf_STRING (cut_3(strpas(p^.fps^.opr),kod_FPS_OPR), buff, pos, DBFdesc_sta_fplc[9].dlz,size);

       if p^.fps^.dr<>0 then code_dbf_CISLO (p^.fps^.dr, buff, pos, DBFdesc_sta_fplc[10].dlz,size);
     end;

 procedure decode_dbf_sta_fplc(buff: PDBF_buff; p: p_rec_fps; size: int{; polia: PDBFfdescs}); far;
     begin
     end;


 type  p_ext_data = ^type_ext_data;
       type_ext_data = record
         dbf  : PDBF;
         fpss : PFPSs;
         poc  : int;
         ind  : int;
       end;

 function  _export_FPLS (data: p_ext_data; o: PProcess): bool; far;
     var   FPS  : PFPS;
           bres : bool;
           fd   : type_rec_fps;
     begin
       bres:= data^.poc<=data^.ind;
       _export_FPLS:= bres;
       if bres then Exit;

       FPS:= data^.fpss^[data^.ind];
       if o<>nil then o^.new_item(cut_(FPS^.fdr.idn+icao_ARR+FPS^.fdr.dep.kod));

       fd.ind:= data^.ind+1;
       fd.fps:= FPS;
       data^.dbf^.zapis(@fd,-1,false);
       inc(data^.ind)
     end;

 procedure export_FPLS(_fn: string; FPSs: PFPSs; top: int);
     var   fn   : string;
           dir  : DirStr; name: NameStr; ext: ExtStr;
           data : type_ext_data;
           bres : bool;
           ires : int;
     begin
       if (FExists(_fn)<>0) then Exit;

      { vytvorenie subora, ak bol binarny subor aktualizovany,
        a kopirovany subor existuje, tak jeho odmazanie :
      }
       fillchar(data,sizeof(data),0);
       fsplit(_fn, dir,name,ext);
       fn:= dir+name+'.'+extDBF;

       if (FExists(fn)=0) and (_GetFTime(fn)<_GetFTime(_fn)) then DelFile(fn);
       data.dbf:= new(PDBF,Init(fn,false,
                           @DBFdesc_sta_fplc,DBFdesc_sta_fplc_items,
                           @code_dbf_sta_fplc,@decode_dbf_sta_fplc,-1
                          ));

      { najdenie posledneho transformovanho zaznamu
        a pokracovanie od neho
      }
       data.fpss:= FPSs;
       data.poc:= top+1;
       data.ind:= data.dbf^.poloziek;
       bres:= InfoProcess (msgWAITING,titDLA,tit_FPSext+': ',rightchar('',kod_7a+1+kod_AP,' '),@_export_FPLS,@data);
       dispose(data.dbf,Done);
       if not bres then Exit;

      { ak transformacia bola uspesna,
        skopirovanie na disketu
      }
       InfoCakaj(msgWAITING,msgCOPY);
       ires:= BackupFile(fn);
       InfoCakaj_zatvor;
       if ires<>0 then Err2('',ErrorMessage(ires,''));
     end;

{$ENDIF}