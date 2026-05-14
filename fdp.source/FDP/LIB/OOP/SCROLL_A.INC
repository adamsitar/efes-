{
‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹
€                                                          €
€ aplikacie scrollu                                        €
€‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹€
}

{ ------------------------------
  zobrazenie obsahu DB subora
  ------------------------------
}
function  scroll_DB (    _title        : string;     { hlavicka }
                         _find_and_process_data,
                         _msg_not_processed : bool;

                    { a) parametre pre pole }
                         _items        : int;      { maximum overdrive }
                         _item_size    : word;     { velkost polozky }

                         _new_item     : pointer;  { Tproc_p2 - alokacia polozky }
                         _format_item  : pointer;  { Tproc_p - formatovanie }
                         _disp_item    : pointer;  { Tproc_pl dealokacia, moze byt nil }
                         _eq_items     : pointer;

                         _p_filter     : pointer;     { zaznam s udajmi podmienok pre nacitanie }
                         _p_kluc       : PBFunc_p2;   { porovnanie identifikacnych udajov }
                         _p_stav       : PBFunc_p2;   { porovnanie inych udajov }
                         _p_datadb     : PBFunc_p2;   { kontrola pripustnosti nacitania }
                         _p_dataext    : PBFunc_p2;   { kontrola pripustnosti zaradenia }

                         _vzostupne    : bool;
                         _sort_item    : pointer;  { Tproc_p2 - zotriedenie zoznamu }
                         _comp_item    : pointer;  { alebo priama funkcia pre porovnanie }

                         _handler_type : TScrollAct_handler_type;
                         _handler      : pointer;  { @TBfunc_i  }
                         _handler_par  : pointer;   { adresa objektu dat alebo parametrov }

                    { b) parametre pre DBF  }
                         _FN          : string;
                         _FNfunc      : pointer;  { Fcia pre FN, @TSfunc_pi   }
                         _FNfunc_p    : pointer;  { parameter p pre TSFunc_pi }
                         _riadkov     : byte;
                         _DATAdecode  : pointer;
                         _DBchg       : pointer;  { ukazovatel na logicku premennu zapisu do DBF }

                    { c) parametre pre ScrollWin }
                         _item_dx,_item_dy : int;  { velkost polozky }
                         _item_list    : pointer; { vypis polozky }

                         _dxb,_dyb : int;
                         _init_buttons,_handle_buttons : pointer;
                         _handler_owner : PObject;

                         _info,_hlpXXX : Pchar
                    ) : bool;

    var   sc : PScrollDB2;
          Ev : TEvent;
    begin
      if (_FN='') and (_FNfunc=nil) then Exit;
      if _info=nil then _info:= SCROLL_SEL;
      sc:= New(PScrollDB2,Init(_title,

                               _find_and_process_data,
                               _msg_not_processed,

                               _items,_item_size,
                               _new_item,_format_item,_disp_item,_eq_items,

                               _p_filter,_p_kluc,_p_stav,_p_datadb,_p_dataext,
                               _vzostupne,_sort_item,_comp_item,
                               _handler_type,_handler,_handler_par,

                               _FN,_FNfunc,_FNfunc_p,
                               _riadkov,_DATAdecode,_DBchg,

                               _item_dx,_item_dy,_item_list,
                               0,0, _init_buttons,_handle_buttons,_handler_owner,

                               _hlpXXX)
                              );
      sc^.RunLocalFunc(Ev,_info);
      scroll_DB:= sc^.finded_and_processed_data;
      Dispose(sc,Done)
    end;



{ ------------------------------
  zobrazenie obsahu adresara
  ------------------------------
}

function _get_items_DIR(_PATH: pstring): int; far;
   begin
     _get_items_DIR:= GetNmbOfFiles(_PATH^)
   end;


procedure _init_items_DIR(_PATH : pstring; _items : PPchars; _pocet : int;
                          _get_item,_sort_item : pointer; _sort_dir : bool
                         ); far;
    var   Dir     : PDir;
          Files,i : int;
          s : string;
    begin
      if GetDirFiles(_PATH^,'', Dir,Files)<>-1 then
         begin
           for i:= 0 to _pocet-1 do
             begin
               s:= Dir^[i]^.name;
               if (_get_item<>nil) then s:= TSfunc_s(_get_item)(s);
               _items^[i]:= StrPasNew(s)
             end;
           FreeDirFiles(Dir,Files);
           if (_sort_item<>nil) then TScrollLst_Sort(_sort_item)(_items,_pocet, _sort_dir)
         end
    end;


function scroll_LST(_title: string;
                    page : int;
                    info,hlpXXX: Pchar;
                    _PATH       : string;
                    _get_item   : pointer;    { @TSfunc         }
                    _sort_item  : pointer;    { @Proc_pib       }
                    _sort_dir   : bool        { smer triedenia  }
                   ): string;

   var   ScL : TScrollLst;
         RES : string;
         POS : int;
   begin
     ScL.Init(nil, ' '+_title+' ' ,-1,-1, page, info,hlpXXX,
              @_PATH, @_get_items_DIR,@_init_items_DIR, _get_item,_sort_item,_sort_dir,
              RES,POS
             );
     scroll_LST:= RES
   end;

