{
  Menu pre Mapy je dynamicke, alokuje sa len pri vyvolani prislusnej
  polozky, potom sa odalokuje, usetri sa tym vela pamate...
}

const SYMfile : Pchar    = nil;
      SYMbool : Pbools   = nil;
      SYMpoc  : TGPpocet = 0;    { Musi byt ten isty typ, ako Mark.pocet ! }

procedure SYMsubmenu_init(Item: PItem); far; forward;
procedure SYMsubmenu_done(Item: PItem; var _Event: TEvent); far; forward;


procedure MAPsubmenu_init(MMenu: PSubmenu);
    var   names : PTMapNames;
          poc   : int;

          T     : text;
          s     : string;

          SMenu : PSubmenu;
          Item  : PItem;

    function _sub_mnu(dn: string): PSubmenu;
       var   Fil : PDir;
             fpoc,dpoc, i,k : int;

             DirName : PathStr;
             MapName : NameStr;

             mnu,ssmnu : PSubmenu;
             wmnu : PWinMenu;

             Data : PMapData;
             kr   : bool;
       begin
         _sub_mnu:= nil;
         if (dn<>'') and (dn[length(dn)]<>'\') then dn:= dn+'\';
         if GetDirF(dn+allfiles,Directory+Archive)=0 then
            begin
              {runerror(dn+allfiles);}
              Exit;
            end;
         GetDir(dn+allfiles, Fil,Directory+Archive, fpoc); { nacitanie obsahu hlavneho adreasara map }

        { a) zistenie typu menu - ak su subory tak OptMenu,
             inak len WinMenu pre podadresare
        }
          k:= 0; for i:= 0 to fpoc-1 do
             if     ((Fil^[i]^.attr and Archive)<>0)
                and eq_str('.'+getstr(Fil^[i]^.name,2,['.']),ext_MAP)
                    then inc(k);

        { b) inicializacia submenu
        }
         FSplit(dn, sDir,sName,sExt);
         DirName:= upstring(getstr(sDir,getstritems(sDir,['\']),['\']));
         {DirName:= InsChar(' '+DirName,Length(NSMstr)-3,' ',1);}
         if k>0 then wmnu:= OptMenu_S(' '+DirName+' ',hlpmnuMMI_MAPS,cmMAPA_PREKRESLI,OMenuS_items,nil)
         else wmnu:= WinMenu(' '+DirName+' ',hlpmnuMMI_MAPS,nil);
         mnu:= SubMenu(' '+DirName+' ',wmnu,nil);
         _sub_mnu:= mnu;
         FSplit(dn, sDir,sName,sExt); DirName:= sDir;

        { c) najprv zoradenie dalsich podadresarov }
         dpoc:= 0;
         for i:= 0 to fpoc-1 do
           if ((Fil^[i]^.attr and Directory)<>0) then
              begin
                inc(dpoc);
                ssmnu:= _sub_mnu(DirName+Fil^[i]^.name);
                if ssmnu<>nil then AddSubMenuToMenu(mnu,ssmnu);
              end;
          if (dpoc>0) and (dpoc<fpoc) then AddItemToMenu(mnu,NewLine(nil));

        { d) mapove polozky                        }
         for i:= 0 to fpoc-1 do
             if ((Fil^[i]^.attr and Archive)<>0) and eq_str('.'+getstr(Fil^[i]^.name,2,['.']),ext_MAP) then
                begin
                  FSplit(Fil^[i]^.name, sDir,sName,sExt); MapName:= SName;
                  Data:= najdi_mapu(Mapa^.zMapy, MapName,'', false);
                  if Data<>nil then AddItemToMenu(mnu,Switch2(UpString(MapName),@(Data^.kr),nil))
                end;

         FreeDirFiles(Fil,fpoc);
         CheckProcesses0
       end;

    begin
      if Mapa=nil then Exit;

      InfoCakaj(msgREAD,tit_MNU_INIT);
      m_set_shape(HODINY);

     { תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
       a) Menu pre mapy : nacitanie menu pre zapnutie/vypnutie map
     }
      read_map_names_cfg(APP_MAPS_CFG,names,poc);  { nacitanie zoznamu map z cfg subora maps.kod }
      SMenu:= _sub_mnu(PathToMaps);
      if SMenu<>nil then AddSubMenuToMenu(MMenu,SMenu);
      if names<>nil then FreeMem(names,poc*SizeOf(TMapNaz));


     { תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
       b) Menu pre symboly - nacitanie map, z ktorych sa vytvaraju symboly,
          tak aby sa dali jednotlive symboly vypnut/zapnut
     }
      if Exists(MAPscfg)=0 then
         begin
           NSMmenu:= SubMenu(NSMstr, WinMenu(NSMstr,nil,nil),nil);
           if NSMmenu=nil then Exit;

           {if SMenu<>nil then AddItemToMenu(MMenu,NewLine(nil));}
           AddSubMenuToMenu(MMenu,NSMmenu);

           Assign(T,MAPscfg); Reset(T); s:= ''; cmNSMtop:= cmNSMxxx;
           while (not Eof(T)) and (cmNSMtop<cmNSMmax) do
             begin
               readln(T,s); s:= cut_(s);
               if (s[1]='"') or (s[1]=';') or (pos(cfg_NASTAV_SYMBOLY,s)=0) then continue;
               s:= getstr(s,2,odd_cfg); s:= cut_(s);
               if (s<>'') then
                  begin
                    {s:= ' '+inschar(s,strlen(NSMmenu^.title),' ',1);}
                    SMenu:= SubMenu(' '+s, OptMenu_S(s,hlpmnuMMI_MAPS,cmMAPA_PREKRESLI,OMenuS_items,nil),nil);
                    SMenu^.PMenu_init:= @SYMsubmenu_init;
                    SMenu^.PMenu_done:= @SYMsubmenu_done;
                    inc(cmNSMtop);
                    AddSubMenuToMenu(NSMmenu,SMenu)
                  end
               else begin
                      Item:= NewLine(nil);
                      AddItemToMenu(NSMmenu,Item)
                    end
             end;
           Close(T)
         end;

      m_restore_shape;
      InfoCakaj_zatvor
    end;


{
 nacita suradnice zo subora do zoznamu
}
procedure SYMsubmenu_init(Item: PItem);
    var   Data : PMapData;
          Mark : PTMark13;
          T    : PGText;
          i    : int;
          b    : bool;
          s    : string;
    begin
      SYMfile:= StrPasNew(FindFile(PathToMAPs, delchar(strpas(Item^.title),[' ','~'])+ext_MAP));
      if SYMfile=nil then Exit;

      InfoCakaj(msgREAD,tit_MNU_INIT);
      m_set_shape(HODINY);

      Data:= mapy_nacitaj_subor(StrPas(SYMfile), nil, false);
      if (Data^.GP=nil) or (Data^.GP^.kod<>gr_Mark13) then
         begin
           dispose_MapOb(Data);
           StrDispose(SYMfile);
           exit
         end;
      Mark:= PTMark13(Data^.GP); { Nie je to ciste, ale kto ma teraz cas ? Kontrola postednym ififakom... }
      SYMpoc:= Mark^.pocet;

      if (MemAvail > MINVOLPAM + SYMpoc * (SizeOf(TSwitch2)+SizeOf(bool))) then
         begin
           m_set_shape(HODINY);
           GetMem(SYMbool,SYMpoc*(SizeOf(bool)));
           Mark^.ZozText^.JdiNaZacatek;
           i:= 0; b:= false;
           while (i<SYMpoc) and (not b) do
               begin
                 T:= Mark^.ZozText^.DejAktPrvek;
                 SYMbool^[i]:= T^.Ts > 0;
                 s:= strpas(T^.Vet);
                 Item^.PMenu^.AddItem(Switch2(cut_(s),@SYMbool^[i],nil));
                 Mark^.ZozText^.JdiNaDalsi(b);
                 inc(i)
               end;
           m_restore_shape
         end
      else begin
             s:= strpas(Item^.title);
             Err2('',msgMEMORY+cut_(s)+'.')
           end;

      dispose_MapOb(Data);

      m_restore_shape;
      InfoCakaj_zatvor
    end;

procedure SYMsubmenu_done(Item: PItem; var _Event: TEvent);
    var   Data  : PMapData;
          Mark  : PTMark13;
          T     : PGText;
          Zd,Zs : TZdZs;
          vet   : ch255;

          i,res : int;
          b     : bool;

          F1,F2,Na : string;
          SymF    : file;

    begin
      if SYMfile=nil then Exit;

      InfoCakaj(msgREAD,tit_MNU_INIT);
      m_set_shape(HODINY);
      Na:= '';
      if isCommand(_Event,cmMAPA_PREKRESLI) then
         begin
         { vytvorenie noveho subora so zaznamenanymi zmenami }
           Data:= mapy_nacitaj_subor(StrPas(SYMfile), nil, false);
           if (Data^.GP<>nil) {or (Data^.GP^.kod<>gr_Mark13)} then
              begin
                Mark:= PTMark13(Data^.GP);
                F1:= StrPas(SYMfile);
                FSplit(F1, sDir,sName,sExt); Na:= sName;
                F2:= sDir+sName+'.@#$';

                mapy_vytvor_subor(F2, $FFFF,map_MARK,cl_MARK, 0,0, 0,0);
                mapy_vytvor_GP   (F2, gr_Mark13, 0,0,0);

                Assign(SymF,F2); Reset(SymF,1);
                Seek(SymF,FileSize(SymF));
                BlockWrite(SymF,SYMpoc,SizeOf(SYMpoc),res);

                Mark^.ZozText^.JdiNaZacatek;
                i:= 0; b:= false;
                while (i<SYMpoc) and (not b) do
                    begin
                      T:= Mark^.ZozText^.DejAktPrvek;
                      if SYMbool^[i] then T^.Ts:= abs(T^.Ts)   { zobraz }
                      else T^.Ts:= -abs(T^.Ts);                { skry   }
                      xy_ZdZs(T^.X,T^.Y, Zd,Zs);
                      StrCopy(vet,T^.vet);
                      RW_Mark13(1, SymF, Zd,Zs, T^.Ts, vet);

                      Mark^.ZozText^.JdiNaDalsi(b);
                      inc(i)
                    end;

                Close(SymF);
                _SetFTime(F2,_GetFTime(F1));
                MoveFile(F2,F1)
              end;
           dispose_MapOb(Data)
         end;

      if Na<>'' then
         begin
         { znovu nacitanie do pamate}
           Mapa^.zMapy^.JdiNaZacatek;
           if Mapa^.zMapy^.DejPocet<>0 then
              repeat
                Data:= Mapa^.zMapy^.DejAktPrvek;
                if Data=nil then break;
                if Data^.naz = Na then
                   begin
                     Data^.kr:= false;
                     Mapa^.uvolni_data(Data);
                     Mapa^.nacitaj_data(Data);
                     Data^.kr:= true; { ak by si to nahodou nestihol zapamatat }
                     break
                  end
              until Mapa^.zMapy^.JdiNaDalsi_
         end;

      if SYMbool<>nil then FreeMem(SYMbool,SYMpoc*(SizeOf(bool)));
      SYMbool:= nil; SYMpoc:= 0;
      StrDispose(SYMfile);

      m_restore_shape;
      InfoCakaj_zatvor
    end;


function  MAPYmenu_init(title: string): PSubmenu;
   begin
     MAPYmenu:= SubMenu(title, WinMenu('MAPY',nil,nil),nil);
     MAPYmenu^.PMenu_init:= @MAPsubmenu_init;
     MAPYmenu_init:= MAPYmenu
   end;

