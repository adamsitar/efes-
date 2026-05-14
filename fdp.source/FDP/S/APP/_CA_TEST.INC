(*
procedure test_fn(head: string);
    var   data : pchars;
          size,size_: long;
    begin
      if (DEV_ASOC<>nil) and ReadFile(pointer(data),size,head+'.'+extASOC) then
         begin
           size_:= size;
           if data^[size_-1] in [kbLF,kbCR] then dec(size_);
           if data^[size_-1] in [kbLF,kbCR] then dec(size_);
           {DEV_ASOC^.send_data('',head,'', data,size_, '');}
           freemem(data,size);
         end;
    end;
*)

procedure test_OLDI_FPL;
    var   s: string;
    begin
      s:= '6506-IF-01ZZZZ/L-F/C-LKPR2200-K0500F080 MZ650 MZ260-LZIB0040 LZTT-OPR/34 RMK/UKOL03 RMK/MNM0112 TYP/L39';
      if DEV_CAMUS<>nil then DEV_CAMUS^.send_data('', hd_CAL4[msFPL],'','', @s[1],length(s), '',0)
    end;

procedure test_OLDI_CHG;
    var   s: string;
    begin
      s:= '6506-LKPR-LZIB-8/VM';
      if DEV_CAMUS<>nil then DEV_CAMUS^.send_data('', 'CHG','','', @s[1],length(s), '',0)
    end;

procedure test_OLDI_DLA;
    var   s: string;
    begin
      s:= '6506-LKPR2317-LZIB';
      if DEV_CAMUS<>nil then DEV_CAMUS^.send_data('', 'DLA','','', @s[1],length(s), '',0)
    end;

procedure test_OLDI_CNL;
    var   s: string;
    begin
      s:= '6506-LKPR-LZIB';
      if DEV_CAMUS<>nil then DEV_CAMUS^.send_data('', 'CNL','','', @s[1],length(s), '',0)
    end;

{
procedure test_OLDI_ABI;
    var   s: string;
    begin
      s:= '1010A-LKPR-BODAL/1745F450-LZIB-9/4MI29/L-15/N0450F450 BODAL MB363 MB371 ODNEM';
      if DEV_CAMUS<>nil then DEV_CAMUS^.send_data('', hd_CAL4[msABI],'', @s[1],length(s))
    end;
}

procedure test_OLDI_ACT;
    var   s: string;
    begin
      s:= '6506-LKPR-BODAL/1750F450-LZIB-9/2MG29/L-15/N0450F450 BODAL MB363 MB371 ODNEM';
      if DEV_CAMUS<>nil then DEV_CAMUS^.send_data('', hd_CAL4[msACT],'','', @s[1],length(s), '',0)
    end;

procedure test_OLDI_REV;
    var   s: string;
    begin
      s:= '1010A-LKPR-BODAL/1745F450-LZIB-9/4MG29/L-15/N0450F450 BODAL MB363 MB371 ODNEM';
      if DEV_CAMUS<>nil then DEV_CAMUS^.send_data('', 'REV','','', @s[1],length(s), '',0)
    end;


procedure test_OLDI_ERR;
    var   s: string;
    begin
      s:= '1010-L3?R-BODAL1745F450-LZI-94MG29-15/N0450F450 BODALMB371ODNEM';
      if DEV_CAMUS<>nil then DEV_CAMUS^.send_data('', 'ERR','','', @s[1],length(s), '',0)
    end;


{$IFDEF DD_EXE}
(*
 procedure O_CAMUS._process_test (data: pbytes; dlz: int);
     {$IFNDEF CAMUS_OLDI}
      var    tpkt: TCAMUSpkt;
     {$ENDIF}
     begin
      {$IFDEF CAMUS_OLDI}
        inherited _process_test (data,dlz);
      {$ELSE}
       tpkt.poc:= minimum(dlz,CAMUS_PACKET_SIZE);
       move(data^,tpkt.buf,tpkt.poc);
       ibuff^.save(@tpkt);
      {$ENDIF}
     end;

  procedure O_CAMUS.test_file(fn: string; soc: char; off: int);
      begin
       {$IFDEF OLDI}
        stat:= DATA_READY_STATE;
       {$ENDIF}
        inherited test_file(fn,soc,off)
      end;
*)
{$ENDIF}
