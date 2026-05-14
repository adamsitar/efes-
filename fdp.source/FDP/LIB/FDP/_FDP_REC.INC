{ prida rec na koniec zakodovaneho retazca
}
 function rectostr(rec: Tplan_rec): string;
    var   s: string;
    begin
      Move(rec,s[1],maxNODEs);
      s[0]:= chr(maxNODEs);
      rectostr:= s
    end;

 procedure strtorec(s: string; var rec: Tplan_rec);
     begin
       s:= cut_(s);
       Move(s[1],rec,minimum(maxNODEs,length(s)))
     end;


 procedure write_rec(rec: bool; xi,yi: int);
     var   nd: int;
     begin
       if rec then icYes(xi+8,yi-2)
       else icNo(xi+5,yi-2)
     end;


 function send2node(stat: string; nd: int): bool;
    begin
      send2node:=

            (nd>-1)
        and (    (     NODEs^[nd].desc.sw in set_nd_S
                 )
              or (     (NODEs^[nd].desc.sw in set_nd_OPL)
                   and _is_stat(stat,
                                del_stat(cnst_all{_valid},cnst_disk{+cnst_sended}),
                                false
                               )
                 )
              or (     (NODEs^[nd].desc.sw in set_nd_EST)
                   and _is_stat(stat,
                                cnst_stat_preact+cnst_stat_arr,
                                false
                               )
                 )
            )
    end;
