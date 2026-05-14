 procedure new_SPR(SPR1, SPR2: PSPR);
     begin
       FillChar(SPR2^,SizeOf(DSPR),0);
       if SPR1<>nil then
          begin
            SPR2^:= SPR1^;
            SPR2^.adr := StrNew(SPR1^.adr);
            SPR2^.text:= StrNew(SPR1^.text)
          end
     end;

 procedure disp_SPR(SPR: PSPR);
     begin
       StrDispose(SPR^.adr);
       StrDispose(SPR^.text)
     end;


 function eq_SPR(SPR1,SPR2: PSPR): bool;
    begin
      eq_SPR:=      ((SPR1<>nil) and (SPR2<>nil))
                and (codekey_SPR(SPR1) = codekey_SPR(SPR2))
    end;

 function chg_SPR(SPR1,SPR2 : PSPR): bool;
    begin
      chg_SPR:= not (     eq_SPR   (SPR1,SPR2)
                     and  eq_str0  (SPR1^.adr, SPR2^.adr)
                     and  eq_datum (SPR1^.daz, SPR2^.daz)
                     and           (SPR1^.acs = SPR2^.acs)
                     and  eq_lines (SPR1^.text,SPR2^.text)
                    )
    end;



 {function find_SPR(SPR: PSPR; _if: pointer): int;
    var   SPRi: DSPR;
    begin
      find_SPR:= DB_prehladaj(_if, SPR,@SPRi, @disp_SPR,
                              pathMAIL+get_PLANfn(day,month,year)+'.'+extMAIL,
                              db_SPR_RIADKOV, @decodeDB_SPR
                             )
    end;
 }

 function get_dbSPRfn(SPR: PSPR): string;
    begin
      if SPR<>nil then get_dbSPRfn:= get_DBfn_(SPR^.dap.den,SPR^.dap.mes,SPR^.dap.rok, pathMES,extMES)
      else get_dbSPRfn:= pathMES+get_PLANfn(day,month,year)+'.'+extMES
    end;


 function read_SPR(key: string; SPR: PSPR): int;
    begin
      if (SPR<>nil) and (key<>'') then
         begin
           decodekey_SPR(key, SPR);
           read_SPR:= DB_najdi(SPR, get_dbSPRfn(SPR),
                               db_SPR_RIADKOV, @decodeDB_SPR,@codekey_SPR,
                               true, @disp_SPR, ''
                              )
         end
      else read_SPR:= -1
    end;

 procedure save_SPR(SPR: PSPR);
     begin
       DB_oprav(SPR, get_dbSPRfn(SPR),
                db_SPR_RIADKOV,@codeDB_SPR,@codekey_SPR,
                @dbchg_SPR, dbattr_SPR
               );
     end;


{ ODOSLANIE/ROZOSLANIE
}
 function send_SPR(SPR: PSPR; adr: TNETadr; wait: bool): bool;
    var   kod    : TNETtyp;
          p_code : pointer;
          p      : pchar;
    begin
      kod:= spr_SPR;
      p_code:= @code_SPR;
      {$IFDEF DATA_BIN}
       p:= nil;
       if NETtype(adr)=FDP0 then
          begin
            {p:= SPR^.adr;
            SPR^.adr:= strpasnew(adr);}
            kod := spr0_SPR;
            p_code:= @code0_SPR
          end;
      {$ENDIF}
      send_SPR:= NETres(NETsend_data
                   (adr, kod,
                    SPR,p_code,@codekey_SPR,@SPR^.rec,
                    false,'',nil, wait,{wait}true,net_flag_SEND
                    )
                   );
      {$IFDEF DATA_BIN}
        {if p<>nil then
           begin
             strdispose(SPR^.adr);
             SPR^.adr:= p
           end;}
      {$ENDIF}

      {$IFDEF STATISTIKA_SERVER}
       if p_save_STA_SPR<>nil then TProc_p(p_save_STA_SPR)(SPR)
      {$ENDIF}
    end;


{ adresy
}
 function _adri(SPR: PSPR; i: int): string;
    begin
      _adri:= format_NETadr(cut_(GetPStr(SPR^.adr,i,set_SPRadr_odd+setNL+setNL_)))
    end;

 function _adri_net(_adri: string): string;
    begin
      _adri_net:= replchar(_adri,[SPRadr_subnet],' ')
    end;


 function _adrmult(adr: pchar): bool;
    begin
      _adrmult:= GetPStrItems(adr,set_SPRadr_odd+setNL+setNL_) > 1
    end;

 function _adrbrc(adr: string): bool;
    begin
      _adrbrc:=     (adr=SPRadr_all)
                {$IFDEF LZ}
                 or (adr=SPRadr_opl)
                 or (adr=SPRadr_let)
                {$ENDIF}
    end;

 function _adri_brc(adri: string; nd: int): bool;
    var   ba,bo,bl : bool;
    begin
      _adri_brc:= false;
      if (nd<-0) or (nd>=NODEpoc) then Exit;

      ba:= (strpos(NODEs^[nd].desc.inf,inf_SPR)<>nil);
      bl:= (strpos(NODEs^[nd].desc.inf,nd_AP)<>nil);
      bo:= bl or (strpos(NODEs^[nd].desc.inf,nd_MACC)<>nil);

      _adri_brc:= (   (ba and (adri=SPRadr_all))
                   or (bl and (adri=SPRadr_let))
                   or (bo and (adri=SPRadr_opl))
                  )
    end;


 function _adr_OPL(adr: string): string;
    begin
      {$IFDEF LZ}
       if (is_NETname(adr)=-1) and (_in_list(adr,@fnMLet,[],1,nil)) then adr:= adr_airbase(adr);
      {$ENDIF}
      _adr_OPL:= adr
    end;

 function _adri_nd (adri: string; var node: int): bool;

    function __adri_nd (adri: string; var node: int): bool;
       begin
         __adri_nd:= true;
         node:= -1;

         node:= is_NETnode (adri);
         if node>-1 then Exit;

         { alebo/a kontrola na OPL adresu
         } node:= is_NETadr (_adr_OPL(adri));
         if node>-1 then Exit;

         __adri_nd:= false
       end;

    var   res : bool;
          _to : T_IPaddress;

    begin
      _adri_nd:= true;

      node:= -1;
      adri:= _adri_net(adri);

      if _adrbrc(adri) then Exit;

      __adri_nd (adri,node);
      if node>-1 then Exit;

      { alebo/a kontrola na AFTN adresu
      }

      { alebo kontrola IP adresu
      } {$IFDEF PCTCP};
         _to.fhost:= nm_prs_addr(adri);
         if neterrno=netRES_OK then Exit;
        {$ENDIF}

      { neznama adresa, je presmerovatelna ?
      } res:= false;
        {$IFDEF _X25}
         res:= NETres (is_X25_LANadr(adri));
         if not res then
        {$ENDIF}
           begin
            { presmerujeme na letisku, ak nie je bridge... ?
            }
             __adri_nd (NETadr_wan(adri),node);
             if node>-1 then Exit;
           end;

      _adri_nd:= res
    end;


 function _odosli_SPR(SPR: PSPR): bool;

    var   nodess  : array[0..maxNODEs-1] of bool;
          msg,tit : string;

    function _odosli_na(adri: TNETadr; n: int): bool;
       var   res : bool;
             adr : TNETadr;
       begin
         _odosli_na:= false;
         {if (n=-1) then Exit;}
         adr:= adri;

         _odosli_na:= true;
         if (n>-1) then
            begin
              if nodess[n] then Exit;
              nodess[n]:= true;
              adri:= NODEs^[n].desc.adr;
            end;

         _INFO_NET_RES:= true;
         res:= send_SPR(SPR, adri, (n>-1) and SPR_ACK_WAIT);

         tit:= msgACCEPT; msg:= tit_MSG_sent;
         if SPR_ACK_WAIT then
            begin
              if n>-1 then
                 begin
                   if res then msg:= tit_MSG_ack
                   else begin tit:= msgWARNING; msg:= tit_MSG_not_ack end
                 end
            end;
         Say2(tit,adri+' :  '+msg);

         _odosli_na:= res
       end;


    function _prerus_odosielanie: bool;
       var   _Event: TEvent;
       begin
         {if      (ReadKey(30, ACheck) = kbEsc)
             and (Ask2(msgVERIPHY,ask_CancelProc,titNO,
                       White,clBUTTON_COLOR,waitASK*18
                      ) = ansAno
                 )
                 then begin
                        Say2(msgMESS,msg_CancelProc);
                        _prerus_odosielanie:= true
                      end
         else} _prerus_odosielanie:= false
       end;


    var   adri     : string;
          i,n,p    : int;

    label X;

    begin
      CISLO_SPRAVY:= (CISLO_SPRAVY + 1) mod MOD_CISLA_SPRAVY;
      if CISLO_SPRAVY=0 then CISLO_SPRAVY:= 1;
      save_cislo(SPR_kod,CISLO_SPRAVY);
      SPR^.cis:= CISLO_SPRAVY;
      save_SPR(SPR);

      fillchar(nodess,sizeof(nodess),0);
      p:= GetPStrItems(SPR^.adr,set_SPRadr_odd+setNL+setNL_);
      for i:= 1 to p do
        begin
          adri:= _adri_net(_adri(SPR,i));
          if _adrbrc(adri) then
             begin
               for n:= 0 to NODEpoc-1 do if (not nodess[n]) then
                 begin
                   if _adri_brc (adri,n) then
                      if     (not _odosli_na(NODEs^[n].desc.adr,n))
                         and _prerus_odosielanie then goto X
                 end
             end
          else begin
                 if _adri_nd (adri,n) then
                    if     (not _odosli_na(adri,n))
                       and _prerus_odosielanie then goto X
               end;
        end;

      X: _odosli_SPR:= true
    end;

 procedure odosli_SPR(SPR: PSPR);
     begin
       _odosli_SPR(SPR)
     end;
