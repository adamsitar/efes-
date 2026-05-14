{$I comp.h}

uses  ovr,bios, typedef, math, str0, crt, msg, io, sets,
      {$I unit_net.h}, _ssr;

var s : string;
    cislo_tmp_packet : long;
    N: PNET;
    nd : int;
    pomb : bool;

begin
 _info ('\xe\d\TMP\sprlam.@@@');

 s:= '\xe\d\prs\27-09-99.aup';
 {
 NET_init (New(PNET,Init));
 NETdistribute_file ([FDP],[],[],spr_AUP,s,inf_FUA,net_flag_SEND,false,true,true);
 NETsend_file ('S2',spr_AUP,s,inf_FUA,net_flag_SEND,false,true,true);
 }
end.

{

  NET_init (New(PNET,Init));
  nd:= 0;
  is_to_nd (nd,inf_FPL4,nil,nil,@pomb)
end.



  s:= najmladsi_subor('\temp\','*.pkt');
  {$IFOPT R+} {$DEFINE R} {$R-} {$ENDIF}
   if s<>'' then cislo_tmp_packet:= scish_(delchar(s,setPism+['.']),false)+1
   else cislo_tmp_packet:= 0;  { potom posledny paket }
  {$IFDEF R} {$UNDEF R} {$ENDIF}
      {$I unit_gr.h},
      io,events,cm,
      _FPL4, _FPL4s;

       {$IFDEF _OVR}
        {$I units.ovl}
        {$I net.ovl}
        {$I oop.ovl}
       {$ENDIF}

  InitBGI;
  SetCommand(_Event,nil,cmPREHLAD_FPL4_PPL);
  _handle_event_FPL4 (_Event,nil,nil);

  _help_index;
  _infop(pathLST+strpas(fnRTE.fn),      tit_rte_ats,  0,0,true,false,nil);
}