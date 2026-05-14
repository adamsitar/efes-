(*
{
  Decode the facility field
}
procedure T_AdCOM.DECODE_FACILITY(var FAC : U8BIT_109; FAC_LEN : U8BIT; FC : FACILITIES);
    var   i,count : S16BIT;
    begin
      count:= 0;
      with fc do
        while (fac_len > 0) do
          begin
            inc(count);
            case fac[count-1] of

              $42: begin  { fcp packet }
                     fcp_packet_tx:= fac[count];
                     inc(count);
                     fcp_packet_rx:=fac[count];
                     inc(count);
                     fac_len:= fac_len-3
                   end;

              $43: begin  { fcp window }
                     fcp_window_tx:=fac[count];
                     inc(count);
                     fcp_window_rx:=fac[count];
                     inc(count);
                     dec(fac_len,3)
                   end;

              $02: begin  { throughput }
                     throughput_tx:=(fac[count] SHR 4) and $0f;
                     throughput_rx:=fac[count] and $0f;
                     inc(count);
                     dec(fac_len,2)
                   end;

              $03: begin  { cug basic }
                     cug_req:= 1;
                     cug_index:=fac[count];
                     inc(count);
                     dec(fac_len,2)
                   end;

              $47: begin  { cug extended }
                     cug_req:= 2;
                     cug_index:=(U16BIT(fac[count] SHL 8));
                     inc(count);
                     cug_index:=cug_index and fac[count];
                     inc(count);
                     dec(fac_len,3)
                   end;

              $41: begin  { bcug }
                     bcug_req:= 1;
                     bcug_index:= (U16BIT(fac[count]) SHL 8);
                     inc(count);
                     cug_index:=cug_index and fac[count];
                     inc(count);
                     dec(fac_len,3)
                   end;

              $01: begin  { reverse charging/fast select }
                     reverse_charge:= fac[count] and $01;
                     if (fac[count] and $80) <> 0 then
                       begin
                         fast_select:=2;
                         if (fac[count] and $40) <> 0 then fast_select:=1
                       end;
                     inc(count);
                     dec(fac_len,2)
                   end;

              $44: begin  { RPOA basic }
                     rpoa_req:= 1;
                     rpoa_length:=(U16BIT(fac[count]) SHL 8);
                     inc(count);
                     rpoa_length:=rpoa_length and fac[count];
                     inc(count);
                     dec(fac_len,3)
                   end;

              $c4: begin  { RPOA extended }
                     rpoa_req:= 2;
                     rpoa_length:= (U16BIT(fac[count]) SHL 8);
                     inc(count);
                     i:=0;
                     while i < rpoa_length div 2 do
                       begin
                         rpoa[i]:=(U16BIT(fac[count]) SHL 8);
                         inc(count);
                         rpoa[i]:=rpoa[i] and fac[count];
                         inc(count);
                         inc(i)
                       end;
                     fac_len:=fac_len - (2 + rpoa_length);
                   end;

              $09: begin  { cug oas basic }
                     cugoas_req:= 1;
                     cugoas_index:=fac[count];
                     inc(count);
                     fac_len:=fac_len - 2
                   end;

              $48: begin  { cug oas extended }
                     cugoas_req:= 2;
                     cugoas_index:=(U16BIT(fac[count]) SHL 8);
                     inc(count);
                     cugoas_index:=cugoas_index and fac[count];
                     inc(count);
                     fac_len:=fac_len - 3
                   end;

              $c6: begin { network user id }
                     network_user_id:= 1;
                     nui_length:=fac[count];
                     inc(count);
                     i:= 0;
                     while i < nui_length do
                       begin
                         nui_data[i]:=fac[count];
                         inc(count);
                         inc(i)
                       end;
                     fac_len:=fac_len - (2 + nui_length)
                   end;

              $04: begin  { charging info request info }
                     charging_info_req:= 1
                   end;

              $c5: begin  { charging info recv info monetary }
                     ci_monetary:= fac[count];
                     inc(count);
                     i:=0;
                     while i < ci_monetary do
                       begin
                         ci_monetary_info[i]:=fac[count];
                         inc(count);
                         inc(i);
                       end;
                     fac_len:=fac_len - (2 + ci_monetary)
                   end;

              $c2: begin  { charging info recv info seg count }
                     ci_segcount:= fac[count];
                     inc(count);
                     i:=0;
                     while i < ci_segcount/4 do
                       begin
                         ci_segcount_info[i]:=(U32BIT(fac[count]) SHL 24);
                         inc(count);
                         ci_segcount_info[i]:=ci_segcount_info[i] and ((U32BIT(fac[count]) SHL 16));
                         inc(count);
                         ci_segcount_info[i]:=ci_segcount_info[i] and ((U32BIT(fac[count]) SHL 8));
                         inc(count);
                         ci_segcount_info[i]:=ci_segcount_info[i] and (U32BIT(fac[count]));
                         inc(count);
                         inc(i);
                       end;
                     fac_len:=fac_len - (2 + ci_segcount)
                   end;

              $c1: begin  { charging info recv info call duration }
                     ci_duration:= fac[count];
                     inc(count);
                     i:=0;
                     while i < ci_duration div 4 do
                       begin
                         ci_duration_info[i]:=(U32BIT(fac[count]) SHL 24);
                         inc(count);
                         ci_duration_info[i]:=ci_duration_info[i] and ((U32BIT(fac[count]) SHL 16));
                         inc(count);
                         ci_duration_info[i]:=ci_duration_info[i] and ((U32BIT(fac[count]) SHL 8));
                         inc(count);
                         ci_duration_info[i]:=ci_duration_info[i] and (U32BIT(fac[count]));
                         inc(count);
                         inc(i)
                       end;
                     fac_len:=fac_len - (2 + ci_duration)
                   end;

              $08: begin  { clamn }
                     clamn:= 1;
                     clamn_code:= fac[count];
                     inc(count);
                     fac_len:=fac_len - 2
                   end;

              $c3: begin  { call redir notification }
                     crn:=fac[count];
                     inc(count);
                     crn_reason:=fac[count];
                     inc(count);
                     crn_addrlen:=fac[count] and $0f;
                     inc(count);
                     i:= 0;
                     while i < crn_addrlen do
                       begin
                         crn_address[i]:=(fac[count] SHR 4);
                         crn_address[i+1]:=fac[count] and $0f;
                         inc(count);
                         inc(i,2);
                       end;
                     if (crn_addrlen and $01)=$01 then
                       begin
                         crn_address[i]:=fac[count] SHR 4;
                         inc(count);
                       end;
                     fac_len:=fac_len - (2 + crn)
                   end;

              $49: begin  { transit delay indication }
                     transit_delay:=1;
                     td_time:=(U16BIT(fac[count]) SHL 8);
                     inc(count);
                     td_time:=td_time and fac[count];
                     inc(count);
                     fac_len:=fac_len - 3;
                   end;

              $00: begin  { facility marker }
                     case fac[count] of
                       $00: begin
                              if fac[count] = $04 then
                                begin
                                  inc(count);
                                  if fac[count] = $01 then
                                    ddn_standard:=1;
                                  inc(count);
                                end
                              else
                              if fac[count] = $08 then
                                begin
                                  inc(count);
                                  ddn_precedence:=1;
                                  ddn_precedence_type:=fac[count];
                                  inc(count);
                                end;
                              fac_len:=fac_len - 4;
                            end;

                       $ff: fac_len:=0;

                       $0f: begin
                              case fac[count] of

                                $cb: begin  { calling address extension }
                                       fac_len:=fac_len - fac[count];
                                       inc(count);
                                       cdae_len:=fac[count] and $0f;
                                       inc(count);
                                       i:=0;
                                       while i < cdae_len do
                                         begin
                                           cdae_addr[i]:=(fac[count] SHR 4);
                                           cdae_addr[i+1]:=fac[count] and $0f;
                                           inc(count);
                                           inc(i,2);
                                         end;
                                       if (cdae_len and $01)=$01 then
                                         begin
                                           cdae_addr[i]:=fac[count] SHR 4;
                                           inc(count);
                                         end;
                                     end;

                                $c9: begin  { called address extension }
                                       fac_len:=fac_len-fac[count];
                                       inc(count);
                                       cgae_len:=fac[count] and $0f;
                                       inc(count);
                                       i:=0;
                                       while i < cgae_len do
                                         begin
                                           cgae_addr[i]:=fac[count] SHR 4;
                                           cgae_addr[i+1]:=fac[count] and $0f;
                                           inc(count);
                                           inc(i,2);
                                         end;
                                       if (cgae_len and $01)=$01 then
                                         begin
                                           cgae_addr[i]:=fac[count] SHR 4;
                                           inc(count);
                                         end;
                                     end;

                                $0a: begin  { qos min tput class }
                                       qos_mtc:=1;
                                       qos_mtc_calling:=(fac[count] SHR 4) and $0f;
                                       qos_mtc_called:=fac[count] and $0f;
                                       inc(count);
                                       fac_len:=fac_len - 4;
                                     end;

                                $ca: begin  { qos end_to_end transit delay }
                                       qos_etetd:=fac[count] div 2;
                                       inc(count);
                                       fac_len:=fac_len - 4;
                                       if qos_etetd = 1 then
                                         begin
                                           qos_etetd_cum:=(U16BIT(fac[count]) SHL 8);
                                           inc(count);
                                           qos_etetd_cum:=qos_etetd_cum and fac[count];
                                           inc(count);
                                           fac_len:=fac_len - 2;
                                         end;
                                       if qos_etetd = 2 then
                                         begin
                                           qos_etetd_req:=(U16BIT(fac[count]) SHL 8);
                                           inc(count);
                                           qos_etetd_req:=qos_etetd_req and fac[count];
                                           inc(count);
                                           fac_len:=fac_len - 2;
                                         end;
                                       if qos_etetd = 3 then
                                         begin
                                           qos_etetd_max:=(U16BIT(fac[count]) SHL 8);
                                           inc(count);
                                           qos_etetd_max:=qos_etetd_max and fac[count];
                                           inc(count);
                                           fac_len:=fac_len - 2;
                                         end;
                                     end;

                                $0b: begin  { expedited data neg }
                                       edn:=fac[count];
                                       inc(count);
                                       fac_len:=fac_len - 4;
                                     end

                              else fac_len:=0

                              end
                            end

                     else fac_len:=0

                     end
                   end
            else fac_len:=0

            end
          end;

      end; { DECODE_FACILITY }


{
  Encode the facility field
}

function  T_AdCOM.ENCODE_FACILITY(var FC : FACILITIES; var FAC : U8BIT_109): U8BIT;
   const  FAC_LEN : U8BIT  = 0;
          count   : U16BIT = 0;
   var    i       : U16BIT;
   begin
     with fc do
       begin

         if (fcp_packet_rx or fcp_packet_tx) <> 0 then
           begin
             fac[count]:=$42;
             inc(count);
             if fcp_packet_rx <> 0 then
               begin
                 fac[count]:=getb2(fcp_packet_rx) and $0f;
                 inc(count);
               end;
             if fcp_packet_tx <> 0 then
               begin
                 fac[count]:=getb2(fcp_packet_rx) and $0f;
                 inc(count);
               end;
             fac_len:=fac_len + 3;
           end;

         if (fcp_window_rx or fcp_window_tx) <> 0 then
           begin
             fac[count]:=$43;
             inc(count);
             if fcp_window_rx <> 0 then
               begin
                 fac[count]:=fcp_window_rx and $7f;
                 inc(count);
               end;
             if fcp_window_tx <> 0 then
               begin
                 fac[count]:=fcp_window_tx and $7f;
                 inc(count);
               end;
             fac_len:=fac_len + 3;
           end;

         if (throughput_rx and throughput_tx) <> 0 then
           begin
             fac[count]:=$02;
             inc(count);
             fac[count]:=(throughput_rx shl 4) and (throughput_tx and $0f);
             inc(fac_len,2);
           end;

         if cug_req<>0 then
           begin
             if cug_req = 1 then
               begin
                 fac[count]:=$03;
                 inc(count);
                 fac[count]:=cug_index and $00ff;
                 inc(count);
                 inc(fac_len,2);
               end;
             if cug_req = 2 then
               begin
                 fac[count]:=$47;
                 inc(count);
                 fac[count]:=cug_index and $ff00;
                 inc(count);
                 fac[count]:=cug_index and $00ff;
                 inc(count);
                 inc(fac_len,3);
               end;
           end;

         if bcug_req <> 0 then
           begin
             fac[count]:=$41;
                 inc(count);
                 fac[count]:=bcug_index and $ff00;
                 inc(count);
                 fac[count]:=bcug_index and $00ff;
                 inc(count);
                 inc(fac_len,3);
           end;

         if (reverse_charge or fast_select) <> 0 then
           begin
             fac[count]:=$01;
             inc(count);
             fac[count]:=$00;
             if reverse_charge <> 0 then
               fac[count]:=fac[count] or $01;
             if fast_select = 1 then
               fac[count]:=fac[count] or $c0;
             if fast_select = 2 then
               fac[count]:=fac[count] or $80;
             inc(count);
             inc(fac_len,2);
           end;

         if rpoa_req <> 0 then
           begin
             if rpoa_req = 1 then
               begin
                 fac[count]:=$44;
                 inc(count);
                 fac[count]:=rpoa_length and $ff00;
                 inc(count);
                 fac[count]:=rpoa_length and $00ff;
                 inc(count);
                 inc(fac_len,3);
               end;
             if rpoa_req = 2 then
               begin
                 fac[count]:=$04;
                 inc(count);
                 fac[count]:=rpoa_length;
                 i:=0;
                 while i < rpoa_length do
                   begin
                     fac[count]:=rpoa[i];
                     inc(count);
                   end;
                 fac_len:=fac_len + 2 + rpoa_length;
               end;
           end;

         if cugoas_req <> 0 then
           begin
             if cugoas_req = 1 then
               begin
                 fac[count]:=$09;
                 inc(count);
                 fac[count]:=cugoas_index and $00ff;
                 inc(count);
                 inc(fac_len,2);
               end;
             if cugoas_req = 2 then
               begin
                 fac[count]:=$48;
                 inc(count);
                 fac[count]:=cugoas_index and $ff00;
                 inc(count);
                 fac[count]:=cugoas_index and $00ff;
                 inc(count);
                 inc(fac_len,2);
               end;
           end;

         if network_user_id <> 0 then
           begin
             fac[count]:=$c6;
             inc(count);
             fac[count]:=nui_length;
             inc(count);
             i:=0;
             while i < nui_length do
               begin
                 fac[count]:=nui_data[i];
                 inc(count);
               end;
             fac_len:=fac_len + 2 + nui_length;
           end;

         if charging_info_req <> 0 then
           begin
             fac[count]:=$04;
             inc(count);
             fac[count]:=$01;
             inc(count);
             inc(fac_len,2);
           end;

         if clamn <> 0 then
           begin
             fac[count]:=$08;
             inc(count);
             fac[count]:=clamn_code;
             inc(count);
             inc(fac_len,2);
           end;

         if transit_delay <> 0 then
           begin
             fac[count]:=$49;
             inc(count);
             fac[count]:=td_time and $ff00;
             inc(count);
             fac[count]:=td_time and $00ff;
             inc(count);
             inc(fac_len,3);
           end;

         if ddn_standard <> 0 then
           begin
             fac[count]:=$00;
             inc(count);
             fac[count]:=$00;
             inc(count);
             fac[count]:=$04;
             inc(count);
             fac[count]:=$01;
             inc(count);
             inc(fac_len,4);
           end;

         if ddn_precedence <> 0 then
           begin
             fac[count]:=$00;
             inc(count);
             fac[count]:=$00;
             inc(count);
             fac[count]:=$08;
             inc(count);
             fac[count]:=ddn_precedence_type;
             inc(count);
             inc(fac_len,4);
           end;

         if cgae <> 0 then
           begin
             fac[count]:=$cb;
             inc(count);
             fac[count]:=1 + cgae_len div 2;
             inc(count);
             if (cgae_len and $01) <> 0 then
               inc(fac[count-1]);
             fac[count]:=cgae_len;
             inc(count);
             i:=0;
             while i < cgae_len do
               begin
                 fac[count]:=((cgae_addr[i] and $0f) shl 4) or
                             (cgae_addr[i+1] and $0f);
                 inc(count);
                 inc(i,2);
               end;
             if (cgae_len and $01) <> 0 then
               fac[count - 1]:=fac[count - 1] and $f0;
                  {fix up last one to be sure it's zero}
             fac_len:=fac_len + 2 + cgae_len div 2;
             if (cgae_len and $01) <> 0 then
               inc(fac_len);
           end;

         if cdae <> 0 then
           begin
             fac[count]:=$c9;
             inc(count);
             fac[count]:=1 + cdae_len div 2;
             inc(count);
             if (cdae_len and $01) <> 0 then
               inc(fac[count-1]);
             fac[count]:=cdae_len;
             inc(count);
             i:=0;
             while i < cdae_len do
               begin
                 fac[count]:=((cdae_addr[i] and $0f) shl 4) or
                             (cdae_addr[i+1] and $0f);
                 inc(count);
                 inc(i,2);
               end;
             if (cdae_len and $01) <> 0 then
               fac[count - 1]:=fac[count - 1] and $f0;
                  {fix up last one to be sure it's zero}
             fac_len:=fac_len + 2 + cdae_len div 2;
             if (cdae_len and $01) <> 0 then
               inc(fac_len);
           end;

         if qos_mtc <> 0 then
           begin
             fac[count]:=$0a;
             inc(count);
             fac[count]:=(qos_mtc_called shl 4) and (qos_mtc_calling and $0f);
             inc(count);
             inc(fac_len,2);
           end;

         if qos_etetd <> 0 then
           begin
             fac[count]:=$ca;
             inc(count);
             inc(fac_len);
             fac[count]:=qos_etetd * 2;
             inc(count);
             if qos_etetd >= 1 then
               begin
                 fac[count]:=qos_etetd_cum and $ff00;
                 inc(count);
                 fac[count]:=qos_etetd_cum and $00ff;
                 inc(count);
                 inc(fac_len,2);
               end;
             if qos_etetd >= 2 then
               begin
                 fac[count]:=qos_etetd_req and $ff00;
                 inc(count);
                 fac[count]:=qos_etetd_req and $00ff;
                 inc(count);
                 inc(fac_len,2);
               end;
             if qos_etetd = 3 then
               begin
                 fac[count]:=qos_etetd and $ff00;
                 inc(count);
                 fac[count]:=qos_etetd and $00ff;
                 inc(count);
                 inc(fac_len,2);
               end;
           end;

         if edn <> 0 then
           begin
             fac[count]:=$0b;
             inc(count);
             fac[count]:=$01;
             inc(count);
             inc(fac_len,2);
           end;

       end;
     encode_facility:= fac_len
   end;{ ENCODE_FACILITY }
*)
