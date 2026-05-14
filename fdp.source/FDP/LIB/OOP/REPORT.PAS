(*-------------------------------------------------------------------*)
(* LETVIS FDP - generovanie hlaseni 3.0                              *)
(* (c) Ales Kosice 1993,5  (ab)                                      *)
(*-------------------------------------------------------------------*)
{$I comp.h}


unit Report;


interface


     uses   TypeDef,
            DB,
            NET_def;


     const  waitSPRAVY  : int = 30;   { sec pre nepotvrdene spravy }

            {namREP     = 'R';}
            znakovREP  = 4;
            {extREP     = '.REP';}


     type   PREP = ^TREP;
            TREP = record
              kod  : TNETtyp;        { kod spravy }
              ods  : TNETadr;

              text : string;         { hlaska     }
              kluc : TDB_riadok;     { kluc uz spracovanych dat }

              dlz  : TNETdlz;        { dlzka dat pola dat }
              data : pchars;         { pole dat }

              del  : real;           { cas, kedy sa odmaze neprevzate hlasenie }
            end;

            Tproc_rep = procedure(const rep: TREP);
            Pproc_rep = ^Tproc_rep;


     type   POREP = ^TOREP;
            TOREP = object

              namREP   : string[1];
              extREP   : string[4];

              in_file  : bool;
              semaphor : bool;
              cislo    : int;
              proc     : Pproc_rep;

              constructor Init (_namREP,_extREP: string; _proc: Pproc_rep);

              function    is_file: bool;
              procedure   check;

              procedure   save_rep (_kod  : word;
                                    _ods  : TNETadr;
                                    _kluc : TDB_riadok;
                                    _text : string;
                                    _dlz  : TNETdlz;        { dlzka dat pola dat }
                                    _data : pchars          { pole dat }
                                   );
              procedure   read_rep;
            end;


implementation

uses  sets,str0,
      IO;

procedure make_REP(_kod  : word;
                   _ods  : TNETadr;
                   _kluc : TDB_riadok;
                   _text : string;
                   _dlz  : TNETdlz;        { dlzka dat pola dat }
                   _data : pchars;         { pole dat }

                   var rep : TREP
                  );
    begin
      FillChar(rep,sizeof(rep),0);
      rep.kod := _kod;
      rep.ods := _ods;
      rep.kluc:= _kluc;
      rep.text:= _text;
      if MaxAvail<=_dlz then Exit;
      rep.dlz := _dlz;
      getmem(rep.data,rep.dlz);
      move(_data^,rep.data^,rep.dlz)
    end;


procedure disp_REP(REP: PREP);
   begin
     if REP^.data<>nil then FreeMem(REP^.data,REP^.dlz);
     REP^.data:= nil;
     REP^.dlz:= 0
   end;


constructor TOREP.Init(_namREP,_extREP: string; _proc: Pproc_rep);
      begin
        namREP:= _namREP;
        extREP:= _extREP;
        proc:= _proc;
        cislo:= getint(najmladsi_subor(pathTMP,namREP+'*'+extREP),1,setPism+['.']);
        in_file:= is_file;
        semaphor:= false
      end;


function TOREP.is_file: bool;
   var   bres: bool;
   begin
     bres:= Exists(pathTMP+namREP+'*'+extREP)=0;
     if not bres then cislo:= 0;
     is_file:= bres
   end;


procedure TOREP.check;
    begin
      if (not semaphor) and in_file then
         begin
           semaphor:= true;
           read_rep;
           in_file := is_file;
           semaphor:= false
         end
    end;


procedure TOREP.save_rep (_kod  : word;
                          _ods  : TNETadr;
                          _kluc : TDB_riadok;
                          _text : string;
                          _dlz  : TNETdlz;        { dlzka dat pola dat }
                          _data : pchars          { pole dat }
                         );
    var   FN  : string;
          f   : file;
          rep : TREP;
          res : word;
    begin
      make_REP(_kod,_ods, _kluc,_text, _dlz,_data, rep);

      FN:= pathTMP + namREP+inttostr(cislo,znakovREP,0)+extREP;
      {$IFOPT R+} {$DEFINE R} {$R-} {$ENDIF}
      inc(cislo);
      {$IFDEF R} {$UNDEF R} {$ENDIF}
      vytvor_novy_subor(FN);
      Assign(f,FN);
      Rewrite(f,1);
      BlockWrite (f,rep.kod,   sizeof(rep.kod),  res);
      BlockWrite (f,rep.ods,   sizeof(rep.ods),  res);
      BlockWrite (f,rep.kluc,  sizeof(rep.kluc), res);
      BlockWrite (f,rep.text,  sizeof(rep.text), res);
      BlockWrite (f,rep.dlz,   sizeof(rep.dlz),  res);
      BlockWrite (f,rep.data^, rep.dlz, res);
      Close(f);
      in_file:= true;
      disp_REP(@rep)
    end;


procedure TOREP.read_rep;
    var   FN  : string;
          f   : file;
          rep : TREP;
          res,dres : word;
    begin
      FN:= najstarsi_subor (pathTMP,namREP+'*'+extREP);
      if FN='' then Exit;

      Assign (f,pathTMP+FN);
      Reset (f,1);
      fillchar  (rep,sizeof(rep),0);
      BlockRead (f,rep.kod, sizeof(rep.kod), res);
      if res<>0 then BlockRead (f,rep.ods,  sizeof(rep.ods),  res);
      if res<>0 then BlockRead (f,rep.kluc, sizeof(rep.kluc), res);
      if res<>0 then BlockRead (f,rep.text, sizeof(rep.text), res);
      if res<>0 then BlockRead (f,rep.dlz,  sizeof(rep.dlz),  res);
      if (res<>0) and (MaxAvail>rep.dlz) then
         begin
           GetMem(rep.data,rep.dlz);
           BlockRead (f, rep.data^,rep.dlz, dres)
         end
      else rep.dlz:= 0;
      Close (f);
      Erase (f);
      {$IFDEF ARCHIVE_PROGRAM_ERR}
       _write_err_log(rep.text+'  ('+rep.kluc+')');
      {$ENDIF}
      if (proc<>nil) then TProc_rep(proc)(rep);
      disp_REP(@rep)
    end;

end.