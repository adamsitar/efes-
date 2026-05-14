{ ----------------------------------------------------------------
  triedenie
  ----------- }

function TlstACC.list_sort: bool;
   var   _FPL    : PAindFPL;
         ind_p   : Pints;
         time_p  : Preals;
         i       : int;
         p       : pointer;
         res     : bool;
         sort_by : Tsort_strip;

   begin
     list_sort:= false;
     if APP_GUI_INIT or (top<0) then Exit;

     if btTitle^.sort_by<>sort_imp then sort_by:= btTitle^.sort_by
     else sort_by:= STRIP_SORT;
     res:= false;

     p:= nil;
     if (popis.NDB=fplMIL) or (popis.NDB=fplFPL) then
        { MIL,AERO -> podla identifikacie -------------- }
          case sort_by of
           {sort_ndb : p:= @comp_ndb_indFPL;}
            sort_idn : p:= @comp_idn_indFPL;
            sort_eto : p:= @comp_ETD_indFPL;
            sort_fl  : p:= @comp_FL_indFPL
          end
     else if (popis.NDB=fplDEP) then p:= @comp_ETD_indFPL
     else if (popis.NDB=fplARR) then p:= @comp_ETA_indFPL
     else { letove cesty -> podla casu na NDB -------------- }
            case sort_by of
              sort_ndb : p:= @comp_ndb_indFPL;
              sort_idn : p:= @comp_idn_indFPL;
              sort_eto : p:= @comp_ETO_indFPL;
              sort_fl  : p:= @comp_FL_indFPL
              else if popis.NDBs<>nil then p:= @comp_ndb_indFPL
            end;
     if p<>nil then res:= QuickSort(pptrs(FPLs), p,nil, 0,top, false);

     list_sort:= res
   end;

procedure TlstACC.set_sort;
    var   NDBmenu  : PWinMenu;
          sort_by  : Tsort_strip;
          _Event   : TEvent;
          pomb     : bool;
    begin
      sort_by:= btTitle^.sort_by;
      pomb:=     (popis.NDBs<>nil)
             and (popis.NDB<>fplMIL) and (popis.NDB<>fplFPL)
             and (popis.NDB<>fplDEP) and (popis.NDB<>fplARR)
            {$IFDEF TABLET_ZAM}
              and (popis.NDB<>fplZAM)
            {$ENDIF}
            {$IFDEF TABLET_PRS}
              and (popis.NDB<>fplPRS)
              {and (popis.NDB<>fplTSA)}
            {$ENDIF}
            ;
      NDBmenu:= OptMenu(SORTING,hlpmnuBOARD_SORT,cmOK,
                  Radio('', @btTitle^.sort_by, 0,
                        RadioItem (_GLOB,
                        RadioItem_(_POINT, @pomb,true,
                        RadioItem (_INDEX,
                        RadioItem (_ETD,
                        RadioItem (_FL,
                        nil) ) ) ) ),
                nil)
                );
      NDBmenu^.MoveRel(btTitle^.x1-NDBmenu^.x1+NDBmenu^.x0-52,btTitle^.y1+2-NDBmenu^.y0);
      NDBmenu^.Run(_Event);
      if isCommand(_Event,cmOK) and (sort_by<>btTitle^.sort_by) then
         begin
           btTitle^.Draw;
           list_sort;
           List;
           add_to_SORT_CFG(popis.NDB,btTitle^.sort_by)
         end;
      Dispose(NDBmenu, Done)
    end;
