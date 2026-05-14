{
ÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜ
Û                       Û
Û Spracovanie DB        Û
ÛÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÛ
}

procedure str_toDBstr_(s: string; var buff: TDB_riadok);
    begin
      buff[0]:= chr(sizeof(buff)-1);
      move(s[1],buff[1],minimum(DB_riadok,length(s)))
    end;

procedure str_toDBstr (s: string; var buff: TDB_riadok);
    begin
      str_toDBstr_(NL_to_NL_(s),buff)
    end;

function  DBstr_to_str_ (buff: TDB_riadok): string;
    var   s : string;
    begin
      move(buff[0],s[0],minimum(sizeof(buff),sizeof(s)));
      DBstr_to_str_:= s
    end;

function  DBstr_to_str (buff: TDB_riadok): string;
    var   s : string;
    begin
      s:= DBstr_to_str_(buff);
      if (length(s)>1+length(kbNL)) and (copy(s,length(s)-1,length(kbNL))=kbNL) then s[0]:= chr(length(s)-length(kbNL));
      DBstr_to_str:= NL__to_NL(cut_r(s))
    end;


{ procedury volajuce DB len s potrebnymi parametrami
}

function  DB_head (_FN: string; var head: TDB_head): bool;
    var   DB: PDB;
    begin
      DB:= New(PDB,Init(_FN, false, 1, nil,nil,nil,nil, 0));
      DB_head:= DB^.FNExist;
      head:= DB^.head;
      Dispose(DB,Done)
    end;

function  DB_poloziek(_FN: string; _riadkov: byte): long;
    var   DB: PDB;
    begin
      DB:= New(PDB,Init(_FN, false, _riadkov, nil,nil,nil,nil, 0));
      DB_poloziek:= DB^.poloziek;
      Dispose(DB,Done)
    end;

function  DB_citaj(_pos: long; _data: pointer;
                   _FN: string; _riadkov: byte; _DATAdecode: pointer
                  ): bool;
    var   DB: PDB;
    begin
      DB:= New(PDB,Init(_FN, DB_RWClose, _riadkov, nil,_DATAdecode,nil,nil, 0));
      DB_citaj:= DB^.citaj(_pos, _data);
      Dispose(DB,Done)
    end;


function  DB_citaj_kluc (_pos: long; _FN: string; _riadkov: byte): string;
    var   DB: PDB;
    begin
      DB:= New(PDB,Init(_FN, DB_RWClose, _riadkov, nil,nil,nil,nil, 0));
      DB_citaj_kluc:= DB^.citaj_kluc(_pos);
      Dispose(DB,Done)
    end;


function  DB_citaj_riadok_vety (_pos,_rdk: long; _FN: string; _riadkov: byte): string;
    var   DB: PDB;
    begin
      DB:= New(PDB,Init(_FN, DB_RWClose, _riadkov, nil,nil,nil,nil, 0));
      DB^.citaj_vetu(_pos);
      if _rdk<_riadkov then DB_citaj_riadok_vety:= DB^.buff^[_rdk]
      else DB_citaj_riadok_vety:= '';
      Dispose(DB,Done)
    end;


function  DB_najdi_(_data: pointer; _FN: string; _riadkov: byte;
                    _DATAdecode,_KEYcode: pointer;
                    _read: bool; _disp_data: pointer;
                    _p_another_key: PSFunc_s;
                    _title: string
                   ): long;
    var   DB: PDB;
    begin
      if __INFO_DB and (_title<>'') then
         begin
           if _title='' then _title:= msgSEARCH+': '+_FN;
           InfoCakaj(msgWAITING,_title+'...');
         end;
      DB:= New(PDB,Init(_FN, DB_RWClose, _riadkov, nil,_DATAdecode,_KEYcode,nil, 0));
      DB^.p_another_key:= _p_another_key;
      DB_najdi_:= DB^.najdi(_data, _read, _disp_data);
      Dispose(DB,Done);
      if __INFO_DB and (_title<>'') then InfoCakaj_zatvor;
    end;

function  DB_najdi(_data: pointer; _FN: string; _riadkov: byte;
                   _DATAdecode,_KEYcode: pointer;
                   _read: bool; _disp_data: pointer;
                   _title: string
                  ): long;
    begin
      DB_najdi:= DB_najdi_(_data, _FN,_riadkov,
                           _DATAdecode,_KEYcode,
                           _read, _disp_data,
                           nil,_title
                          )
    end;


function  DB_najdi_nil(_FN: string; _riadkov: byte): long;
    var   DB: PDB;
    begin
      DB:= New(PDB,Init(_FN, DB_RWClose, _riadkov, nil,nil,nil,nil, 0));
      DB_najdi_nil:= DB^.najdi_nil;
      Dispose(DB,Done)
    end;


function  DB_najdi_data(_data: pointer; _FN: string; _riadkov: byte;
                        _DATAdecode: pointer
                       ): long;
    var   DB : PDB;
          res: long;
    begin
      DB:= New(PDB,Init(_FN, DB_RWClose, _riadkov, nil,_DATAdecode,nil,nil, 0));
      res:= DB^.najdi_data;
      if res>-1 then DB^.citaj(res, _data);
      DB_najdi_data:= res;
      Dispose(DB,Done)
    end;


procedure DB_zapis(_data: pointer; _pos: long; {_ins: bool}
                   _FN: string; _riadkov: byte;
                   _DATAcode,_KEYcode, _DBchg: pointer;
                   _attr: TDB_attr
                  );
    var   DB: PDB;
    begin
      DB:= New(PDB,Init(_FN, DB_RWClose, _riadkov, _DATAcode,nil,_KEYcode, _DBchg, _attr));
      DB^.zapis(_data, _pos, true);
      Dispose(DB,Done)
    end;


function  DB_oprav_riadok(_oprava,_data: pointer; _kluc: TDB_riadok;
                         _FN: string; _riadkov: byte;
                          _DATAcode,_KEYcode : pointer;
                          _riadok: long; _code: pointer;
                          _attr: TDB_attr
                         ): bool;
    var   DB: PDB;
    begin
      DB_oprav_riadok:= true;
      DB:= New(PDB,Init(_FN, DB_RWClose, _riadkov, _DATAcode,nil,_KEYcode,nil, _attr));
      if not DB^.oprav_riadok (_kluc,_oprava,_riadok,_code) then
         if _data<>nil then DB^.zapis (_data,-1,false)
         else DB_oprav_riadok:= false;
      Dispose(DB,Done)
    end;


procedure DB_oprav(_data: pointer;
                   _FN: string; _riadkov: byte;
                   _DATAcode,_KEYcode, _DBchg: pointer;
                   _attr: TDB_attr
                  );
    var   DB: PDB;
    begin
      DB:= New(PDB,Init(_FN, DB_RWClose, _riadkov, _DATAcode,nil,_KEYcode, _DBchg, _attr));
      DB^.oprav(_data);
      Dispose(DB,Done)
    end;


procedure DB_zrus(_data: pointer;
                   _FN: string; _riadkov: byte;
                   _DATAcode,_KEYcode, _DBchg: pointer
                  );
    var   DB: PDB;
    begin
      DB:= New(PDB,Init(_FN, DB_RWClose, _riadkov, _DATAcode,nil,_KEYcode, _DBchg, 0));
      DB^.zrus(_data);
      Dispose(DB,Done)
    end;
