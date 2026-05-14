 const _p_zarad_FPL4      : pproc_zarad_FPL4 = nil;
       _p_zarad_FPLC_FPL4 : pproc_p = nil;
       _p_zarad_PLN_FPL4  : pproc_p = nil;
       _p_zarad_RPL_FPL4  : pproc_p = nil;


 {$IFDEF PLN}
  procedure zarad_PLN_FPL4(PLN: PPLN); far;
      var   FPL  : DFPL4;
            key,res : string;
            ires,dbind : int;
            check_par : word;
      begin
        if _p_zarad_PLN_FPL4<>nil then TProc_p(_p_zarad_PLN_FPL4)(PLN);

        {$IFDEF PROCESS_FPL4}
        {
          - funkcia predpoklada, ze ak je volana tato fcia, to znamena,
            ze v prijatom PLNe je zmena oproti povodnemu PLNu alebo
            je to novy, preto je potrebne aktualizovat FPL4 a nasledne
            zaznam FDR;

          - aktualizacia zatia spociva len v zaradeni zazanmu o existencii
            povovolenia do pola 18 alebo jeho aktualizacii o potvrdenie
            (PLN/PPL, PLN/FMU2341) alebo vytvoreni noveho FPL4, ak este
            neexistuje

        }
         key:= codekey_PLN(PLN);
         dbind:= read_FPL4(key,@FPL);
         if dbind >-1 then update_PLN_to_FPL4 (PLN^,FPL)
         else code_PLN_to_FPL4 (PLN^,FPL);
         {pdbind:= @dbind;}

         FPL.src:= 0; fplsrc_decode (FPL._18, FPL.src);

         check_par:= cm_zarad_FPL4 or cm_check_FPL4_EET or cm_rozosli_FPL4;
         _FPL4._zaradenie_FPL4 (@FPL,check_par,'',aftn, res,ires, @dbind);
         disp_FPL4(@FPL);
        {$ENDIF}
      end;
 {$ENDIF}


 {$IFDEF RPL}
  procedure zarad_RPL_FPL4 (RPL: PRPLF); far;
      var   FPL  : DFPL4;
            key,res : string;
            dbind,ires : int;
            check_par : word;
      begin
        if _p_zarad_RPL_FPL4<>nil then TProc_p(_p_zarad_RPL_FPL4)(RPL);

        {$IFDEF PROCESS_FPL4}
         key:= codekey_FPL4(@RPL^.fpl);
         dbind:= read_FPL4(key,@FPL);

         if dbind >-1 then
            begin
              update_RPL_to_FPL4 (RPL^,FPL);
            end
         else begin
                new_FPL4(@RPL^.fpl,@FPL);
                FPL._3:= hd_FPL;
              end;

         FPL.src:= 0; fplsrc_decode (FPL._18, FPL.src);

         check_par:= cm_zarad_FPL4 or cm_rozosli_FPL4;
         _FPL4._zaradenie_FPL4 (@FPL,check_par,'',letvis,res,ires, @dbind);
         disp_FPL4(@FPL);
        {$ENDIF}
      end;
 {$ENDIF}


 procedure _zaradenie_FPL4 (FPL: PFPL4;
                            var check_par: word; _stat: string; _src: fdp_src;
                            var res: string; var ires: int;
                            dbind: pint
                          ); far;

     var   ores : int;
           bres : bool;
           key  : string;

           FDR  : DFDR;
           FPLc : DFPLC;

           p: PFPLC;
           o: P_OFPL;

     begin
       res:= ''; ires:= -1;

       if _p_zarad_FPL4<>nil then proc_zarad_FPL4(_p_zarad_FPL4) (FPL,check_par,_stat,_src,res,ires, dbind);

      { zaradenie planu do zoznamu preaktivavanych letov FDR
        a pripadna aktivacia/deaktivacia spravy o lete FPLC
      }

       {$IFDEF FPL4_ACT}
        key:= codekey_FPL4(FPL);
        if (oFDR<>nil) then ores:= oFDR^.find_key(key)
        else ores:= -1;

        if in_icao_head (FPL^.stat,ms_ICAOcnl+ms_ICAOarr,bres) then
           begin
           { a) odmazanie zaznamu preaktivovanych letov
           } if ores>-1 then oFDR^.Del(ores);

           { b) odmazanie zaznamu aktivovanych letov
           }
             p:= find_FPLCa(key);
             if p<>nil then
                begin
                  new_cFPL(p,@FPLc);
                 _zarad_FPLc(@FPLc,FPL^.stat, true,[],user,'', true,false,false, p,true);
                 disp_cFPL(@FPLc);
              end;
           end

        else begin
             { a) zaradenie do zaznamu
                  preaktivovanych planov
             } if oFDR<>nil then
                 begin
                   if (FPL^.data<>nil) and (FPL^.data^.fdr<>nil) then new_FDR_data(FPL^.data^.fdr,@FDR)
                   else code_FPL4data_to_FDR (FPL^,FDR);
                   if     (ores<>-1) and in_icao_head (PFDR(oFDR^.ap^[ores])^.stat,ms_ICAOact,bres)
                      and in_icao_head (FPL^.stat,ms_ICAOplan,bres)
                          then
                       begin
                       { kontrola aby sprava o plane neprepisala
                         aktivovany let
                       } FPL^.stat:= PFDR(oFDR^.ap^[ores])^.stat;
                         FDR.stat:= FPL^.stat;
                       end
                   else FDR.stat:= FPL^.stat;
                   oFDR^.Add(@FDR);
                   if (p_fdr_dbscroller<>nil) then p_fdr_dbscroller^.data_update(@FDR);
                   disp_FDR(@FDR);
                 end;

             { b) pridanie zaznamu do zoznamu aktivovanych letov,
                  len ak sprava nie je prijata od LETVISu, pretoze
                  v tom pripade bude dorucena sprava FPLC zvlast;
                  ignoruju sa spravy CHG, DLA realizovane
                  na aktivovanych letoch
             } if      ( (_src in [user,ext_])
                         or (check_par or cm_spracuj_FPL4_FPLC <> 0)
                       )
                   and _FPL4act (FPL)
                    then
                 begin
                   _zarad_FPLc(FPL^.data^.fdr^.fpl,'',true,[],letvis,'',true,false,false, nil,false);
                 end;
             end;
       {$ENDIF}
     end;



 procedure zarad_FPLC_FPL4(FPL: PDcFPL); far;
     var   FP4  : DFPL4;
           FDR  : PFDR;
           key  : string;
           ires : int;
           bres : bool;
     begin
       if _p_zarad_FPLC_FPL4<>nil then TProc_p(_p_zarad_FPLC_FPL4)(FPL);

       if    ((FPL=nil) or (oFDR=nil))
          or (not ((FPL^.stt=hd_EST) or (FPL^.stt=hd_ACT) or (FPL^.stt=hd_CNL)))
             then Exit;
       key:= codekey_FPLC(FPL);

       { vyhladanie zaznamu o aktivovanm lete a jeho plane,
         zapis o ich aktivacii...
       }

       {$IFDEF PROCESS_FPL4}
       { ak bola podana sprava o aktivovanom lete,
         skontroluje sa, ci uz bola spracovana jeho plan,
         aby neostal v ocakavani aktivacie...

         moze sa tak stat, len ak sa zaradzuje prilis vopred len na zaklade podanej spravy EST
       }
        ires:= oFDR^.find_key(key);
        if (ires=-1) or in_icao_head (PFDR(oFDR^.ap^[ires])^.stat,ms_ICAOact,bres) then Exit;

       { zaradenie aktivovaneho FDR sposobi jeho uvolnenie
         z radu ocakavanyc letov
       }
        new_FDR_(oFDR^.ap^[ires],FDR);
        FDR^.stat:= FPL^.stt;
        oFDR^.add(FDR);
        disp_FDR_(FDR);

       { ENDIF}
       { IFDEF PROCESS_FPL4}

       { kvoli preaktivovaniu po restarte sa opravi i zapis FPL na DB,
         sprava FPL4 sa nerozosiela, pretoze sa distribuuje FPLC;
         tuto opravu si urobi kazda stanica sama,

         robia to len stanice s "PROCESS_FPL4",
         tam je to rychle, kde nie je oFDR,
         zdrzovalo by to
       }
        ires:= read_FPL4(key,@FP4);
        if ires >-1 then
           begin
             FP4.stat:= FPL^.stt;
             save_FPL4(@FP4);
             disp_FPL4(@FP4);
           end;
       {$ENDIF}
     end;


 procedure  initialize_FPLs;
     begin
      {$IFDEF FPL4_ACT}
       _p_zarad_FPL4      := p_zarad_FPL4;
       p_zarad_FPL4       := @_zaradenie_FPL4;

       _p_zarad_FPLC_FPL4 := p_zarad_FPLC_FPL4;
       p_zarad_FPLC_FPL4  := @zarad_FPLC_FPL4;
      {$ENDIF}

      {$IFDEF PROCESS_FPL4}
       {$IFDEF PLN}
        _p_zarad_PLN_FPL4 := p_zarad_PLN_FPL4;
        p_zarad_PLN_FPL4  := @zarad_PLN_FPL4;
       {$ENDIF}

       {$IFDEF RPL}
        _p_zarad_RPL_FPL4 := p_zarad_RPL_FPL4;
        p_zarad_RPL_FPL4  := @zarad_RPL_FPL4;
       {$ENDIF}
      {$ENDIF}
     end;

