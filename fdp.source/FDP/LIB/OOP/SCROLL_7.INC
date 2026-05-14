(*          { --------------------------------------------- }
          { TScrollDB                                     }
          { --------------------------------------------- }

    type  TScrollDBdecode = procedure(DB: PDB; i: int);
          TSFunc_pi = function(p: pointer; i: int): string;
                    { fcia pre vratenie nazvu subora p^
                      podla indexu i, ak je mimo rozsah, vrati ''
                    }

    type  PScrollDBI = ^TScrollDBI;
          TScrollDBI = object(TScrollInd)

          { a) DBF  }
            FN         : string;
            FNfunc     : pointer;
            FNfunc_p   : pointer;

            riadkov    : byte;
            DATAdecode : pointer;
            DBchg      : pointer;   { ukazovatel na logicku premennu zapisu do DBF }
            DBdone     : pointer;

          { b) pole }
            pole_adr  : pointer;    { adresa vonkajsej adresy pola smernikov na hodnoty }
            max_pole  : int;        { maxium overdrive }
            size_item : word;

            vzostupne : bool;

            data_item   : pointer;  { ukazovatel na polozku typu pola ako - funkcia buffera }
            disp_item   : pointer;  { Tproc_pl dealokacia polozky     }

            data_filter : pointer;  { ukazovatel na podmienku }
            filter      : pointer;  { TBfunc_p2: premenna, podmienky }

            add_item   : pointer;   { Tproc_p3l alokacia polozky         }
            del_item   : pointer;   { Tproc_pl dealokacia, moze byt nil  }
           { sort_item  : pointer;    Tproc_p2 - zotriedenie zoznamu     }

           { c)     }
            info : Pchar;


            constructor Init({ a) parametre pre DB   }
                                  _FN          : string;
                                  _FNfunc      : pointer;  { @TSfunc_pi                }
                                  _FNfunc_p    : pointer;  { parameter p pre TSFunc_pi }

                                  _riadkov     : byte;
                                  _DATAdecode  : pointer;
                                  _DBchg       : pointer;  { ukazovatel na logicku premennu zapisu do DBF }

                             { b) parametre pre alokaciu externeho pola         }
                                  _pole_adr  : pointer;    { adresa pola <> nil }
                                  _top_adr   : pointer;    { adresa ukazovatela na vrchol <> nil}

                                  _max_pole  : int;        { maximum overdrive  }
                                  _size_item : word;       { velkost polozky    }

                                  _data_item   : pointer;  { ukazovatel na polozku typu pola ako - funkcia buffera }
                                  _disp_item   : pointer;  { Tproc_pl dealokacia, moze byt nil }

                                  _data_filter : pointer;  { ukazovatel na podmienku           }
                                  _filter      : pointer;  { TBfunc_p2: premenna, podmienky    }

                                  _add_item    : pointer;  { Tproc_p3l alokacia, moze byt nil  }
                                  _del_item    : pointer;  { Tproc_pl dealokacia, moze byt nil }

                                  _vzostupne   : bool;
                                  _sort_item   : pointer;  { Tproc_p2 - zotriedenie zoznamu    }

                             { c) parametre pre ScrollInd               }
                                  _title : string;
                                  _page  : int;

                                  _comp         : pointer;     { @TBfunc_p2: bool; pre porovnanie  }
                                  _handler      : pointer; { @TBfunc_i  }
                                  _handler_type : TScrollAct_handler_type;
                                  _item_pos     : pointer; { handled pos - @int }

                                  _item_list : pointer;
                                  _item_dx,_item_dy : int;

                                  _hlpXXX   : Pchar;
                                  _info     : pchar
                            );

            destructor  Done; virtual;

            function    is_changed: bool; virtual;
            procedure   new_data;  virtual;
            procedure   disp_data; virtual;
          end;



{
‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹
€                                                          €
€ TScrollDB                                                €
€‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹€
}
constructor TScrollDBI.Init({ a) parametre pre DB   }
                                 _FN          : string;
                                 _FNfunc      : pointer;  { @TSfunc_pi                }
                                 _FNfunc_p    : pointer;  { parameter p pre TSFunc_pi }

                                 _riadkov     : byte;
                                 _DATAdecode  : pointer;
                                 _DBchg       : pointer;  { ukazovatel na logicku premennu zapisu do DBF }

                            { b) parametre pre alokaciu externeho pola         }
                                 _pole_adr  : pointer;    { adresa pola <> nil }
                                 _top_adr   : pointer;    { adresa ukazovatela na vrchol <> nil }

                                 _max_pole  : int;        { maximum overdrive  }
                                 _size_item : word;       { velkost polozky    }

                                 _data_item   : pointer;  { ukazovatel na polozku typu pola ako - funkcia buffera }
                                 _disp_item   : pointer;  { Tproc_pl dealokacia, moze byt nil }

                                 _data_filter : pointer;  { ukazovatel na podmienku           }
                                 _filter      : pointer;  { TBfunc_p2: premenna, podmienky    }

                                 _add_item    : pointer;  { Tproc_p3l alokacia, moze byt nil  }
                                 _del_item    : pointer;  { Tproc_pl dealokacia, moze byt nil }

                                 _vzostupne   : bool;
                                 _sort_item   : pointer;  { Tproc_p2 - zotriedenie zoznamu    }

                            { c) parametre pre ScrollInd               }
                                 _title : string;
                                 _page  : int;

                                 _comp         : pointer;     { @TBfunc_p2: bool; pre porovnanie  }
                                 _handler      : pointer; { @TBfunc_i  }
                                 _handler_type : TScrollAct_handler_type;
                                 _item_pos     : pointer; { handled pos - @int }

                                 _item_list : pointer;
                                 _item_dx,_item_dy : int;

                                 _hlpXXX   : Pchar;
                                 _info     : Pchar
                           );

      var   _Event: TEvent;
      begin

       { a) parametre pre DBF  }
         FN:= _FN; FNfunc:= _FNfunc; FNfunc_p:= _FNfunc_p;
         riadkov:= _riadkov; DATAdecode:= _DATAdecode; DBchg:= _DBchg;
         DBdone:= nil;

       { b) parametre pre pole }
         pole_adr:= _pole_adr;
         max_pole:= _max_pole;   size_item:= _size_item;

         data_item:= _data_item; disp_item:= _disp_item;
         data_filter:= _data_filter; filter:= _filter;

         add_item := _add_item; del_item:= _del_item;
         vzostupne:= _vzostupne;

       { c) inherited call }
         inherited Init(_title,_page,
                        nil, nil,_top_adr, nil,
                        _comp, _handler, _handler_type,
                        _item_list, _item_dx,_item_dy,
                        _hlpXXX
                        {nil _arr: Pptrs,}
                       );

         if _info<>nil then info:= _info else _info:= SCROLL_INFO;

       { d) nacitanie dat }
         new_DBarray(pole_adr, max_pole, size_item);
         new_data;

         {if (not LIST_EMPTY_SCROLL) and (top=-1) then Say2(msgMESS,msgDATA_NOT_FOUND)
         else} RunLocalFunc(_Event,_info);
         Done
       end;


destructor TScrollDBI.Done;
     begin
       if (DBdone<>nil) then Tproc(DBdone);          { akcia na zaver }
       disp_data;
       dispose_DBarray(pole_adr, max_pole, size_item);
       inherited Done
     end;


function TScrollDBI.is_changed: bool;
   begin
     if (     (DBchg<>nil) and bool(DBchg^)
          and (OpenWins=1{2})) then  { 1.okno - stav.riadok, 2.okno - scrollwin }
           begin
             bool(DBchg^):= false;
             is_changed:= true;
             new_data;
             List
           end
     else is_changed:= false
   end; { TScroller.is_changed }


procedure TScrollDBI.new_data;
    var   i,j : int;
          fname,fpname : string;
    begin
    { prerobit na vnorene volanie nazvov suborov }
      disp_data;

      fname:= FN;
      i:= 0;
      repeat
        fpname:= fname;
        if not ((i=0) and (FN<>'')) then
           if FNfunc<>nil then fname:= TSfunc_pi(FNfunc)(FNfunc_p,i);
        new_DBitems(pole_adr, top_adr, top, max_pole,
                    data_item, disp_item, data_filter,
                    filter, add_item, vzostupne,
                    fname, riadkov, DATAdecode
                   );
        top:= int(top_adr^);
        inc(i)
      until (FNfunc=nil) or (fname='') or (fpname=fname);
      {if sort_item<>nil then TProc_p2(sort_item)(pole_adr, top_adr)}

      inherited new_data
    end;


procedure TScrollDBI.disp_data;
    var   i: int;
    begin
      inherited disp_data;

      dispose_DBitems(pole_adr, top_adr, del_item);
      top:= int(top_adr^);
      pos:= Limit(pos, lo,N(top), 0)
    end;

*)