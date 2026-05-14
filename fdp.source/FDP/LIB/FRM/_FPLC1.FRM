{
‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹
€                                                          €
€ externe procedury pre TcFPLform                          €
€‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹€
}

function cFPLbod (ind: int): int;
   begin
     cFPLbod:= ind - ((ind-i_15c_FDR) mod 3)
   end;

procedure cFPL_image(x0,y0,x1,y1: int);
    var   i, y3,y4, bg: int;
    begin
      y3:= y0+3; y4:= y0+39; bg:= clBUTTON_COLOR+1;
      BGIgraph.button(x0,y0,x1,y1, bg, btSmall, btOFF);
      _linev (x0+157,y3,y4,bg);
      _linev (x0+295,y3,y4,bg);
      _lineh (x0+5,x1-5,y0+42,bg);
      for i:= 1 to max_bod_FPLC-1 do _linev(x0+3+50*i,y0+48,y1-5,bg);
    end;


procedure cFPL_init_data(form: PcFPLform; FPL: PDcFPL);
    var   s : string;
          i,r : int;
    begin
      if (FPL^.idn<>'') then clear_form(form^.itemd,i_15c_FDR,nil);

      if (form<>nil) and (FPL<>nil) and (FPL^.idn<>'') then with FPL^ do
         begin
           form^._in(i_7_FDR,idn);
           form^._in(i_18_FDR,inf);

           form^._in(i_8a_FDR,_8a);
           form^._in(i_8b_FDR,_8b);

           if delchar(typ,[icao_NXT,icao_NXIT])<>'' then form^._in(i_9_FDR,typ);

           form^._in(i_7b_FDR,ssr);
           form^._in(i_7b0_FDR,ssr0);
         end
    end;


procedure cFPL_init_route(form: PcFPLform; FPL: PDcFPL);
    var   s : string;
          v : word; v_: char;
          i,r : int;
          bres1,bres2 : bool;
    begin
      if (FPL^.idn='') then Exit;
      with FPL^ do
        begin
          form^._in(i_15a_FDR_,rych_);
          if rych<>0 then form^._in(i_15a_FDR,delchar(code_l4_rych (rych,rych_),setRych_));

          bres1:= (start.h<>0) or (start.m<>0) or (prist.h<>0) or (prist.m<>0);
          form^._in(i_13a_FDR,start.kod);
          if bres1 then
             begin
               form^._in(i_13b_FDR,TimeToStr(start.h,start.m, ':'));
               bres2:= (start_.h<>start.h) or (start_.m<>start.m);
               if bres2 then form^._in(i_13c_FDR,TimeToStr(start_.h,start_.m, ':'))
               else clear_form(@form^.itemd^[i_13c_FDR],1,nil)
             end
          else clear_form(@form^.itemd^[i_13b_FDR],2,nil);

          form^._in(i_16a_FDR,prist.kod);
          bres1:= bres1 and ((start.h<>prist.h) or (start.m<>prist.m));
          if bres1 then form^._in(i_16b_FDR,TimeToStr(prist.h,prist.m, ':'))
          else clear_form(@form^.itemd^[i_16b_FDR],1,nil);

          if vys<>0  then form^._in(i_15b_FDR,alt_to_str(vys,vysOB,' ',false,false))
          else clear_form(@form^.itemd^[i_15b_FDR],1,nil);
          if vys1<>0 then form^._in(i_14c_FDR,alt_to_str(vys1,vysOB,vys1_a,false,false))
          else clear_form(@form^.itemd^[i_14c_FDR],1,nil);

          {$IFDEF FPLC_ION}
           if vysO<>0 then form^._in(i_EXIo,alt_to_str(vysO,vysOB,vysO_a,false,false))
           else clear_form(@form^.itemd^[i_EXIo],1,nil);
           if vysH<>0  then form^._in(i_EXIh,alt_to_str(vysH,vysOB,' ',false,false))
           else clear_form(@form^.itemd^[i_EXIh],1,nil);
          {$ENDIF}

          bres1:= (start.h<>0) or (start.m<>0) or (prist.h<>0) or (prist.m<>0);
          form^._in(i_16a_FDR,prist.kod);
          if bres1 then form^._in(i_16b_FDR,TimeToStr(prist.h,prist.m, ':'))
          else clear_form(@form^.itemd^[i_16b_FDR],1,nil);

          clear_form(@form^.itemd^[i_15c_FDR], form^.items-i_15c_FDR-2, nil);
          v:= vys; v_:= ' '{vys_a};
          for i:= 0 to max_bod_FPLC-1 do with trat[i] do
              begin
                if cut_(kod)='' then break;
                r:= 3*i+i_15c_FDR;
                form^._in(r,kod);
                inc(r);
                if (kod<>'') and (h<24) then s:= timetostr(h,m,':') else s:= '  :  ';
                form^._in(r,s);
                inc(r);
                if (kod<>'') and ((v<>vys) or (v_<>vysab)) then
                   begin
                     s:= alt_to_str(vys,vysOB,' ',false,false);
                     if s[1]=altS then s:= copy(s,2,length(s)-1);
                     s:= s + vysab
                   end
                else s:= ' ';
                form^._in(r,s);
                v:= vys; v_:= vysab
              end
        end
    end;

procedure cFPL_init(form: PcFPLform; FPL: PDcFPL);
    begin
      if (FPL^.idn<>'') then clear_form(form^.itemd,form^.items,nil);
      cFPL_init_data (form, FPL);
      cFPL_init_route(form, FPL)
    end;


procedure cFPL_send(FPL: PDcFPL); far;
    begin
      {send_cFPL(FPL, SERVERaddress,false);}
      distribute_cFPL(FPL,[],[])
     {$IFDEF DEBUG} {$IFDEF CONNECT_TO_OPL_EXT};
        {if DEV_OPL<>nil then DEV_OPL^.send_cFPL_EST(FPL^);}
     {$ENDIF} {$ENDIF}
    end;
