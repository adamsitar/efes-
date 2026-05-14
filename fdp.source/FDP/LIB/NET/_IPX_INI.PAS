(*-------------------------------------------------------------------*)
(* LETVIS FDP - IPX                                                  *)
(* (c) Ales Kosice 1993,96  (Jirko, Mirko a nakoniec ab)             *)
(*-------------------------------------------------------------------*)
{$I comp.h}
{$I comp_IPX.h}

{
  predpoklad : TIPXdpacket = TNETBpkt_data je polozka inp_brd_buff !
}

unit _IPX_ini;


interface


      uses  TypeDef, Arrays,
            NET_def, IPX_def;


      {$IFDEF IPX}
        procedure  IPX_detect;
        procedure  IPX_init;
      {$ENDIF}



implementation

uses Crt, Dos, BIOS, IO,
     mem, math, str0, sets, mess,
     _IPX;

{$IFDEF IPX}

  procedure  IPX_done; forward;

  {$IFDEF SOCKET}
    {$I IPX_in0s.inc}
  {$ELSE}
    {$I IPX_in0.inc}
  {$ENDIF}


  { IPX.ini je pri protokole IPX3 uz nepotrebny, tabulka uzlov sa moze
    generovat autoamticky, no nemam to zatial osetrene
  }

  var  SaveExit: pointer;

  {$IFDEF SOCKET}
    {$I IPX_inis.inc}   { inicializacia IPX }
  {$ELSE}
    {$I IPX_ini.inc}
  {$ENDIF}


 {$I IPX_cfg.inc}

 procedure IPX_detect;
     var   i: int;
     begin
       SaveExit:= ExitProc;
       ExitProc:= @IPX_done;

       for i:= 0 to maxIPX_NODEs-1 do IPXnodes[i]:= New(PIPXnode,Init(i));

       {$IFDEF IPX}
        IPX_installed:= GetAdrIPX;
        {$IFDEF IPX}
          if (not NONET) and (not IPX_installed) then RunError('Ethernet card is not installed or IPX not initialized.')
          {else writeln('Ethernet card detected.')};
        {$ENDIF}
       {$ELSE}
        IPX_installed:= false
       {$ENDIF}

       IPXcfg_read
     end;

{$ENDIF}

end.
