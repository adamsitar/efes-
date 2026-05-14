 procedure TApp.get_app_config (typ : Tnd_typ; sw : Tnd_sw; nd : Tnd_nd;
                                var data: pchars; var size: word
                               );
     begin
       data:= nil; size:= 0
     end;

 procedure TApp.set_app_config (const data: pchars; size: word);
     begin
       Mail(@Self,cmMenuRedraw,One,nil,0)
     end;

 procedure TApp.distribute_app_config;
     begin
       { zamerne void, aby nevznikli kruhove rerferencie na _NET }
     end;



 function TApp.ReadProgramCfg (cfg_fn: string; _dialog: bool): bool;
    begin
    end;

 procedure TApp.SaveProgramCfg (cfg_fn: string);
     begin
     end;


{ -----------------------------------
   uzivatelska konfiguracia programu
  -----------------------------------
}

 function vytvor_zoznam_uzivatelov(var lst: TListDesc; fn,ext: string): bool;
    var   dir : PDir;
          files,i : int;
          t : text;
          D : DirStr; N : NameStr; E : ExtStr;
    begin
      vytvor_zoznam_uzivatelov:= false;
      new_ListDesc (lst,pathTMP+fn+ext);
      if GetDirFiles ('', fn_all+ext, dir,files)>0 then
         begin
           vytvor_zoznam_uzivatelov:= true;
           Assign(t,strpas(lst.fn)); Rewrite(t);
           QuickSort(Pptrs(dir),@comp_fn_FileAttr,nil,0,files-1,false);
           for i:= 0 to files-1 do
             begin
               FSplit(Dir^[i]^.Name,D,N,E);
               writeln(t,N);
             end;
           FreeDirFiles(dir,files);
           Close(t)
         end;
    end;

 procedure zrus_zoznam_uzivatelov (var lst: TListDesc);
     begin
       DelFile (strpas(lst.fn));
       disp_ListDesc (lst);
     end;

 function vrat_meno_uzivatela (ext: string; index: word): string;
    var   dir   : PDir;
          files : int;
          meno  : string;
    begin
      meno:= '';
      if GetDirFiles ('', fn_all+ext, dir,files)>0 then
         begin
           QuickSort(Pptrs(dir),@comp_fn_FileAttr,nil,0,files-1,false);
           if (index<files) then meno:= Dir^[index]^.Name;
           FreeDirFiles(dir,files);
         end;
      vrat_meno_uzivatela:= meno
    end;

 function zadaj_meno_uzivatela (fn,ext: string): string;
    var   lst : TListDesc;
          frm : PForms;
          sres: string;
          D : DirStr; N : NameStr; E : ExtStr;
    begin
      FSplit(fn,D,N,E); ResetIOError;
      sres:= N;
      vytvor_zoznam_uzivatelov(lst,fn,ext);
      if formular_s(sres,sizeof(NameStr)-1,titSAVEas,@lst,1,@setASCII,nil,0, nil,false,true,true, hlp_CFG) then
         begin
           if (sres<>N) and (FExists(sres+ext)=0) then
              begin
                if Ask2(msgVERIPHY,ask_CFG,'',White,clBUTTON_COLOR,waitASK)<>ansAno then sres:= '';
              end;
           if sres<>'' then sres:= sres+ext;
         end;
      zrus_zoznam_uzivatelov(lst);
      zadaj_meno_uzivatela:= sres;
    end;


