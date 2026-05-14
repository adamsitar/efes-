(*-------------------------------------------------------------------*)
(* LETVIS FDP - ASTA driver...                                       *)
(* (c) Ales Kosice 1993  (ab)                                        *)
(*-------------------------------------------------------------------*)
{$I comp.h}


unit _ASTA;


interface


     uses   TypeDef, Arrays,
            {$I unit_gr.h},
            {$I unit_net.h},
            _ASTA_def;


     const  writeln_ASTA           : bool = true;
            writeln_ASTA_utc       : bool = true;
            archive_ASTA           : bool = true;

            cl_ASTA                : byte = clGR8;
            cl_ASTA_err            : byte = red;

            process_ASTA_CPL       : bool = false;
            supervisor_FDP         : TNETadr = '';


    {$IFDEF ASTA_PRN}
     procedure check_ASTA_PRN; far;

     {$IFDEF DD_EXE}
        procedure asta_prn_test;
     {$ENDIF}

    {$ENDIF}


    {$IFDEF ASTA_FDP}
     procedure check_ASTA_FDP; far;

     {$IFDEF DD_EXE}
       procedure asta_fdp_test;
       procedure asta_fdp_test_send;
     {$ENDIF}

    {$ENDIF}



implementation


uses COMs, BIOS, IO,
     str0, utime, sets, keyb,
     App,
     Body, Bod_def, Vypocty, Archiv,
     _L4_def, _FDP_def, _FPL_def, _FPL,
     _FPL4
     {$IFDEF FPL0}, _FPLc, _FPLm    {$ENDIF}
     {$IFDEF CONNECT_TO_OPL_EXT},  _OPL {$ENDIF}
     {$IFDEF SPR}, _SPR {$ENDIF}
     ;


const Skip : Set of byte = [];

{$IFDEF FPL0}
 procedure _add_cFPL(FPL: PDcFPL);
     begin
       save_cFPL(FPL);
       p_add_FPLc(FPL);
       distribute_cFPL(FPL,[],[SLAVE]);
       {$IFDEF CONNECT_TO_OPL_EXT}
         if DEV_OPL<>nil then DEV_OPL^.send_ESTc(FPL^);
       {$ENDIF}
     end;
{$ENDIF}

procedure _ASTA_err(idn,err: string);
    var   i   : int;
          e   : string;
         {$IFDEF SPR}
          SPR : DSPR;
         {$ENDIF}
    begin
      e:= 'ASTA DECODE ERROR ... '+idn+' - '+err;
      if (MainApp<>nil) then MainApp^.writeln(e, cl_ASTA_err,arch_MESS,writeln_ASTA_utc);
     {$IFDEF SPR}
      for i:= 0 to NODEpoc-1 do if strpos(NODEs^[i].desc.inf,nd_FDA)<>nil then
        begin
          {init_SPR(@SPR,NODEs^[i].desc.adr);
          SPR.text:= StrPasNew(' Nespracovany strip...');
          SPR.text:= StrPasNew('----------------------');
          SPR.text:= StrPasNew(' - '+idn);
          SPR.text:= StrPasNew(' - '+err);
          SPR.text:= StrPasNew('               FDP server');
          send_SPR(@SPR, SPR.adr, false);
          disp_SPR(@SPR)}
        end;
     {$ENDIF}
    end;


{$IFDEF ASTA_PRN}

  {$IFDEF FPL0}
   {$I ASTA_PRN.inc}
  {$ENDIF}

  procedure check_ASTA_PRN;
      const semaphor : bool = false;
      var   pkt : PASTA_PRNpacket;
           {$IFDEF FPL0}
            FPL : PDcFPL;
           {$ENDIF}
            err : string;
      begin
        if (not power_ASTA) then Exit;

       {$IFDEF FPL0}
        if (ASTA_PRN_buff^.is) and (not semaphor) then
           begin
             semaphor:= true;
             New(pkt);
             if ASTA_PRN_buff^.read(pkt) then
                begin
                  if archive_ASTA then
                     archivuj_data(path_ASTA,get_ARCHfn(0)+'.'+extASTA_PRN,
                                   @pkt^.b,pkt^.t, arch_PKT_REC,true,false
                                  );
                  if (writeln_ASTA) and (MainApp<>nil) then
                     MainApp^.writeln_(@pkt^.b,pkt^.t, cl_ASTA, arch_PKT_REC,writeln_ASTA_utc,false);
                  New(FPL); fillchar(FPL^,sizeof(FPL^),0);
                  if decode_ASTA_PRN(pkt^, FPL^, err) then
                     begin
                       format_cFPL(FPL);
                       if (cut_(FPL^.idn)<>'') then _add_cFPL(FPL)
                     end
                  else _ASTA_err(FPL^.idn,err);
                  Dispose(FPL)
                end;
             Dispose(pkt);
             semaphor:= false
           end
       {$ENDIF}
      end;


  {$IFDEF DD_EXE}
   procedure asta_prn_test;
      var    f : file of char;
             A : TASTA_PRNpacket;
      begin
        fillchar(A,sizeof(A),0);
        Assign(f,{'test.asp'} paramstr(1));
        Reset(f);
        while (not eof(f)) and (A.t<max__ASTA_PRNmess) do
          begin
            read(f,A.b[A.t]);
            inc(A.t)
          end;
        Close(f);
        ASTA_PRN_buff^.save(@A)
      end;
  {$ENDIF}


{$ENDIF}


{$IFDEF ASTA_FDP}

  {$IFDEF FPL0}
   {$I ASTA_FDP.inc}
  {$ENDIF}

  procedure check_ASTA_FDP;
      const semaphor: bool = false;
      var   pkt : PASTA_FDPpacket;
           {$IFDEF FPL0}
            FPL : PDcFPL;
           {$ENDIF}
            ind : int;
            err : string;
      begin
        if (not power_ASTA) then Exit;

       {$IFDEF FPL0}
        if (ASTA_FDP_buff^.is) and (not semaphor) then
           begin
             semaphor:= true;
             New(pkt);
             if ASTA_FDP_buff^.read(pkt) then
                begin
                  if archive_ASTA then
                     archivuj_data(path_ASTA,get_ARCHfn(0)+'.'+extASTA_FPL, @pkt^.b,pkt^.t, arch_PKT_REC,true,false);
                  if (writeln_ASTA) and (MainApp<>nil) then
                      MainApp^.writeln_(@pkt^.b,pkt^.t, cl_ASTA, arch_PKT_REC,writeln_ASTA_utc,false);
                  New(FPL); fillchar(FPL^,sizeof(FPL^),0);
                  err:= '';
                  if decode_ASTA_FDP(pkt^, FPL^) then
                     begin
                       format_cFPL(FPL);
                       if cFPL<>nil then ind:= cFPL^.find_id(FPL^.idn)
                       else ind:= -1;
                       if     (cut_(FPL^.idn)<>'')
                         {$IFDEF ASTA_PRN}
                          and (   (ind=-1)       )
                         {$ENDIF}
                          and (   (FPL^.stt<>fpl_CPL)
                               or (    (FPL^.stt=fpl_CPL)
                                   and (process_ASTA_CPL)
                                   and ((ind=-1) or ((ind<>-1) and (PDcFPL(cFPL^.ap^[ind])^.stt<>fpl_EST)))
                                  )
                              )
                          then _add_cFPL(FPL)
                     end
                  else _ASTA_err(FPL^.idn,err);
                  Dispose(FPL)
                end;
             Dispose(pkt);
             semaphor:= false
           end
        {$ENDIF}
      end;


  {$IFDEF DD_EXE}
    procedure asta_fdp_test;
       var    f   : text;
              A,P : TASTA_FDPpacket;
              s   : string;
              i   : int;
       const  cit : int = 0;
       begin
         fillchar(A,sizeof(A),0);
         Assign(f,'test.asf');
         Reset(f);
         {
         while (not eof(f)) do
           begin
           end;
         }
         i:= 0;
         while (i<=cit) and (not Eof(f)) do
           begin
             readln(f,s);
             inc(i)
           end;
         if (not Eof(f)) then
            begin
              inc(cit);
              i:= 1; while (i<=length(s)) and (s[i]<>'') do inc(i);
              if i<=length(s) then
                 begin
                   P.t:= length(s)-i+1;
                   Move(s[i],P.b[0],P.t);
                   ASTA_FDP_buff^.save(@P)
                 end;
            end;
         Close(f)
       end;

    procedure asta_fdp_test_send;
       var    s: string;
       begin
         s:=  '(ESTBR/MI518-SAS779/6256-MD80-EKCH-ODNEM/1400F330-N0440F330-LHBP-ODNEM/330/1400'
             +'BERVA/170/1404 SWCN/170/1405 NIT/170/1407 RUTOL/170/1411 OKI/170/1413)Vi';
         {sendcomi(comASTA_FDP,s);}
       end;
  {$ENDIF}

{$ENDIF}


var SaveExit: pointer;

procedure done_buff; far;
    begin
      {$IFDEF ASTA_PRN}
       if ASTA_PRN_buff<>nil then dispose(ASTA_PRN_buff,Done);
      {$ENDIF}
      {$IFDEF ASTA_FDP}
       if ASTA_FDP_buff<>nil then dispose(ASTA_FDP_buff,Done);
      {$ENDIF}
      ExitProc:= SaveExit
    end;

procedure init_buff;
   begin
     {$IFDEF ASTA_PRN}
       fillchar(b_PRN,sizeof(b_PRN),0);
       ASTA_PRN_buff:= New(PBuffer,Init(ASTA_PRN_buff_size,sizeof(TASTA_PRNpacket), false));
     {$ENDIF}
     {$IFDEF ASTA_FDP}
       fillchar(b_FDP,sizeof(b_FDP),0);
       ASTA_FDP_buff:= New(PBuffer,Init(ASTA_FDP_buff_size,sizeof(TASTA_FDPpacket), false));
     {$ENDIF}
     SaveExit:= ExitProc;
     ExitProc:= @done_buff
   end;

begin
  init_buff
end.
