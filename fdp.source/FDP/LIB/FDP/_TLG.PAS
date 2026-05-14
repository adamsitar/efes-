{$I comp.h}

unit _TLG;


interface


    uses   TypeDef,
           sets, io,
           {$I unit_gr.h},
           {$I unit_oop.h}, Lists,
           {$I unit_net.h},
           FIR_def, Bod_def, Body, ZemSur,
           _MTK_2, _L4_def, _FDP_def;


    { I _TLG_cnst.h}        { v _FDP_def : nastavenie spracovania planov }


    procedure init_tlg_adr (head: string; form: PAForm; ind_head: int);
    function  read_tlg_adr(form: PAForm; size_adr: int; var prty,adr: string; var res: string; var ires: int): string;

    procedure image_TLGadr(x0,y0,x1,y1: int); far;
    function  _lat_TLG(s: string): string; far;


    {$IFDEF TLG}

      { I _TLG_title.h}

      function _handle_event_TLG (var _Event: TEvent; O: PObject; p: pointer): bool;
    {$ENDIF}


implementation

uses  mouse, keyb, str0, math, mess, utime, msg,
      Crt, DOS, BIOS, DB,
      Archiv,
      form_SYS, frm_TLG;


{$I _TLG.inc}
{$I _TLG_handle.inc}

end.