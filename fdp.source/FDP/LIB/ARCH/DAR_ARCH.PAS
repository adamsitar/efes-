{$I comp.h}
{$R-,O-}
{$C FIXED PRELOAD PERMANENT}

unit DAR_arch;


interface

    uses  TypeDef, uTime,
          {$I unit_net.h},
          DAR_def;


   {$IFDEF ARCHIVE_DAR}
    var   ThisNetwork : Byte;
          EDD_Node    : Byte;
          EDD_Address, ThisNetworkZeroAddress, ThisNetworkBroadcastAddress : Word;
          SaveStrip,SaveRLI : record_header;


    procedure init_DAR   (_save_plans: pointer);
    function  backup_DAR_file(Path: string): int;

    procedure save_RLI   (data: pbytes; data_length: word); far;
    procedure save_FDP   (typ: word; p_data: pointer; p_code: Pcode_NETpkt_data); far;
   {$ENDIF}


implementation

uses  BIOS, _Check, DOS,
      math, str0, mess, io,
      {$I unit_gr.h},
      Arrays, App,
      Msg, FDP_msg, Archiv,
      Asterix, _RTR, FDP_NETb
      {$IFDEF PCTCP}, PCTCP, _PCTCP {$ENDIF}
      ;


const DARbuff  : PBuffer = nil;  { musi byt }

var   DAR_file : file;
const DAR_name : string = '';
      recorded_in_hour: int = 25;
      save_plans: pointer = nil; { procedura pre ulozenie vsetkytch planov na zaciatku kazdej hodiny }


{$IFDEF ARCHIVE_DAR}

 {$I DARarch9.inc}  { ulozenie paketu  }
 {$I DARarch3.inc}  { ulozenie dat     }
 {$I DARarch0.inc}  { init, done, main }

begin
  DAR_buff_size:= Limit(read_cfg_word(SYSTEMcfg,cfg_DAR_buff_size,DAR_buff_size), 0,300, 0);
  archive_DAR:=   read_cfg_bool(SYSTEMcfg,cfg_archive_DAR,archive_DAR);
 {$IFDEF IPX}
  if DAR_buff_size>0 then _IPX.save_RLI:= @save_RLI
 {$ENDIF}
{$ENDIF}
end.
