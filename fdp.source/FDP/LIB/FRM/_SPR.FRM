 const  size_SPRadr {: int}  = 1 + max_SPR_a_hi;
        form_SPRadr : PForms = nil;


 type   PSPR_form = ^OSPR_form;
        OSPR_form = object(OTLG_form)

          SPR : DSPR;

          constructor Init(_SPR: PSPR;
                           _tit : string; _head: string;
                           _lines: int;
                           var f : Tcentr
                          );
          destructor  Done; virtual;

          procedure  draw_buttons; virtual;

          procedure  init_tlg_adr; virtual;
          procedure  init_tlg_data; virtual;

          function   _read_tlg_adr(size_adr: int; var _adr: string; var _res: string; var _ires: int): string; virtual;
          function   _read_formular_data (var res: string; var ires: int): string; virtual;

          function   check_formular_data(var res: string; var ires: int): string; virtual;
          function   send_formular(var res: string; var ires: int): string; virtual;
        end;


 procedure SPR_init_adr_list(SPR: PSPR); far; forward;
 procedure SPR_done_adr_list(SPR: PSPR); far; forward;


 constructor OSPR_form.Init(_SPR: PSPR;
                            _tit : string; _head: string;
                            _lines: int;
                            var f : Tcentr
                           );
       var   i: int;
       begin
         fillchar(SPR,sizeof(SPR),0);
         if (_SPR<>nil) {and (not _arch)} then new_SPR(_SPR,@SPR);
         inherited Init(_tit, f, _head, kbNL,
                        form_SPRadr,size_SPRadr,
                        form_TLGaftn,minimum(_lines,size_TLGaftn), 0,
                        @SPR, nil,nil{@check},nil,nil, 10,nil
                       );

         first_pos:= i_tlg_adr;
         for i:= 0 to i_form_ADR-1 do itemd^[i].legal:= @set_SPRadr;
         init_list:= @SPR_init_adr_list;
         done_list:= @SPR_done_adr_list;
         upcas:= false;

         hlpXXX:= hlp_SPR
       end;


 destructor OSPR_form.Done;
      begin
        disp_SPR(@SPR);
        inherited Done;
      end;

 procedure OSPR_form.draw_buttons;
     begin
       inherited draw_buttons;
       upcas:= ind < o_f
     end;


 procedure SPR_init_adr_list(SPR: PSPR);
     var   t : text;
           i : int;
           ba,bo,bl : bool;
     begin
       Assign(t,fnSPR.fn);
       Rewrite(t);
       for i:= 0 to NODEpoc-1 do with NODEs^[i].desc do
         begin
           ba:= ba or (strpos(NODEs^[i].desc.inf,inf_SPR)<>nil);
           bl:= bl or (strpos(NODEs^[i].desc.inf,nd_AP)<>nil);
           bo:= bl or (strpos(NODEs^[i].desc.inf,nd_MACC)<>nil);
        end;

       if ba then writeln(t,SPRadr_all+tit_SPRadr_all);
       {$IFDEF LZ}
        if bl then writeln(t,SPRadr_let+tit_SPRadr_let);
        if bo then writeln(t,SPRadr_opl+tit_SPRadr_opl);
       {$ENDIF}
       if ba or bo or bl then writeln(t,'');

       for i:= 0 to NODEpoc-1 do with NODEs^[i].desc do
           if strpos(inf,inf_SPR)<>nil then
              if name<>nil then writeln(t,strpas(name))
              else writeln(t,adr);
       Close(t)
     end;

 procedure SPR_done_adr_list(SPR: PSPR);
     begin
       DelFile(strpas(fnSPR.fn))
     end;


 procedure OSPR_form.init_tlg_adr;
     var   i: int;
     begin
       _in(i_tlg_prty,tlgSS);
       itemd^[i_tlg_prty].legal:= @setNil;
       for i:= i_tlg_adr to i_tlg_adr+i_tlg_adrs-1 do
           begin
             itemd^[i].lst:= @fnSPR;
             itemd^[i].legal:= @set_SPRadr
           end;
       if (SPR.ods<>'') {and (SPR.adr<>nil)} then init_pole(i_tlg_adr,SPR.adr)
       {else inherited init_tlg_adr}
     end;

  procedure OSPR_form.init_tlg_data;
     begin
       if (SPR.ods<>'') {and (SPR.etxt<>nil)} then init_pole(o_f,SPR.text)
       else inherited init_tlg_data
     end;


 function OSPR_form._read_tlg_adr (size_adr: int; var _adr: string; var _res: string; var _ires: int): string;
    var   adri  : string;
          i,p,n : int;
          a     : pchar;
    begin
      _read_tlg_adr:= '';

      strdispose(SPR.adr);
      read_pole(i_tlg_adr,SPR.adr);
      _adr:= strpas(SPR.adr);
      a:= nil;

     { Kontrola adries i s konverziou...
     } p:= GetPStrItems(SPR.adr,set_SPRadr_odd+setNL+setNL_);
       if (p=0) then l4_err(a_TLG, '', i_tlg_adr{i_tlg_adr},3, _res)
       else begin
              i:= 1; while (i<=p) and (_res='') do
                begin
                  adri:= _adri(@SPR,i);
                  if not _adri_nd (adri, n) then
                     begin
                       _ires:= l4_err(a_TLG, adri, {_ires}i_tlg_adr,6, _res);
                       break
                     end;
                  inc(i);
                  {if i<=p then adri:= adri+SPRadr_odd+icao_NXIT;
                  a:= StrNPCopy (a,adri,true,true);}
                end
            end;
       {strdispose(SPR.adr);}
       {SPR.adr:= a;}

      _read_tlg_adr:= _res
    end;


 function OSPR_form._read_formular_data(var res: string; var ires: int): string;
    var   a,s,t : string; p: char;
          c,i   : int;
          d     : pchars;
    begin
      if data<>nil then StrDispose(data);
      res:= '';
      read_pole(o_f,data);
      _read_formular_data:= res
    end;


 function OSPR_form.check_formular_data(var res: string; var ires: int): string;
    label X;
    begin
      check_formular_data:= '';

      check_formular_data:= inherited check_formular_data(res,ires);
      if res<>'' then Exit;

      strdispose(SPR.text);
      SPR.text:= strnew(data);
      if SPR.text=nil then
         begin
           ires:= l4_err(a_TLG, '', size_SPRadr,9, res);
           goto X
         end;

      SPR.ods:= NETaddress;

      if i_form_XXX=size_TLGaftn then SPR.typ:= hd_TLG
      else SPR.typ:= hd_MSG;
      SPR.prty:= prty;

      datum_init (SPR.dap, day,month,year, hour,min,sec);

      X: check_formular_data:= res
    end;


 function OSPR_form.send_formular(var res: string; var ires: int): string;
    begin
      send_formular:= '';
      if SPR.text=nil then Exit;
      _odosli_SPR(@SPR);
      send_formular:= ''
    end;


 function  _formular_SPR(SPRi: PSPR; _tit,_head: string; _lines: int): bool;
    const  f    : Tcentr = (x: initX; y: initY; m: 1);
    var    Ev   : TEvent;
           form : PSPR_form;
    begin
      form:= New(PSPR_form,Init(SPRi, _tit,_head, _lines, f));
      form^.RunLocalFunc(Ev,FDPFormLocalMenu);
      _formular_SPR:= form^.corr_res;
      Dispose(form,Done)
    end;

 function  formular_SPR(SPRi: PSPR): bool;
    begin
      formular_SPR:= _formular_SPR(SPRi, tit_MSG,hd_MSG, size_SPRmsg)
    end;
