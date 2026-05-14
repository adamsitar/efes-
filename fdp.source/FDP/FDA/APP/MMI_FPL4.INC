{$IFDEF PROCESS_FPL4}

 const dxi = 3;
       dyi = 4;


 function handle_item_FDR (var Ev: TEvent; sc: PScrollInd; FDRi: PFDR): bool; far;
    begin
      handle_item_FDR:= _handle_o_FDR_list (Ev,sc,FDRi,-123,-12)
    end;

 function handle_item_EST (var Ev: TEvent; sc: PScrollInd; FPLi: PDcFPL): bool; far;
    var   dx,dy : int;
    begin
      handle_item_EST:= _handle_plan_FPLC(Ev, FPLi,nil, sc,-123,-12, false,false);
    end;

 function is_FDRact (FDR: PFDR; p: pointer): bool; far;
    begin
      is_FDRact:= FDR^.poz in pozACT
    end;


 procedure item_FDR_(x,y: int; b: bool;
                     idn,bod: string;
                     h,m: byte;
                     poz: TPoz;
                     src: Tfplsrc
                    );
     var   dx,bi : int;
     begin
       if b then BGIgraph.button(x-1,y,x+dx_FDR_item,y+dy_FDR_item,itScrollApp, btSmall,btOFF)
       else FillWin(x-1,y,x+dx_FDR_item,y+dy_FDR_item, bkScrollApp);

       if fpl_approved(src,_FPL4_APROVED_DISPLAY) then bi:= pozCL[poz] else bi:= red;
       SetColor (bi);
       outtextxy(x,   y+1, _lat_FPL4(idn)); dx:= (kod_7a+1) shl 3;
       if bod<>'' then
          begin
            outtextxy(x+dx,y+1, _lat_FPL4(bod)); inc(dx,(kod_NDB shl 3)+4);
            if m<>60 then outtextxy(x+dx,y+1, code_l4_utc(h,m))
          end;
     end;

 procedure item_FDR (FDR: PFDR; x,y: int; b: bool); far;
     begin
       with FDR^ do item_FDR_(x,y,b, idn,eet.kod,eet.h,eet.m, poz, src)
     end;

 procedure item_EST (FPL: PDcFPL; x,y: int; b: bool); far;
     var   bod : string[kod_NDB];
           h,m : byte;
     begin
       if FPL^.bodov>0 then
          begin
            bod:= FPL^.trat[0].kod;
            h:= FPL^.trat[0].h;
            m:= FPL^.trat[0].m;
          end
       else begin
              bod:= FPL^.start.kod;
              h:= FPL^.start_.h;
              m:= FPL^.start_.m;
            end;
       item_FDR_(x,y,b, FPL^.idn,bod,h,m, FPL^.poz, fplsrc_PLN)
     end;


 procedure init_FPL4mmi (_Owner: PGroup);
     begin
       {FPL4prea:=  New(PScrollApp_FDP,Init(_Owner,

                        '~P~R~EACTIVED',
                        oFDR,nil,@is_FDRprop,
                        @comp_xxx_FDR,

                        4,dy_ScrollApp, dx_FDR_item,dy_FDR_item,
                        dxi,dyi,1,bkScrollApp,
                        @item_FDR,
                        1, true,true,true,

                        _TBFunc_vEp2, @handle_item_FDR, nil,
                        @tab_FPL4prea,
                        cmSetactive,
                        nil)
                      );}


       FPL4prop:=  New(PScrollApp_FDP,Init(_Owner,

                        'P~R~OPOSED   ',
                        oFDR,nil,@is_FDRcoor,
                        @comp_xxx_FDR,

                        4,dy_ScrollApp, dx_FDR_item,dy_FDR_item,
                        dxi,dyi,1,bkScrollApp,
                        @item_FDR,
                        1, true,true,true,

                        _TBFunc_vEp2, @handle_item_FDR, nil,
                        @tab_FPL4prop,
                        cmSetactive,
                        nil)
                      );


       {FPL4coor:= New(PScrollApp_FDP,Init(_Owner,

                        'C~O~ORDINATED',
                        oFDR,nil,@is_FDRcoor,
                        @comp_xxx_FDR,

                        4,dy_ScrollApp, dx_FDR_item,dy_FDR_item,
                        dxi,dyi,1,bkScrollApp,
                        @item_FDR,
                        1, true,true,true,

                        _TBFunc_vEp3, @handle_item_FDR, @c_true,
                        @tab_FPL4coor,
                        cmSetactive,
                        nil)
                      );}

      { Kym nezjednotime FPLc,FPLm a FPL4 do FDR/FPL4
        je tu trochu zmatok, lebo pouzivam namiesto FDR
        starsi FPLc
      }
       FPL4coor := New(PScrollApp,Init(_Owner,

                        'C~O~ORDINATED',
                        cFPL^.ap,@cFPL^.top, true,
                        @cFPL^.is_chg,@cFPL^.arr_chg, @cFPL^.s_loadDB,
                        0,nil,nil,
                        nil,nil{@is_FPLactive},@comp_idn_cFPL,

                        4,dy_ScrollApp, dx_FDR_item,dy_FDR_item,
                        dxi,dyi,1,bkScrollApp,
                        @item_EST,
                        1, true,true,true,

                        _TBFunc_vEp2, @handle_item_EST, nil,
                        @tab_FPL4coor,
                        cmSetactive,
                        nil)
                      );

     end;


 function  reinit_FPL4mmi(x,y,dx,dy: int): int;
     var   y0a,y0b,y0c, page, pocet: int;
     begin
       {FPL4prea^.hide;}
       FPL4prop^.hide;
       FPL4coor^.hide;
       pocet:= {(ord(tab_FPL4prea) and 1) +} (ord(tab_FPL4prop) and 1) + (ord(tab_FPL4coor) and 1);
       if pocet<>0 then
          begin
            x:= dx - (FPL4prop^._win_.x1 - FPL4prop^._win_.x0);
            dy  := (dy {MaxX} - (btmdXY.y0+btmdXY.y1+3)) div pocet;
            y0a := btmdXY.y0;
            y0b := y0a {+ dy * ( ord(tab_FPL4prea) and 1)};
            y0c := y0a + dy * ({(ord(tab_FPL4prea) and 1) +} (ord(tab_FPL4prop) and 1));
            page:= (dy-winHEIGHT-6) div (FPL4prop^.item_dy + FPL4prop^.medzera);
            {FPL4prea^.reinit_(x,y0a, page);}
            FPL4prop^.reinit_(x,y0b, page);
            FPL4coor^.reinit_(x,y0c, page);
            {set_region(0,btmdXY.y0,MaxX-x+4,btmdXY.y1, btMapydXY)
            }
          end
       else x:= dx;
       reinit_FPL4mmi:= x
     end;

{$ENDIF}
