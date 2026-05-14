    const ispath__UP = false;
          isext__UP  = true;


   { ------------
      NET
     ------------
   }

    {procedure init_FUA;
    procedure done_FUA;}

    function  neschvalovany_PRS (kod: string): bool;

    {$IFDEF FUA_DATA}
     function _up_head (fn  : string;
                        buf : PTxtFileBuffer;

                        var _up : string;   { typ spravy   }
                        var cis : string;   { cislo spravy }
                        var ref : string;   { odkazovana sprava }

                        var adr : string;   { adresati spravy }
                        var zac : TDatum;   { datum zaciatku platnosti spravy }
                        var kon : TDatum;   { datum konca platnosti spravy }

                        var val : TDate;

                        check_all : bool;
                        typ     : string;   { ocakavany tup spravy }

                        var res : string
                       ): bool;             { true, ak subor existuje }

    function _get_db_up_dfn (val: TDate; path,cis: string): string;


    procedure _pkt_AUP (var pkt: TNETpkt); far;
    procedure _pkt_UUP (var pkt: TNETpkt); far;

    procedure _ack_AUP (key: string; rec: Tplan_rec; fdp: bool; nd: int); far;
    procedure _ack_UUP (key: string; rec: Tplan_rec; fdp: bool; nd: int); far;
   {$ENDIF}
