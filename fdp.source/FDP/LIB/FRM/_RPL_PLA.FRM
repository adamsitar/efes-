{ =========================

   RPL

  תתתתתתתתתתתתתתתתתתתתתתתתת
}

 procedure image_RPL(x0,y0,x1,y1: int); far;
     begin
       BGIgraph.button(x0,y0,x1,y1, clBUTTON_COLOR+1, btSmall, btOFF);
       _lineh(x0+9,x0+320, y0+23,   clBUTTON_COLOR+1);
       _lineh(x0+9,x0+320, y0+44,   clBUTTON_COLOR+1);
       _lineh(x0+9,x1-10,  y0+77,   clBUTTON_COLOR+1);
       _lineh(x0+9,x1-10,  y0+149,  clBUTTON_COLOR+1);
     end;


 constructor TRPLform.Init(var _x,_y, _mode: int;
                           _tit : string;
                           _RPLi : PRPL;
                           _novy : bool
                          );
       begin
         fillchar(RPLn,sizeof(RPLn),0);
         new_RPL(_RPLi, @RPLn);

         inherited Init (_x,_y,_mode, _tit,
                         @form_RPL, size_RPLfrm, 0,
                         nil{@init_RPL}, @image_RPL, nil{@check_RPL},

                         @RPLn,nil, nil,user,'',

                         _novy, 0,nil,nil,
                         nil,nil,

                         nil,nil,
                         nil,@disp_RPL,

                         hlp_RPL
                        );

         novy:= _novy; { pretoze inherited predpoklada, ze ked prev=nil, tak je to novy plan... }
         ins:= _RPLi=nil;

         f_7a := i_rpl7a;
         f_13a:= i_rpl13a;
         f_15c:= i_rpl15c;

         {copy_back:= false;}
       end;


 destructor TRPLform.Done;
      begin
        inherited Done;
        disp_RPL(@RPLn);
      end;



{ ======================
   Naplnenie formulara
  ----------------------
}
 procedure TRPLform.init_formular; { inicializacia formulara  }
     begin
       inherited init_formular;
       {InfoCakaj(msgWAITING,'Initializing RPL..');}
       init_formular_by_data;
       {InfoCakaj_zatvor}
     end;

 procedure TRPLform.init_formular_by_data;
     var   i : int;
           s1,s2,s3 : string;
           c1,c2 : char;
           b1,b2 : bool;
           h,m   : byte;
           r : single;
           z,k : word;
           p : pchar;

     begin
       with RPLn do if _7a<>'' then
         begin
           clear_form(itemd,items,nil);

           _in(i_rplH,val);
           _in(i_rplI,zac);
           _in(i_rplJ,kon);
           for i:= low(dni) to high(dni) do _in(i_rplK1-1+i,dni[i]);

           _in(i_rpl7a,_7a);

           _in(i_rpl9b,_9b);
           _in(i_rpl9c,icao_NXT+_9c);

           _in(i_rpl13a,_13a);
           _in(i_rpl13b,_13b);

           _in(i_rpl16a,_16a);
           _in(i_rpl16b,_16b);

           p:= _15;
           if decode_l4_rych_vys_ (getstr(strpas(_15),1,[icao_NXIT]),r,c1, s1,b1, z,c2, s2,b2) then
              begin
                _in(i_rpl15a,_lat_FPL4(s1));
                _in(i_rpl15b,_lat_FPL4(s2));
                if get_ind(pchars(_15),strlen(_15),2,[icao_NXIT],z,k) then p:= @_15[z];
              end;
           init_pole(i_rpl15c, p);

           init_pole(i_rpl18, _18);

           itemd^[i_rpl7a].legal:= nil;
           itemd^[i_rpl13a].legal:= nil;
         end
       else clear_item_i(i_rpl7a)
     end;


{ ===============================
   Nacitanie udajov z formulara
  -------------------------------
}
 function  TRPLform.read_formular: bool;
    var    s : string;
           i : int;
    begin
      read_formular:= false;
      disp_RPL(@RPLn);

      with RPLn do
        begin
          val := getchar(_it(i_rplH));
          zac := _it(i_rplI);
          kon := _it(i_rplJ);
          for i:= low(dni) to high(dni) do dni[i]:= getchar(_it(i_rplK1-1+i));

          _7a := _it(i_rpl7a);

          _9b := _it(i_rpl9b);
          _9c := delchar(_it(i_rpl9c),[icao_NXT]);

          _13a:= _it(i_rpl13a);
          _13b:= _it(i_rpl13b);

          _16a:= _it(i_rpl16a);
          _16b:= _it(i_rpl16b);

          s:= _it(i_rpl15a)+_it(i_rpl15b);

          read_pole(i_rpl15c,_15);
          _15:= StrNPCopy(_15,s+icao_NXIT,false,true);

          read_pole(i_rpl18,_18);
        end;

      read_formular:= true
    end;


 function  TRPLform.check_formular: bool;
    var    res  : string;
           ires : int;
           cm   : word;
           FPL  : DFPL4;
    begin
      check_formular:= false;
      if not read_formular then Exit;

      InfoCakaj(msgWAITING,tit_FPL4_checking);
      cm:= cm_zarad_RPL or cm_decode_RPL_FPL4;
      if novy then cm:= cm or cm_check_RPL_KEY;

      code_RPL_to_FPL4_ (RPLn,FPL,false);
      _fpl4_date_all:= true;
      _fpl4_15_bxr_en:= true;
      ires:= _decode_FPL4 (FPL,true,res);
      disp_FPL4(@FPL);

      if res='' then _zarad_RPL (@RPLn, cm, true,user, res,ires)
      else begin
           { pretoze tu sa mozu kombinovat chyby od viacerych zdrojov,
             najma FPL4 a RPL, ktore maju rozne indexy poli, chyba
             sa nezobrazuje do pola indexu...
           }
             Err2('',res);
           end;

      InfoCakaj_zatvor;
      check_formular:= res='';
    end;

{
 procedure display_decoded_RPL (RPL: PRPL; void: word; var res: string; var ires: int);
     var   FPL : DFPL4;
           FDR : DFDR;
           FPLc: DcFPL;
     begin
       InfoCakaj(msgWAITING,'Decoding of RPL...');
       _decode_RPL (RPL^,FPL,FDR, false,res);
       InfoCakaj_zatvor;
       FDR_to_EST (FDR,FPLc);
       formular_cFPL (@FPLc,tit_decoded_FPL4+FPLc.idn,false,false,true,false);
       disp_FDR   (@FDR);
       disp_FPL4  (@FPL);
     end;

 function TRPLform.decode_15 (var res: string; var ires: int): bool;
    begin
      read_formular;
      display_decoded_RPL (@RPLn,0,res,ires);
      decode_15:= (res='') and (ires=0)
    end;
}

 function  formular_RPL_(RPL: PRPL; tit: string; novy: bool): bool;
    const  f    : Tcentr = (x: initX; y: initY; m: 1);
    var    form : PRPLform;
           E    : TEvent;
    begin
      form:= New(PRPLform,Init(f.x,f.y,f.m, tit, RPL, novy));
      form^.RunLocalFunc(E,FDPFormLocalMenu);
      formular_RPL_:= form^.corr_res;
      Dispose(form,Done)
    end;
