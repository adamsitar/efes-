 type   PALRform = ^TALRform;
        TALRform = object(TFPL4form)

          aitemd : PForms;
          aitems : int;

          prty,adr : string;

          constructor Init (_FPLi : PFPL4; _tit : string; var f : Tcentr);
          destructor  Done; virtual;

          procedure   init_formular_by_stat; virtual;
          procedure   init_formular; virtual;
          procedure   write_in_formular; virtual;

          function    read_formular: bool;  virtual;
          function    check_formular: bool; virtual;
        end;



 procedure image_ALR(x0,y0,x1,y1: int); far;
     begin
       image_TLGadr(x0,y0,x1,y1);
       _lineh(x0+9,x0+320, y0+ 98,  clBUTTON_COLOR+1);
       _lineh(x0+9,x1-13,  y0+133,  clBUTTON_COLOR+1);
       _lineh(x0+9,x1-13,  y0+204,  clBUTTON_COLOR+1);
       _lineh(x0+9,x1-13,  y0+255,  clBUTTON_COLOR+1);
     end;


 constructor TALRform.Init(_FPLi : PFPL4; _tit : string; var f : Tcentr);
       var   i : int;
             s : string;
             _kbHot : char;
       begin
         if _tit='' then _tit:= tit_fpl_alr;
         if _FPLi<>nil then _tit:= _tit+' - '+decode_l4_7a(_FPLi^._7);

       { vytvorenie formulara pre ALR spojenim dvoch
         existujucich formularov frmFPL4 a tlgFPL4
       }
         aitems:= size_TLGadr+size_FPL4alr;
         aitemd:= alloc_form (aitems);
         o_f:= size_TLGadr;
         acpy_form(@form_TLGadr[0], @aitemd^[0],   size_TLGadr);
         acpy_form(@form_FPL4  [0], @aitemd^[o_f], size_FPL4alr);
         inc(aitemd^[o_f+i_3a].dy,dy_TLGadr+5);
         for i:= o_f+i_5a   to o_f+i_5c do inc(aitemd^[i].dy,dy_TLGadr);
         for i:= o_f+i_5c+1 to aitems-1 do inc(aitemd^[i].dy,dy_TLGadr+15);

         inherited Init(f.x,f.y,f.m, _tit,
                        aitemd,aitems,size_TLGadr,
                        _FPLi,letvis,hd_ALR,
                        _FPLi=nil
                       );

         p_image_form:= @image_ALR;
         {p_process := @p_add_ALR;}
         copy_back:= false;

         if btOK<>nil then
            begin
              with btOk^ do new_title(' '+titSEND+' ',false);
              btOk^.kbHot:= kbCtrlEnter;
              btOk^.kbAltHot:= GetAltCode(get_HotKey(_kbHot,titSEND))
            end;

         if (cut_(getstr(FPLn^._7,1,[icao_NXT]))<>'') then first_pos:= o_f+1
         else first_pos:= o_f+1
       end;


destructor TALRform.Done;
     begin
       inherited Done;
       disp_form (aitemd,aitems);
     end;


{ ---------------
  Naplnenie
  ---------------
}
 procedure TALRform.init_formular_by_stat;
     var   i  : int;
           s  : string;
     begin
       inherited init_formular_by_stat;
       for i:= o_f+i_5a to items-1 do itemd^[i].legal:= form_FPL4[i-o_f].legal;

       if (cut_(getstr(FPLn^._7,1,[icao_NXT]))<>'') then
          begin
            itemd^[o_f+i_7a].legal := nil;
            itemd^[o_f+i_13a].legal:= nil;
            itemd^[o_f+i_13b].legal:= nil
          end
     end;


 procedure TALRform.init_formular; { inicializacia formulara  }
     var   is  : bool;
           i,k : int;
           s,idn,ssr : string;
           fpl : PFPLC;
     begin
       inherited init_formular;

       _in(o_f+i_5b,icao_NXT+_lat_TLG(ADR_O_THIS));
       _in(o_f+i_5c,icao_NXT);


     { a) Naplnenie FPL
     }
       idn:= decode_l4_7a(FPLn^._7);
       is:= cut_(idn)<>'';

       if is then
         begin
           _in(o_f+i_5a,_lat_TLG(getPstr(FPLn^._5,1,[icao_NXT])));
           _in(o_f+i_5c,icao_NXT+_lat_TLG(getPstr(FPLn^._5,3,[icao_NXT])));

           {if (DEV_AFTN<>nil) then
              begin
                s:= icao_NXT+system.copy(DEV_AFTN^.NODE_THIS,1,7)+'X';
                with itemd^[i_5b] do StrPICopy(item, s, strlen(item))
              end
           }

          { Co ked informacia o SSR je stara ?
          }
           fpl:= find_FPLCa (codekey_FPL4(FPLn));
           if fpl<>nil then ssr:= fpl^.ssr
           else ssr:= '';
           _in(o_f+i_7c,ssr);

           init_pole(o_f+i_19, FPLn^._19);
           init_pole(o_f+i_20, FPLn^._20);
         end;

       if {(not is) or (_20=nil)} cut_(_it(o_f+i_20))='' then
          begin
            {if cut_(_it(o_f+i_20))='' then}
               begin
                 _in(o_f+i_20,
                                  rmk_UTC + icao_NXT+code_l4_utc(hour,min)
                      + icao_NXIT+rmk_PNT + icao_NXT+'                       '
                    )
               end;

            {if cut_(_it(o_f+i_20+1))='' then}
               begin
                 _in(o_f+i_20+1,rmk_KIND+icao_NXT)
               end;

            {if cut_(_it(o_f+i_20+2))='' then}
               begin
                 _in(o_f+i_20+2,rmk_RMK+icao_NXT)
               end
          end;

     { b) Naplnenie adresatov
     } init_tlg_adr(stat,@Self,0)

     end;

 procedure TALRform.write_in_formular;
     begin
     end;


{ ---------------
  Spracovanie
  ---------------
}
 function TALRform.read_formular: bool;
    var   bres: bool; res: string; i,ires: int;
          _5a,_5b,_5c: string;
          FDR : DFDR;
          dd  : TFDR_decoded_data;

    label X,N;

    begin
      read_formular:= false;

      res:= ''; ires:= -1;
      (* kontrola na spravnost
       _5a:= ith itemd^[o_f+i_5a] do StrPICopy(item,          _lat_FPL(getPstr(_5,1,[icao_NXT])), strlen(item));
               with itemd^[o_f+i_5b] do StrPICopy(item, icao_NXT+_lat_FPL(getPstr(_5,2,[icao_NXT])), strlen(item));
               with itemd^[o_f+i_5c] do StrPICopy(item, icao_NXT+_lat_FPL(getPstr(_5,3,[icao_NXT])), strlen(item))
      *)

     { a) nacitanie adries
     } res:= read_tlg_adr(@Self, o_f, prty,adr, res,ires);
       if res='' then
          begin
          { b) nacitanie dat
          } bres:= inherited read_formular;

            if bres then with FPLn^ do
               begin
                 fillchar(FDR,sizeof(FDR),0);
                 fillchar(dd,sizeof(dd),0); dd.check_en:= true;

                 _5a:= cut_(delchar(_it(o_f+i_5a),[icao_NXT]));
                 if _5a='' then ires:= l4_err(a_TLG,_5a, i_5a,10, res);
                 if (res='') and (not _in_list(_5a,@fn_5a,[';'],1,nil)) then ires:= l4_err(a_5a,_5a, i_5a,0, res);
                 if res<>'' then goto X;

                 _5b:= cut_(delchar(_it(o_f+i_5b),[icao_NXT]));
                 if _5b='' then begin ires:= l4_err(a_TLG,'', i_5b,10, res); goto X end;

                 _5c:= cut_(delchar(_it(o_f+i_5c),[icao_NXT]));
                 if _5c='' then begin ires:= l4_err(a_TLG,'', i_5c,10, res); goto X end;

                 strdispose(_5);
                 _5 := strpasnew(format_s(_5a) + icao_NXT+ format_s(_5b) + icao_NXT+ format_s(_5c));

                 ires:= _decode_FPL4_DATA (FPLn^,FDR, dd,res);
                 if res<>'' then goto N;

                 strdispose(_19);
                 strdispose(_20);
                 for i:= 0 to max_FPL4_19_r_hi-1 do _19:= StrNPCopy(_19,_it(o_f+i_19+i)+kbNL,true,true);
                 for i:= 0 to max_FPL4_20_r_hi-1 do _20:= StrNPCopy(_20,_it(o_f+i_20+i)+kbNL,true,true);

                 {if FPLn._19=nil then ires:= l4_err(a_19,'',i_19,1, res)
                 else} if FPLn^._20=nil then ires:= l4_err(a_20,'',i_20,1, res);
                 N: disp_FDR(@FDR)
               end;
          end;

      X: if res<>'' then
         if ires<0 then Err2('',res)
         else ErrorS(o_f+ires,res);

      read_formular:= bres and (res='')
    end;


 function TALRform.check_formular: bool;
    var   bres: bool;
          ires,is,i: int;
          idn,res,ssr,s: string;
    begin
      prty:= ''; adr:= ''; res:= '';
      bres:= read_formular;
      if bres then
         begin
           {$IFDEF EXTERNAL_NET}
            for i:= 0 to EXT_DEVICESpoc-1 do
              if EXT_DEVICES[i]^.is_4444 then
                 PO_L4444(EXT_DEVICES[i])^.send_ALR(FPLn^,''{codekey_FPL4(FPL)},0{spr_FPL4},adr);
           {$ENDIF}
           (*
           {if      process_ALR_to_FPL4
              and (   cut_(getstr(FPLp.idn,1,[icao_NXT]))='')
                   or in_icao_head (FPLp.head, ms_ICAOplan, true)
                  ) then
              begin
                FPLn.stt:= hd_FPL
              end};

           decode_l4_7  (FPLn^._7, idn,s,ssr);
           if (idn<>'') and (FPLn^._13<>'') and (FPLn^._15<>nil) then
              if process_ALR_to_FPL4 then
                 begin
                   if (idn<>'') and (ssr='') then
                      begin
                      { priradenie SSR kodu, ak je aktivny
                      } ssr:= ssr_of_idn (idn,'');
                        FPLn._7:= idn+icao_NXT+ssr;
                      end;
                   if (idn<>'') then p_add_FPL4(@FPLn,zarad_FPL4_EST,res,ires)
                 end
              else save_FPL4(FPLn)
           *)
           {if FPLp<>nil then save_FPL4(FPLn)}
         end;

      {if (res<>'') then
         if ires<0 then Err2('',res)
         else ErrorS(o_f+ires,res);}

      check_formular:= bres
    end;


 procedure  formular_ALR(_FPLi: PFPL4);
     const  f     : Tcentr = (x: initX; y: initY; m: 1);
     var    form  : PALRform;
            Ev    : TEvent;
     begin
       form:= New(PALRform,Init(_FPLi,tit_fpl_alr,f));
       form^.RunLocalFunc(Ev,FDPFormLocalMenu);
       Dispose(form,Done)
     end;