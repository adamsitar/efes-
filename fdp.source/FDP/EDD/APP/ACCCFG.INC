 procedure mnuGROUPs_init(MMenu: PSubmenu); far;
     const max_items = cmACC_DEFAULT_hi-cmACC_DEFAULT_lo+1;
     var   smnu    : array[0..max_items-1] of PItem;
           i,items : int;

           dir   : PDir;
           files : int;

     begin
       smnu[0]:= Item(ACCDEFAULT, cmACC_DEFAULT, nil);
       items:= 1;

       if GetDirFiles ('', fn_all+ext_tbl, dir,files)>0 then
          begin
            QuickSort(Pptrs(dir),@comp_fn_FileAttr,nil,0,files-1,false);
            smnu[items]:= NewLine(nil);
            inc(items);
            i:= 0; while (i<files) and (items<max_items) do
              begin
                smnu[items]:= Item(' '+getstr(dir^[i]^.name,1,['.']), cmACC_DEFAULT_lo+i, nil);
                inc(items);
                inc(i)
              end;
          end;
       if files>0 then FreeDirFiles(dir,files);

       for i:= 0 to items-1 do AddItemToMenu(MMenu,smnu[i])
     end;


 procedure mnuGROUPs_done(O: PObject {MMenu: PSubmenu}; var _Event: TEvent); {far;}
     var   dir     : PDir;
           files,i : int;
     begin
       case _Event.What of

         evCommand, evBroadcast :

           case _Event.Command of

             cmACC_DEFAULT       : if winACC<>nil then winACC^.reinit_tablet(TABLET_CFG,true);

             cmACC_DEFAULT_lo..
             cmACC_DEFAULT_hi    :
                 if winACC<>nil then
                    begin
                      if GetDirFiles ('', fn_all+ext_tbl, dir,files)>0 then
                         begin
                           i:= _Event.Command-cmACC_DEFAULT_lo;
                           if (i>=0) and (i<files) then
                              begin
                                QuickSort(Pptrs(dir),@comp_fn_FileAttr,nil,0,files-1,false);
                                winACC^.reinit_tablet(Dir^[i]^.Name,true)
                              end
                         end;
                      FreeDirFiles(Dir,Files)
                    end

             else Exit;
           end

         else Exit
       end;

       ClearEvent(_Event,O{MMenu})
     end;


 function GROUPs_menu_init(title: string): PSubMenu;
    var   sbmnu : PSubMenu;
    begin
      sbmnu:= {$IFDEF MAPY} SubMenu_  (title,@PLANZET_MAPA,false,
              {$ELSE}       SubMenu   (title,
              {$ENDIF}      WinMenu_S (delchar(title,['~']),hlpmnuBOARD_GROUPS,10,nil),nil);

      sbmnu^.PMenu_init:= @mnuGROUPs_init;
      {sbmnu^.PMenu_done:= @mnuGROUPs_done;}
      GROUPs_menu_init:= sbmnu
    end;



(*
procedure mnuGROUPs_done(O: PObject {MMenu: PSubmenu}; var _Event: TEvent); {far;}
    var   {dir     : PDir;
          files,i : int;}
          s   : string;
    begin
      case _Event.What of

        evCommand, evBroadcast :

          case _Event.Command of

            cmACC_DEFAULT : if winACC<>nil then
                   winACC^.reinit_tablet(TABLET_INI);

            cmACC_USER    : if winACC<>nil then
                   begin
                     if _handler=nil then _handler:= @BackupFile;
                     bck:= New(PScrollDIR,Init(_path,_name,
                                               _title,_mess,
                                               nil,true,0,
                                               @comp_dir_date,0,
                                               _handler,
                                               nil)
                                              );
                     bck^.RunLocalFunc(_Event,SCROLL_NC);
                     Dispose(bck,Done)
                   end

            else Exit;
          end

        else Exit
      end;

      ClearEvent(_Event,MMenu)
    end;
*)


{$IFDEF SECTORS}
  procedure SECTOR_chg(nS: mask_SECTORs; _draw: bool); far;
      var   was,nis, dis : bool;
            i : int;
      begin
        Sector.SECTOR_chg(nS,_draw);

       {$IFDEF EDD}
         if _draw then
            begin
              i:= 0; while (i<nsec) do
                begin
                  if SECTORs^[i]^.is and (Exists(SECTORs^[i]^.tablet+ext_tbl)=0) then
                     begin
                       if winACC<>nil then winACC^.reinit_tablet(SECTORs^[i]^.tablet+ext_tbl,true);
                       break
                     end;
                  inc(i);
                end;
            end;
       {$ENDIF}
      end;
{$ENDIF}
