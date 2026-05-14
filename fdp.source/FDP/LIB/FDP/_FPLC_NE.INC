{ --------------
   Prijaty plan
  --------------
}
 (*
 function _accept_FPLC(ods: TNETadr; FPL: PDcFPL): bool;
    var   nd: int;
    begin
     _accept_FPLc:= true;
    end;
 *)


 function  _pkt_FPLC_(ods: TNETadr; FPL: PFPLC): bool;
     var   FPLp    : PDcFPL;
           ires,nd : int;
     label X;
     begin
       _pkt_FPLC_:= false;

       {$IFDEF NO_PLAN}
        {$IFDEF MPU}
          nd:= is_NETadr(ods);
          if (nd>-1) and (NODEs^[nd].desc.ai<>$FF) then print_cFPL_MPU(FPL,nd,NODEs^[nd].desc.ai);
        {$ENDIF}

         Exit;
       {$ENDIF}

       {ires:= read_cFPL(codekey_FPLC(FPL),@FPLp);}
       FPLp:= find_FPLCa (codekey_FPLC(FPL));
       if (FPL<>nil) and (not chg_cFPL (FPL,FPLp)) then goto X;

       _pkt_FPLC_:= true;

       {$IFDEF PVO}
        { PVO zaujima cas prveho prijatia spravy }
         if (ires>-1) then FPL^.rec_cas:= FPLp^.rec_cas
         else init_time(FPL^.rec_cas, hour,min,sec);
       {$ENDIF}

       _zarad_FPLc(FPL,FPL^.stt,true,[],letvis,ods,true,true,true, FPLp,true);

       X: {disp_cFPL(@FPLp)}
     end;



{ --------------------
   Prijate potvrdenie
  --------------------
}
 {
   Ak sa bude vysielat i z prop okna, treba pri prijme potvrdenia
   prehladat i okno navrhovanych stripov
 }

{ I DB.h}   { Objekt pre DB LETVIS    }
{ I DB_0.inc}

 {procedure _codeDBB_FPLCrec (FPL: PDcFPL; buff: PDB_riadok; head: PDB_head); far;
     var   size: int;
           s,t: string;
           i: int;
     begin
       with FPL^ do
         begin
           s:= '';
           add_s(@rec,sizeof(rec), s,t);
           str_toDBstr_(s,buff^)
         end;
     end;}

 procedure _ack_FPLC(key: string; rec: Tplan_rec; fdp: bool; nd: int);
     var   FPL  : PFPLC;
           iFPL : P_OFPL;
           i    : int;
     begin
       FPL:= find_FPLCa (key);
       if FPL=nil then Exit;

       if NET_ACK_ALL then rec_copy (rec, FPL^.rec)
       else rec_pkt(nd,FPL^.rec,is_ack);
       if not fdp then Exit;

       {$IFDEF EDD}
         if pis_STRIP_ACK then
            begin
              i:= PROP_cFPL^.find_key(key);
              if i>-1 then iFPL:= PROP_cFPL
              else begin
                     i:= cFPL^.find_key(key);
                     if i>-1 then iFPL:= cFPL
                   end;
              if i>-1 then iFPL^.vypis_plan(i, false,false)
            end;
       {$ENDIF}

       {nemam zarucene nacitanie udajov, ak je to v dalej hodine :
        DB_oprav_riadok
                 (FPL,FPL, key,
                  get_fn_cFPL,db_cFPL_RIADKOV,
                  @codeDB_FPLC,@codekey_FPLC,
                  db_cFPL_ine,@_codeDBB_FPLCrec,
                  dbattr_FPC
                 )
       }
       save_cFPL(FPL)
     end;


{ --------------------
   Inicializacia uzla
  --------------------
}
