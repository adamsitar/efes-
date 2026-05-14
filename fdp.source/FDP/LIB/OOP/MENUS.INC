{
  Ako funguje?
   - Item nevysiela command cez Mail ale zapise ho do _Event
   - SubMenu spusti pirslusne menu cez "Run"
}
function _ct_(is_active,is_enabled: bool): byte;
   begin
     if is_enabled then _ct_:= cl_Item[mnu_palette,is_active]
     else _ct_:= {$IFDEF EGAVGA}lightgray{$ELSE}clBUTTON_COLOR+4{$ENDIF}
   end;

function _ck_(is_active,is_enabled: bool): byte;
   begin
     if is_enabled then _ck_:= cl_Key[mnu_palette,is_active]
     else _ck_:= {$IFDEF EGAVGA}lightgray{$ELSE}clBUTTON_COLOR+4{$ENDIF}
   end;

function _bk_(is_active,is_enabled: bool): byte;
   begin
     if is_enabled then _bk_:= bk_Item[mnu_palette,is_active]
     else _bk_:= clBUTTON_COLOR
   end;

(*
function _cts_(is_active,is_enabled: bool): byte;
   begin
     if is_enabled then _ct_:= cl_Item[mnu_palette,is_active]
     else _ct_:= {$IFDEF EGAVGA}lightgray{$ELSE}clBUTTON_COLOR+4{$ENDIF}
   end;

function _cks_(is_active,is_enabled: bool; stat: TbtStat): byte;
   begin
     if is_enabled then _ck_:= cl_Key[mnu_palette,is_active]
     else _ck_:= {$IFDEF EGAVGA}lightgray{$ELSE}clBUTTON_COLOR+4{$ENDIF}
   end;

function _bks_(is_active,is_enabled: bool; stat: TbtStat): byte;
   begin
     if is_enabled then _bk_:= bk_Item[mnu_palette,is_active]
     else _bk_:= clBUTTON_COLOR
   end;


function _cts(act,en: bool): byte;
   begin
     if en then
        if act then _cts:= clActItem
        else _cts:= clItem
    else if act then _cts:= clBUTTON_COLOR+4
         else _cts:= clBUTTON_COLOR+2
   end;

function _cks(act,en: bool): byte;
   begin
     if en then
        if act then _cks:= clActKey
        else _cks:= clKey
     else if act then _cks:= clBUTTON_COLOR+4
        else _cks:= clBUTTON_COLOR+2
   end;
*)