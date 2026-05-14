{ --------------
   NET read
  --------------
}
 procedure _pkt_PLN (PLN: PPLN);
     begin
       _zarad_PLN(PLN,true,letvis,false)
     end;


 procedure _codeDBB_PLNrec (src: Pplan_rec; buff: PDB_riadok; head: PDB_head); far;
     var   s,t  : string;
           i,size: int;
           p : pchars;
           rec : Tplan_rec;
           f : PPLN;
     begin
       with f^ do size:= sizeof(idn)+sizeof(typ)+sizeof(dep)+sizeof(eet)+sizeof(exi)+sizeof(arr);

       s:= DBstr_to_str_ (buff^);
       p:= @s[1];
       incptr(pointer(p),size);
       get_s_x(p, t,sizeof(t)-1);
       incptr(pointer(p),sizeof(f^.date));
       get_s (p, @rec,sizeof(rec));
       rec_copy (src^,rec);
       decptr(pointer(p),sizeof(rec));
       move(rec,p^,sizeof(rec));
       str_toDBstr_ (s,buff^)
     end;

 procedure _codeDBB_PLNnd (nd: pint; buff: PDB_riadok; head: PDB_head); far;
     var   s,t  : string;
           i,size: int;
           p : pchars;
           rec : Tplan_rec;
           f : PPLN;
     begin
       with f^ do size:= sizeof(idn)+sizeof(typ)+sizeof(dep)+sizeof(eet)+sizeof(exi)+sizeof(arr);

       s:= DBstr_to_str_ (buff^);
       p:= @s[1];
       incptr(pointer(p),size);
       get_s_x(p, t,sizeof(t)-1);
       incptr(pointer(p),sizeof(f^.date));
       get_s (p, @rec,sizeof(rec));
       rec_pkt (nd^,rec,is_ack);
       decptr(pointer(p),sizeof(rec));
       move(rec,p^,sizeof(rec));
       str_toDBstr_ (s,buff^)
     end;


 procedure _ack_PLN (key: string; rec: Tplan_rec; fdp: bool; nd: int);
     var   date  : TDate;
           s,t   : string;
           p1,p2 : pointer;
     begin
       if not fdp then Exit;

       if NET_ACK_ALL then
          begin
            p1:= @rec;
            p2:= @_codeDBB_PLNrec
          end
       else begin
              p1:= @nd;
              p2:= @_codeDBB_PLNnd
            end;
       decodekey_fpl(key,s,t,date);
       DB_oprav_riadok (p1,nil,key,
                        get_DBfn(date, pathFPL,extPLN),db_PLN_RIADKOV,
                        @codeDB_PLN,@codekey_PLN,
                        db_PLN_data,p2,
                        dbattr_PLN
                       );
     end;
