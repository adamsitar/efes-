function _plan_pre_pracovisko(PRS: PPRS): bool; far;
   begin
     _plan_pre_pracovisko:=    _plan_pre_(PRS^.unt,false,false)
                            or _plan_pre_(PRS^.let,false,false)
   end;


function _is_stata_PRS (PRS: PPRS; s: Pstring): bool; far;
   begin
     _is_stata_PRS:= _is_statp(PRS^.stat,s,false)
   end;

function _is_stat_PRS (PRS: PPRS; s: Pstring): bool; far;
   begin
     _is_stat_PRS:= _is_stata_PRS(PRS,s) and _plan_pre_pracovisko(PRS)
   end;

function _is_stato_PRS (PRS: PPRS; s: Pstring): bool; far;
   begin
     _is_stato_PRS:= _is_stata_PRS(PRS,s) and (not _plan_pre_pracovisko(PRS))
   end;


function comp_PRS(PRS1,PRS2: PPRS): bool; far;
   begin
     if PRS1^.kod = PRS2^.kod then
        comp_PRS:=   DTtoSec(PRS1^.zac.rok,PRS1^.zac.mes,PRS1^.zac.den, PRS1^.zac.h,PRS1^.zac.m,0)
                   < DTtoSec(PRS2^.zac.rok,PRS2^.zac.mes,PRS2^.zac.den, PRS2^.zac.h,PRS2^.zac.m,0)
     else comp_PRS:= PRS1^.kod < PRS2^.kod
   end;

procedure sort_PRS(PRSs: Pptrs; top: pointer); far;
    begin
      QuickSort(PRSs,@comp_PRS,nil,0,int(top^), false)
    end;

{$IFDEF PROCESS_PRS}
  procedure send_PRSs (PRSs: Pptrs; top: pointer); far; forward;
{$ENDIF}


{ Moze zadat lubovolny let vyhovujuci kriteriam
  alebo len podmnozinu letov dodefinovanych
  podla "select"
}
type  PPRS_key = ^TPRS_key;
      TPRS_key = record
        kod : string;
        unt : string;
        let : string;
        das : TDate;
      end;

type  PPRS_item_filter = ^TPRS_item_filter;
      TPRS_item_filter = record
        key         : TPRS_key;
        data_filter : pointer;
        prev_filter : pointer;
      end;

{$I _PRS_id.frm}   { formular pre zadanie identifikacie letu }

function _item_filter_PRS(PRS: PPRS; _item: PPRS_item_filter): bool; far;
   begin
     _item_filter_PRS:=
          (_item<>nil)
      and (                             eq_str(_item^.key.kod,PRS^.kod))
      and ((_item^.key.unt='')      or (eq_str(_item^.key.unt,_mairbase(PRS^.unt))))
      and ({$IFDEF AIRBASE}
             (eq_str(_mairbase(airbase),_mairbase(PRS^.let)))
           {$ELSE}
             (_item^.key.let='')    or (eq_str(_item^.key.let,_mairbase(PRS^.let)))
           {$ENDIF}
          )
      and ((_item^.key.das.r=0)     or (eq_date(_item^.key.das,PRS^.das)))
      and ((_item^.prev_filter=nil) or Tfilter_items_DB(_item^.prev_filter)(PRS,_item^.data_filter))
   end;


procedure spracuj_PRS(_find_and_process_data,_find_cnl_data : bool;
                      _ppl,_arch,_rpl : bool;

                      _data_filter : string; _filter : pointer;
                      _handler : pointer; _handler_type : TScrollAct_handler_type;
                      _print, _send : bool;
                      _title: string; _info: pchar; _hlpXXX : Pchar
                     );

   var    item          : TPRS_item_filter;
          p_data_filter : pointer;
          key           : string;

          _FN           : string;
          _dbchg        : pointer;

          print, send   : pointer;

   begin

    { urcenie dat na vyhladanie...
    }
     key:= '';
     fillchar(item,sizeof(item),0);
     p_data_filter:= @_data_filter;
     if _find_and_process_data then
        begin
          if not formular_key_prs(tit_PRS,@fnAREA,true,_arch,item.key) then Exit;
          if cut_(item.key.kod)<>'' then
             begin
               item.data_filter:= @_data_filter;
               item.prev_filter:= _filter;
               p_data_filter:= @item;
               _filter:= @_item_filter_PRS;
             end
          else _find_and_process_data:= false
        end;

    { urcenie subora, kde sa ma vyhladavat...
    }
     if _rpl then
        begin
          _FN:= get_dbPRS_RPLfn;
          _dbchg:= @dbchg_PRS_RPL
        end
     else begin
            if (item.key.das.r<>0) and (CheckDate(item.key.das.r,item.key.das.m,item.key.das.d, false))
               then _FN:= get_dbfn(item.key.das, pathPRS,extPRS)
            else begin
                   if _ppl then _FN:= get_PPL_FN(pathPRS,extPRS,_title)
                   else if _arch then _FN:= get_ARCH_FN(pathARCH_PRS,extPRS,_title)
                   else _FN:= get_dbPRSfn;
                 end;
            _dbchg:= nil {@dbchg_PRS}
          end;

    { parametre pre tlac, odoslanie...
    }
     send:= nil;
     print:= nil;

     {$IFDEF PROCESS_PRS} {$IFDEF AIRBASE}
       if _send then send:= @send_PRSs;
     {$ENDIF} {$ENDIF}

     {$IFDEF PRN}
       if _print then print:= @print_PRSs;
     {$ENDIF}

     scroll_DB_FDP(_title,

                   _find_and_process_data,
                   _find_cnl_data,
                   true, nil,

                   max_PRS, sizeof(TPRS),
                   @new_PRS,nil,@disp_PRS,@eq_PRS,

                   key,@read_PRS,
                   p_data_filter,nil,nil,_filter,_filter,

                   true,@sort_PRS,nil,
                   _handler_type,_handler,nil,
                   nil,nil,nil, print,send,

                   _FN, {_FNfunc, _FNfunc_p,} nil,nil,
                   db_PRS_RIADKOV,@decodeDB_PRS, _dbchg,

                   dxi_PRS, dyi_PRS, @plan_PRS,
                   _info, _hlpXXX,

                   @p_prs_dbscroller
                  )
   end;