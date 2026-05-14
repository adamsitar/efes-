constructor TFDP_AForm0.Init(_Owner: PGroup;  var _x,_y, _mode: int;
                             _kbHot: char; _cmXXXX: word; _title: string;
                             _itemd: PForms; _items: byte;
                             _bg,_text, _abg,_atext: byte;

                             _dole: byte;      { kam spinace umiestnit }
                             _tit : byte;              { vypisovat title pre item ked, tak a ako ? }
                             _inc_dx,_inc_dy : int;    { len ak title = 1 (bude sa vypisovat dole) }
                             _init_buttons   : pointer;

                             _dx_h, _dy_h: int;
                             _htext, _hbg: byte;

                             _adr_var  : pointer;
                             _adr_data : pointer;      { data pre kontrolu, ci dany plan este neexistuje }

                             _rec      : Pplan_rec;

                             _novy : bool;

                             _data_size : word;
                             _code_key  : PSFunc_p;
                             _read_orig : PIFunc_sp;

                             _is_data,
                             _chg_data  : PPLAN_zmeneny;

                             _init_form, _check_func, _done_form: pointer;

                             _image_form: pointer;
                             _handle_event: pointer;

                             _hlpXXX : Pchar;

                             _copy,_clear,_pole_en: bool
                            );
      begin

       { Nacitanie vzoru pre kontrolu duplicity spracovania
         na <> pracoviskach
       }
        data_size:= _data_size;
        if (not _novy) and (_adr_data<>nil) and (_chg_data<>nil) and (_code_key<>nil) and (_read_orig<>nil) then
           begin
             getmem(adr_orig,data_size);
             fillchar(adr_orig^,data_size,0);
             if TIFunc_sp(_read_orig)(TSFunc_p(_code_key)(_adr_data),adr_orig)<0 then
                begin
                  freemem(adr_orig,data_size);
                  adr_orig:= nil
                end;
           end
        else adr_orig:= nil;

        novy:= _novy or (_adr_data=nil);
        adr_data:= _adr_data;
        p_is_data:= _is_data;
        p_chg_data:= _chg_data;

        is_rqst       := false;
        p_handle_rqst := nil;
        rqst_res      := _;

        rec:= _rec;

        inherited Init(_Owner, _x,_y, _mode,
                       _kbHot, _cmXXXX, _title,
                       _itemd, _items,
                       _bg,_text, _abg,_atext,
                       _dole, _tit, _inc_dx,_inc_dy,
                       _init_buttons,
                       _dx_h, _dy_h,
                       _htext, _hbg,
                       _adr_var,
                       _init_form,_check_func,_done_form,
                       _image_form,
                       _handle_event,
                       _copy,_clear, _pole_en,
                       _hlpXXX
                      );

        win^.btTitle^.cmXXXX:= cmDefault;
        copy_back := true;

        beeping  := false;
        PBFunc   := nil;
        beep_par := nil;
      end;


destructor TFDP_AForm0.Done;
     begin
       if (adr_orig<>nil) then
          begin
            if (disp_proc<>nil) then proc__adr_var(disp_proc,adr_orig);
            freemem(adr_orig,data_size)
          end;
       inherited Done;
     end;  { Tbox.Done }



procedure TFDP_AForm0.Idle (var _Event: TEvent);
    begin
      if is_update and isActive then
         begin
           update_formular;
           is_update:= false
         end;
    end;


(*procedure TFDP_AForm0.form_copy;
    var   _itemd : PForms;
          _items : int;
    begin
      _itemd:= itemd; _items:= items;
      if copy_of_form then
         begin
           if copy_back then copy_form(_itemd,itemd_adr,items);
           disp_form(_itemd,_items)
         end;
    end;

destructor TFDP_AForm0.Done;
     begin
       inherited Done;
       form_copy       { neviem, preco je to na konci, lepsie by bolo pred }
     end;
*)


procedure TFDP_AForm0.update_formular;
    begin
      init_local_var;
      draw;
    end;


function TFDP_AForm0.plan_uz_bol_podany (data: pointer): bool;
   var   res : bool;
   begin
     res:= false;
     if novy and (adr_var<>nil) and (p_is_data<>nil) then res:= TPLAN_zmeneny(p_is_data)(adr_var,true);
     plan_uz_bol_podany:= res
   end;

function TFDP_AForm0.check_data_not_chg (var _Event: TEvent): bool;
   var   res : bool;
         p : pointer;
   begin
     res:= true;
     if (not viewer) and (_Event.Command<>cmULOZ_RPL) then
        begin
        { Nebol plan uz podany ?
        } if novy then res:= not plan_uz_bol_podany(adr_var);

        { Nebol medzitym plan zmeneny inym zdrojom ?
        } if (not novy) and res then
             begin
               if adr_orig<>nil then p:= adr_orig else p:= adr_data;
               if (p<>nil) and (p_chg_data<>nil) then res:= not TPLAN_zmeneny(p_chg_data)(p,true);
             end;

          if res then corr_res:= true
          else corr_res:= false
        end;
     check_data_not_chg:= res
   end;


function TFDP_AForm0.check_formular: bool;
   var   bres : bool;
         size : int;
   begin
     bres:= inherited check_formular;
    { Pretoze sa do zoznamu zapisuje i povtrdenie od externych
      smerov, nuluju sa len priznaky od uzlov siete LETVIS.
      Ak je sprava novou, tak potom sa nuluju vsetky priznaky.
    }
     if bres and (rec<>nil) then
        begin
          if novy then size:= sizeof(rec^) else size:= minimum(NODEpoc,sizeof(rec^));
          fillchar(rec^,size,no_ack);
        end;
     check_formular:= bres
   end;

function TFDP_AForm0.call_check_func(var _Event: TEvent): bool;
   var   res : bool;
   begin
     res:= inherited call_check_func(_Event) and check_data_not_chg(_Event);
     call_check_func:= res
   end;


procedure TFDP_AForm0.InitApp2;
    begin
      if beeping then Beep999(PBFunc,beep_par)
    end;


function TFDP_AForm0._it_i(_ind: int): string;
   begin
     _it_i:= replchar(_it(_ind),[icao_ARR],icao_NXIT)
   end;

procedure TFDP_AForm0.read_pole(ip: int; var it: pchar);
   begin
     inherited read_pole(ip,it);
     it:= ReplChar0 (it,[icao_ARR],icao_NXIT,false)
   end;


procedure TFDP_AForm0.handle_rqst(_rqst_res: Trqst);
    begin
      if is_rqst and (p_handle_rqst<>nil) and (_rqst_res<>_) then
         begin
           if adr_var<>nil then Tproc_rp(p_handle_rqst)(rqst_res,adr_var)
           else Tproc_r(p_handle_rqst)(rqst_res);
         end
    end;

procedure TFDP_AForm0.HandleEvent(var _Event: TEvent);
    var   _Ev : TEvent;
    begin
      {$IFDEF DEBUG}
       if isKey (_Event,#11) then net_pkt_test(paramstr(1),-1,-1);
      {$ENDIF}

      inherited HandleEvent(_Event);

      if      is_rqst
          and ((_Event.What and evMessage) <> 0)
          and (   (_Event.Command = cmREQ_DLA)
               or (_Event.Command = cmREQ_ACK)
               or (_Event.Command = cmREQ_CHG)
               or (_Event.Command = cmREQ_DCL)
              )
                then
         begin
           _Ev:= _Event;
           if call_check_func(_Event) then
              case _Ev.Command of
                cmREQ_DLA : rqst_res:= dla;
                cmREQ_ACK : rqst_res:= ack;
                cmREQ_CHG : rqst_res:= chg;
                cmREQ_DCL : rqst_res:= dcl
              end;
           handle_rqst(rqst_res);
           if corr_res then cmXXXX:= _Ev.Command;
         end
    end;


procedure TFDP_AForm0.spracovany_plan(plan: pointer);
    begin
    end;
