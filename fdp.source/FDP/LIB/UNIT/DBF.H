{$IFDEF DB_DBASE}

    { ------------------------------------
      Vystup do DBASE
      ------------------------------------
    }

    const { X hlavicka
          }
           dbf_START_OF_FILE_03 = $03;
           dbf_START_OF_FILE_08 = $08;

           dbf_FILL_HEADER      = $00;
           dbf_FILL_DATA        = $20;

           dbf_END_OF_HEADER    = $0D;
           dbf_END_OF_DATA      = $1A;


          { Typy poloziek
          }
           dbfSTRING = 'C';
           dbfCISLO  = 'N';
           dbfDATUM  = 'D';
           dbfBOOL   = 'L';
           dbfMEMO   = 'M';
           dbfBIN    = 'B';


          { Pripustne hodnoty
          }
           dbf_TRUE  = 'T';
           dbf_FALSE = 'F';

           extDBF    = 'DBF';

    { Povolene operacie nad DBF (vety s polozkami)

       - otvorenie
       - zatvorenie
       - posun po vetach : vpred, vzad, zac, koniec
       - nacitanie
       - oprava, zapis
       - vymaz vety
       - obnovenie vety
    }

    const  max_dbffields = 100;

    type { DBF veta : celkom musi byt 32 byte
         }
           PDBFfield  = ^TDBFfield;
           TDBFfield  = record
             name   : array[1..10] of char;  { meno polozky (velkymi pismenami)   }
             null   : char;                  { nulov˜ (mal by byt) alebo iny znak }
             typ    : char;

             offset : word;                  { offset konca od zaciatku }
             r1     : word;                  { rezerva                  }

             size,                           { dlzka polo‘ky           }
             dec    : byte;                  { pocet desetinnych miest }

             fill   : array[1..14] of char
           end;

         { Konfiguracny popis polozky dbf
         }
           PDBFfdesc  = ^TDBFfdesc;
           TDBFfdesc  = record
             name : string[10];
             typ  : char;
             dlz  : byte;
           end;

           TDBFfdescs  = array[0..max_dbffields-1] of TDBFfdesc;
           PDBFfdescs  = ^TDBFfdescs;


         
         { DBF hlavicka : celkom musi byt 32 byte
         }
           TDBFhead = record
             X      : byte;    { priznaky: 03 bez memo poli, 08 s memo polom }

             rok    : byte;    { posledne dva znaky roka }
             mes    : byte;
             den    : byte;

             poc    : long;    { pocet viet }
             zac    : word;    { offset prvnej vety od zaciatku souboru }
             dlz    : word;    { dlzka vety }

             fill   : array[1..20] of char
           end;


    type   PDBF_buff  = ^TDBF_buff;
           TDBF_buff  = Tchars;

           TDBFcode_proc   = procedure (p: pointer; buff: PDB_buff; size: int{; polia: PDBFfdescs});
           TDBFdecode_proc = procedure (buff: PDB_buff; p: pointer; size: int{; polia: PDBFfdescs});



    type { ---------------------------------------
           Objekt  DBF
           ---------------------------------------
         }
            PDBF = ^TDBF;
            TDBF = object

              FN         : string;
              DBf        : file;

              head       : TDBFhead;
              polia      : PDBFfdescs;
              poli       : byte;

              buff_size  : long;     { velkost buffera }
              buff       : PDBF_buff;

              FNExist    : bool;     { existuje subor }
              RWClose    : bool;     { urcuje, ci otvori a zatvori DB po kazdom pristupe }

              hlavicka   : bool;     { zhoduju sa zadane parametre s realnymi }
              semaphor   : bool;
              zapisane   : bool;     { vypoctova premenna pre urcenie, ci bol upraveny obsah db }

              DATAcode   : pointer;  { @TDBFcode_proc   }
              DATAdecode : pointer;  { @TDBFdecode_proc }
              kluc       : int;

              public
              constructor Init(_FN : string;
                               _RWClose : bool;

                               _polia : PDBFfdescs;
                               _poli  : byte;

                               _DATAcode   : pointer; { @TDBFcode_proc    }
                               _DATAdecode : pointer; { @TDBFdecode_proc  }
                               _kluc       : int      { pozicia pre kluc }
                              );
              destructor  Done;

              function    poloziek: long;

              function    citaj_vetu(_pos: long): bool;
              procedure   zapis_vetu(_pos: long; _ins: bool);

              procedure   koduj_vetu(p: pointer);
              procedure   dekoduj_vetu(p: pointer);

              function    citaj (_pos: long; _data: pointer): bool;
              procedure   zapis(_data: pointer; _pos: long; _ins: bool);

              (*
              function    citaj (_pos : long; _data: pointer): bool;
              function    najdi (_data: pointer; _read: bool; _disp_data: pointer): long;

              function    najdi_nil: long;
              function    najdi_data: long;

              procedure   zapis (_data: pointer; _pos: long; _ins: bool);
              procedure   oprav (_data: pointer);

              {protected}
              procedure   koduj_vetu  (p: pointer); { p :  -> data   }
              procedure   dekoduj_vetu(p: pointer); { data -> DBbuff }
              function    vyhladaj_kluc (_kluc: TDB_riadok): long;
              function    vyhladaj_data (_data: pointer): long;
              *)

            end; { TDBF }


(*    function do_alloc_DBF({ a) funkcia pre spracovanie poloziek DBF }
                               IFunc_p   : pointer;    { TIfunc <> nil }
                               parametre : pointer;    { Parmetre pre IFunc_p }

                          { b) parametre pre pole }
                               pole_adr  : pointer;    { adresa adresy pola <> nil }
                               top_adr   : pointer;    { adresa ukazovatela na vrchol <> nil}
                               max_pole  : int;        { maximum overdrive }
                               size_item : word;       { velkost polozky }

                               data_item   : pointer;  { ukazovatel na polozku typu pola ako - funkcia buffera }
                               disp_item   : pointer;  { Tproc_p odalokuje nacitany buffer }
                               data_filter : pointer;  { ukazovatel na podmienku }
                               filter      : pointer;  { TBfunc_p2: premenna, podmienky }

                               add_item    : pointer;  { Tproc_p3l alokacia, moze byt nil  }
                               del_item    : pointer;  { Tproc_p3 dealokacia, moze byt nil  }
                               vzostupne   : bool;     { smer nacitavania : true=vzostupne }

                          { c) parametre pre DBF  }
                               FN          : string;
                               riadkov     : byte;
                               DATAdecode  : pointer
                         ): int;

*)

      procedure  code_dbf_STRING (s: string; buff: PDBF_buff; var pos: int; dlz,size: int);
      procedure  code_dbf_CISLO  (cis: long; buff: PDBF_buff; var pos: int; dlz,size: int);

{$ENDIF}