{ ----------
  SYN
  ---------- }

function eq_SYN(SYN1, SYN2: PSYN): bool;
   begin
     eq_SYN:=     (SYN1^.ident = SYN2^.ident)
              and eq_str (SYN1^.let, SYN2^.let)
              and eq_time(SYN1^.time,SYN2^.time)
              and eq_date(SYN1^.date,SYN2^.date)
   end;

procedure new_SYN(SYN1, SYN2: PSYN);
    begin
      FillChar(SYN2^,SizeOf(TSYN),0);
      if SYN1<>nil then
         begin
           SYN2^:= SYN1^;
           SYN2^.nazov:= StrNew(SYN1^.nazov);
           SYN2^.qbb  := StrNew(SYN1^.qbb);
           SYN2^.stav := StrNew(SYN1^.stav)
         end
    end;

procedure disp_SYN(SYN: PSYN);
    begin
      with SYN^ do
        begin
          StrDispose(nazov);
          StrDispose(qbb);
          StrDispose(stav)
        end
    end;


function read_SYN(key: string; SYN: PSYN): int;
   begin
     if (SYN<>nil) and (key<>'') then
        begin
          decodekey_SYN(key, SYN);
          read_SYN:= DB_najdi(SYN,pathSYN+get_PLANhod(SYN^.date.d,SYN^.date.m,SYN^.date.r, SYN^.time.h),
                              db_SYN_RIADKOV,@decodeDB_SYN,@codekey_SYN,
                              true, @disp_SYN,''
                             )
        end
     else read_SYN:= -1
   end;


procedure save_SYN(_SYN: PSYN);
    var   SYN: TSYN;
    begin
      new_SYN(_SYN,@SYN); { tu je to mozno i zbytocne, ale z principu buffer }
      DB_oprav(@SYN, pathSYN+get_PLANhod(SYN.date.d,SYN.date.m,SYN.date.r, SYN.time.h),
               db_SYN_RIADKOV,@codeDB_SYN,@codekey_SYN,
               @dbchg_SYN,dbattr_SYN
              );
      disp_SYN(@SYN)
    end;

function get_dbSYNfn: string;
   begin
     get_dbSYNfn:= pathSYN+get_DBfn__(pathSYN,'*.*', archiv_HODfn)
   end;


{ -------------------------- }
{ send                       }
{ -------------------------- }

function send_SYN(SYN: PSYN; adr: TNETadr; wait: bool): bool;
   begin
     if NETtype(adr)=RDP then Exit;
     send_SYN:= NETres(NETsend_data
                (adr, spr0_SYN,
                 SYN,@code_SYN,@codekey_SYN,@SYN^.rec,
                 true,inf_SYN,nil,
                 wait,false,net_flag_NIL)
                )
   end;

function  distribute_SYN(SYN: PSYN; sw: Tnd_sw_set; nd: Tnd_nd_set): bool;
   var    res : bool;
   begin
    {$IFDEF ARCHIVE_DAR}
      DAR_arch.save_FDP(spr0_SYN, SYN, @code_SYN);
    {$ENDIF}

    {$IFDEF DATA_BIN}
     res:= NETdistribute_data
                  (
                   [FDP0],sw,[MASTER,SLAVE],
                   spr0_SYN, SYN,@code_SYN,@codekey_SYN,@SYN^.rec,
                   true,inf_SYN,nil,false,false,net_flag_NIL
                  );
      res:= true;
    {$ENDIF}

     res:= NETdistribute_data
                  (
                   [FDP,RDP,MON],sw,[MASTER,SLAVE],
                   spr0_SYN, SYN,@code_SYN,@codekey_SYN,@SYN^.rec,
                   true,inf_SYN,nil,false,false,net_flag_NIL
                  ) and res;

     distribute_SYN:= res
   end;


{ ----------
  MET
  ---------- }
(*
function eq_MET(MET1, MET2: PMET): bool;
   begin
     eq_MET:=     (MET1^.ident = MET2^.ident)
              and eq_time(MET1^.time,MET2^.time)
              and eq_date(MET1^.date,MET2^.date)
   end;

procedure new_MET(MET1, MET2: PMET);
    begin
      FillChar(MET2^,SizeOf(TMET),0);
      if MET1<>nil then
         begin
           MET2^:= MET1^;
           MET2^.nazov:= StrNew(MET1^.nazov);
           MET2^.line1:= StrNew(MET1^.line1);
           MET2^.line2:= StrNew(MET1^.line2)
         end
    end;

procedure disp_MET(MET: PMET);
    begin
      with MET^ do
        begin
          StrDispose(nazov);
          StrDispose(line1);
          StrDispose(line2)
        end
    end;

function read_MET(key: string; MET: PMET): int;
   begin
     if (MET<>nil) and (key<>'') then
        begin
          decodekey_MET(key, MET);
          read_MET:= DB_najdi(MET,pathMET+get_PLANhod(MET^.date.d,MET^.date.m,MET^.date.r, MET^.time.h),
                              db_MET_RIADKOV,@decodeDB_MET,@codekey_MET,
                              true, @disp_MET,''
                             )
        end
     else read_MET:= -1
   end;

procedure save_MET(_MET: PMET);
    begin
      new...
      DB_oprav(MET,get_PLANhod(MET^.date.d,MET^.date.m,MET^.date.r, MET^.time.h),
               db_MET_RIADKOV,@codeDB_MET,@codekey_MET,@dbchg_MET
              )
    end;

function get_dbMETfn: string;
   begin
     get_dbMETfn:= pathMET+get_DBfn__(pathMET,'*.*', archiv_HODfn)
   end;


{ -------------------------- }
{ send                       }
{ -------------------------- }

function send_MET(MET: PMET; adr: TNETadr; wait: bool): bool;
   begin
     if NETtype(adr)<>RDP then
        send_MET:= NETres(NETsend_(adr,MET, spr_MET,inf_MET,nil, @code_MET,nil,@codekey_MET, wait,@MET^.rec))
   end;

function  distribute_MET(MET: PMET; sw: Tnd_sw_set; wp: Tnd_wp_set): bool;
   begin
     distribute_MET:= NETdistribute([FDP],sw,wp, MET, spr_MET,inf_MET,nil, @code_MET,nil,@codekey_MET, @MET^.rec);
   end;
*)