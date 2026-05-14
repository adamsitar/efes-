{ -----------------------
   editovanie stranky...
}
const ed_nic                = 0;
      ed_znak               = 1;
      ed_riadok             = 2;
      ed_strana             = 3;
      ed_pred_riadkom       = 4;
      ed_po_riadku          = 5;
      ed_nasledujuci_riadok = 6;


procedure TEditors.move_cursor({rdk,}nstl: int; nins: bool; res: int);
    var   bp : bool; xl,yl : int;
          co,bk: byte;
    begin
      m_off(bp, xl,yl);

      item_cl(pos=rdk, co,bk);
      hide_cursor(x0+dxi+dxioff, y0+dyi+dyioff, dx_ch,item_dy+medzera, 2,-2,
                  stl, rdk-lo,
                  pchr(r_s(rdk,stl, true))^ {strana^[rdk][stl+1]},
                  co,bk
                 );

      if (pos<>rdk) then item_list_pos(rdk);
     {if (res=ed_riadok) or (res=4) or (pos<>rdk) then item_list_pos(pos);}
      if (pos<>rdk) or (res>=ed_riadok) then item_list_pos(pos);
      item_cl(pos=rdk, co,bk);
      show_cursor(x0+dxi+dxioff, y0+dyi+dyioff, dx_ch,item_dy+medzera, 2,-2,
                  nstl,pos-lo,
                  pchr(r_s(pos,nstl, true))^ {strana^[pos][nstl+1]},
                  nins, co,bk
                 );

      ins:= nins; stl:= nstl; rdk:= pos;

      m_on(bp, xl,yl)
    end;


function TEditors.ClickedChar(var _Event: TEvent): bool;
   var   dx,nstl : int;
   begin
     if (not viewer) then with _Event do
       if TView.inView(M.x+(-Moff[M.curs].x),M.y+(-Moff[M.curs].y)) then
          begin
            dx:= item_dx div znakov;
            nstl:= Limit(((_Event.M.x-x0-dxi-dxioff) div (dx)), 0,znakov-1,0);
            {(((M.x+(dx div 2)+(-Moff[M.curs].x))-x0) div dx)-1}
            if nstl<>stl then move_cursor(nstl,ins,1);
            ClickedChar:= true
          end
       else ClickedChar:= false
   end;


function TEditors._AcceptedKey(var _Event: TEvent): bool;

   var   nstl, pg, res, i,z,k, cez : int;
         nins, bres : bool;


   { urci novu poziciu vo vypise
     a efektivny sposob obnovenia obsahu
     obrazovky
   }
   function  _ed_obnov: int;
       begin
         if      (lo_prev<>lo)  then res:= ed_strana
         else if (res<=ed_znak) then
                 begin
                   if      (pos<rdk)   then res:= ed_pred_riadkom
                   else if (pos>rdk)   then res:= ed_po_riadku
                   else if (nstl<>stl) then res:= ed_riadok
                   else res:= ed_znak
                 end;
         _ed_obnov:= res
       end;


   procedure _scroll_key(key: char);
       begin
         set_scroll_par(key, lo,hi, pos,top, cez, pos_en,smer,za_posl_en,false);
         _ed_obnov
       end;


   { nastavi sa na koniec riadku - za posledny znak<>' ',
     ak je to medzera, inak nan
   }
   function _koniec_riadku(_rdk: int; _mdzr: bool): int;
      var   _stl: int;
      begin
        _stl:= N(znakov-1);
        if (_rdk>=0) and (_rdk<riadkov) then
          while     (_stl>0)
                and (pchr(r_s(_rdk,_stl, true))^=' ') {(strana^[_rdk][_stl+1]=' ')}
          do dec(_stl);
        if     _mdzr
           and (pchr(r_s(_rdk,_stl, true))^<>' ')   {(strana^[_rdk][_stl+1]<>' ')}
           and (_stl<znakov-1) then inc(_stl);
        _koniec_riadku:= _stl
      end;


   { posun na dalsie slovo Tab, ShiftTab...
   }
   procedure _dalsie_slovo(o: int);
       var   _rdk,_stl: int;

       function _find_ch(o: int; skip: bool): bool;
          var   is_end : bool;
          begin
            repeat
              if (o>0) {or (not skip)} then
                 if (_stl<znakov-1) then inc(_stl)
                 else begin
                        if _rdk<riadkov-1 then
                           begin
                             inc(_rdk);
                             _stl:= 0
                           end
                      end
              else if (_stl>0) then dec(_stl)
                   else begin
                          if _rdk>0 then
                             begin
                               dec(_rdk);
                              _stl:= _koniec_riadku(_rdk,true)
                             end
                        end;

              is_end:=    (      skip
                            and (pchr(r_s(_rdk,_stl, true))^ in odd_slv)
                          )
                       or (     (not skip)
                            and (not (pchr(r_s(_rdk,_stl, true))^ in odd_slv))
                          )

            until    is_end
                  or ((_rdk=0) and (_stl=0))
                  or ((_rdk=riadkov-1) and (_stl=znakov-1));

            _find_ch:= is_end
          end;

      begin
        _rdk:= rdk; _stl:= stl;
        if _find_ch(o,true) then _find_ch(o,false);
        nstl:= _stl;
        if (_rdk<lo) or (_rdk>hi) then set__scroll_pos(lo,hi, pos,top, _rdk, za_posl_en,false)
        else pos:= _rdk;
        _ed_obnov
      end;


   procedure zmaz_riadok(r,od: int);
       var   p: pchar;
       begin
         p:= r_s(r,0,false);
         p^:= chr(znakov);
         p:= p + od+1;
         fillchar(p^,N(znakov-od),' ');
         res:= ed_riadok;
         is_chg:= true
       end;

   procedure zrus_riadok(od: int);
       var   i: int;
       begin
         for i:= od to riadkov-2 do
            move(pchr(r_s(i+1,0, false))^,
                 pchr(r_s(i,0, false))^,
                 znakov+1
                 );
         zmaz_riadok(riadkov-1,0);
       end;


   procedure odsun_riadok(rdk,stl: int; ins: bool);
       var   i : int;
             z : char;
       begin
         if rdk<riadkov-1 then
            begin
              if ins then
                 begin
                   for i:= riadkov-2 downto rdk+1 do move(pchr(r_s(i, 0, true))^, pchr(r_s(i+1,0, true))^, znakov);
                   zmaz_riadok(rdk+1,0);
                   move(pchr(r_s(rdk,stl,true))^,pchr(r_s(rdk+1,0, true))^,znakov-stl);
                   zmaz_riadok(rdk,stl);
                   res:= ed_po_riadku;
                   is_chg:= true
                 end
            end;
       end;


 { AcceptedKey :
   ------------
 } begin

     nins:= ins; nstl:= stl; {nrdk:= rdk;}
     pg:= hi-lo+1;
     res:= ed_znak;

     case CtrlToArrow(_Event.key) of

      {kbEsc         : res:= 0;}

      {kbCtrlEnter   : if call_check_func(_Event) then res:= 0;}

       kbIns         : nins:= not(ins);

       kbEnter       : if rdk < riadkov-1 then
                          begin
                            odsun_riadok(rdk,stl, ins);
                            _scroll_key(kbDown);
                            nstl:= 0
                          end;

       kbBS          : begin
                         if stl>0 then
                            begin
                              move(pchr(r_s(rdk,stl, true))^,    {strana^[rdk][stl+1]}
                                   pchr(r_s(rdk,stl-1, true))^,  {strana^[rdk][stl]}
                                   znakov-stl
                                  );
                              pchr(r_s(rdk,znakov-1, true))^:= ' '; {strana^[rdk][znakov-1]:= ' '}
                              nstl:= stl-1;
                              res:= ed_riadok;
                              is_chg:= true
                            end
                         else if rdk>0 then
                                 begin
                                 { ak je na zaciatku riadku, presunie aspon
                                   jeden znak na predchadzajuci riadok :
                                 }
                                   z:= _koniec_riadku(rdk-1,true);
                                   move(pchr(r_s(rdk,0, true))^,
                                        pchr(r_s(rdk-1,z, true))^,
                                        znakov-z
                                       );
                                   move(pchr(r_s(rdk,znakov-z, true))^,
                                        pchr(r_s(rdk,0, true))^,
                                        z
                                       );
                                   zmaz_riadok(rdk,z);
                                   if _koniec_riadku(rdk,true)=0 then zrus_riadok(rdk);
                                   nstl:= z {_koniec_riadku(rdk-1,true)};
                                   if rdk=lo then _scroll_key(kbUp)
                                   else pos:= N(rdk-1);
                                   res:= ed_strana;
                                   is_chg:= true
                                 end
                       end;

       kbDel         : begin
                         z:= _koniec_riadku(rdk,false);
                         if (z>0) and (stl<=z) then
                            begin
                              if (stl<znakov-1) then
                                 move(pchr(r_s(rdk,stl+1, true))^,
                                      pchr(r_s(rdk,stl,   true))^,
                                      znakov-1-stl
                                     );
                              pchr(r_s(rdk,znakov-1, true))^:= ' ';  {strana^[rdk][znakov]:= ' ';}
                              res:= ed_riadok;
                              is_chg:= true
                            end
                         else if rdk<riadkov-1 then
                                 begin
                                 { ak je za poslednynm znakom v riadku, vlozi po seba cast
                                   predchadzajuceho riadku :
                                 }
                                   move(pchr(r_s(rdk+1,0, true))^, {strana^[rdk+1][1]}
                                        pchr(r_s(rdk,stl, true))^, {strana^[rdk][j+1+1]}
                                        znakov-stl
                                       );
                                   move(pchr(r_s(rdk+1,znakov-stl, true))^, {strana^[rdk+1][j+1]}
                                        pchr(r_s(rdk+1,0, true))^, {strana^[rdk+1][1]}
                                        stl
                                       );
                                   zmaz_riadok(rdk+1,stl);
                                   if _koniec_riadku(rdk+1,false) = 0 then zrus_riadok(rdk+1);
                                   res:= ed_strana;
                                   is_chg:= true
                                 end
                       end;

       kbCtrlDel     : begin
                       { zmazanie celeho riadku
                       }
                         if cut_(_read_line_from_editor (rdk))<>'' then
                            begin
                              zmaz_riadok(rdk,0);
                              nstl:= 0;
                              res:= ed_riadok
                            end
                         else begin
                                zrus_riadok(rdk);
                                res:= ed_po_riadku
                              end;
                         is_chg:= true
                       end;

       kbAltDel      : begin
                       { zmazanie celeho formulara
                       }
                         clear_items;
                         res:= ed_strana
                       end;

       kbLeft        : if stl>0 then nstl:= N(stl-1)
                       else if rdk>0 then
                            begin
                              nstl:= _koniec_riadku(pos-1,true);
                              _scroll_key(kbUp)
                            end;

       kbRight       : if stl<znakov-1 then nstl:= minimum(stl+1,znakov-1)
                       else if rdk<riadkov-1 then
                            begin
                              _scroll_key(kbDown);
                              nstl:= 0
                            end;

       kbCtrlLeft,kbShiftTab   : _dalsie_slovo(-1);
       kbCtrlRight,kbTab       : _dalsie_slovo(+1);

       kbHome,kbCtrlHome       : nstl:= 0;
       kbEnd,kbCtrlEnd         : nstl:= _koniec_riadku(rdk,true);

       kbUp, kbDown, kbPgUp,kbPgDn, kbCtrlPgUp,kbCtrlPgDn, kbCtrlHome,kbCtrlEnd
                     : {begin
                         _scroll_key(_Event.key);
                         case CtrlToArrow(_Event.key) of
                           kbCtrlPgUp,kbCtrlPgDn,kbCtrlHome : nstl:= 0;
                           kbCtrlEnd : nstl:= znakov-1
                         end
                       end}

       else if not (_Event.key in setNOKEY) then
            begin
              res:= ed_riadok;
              is_chg:= true;

              _Event.key:= kblayout(_Event.key);
              if upcas then _Event.key:= upcase(_Event.key);

              if ins then
                 begin
                 { odsunutie zvysku textu
                 }
                   if pchr(r_s(rdk,znakov-1, true))^<>' ' then
                      begin
                      { posledny znak riadku je <> ' ',
                        odsunie sa nasledujuci text
                        na novy riadok
                      }
                        if rdk<riadkov-2 then
                           begin
                             if pchr(r_s(rdk+1,znakov-1, true))^<>' ' then
                                begin
                                { odsunutie i druheho riadku
                                  a vytvorenie prazdneho riadku
                                }
                                  odsun_riadok(rdk,znakov-1, ins);
                                  res:= ed_po_riadku
                                end
                             else begin
                                    move(pchr(r_s(rdk+1,0, true))^,pchr(r_s(rdk+1,1, true))^,znakov-1);
                                    move(pchr(r_s(rdk,znakov-1, true))^,pchr(r_s(rdk+1,0, true))^,1);
                                    res:= ed_nasledujuci_riadok
                                  end
                           end
                       end;
                   if (stl<znakov-1) then
                      begin
                        move(pchr(r_s(rdk,stl, true))^,   {strana^[rdk][stl+1]}
                             pchr(r_s(rdk,stl+1, true))^, {strana^[rdk][stl+2]}
                             znakov-stl-1
                            );
                      end
                 end;

            { zapis vlozeneho znaku
            } pchr(r_s(rdk,stl,true))^:= _Event.key; {strana^[rdk][stl+1]}
              nstl:= limit(stl+1, 0,znakov-1, 0);
              if (nstl=stl) and (rdk<riadkov-1) then
                 begin
                  { koniec riadku
                  } _scroll_key(kbDown);
                   nstl:= 0
                 end
            end
         else res:= ed_nic
     end;

     if res <> ed_strana then
        begin
         { aktualizacia editaciou postihnutych casti textu
           (znakov, riadku, alebo riadkov)
         }
          if res > ed_riadok then
             begin
               if      res=ed_pred_riadkom then begin z:= lo; k:= minimum(rdk,hi) end
               else if res=ed_po_riadku then begin z:= maximum(rdk-1,lo); k:= hi end
               else if res=ed_nasledujuci_riadok then begin z:= maximum(rdk-1,lo); k:= z+1 end
               else k:= -1;
               while (k>z) and (cut_(_read_line_from_editor(k))='') do dec(k);
               for i:= z to k do item_list(i, get_x,get_yi(i), {$IFNDEF EDD} (pos_en) and {$ENDIF} (i=pos))
             end;

         { aktualizacia ukazatela polohy v editore
         }
          sb^.param(lo,hi,top,pos, true);

         { aktualizacia aktualneho riadku
         }
          move_cursor(nstl,nins,res);
        end;
     ins:= nins; rdk:= pos; stl:= nstl;

     if res=ed_strana then
        begin
        { aktualizacia celeho zoznamu
        }
          pos_prev:= -1;
          List
        end;

      mark_pos;

     _AcceptedKey:= res<>ed_nic
   end;


function TEditors.AcceptedKey(var _Event: TEvent): bool;
   begin
     if viewer then AcceptedKey:= false
     else AcceptedKey:= _AcceptedKey(_Event)
   end;


function TEditors._call_check_func: bool;
   var   res: bool;
   begin
     if (text_adr<>nil) and (check_func<>nil) then res:= TBFunc_p3(check_func)(@Self,handler_owner,text_adr)
     else res:= true;
     _call_check_func:= res
   end;

function TEditors.call_check_func: bool;
   begin
     read_from_editor;
     call_check_func:= _call_check_func
   end;


{ prepinanie medzi view/edit
}
procedure TEditors.functionality(_viewer: bool);
    begin
      if _viewer=viewer then Exit;
      viewer:= _viewer;
      if not viewer then begin pos:= 0; stl:= 0 end;
      pos_prev:= -1;
      List
    end;
