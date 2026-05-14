const SIPKA__VYSKA      = 10;
      ZNACKA__VYSKA     = 12;

      dxAr   = SCROLL_BAR__SIRKA shr 2 + 5;
      dyAr   = SIPKA__VYSKA;
      dx0pos = 2;
      dx1pos = dx0pos + ZNACKA__VYSKA + 2;


{ procedura ma opravit hranice lo a hi,
  aby sa nevypisovalo v zozname prazdne miesto
}
procedure check_hi(vypis_za_posl, vypis_posun: bool; var lo,hi, pos: int; top: int);
    var   pg: int;
    begin
      pg:= hi-lo;
      if (top>-1) then
         if (hi>top) then
            begin
            { nemozem vypisovat za poslednou polozkou }
             if (vypis_za_posl) then
                begin
                  {
                  if lo>top then
                     begin
                       hi:= hi-lo;
                       lo:= 0
                     end
                  }
                end
             else if (top<lo) or vypis_posun then
                begin
                  lo:= maximum(0,top-pg);
                  hi:= lo+pg;
                  pos:= hi
                end
            end
         else if vypis_posun then
                 begin
                   if top=hi then
                      begin
                        lo:= N(top-1);
                        hi:= top+pg;
                      end;
                   pos:= N(top)
                 end
    end;

{
 true znamena, ze sa posunuli hranice lo a hi
}
function set__scroll_pos(var lo,hi, pos: int; top, new_pos: int;
                         vypis_za_posl, vypis_posun: bool
                        ): bool;
   var   _max,prev_pos,page,i : int;
   begin
     page:= hi-lo;
     _max:= top; if vypis_za_posl then _max:= _max+page;
     new_pos:= Maximum(0,Minimum(_max,new_pos));  { 0<=new_pos<=top }
     if pos<>new_pos then
        begin
          prev_pos:= pos;
          if (new_pos<lo) or (new_pos>hi) then
             if (new_pos>hi) and vypis_za_posl then
                begin
                  inc(lo,new_pos-pos);
                  inc(hi,new_pos-pos)
                end
             else begin
                    lo:= N(lo+new_pos-pos);
                    hi:= lo + page
                  end;
          pos:= new_pos;
          check_hi(vypis_za_posl,vypis_posun and (prev_pos+1=new_pos), lo,hi,pos,top); { zmensit hi ? }
          set__scroll_pos:= true
        end
     else set__scroll_pos:= false
   end;  { set__scroll_pos }


{
 nastavi parametre scrollovacieho okna a scroll_bar-u;
 true znamena, ze sa posunuli hranice lo a hi
}
function is_scroll_key(kbXXXX: char): bool;
   begin
     is_scroll_key:= CtrlToArrow(kbXXXX) in setSCROLL
   end;


function set_scroll_par(kbXXXX: char;
                        var lo,hi, pos: int; top: int;
                        var cez: int; { -1,0,1 }
                        pos_en, smer : bool;
                        vypis_za_posl, vypis_posun : bool
                       ): bool;
   var   _pos, _max, page: int;
   begin
     if is_scroll_key(kbXXXX) then
        begin
          kbXXXX:= CtrlToArrow(kbXXXX);
          if not smer then
             case kbXXXX of
               kbUp   : kbXXXX:= kbDown;
               kbDown : kbXXXX:= kbUp;
               kbPgUp : kbXXXX:= kbPgDn;
               kbPgDn : kbXXXX:= kbPgUp;
             end;
          if not pos_en then
             if  kbXXXX in [kbUp,kbPgUp,kbHome,kbCtrlPgUp] then pos:= lo
             else pos:= hi;
          _pos := pos; page := hi-lo + 1; cez:= 0;
          case kbXXXX of
            kbUp   : if _pos>0 then Dec(_pos) else cez:= -1;
            kbDown : begin
                       _max:= top;
                       if vypis_za_posl then _max:= _max+page;
                       if _pos<_max then inc(_pos);
                       if _pos>top then cez:= +1
                     end;
            kbPgUp : if (_pos >= page) then Dec(_pos,page)
                     else begin _pos:= 0; cez:= -1 end;
            kbPgDn : if (top>=hi) or vypis_za_posl then
                        begin
                          _max:= top;
                          if vypis_za_posl then _max:= _max+page;
                          if (_pos+page<_max) then inc(_pos,page) else _pos:= _max;
                          if _pos>top then cez:= +1
                        end;
            kbHome,kbCtrlPgUp,kbCtrlHome : _pos:= 0;
            kbEnd,kbCtrlPgDn,kbCtrlEnd   : _pos:= top;
          end;
          set_scroll_par:= set__scroll_pos(lo,hi,pos,top,_pos, vypis_za_posl,vypis_posun)
        end
     else set_scroll_par:= false
   end; { set_scroll_par }


procedure receive__scroll_mail(var lo,hi,top,pos: int);
    var   p: pointer;
    begin
      p:= MailBox;            Move(p^,lo,  SizeOf(int));
      IncPtr(p,SizeOf(int));  Move(p^,hi,  SizeOf(int));
      IncPtr(p,SizeOf(int));  Move(p^,top, SizeOf(int));
      IncPtr(p,SizeOf(int));  Move(p^,pos, SizeOf(int));
    end;


{
 vypocita pocet poloziek na celu stranku pre scrollwin
}
function _set_page_size(_page,_top, _item_dy,_medzera,_dy: int): int;
   var   Y, val: word;
   begin
     Y:= MaxY - sc_dy - _dy;
     val:= Minimum((Y-btmdXY.y0-btmdXY.y1-30), 9*MaxY div 10) div (_item_dy+_medzera);
     {val:= val - (val div (ord(GraphMode)+1));}
     if _page<-1 then _set_page_size:= Minimum(_top+1,val)
     else _set_page_size:= val
   end;

function _get_scroller_size(_item_dx: int; var _dxi: int): word;
   begin
     if _dxi=0 then _dxi:= 4;
     _get_scroller_size:= _dxi + _item_dx + _dxi + 1
   end;

function _get_scroller_height(_page: int; _item_dy: int; var _dyi: int; _medzera: int): word;
   var   _dy: int;
   begin
     if _dyi=0 then _dyi:= 4;
     _get_scroller_height:= Maximum(_dyi + _page*(_item_dy+_medzera)-_medzera + _dyi + 1,
                                    dyAr + dx0pos + dx1pos + dyAr
                                   );
   end;

