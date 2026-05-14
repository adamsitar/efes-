{ "-2" kvoli kurzoru, ktory sa vykresluje nad riadok nastaveny
  na idem_dy=10
}
 procedure WriteStr(x,y: int; S: string; cl,bg: byte);
     begin
       SetTextJustify(LeftText,TopText);
       {$IFDEF BGI} FillWin(x-1,y-2,x+TextWidth(S)-1,y+TextHeight('H'), bg); {$ENDIF}
       {$IFDEF SPEA} SetBkColor(bg); {$ENDIF}
       SetColor(cl); OutTextXY(x,y,S)
     end; { WriteStr }

{
 vymazanie nepotrebnych znakov - cislic z formulara
 volat pre kazdy prototyp formulara na zaciatku programu
}
procedure delete_item(var itemd: TForm);
    var   j: int;
    begin
      with itemd do
         for j:= 0 to StrLen(item)-1 do
             if not(item[j] in skip^) then item[j]:= ' '
    end;

procedure clear_form(_itemd: PForms; _items: byte; _init: PCharSet);
    var   i,j: int;
          S: string;
    begin
      for i:= 0 to _items-1 do with _itemd^[i] do
          if _itemd^[i].legal<>@setNil then
             begin
               j:= 1; S:= StrPas(item);
               while (j<=Length(S)) do
                 begin
                   if (not (S[j] in skip^)) and ((_init=nil) or (not (S[j] in _init^)) ) then S[j]:= ' ';
                   Inc(j)
                 end;
              {S:= ReplChar(S,[kbCRLF],' ');}
               StrPCopy(item, S);
             end
    end;

{
 nastavi res (index polozky) a kod (kod chyby) pri kontrole v check_func
}
procedure set_rk(var erra: string; _erra: string;
                 var errc: int; _errc: int;
                 var ires: int; _ires: int
                );
    begin
      erra:= _erra;
      errc:= _errc;
      ires:= _ires;
    end;

function chg_legal_set(var CharSet: PCharSet; Value: PCharSet): PCharSet;
   begin
     chg_legal_set:= CharSet;
     CharSet:= Value
   end;


function  alloc_form (items: byte): PForms;
   var    _itemd : PForms;
   begin
     GetMem(_itemd,sizeof(TForm)*items);
     FillChar(_itemd^,sizeof(TForm)*items,0);
     alloc_form:= _itemd
   end;

procedure acpy_form(itemd1,itemd2: PForms; items: byte);
   var    i : int;
   begin
     for i:= 0 to items-1 do
         begin
           itemd2^[i]:= itemd1^[i];
           itemd2^[i].item := StrNew(itemd1^[i].item);
           itemd2^[i].title:= StrNew(itemd1^[i].title)
         end;
   end;

function  new_form (itemd: PForms; items: byte): PForms;
   var    _itemd : PForms;
          i      : int;
   begin
     _itemd:= alloc_form(items);
     acpy_form(itemd,_itemd, items);
     new_form:= _itemd
   end;

procedure disp_form (itemd: PForms; items: byte);
    var   i : int;
    begin
      for i:= 0 to items-1 do
          begin
            StrDispose(itemd^[i].item);
            StrDispose(itemd^[i].title)
          end;
      FreeMem(itemd,sizeof(TForm)*items)
    end;

procedure copy_form(itemd1,itemd2: PForms; items: byte);
   var    i,k,l : int;
   begin
     for i:= 0 to items-1 do
       begin
         StrLCopy(itemd2^[i].item,itemd1^[i].item,minimum(StrLen(itemd2^[i].item),StrLen(itemd1^[i].item)))
       end
   end;
