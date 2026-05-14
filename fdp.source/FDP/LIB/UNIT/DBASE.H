{$IFDEF DB_DBASE}

    const {-- Pouze specifick‚ chyby, ostatn¡ jsou shodn‚ s chybami DosFile }
          MemErr    = $2001;   { P©ete‡en¡ pamˆti }
          StruErr   = $2002;   { Struktura datab zov‚ho souboru je prazdna }
          FormatErr = $2003;   { To nen¡ soubor DBASE }

    type  FieldName  = string[12];
          RecBufType = array[0..0] of Char;

    type  { --------------------------------------- }
          {  FieldPtr                               }
          { --------------------------------------- }
            FieldPtr = ^Field;
            Field = object(Node)
              Name   : array[1..10] of char;
              Null   : char; { nulov˜ znak }
              Typ    : char;
              Offset : word;
              R1     : word; { rezerva }
              Len,           { d‚lka polo‘ky  }
              Dec    : byte; { po‡et desetinn˜ch m¡st }
              Fill   : array[1..14] of Char;
              {-- celkem musi byt 32 byte }

              constructor Init;
              destructor  Done; virtual;
            end;


    type  { --------------------------------------- }
          {  FieldList                              }
          { --------------------------------------- }
            FieldList= object(List)
              Count  : word; { po‡et polo‘ek }

              constructor Init;
              procedure   AddField(N: FieldName; T: Char; L,D: byte);

              { Najde pole a nastav¡ Curr }
              function Find(_FN: FieldName): boolean;

              { Tyto funkce vrac¡ hodnoty polo‘ek aktualn¡ho pole }
              function Name: FieldName;
              function Typ: Char;
              function Len: byte;
              function Dec: byte;
              function Offset: word;
            end;


    type  { --------------------------------------- }
          {  TDBF                                   }
          { --------------------------------------- }
            PDBF = ^TDBF;
            TDBF = object( DosFile )
              {-- Hlavi‡ka souboru TDBF }
              X      : byte;    { p©¡znaky: 03 bez memo pol¡, 08 s memo polem }
              Year   : byte;    { posledn¡ dva znaky roku }
              Month  : byte;
              Day    : byte;
              NumRec : long;    { po‡et vˆt }
              Offset : word;    { offset prvn¡ vˆty od za‡ tku souboru }
              RecLen : word;
              Fill   : array[1..20] of char;
              {-- Celkem 32 byte, tak jak le‘¡ v souboru TDBF }

              CurrRec: long;    { aktualn¡ z znam }
              Recs   : FieldList;
              N      : word;       { pocet zapsanych bytu pri posledni diskove operaci }

              {-- Bufr jedn‚ vˆty }
              Updated: boolean;    { zda se do bufru udˆlala zmˆna }
              RecBuf: ^RecBufType; { ukazov tko na bufr vˆty }


              constructor Init(_FN: PathStr);
              destructor  Done; virtual;

              function    Status: word; virtual; { Vrac¡ IO status 0= bez chyby }

              procedure   WriteHeader;
              procedure   Open; virtual;
              procedure   Close; virtual;

              { P©ed Make se mus¡ vytvo©it struktura pomoc¡ Recs.AddField }
              procedure   AddField(_FN: FieldName; T: Char; L,D: byte);
              procedure   Make; virtual;

              function    EOF: boolean;
              procedure   GoTop;         { nastavuj¡ pozici v souboru na za‡ tek }
              procedure   GoBot;         { nastavuj¡ pozici v souboru na konec   }

              { Tyto metody pracuj¡ s aktu ln¡ vˆtou a pou‘¡vaj¡ RecBuf }
              function    GetFld(_FN: FieldName): string; { vr t¡ obsah jedn‚ polo‘ky aktu ln¡ vˆty }
              procedure   PutFld(_FN: FieldName; Value: string);
              procedure   WriteRec; { zap¡¨e bufr a p©ejde na dal¨¡ vˆtu          }
              procedure   ReadRec;  { p©e‡te vˆtu do bufru a p©ejde na dal¨¡ vˆtu }

              procedure   Seek(D: long); virtual;
              procedure   GoBack; { posune smˆrn¡k souboru o jednu vˆtu zpˆt }
              procedure   Write(var Rec); virtual; { p©¡m˜ z pis do souboru bez bufru }
              procedure   Read(var Rec); virtual;
              function    Size: long; virtual;
              function    RecSize : Word; virtual;
              function    FilePos : long; virtual;
            end; { TDBF }



          { ------------------------------------------ }
          { Odvodena DB                                }
          { ------------------------------------------ }
    const   PathToDBF    = '';
            SIZE_DBF_STR = 200;

    type    TDBF_STR  = string[SIZE_DBF_STR];

            PDBF_STRs = ^TDBF_STRs;
            TDBF_STRs = array[0..MAX_ARRAY_SIZE div (SizeOf(TDBF_STR)+1)-1] of TDBF_STR;


    type  { Deklarovanie typu polozky DBF }
            TDBFtype = record
              M : pchar;      {  Meno }
              T : char;       {  Typ  }
              P : byte;       {  Pocet miest}
              D : byte;       {  Pocet des. miest }
            end;

            PDBFdef = ^TDBFdef;
            TDBFdef = array[0..MAX_ARRAY_SIZE div SizeOf(TDBFtype)] of TDBFtype;


            PUnion = ^TUnion;
            TUnion  = record
             case ch: char of
               'C' : (C : string);
               'N' : (N : real);
               'L' : (L : bool);
               'D' : (D : TDate);
            end;


          { ------------------------------------------ }
          { TPolV - polozka vety                       }
          { ------------------------------------------ }
    type    PPolV = ^tPolV;
            TPolV  = object(Node)
              V : TUnion;
              constructor Init;
              destructor Done; virtual;
            end;


          { ------------------------------------------ }
          { TPolVList - zoznam poloziek vety           }
          { ------------------------------------------ }
    type    TPolVList= object(List)
              Count: word;       { po‡et polo‘ek }
              constructor Init;
              procedure   AddVetu;
              procedure   SetVetu(_U : TUnion);

              function Find(_T: char;_U : TUnion): bool; { Najde pole a nastav¡ Curr }
              function V: PUnion;  { Tyto funkce vrac¡ hodnoty polo‘ek aktualn¡ho pole }
            end;


          { ------------------------------------------ }
          { TAppDBF                                    }
          { ------------------------------------------ }
    type    TDBFcode_proc   = procedure(p: pointer; DBFbuff: PDBF_STRs);
            TDBFdecode_proc = procedure(DBFbuff: PDBF_STRs; p: pointer; pos: long);

    type    PAppDBF = ^TAppDBF;
            TAppDBF = object(TDBF)
            { private }
              Veta : TPolVList;   { ukazovatel na vetu - na zoznam jej poloziek }
              D    : char ;       { ' ' - OK, '*' - oznacena Veta na zmazanie   }

              DBFsize: byte;      { pocet poloziek vety                    }
              DBFdef : PDBFdef;   { ukazovatel na definiciu typu vety      }
              DBFbuff: PDBF_STRs; { buffer pre transformaciu DBF->premenna }
              DBFchg : pointer;

              DBFcode  : pointer; { TDBFcode_proc   }
              DBFdecode: pointer; { TDBFdecode_proc }

            { INIT/DONE }
              constructor Init(_FN: PathStr;
                               _DBFdef: PDBFdef; _DBFsize: byte;
                               _DBFcode  : pointer; { TDBFcode_proc   }
                               _DBFdecode: pointer; { TDBFdecode_proc }
                               _DBFchg   : pointer  { @bool }
                              );
              destructor  Done; virtual;


              procedure   koduj_vetu  (p: pointer);  { p :  -> data    }
              procedure   dekoduj_vetu(p: pointer);  { data -> DBFbuff }

              procedure   nastav_na_vetu(_pos: long);
              procedure   citaj_vetu (_pos: long; _DBFbuff: PDBF_STRs);
              procedure   zapis_vetu (_DBFbuff: PDBF_STRs; _pos: long; _ins: bool);
              procedure   oprav_vetu (_DBFbuff: PDBF_STRs; _pos: long);


            { ERASE/UNERASE }
              procedure   oznac_del_veta(_pos: int); { oznaci vetu '*' }
              procedure   obnov_del_veta(_pos: int); { oznaci vetu ' ' }

              procedure   obnov_del_vety;  { vsetky }
              procedure   vymaz_del_vety;  { vsetky }


            { protected }
            { oznacenie viet '*', ' ' }
              function    GetD: bool;           { je urcena na del }
              procedure   SetD(delete: bool);   { zmazat ?         }
              procedure   SetRB0(_d : char);    { nastavenie RecBuf^[0] }
              procedure   SetVetu(_U : TUnion); { pomocna          }
              procedure   ZapisPol(_T : char;_s : string);

              procedure   insert(_pos : long);  { vytvorenie jednej prazdnej vety na _pos }
              procedure   nacitaj;
              procedure   zapis (_pos: long; _ins: bool);
            end;

{$ENDIF}