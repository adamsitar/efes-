function eq_RTZ(RTZ1, RTZ2: PRTZ): bool;
   begin
     eq_RTZ:=      ((RTZ1<>nil) and (RTZ2<>nil))
               and (codekey_RTZ(RTZ1) = codekey_RTZ(RTZ2))
   end;

function chg_RTZ (RTZ1, RTZ2: PRTZ): bool;
   begin
     chg_RTZ:= not (    eq_RTZ (RTZ1,RTZ2)
                    and eq_str0(RTZ1^.data,RTZ2^.data)
                   )
   end;

procedure new_RTZ(RTZ1, RTZ2: PRTZ);
    begin
      FillChar(RTZ2^,SizeOf(TRTZ),0);
      if RTZ1<>nil then
         begin
           RTZ2^:= RTZ1^;
           RTZ2^.data:= StrNew(RTZ1^.data);
         end
    end;

procedure copy_RTZ(RTZ1, RTZ2: PRTZ);
    begin
      disp_RTZ(RTZ2);
      new_RTZ(RTZ1, RTZ2)
    end;

procedure disp_RTZ(RTZ: PRTZ);
    begin
      with RTZ^ do
        begin
          StrDispose(data);
        end
    end;

procedure format_RTZ(RTZ: PRTZ);
    begin
    end;


function _line_rtz_data(data: pchar; zac,kon,kon2: string; var zacp,konp: pchar; _drw: bool): string;
   var   dlz : int;
         res : string;
   begin
     _line_rtz_data:= '';
     zac:= zac+NULL; kon:= kon+NULL; kon2:= kon2+NULL;
     konp:= nil;
     zacp:= strpos(data,@zac[1]);
     if (zacp=nil) then Exit;
     if kon<>'' then
        begin
          konp:= strpos(data,@kon[1]);
          if (konp=nil) and (kon2<>'') then konp:= strpos(data,@kon2[1]);
        end;
     if konp=nil then res:= strpas(zacp)
     else if konp<zacp then Exit
     else begin
            dlz:= minimum(N(konp-zacp),sizeof(res)-1);
            res[0]:= chr(dlz);
            move(zacp[0],res[1],dlz);
          end;
     res:= cut_(res);
     zacp:= konp;
     if _drw and (textwidth(res)>dx_RTZ-20) then res:= copy(res,1,((dx_RTZ-20) div textwidth('T'))-3)+'...';
     _line_rtz_data:= res
   end;


{ -------------------------- }
{ save                       }
{ -------------------------- }

function get_dbRTZfn: string;
   begin
     get_dbRTZfn:= get_DBfn_(day,month,year, pathRTZ,extRTZ)
   end;

function read_RTZ(key: string; RTZ: PRTZ): int;
   begin
     if (RTZ<>nil) and (key<>'') then
        begin
          decodekey_RTZ(key, RTZ);
          read_RTZ:= DB_najdi(RTZ,get_DBfn(RTZ^.date, pathRTZ,extRTZ),db_RTZ_RIADKOV,@decodeDB_RTZ,@codekey_RTZ,
                              true,@disp_RTZ,''
                             )
        end
     else read_RTZ:= -1
   end;

procedure save_RTZ(_RTZ: PRTZ);
    var   RTZ: TRTZ;
    begin
      new_RTZ(_RTZ, @RTZ);
      DB_oprav(@RTZ, get_DBfn(RTZ.date, pathRTZ,extRTZ), db_RTZ_RIADKOV,@codeDB_RTZ,@codekey_RTZ,@dbchg_RTZ, dbattr_RTZ);
      disp_RTZ(@RTZ);
    end;

