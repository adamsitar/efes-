{ --------------
   Prijaty plan
  --------------
}

 procedure _pkt_FPL4(FPL: PFPL4);
      begin
        _zarad_FPL4 (FPL,cm_spracuj_FPL4_NET,FPL^.stat,true,letvis);
        disp_FPL4(FPL)
      end;


{ --------------------
   Prijate potvrdenie
  --------------------
}
 {
   Ak sa bude vysielat i z prop okna, treba pri prijme potvrdenia
   prehladat i okno navrhovanych stripov
 }

 procedure _codeDBB_FPL4rec (src: Pplan_rec; buff: PDB_riadok; head: PDB_head); far;
     var   s,t  : string;
           p : pchars;
           rec : Tplan_rec;
           f : PFPL4;
     begin
       s:= DBstr_to_str_ (buff^);
       p:= @s[1];
       get_s (p, @rec,sizeof(rec));
       rec_copy (src^,rec);
       p:= @s[1];
       move(rec,p^,sizeof(rec));
       str_toDBstr_ (s,buff^)
     end;

 procedure _codeDBB_FPL4nd (nd: pint; buff: PDB_riadok; head: PDB_head); far;
     var   s,t  : string;
           p : pchars;
           rec : Tplan_rec;
           f : PFPL4;
     begin
       s:= DBstr_to_str_ (buff^);
       p:= @s[1];
       get_s (p, @rec,sizeof(rec));
       rec_pkt (nd^,rec,is_ack);
       p:= @s[1];
       move(rec,p^,sizeof(rec));
       str_toDBstr_ (s,buff^)
     end;


 procedure _ack_FPL4 (key: string; rec: Tplan_rec; fdp: bool; nd: int);
     var   date  : TDate;
           s,t   : string;
           p1,p2 : pointer;
     begin
       if not fdp then Exit;

       if NET_ACK_ALL then
          begin
            p1:= @rec;
            p2:= @_codeDBB_FPL4rec
          end
       else begin
              p1:= @nd;
              p2:= @_codeDBB_FPL4nd
            end;
       decodekey_fpl(key,s,t,date);
       DB_oprav_riadok (p1,nil,key,
                        get_DBfn(date, pathFPL, extFPL),db_FPL4_RIADKOV,
                        @codeDB_FPL4,@codekey_FPL4,
                        db_FPL4_ine,p2,
                        dbattr_FPL4
                       );
     end;

{ --------------------
   Inicializacia uzla
  --------------------
}
