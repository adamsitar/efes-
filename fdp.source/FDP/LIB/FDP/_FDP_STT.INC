{ -----------------------------
  Testovanie stavu

}
 function _is_stat(_stat : string; { testovany stav }
                   _cond : string; { testovane podmienky - moznosti }
                   _all  : bool    { musia byt vsetky podmienky musia splnene ? }
                  ): bool;
    var   b: bool;
          i: int;
    begin
      if cut_(_cond)='' then
         begin
           _is_stat:= true;
           if (cnst_cnl = _stat) and (not CNL_VYPIS) then _is_stat:= false;
           if (pos(cnst_dec,_stat)<>0) and (not DEC_VYPIS) then _is_stat:= false;
           if (cnst_stat_ARR = _stat) and (not ARR_VYPIS) then _is_stat:= false;
         end
      else begin
             b:= pos(_cond,_stat)<>0;
             if (not b) and (not _all) then
                begin
                  i:= 1;
                  while (not b) and (i<=length(_cond)) do
                    begin
                      b:= pos(_cond[i],_stat)<>0;
                      inc(i)
                    end
                end;
             _is_stat:= b
           end
    end;


{ Odvodene a pomocne fcie
}
 function _is_statp(_stat  : string;  { stav }
                    _pcond : pstring; { podmienky }
                    _all   : bool     { vsetky podmienky musia byt splnene ? }
                   ): bool;
    var   s: string;
    begin
      if _pcond<>nil then s:= _pcond^ else s:= '';
      _is_statp:= _is_stat(_stat,s,_all)
    end;

 function __is_stat(_stat,_cond : string): bool;
    begin
      __is_stat:= _is_stat(_stat,_cond,false)
    end;

 function  __is_statp(_stat: string; _cond : pstring): bool;
    begin
      __is_statp:= _is_statp(_stat,_cond,false)
    end;


 function _is_stat_us (_src, _stat,_cond: string): bool;
    begin
      _is_stat_us:= (_plan_pre(_src)) and __is_stat(_stat,_cond)
    end;

 function _is_stat_ot (_src, _stat,_cond: string): bool;
    begin
      _is_stat_ot:= (not _plan_pre(_src)) and __is_stat(_stat,_cond)
    end;

 function _sw_stat_us (all: bool; p_all,p_own: pointer): pointer;
    begin
      if all then _sw_stat_us:= p_all
      else _sw_stat_us:= p_own
    end;


 function _is_stat_cnl (_stat: string): bool;
    begin
      _is_stat_cnl:= (pos(cnst_cnl,_stat)<>0) and (_stat<>cnst_stat_arr)
    end;


{ -----------------------------
  Dekodovanie stavu
}

{ Nemyslim, ze nasledujuce fcie budu potrebne
  pre FDP NX...
}
 function decode_stat_s(stat: string; rod: byte): string;
     var  r: string[1];
     begin
       r:= pripona_podla_rodu[rod];

       if      pos(cnst_pause,stat)<>0         then decode_stat_s:= st_pause+r
       else if pos(cnst_stat_mzp,stat)<>0      then decode_stat_s:= st_mzp
       else if    (pos(cnst_stat_mzs,stat)<>0)
               or (pos(cnst_active,stat)<>0)   then decode_stat_s:= st_active+r

       else if pos(cnst_prop,stat)<>0          then decode_stat_s:= st_prop
       else if pos(cnst_acc,stat)<>0           then decode_stat_s:= st_acc+r
       else if pos(cnst_dec,stat)<>0           then decode_stat_s:= st_dec+r

       else if pos(cnst_start,stat)<>0         then decode_stat_s:= st_start
       else if pos(cnst_finish,stat)<>0        then decode_stat_s:= st_finish+r
       else if pos(cnst_warn,stat)<>0          then decode_stat_s:= st_warn

       else if pos(cnst_cnl,stat)<>0           then decode_stat_s:= st_cancel+r
       else if pos(cnst_sended,stat)<>0        then decode_stat_s:= st_sended+r

       else                                         decode_stat_s:= st_disk+r
     end;

 function decode_stat_fpl (stat: string): string;
    var   s: string;
    begin
      {if      pos(cnst_acc,stat)<>0       then s:= st_fpl_acc   Tieto hlasenia su zaujimave len pri directive
      else if pos(cnst_dec,stat)<>0       then s:= st_fpl_dec    PROCESS_FPLM (OPL) a na stanovistiach podania planov

      else} if pos(cnst_start,stat)<>0     then s:= st_fpl_start
      else if pos(cnst_stat_mzp,stat)<>0  then s:= st_fpl_mzp
      else if pos(cnst_stat_mzs,stat)<>0  then s:= st_fpl_mzs
      else if pos(cnst_finish,stat)<>0    then s:= st_fpl_finish

      {else if pos(cnst_warn,stat)<>0     then s:= st_fpl_warn}

      else if pos(cnst_cnl,stat)<>0       then s:= st_fpl_cancel
      {else if pos(cnst_active,stat)<>0    then s:= st_fpl_rte  Len pri zmene obsahu trate }
      else if pos(cnst_chg,stat)<>0       then s:= st_fpl_chg
      else                                     s:= '';

      decode_stat_fpl:= s
    end;

 function decode_stat_act (stat: string): string;
    var   s : string;
    begin
      if      pos(cnst_chg,stat)<>0      then s:= st_oprava

      else if pos(cnst_acc,stat)<>0      then s:= st_schvalenie
      else if pos(cnst_dec,stat)<>0      then s:= st_zamietnutie

      else if pos(cnst_stat_dep,stat)<>0 then s:= st_zaciatok
      else if pos(cnst_pause, stat)<>0   then s:= st_prerusenie
      else if (stat=cnst_active)         then s:= st_pokracovanie
      else if pos(cnst_warn,stat)<>0     then s:= st_warn
      else if pos(cnst_stat_arr,stat)<>0 then s:= st_ukoncenie

      else if pos(cnst_cnl,stat)<>0      then s:= st_zrusenie
      {else if pos(cnst_chg,stat)<>0     then s:= st_plan}
      else s:= '';

      decode_stat_act:= s
    end;


{ Pre farbu hlavicky planu,
  farba v okne preletov je
  v module prelety.write_item
}
 function get_stat_cl(stat: string): byte;
    begin
      if      pos(cnst_pause,stat)<>0         then get_stat_cl:= cl_STOJI
      else if pos(cnst_stat_mzp,stat)<>0      then get_stat_cl:= cl_MZP

          { aktivne lety maju byt zelene }
      else if    (pos(cnst_start,stat)<>0)
              or (pos(cnst_stat_mzs,stat)<>0)
              or (pos(cnst_stat_dep,stat)<>0) then  get_stat_cl:= cl_LETI
      else if    (pos(cnst_active,stat)<>0)   then  get_stat_cl:= cl_ACTIVE

      else if pos(cnst_prop,stat)<>0          then  get_stat_cl:= cl_PROP
      else if pos(cnst_acc,stat)<>0           then  get_stat_cl:= cl_ACC

      {else if pos(cnst_stat_arr,stat)<>0      then  get_stat_cl:= cl_HANGAR}
      else if pos(cnst_finish,stat)<>0        then  get_stat_cl:= cl_PRIST
      else if pos(cnst_warn,stat)<>0          then  get_stat_cl:= cl_PATRAT

      else if pos(cnst_cnl,stat)<>0           then  get_stat_cl:= cl_HANGAR
      else if pos(cnst_sended,stat)<>0        then  get_stat_cl:= cl_SEND
      else                                          get_stat_cl:= cl_DISK
    end;

 procedure write_stat(stat: string; rec: TPlan_rec; adr: TNETadr; xi,yi, cl: int);
     var   nd: int;
     begin
       if cl>0 then setcolor(cl) else setcolor(get_stat_cl(stat));
       if (cl<>-1) and STAV_PLANU then outtextxy(xi-(N(length(stat)-1))*8,yi,stat);
      {$IFDEF FDP_OPL} {IFDEF AIRBASE}
       if (adr<>'') and (stat<>cnst_disk) then
          begin
            nd:= is_NETadr(adr);
            if nd=-1 then nd:= is_NETadr(adr_airbase(adr));
            if nd<>-1 then write_rec(rec[nd] in [is_ack,is_rec],xi,yi)
          end;
      {$ENDIF} {ENDIF}
     end;



{ -----------------------------
  Oprava priznaku stavu

}

 function add_stat(status: string; novy: string): string;
    var   i: int;
    begin
      status:= cut_(status);
      for i:= 1 to length(novy) do if (pos(novy[i],status)=0) then status:= status+novy[i];
      add_stat:= status
    end;

 function del_stat(status: string; novy: string): string;
    var   i: int;
    begin
      for i:= 1 to length(novy) do status:= delchar(status, [novy[i]]);
      del_stat:= status
    end;


{ Odvodene a pomocne fcie
}

 function sended_stat (adr: TNETadr; stat: string): string;
    begin
      if (stat=cnst_disk) and (adr=SERVERaddress) then stat:= cnst_sended;
      sended_stat:= stat
    end;

 function cnl_stat(stat: string): string;
    begin
      if CNL_VYPIS then stat:= stat + cnst_cnl;
      if DEC_VYPIS then stat:= stat + cnst_dec;
      if ARR_VYPIS then stat:= stat + cnst_finish;
      cnl_stat:= stat
    end;

 function del_cnl_stat(status: string): string;
    begin
      status:= cut_(del_stat(status,cnst_finish+cnst_cnl+cnst_read));
      if status='' then status:= {$IFDEF FDP_EDD} cnst_active
                                 {$ELSE} cnst_disk {$ENDIF};
      del_cnl_stat:= status
    end;

{ vrati status pre spracovanie(vypis) podla nastavenia premennej vypis
}
 function valid_plan(stt: string): bool;
    begin
      valid_plan:= CNL_VYPIS or (hd_CNL<>mtks_rus_to_lat(stt))
    end;
