{ ----------------------------
  save cfg
  ----------------------------
}

 procedure TMapa.save_cfg_fn(fn: string);
     var   PData : PMapData;
           f     : file;
           res   : int;
     begin
       {if (not saveMAPY) then Exit;}

      { Ulozenie polohy a rozsahu
      }
       Assign(f,fn);
       Rewrite(f,1);
       BlockWrite(f,Rozsah  ,SizeOf(Real),res);
       BlockWrite(f,Xvystred,SizeOf(Real),res);
       BlockWrite(f,Yvystred,SizeOf(Real),res);
       BlockWrite(f,FILLOVAT,sizeof(bool),res);

      { Zapisanie map, ktore boli zobrazene
      }
       zMapy^.JdiNaZacatek;
       repeat
         PData:= zMapy^.DejAktPrvek;
         if PData=nil then break;
         if (not PData^.kr_) and (PData^.kr) and (not PData^.plan) then
            begin
              BlockWrite(f,PData^.naz,SizeOf(PData^.naz),res)
            end;
       until zMapy^.JdiNaDalsi_;

       Close(f)
     end;


{ ----------------------------
  read cfg
  ----------------------------
}

{ funkcia nacita do pola nazvy map obsiahnute v cfg subore...
}
 function read_map_names_cfg (fn : string; var names: PTMapNames; var poc: int): bool;
    var   i,res : int;
          f : file;
    begin
      read_map_names_cfg:= false;
      names:= nil; poc:= 0;
      if Exists(fn)<>0 then Exit;

      Assign(f,fn);
      Reset(f,1);
      poc:= (FileSize(f)-3*sizeof(real)-sizeof(bool)) div SizeOf(TMapNaz);
      GetMem(names,poc*SizeOf(TMapNaz));

      Seek(f,3*sizeof(real) + sizeof(bool));
      i:= 0;
      repeat
        BlockRead(f,names^[i],SizeOf(names^[i]),res);
        inc(i);
      until (i>=poc) or (FilePos(f) = Filesize(f));
      Close(f);

      read_map_names_cfg:= true
    end;


 procedure TMapa.read_cfg_fn(fn: string);

     var   names : PTMapNames;
           poc   : int;

     procedure _read_map (fn: string);
         var   Data  : PMapData;
               Name  : NameStr;
               kr    : bool;
               s     : string;
               i     : int;
               T     : text;
         begin
           FSplit(fn, sDir,sName,sExt); Name:= sName;

           Data:= mapy_nacitaj_subor(fn, zMapy, false);
           if poc>0 then
              begin
                i:= 0; while (i<=poc) and (not eq_str(names^[i],Name)) do inc(i);
                if poc>0 then Data^.kr:= i<=poc
              end
           {else Data^.kr:= false plati implicitne nastavenie v mape};
           kr:= MaxAvail > MINVOLPAM;
           if Data^.kr and (not kr) then
              begin
                Nevojde(Name);
                Data^.kr:= false
              end;
           if not Data^.kr then uvolni_data(Data)
           else nacitaj_data(Data);
         end;

     procedure _read_maps(dn: string);
         var   Fil   : PDir;
               fpoc, i : int;

               DirName : PathStr;
               MapName : NameStr;

               Data : PMapData;
               kr   : bool;
         begin
           if (dn<>'') and (dn[length(dn)]<>'\') then dn:= dn+'\';
           if GetDirF(dn+allfiles,Directory+Archive)=0 then Exit;

           GetDir(dn+allfiles, Fil,Directory+Archive, fpoc); { nacitanie obsahu hlavneho adreasara map }

          { a) nacitanie map }
           for i:= 0 to fpoc-1 do
               if     ((Fil^[i]^.attr and Archive)<>0)
                  and eq_str('.'+getstr(Fil^[i]^.name,2,['.']),ext_MAP)
                      then _read_map(dn+Fil^[i]^.name);

          { b) nacitanie podadresarov }
           for i:= 0 to fpoc-1 do
             if ((Fil^[i]^.attr and Directory)<>0)
                then _read_maps(dn+Fil^[i]^.name);

           FreeDirFiles(Fil,fpoc)
         end;


     var   Map  : PMapData;
           res  : int;
           bres : bool;
           f    : file;

     begin
       if zMapy=nil then Exit;

      { Odmazanie uzivatelom vykreslenych map,
        ostanu len mapy aktivovane automaticky
        na zaklade spracovania planov
      }
       zMapy^.JdiNaZacatek;
       repeat
         Map:= zMapy^.DejAktPrvek;
         if (Map=nil) then break;
         if (not Map^.plan) then
            begin
              zMapy^.ZrusPrvek(Map);
              bres:= zMapy^.DejPocet=0
            end
         else bres:= zMapy^.JdiNaDalsi_
       until bres;

      { Nacitanie polohy a rozsahu
      }
       if (Exists(fn)<>0) {or (not saveMAPY)} then Centr
       else begin
              Assign(f,fn);
              Reset(f,1);
              BlockRead(f,Rozsah  ,SizeOf(Real),res);
              BlockRead(f,Xvystred,SizeOf(Real),res);
              BlockRead(f,Yvystred,SizeOf(Real),res);
              BlockRead(f,FILLOVAT,sizeof(bool),res);
              Close(f)
            end;

       read_map_names_cfg(fn,names,poc);
       _read_maps(PathToMAPs);
       if names<>nil then FreeMem(names,poc*SizeOf(TMapNaz));
       mapy_zotried_mapy(zMapy)

     end; { read_cfg_fn }



 procedure TMapa.save_user_cfg (fn: string);
    var    D : DirStr; N : NameStr; E : ExtStr;
           cfg_fn : string;
    begin
      {save_cfg_fn(USER_MAPS_CFG);}

      FSplit(fn,D,N,E);
      cfg_fn:= N+ext_usm;
      {if USER_MAPS_CFG=cfg_fn then Exit;}

      USER_MAPS_CFG:= cfg_fn;
      save_cfg_fn(cfg_fn);
    end;


 function TMapa.load_user_cfg (fn: string): bool;
    var   D : DirStr; N : NameStr; E : ExtStr;
          cfg_fn,cfg_fn0 : string;
          bres : bool;
    begin
      load_user_cfg:= false;

      cfg_fn0:= USER_MAPS_CFG;
      if fn=APP_CFG then
         begin
         { Vzorovy cfg...
         } cfg_fn:= MAPS_CFG;
           USER_MAPS_CFG:= APP_MAPS_CFG
         end
      else begin
             FSplit(fn,D,N,E);
             cfg_fn:= N+ext_usm;
             USER_MAPS_CFG:= cfg_fn;
           end;
      if cfg_fn0<>USER_MAPS_CFG then save_cfg_fn(cfg_fn0);

      if Exists(cfg_fn)<>0 then
         begin
           CopyFile(cfg_fn0,cfg_fn);
           Exit
         end;

      read_cfg_fn(cfg_fn);
      load_user_cfg:= true
    end;