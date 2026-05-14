{ -----------------------------------------
   prehlad poslednych archivovanych planov
  -----------------------------------------  }

{ ----------
   cFPL
  ----------
}

 function filter_spracuj_ukoncene_cFPL(FPL: PDcFPL; _item: PFPL_item_filter): bool; far;
    var   is : bool;
    begin
      {is:= (    ((idn<>nil) and (idn^=FPL^.idn))
             or (((idn=nil) or (cut_(idn^)='')) and (cFPL^.find(FPL)=-1))
           );}
      is:= find_FPLCa(codekey_FPLC(FPL))=nil;
      {$IFDEF SECTORS}
       if is and S_ARCHIV {S_DISPLAY} then
          begin
            sektor_FPLc (FPL);
            with FPL^ do is:= ((sec and s_th)<>0) or ((sec and s_is)<>0)
          end;
      {$ENDIF}
      filter_spracuj_ukoncene_cFPL:= is
    end;

 function handle__spracuj_ukoncene_cFPL(FPL: PDcFPL): bool;  { far; - v interface }
    begin
      handle__spracuj_ukoncene_cFPL:= false;
      formular_cFPL(FPL,letvis,false, tit_reload_cFPL,pos_frm_FPLC,false,false,false)
    end;


 procedure spracuj_ukoncene_cFPL;
     {var   idn: string;}
     begin
       {if formular_s(idn,kod_7a,tit_reload_cFPL, nil,1, @setABC,@setNil,1, nil,false,true,false) then}
          spracuj_cFPL('',
                       find_and_process_FPLC, @_arch_fn_cFPL, nil,
                       nil, @filter_spracuj_ukoncene_cFPL,
                       @handle__spracuj_ukoncene_cFPL, _TBFunc_p,
                       tit_fnsh_cFPL, nil,nil
                      )
     end;



 function filter_spracuj_archivovane_cFPL(FPL: PDcFPL; idn: pstring): bool; far;
    var   is : bool;
    begin
     is:= true;
     {$IFDEF SECTORS}
      if is and S_ARCHIV {S_DISPLAY} then
         begin
           sektor_FPLc (FPL);
           with FPL^ do is:= ((sec and s_th)<>0) or ((sec and s_is)<>0)
         end;
     {$ENDIF}
      filter_spracuj_archivovane_cFPL:= is
    end;

 function handle__spracuj_archivovane_cFPL(FPL: PDcFPL): bool; far;
    begin
      handle__spracuj_archivovane_cFPL:= false;
      formular_cFPL(FPL,letvis,true, tit_arch_cFPL, pos_frm_FPLC,false,false,false)
    end;

 procedure prehlad_cFPL_ARCH(arch: bool);
     var   fn,tit : string;
     begin
       if arch then
          begin
            tit:= tit_fnsh_cFPL;
            fn:= get_ARCH_FN (pathARCH_FPL_C,'*',tit)
          end
       else begin
              tit:= tit_fnsh_cFPL;
              fn:= get_ARCH_FN (pathFPL_C,'*',tit)
            end;
       spracuj_cFPL(fn, false,
                    nil,nil,
                    nil, @filter_spracuj_archivovane_cFPL, {cnl_stat(cnst_all_valid), @_is_stat,}
                    @handle__spracuj_archivovane_cFPL, _TBFunc_p,
                    tit+' - '+decode_date_fn(getstr(fn,getstritems(fn,['\']),['\'])), nil,nil
                   )
     end;



{ ----------
   mFPL
  ----------
}
{$IFNDEF FPLM_DISABLED}

 function filter_spracuj_ukoncene_mFPL(FPL: PDmFPL; _item: PFPL_item_filter): bool; far;
    begin
      filter_spracuj_ukoncene_mFPL:= (is_mFPL(FPL)) and (mFPL^.find(FPL)=-1)
                      {and (    ((idn<>nil) and (idn^=FPL^.idn))
                            or (((idn=nil) or (cut_(idn^)='')) )
                          )}
    end;

 function handle__spracuj_ukoncene_mFPL(FPL: PDmFPL): bool;
    var   tit : string;
    begin
      handle__spracuj_ukoncene_mFPL:= false;
      if is_mFPL(FPL) then tit:= tit_reload_mFPL else tit:= tit_reload_mFPL;
      formular_mFPL(FPL,letvis,FPL^.stat,false, tit,i_15M,nil,hlp_mFPL)
    end;

 procedure spracuj_ukoncene_mFPL;
     {var   idn: string;}
     begin
       {if formular_s(idn,kod_7a,'STRIP', nil,1, @setABC,@setNil,1, nil,false,true,false) then}
          spracuj_mFPL(find_and_process_FPLM,find_and_process_FPLM,
                       false,false,false,true,
                       '', @filter_spracuj_ukoncene_mFPL,
                       @handle__spracuj_ukoncene_mFPL, _TBFunc_p,
                       false,false,
                       tit_fnsh_mFPL, nil,nil
                      )
     end;


 { ----------
   inso FPL
   ----------
 }

 function filter_spracuj_ukoncene_oFPL(FPL: PDmFPL; _item: PFPL_item_filter): bool; far;
    begin
      {$IFDEF FPLO}
       filter_spracuj_ukoncene_oFPL:= is_oFPL(FPL) and (oFPL^.find(FPL)=-1)
                      {
                      and (    ((idn<>nil) and (idn^=FPL^.idn))
                            or (((idn=nil) or (cut_(idn^)='')) and (oFPL^.find(FPL)=-1))
                          )
                      }
      {$ELSE}
       filter_spracuj_ukoncene_oFPL:= false
      {$ENDIF}
    end;

 procedure spracuj_ukoncene_oFPL;
     {var   idn: string;}
     begin
      {$IFDEF FPLO}
       {if formular_s(idn,kod_7a,'STRIP', nil,1, @setABC,@setNil,1, nil,false,true,false) then}
          spracuj_mFPL(find_and_process_FPLM,find_and_process_FPLM,
                       false,false,false,true,
                       '', @filter_spracuj_ukoncene_oFPL,
                       @handle__spracuj_ukoncene_mFPL, _TBFunc_p,
                       false,false,
                       tit_fnsh_oFPL, nil,nil
                      )
      {$ENDIF}
     end;


 { Zvlastna funkcia len kvoli urychleniu nacitania,
   pretoze FPL podane z vojenskych pracovisk sa
   tykaju vojenskych i inych letov...
 }
   const  pmi: P_OFPL = nil;
          poi: P_OFPL = nil;

   function _FPL_load(p: pointer; FPL: PDmFPL): bool; far;
        begin
          if is_mFPL(FPL) then p:= pmi else p:= poi;
          if p<>nil then nacitaj_plan(p,FPL);
          _FPL_load:= false
        end;

   procedure load_mFPL(FN: string; pm,po: P_OFPL);
       var   FPL: DmFPL;
       begin
         pmi:= pm; poi:= po;
         DB_prehladaj(@_FPL_load,nil,@FPL,@disp_mFPL, FN,db_mFPL_RIADKOV,@decodeDB_FPLM,@codekey_FPLM,true,'')
       end;

{$ENDIF}