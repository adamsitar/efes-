{$IFDEF RTR} {$IFDEF UDP} {$DEFINE nd_UROUTER} {$ENDIF} {$ENDIF}

function E(i: int) : string;
   begin
     E:= NETcfg+' -> '+strpas(NODEs^[i].desc.name)+' : '
   end;

procedure NETcfg_read;
    var   f  : Text;
          i,k,r,_nd,p : int;
          s,o,t,a,u  : string;

          NODEthis : int;
          _X25_LANaddress, pom1, pom2 : string;
          is_RTR, is_RTI, is_RTU, is_X25, is_COM, is_IP, proNX0 : bool;

    function is_substr(subt,t: string): string;
       var   i,j : int;
             s   : string;
       begin
         is_substr:= '';
         for i:= 1 to GetStrItems(t, [',']) do
           begin
             s:= GetStr(t,i,[',']);
             if pos(subt,s)<>0 then
                begin
                  is_substr:= GetStr(s,2,['=']);
                  Exit
                end;
           end
       end;

    function get_name(s: string): string;
       begin
         s:= cut_(getstr(getstr(s,2,[';']),1,[',']));
         if (getstritems(s,[odd_NETadr])>2) {or (cut_(t)='')} then
                   RunError(NETcfg+' - '+s+' : invalid address.');
         get_name:= format_NETadr(s)
       end;

    function _ip_adr(s: string): string;
      {$IFDEF PCTCP}
       var   adrip : TIPadr;
      {$ENDIF}
       begin
         s:= getstr(s,limit(getstritems(s,[',']),2,3,0),[',']); s:= cut_(s);
        {$IFDEF PCTCP}
         adrip:= nm_prs_addr(s);
         if (neterrno<>0) or (adrip=0) then s:= '';
        {$ENDIF}
         _ip_adr:= s
       end;

    var _err: bool;

    begin
     _err:= false;

     {$IFDEF NET} if Exists(NETcfg)<>0 then RunError('Can not read '+NETcfg+'.');
     {$ELSE}      Exit;
     {$ENDIF}

     write('Reading '+NETcfg+'... ');

     NODEthis:= -1;
     is_RTR:= false; is_RTI:= false; is_RTU:= false;
     is_X25:= false; is_COM:= false; is_IP:= false;

     Assign(f,NETcfg);

     k:= 0; Reset(f);
     while not Eof(f) do
       begin
         s:= read_cfg_line(f);
         s:= uni_str(s);
         if (s<>'') and (s[1]<>';') and (pos(nd_RBRIDGE,s)=0) and (pos(nd_UROUTER,s)=0) then inc(k)
       end;

     if k>maxNODEs then MessError('To many nodes in the '+NETcfg+'. Maximum is '+inttostr(maxNODEs,1,1)+'.', true,_err);

     NODEpoc:= N(Minimum(k-1,maxNODEs));
     GetMem(NODEs,sizeof(TNETnode)*NODEpoc);
     FillChar(NODEs^,sizeof(TNETnode)*NODEpoc,0); { Dole sa nastavi NodeInit - zabezpeci inicializaciu uzla po prihlaseni sa }
     for i:= 0 to NODEpoc-1 do NODEs^[i].stat.InitEn:= true;


    { -------------------------- }
    { vyhladanie vlastnej adresy }
    { -------------------------- }

     Reset(f);
     while (not Eof(f)) do
       begin
         readln(f,o); s:= uni_str(o);
         if (o='') or (o[1]=';') or (pos(nd_THIS,s)=0) then continue;

         s:= uni_str(o);
         if (NODEthis<>-1) then RunError(NETcfg+' - another self address.')
         else begin
                NODEthis:= i;
                NODEinfo:= strpasnew(s);
                t:= cut_(getstr(o,1,[';']));
                NODEname:= strpasnew({format_NETadr(}t{)});

                t:= get_name(s);
                NETaddress      := NETadr(NETadr_wan(t),NETadr_lan(t));
                {$IFDEF IPX}
                 _X25_LANaddress := NETadr(X25address,IPXnodes[IPXnode]^.name);
                {$ELSE}
                 _X25_LANaddress := NETaddress;
                 X25address      := NETadr_wan(NETaddress);
                 LANaddress      := NETadr_lan(NETaddress);
                {$ENDIF}

                t:= cut_(getstr(s,2,[';']));
                IPaddress := cut_(getstr(t,minimum(3,getstritems(t,[','])),[',']));
                RTRaddress:= NETadr(getstr(t,1,[',']),'');

                t:= cut_(getstr(t,minimum(2,getstritems(t,[','])),[',']));
                val(t,RTRadr,r);
                {$IFDEF RTR1}
                 if (ROUTERipx<>-1) then
                    begin
                      Str(ROUTERipx,ROUTERaddress);
                      ROUTERaddress:= Copy(t,1,Length(t)-1) + ROUTERaddress;
                      if ROUTERaddress[1]<>'$' then ROUTERaddress:= '$'+ROUTERaddress;
                      val(ROUTERaddress,k,r);
                      str(k,ROUTERaddress)
                    end;
                {$ENDIF}
                {break}
              end;
       end;


    { -------------------------- }
    { nacitanie ostatnych adries }
    { -------------------------- }

     i:= 0; Reset(f);
     while (not Eof(f)) do
       begin
         readln(f,o); s:= uni_str(o);
         if (s='') or (s[1]=';') or (pos(nd_THIS,s)<>0) then continue;

        { ------------------------ }
        { BRIDGE, ROUTER, SERVER ? }
        { ------------------------ }

        { BRIDGE cez router IPX ...
        }
         if (pos(nd_RBRIDGE,s)>0) then
            begin
             {$IFDEF RTR}
              t:= getstr(s,2,[';']);
              RBRIDGEadr:= getint(t,minimum(2,getstritems(t,[','])),[',']);
              if RBRIDGEadr=0 then RunError(NETcfg+' - missing "RTR" address of BRIDGE.');
             {$IFDEF IPX}
              if ROUTERipx<0  then RunError(NETcfg+' - ROUTER not defined in '+IPXcfg+'.');
             {$ENDIF}
             {$ELSE}
              {$IFNDEF DEMO}
                MessError(NETcfg+' -> RTR protocol not allowed.',true,_err);
              {$ENDIF}
             {$ENDIF}
              continue
            end;

        { BRIDGE cez router UDP ...
        }
         if (pos(nd_UROUTER,s)>0) then
            begin
             {$IFDEF UDP}
               {$IFDEF RTR}
                 t:= cut_(getstr(s,minimum(2,getstritems(s,[','])),[',']));
                 val(t,ROUTERadr_rtr,k);
                 ROUTERadr_ip:= nm_prs_addr(_ip_adr(getstr(s,2,[';'])));
                 if (neterrno<>0) or (ROUTERadr_ip=0) then
                    RunError(E(i)+' -> invalid or missing router IP address in pctcp.ini file.');
               {$ELSE}
                {$IFNDEF DEMO}
                 MessError(NETcfg+' -> RTR protocol not allowed.',true,_err);
                {$ENDIF}
               {$ENDIF}
             {$ENDIF}
              continue
            end;

        { BRIDGE cez seriovy port ...
        }
         {$IFDEF COM}
           if (pos(nd_CBRIDGE,s)>0) then
              begin
                if CBRIDGEadr<>'' then RunError(E(i)+'another BRIDGE COM configured.')
                else CBRIDGEadr:= get_name(s)
              end;
         {$ENDIF}

        { BRIDGE vseobecne ...
        }
         if (pos(nd_BRIDGE,s)>0) then
            begin
              if BRIDGEadr<>'' then RunError(E(i)+'another BRIDGE configured.')
              else BRIDGEadr:= get_name(s);
              BRIDGEipadr:= _ip_adr(getstr(s,2,[';'])); {adrip}
            end;

         if (pos(nd_MON,s)>0) then
            if (MONaddress='') then MONaddress:= get_name(s)
            else MessError(E(i)+'another MONITORING configured.', true,_err);

         if (pos(nd_PRN,s)>0) then
            if (PRNaddress='') then PRNaddress:= get_name(s)
            else MessError(E(i)+'another PRINTER SERVER configured.', true,_err);

        {$IFDEF PRN_SERVER}
         if (pos(nd_STRIPPRN,s)>0) then
            if (STRIPPRNaddress='') then STRIPPRNaddress:= get_name(s)
            else MessError(E(i)+'another STRIP PRINTER configured.', true,_err);
        {$ENDIF}


        { ----------------------- }
        { pripojene uzly          }
        { ----------------------- }
         if (i<NODEpoc) then with NODEs^[i].desc do
            begin

            { -------- }
            { meno     }  { polozka ma len informativny charakter }
            { -------- }
              t:= getstr(o,1,[';']); t:= cut_(t);
              name:= strpasnew({format_NETadr(}t{)});

            { -------- }
            { protokol }
            { -------- }
              t:= uni_str(getstr(getstr(s,3,[';']),1,[' ']));

              {pro:= X25;} pro:= no_pro;

              if     (t=pX25) or (t=pIPX) then pro:= X25
              else if t=pBX25 then pro:= BX25
              else if t=pRTR then begin pro:= RTR; is_RTR:= true end
              else if t=pRTI then begin pro:= RTI; is_RTI:= true end
              else if t=pRTU then begin pro:= RTU; is_RTU:= true; is_IP:= true end
              else if t=pUDC then begin pro:= UDC; is_IP:= true end
              else if t=pUDX then begin pro:= UDX; is_IP:= true end
              else if t=pTCP then begin pro:= TCP; is_IP:= true end
              else if t=pCOM then
                 begin
                   pro:= COM;
                   {$IFDEF COM} if is_COM then RunError(E(i)+'another COM node configured.');
                   {$ELSE}      MessError(E(i)+'COM protocol is not allowed.', true,_err);
                   {$ENDIF}
                   is_COM:= true
                 end
              else RunError(E(i)+'not allowed protokol '+t+'.');
              {
              if pro = no_pro then ;
              }


            { ----------------------------- }
            { dlzka dat, aplikacny protokol }
            { ----------------------------- }
              t:= uni_str(getstr(getstr(s,3,[';']),2,[' ']));
              u:= uni_str(getstr(getstr(s,4,[';']),2,[' ']));
              proL:= (t=pL) or (t=pOX) or (u=pL) or (u=pOX);
              {proS:= (t=pS) or (u=pS);}
              proNX0:= (t=pNX0) or (u=pNX0);


            { -------- }
            { adresa   }
            { -------- }
              t:= getstr(s,2,[';']);

              adr:= get_name(s); {NETadr(cut_(getstr(t,1,[','])),'');}
              for k:= 0 to i-1 do if adr = NODEs^[k].desc.adr then RunError(E(i)+'another address '+t+'.');

              u:= cut_(getstr(t,minimum(2,getstritems(t,[','])),[',']));
              val(u,adrr,k);
              if (pro in [RTR,RTI,RTU]) and ((adrr=0) or (k<>0)) then RunError(E(i)+'invalid RTR adrress ('+t+').');

             {$IFDEF PCTCP}
               t:= _ip_adr(t); {cut_(getstr(t,limit(getstritems(t,[',']),2,3,0),[',']));}
               if (t<>'') or (pro in [UDC,TCP]) then
                  begin
                    if (t='') then RunError(E(i)+'missing IP address.');
                    adrip:= nm_prs_addr(t);
                    if (neterrno<>0) or (adrip=0) then RunError(E(i)+'invalid IP address or error in pctcp.ini file.')
                  end;
             {$ENDIF}

             {$IFDEF _X25}
              a:= NETadr_lan_(adr);
              if     (pro=X25)
                 and (    (not is_this_X25node(adr))
                      {$IFDEF IPX}
                      and (    isIPXname(a)=-1)
                      {$ENDIF}
                     ) then is_X25:= true;
             {$ENDIF}

              t:= getstr(s,2,[';']);
              t:= cut_(getstr(t,limit(getstritems(t,[',']),3,5,0),[',']));
              if (t<>'') and (length(t)<=3) then
                 begin
                   val(t,ai,k);
                   if k<>0 then RunError(E(i)+'invalid index address.')
                 end
              else ai:= $FF;


            { --------- }
            { typ uzla  } { uz to zacalo byt zbytocne komplikuvane }
            { --------- }

              t:= uni_str(getstr(s,5,[';']));
              if pos(nd_MASTER,t)>0 then nd:= MASTER
              else if pos(nd_SLAVE,t)>0 then nd:= SLAVE
              else nd:= no_nd;
              sw:= no_sw;

              t:= uni_str(getstr(s,4,[';']));

              if      pos(nd_RDP,t)>0 then
                         begin
                           if proNX0 then typ:= RDP0NX
                           else if proL then typ:= RDP
                           else typ:= RDP0;
                           sw:= EDD;
                           inc(nodesRDP)
                         end

              else if pos(nd_MON,t)>0 then
                      begin
                        if proNX0 then typ:= RDP0NX
                        else if proL then typ:= MON
                        else typ:= RDP0;
                        sw:= EDD;
                        NODEs^[i].stat.InitEn:= false
                      end

              else if pos(nd_MET,t)>0 then
                       if proL then typ:= MET
                       else typ:= MET


              else if pos(nd_BSERVER,t)>0 then
                 begin
                   if BACKUPnode<>-1 then MessError(E(i)+'another BACKUP SERVER configured.', true,_err);
                   BACKUPaddress:= NODEs^[i].desc.adr;
                   BACKUPnode:= i;
                   if proL then typ:= FDP else typ:= FDP0;
                   sw:= BSERVER;
                   nd:= MASTER
                 end

              else if (pos(nd_SERVER,t)>0) then
                 begin
                   if SERVERnode<>-1 then MessError(E(i)+'another SERVER configured.', true,_err);
                   SERVERaddress:= NODEs^[i].desc.adr;
                   SERVERnode:= i;
                   if proNX0 then typ:= FDP0NX
                   else if proL then typ:= FDP
                   else typ:= FDP0;
                   sw:= SERVER;
                   nd:= MASTER
                 end

              else if pos(nd_BRIDGE,t)>0 then
                 begin
                   if proL then typ:= FDP else typ:= FDP0;
                   sw:= BRIDGE
                 end

              else begin
                     if      pos(nd_FDA,t)>0 then sw:= FDA
                     else if pos(nd_OPL,t)>0 then sw:= OPL
                     else if pos(nd_IDD,t)>0 then sw:= IDD
                     else if pos(nd_EDD,t)>0 then sw:= EDD
                     else if pos(nd_LIS,t)>0 then sw:= LIS
                     else if pos(nd_FDP,t)>0 then
                             begin
                               {$IFDEF FDP_OPL} sw:= OPL
                               {$ELSE} {$IFDEF FDP_EDD} sw:= EDD
                                       {$ELSE} sw:= IDD
                                       {$ENDIF}
                               {$ENDIF}
                             end
                     else if    (pos(nd_PRN,t)>0)
                             or (pos(nd_STRIPPRN,t)>0)
                             then sw:= PRN;
                     if sw <> no_sw then
                       if proNX0 then typ:= FDP0NX
                       else if proL then typ:= FDP
                       else typ:= FDP0
                    end;


              if sw = no_sw then
                 begin
                   if t<>'' then typ:= iny_typ
                   else typ:= no_typ
                 end;

              {
               if (typ in [no_typ,iny_typ]) and (sw in set_nd_FDP+[PRN]) then
                   if proL then typ:= FDP
                   else typ:= FDP0;
              }


            { --------- }
            { info      }
            { --------- }
              inf:= strpasnew(uni_str(getstr(s,5,[';'])));
              if typ=iny_typ then inf:= StrNPCopy(inf,t+' ',false,true);


              {$IFDEF ARCHIVE_DAR};
               if strpos(inf,nd_RLI)<>nil then posRLI_ARCH:= i;
              {$ENDIF}
              if strpos(inf,ndp_NOINIT)<>nil then NODEs^[i].stat.InitEn:= false;

              if strpos(inf,nd_FDA)<>nil then
                 begin
                   FDAaddress:= adr;
                   FDAnode:= i
                 end;


            { ----------- }
            { iny TimeOut }
            { ----------- }
              t:= uni_str(getstr(s,6,[';']));
              val(is_substr(ndp_TIMEOUT,t),tmout,k);
              if tmout=0 then tmout:= tmout_ACK
              else tmout:= limit(tmout, ndp_TIMEOUT_min,ndp_TIMEOUT_max, 0)*18;
              tmout_HEARTBEAT_max:= maximum(tmout_HEARTBEAT_max,tmout);

             {sec:= strpasnew(is_substr(ndp_SECTOR ,t));}


            { ----------- }
            { FDA         }
            { ----------- }
              t:= uni_str(getstr(s,7,[';']));
              if t<>'' then
                 begin
                   indFDA:= FDAnodes;
                   inc(FDAnodes);
                   infFDA:= strpasnew(t);
                 end
              else indFDA:= -1;


            { --------- }
            { stat      }
            { --------- }
              NODEs^[i].stat.NodeInit:= true;
              NODEs^[i].stat.NextTest:= Maximum(tmout_CALL,tmout);

              inc(i)
            end
       end;

     Close(f);


    { --------------------------------------------------------------- }
    { su oznacene SERVER, RTR, BRIDGE a je modul kompilovany pre ne ? }
    { --------------------------------------------------------------- }

    { ----------------------- }
    { SERVER                  }
    { ----------------------- }

     {$IFDEF SERVER}   {$DEFINE I_am_a_server} {$ENDIF}
     {$IFDEF MASTER}   {$DEFINE I_am_a_server} {$ENDIF}
     {$IFDEF BRIDGE}   {$DEFINE I_am_a_server} {$ENDIF}
     {$IFDEF TRENAZER} {$DEFINE I_am_a_server} {$ENDIF}

     {$IFNDEF I_am_a_server}
       if SERVERnode=-1 then MessError(NETcfg+' -> SERVER is not configured.', true,_err);
     {$ENDIF}


    { ----------------------- }
    { BRIDGE, pre X25         }
    { ----------------------- }

    {$IFDEF _X25}
     if (is_X25) then

        begin
          {if (X25node=-1) and ((RBRIDGEadr=0) or (RTRadr=0)) then RunError(X25cfg+' - missing self X25 or RTR address.');}

          {$IFDEF X25}    {$DEFINE NO_BRIDGE_CFG} {$ENDIF}
          {$IFDEF BRIDGE} {$DEFINE NO_BRIDGE_CFG} {$ENDIF}
          {$IFNDEF NO_BRIDGE_CFG}
            {$IFDEF IPX}
              if not is_bridge then MessError(IPXcfg+'-> BRIDGE or RBRIDGE are not configured.',true,_err);
            {$ENDIF}
            if BRIDGEadr='' then MessError(NETcfg+'-> BRIDGE are not configured.',true,_err);
          {$ELSE}
             {$UNDEF NO_BRIDGE_CFG}
          {$ENDIF}

          if (NETaddress<>_X25_LANaddress) then
             begin
              {$IFDEF IPX}
               if (IPXnode>-1) and (X25node>-1) then RunError('NET configuration error [X25 IPX <> NET]')
              {$ENDIF}
             end
        end;
    {$ENDIF}


    { ----------------------- }
    { ROUTER                  }
    { ----------------------- }

     if (is_RTR) then
        begin
        {$IFDEF IPX}
          if ROUTERipx<>-1 then IPXnodes[ROUTERipx]^.pro:= RTR
          else RunError(NETcfg+' -> ROUTER IPX is not configured (ipx.ini).')
        {$ELSE}
         {$IFNDEF DEMO}
           MessError('ROUTER IPX is not allowed.',true,_err);
         {$ENDIF}
        {$ENDIF}
        end;

     if is_RTU then
        begin
          {$IFDEF nd_UROUTER}
            if (ROUTERadr_ip=0) then RunError(NETcfg+' -> invalid or missing ROUTER IP address.');
            if (ROUTERadr_rtr=0) then RunError(NETcfg+' -> invalid or missing ROUTER RTR address.')
          {$ELSE}
           {$IFNDEF DEMO}
            MessError(NETcfg+' -> ROUTER UDP is not allowed.',true,_err)
           {$ENDIF}
          {$ENDIF}
        end;

     if (is_RTR or is_RTI or is_RTU) and (RTRadr=0) then RunError(NETcfg+'-> invalid or missing self RTR address.');


    { ----------------------- }
    { PCTCP                   }
    { ----------------------- }

     if (is_IP) {$IFDEF PCTCP} or (IPaddress<>'') {$ENDIF} then
        begin
         {$IFDEF PCTCP}
           if (IPaddress='') then RunError(NETcfg+'-> missing self IP address.');
           IPadr:= nm_prs_addr(IPaddress);
           if (IPadr=0) or (neterrno<>0) then RunError(NETcfg+'-> invalid self IP address ('+IPaddress+').')
         {$ELSE}
         (*
           {$IFDEF DD_EXE}
             MessError(NETcfg+' -> IP protocol not enabled.', true,true)
           {$ELSE}
             RunError(NETcfg+' -> IP protocol not enabled.')
           {$ENDIF}
         *)
         {$ENDIF}
        end;


    { --------------------------------------------------------------- }
    { suhlasia adresy v users.cfg, ipx.cfg a X25.cfg ?                }
    { --------------------------------------------------------------- }

     for i:= 0 to NODEpoc-1 do with NODEs^[i].desc do
       begin
         r:= netRES_OK;
         case pro of
          {$IFDEF _X25}
           X25 : begin
                   r:= is_X25_LANadr(adr);
                  {$IFDEF BRIDGE}
                   if NETres(r) {and is_this_X25node(adr) and (NETadr_wan(adr)<>X25address)} then
                      begin
                        pom1:= NETadr_lan(adr);
                        pom2:= NETadr_wan(adr);
                        _nd:= isX25name(pom2);
                        if _nd>-1 then
                           X25nodes^.NODE^[_nd]^.netnd:= {$IFDEF IPX} isIPXname(pom1)
                                                         {$ELSE}      i
                                                         {$ENDIF}
                      end
                  {$ENDIF}
                 end;
          {$ENDIF}
           RTI : begin
                  {$IFDEF IPX}
                   s:= NETadr_lan_(adr); k:= isIPXname(s);
                   if k<>-1 then IPXnodes[k]^.pro:= RTI
                   else r:= rtrBAD_ADDR;
                   if (r=netRES_OK) and (s=IPXnodes[IPXnode]^.name) then r:= netADDR_DUPL
                  {$ELSE}
                   {$IFNDEF DEMO}
                     MessError('ipx.ini -> RTI protocol is not allowed.',true,_err)
                   {$ENDIF}
                  {$ENDIF}
                 end
         end;
         if not NETres(r) then MessError(E(i)+strpas(NETmsg(r)),true,_err)
       end;

      {$IFDEF COM}
        {if is_COM then COM_init(nil);}
      {$ENDIF}


    { ----------------------- }
    { IPX2->                  }
    { ----------------------- }
     {$IFDEF IPX} {$IFDEF SOCKET} {$IFNDEF IPX3}
       for i:= 1 to maxIPX_NODEs-1 do
           for k:= i+1 to maxIPX_NODEs-1 do
               if     IPX_adr_eq(IPXnodes[i]^.adr,IPXnodes[k]^.adr)
                  and (IPXnodes[i]^.pro<>IPXnodes[k]^.pro)
                  and (not IPX_adr_nil(IPXnodes[i]^.adr))
                   then RunError(IPXcfg+' -> Equal address for different nodes ('+inttostr(i,1,1)+', '+inttostr(k,1,1)+').');
     {$ENDIF} {$ENDIF} {$ENDIF}


     {$IFDEF PRN_SERVER}
       if (STRIPPRNaddress='') then MessError(NETcfg+' -> STRIP PRINTER is not configured.', true,_err);
     {$ENDIF}

    { vlastne adresa ? }
      if NODEthis=-1 then RunError(NETcfg+' -> missing self address.');

      is_PRN_NET:= PRNaddress<>'';

      if _err then writeln;
      writeln('Done.')
    end;

{$UNDEF nd_UROUTER}


procedure NETcfg_done;
    var   i : int;
    begin
      for i:= 0 to NODEpoc-1 do with NODEs^[i].desc do
        begin
          strdispose(name);
          strdispose(inf);
          strdispose(infFDA);
        end;
      FreeMem(NODEs,sizeof(TNETnode)*NODEpoc);
      StrDispose(NODEname);
      StrDispose(NODEinfo);
    end;
