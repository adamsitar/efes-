constructor O_TSF.Init;
      begin
        SW_INTR_TSF:= $5C;       { interrupt number to use for SWF-x25 calls }
        ADPTR_NUM:= 1;
       {MODE:= X25MODE;}
        PKTWINDOWSZ:= 2;
        PKTPKTSZ:= 128;

        tsf_stat:= tsf_idle
      end;


destructor O_TSF.Done;
     begin
     end;


{
  vola sluzbu rezidentneho modulu TSF
}
function O_TSF.call_API(var ncb: NETBIOS_control_block): byte;
   var   reg : Registers;  { bx and es are significant }
   begin
     ncb.cmd_cplt:= 0;
     reg.bx:= ofs(ncb);
     reg.es:= seg(ncb);

     intr(SW_INTR_TSF,reg);
     call_API:= reg.al
   end;

