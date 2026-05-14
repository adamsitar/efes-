{ ----------------------------------------------------
  TSF ... communication protocol with NETBIOS of X25
 תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת

  - vychadza z demo programu toolkitu pre RACAL adapter a dokumnetacie pre popis NETBIOSu TSF

 תתתתתתתתתתתתתתת
  (c) ALES 1996,  Kosice, 18-?.3.,
 תתתתתתתתתתתתתתת


 XE_FACILITIES treba v NOTIFY.CALL extrahovat, vid read.me

}

unit TSF;


{$I comp.h}

{$A-}                                           { ... see "Note" in TSF_t.h }


interface


    uses   TypeDef, X25_def, NET_def;


    {$I TSF_c.h}
    {$I TSF_t.h}
    {$I TSF_def.h}



implementation

{
  A X25MODE is preffered - this means that data transfer must use
  the 20 byte preamble at the head of the data
}

uses  DOS, BIOS,
      math, mess, str0;


{$I TSF_0.inc}  { init   }
{$I TSF_1.inc}  { pkt    }
{$I TSF_2.inc}  { adresy }
{ I TSF_3.inc}  { listen, call, disconnect }

{$I TSF_4.inc}
{$I TSF_5.inc}  { receive }


{$IFDEF DEBUG}
begin
  if sizeof(X25_extended_connection_record)>X25_PACKET_SIZE then RunError('X25_extended_connection_record) > X25_PACKET_SIZE.')
{$ENDIF}
end.
