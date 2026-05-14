{$I comp_X25.h}
{$O+}


unit  X25_def;


interface


    uses  TypeDef,
          NET_def;


   { IFDEF _X25}

    { I net_def1.h}   { TNETpacket }

    {$I X25_def0.h}   { TimeOut-y  }



    const  X25_PACKET_SIZE = 1024; {? alebo cfg ? sizeof(TNETpkt);}  { 1024 = maximum size of NPDU }
           X25_ADR_SIZE    = 16;


    type   Network_Service_Access_Point = array [0..X25_ADR_SIZE-1] of char;
           Network_User_Address         = string[X25_ADR_SIZE-1];

           TX25adr  = array[0..(X25_ADR_SIZE-1) - 1] of byte;
           TX25name = Network_User_Address;


    {const  archive_X25operation : PProc_s = nil;}


    type   X25_packet_array   = array[0..X25_PACKET_SIZE-1] of byte;
           PX25_packet_array  = ^X25_packet_array;  { doplnene by Pali (c) I.1994 }

           TX25data           = X25_packet_array;


           PX25_INPUT_BUFFER = ^X25_INPUT_BUFFER;    { UNIVERZALNY PRIJIMACI BUFFER }
           X25_INPUT_BUFFER  = record
             LINE   : word;             { cislo linky    }
             CHAN   : word;             { cislo kanalu   }
             SIZE   : word;             { velkost paketu }
             PACKET : byte;             { typ paketu     }
             QMD    : byte;             { QMD bity       }
             CAUSE  : byte;             { pole priciny   }
             DIAG   : byte;             { diag.pole      }

             DATA   : X25_PACKET_ARRAY; { vlastne data   }
             NEXT   : PX25_INPUT_BUFFER;
           end;


           PX25_OUTPUT_BUFFER = ^X25_OUTPUT_BUFFER;
           X25_OUTPUT_BUFFER  = record
             CHAN   : word;
             ADR    : TX25name;         { moze byt byte napr. '105' = 105 }
             TICKS  : word;             { kvoli identifikacii, kedy bol vyslany paket }
             SIZE   : word;

             DATA   : X25_PACKET_ARRAY;
             NEXT   : PX25_OUTPUT_BUFFER;
           end;


           PX25_SERVICE_BUFFER = ^X25_SERVICE_BUFFER;
           X25_SERVICE_BUFFER  = record
             CHANNEL : word;
             SIZE    : word;
             PACKET  : byte;
             QMD     : byte;
             CAUSE   : byte;
             DIAG    : byte;

             DATA    : pbytes;
           end;


           PX25_CALL_BUFFER = ^X25_CALL_BUFFER;
           X25_CALL_BUFFER  = record
             CHANNEL   : word;
             CALLG_ADR : TX25name;
             CALLD_ADR : TX25name;
             FAC_LEN   : byte;
             FAC_DATA  : pbytes;

             USR_LEN   : byte;
             USR_DATA  : pbytes;
           end;


    procedure  _X25name_to_adr(adr_n: TX25name; var adr_a: TX25adr);
    procedure  _X25adr_to_name(adr_a: TX25adr ; len: byte; var adr_n: TX25name);

  { ENDIF}


implementation

{ IFDEF _X25}
{
  Konverzia adresy zo stringu na pole
}
procedure _X25name_to_adr(adr_n: TX25name; var adr_a: TX25adr);
    var   i: byte;
    begin
      fillchar(adr_a,sizeof(adr_a),0);
      for i:= 1 to (length(adr_n) and $F) do adr_a[i-1]:= ord(adr_n[i])
    end; { _X25name_to_adr }


{
  Konverzia adresy z pola na string
}
procedure _X25adr_to_name(adr_a: TX25adr; len: byte; var adr_n: TX25name);
    var   i: int;
          s: string[1];
    begin
      adr_n:= '';
      for i:= 0 to len-1 do
        begin
          str(adr_a[i],s);
          adr_n:= adr_n + s
        end
    end; { _X25adr_to_name }

{ ENDIF}

end.