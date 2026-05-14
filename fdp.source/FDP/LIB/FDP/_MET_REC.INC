{ --------------
   Prijaty plan
  --------------
}
 procedure _pkt_SYN(SYN: PSYN);
     begin
       save_SYN(SYN);
       distribute_SYN(SYN,[],[]);
       if (p_syn_dbscroller<>nil) then p_syn_dbscroller^.data_update(SYN);
     end;

 {$IFDEF MET_RLI}
  procedure _pkt_MRL(pkt: TNETpkt);
      begin
        if (fn_MRL='') then
           if is_SOD_MRL(pbytes(pkt.pkt.data),pkt.pkt.dlz) then
              begin
                fn_MRL:= get_ARCHfn(bios.min)+'.'+extMRL
              end
           else Exit;
        save_MRL(pbytes(pkt.pkt.data),pkt.pkt.dlz);
        distribute_MRL(pbytes(pkt.pkt.data),pkt.pkt.dlz);
        if is_EOD_MRL(pbytes(pkt.pkt.data),pkt.pkt.dlz) then
           begin
             fn_MRL:= '';
           end
      end;
 {$ENDIF}


{ --------------------
   Prijate potvrdenie
  --------------------
}
 procedure _ack_SYN(key: string; rec: Tplan_rec; fdp: bool; nd: int);
     var   SYN : TSYN;
     begin
       if read_SYN(key, @SYN)<>-1 then
          begin
            if NET_ACK_ALL then
               begin
                 rec_copy (rec,SYN.rec);
               end
            else begin
                   rec_pkt (nd,SYN.rec,is_ack);
                 end;
            save_SYN(@SYN);
            disp_SYN(@SYN)
          end
     end;


{ --------------------
   Inicializacia uzla
  --------------------
}
 {$IFDEF MET_RLI}
   procedure initialize_MRL (nd: int);
       var   fn : string;
             f  : file;
             data : pbytes;
             size,buff_size : int;
             dt : DateTime;
             ri,rd : real;
       begin
         fn:= najmladsi_subor (pathMRL,'*.'+extMRL);
         if fn='' then Exit;

        { udaje starsie ako nastavenny limit sa uz neposielaju
        }
         UnpackTime(_GetFTime(pathMRL+fn),dt);
         rd:= dt_MRLdata; rd:= rd*60;
         with dt do ri:= DTtoSec(year,month,day, hour,min,sec);
         if ri+rd<absTime then Exit;

         Assign(f,pathMRL+fn);
         Reset(f,1);
         buff_size:= sizeof(int)+max_MRLsize;
         getmem(data,buff_size);
         while read_MRL(f, data,size, 0,max_MRLsize) and (not IOError) do
           begin
             NETsend_msg (NODEs^[nd].desc.adr,spr0_MRL,pchars(data),size,false,net_flag_SEND);
             CheckProcesses0
           end;
         freemem(data,buff_size);
         Close(f);
       end;
 {$ENDIF}

