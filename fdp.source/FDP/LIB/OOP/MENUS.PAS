(*-------------------------------------------------------------------*)
(* Menus 1.0                                                         *)
(* 1993,94                                                           *)
(*-------------------------------------------------------------------*)
{$I comp.h}

{
 POUZITELNE OBJEKTY:
 ~~~~~~~~~~~~~~~~~~~
 menu:
 SubMenu:   definicia submenu s roznymi polozkami, musi sa udat Win alebo OptMenu
  WinMenu - specifikuje menu pre prikazy a spinace
  OptMenu - specifikuje menu pre nastavenie premennych (Switch,Radio)
            a ich potvrdenie cez cmOK

 polozky:
 WinMenu:
  Item    - spinac pre generovanie prikazu, tiez otec
  Switch1 - prepinac logickej premennej, generuje spravu o prepnuti
  Switch0 - ako Switch1, ale do hlavneho menu

 OptMenu:
  Switch2 -  -//- ako sucast OptMenu, nastavi sa len po slaceni "Ok"
  RadioItem  - prepinac do jedneho zo stavov pre RadioItem
  Radio      - prepinac na jeden z viacerych stavov


 POZNAMKY O PREPINACOCH:
 ~~~~~~~~~~~~~~~~~~~~~~~
 switch1 - cmNil -> pouzit len pre objekty, ktore sa len prepinaju/zapinaju

}

unit Menus;


interface

    uses   TypeDef, graph_h, {$IFDEF BGI} Graph {$ELSE} Graphs {$ENDIF},
           Events, Objects, Views, Button, Scroll, Edit;


    const  cnst_AltHotKey = '"';
           MEDZERA_ITEM   = 4;
           dx_ITEM        = 20;
           dy_ITEM        = winHEIGHT + 2;


    const  mnu_palette          : bool = true;
           mnu_mouse_scroll     : bool = false;
           mnu_data_opt_common  : bool = {$IFDEF OPL} false
                                         {$ELSE} {$IFDEF FDA} true
                                         {$ELSE} true
                                         {$ENDIF} {$ENDIF};

           cfg_mnu_palette      = 'menu palette';
           cfg_mnu_mouse_scroll = 'menu scroll by mouse';


    {$I menus.h}


    type   FBarMenu   = function: PBarMenu;
           Tproc_p_vE = procedure(P: pointer; var _Event: TEvent);

    const  BarMenu  : PBarMenu = nil;
           max_Pitems = 80;

    type   TPItems = array[0..max_Pitems-1] of PItem;


    {function  do_(kolko: int): string;}
    function  hk_(var ihk: int): char;
    function  hk (var ihk: int): string;
    function  hki(var ihk: int): string;

    procedure add_newline__(typ: int; nls: int; var nl,items: int; var smnu : TPItems);
    procedure add_newline_ (typ: int; var nl,items: int; var smnu : TPItems);
    procedure add_newline  (var nl,items: int; var smnu : TPItems);


    function  SubMenu (_title: string; _PMenu: PWinMenu; _Next: PItem): PSubMenu;
    function  SubMenu_(_title: string; _en_func: pointer; _en_bool: bool{;_is_func: bool}; _PMenu: PWinMenu;
                       _Next: PItem
                      ): PSubMenu;

    function  SubMenuInitialized(SubMenu: PSubMenu; _Next: PItem): PSubMenu;
    function  AddItemToMenu     (SubMenu: PSubMenu; _Next: PItem): PSubMenu;
    function  AddSubMenuToMenu  (SubMenu: PSubMenu; _Next: PItem): PSubMenu;

    function  WinMenu  (_title: string; _hlpXXX : Pchar; _FirstItem: PItem): PWinMenu;
    function  WinMenu_S(_title: string; _hlpXXX : Pchar; _page: byte; _FirstItem: PItem): PWinMenu_S;

    function  OptMenu  (_title: string; _hlpXXX : Pchar; _cmXXXX: word; _FirstItem: PItem): POptMenu;
    function  OptMenu_S(_title: string; _hlpXXX : Pchar; _cmXXXX: word; _page: byte; _FirstItem: PItem): POptMenu_S;

    procedure RunMenu  (Menu: PWinMenu; var _Event: TEvent);

    function  Item    (_title: string; _cmXXXX: word; _Next: PItem): PItem;
    function  Item_   (_title: string; _cmXXXX: word; _en_func: pointer; _en_bool: bool{;_is_func: bool};
                       _Next: PItem
                      ): PItem;
    function  Item2   (_title: string; _kbHot: char ; _cmXXXX: word; _Next: PItem): PItem;

    function  NewLine (_Next: PItem): PItem;
    function  NewLine2(_sirka: byte; _Next: PItem): PItem;
    function  NewTLine(_title: string; _Next: PItem): PItem;

    function  Switch0 (_title: string; _cmXXXX: word; _check_adr: pointer; _Next: PItem): PSwitch0;
    function  Switch0_(_title: string; _cmXXXX: word; _check_adr: pointer; _en_func: pointer; _en_bool: bool{;_is_func: bool};
                       _Next: PItem
                      ): PSwitch0;

    function  Switch1 (_title: string; _cmXXXX: word; _check_adr: pointer; _Next: PItem): PSwitch1;
    function  Switch1_(_title: string; _cmXXXX: word; _check_adr: pointer; _en_func: pointer; _en_bool: bool{;_is_func: bool};
                       _Next: PItem
                      ): PSwitch1;
    function  Switch2 (_title: string; _check_adr: pointer; _Next: PItem): PSwitch2;
    function  Switch2_(_title: string; _check_adr: pointer; _en_func: pointer; _en_bool: bool{;_is_func: bool};
                       _Next: PItem
                      ): PSwitch2;

    function  SwitchI (_title: string; _check_adr: pint; _unt: string; _imin,_imax: int; _Next: PItem): PSwitchI;
    function  SwitchI_(_title: string; _check_adr: pint; _unt: string; _imin,_imax: int;
                       _en_func: pointer; _en_bool: bool; {_is_func: bool;}
                       _Next: PItem
                      ): PSwitchI;

    function  RadioItem (_title: string; _Next: PItem): PRadioItem;
    function  RadioItem_(_title: string; _en_func: pointer; _en_bool: bool{;_is_func: bool};
                         _Next: PItem
                        ): PRadioItem;
    function  Radio     (_title: string; _check_adr: pointer; _val_off: int; _FirstItem: PSwitch2; _Next: PSwitch2): PRadio;



implementation

uses BIOS, IO,
     math, mem, str0, sets, mess, msg,
     mouse, keyb,
     BGIgraph, SVGA,
     CMs;


const init_menus  : bool = false;

type  Pshift_menu = ^Tshift_menu;
      Tshift_menu = record
        c : char;
        p : pointer
      end;


{$I menus.inc}

const activeMenu: PWinMenu = nil;

procedure RunMenu(Menu: PWinMenu; var _Event: TEvent);
    var   mp,ms: bool;
          am: PWinMenu;
    begin
      ms:= mnu_mouse_scroll;
      if mnu_mouse_scroll then
         begin
           {m_set_shape(NIC);}
           mp:= MouseMotionEvents; MouseMotionEvents:= true;
           ev_mx:= mouse_status.stat.x; ev_my:= mouse_status.stat.y
         end;
      am:= activeMenu; activeMenu:= Menu;
      Menu^.Run(_Event);
      activeMenu:= am;
      if mnu_mouse_scroll then
         begin
           ev_mx:= mouse_status.stat.x; ev_my:= mouse_status.stat.y;
           MouseMotionEvents:= mp;
         end;
      {if ms then m_restore_shape}
    end;

{$I menus_1.inc} { TItem, TLine, TSubMenu }
{$I menus_2.inc} { TSwitch0..2            }
{$I menus_3.inc} { TRadioItem, TRadio     }
{$I menus_4.inc} { TWinMenu, TWinMenu_S   }
{$I menus_5.inc} { TOptMenu, TOptMenu_S   }
{$I menus_6.inc} { TBarMenu               }


{
‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹
€                                                          €
€ Inicializacne funcie (alokuju cez New)                   €
€‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹€

SubMenu - definicia submenu s roznymi polozkami
 WinMenu - menu pre prikazy a spinace
 OptMenu - menu pre nastavenie premennych (Switch,Radio)
          a ich potvrdenie cez cmOK


WinMenu:
 Item    - spinac pre generovanie prikazu, tiez otec
 Switch1 - prepinac logickej premennej, navyse generuje spravu o prepnuti

OptMenu:
 Switch2    - prepinac logickej premennej
 RadioItem  - prepinac do jedneho zo stavov pre RadioItem
 Radio      - prepinac na jeden z viacerych stavov
}

{$I menus_f.inc}

{begin
  mnu_palette:= read_cfg_word(SYSTEMcfg,cfg_mnu_palette,1)<>0;
  mnu_mouse_scroll:= read_cfg_bool(SYSTEMcfg,cfg_mnu_mouse_scroll,true)}
end. { Menus }