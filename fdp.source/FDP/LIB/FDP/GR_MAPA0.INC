{ -----------------------------------------------------------
  Zo subora nacita kod a podla neho vytvori grf. primitivum;
  na zaciatku sa nastavi _lastGrOb : PTGrOb = nil
}
procedure mapy_pridaj_primitivum(var _MapOb: TMapOb; GP: PTGrOb; var _lastGrOb: PTGrOb);
    begin
      if _MapOb.GP = nil then _MapOb.GP:= GP
      else _lastGrOb^.SetGP(GP);  { prida novy graficky objekt na koniec }
      _lastGrOb:= GP
    end;

function  mapy_nacitaj_suradnice(var _InF: file; var _MapOb: TMapOb; var _lastGrOb: PTGrOb; var kod : TtypGRP): PTGrOb;
    var   GP  : PTGrOb;
          res : int;
    begin
      BlockRead(_Inf,kod,SizeOf(kod),res);
      case kod of
        gr_Poly    : GP:= New(PTPoly,     Init(kod,_InF, _MapOb.cl,_MapOb.ciar));
        gr_FPoly   : GP:= New(PTFillPoly, Init(kod,_InF, _MapOb.cl,_MapOb.ciar));
        gr_KrVys   : GP:= New(PTKrVys,    Init(kod,_InF, _MapOb.cl,_MapOb.ciar));
        gr_FKrVys  : GP:= New(PTFillKrVys,Init(kod,_InF, _MapOb.cl,_MapOb.ciar));
        gr_Kruz    : GP:= New(PTKruz,     Init(kod,_InF, _MapOb.cl,_MapOb.ciar));
        gr_FKruz   : GP:= New(PTFillKruz, Init(kod,_InF, _MapOb.cl,_MapOb.ciar));
        gr_SusKruz : GP:= New(PTSusKruz,  Init(kod,_InF, _MapOb.cl,_MapOb.ciar));
        gr_SusAzim : GP:= New(PTSusAzim,  Init(kod,_InF, _MapOb.cl,_MapOb.ciar));
        gr_StSiet  : GP:= New(PTStSiet,   Init(kod,_InF, _MapOb.cl,_MapOb.ciar));
        gr_Mark10  : GP:= New(PTMark10,   Init(kod,_InF, _MapOb.cl,_MapOb.ciar));
        gr_Mark11  : GP:= New(PTMark11,   Init(kod,_InF, _MapOb.cl,_MapOb.ciar));
        gr_Mark13  : GP:= New(PTMark13,   Init(kod,_InF, _MapOb.cl,_MapOb.ciar))
        else GP:= nil
      end;
      if GP<>nil then
         begin
           (*{IFDEF SK} if _MapOb.typ=map_Pf then GP^.fill:= _fill_; {ENDIF}*)
           mapy_pridaj_primitivum(_MapOb, GP, _lastGrOb)
         end;
      mapy_nacitaj_suradnice:= GP
    end; { nacitaj_suradnice }


procedure mapy_zotried_mapy(ZozMap: PZozMap);
    var   Pred,Za,Pom : PTMapOb;
          vymenic     : bool;
    begin
      if ZozMap<>nil then with ZozMap^ do
         repeat
           vymenic:= false;
           JdiNaZacatek;
           repeat
             Pred:= DejAktPrvek;
             Za  := DejDalsi;
             if (Pred<>nil) and (Za<>nil) and (Pred^.prior > Za^.prior) then
                begin
                  vymenic:= true;
                  Pom:= VyjmiPrvek(Za);
                  VlozPredAkt(Pom)
                end;
           until Za=nil;
         until not vymenic
    end; { zotried_mapy }


procedure mapy_set_fill(ZozMap: PZozMap; MapOb: PTMapOb; fill: TGRPfill; typ,prior: word);
    var   GP: PTGrOb;
    begin
     {$IFDEF DRAW}
      if MapOb<>nil then
         begin
           GP:= MapOb^.GP;
           while GP<>nil do
             begin
               if GP^.fill_en then GP^.set_fill(fill);
               GP:= GP^.GP
             end;
           MapOb^.typ:= typ;
           MapOb^.prior:= prior;
           MapOb^.cl:= mapa_farba(prior)
         end;
      if ZozMap<>nil then mapy_zotried_mapy(ZozMap)
     {$ENDIF}
    end;


function mapy_nacitaj_data(subor: string; MapOb: PTMapOb): PTMapOb;
   var   InF,OuF  : file;
         HeadFile : THeadFile;
         lastGrOb,GP : PTGrOb;
         kod      : TtypGRP;
         poc      : TGPpocet;
         res      : int;
         s        : string;
   begin
     mapy_nacitaj_data:= nil;
     if Exists(subor)<>0 then {Varovanie} Exit;

     Assign(InF,subor);
     Reset (InF,1);
     if MapOb^.GP<>nil then Dispose(MapOb^.GP,Done);
     BlockRead(InF, headfile, SizeOf(THeadFile), res);

    { nacitanie primitiv(ov) zo subora
    }
     lastGrOb:= nil;
     repeat
       GP:= mapy_nacitaj_suradnice(Inf,MapOb^,lastGrOb,kod);
     until FilePos(InF) = FileSize(InF);
     ResetIOError;

    { prohibited mapy su dodavane len ako hranice;
      FDP ich chce fillovane...
      velmi nestandartny postup
    }
     if (MapOb^.typ=map_P) or (MapOb^.typ=map_Pf) then mapy_set_fill(nil,MapOb,_fill_,map_Pf,map_Pf);

     {$IFDEF DEBUG}
     { Len specializovana pomocna funckia pre rozbitie/zjednotenie mapy

      s:= '1.bak';
      Assign(OuF,s);  Rewrite(OuF,1);
      BlockWrite(OuF, headfile, SizeOf(THeadFile), res);
      BlockWrite(OuF, kod,SizeOf(kod),res);
      GP:= MapOb^.GP; poc:= 0;
      while GP<>nil do
        begin
          poc:= poc + PTPoly(GP)^.pocet;
          GP:= GP^.GP
        end;
      GP:= MapOb^.GP;
      BlockWrite(OuF,GP^.prior,SizeOf(GP^.prior),res);
      BlockWrite(OuF,GP^.farba,SizeOf(GP^.farba),res);
      BlockWrite(OuF,GP^.typc ,SizeOf(GP^.typc) ,res);
      BlockWrite(OuF,poc,SizeOf(poc),res);
      while GP<>nil do
        begin
          GP^.writeGrOb(OuF,false);
          GP:= GP^.GP
        end;
      Close(OuF);}
     {$ENDIF}

     mapy_nacitaj_data:= MapOb;
     Close(InF);
   end; { nacitaj_data }


function mapy_nacitaj_subor(subor: string; ZozMap: PZozMap; zobraz: bool): PTMapOb;
   var   InF      : file;
         HeadFile : THeadFile;
         MapOb    : PTMapOb;
         res      : int;
   begin
     mapy_nacitaj_subor:= nil;
     if Exists(subor)<>0 then Exit;

     Assign(InF,subor);
     Reset (InF,1);

    { nacitanie hlavicky  30 bytes }
     BlockRead(Inf, headfile, SizeOf(THeadFile), res);
     ResetIOError;
     Close(InF);
     if     (HeadFile.magic_number <> GRP_magic_number_KRASOVSKIJ)
        and (HeadFile.magic_number <> GRP_magic_number_WGS84)
        then {Mess...} Exit;

     FSplit(subor, sDir,sName,sExt);
     MapOb:= new_MapOb(UpString(sName), headfile.line_prior,headfile.line_prior,0,0{headfile.line_color}, zobraz,false);
     mapy_nacitaj_data(subor, MapOb);
     if ZozMap<>nil then ZozMap^.PridejNaKonec(MapOb);
     mapy_nacitaj_subor:= MapOb
   end; { nacitaj_subor }


{ -----------------------------------------------------------

}
function mapy_najdi_a_nacitaj_data(MapOb: PTMapOb): PTMapOb;
   var   subor: string;
   begin
     subor:= FindFile(PathToMAPs,MapOb^.naz+ext_MAP);
     if subor<>'' then mapy_najdi_a_nacitaj_data:= mapy_nacitaj_data(subor, MapOb)
     else mapy_najdi_a_nacitaj_data:= nil
   end;

function mapy_najdi_a_nacitaj_subor(subor: string; ZozMap: PZozMap; zobraz: bool): PTMapOb;
   begin
     FSplit(subor, sDir,sName,sExt);
     if sExt=''{<>ext_map} then sExt:= ext_map;
     if sDir=''{<>ext_map} then sDir:= PathToMaps;
     subor:= sName+sExt;
     subor:= FindFile(sDir{PathToMaps},subor);
     if subor<>'' then
        begin
          mapy_najdi_a_nacitaj_subor:= mapy_nacitaj_subor(subor, ZozMap, zobraz);
          mapy_zotried_mapy(ZozMap)
        end
     else mapy_najdi_a_nacitaj_subor:= nil
   end;


{ -----------------------------------------------------------

}
procedure mapy_vytvor_subor(subor: string; tline,lprior,lcolor, fprior,fcolor, eprior,ecolor: word);
    var   HeadFile : THeadFile;
          InF      : file;
          res      : int;
    begin
      with HeadFile do
        begin
          Magic_number := GRP_magic_number_KRASOVSKIJ;
          type_line    := tline;
          line_prior   := lprior;
          line_color   := lcolor;
          fill_prior   := fprior;
          fill_color   := fcolor;
          extra_prior  := eprior;
          extra_color  := ecolor;

          FillChar(Pole12,SizeOf(Pole12),0)
        end;

      Assign(InF,subor);
      Rewrite(InF,1);
      BlockWrite(InF, HeadFile, SizeOf(THeadFile), res);
      Close(InF)
    end;


procedure mapy_vytvor_GP(subor: string; kod: TtypGRP; prior,farba,typc: TparGP);
    var   InF      : file;
          res      : int;
    begin
      Assign(InF,subor);
      Reset(InF,1); Seek(InF,FileSize(InF));
      BlockWrite(InF, kod,   SizeOf(kod),   res);
      BlockWrite(InF, prior, SizeOf(prior), res);
      BlockWrite(InF, farba, SizeOf(farba), res);
      BlockWrite(InF, typc,  SizeOf(typc),  res);
      Close(InF)
    end;
