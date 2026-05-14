 procedure new_NTM(NTM1,NTM2 : PNTM);
     begin
       FillChar(NTM2^,SizeOf(TNTM),0);
       if NTM1<>nil then
          begin
            NTM2^:= NTM1^;
            NTM2^._NTM:= StrNew(NTM1^._NTM);
            NTM2^._Q  := StrNew(NTM1^._Q);
            NTM2^._D  := StrNew(NTM1^._D);
            NTM2^._E  := StrNew(NTM1^._E);
          end
     end;

 procedure disp_NTM(NTM: PNTM);
     begin
       StrDispose(NTM^._NTM);
       StrDispose(NTM^._Q);
       StrDispose(NTM^._D);
       StrDispose(NTM^._E);
     end;


 function eq_NTM(NTM1,NTM2: PNTM): bool;
    begin
      eq_NTM:=      ((NTM1<>nil) and (NTM2<>nil))
                and eq_str(key_NTM(NTM1),key_NTM(NTM2))
                {and (codekey_NTM(NTM1) = codekey_NTM(NTM2))}
    end;


 function chg_NTM(NTM1,NTM2 : PNTM): bool;
    begin
      chg_NTM:= not (     eq_NTM   (NTM1,NTM2)

                     and  eq_str0  (NTM1^._Q, NTM2^._Q)

                     and  eq_str   (NTM1^._A, NTM2^._A)
                     and  eq_str   (NTM1^._B, NTM2^._B)
                     and  eq_str   (NTM1^._C, NTM2^._C)

                     and  eq_lines (NTM1^._D, NTM2^._D)
                     and  eq_lines (NTM1^._E, NTM2^._E)

                     and  eq_str   (NTM1^._F, NTM2^._F)
                     and  eq_str   (NTM1^._G, NTM2^._G)

                     and  eq_str   (NTM1^.stt, NTM2^.stt)
                )
    end;


{ -------------------------- }
{ read/save                  }
{ -------------------------- }

 function  _read_NTM (key: string; NTM: PNTM; path,ext: string): int;
    var    FN : string;
    begin
      if (NTM<>nil) and (key<>'') then
         begin
           decodekey_NTM (key, NTM);
           FN:= get_DBfn_ (NTM^.dav.d,NTM^.dav.m,NTM^.dav.r, path,ext);
           _read_NTM:= DB_najdi (NTM,FN,db_NTM_RIADKOV,@decodeDB_NTM,@codekey_NTM,true,@disp_NTM,'')
         end
      else _read_NTM:= -1
    end;

 procedure _save_NTM (NTM: PNTM; path,ext: string; var dbchg: bool);
     var   DB   : PDB;
           NTMi : TNTM;
           FN   : string;
           kluc : string;
           _pos : long;
     begin
       new_NTM (NTM,@NTMi);
       FN:= get_DBfn_ (NTM^.dav.d,NTM^.dav.m,NTM^.dav.r, pathNTM,extNTM);
       DB:= New(PDB,Init(FN,DB_RWClose,db_NTM_RIADKOV,@codeDB_NTM,@decodeDB_NTM,@codekey_NTM,@dbchg,dbattr_NTM));
       _pos:= DB^.vyhladaj_kluc(codekey_NTM_(key_NTM (@NTMi),NTMi.dav));
       DB^.zapis(@NTMi,_pos,false);
       Dispose(DB,Done);
       disp_NTM (@NTMi)
     end;


{ -------------------------- }
{ send                       }
{ -------------------------- }
 (*
 function  _send_NTM (NTM: PNTM; adr: TNETadr; wait: bool; typ: TNETtyp; info: string): bool;
    begin
      _send_NTM:= NETres(NETsend_data
                   (adr, typ,
                    NTM, @code_NTM,@codekey_NTM,@NTM^.rec,
                    true,info,nil,
                    wait,false, net_flag_NIL
                   ))
   end;


 function  _distribute_NTM (NTM: PNTM; sw: Tnd_sw_set; nd: Tnd_nd_set; typ: TNETtyp; info : string): bool;
    var    res : bool;
    begin
      {$IFDEF ARCHIVE_DAR}
       DAR_arch.save_FDP(typ, NTM, @code_NTM);
      {$ENDIF}

      res:= NETdistribute_data
                   (
                    [FDP,RDP,MON],sw,[MASTER,SLAVE],
                    typ, NTM,@code_NTM,@codekey_NTM,@NTM^.rec,
                    true,info,nil,false,false,net_flag_NIL
                   );

      _distribute_NTM:= res
    end;
*)