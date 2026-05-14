{ תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
   odoslanie a rozoslanie
  תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
}
 function send_FPL4(FPL: PFPL4; adr: TNETadr; wait: bool): bool;
    var   kod    : TNETtyp;
          p_code : pointer;
    begin
      kod:= spr_FPL4;
      p_code:= @code_FPL4;
      if NETtype(adr) in [FDP0,FDP0NX] then
         begin
           kod:= spr0_FPL4;
           p_code:= @code0_FPL4
         end;
      send_FPL4:= NETres(NETsend_data
                     (adr,
                      kod, FPL,p_code,@codekey_FPL4,@FPL^.rec,
                      true,inf_FPL4,nil, wait,false, net_flag_NIL
                     ))
    end;

 function distribute_FPL4(FPL: PFPL4; sw: Tnd_sw_set; nd: Tnd_nd_set): bool;
    var   bres: bool;
    begin
      bres:= NETdistribute_data
                   (
                    [FDP0,FDP0NX],sw,nd,
                    spr0_FPL4,FPL,@code0_FPL4,@codekey_FPL4,@FPL^.rec,
                    true,inf_FPL4,nil, false,false,net_flag_NIL
                   );

      distribute_FPL4:= NETdistribute_data
                   (
                    [FDP],sw,nd,
                    spr_FPL4,FPL,@code_FPL4,@codekey_FPL4,@FPL^.rec,
                    true,inf_FPL4,nil, false,false,net_flag_NIL
                   ) and bres
    end;



{ -------------------
   EXT - koordinacia
  -------------------
}
 {function  spracovanie_FPL4_EXT(przn : TFPL4_spracovanie): TFPL4_spracovanie;
    begin
      if rozosielat_FPL4_EXT then przn:= przn or rozosli_FPL4_EXT;
      spracovanie_FPL4_EXT:= przn
    end;
 }

(*
 procedure coordinate_FPL4 (FPL: PFPL4;
                            src: fdp_src; dst: set_fdp_src;
                            zmena, zmeneny: bool
                           );
     var   head: Thead_ICAO;
           stat: string;
     begin
      {$IFDEF EXTERNAL_NET}
       if is_KRL(FPL) then Exit;

       {if zmena then zmeneny:= zmeneny_mFPL(FPL,false);}

       stat:= FPL^.stat;
       {if __is_stat(stat,cnst_acc) then head:= hd_ABI
       else} if __is_stat(stat,cnst_stat_dep) then head:= hd_ACT
       else if pos(cnst_stat_arr,stat)>0 then head:= hd_ARR
       else if get_poz(stat)<=poz_COORDINATED then
            begin
              if         (cnst_cnl=stat)        then head:= hd_CNL
              else if pos(cnst_dla,stat)>0      then head:= hd_DLA
              {este nie je - else if _zmeneny or (pos(cnst_chg,stat)>0) then head:= hd_CHG}
              else if pos(cnst_sended,stat)>0   then head:= hd_FPL
            end;

       fdp_co_ordinate_procedure (src,dst, spr_FPLM,head, zmeneny,FPL^);
      {$ENDIF}
     end;
*)

{ --------------
   NET+EXT
  --------------
}
 function _odosli_FPL4 (FPL: PFPL4; _src: fdp_src): bool;
    begin
      _odosli_FPL4:= false;
      distribute_FPL4 (FPL,[],[]);
      {coordinate_FPL4 (FPL,_src,[],false,true);}
    end;

 procedure odosli_FPL4 (FPL: PFPL4);
    begin
      _odosli_FPL4 (FPL,letvis);
    end;
