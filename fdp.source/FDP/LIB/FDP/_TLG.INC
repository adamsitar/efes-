 procedure init_tlg_adr (head: string; form: PAForm; ind_head: int);
     var   prty,adr,s: string;
           _ind, i,j,l: int;
     begin
       get_msg_adr (head, prty,adr);
       if (form<>nil) and (form^.itemd<>nil) then with form^ do
          begin
            _in(ind_head,prty);
            adr:= adr+NULL;
            init_pole(ind_head+1, @adr[1])
          end
     end;

 function read_tlg_adr(form: PAForm; size_adr: int; var prty,adr: string; var res: string; var ires: int): string;
    var   s,a     : string;
          i,j,al  : int;
          ni      : bool;        { nova polozka }

    label X;
    begin
      prty:= ''; adr:= '';
      read_tlg_adr:= 'There is no adrress in the telegram.';
      if form=nil then Exit;
      res:= '';

     { a) priorita
     } prty:= cut_(form^._it(0));
       if is_mtkprty(prty+icao_NXIT+icao_ARR)='' then ires:= l4_err(a_TLG,prty, 0,2, res);
       if prty='' then ires:= l4_err(a_TLG,'',0,1, res);
       if res<>'' then goto X;

     { b) nacitanie adries
     } al:= 0;
       for i:= 1 to size_adr-1 do
           begin
             ires:= _check_mtk_adr (cut_(form^._it(i)), adr,al,false,0,res);
             if ires<>-1 then break;
              {s:= cut_(form^._it(i));
             if (s<>'') then
                for j:= 1 to getstritems(s,[icao_NXIT]) do
                  begin
                    a:= getstr(s,j,[icao_NXIT]);
                    if (length(a)<_MTK_ADR_lo) or (length(a)>_MTK_ADR_hi) then
                       begin
                         ires:= l4_err(a_TLG,a, 1,4, res);
                         goto X
                       end;
                    if a<>'' then
                       begin
                         if adr<>'' then a:= icao_NXIT+a;
                         adr:= adr+a;
                       end;
                    inc(al,length(a))
                  end;}
           end;
       {if al=0 then ires:= l4_err(a_TLG,'',1,3, res);
       {if al>_MTK_ADR_ar then l4_err(a_TLG,'',5,5, res);}
       if res='' then ires:= _check_mtk_adr ('', adr,al,true,0,res);
       if ires<>-1 then ires:= i_tlg_adr;

       X: read_tlg_adr:= res
    end;


 procedure image_TLGadr(x0,y0,x1,y1: int);
     begin
       BGIgraph.button(x0,y0,x1,y1, clBUTTON_COLOR+1, btSmall, btOFF);
       on_off(x0+4,y0+4,x1-5,y0+dy_TLGadr, clBUTTON_COLOR+clBUTTON_DARK,clBUTTON_COLOR+clBUTTON_LIGHT, btSmall, btOFF);
       on_off(x0+4,y0+4,x1-5,y0+dy_TLGadr, clBUTTON_COLOR+clBUTTON_DARK,clBUTTON_COLOR+clBUTTON_LIGHT, btSmall, btON);
     end;


 function _lat_TLG(s: string): string;
    begin
      if RUSSIAN_TLG then _lat_TLG:= s else _lat_TLG:= mtks_rus_to_lat(s)
    end;
