function PIS_povol(x0,y0,x1,y1: int; var TempWinReg: PWinReg; zostane: int): bool;
   begin
     TempWinReg:= nil;
     if (OpenWins > zostane) then PIS_povol:= vypis_do_okna(x0,y0,x1,y1, TempWinReg, -1,zostane)
     else PIS_povol:= true
   end;

procedure PIS_zakaz(TempWinReg: PWinReg);
    begin
      obnov_okna(TempWinReg, true)
    end;


function  TPLAN.vypis_plan(ind: int; _sort,_novy: bool): bool;
    var   TempWinReg : PWinReg;
          bres : bool;
    begin
      {set_chg_ticks(lst_chg);}
      if not vypisovat then Exit;

     {$IFDEF SECTORS}
      { Objekt plan vypisuje vsetky zmeny v planoch.
        Vypis planu do globalneho planu zoznamov (p_viewer_gl), alebo do prehladu
        planov. Ten ja navrhnuty tak, ze ak je otvoreny, tak sa don zaradi kazda
        zmena v poli planov.

        Funkcia zisti, ci plan patri na sektor.
        Ak ano, vrati true, aby odovodena funkcia mohla plan zaradit a zobrazit.
      }
     {$ENDIF}

     { celkovy zoznam
     }
      if (p_viewer<>nil) then
         begin
           if _sort then p_viewer^.List
           else p_viewer^.redraw(ind)
         end;

      if (viewer<>nil) then
         begin
           {if PIS_povol(viewer^.win^.x0,viewer^.win^.y0,viewer^.win^.x1,viewer^.win^.y1, TempWinReg,1) then}
             if _sort then viewer^.List else viewer^.redraw(ind)
           {else PREPIS__VYPIS_PLANOV:= true;
           PIS_zakaz(TempWinReg)}
         end;

     { ostatne zoznamy
     }
      bres:= true;
      {$IFDEF SECTORS}
       bres:= (not S_DISPLAY) or is_to_addS(ap^[ind]);
      {$ENDIF}
      {$IFDEF EDD}
       bres:= bres and get_on_board(ap^[ind]);
      {$ENDIF}
      if not bres then zmaz_plan(ind,false);
      vypis_plan:= bres;
    end;


procedure TPLAN.zmaz_plan(ind: int; _zrus: bool);
    var   TempWinReg : PWinReg;
    begin
      {set_chg_ticks(lst_chg);}
      if vypisovat and _zrus then
         begin
           if (p_viewer<>nil) then p_viewer^.erase(ind);

           if (viewer<>nil) then
              begin{
                if PIS_povol(viewer^.win^.x0,viewer^.win^.y0,viewer^.win^.x1,viewer^.win^.y1, TempWinReg,1) then}
                   viewer^.erase(ind)
                {else PREPIS__VYPIS_PLANOV:= true;
                PIS_zakaz(TempWinReg)}
              end
         end
    end;


{$IFDEF SECTORS}

{ nastavia priznak do planu, ze je vypisany tablete...
}
 function  TPLAN.get_on_sector(p: pointer): bool;
    begin
      get_on_sector:= true {(not S_DISPLAY_SECTOR)}
    end;

 procedure TPLAN.set_on_sector(p: pointer; _on_sector: bool);
     begin
     end;

{$ENDIF}


 function zobrazeny_plan (p: byte): bool;
    begin
      zobrazeny_plan:= p and s_hide = 0
    end;

{$IFDEF EDD}

 function  TPLAN.nmb_on_board: int;
    var    i,p: int;
    begin
      p:= 0;
      for i:= 0 to top do
        if     get_on_board (ap^[i])
           {$IFDEF SECTORS}
            and ((not S_DISPLAY) or get_on_sector (ap^[i]))
           {$ENDIF}
               then inc(p);
      nmb_on_board:= p
    end;


 function TPLAN.get_on_board (p: pointer): bool;
    begin
      get_on_board:= (not hidding) or zobrazeny_plan(get_priznak(p))
    end;

 procedure TPLAN.set_on_board (p: pointer; _on_board: bool);
     var   b: byte;
     begin
       b:= get_priznak(p);
       if _on_board then b:= b xor s_hide else b:= b or s_hide;
       set_priznak (p,b,true);
     end;


 function  TPLAN.is_to_board (i: int): bool;
    begin
      is_to_board:=    get_on_board(ap^[i])
                     {$IFDEF SECTORS} and get_on_sector(ap^[i]) {$ENDIF}
    end;

 procedure TPLAN.put_on_board (p: pointer; _vis : bool);
     var   i : int;
           b,is : bool;
     begin
       i:= find(p);
       if i<0 then Exit;

       b:= get_on_board(ap^[i]);
       if b=_vis then Exit;

       is:= is_to_board(i);
       set_on_board (ap^[i],_vis);
       vypis_plan(i,false,false)
     end;

{$ENDIF}



{$IFDEF MAPY}

 function TPLAN.get_id_map(p: pointer; count: int; var map_naz: string): bool;
    begin
      get_id_map:= false;
      {$IFNDEF MAPY_1.0}
        {if (p_id_map<>nil) then get_id_map:= TSFunc_pi(p_id_map)(p,count)
        else} map_naz:= get_id(p)
      {$ELSE}
        map_naz:= ''
      {$ENDIF}
    end;


 function  TPLAN._zapni_mapu(p: pointer; map_naz: string; p_NewOb: pointer; PIS: bool): PMapData;
    var    stat : TMapStat;
           fill : TGRPfill;
           typ  : word;
           key  : string;
           bres : bool;
    begin
      _zapni_mapu:= nil;
      if map_naz<>''then
         begin
           if (p_codekey<>nil) then key:= TSFunc_p(p_codekey)(p) else key:= '';
           case stav_planu(p,absTime,bres) of
             poz_PROPOSED..poz_COORDINATED,
             poz_STOJI             : stat:= map_plan;
             poz_LETI,poz_PRIST    : stat:= map_act
             else stat:= map_
           end;
           if stat=map_act then begin typ:= typ_mapy+GRPprty_act_; fill:= _act_ end
           else begin typ:= typ_mapy; fill:= _draw_ end;
           if (Mapa<>nil) and (stat in[map_plan,map_act]) then
              _zapni_mapu:= Mapa^.zapni_mapu(map_naz, p_NewOb,p,key,typ,fill,PIS)
         end;
    end;


 procedure TPLAN._nenajdena_mapa_pre_plan(p: pointer; naz,msg: string);
     var   ind: int;
     begin
       if (not s_loadDB) and map_wrng and HLAS_NENAJDENA_MAPA then Say2(msgWARNING, naz+': '+msg);
       set_flag (p, gr_map,fl_map);
       ind := find(p);
       if ind>-1 then vypis_plan(ind,false,false)
     end;


 procedure TPLAN._zobraz_plan_na_mape(p: pointer; PIS: bool);
     var   Map  : PMapData;
           naz,sres  : string;
           i    : int;
           dalsi,
           boli : bool;
     begin
      {$IFNDEF MAPY_1.0}
       if (Mapa=nil) or (not is_map) then Exit;

      { vyhladanie mapy (map) a jej zapnutie
      }
       i:= 0; boli:= false; dalsi:= false; Map:= nil;
       repeat
         dalsi:= get_id_map(p,i, naz);
         if naz<>'' then
            begin
              Map:= _zapni_mapu(p,naz,nil,PIS);
              boli:= boli or (Map<>nil)
            end;
         inc(i)
       until (naz='') or ((not dalsi) and (Map<>nil));    { len jednu mapu sme hladali       }

       if (Map=nil) and (p_GrOb=nil) then
          begin
            l4_err(a_FUA,'',0,err_MAP_NOT_FOUND,sres);
            _nenajdena_mapa_pre_plan(p,get_id(p),sres);
          end;

       if (not boli) and (p_GrOb<>nil) then
          begin
            _nenajdena_mapa_pre_plan(p,get_id(p),tit_GrOb);
            Map:= _zapni_mapu(p,get_id(p), p_GrOb,PIS);
          end;
      {$ENDIF}
     end;


 procedure TPLAN.zobraz_plan_na_mape(p: pointer);
     var   TempWinReg : PWinReg;
           PIS        : bool;
     begin
       if (Mapa=nil) or (not is_map) then Exit;

       PIS:= PIS_povol(Mapa^.x0,Mapa^.y0,Mapa^.x1,Mapa^.y1, TempWinReg,0);
       _zobraz_plan_na_mape(p, PIS);
       map_wrng:= true;
       PIS_zakaz(TempWinReg)
     end;


 procedure TPLAN._zmaz_plan_na_mape(p: pointer; _del: bool; PIS: bool);
     var   naz,key: string;
     begin
       if not ((Mapa<>nil) and (is_map) and (not isCommand(MainEvent,cmQuit))) then Exit;

       if (p_codekey<>nil) then key:= TSFunc_p(p_codekey)(p) else key:= '';
       while Mapa^.vypni_mapu(''{get_id(p)},key, PIS) do
     end;


 procedure TPLAN.zmaz_plan_na_mape(p: pointer; _del: bool);
     var   TempWinReg : PWinReg;
           PIS        : bool;
     begin
       if (Mapa=nil) or (not is_map) then Exit;

       PIS:= PIS_povol(Mapa^.x0,Mapa^.y0,Mapa^.x1,Mapa^.y1, TempWinReg,0);
       _zmaz_plan_na_mape(p,_del, PIS);
       PIS_zakaz(TempWinReg)
     end;


 procedure TPLAN.vykresli_plan_na_mape(p: pointer);
     begin
       if p_kresli<>nil then TProc_p(p_kresli)(p)
     end;
{$ENDIF}
