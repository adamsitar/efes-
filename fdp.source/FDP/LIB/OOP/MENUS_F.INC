(*function do_(kolko: int): string;
   begin
     do_:= ' ('+{$IFNDEF A36YKA}'ó'{$ELSE}'<'{$ENDIF}+cstr(kolko,1)+')'
   end;
*)
function hk_(var ihk: int): char;
   var   ch: char;
   begin
     ch:= chr(ord('a')+ihk);
     if ch > 'z' then ch:= chr(ord('0')+(ord(ch)-ord('z')));
     hk_:= ch;
     inc (ihk)
   end;

function hk(var ihk: int): string;
   begin
     hk:= '~'+hk_(ihk)+'~) ';
   end;

function hki(var ihk: int): string;
   var   ch: char;
   begin
     ch:= chr(ord('1')+ihk);
     hki:= '~'+ch+'~.';
     inc (ihk)
   end;


procedure add_newline__(typ: int; nls: int; var nl,items: int; var smnu : TPItems);
    begin
      if nl < nls then
         begin
           smnu[items] := NewLine2(typ,nil);
           inc(items);
           inc(nl)
         end;
    end;

procedure add_newline_(typ: int; var nl,items: int; var smnu: TPItems);
    begin
      if nl < items then
         begin
           smnu[items] := NewLine2(typ,nil);
           inc(items);
           nl:= items;
         end;
    end;

procedure add_newline(var nl,items: int; var smnu : TPItems);
    begin
      add_newline_(0, nl,items,smnu);
    end;


function SubMenu(_title: string; _PMenu: PWinMenu; _Next: PItem): PSubMenu;
   begin
     SubMenu:= New(PSubMenu, Init(_title,_PMenu,_Next))
   end;

function SubMenu_(_title: string; _en_func: pointer; _en_bool: bool{;_is_func: bool}; _PMenu: PWinMenu;
                  _Next: PItem
                 ): PSubMenu;
   var   I: PSubMenu;
   begin
     I:= SubMenu(_title,_PMenu,_Next);
     I^.en_func:= _en_func;
     I^.en_bool:= _en_bool;
     {is_func:= _is_func};
     SubMenu_:= I
   end;


function SubMenuInitialized(SubMenu: PSubMenu; _Next: PItem): PSubMenu;
   begin
     if SubMenu<>nil then SubMenu^.Next:= _Next;
     SubMenuInitialized:= SubMenu
   end;

function AddItemToMenu(SubMenu: PSubMenu; _Next: PItem): PSubMenu;
   begin
     if (SubMenu<>nil) and (SubMenu^.PMenu<>nil) then SubMenu^.PMenu^.AddItem(_Next);
     AddItemToMenu:= SubMenu
   end;

function AddSubMenuToMenu(SubMenu: PSubMenu; _Next: PItem): PSubMenu;
   begin
     AddSubMenuToMenu:= AddItemToMenu(SubMenu,_Next);
     if SubMenu<>nil then SubMenu^.MoveRel(0,0)
    end;


function WinMenu(_title: string; _hlpXXX : Pchar; _FirstItem: PItem): PWinMenu;
   begin
     WinMenu:= New(PWinMenu, Init(_title,_hlpXXX, _FirstItem))
   end;

function WinMenu_S(_title: string; _hlpXXX : Pchar; _page: byte; _FirstItem: PItem): PWinMenu_S;
   begin
     WinMenu_S:= New(PWinMenu_S, Init(_title,_hlpXXX, cmDefault,_page, _FirstItem))
   end;


function OptMenu(_title: string; _hlpXXX : Pchar; _cmXXXX: word; _FirstItem: PItem): POptMenu;
   begin
     OptMenu:= New(POptMenu, Init(_title,_hlpXXX, _cmXXXX,_FirstItem))
   end;

function OptMenu_S(_title: string; _hlpXXX : Pchar; _cmXXXX: word; _page: byte; _FirstItem: PItem): POptMenu_S;
   begin
     OptMenu_S:= New(POptMenu_S, Init(_title,_hlpXXX, _cmXXXX,_page, _FirstItem))
   end;


function Item(_title: string; _cmXXXX: word; _Next: PItem): PItem;
   begin
     Item:= New(PItem, Init(_title,_cmXXXX,_Next))
   end;

function Item_(_title: string; _cmXXXX: word; _en_func: pointer; _en_bool: bool{;_is_func: bool};
               _Next: PItem
              ): PItem;
   var   I: PItem;
   begin
     I:= Item(_title, _cmXXXX, _Next);
     I^.en_func:= _en_func;
     I^.en_bool:= _en_bool;
     {is_func:= _is_func};
     Item_:= I
   end;

function Item2(_title: string; _kbHot: char; _cmXXXX: word; _Next: PItem): PItem;
   begin
     Item2:= New(PItem2, Init(_title,_kbHot,_cmXXXX,_Next))
   end;


function NewLine(_Next: PItem): PItem;
   begin
     NewLine:= New(PLine, Init(_Next))
   end;

function NewLine2(_sirka: byte; _Next: PItem): PItem;
   var   NL: PLine;
   begin
     NL:= New(PLine, Init(_Next));
     NL^.sirka:= _sirka;
     NewLine2:= NL
   end;

function NewTLine(_title: string; _Next: PItem): PItem;
   var   NL: PTextLine;
   begin
     NL:= New(PTextLine, Init(_title,_Next));
     NewTLine:= NL
   end;


function Switch1(_title: string; _cmXXXX: word; _check_adr: pointer; _Next: PItem): PSwitch1;
   begin
     Switch1:= New(PSwitch1, Init(_title,_cmXXXX,_check_adr,_Next))
   end;

function Switch1_(_title: string; _cmXXXX: word; _check_adr: pointer; _en_func: pointer; _en_bool: bool{;_is_func: bool};
                  _Next: PItem
                 ): PSwitch1;
   var   I: PSwitch1;
   begin
     I:= Switch1(_title,_cmXXXX,_check_adr,_Next);
     I^.en_func:= _en_func;
     I^.en_bool:= _en_bool;
     {is_func:= _is_func};
     Switch1_:= I
   end;


function Switch2(_title: string; _check_adr: pointer; _Next: PItem): PSwitch2;
   begin
     Switch2:= New(PSwitch2, Init(_title,_check_adr,_Next))
   end;

function Switch2_(_title: string; _check_adr: pointer; _en_func: pointer; _en_bool: bool{;_is_func: bool};
                  _Next: PItem
                 ): PSwitch2;
   var   I: PSwitch2;
   begin
     I:= Switch2(_title,_check_adr,_Next);
     I^.en_func:= _en_func;
     I^.en_bool:= _en_bool;
     {is_func:= _is_func};
     Switch2_:= I
   end;


function Switch0(_title: string; _cmXXXX: word; _check_adr: pointer; _Next: PItem): PSwitch0;
   begin
     Switch0:= New(PSwitch0, Init(_title, _cmXXXX, _check_adr, _Next))
   end;

function Switch0_(_title: string; _cmXXXX: word; _check_adr: pointer; _en_func: pointer; _en_bool: bool{;_is_func: bool};
                  _Next: PItem
                 ): PSwitch0;
   var   I: PSwitch0;
   begin
     I:= Switch0 (_title,_cmXXXX,_check_adr,_Next);
     I^.en_func:= _en_func;
     I^.en_bool:= _en_bool;
     {is_func:= _is_func};
     Switch0_:= I
   end;


function SwitchI(_title: string; _check_adr: pint; _unt: string; _imin,_imax: int; _Next: PItem): PSwitchI;
   begin
     SwitchI:= New(PSwitchI, Init(_title, _check_adr,_unt,_imin,_imax,_Next));
   end;

function SwitchI_(_title: string; _check_adr: pint; _unt: string; _imin,_imax: int;
                  _en_func: pointer; _en_bool: bool; {_is_func: bool;}
                  _Next: PItem
                 ): PSwitchI;
   var   I: PSwitchI;
   begin
     I:= SwitchI (_title,_check_adr, _unt,_imin,_imax, _Next);
     I^.en_func:= _en_func;
     I^.en_bool:= _en_bool;
     {is_func:= _is_func};
     SwitchI_:= I
   end;



function RadioItem(_title: string; _Next: PItem): PRadioItem;
   begin
     RadioItem:= New(PRadioItem, Init(_title,_Next))
   end;

function RadioItem_(_title: string; _en_func: pointer; _en_bool: bool{;_is_func: bool};
                    _Next: PItem
                   ): PRadioItem;
   var   I: PRadioItem;
   begin
     I:= New(PRadioItem, Init(_title,_Next));
     I^.en_func:= _en_func;
     I^.en_bool:= _en_bool;
     {is_func:= _is_func};
     RadioItem_:= I
   end;


function Radio(_title: string; _check_adr: pointer; _val_off: int; _FirstItem: PSwitch2; _Next: PSwitch2): PRadio;
   begin
     Radio:= New(PRadio, Init(_title,_check_adr,_val_off,_FirstItem,_Next))
   end;


