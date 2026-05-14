function eq_QGO(QGO1, QGO2: PQGO): bool;
   begin
     eq_QGO:=     ((QGO1<>nil) and (QGO2<>nil))
              and (codekey_QGO(QGO1) = codekey_QGO(QGO2))
   end;

function chg_QGO (QGO1, QGO2: PQGO): bool;
   begin
     chg_QGO:= not (    eq_QGO (QGO1,QGO2)

                    and eq_lines(QGO1^.stav,QGO2^.stav)

                    and (QGO1^.TQGO=QGO2^.TQGO)
                    and eq_str0(QGO1^.TQGO_,QGO2^.TQGO_)
                    and eq_str(QGO1^.TQGOc,QGO2^.TQGOc)

                    and (QGO1^.MQGO=QGO2^.MQGO)
                    and eq_str0(QGO1^.MQGO_,QGO2^.MQGO_)
                    and eq_str(QGO1^.MQGOc,QGO2^.MQGOc)

                    and (QGO1^.stat=QGO2^.stat)
                   )
   end;

procedure new_QGO(QGO1, QGO2: PQGO);
    begin
      FillChar(QGO2^,SizeOf(TQGO),0);
      if QGO1<>nil then
         begin
           QGO2^:= QGO1^;
           QGO2^.stav  := StrNew(QGO1^.stav);
           QGO2^.TQGO_ := StrNew(QGO1^.TQGO_);
           QGO2^.MQGO_ := StrNew(QGO1^.MQGO_)
         end
    end;

procedure copy_QGO(QGO1, QGO2: PQGO);
    begin
      disp_QGO(QGO2);
      new_QGO(QGO1, QGO2)
    end;

procedure disp_QGO(QGO: PQGO);
    begin
      with QGO^ do
        begin
          StrDispose(stav);
          StrDispose(TQGO_);
          StrDispose(MQGO_)
        end
    end;

procedure format_QGO(QGO: PQGO);
    begin
    end;


{ -------------------------- }
{ save                       }
{ -------------------------- }

function get_dbQGOfn: string;
   begin
     get_dbQGOfn:= get_DBfn_(day,month,year, pathQGO,extQGO)
   end;

function  get_dbQGO_RPLfn: string;
   begin
     get_dbQGO_RPLfn:= pathRPL +
                       {$IFDEF AIRBASE} this_airbase
                       {$ELSE}          extQGO
                       {$ENDIF}
                       +'.'+extQGO
   end;


{$IFDEF AIRBASE}
  function read_this_QGO(QGO: PQGO; FN: string): int;
     begin
       fillchar(QGO^,sizeof(TQGO),0);
       QGO^.kod:= this_airbase;
       FSplit(FN, sDir,sName,sExt);
       get_plan_date(QGO^.date,FN);
       if QGO<>nil then read_this_QGO:= DB_najdi(QGO,FN, db_QGO_RIADKOV,@decodeDB_QGO,@codekey_QGO, true,@disp_QGO,'')
       else read_this_QGO:= -1
     end;
{$ENDIF}

function read_QGO(key: string; QGO: PQGO): int;
   begin
     if (QGO<>nil) and (key<>'') then
        begin
          decodekey_QGO(key, QGO);
          read_QGO:= DB_najdi(QGO,get_DBfn(QGO^.date, pathQGO,extQGO),db_QGO_RIADKOV,@decodeDB_QGO,@codekey_QGO,
                              true,@disp_QGO,''
                             )
        end
     else read_QGO:= -1
   end;


procedure save_QGO(_QGO: PQGO);
    var   QGO: TQGO;
    begin
      new_QGO(_QGO, @QGO);
      DB_oprav(@QGO, get_DBfn(QGO.date, pathQGO,extQGO), db_QGO_RIADKOV,@codeDB_QGO,@codekey_QGO,@dbchg_QGO, dbattr_QGO);
      disp_QGO(@QGO);
    end;


procedure save_QGO_RPL(_QGO: PQGO);
    var   QGOi: TQGO;
    begin
      new_QGO (_QGO,@QGOi);
      QGOi.date := RPL_DATE;
      QGOi.stat:= cnst_disk;
      fillchar (QGOi.rec,sizeof(QGOi.rec),0);
      DB_oprav (_QGO, get_dbQGO_RPLfn, db_QGO_RIADKOV,
                @codeDB_QGO,@codekey_QGO_RPL,
                @dbchg_QGO_RPL, dbattr_QGO
               );
      disp_QGO (@QGOi)
    end;
