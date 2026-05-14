{$IFDEF SSR_MANAGEMENT}
{ spravne priradenie ssr ?
}
 function  _zarad_FPLCssr (FPL : PFPLC;

                           zaradit : bool;
                           var res : string;
                           err : pstring;

                           FPLp: PDcFPL;
                           _hladany : bool
                          ): int;
    var    key,ssrp : string;
    begin
      _zarad_FPLCssr:= -1;
      {if FPLC_SSR then Exit;}

      key:= codekey_FPLC(FPL);
      if not _hladany then FPLp:= find_FPLCa (key);
      if FPLp<>nil then ssrp:= FPLp^.ssr else ssrp:= '';

      _zarad_FPLCssr:= zarad_ssr (key,FPL^.ssr,ssrp,exi_FPLC(FPL),FPL^.stt,zaradit,res,err)
    end;
{$ENDIF}


 {$IFDEF EDD}
   procedure add_prop_FPLc(FPL: PDcFPL);
       begin
       { zaradenie ku navrhovanym, pokial nebol uz prebrany
       } if (cFPL^.find(FPL)>-1) then add_FPLc(FPL)
         else PROP_cFPL^.add(FPL)
       end;
 {$ENDIF}

 procedure add_FPLc(FPL: PDcFPL);
     begin
       cFPL^.add(FPL)
     end;


{ zaradenie spravy medzi aktivne
}
 function _zarad_FPLc(FPL: PDcFPL; _stat: string;
                      _send: bool; _nd: Tnd_nd_set;
                      _src: fdp_src;
                      _src_adr : TNETadr;

                      _ssr,               { kontrola duplicity _ssr    }
                      _fpl4,              { aktivacia _fpl4            }
                      _prop: bool;        { zaradenie medzi navrhovane }

                      FPLp : PDcFPL;
                      _hladany : bool
                     ): bool;

    var   res,err : string;
          ires : int;
    begin
      _zarad_FPLc:= true;
      if _stat<>'' then FPL^.stt:= _stat;
      format_cFPL(FPL);

      {$IFDEF FLI_COORDINATION} {$DEFINE HLADAT} {$ENDIF}
      {$IFDEF SSR_MANAGEMENT}   {$DEFINE HLADAT} {$ENDIF}

      {$IFDEF HLADAT}
        if not _hladany then
           begin
             FPLp:= find_FPLCa (codekey_FPLC(FPL));
             _hladany:= true;
           end;
      {$ENDIF}

      {$IFDEF FLI_COORDINATION}
      { uchovanie informacie o odoslanych FLI
      } if FPLp<>nil then _decode_l4_fli(_code_l4_fli(FPLp),FPL);
        FPL^.przn[p_fli]:= _najdi_FLI(FPL,0);
      {$ENDIF}

      {$IFDEF SSR_MANAGEMENT}
      { kontrola na spravnost priradenia kodu ssr vykona pri priradzovani kodu
        (priradzuje sa rucne, ak by to bolo automaticky, tak tu...)
        a pri spracovani prijatej spravy FPLC (zatial len z NET...)
      }
        if _ssr then
           begin
             _zarad_FPLCssr (FPL, true,res,@err, FPLp,_hladany);
             {$IFDEF SSR_SERVER}
              if FPLC_SSR and (_src_adr<>'') and (ires=err_ssr_is_used) then
                 begin
                   if (_src_adr<>SERVERaddress) and (_src_adr<>BACKUPaddress) then
                      NETsend_msg (_src_adr,spr_SSR_ERR,@err[1],length(err),false,net_flag_SEND)
                   else if SERVERnode<>-1 then NETsend_msg (SERVERaddress,spr_SSR_ERR,@err[1],length(err),false,net_flag_SEND);
                  end;
             {$ENDIF}
           end;
      {$ENDIF}

      {$UNDEF HLADAT}

      save_cFPL(FPL);

      {$IFDEF PROCESS_FPL4}
      { Spracovanie spravy o aktivovani (DEP,ACT), vlete (EST,...) alebo zruseni
        letu (CNL) musi sposobit, ze sa aktualizuju udaje o plane letu, aby na
        zaklade spravy o aktivacii alebo zruseni bol plan vyradeny z radu planov
        ocakavajucich aktivaciu.

        Tuto funkciu realizuje modul, ktory ma na starosti FPL4,
        bud pretazenim fcie alebo externym odkazom
      }
       if _fpl4 and ((not _hladany) or (FPLp=nil)) and (p_zarad_FPLC_FPL4<>nil) then TProc_p(p_zarad_FPLC_FPL4)(FPL);
      {$ENDIF}

      {$IFDEF STATISTIKA_SERVER}
       if (p_save_STA_FPLC<>nil) then TProc_p(p_save_STA_FPLC)(FPL);
      {$ENDIF}

      { musi byt na konci pretoze tato funkcia moze byt volana
        po spracovani z handlera tohto objektu objektu, ktory
        moze data uvolnit z pamate a dostanem takto referenciu
        na odalokovanu pamat
      }
      if _send then _odosli_FPLc(FPL,_src,_nd);
      {$IFDEF EDD}
        if _prop then add_prop_FPLc(FPL)
        else
      {$ENDIF}
             p_add_FPLc(FPL);
    end;

 function zarad_FPLc(FPL: PDcFPL; _stat: string; _send: bool; _src: fdp_src): bool;
    begin
      zarad_FPLc:= _zarad_FPLc(FPL,_stat,_send,[],_src,'',true,true,false, nil,false)
    end;
