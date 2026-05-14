{ ---------------------------------------------------------------
  EXT
 תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
 תתתתתתתתתתתתתתתתתתתתתתתתת
  (c) ALES 1996,9 Kosice,
 תתתתתתתתתתתתתתתתתתתתתתתתת
}

{$DEFINE EXTERNAL_NET}

{$I comp.h}

{$I _EXT_1d.h}     { popis algoritmu spracovania dat }
{$I _EXT_2d.h}


unit _EXT;


interface

    uses   TypeDef,
           _Check, IO, Arrays, AStream, coms,
           DB,
           {$I unit_gr.h},
           {$I unit_oop.h},
           _MTK_2, _L4_def, _EXT_def,
           NET_def, FIR_def, _FDP_def;


    {$I _EXT_cnst.h}
    {$I _EXT_title.h}
    {$I _EXT_func.h}
    {$I _EXT_lam.h}
    {$I _EXT_object.h}
    {$I _EXT_nodes.h}
    {$I _EXT_edi.h}

    function  get_icao_streamFN (path,ext: string; den,mes,rok, hod,min: word): string;

    const  DEV_EXT : PO_EXT = nil;

           max_EXT_DEVICES  = 20;
           EXT_DEVICESpoc   : byte = 0;
    type   TEXT_DEVICES     = array[0..max_EXT_DEVICES-1] of PO_EXT;
    var    EXT_DEVICES      : TEXT_DEVICES;

    procedure Init_EXT;
    procedure Done_EXT;


implementation

uses  DOS, BIOS, prnt, mem, utime, mess, math, str0, keyb, sets, msg,
      Kody, _NET,
      Vypocty, Archiv;

{const  process_ERR_pkt : bool = true;}


{$I _EXT_buffers_pkt.inc} { TEXTpkt,TIREGpkt }
{$I _EXT_nodes.inc}

{$I _EXT_editor.inc}      { editor           }
{$I _EXT_eeditor.inc}     { err_editor       }

{$I _EXT_.inc}            { init, cfg, initialize }
{$I _EXT_object.inc}      { TObject }
{$I _EXT_check.inc}       { check   }
{$I _EXT_net.inc}         { NET; synchronizacia master-server }

{$I _EXT_receive_pkt.inc} { pkt: save, read, receive          }
{$I _EXT_send_pkt.inc}    { pkt: send do EXT                  }
{$I _EXT_decode_pkt.inc}  { pkt: process, decode head & data  }
{$I _EXT_archive_pkt.inc} { pkt: archive, writeln             }
{$I _EXT_lam.inc}         { spracovanie povtrdeni             }
{$I _EXT_error_pkt.inc}   { error, alert                      }
{$I _EXT_test_pkt.inc}    { txt_file...                       }

{$I _EXT_functions.inc}   { ak...                             }

var  SaveMain0 : TProc;
     SaveMainD : TProc;

procedure check0_EXT;
    var   i: int;
    begin
      if not EXT_ENABLED then Exit;

      if @SaveMain0<>nil then SaveMain0;
      {$IFDEF EXTERNAL_NET}
       if _EXT_EN then for i:= 0 to EXT_DEVICESpoc-1 do EXT_DEVICES[i]^.check0;
      {$ENDIF}
    end;

procedure checkD_EXT;
    var   i: int;
    begin
      if not EXT_ENABLED then Exit;

      if @SaveMainD<>nil then SaveMainD;
      {$IFDEF EXTERNAL_NET}
       if _EXT_EN then for i:= 0 to EXT_DEVICESpoc-1 do EXT_DEVICES[i]^.check;
      {$ENDIF}
    end;


procedure Init_EXT;
    begin
      EXTs:= nil;
      EXTpoc:= 0;
    end;

procedure Done_EXT;
    var   i: int;
    begin
      for i:= 0 to EXT_DEVICESpoc-1 do
        begin
          Dispose(EXT_DEVICES[i],Done);
          EXT_DEVICES[i]:= nil;
        end;

      for i:= 0 to EXTpoc-1 do
        begin
          disp_EXTnode(EXTs^[i]);
          dispose(EXTs^[i]);
        end;
      EXTs:= nil;
      EXTpoc:= 0;
    end;


begin
  SaveMain0:= ACheckProcesses0;
  ACheckProcesses0:= check0_EXT;

  SaveMainD:= ACheckProcessesA;
  ACheckProcessesD:= checkD_EXT;
end.