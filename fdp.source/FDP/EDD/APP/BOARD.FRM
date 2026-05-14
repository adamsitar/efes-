{
ÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜ
Û                                                          Û
Û Settings ACC                                             Û
ÛÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÛ
}
{ - lepsie je naprogramovat do editora, ale tera nemam cas vymyslat
    citatelneu gramatiku na oddelenie strlpcov, majakov.
  - nemoze byt pouzita viacnasobne sucasne -> frm_mini_STRIP urcuje,
    s ktorym druhom stripov sa pracuje
}

const  rdk_na_skupinu   = max_skupin+1;
       stlpcov_form_acc = 60;


procedure init_TABLET(form: PFormular); far;
    var   i,j,k : int;
          s : string;
    begin
      k:= 0;
      for i:= 0 to _stlpcov (miniSTRIP)-1 do
        begin
          for j:= max_skupin-1 downto 0 do
              begin
                s:= Popis_to_str(p_tab_stripi[miniSTRIP]^[i][j]); s:= cut_(s);
                if (k>=form^.items) then break;
                strpicopy(form^.itemd^[k].item,s,strlen(form^.itemd^[k].item));
                inc(k)
              end;
          strpicopy(form^.itemd^[k].item,' ',strlen(form^.itemd^[k].item));
          inc(k)
        end;
    end;

function check_TABLET(form: PFormular): bool; far;
   var   r,s,k: int;

   procedure stlpec(s: int; var r: int);
      var   t : string;
            zac,kon,zac0,j : int;
      begin
        zac0:= r; zac:= r; kon:= r;
        while (kon-zac<max_skupin) and (r<form^.items) do
          begin
            t:= form^._it(r); t:= cut_(t);
            if ((t='') and (zac<>zac0)) then break
            else if (t<>'') then
                    begin
                      if zac0=zac then begin zac:= r; zac0:= zac-1 end;
                      if (r-zac+1> max_skupin) then break else kon:= r;
                    end;
            inc(r)
          end;

        for j:= kon downto zac do
          begin
            str_to_Popis(cut_(form^._it(j)),p_tab_stripi[miniSTRIP]^[s][kon-j])
          end
      end;

   begin
     r:= 0; s:= 0; k:= _stlpcov(miniSTRIP);
     while (r<form^.items) and (s<k) do
       begin
         disp_Stlpec(p_tab_stripi[miniSTRIP]^[s]);
         stlpec(s,r);
         inc(s)
       end;
     for r:= s to k-1 do disp_Stlpec(p_tab_stripi[miniSTRIP]^[r]);
     check_TABLET:= true
   end;


procedure update_tablet_lst(var lst: TListDesc);
    var   t       : text;
          dir     : PDir;
          files,i : int;
    begin
      Assign(t,strpas(lst.fn)); Rewrite(t);
      if GetDirFiles ('', fn_all+ext_tbl, dir,files)>0 then
         begin
           QuickSort(Pptrs(dir),@comp_fn_FileAttr,nil,0,files-1,false);
           for i:= 0 to files-1 do writeln(t,dir^[i]^.name);
         end;
      if files>0 then FreeDirFiles(dir,files);
      Close(t)
    end;


procedure  formular_TABLET;

    const  c     : Tcentr  = (x: initX; y: initY; m:1);
           {cfg   : string[NAME] = '';}

    var    frm : PForms;
           F   : PFormular;
           Ev  : TEvent;
           it,i,j,k : int;

           s   : string;
           t   : text;
           lst : TListDesc;

           D : DirStr; N : NameStr; E : ExtStr;

    begin
     { zistenie nastavenia
     }
      it:= _stlpcov (miniSTRIP)*(rdk_na_skupinu+1);
      frm:= alloc_form (it);
      for i:= 0 to it-1 do with frm^[i] do
        begin
          GetMem(item,stlpcov_form_acc+1);
          FillChar(item^,stlpcov_form_acc,' ');
          item[stlpcov_form_acc]:= #0;
          legal:= @setABCcs_;
          lst:= @fnNDB;
          dx:= 8; dy:= 8+i*10;
        end;
      F:= New(PFormular,Init(nil, c.x,c.y,c.m, kbCtrlEnter,cmOK,title_ARRANGE,
              frm,it, 0,0,0,0, 0, 0, 0,0,nil,0,0,0,0,
              nil, @init_TABLET,@check_TABLET,nil,nil, {_init_form, _check_func, _done_form, _image_form: pointer}
              true,false,true,
              hlpmnuBOARD_EDIT)
             );
      F^.pole_en:= true;
      F^.pole_cr:= true;
      F^.upcas:= true;

      F^.RunLocalFunc(Ev,' ~Ctrl~+~ÄÙ~ :  '+title_ARRANGE+'...');

      if F^.corr_res then
         begin

         { zistenie nazvu cfg pre nastavenie...
         } new_ListDesc  (lst,pathTMP+USER_TABLET_CFG);
           update_tablet_lst (lst);

           FSplit(USER_TABLET_CFG,D,N,E);
           if formular_s(N,10,titSAVEas,@lst,1,@setASCII,nil,0, nil,false,false,true,nil) then
              begin
                USER_TABLET_CFG:= N+E;

                { nastavenie
                } send_mail(F,MainApp, cmACC_SETT, one,nil,0);

                { zapis do cfg so zadanym menom
                } save_tablet_cfg(USER_TABLET_CFG);
                  {if cfg<>'' then s:= cfg+ext_tablet else s:= TABLET+ext_kod;
                  CopyFile(USER_TABLET_CFG,s)}
              end;

           DelFile (strpas(lst.fn));
           disp_ListDesc (lst);
         end;

      Dispose(F,Done);
      disp_form (frm,it);
    end;
