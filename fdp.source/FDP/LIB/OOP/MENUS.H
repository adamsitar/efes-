    type   TTypeMenu = (_item,_line,_submenu,_switch0,_switch1,_switch2, _radio,_radioitem);

           PWinMenu = ^TWinMenu;

         { --------------------------------------------- }
         { TItem - prototyp polozky menu a spinaca       }
         { --------------------------------------------- }
           PItem = ^TItem;
           TItem = object(TButton)
             mnu        : TTypeMenu;

             Next       : PItem;
             PMenu      : PWinMenu;

             PMenu_init : pointer;
             PMenu_done : pointer;

             en_func    : pointer;
             en_bool    : bool;
             is_func    : bool;

             constructor Init(_title: string; _cmXXXX: word; _Next: PItem);
             procedure   HandleEvent(var _Event: TEvent); virtual;
             procedure   Draw; virtual;
             procedure   Text(_ct,_ck: byte); virtual;

             procedure   init_for_draw; virtual;

             procedure   ActiveOn;  virtual;
             procedure   ActiveOff; virtual;
             procedure   isActive;

             function    isEnabled: bool; virtual;

             {protected}
             function    get_width : int; virtual;
             function    get_height: int; virtual;

             procedure   InitXY(x,y, dx: int); virtual;
             procedure   DoneItems; virtual;
           end;


         { --------------------------------------------- }
         { TItem2                                        }
         { --------------------------------------------- }
           PItem2 = ^TItem2;
           TItem2 = object(TItem)
             constructor Init(_title: string; _kbHot: char; _cmXXXX: word; _Next: PItem);
           end;



         { --------------------------------------------- }
         { TLine - prazdna polozka                       }
         { --------------------------------------------- }
           PLine = ^TLine;
           TLine = object(TItem)
             sirka: byte;

             constructor Init(_Next: PItem);
             procedure   Draw; virtual;
             {protected}
             procedure   InitXY(x,y, dx: int); virtual;

             {function    isEnabled: bool; virtual;}
           end;


         { --------------------------------------------- }
         { TTextLine - info text                         }
         { --------------------------------------------- }
           PTextLine = ^TTextLine;
           TTextLine = object(TLine)
             Ttitle : pchar;
             Tkey   : string[5];

             constructor Init(_title: string; _Next: PItem);
             destructor  Done; virtual;

             procedure   Draw; virtual;
             procedure   ActiveOn;  virtual;
             procedure   ActiveOff; virtual;
           end;


         { --------------------------------------------- }
         { TSubMenu - polozka menu pre dalsie menu       }
         { --------------------------------------------- }
           PSubMenu = ^TSubMenu;
           TSubMenu = object(TItem)
             public
             constructor Init(_title: string; _PMenu: PWinMenu; _Next: PItem);
             destructor  Done; virtual;
             procedure   HandleEvent(var _Event: TEvent); virtual;
             procedure   MoveRel(dx,dy: int); virtual;
           end;


         { --------------------------------------------- }
         { TSwitch0 - prepinac pre MainMenu              }
         { --------------------------------------------- }
           PSwitch0 = ^TSwitch0;
           TSwitch0 = object(TItem)
             {protected}
             check_adr: pointer;  { na adrese check_adr je bool stav   }

             public
             constructor Init(_title: string; _cmXXXX: word; _check_adr: pointer; _Next: PItem);
             procedure   HandleEvent(var _Event: TEvent); virtual;
             procedure   Draw; virtual;

             procedure   read_check_adr; virtual;
             procedure   writeto_check_adr; virtual;
           end;


         { --------------------------------------------- }
         { TSwitch1 - prepinac pre menu                  }
         { --------------------------------------------- }
           PSwitch1 = ^TSwitch1;
           TSwitch1 = object(TItem)
             {protected}
             check_adr: pointer;  { na adrese check_adr je bool stav   }
             xt : int;

             public
             constructor Init(_title: string; _cmXXXX: word; _check_adr: pointer; _Next: PItem);
             procedure   HandleEvent(var _Event: TEvent); virtual;

             procedure   read_check_adr; virtual;
             procedure   writeto_check_adr; virtual;
             procedure   init_for_draw; virtual;

             procedure   draw_switch; virtual;
             procedure   text_switch; virtual;
             procedure   Draw; virtual;
             procedure   _text_bk(bk: byte); virtual;
             procedure   Text(_ct,_ck: byte); virtual;

             {protected}
             function    get_width: int; virtual;
             procedure   InitXY(x,y, dx: int); virtual;
             function    inView(x,y: int): bool; virtual;
           end;


         { --------------------------------------------- }
         { TSwitch2 - prepinac pre Options               }
         { --------------------------------------------- }
           PSwitch2 = ^TSwitch2;
           TSwitch2 = object(TSwitch1)
             constructor Init(_title: string; _check_adr: pointer; _Next: PItem);
             procedure   HandleEvent(var _Event: TEvent); virtual;
           end;


         { --------------------------------------------- }
         { TSwitchI - prepinac pre Options               }
         { --------------------------------------------- }
           PSwitchI = ^TSwitchI;
           TSwitchI = object(TSwitch2)

             iadr : pint;
             ivar,imin,imax : int;
             unt  : pchar;

             ifrm : PForm;
             flen : byte;
             box  : PBox;

             constructor Init(_title: string; _check_adr: pint; _unt: string; _imin,_imax: int; _Next: PItem);
             function    get_width: int; virtual;
             procedure   MoveRel(dx,dy: int); virtual;  { tieto dve misia byt, lebo je to len TView }
             procedure   InitXY(x,y, dx: int); virtual;
             destructor  Done; virtual;

             procedure   read_check_adr; virtual;
             procedure   writeto_check_adr; virtual;
             procedure   init_for_draw; virtual;

             procedure   draw_switch_(_active: bool);
             procedure   draw_switch; virtual;
             procedure   text_switch; virtual;
             procedure   _text_bk(bk: byte); virtual;
             procedure   HandleEvent(var _Event: TEvent); virtual;
           end;


         { --------------------------------------------- }
         { TRadioItem - jeden z prepinacov pre Options   }
         { --------------------------------------------- }
           PRadioItem = ^TRadioItem;
           TRadioItem = object(TSwitch2)
             constructor Init(_title: string; _Next: PItem);
             procedure   HandleEvent(var _Event: TEvent); virtual;
           end;


         { ------------------------------------------------- }
         { TRadio -> prepinace - len jeden moze byt ON       }
         { ------------------------------------------------- }
           PRadio = ^TRadio;
           TRadio = object(TItem)
             {protected}
             Switches : PGroup;
             check_adr: pointer;  { na adrese check_adr je vyctovy typ }
             val_off  : int;      { posun vyctoveho typu oprotu 0 }
             sw       : byte;     { pocet spinacov }
             swON     : int;      { cislo pre ON   }

             FirstItem, LastItem: PItem;  { prva a posledna  }
             ActItem: PItem;              { aktualna polozka }

             public
             constructor Init(_title: string; _check_adr: pointer; _val_off: int; _FirstItem: PSwitch2; _Next: PSwitch2);
             procedure   Draw; virtual;
             destructor  Done; virtual;

             procedure   ActiveOn;  virtual;
             procedure   ActiveOff; virtual;

             {protected}
             function    get_width : int; virtual;
             function    get_height: int; virtual;
             procedure   InitXY(x,y, dx: int); virtual;

           { metody definujuce spravanie sa Radia ako skupiny TGroup }
             procedure   m_shape; virtual;
             procedure   HandleEvent(var _Event: TEvent); virtual;
             procedure   MoveRel(dx,dy: int); virtual;
             procedure   SwitchesDraw;
           end;


         { --------------------------------------------- }
         { TWinMenu - menu pull down                     }
         { --------------------------------------------- }
         { generuje cmXXXX, ktory mu odovzda Item
           a ten sa vrati hlavnej aplikacii
         }
           TWinMenu = object(TWindow)
             {protected}
             FirstItem, LastItem: PItem;  { prva a posledna  }
             ActItem: PItem;              { aktualna polozka }

             PConfirmed : PProc;

             sirka,vyska  : int;          { max sirka a vyska polozky }
             r            : Tregion;
             initialized  : bool;         { boli precitane hodnoty do Switch2 }

             public
             constructor Init(_title: string; _hlpXXX : Pchar; _FirstItem: PItem);
             procedure   HandleEvent(var _Event: TEvent); virtual;
             procedure   Draw; virtual;
             procedure   ReInitDraw; virtual;

             procedure   AddItem(_Item: PItem);
             procedure   set_size; virtual;

             function    PrevItem(P: PItem): PItem;  { predchadzajuca }
             function    NextItem(P: PItem): PItem;  { nasledujuca }
             procedure   SetActItem(_next: PItem); virtual; { nastavi a prekresli }

             {protected}
             procedure   DoneItems; virtual;
             function    EndState(var _Event: TEvent): bool; virtual;
             procedure   Image; virtual;
           end;


         { --------------------------------------------- }
         { TOptMenu - nastavovacie menu                  }
         { --------------------------------------------- }
           POptMenu = ^TOptMenu;
           TOptMenu = object(TWinMenu)

             private
             btOK     :  PbtOK;
             btCancel :  PbtCancel;
             procedure   init_buttons; virtual;

             public
             constructor Init(_title: string; _hlpXXX : Pchar; _cmXXXX: word; _FirstItem: PItem);
             procedure   HandleEvent(var _Event: TEvent); virtual;

             function    get_width: word; virtual;
             procedure   set_size; virtual;
           end;


         { --------------------------------------------- }
         { TOptMenu_S - scrolovacie OptMenu              }
         { --------------------------------------------- }
           POptMenu_S = ^TOptMenu_S;
           TOptMenu_S = object(TOptMenu)
             lo,          { index prvej a poslednej polozky v okne }
             hi  : int;   { podla ich indexov v originalnom poli   }
             top : int;   { pocet poloziek                         }
             pos : int;   { pozicia vo vypise v <0,top>            }

             item_dy : int;    { vyska polozky pre vypis           }

             page : byte;
             sb   : PScrollBar;

             constructor Init(_title: string; _hlpXXX : Pchar; _cmXXXX: word; _page: byte; _FirstItem: PItem);
             procedure   HandleEvent(var _Event: TEvent); virtual;

             procedure   set_size; virtual;

             function    get_pos(Item: PItem): int;
             function    get_Item(pos_: int): PItem;
             procedure   set_Item_dy;

             function    ScrollItem(di: int): PItem;
             procedure   SetActItem(_next: PItem); virtual;

             {protected}
             procedure   DoneItems; virtual;
           end;


         { --------------------------------------------- }
         { TWinMenu_S - scrolovacie OptMenu              }
         { --------------------------------------------- }
           PWinMenu_S = ^TWinMenu_S;
           TWinMenu_S = object(TOptMenu_S)
             procedure   init_buttons; virtual;
             function    get_width: word; virtual;
           end;

         { --------------------------------------------- }
         { TBarMenu - riadkove menu                      }
         { --------------------------------------------- }
           PBarMenu = ^TBarMenu;
           TBarMenu = object(TGroup)
             {protected}
             btTit, btEmp:  PButton;
             FirstItem   :  PItem;

             function inView(x,y: int): bool; virtual;

             public
             constructor Init(_title: string; _FirstItem: PItem);
             procedure   HandleEvent(var _Event: TEvent); virtual;

             procedure   Reinit(x,y,dx,dy: int); virtual;
             function    inBarMenuKeys(key: char): bool;
           end;
