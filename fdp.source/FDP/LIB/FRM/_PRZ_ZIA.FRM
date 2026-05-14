{ -------------------------
   Inicializacia formulara
  -------------------------
}
 procedure _init_formular_by_data(form: PFDP_AForm; PRZ: PPRZ); far;
     var   l,i : int;
           d : TDate;
     begin
       with form^ do
         begin
           if ((form^.arch) and (PRZ^.dap.rok<>0)) or (PRZ^.dap.rok<>0) then with PRZ^ do
              begin
                _in (it_NTM, strpas(_NTM));

                for i:= 0 to max_Q-1 do _in (it_Q+i*2, getPstr(_Q,i+1,[icao_NXT]));

                _in (it_A, _A);

                _in (it_B, _B);
                _in (it_C, _C);

                init_pole (it_D, _D);
                init_pole (it_E, _E);

                _in (it_F, _F);
                _in (it_G, _G);

                form^.first_pos:= it_D;
              end
           else begin
                  _in (it_NTM, strpas(PPRZ(form^.adr_var)^._NTM));
                  _in (it_Q, FIR_adr);
                  {$IFDEF AIRBASE}
                   _in (it_A, _cairbase(airbase));
                  {$ENDIF}
                  form^.first_pos:= it_B;
                end
         end
     end;

 procedure _init_formular_by_stat(form: PFDP_AForm); far;
     begin
       if (form^.adr_data<>nil) and (PPRZ(form^.adr_data)^.dav.r<>0) and (not form^.arch) then
          begin
          end;
     end;

 procedure _PRZ_init(form: PFDP_AForm; PRZ: PPRZ); far;
     begin
       _init_formular_by_data(form,PPRZ(form^.adr_var));
       _init_formular_by_stat(form)
     end;


 procedure _PRZ_image(x0,y0,x1,y1: int); far;
     begin
       _plan_PRZ(x0,y0,x1,y1, clBUTTON_COLOR+1, max_NTM_D_r_hi,max_NTM_E_r_hi, true)
     end;


{ -------------------------
   Spracovanie formulara
  -------------------------
}

function _PRZ_check(form: PFDP_AForm; PRZ: PPRZ): bool; far;

   var   res,s  : string;
         ires,i : int;
         r1,r2: word; m1,m2,d1,d2: byte;

   label X;

   begin
     res:= ''; ires:= -1;
     disp_PRZ(PRZ);

     with form^,PRZ^ do
       begin

        { Identifikacia
        }
         _NTM := strpasnew(_it(it_NTM));

         s:= ''; for i:= 0 to max_Q-2 do s:= s + _it(it_Q+i*2)+icao_NXT;
         s:= s + _it(it_Q+(i+1)*2);
         _Q:= strpasnew(s);


         if let='' then
            begin
             {$IFDEF AIRBASE}
               let:= airbase; {let:= NETadr_wan (NETaddress); zdroj planu }
             {$ENDIF}
            end;
         _A:= cut_(_it(it_A));
         if _A='' then _A:= aftn_airbase (let);


        { Casove rozpatie
        }
         _B:= cut_(_it(it_B));
         _C:= cut_(_it(it_C));


        { Vyskove rozhranie
        }
         _F:= cut_(_it(it_F));
         _G:= cut_(_it(it_G));


        { Popis cinnosti a priestoru
        }
         form^.read_pole(it_D,PRZ^._D);
         form^.read_pole(it_E,PRZ^._E);


        { Kontrola spravnosti vyplnenia a podania planu
        } if not _check_NTM(PNTM(PRZ),nil, res,ires, form) then goto X;


        { Vsetky polozky su v poriadku
        }
         if PRZ^.dap.den=0 then with PRZ^.dap do
            begin
              rok:= year; mes:= month; den:= day;
              h:= hour; min:= min; s:= sec;
            end;

         _PRZ_check:= true;
         format_PRZ(PRZ);
         Exit;

         X:  _PRZ_check:= false;
             form^.ErrorS(ires, res);
             disp_PRZ(PRZ)
       end
   end;


{ -------------------------
   Volanie formulara
  -------------------------
}
 function  formular_PRZ(PRZi: PPRZ; _uloz,_arch: bool; _stat,_tit: string): bool;
    const  f     : Tcentr = (x: initX; y: initY; m: 1);
    var    form  : PFDP_AForm;
           PRZ   : TPRZ;
           E     : TEvent;
           _dole : byte;
           _novy : bool;
    begin
      fillchar(PRZ,sizeof(PRZ),0);
      new_PRZ(PRZi,@PRZ);
      _novy:= (PRZi=nil) or (_arch);
      if (_stat=cnst_disk) or (_novy) then
         begin
           _stat:= cnst_disk;
           strdispose(PRZ._NTM);
           if _novy then fillchar(PRZ.dap,sizeof(PRZ.dap),0);
         end;
      modify_head_NOTAM (PNTM(@PRZ),_stat);

      if graphmode>_VGA then _dole:= 0 else _dole:= 1;
      form:= New(PFDP_AForm,Init(f.x,f.y, f.m, _tit,

                 @frm_PRZ,size_frm_PRZ, _dole,1, 0,0, 10,260,
                 @_PRZ_init,@_PRZ_image,@_PRZ_check,

                 hlp_PRZ,

                 @PRZ,PRZi,  @PRZ.rec, letvis, PRZ.stt,
                 (PRZi=nil) or _arch, sizeof(TPRZ), @codekey_PRZ,@read_PRZ,nil,nil,
                 nil,nil, @zarad_PRZ,@disp_PRZ,

                 true,false,true
                 {$IFDEF ODOSLI_ULOZ}, _uloz or _novy {$ENDIF}
                 {$IFDEF SKRY_OKNA}, false {$ENDIF}
                 {$IFDEF STATISTIKA_OPL}, nil {$ENDIF})
                );

      form^.upcas:= true;
      form^.novy:= _novy;
      form^.arch:= _arch and (PRZi<>nil);
      form^.ins_date:= false;
      form^.copy_back:= true;
      form^.Ltitle:= true;

      form^.RunLocalFunc(E,nil);
      formular_PRZ:= form^.corr_res;
      Dispose(form,Done);

      disp_PRZ(@PRZ)
    end;