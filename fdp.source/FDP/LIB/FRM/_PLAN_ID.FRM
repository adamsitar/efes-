const  Form_idn: TForm =
            ( item : '         1'; title: 'Index';
              lst : @fnIDN; pos: 0;
              legal: @setABC; skip : @setNil;
              dx:0 ; dy: 0; font:0; color: 0
            );


procedure idn_init_list(ind: PindPLAN); far;
    var   t : text;
          s : string;
          i : int;
    begin
      Assign(t,fnIDN.fn);
      Rewrite(t);
      with ind^.iPLAN^ do for i:= 0 to top do writeln(t, get_id(ap^[i]));
      Close(t)
    end;

procedure idn_done_list(ind: PindPLAN); far;
    begin
      DelFile(strpas(fnIDN.fn))
    end;


function idn_check(form: PSingleForm; ind: PindPLAN): bool; far;
   var   b : bool;
         t : string;
         E : TEvent;
   begin
     idn_check:= false;
     t:= cs_ascii_str(cut_(StrPas(Form_idn.item)));
     if t='' then
        begin
          SetCommand (E,nil,cmList);
          form^.HandleEvent(E);
          t:= cs_ascii_str(cut_(StrPas(Form_idn.item)));
          if t='' then Exit
        end;
     ind^.ind:= ind^.iPLAN^.find_id(t);
     if ind^.ind=-1 then
        begin
          t:= msgDATA +' '+t+' '+ msgNOT_FOUND+#0;
          form^.Error(24,@t[1])
        end;
     idn_check:= ind^.ind<>-1
   end;


function formular_idn(iPLAN: pointer; _tit: string): int;
   var   form : PSingleForm;
         E    : TEvent;
         ind  : TindPLAN;
   const f: Tcentr = (x: initX; y: initY; m: 1);
   begin
     ind.iPLAN:= iPLAN; ind.ind:= -1;
     form:= New(PSingleForm,Init(nil, f.x,f.y, f.m,
                kbEnter,cmOK, _tit, @Form_idn,
                clGR2,cfText, 0,
                @ind, nil,@idn_check,nil, nil, false)
               );
     form^.init_list  := @idn_init_list;
     form^.clear_list := true;
     form^.sort_list  := true;
     form^.done_list  := @idn_done_list;
     form^.Run(E);
     Dispose(form,Done);
     formular_idn:= ind.ind
   end;


function idn_check_i(form: PSingleForm; ind: PindPLAN): bool; far;
   var   t : string;
   begin
     t:= cs_ascii_str(cut_(form^._it(0)));
     ind^.ind:= ind^.iPLAN^.find_id(t);
     idn_check_i:= true
   end;

function formular_idn_i(iPLAN: pointer; _tit: string; var i: int): bool;
   var   form : PSingleForm;
         E    : TEvent;
         ind  : TindPLAN;
   const f: Tcentr = (x: initX; y: initY; m: 1);
   begin
     ind.iPLAN:= iPLAN; ind.ind:= -1;
     form:= New(PSingleForm,Init(nil, f.x,f.y, f.m,
                kbEnter,cmOK, _tit, @Form_idn,
                clGR2,cfText, 0,
                @ind, nil,@idn_check_i,nil, nil, false)
               );
     form^.init_list  := @idn_init_list;
     form^.clear_list := true;
     form^.sort_list  := true;
     form^.done_list  := @idn_done_list;
     form^.Run(E);
     formular_idn_i:= form^.corr_res;
     i:= ind.ind;
     Dispose(form,Done)
   end;


{function idn_s_check(form: PSingleForm; idn: pstring): bool; far;
   begin
     idn^:= cs_ascii_str(cut_(form^._it(0)));
     idn_s_check:= true
   end;

function formular_idn_s(iPLAN: pointer; _tit: string; var idn : string): bool;
   var   form : PSingleForm;
         E    : TEvent;
   const f: Tcentr = (x: initX; y: initY; m: 1);
   begin
     form:= New(PSingleForm,Init(nil, f.x,f.y, f.m,
                kbEnter,cmOK, _tit, @Form_IDN,
                clGR2,cfText, 0,
                @idn, nil,@idn_s_check,nil, nil, false)
               );
     form^.init_list  := @IDN_init_list;
     form^.clear_list := true;
     form^.sort_list  := true;
     form^.done_list  := @IDN_done_list;
     form^.Run(E);
     formular_idn_s:= form^.corr_res;
     Dispose(form,Done);
   end;
}
