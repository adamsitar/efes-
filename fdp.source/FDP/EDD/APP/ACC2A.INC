{ ------------------------------
  polozka NDB na tabuli stripov
  ------------------------------}

function TlstACC.get_scroller_size(_item_dx: int; var _dxi: int): word;
   begin
     get_scroller_size:= _dxi + _item_dx + _dxi {+ 1}
   end;

function TlstACC.get_scroller_height(_page: int; _item_dy: int; var _dyi: int; _medzera: int): word;
   begin
     if (top>=0) then inc(_page);
     get_scroller_height:= _dyi + _page*(_item_dy+_medzera){-_medzera} +_dyi { + 1}
   end;


const SORT_NDBs       : PSORT_NDBs = nil;
      pocet_SORT_NDBs : int  = 0;


constructor TlstACC.Init(_Owner: PGroup; _popis: TpopisSkupina; _stl,_rdk: int);
      var   i : int;
      begin
        inherited Init(_Owner, { nezaklada do zasobnika }
                       1, 10,10, {x,y,} dx_strip,dy_strip, {_item_dx,_item_dy}
                       0,0, {_dxi,_dyi} dy_medzera, bgTABLET,
                       true, true,
                       nil, {_item_list: Pproc_i3b;}
                       nil,@is_chg{nil},nil
                      );

        sc_lst:= nil;
        is_chg:= false;

        new_Popis(@_popis,@popis);

        smer:= false; za_posl_en:= false;
        sb^.smer:= smer; if not smer then sb^.posun:= 1; sb^.za_posl_en:= za_posl_en;
        {stranka:= true; sb^.stranka:= true;}
        in_frame:= false; ScreenSave:= false;
        pos_chg_and_list:= false;

        stl:= _stl; rdk:= _rdk;

        sb^.visible:= false; sb^.bk0:= clTABLET;
        sb_left; sb^.MoveRel(dxof_sb,0);
        btTitle:= New(PtitACC,Init(@Self, x0,y1-dy_strip, dx_strip,dy_strip div 2, popis.NDB));
        if SORT_NDBs<>nil then
           begin
             i:= 0; while (i < pocet_SORT_NDBs) and (popis.NDB <> SORT_NDBs^[i].NDB) do inc(i);
             if i < pocet_SORT_NDBs then btTitle^.sort_by:= SORT_NDBs^[i].sort_by
           end;

        visible:= NDB_NULL;
        reinit_(1, rdk); { inicializacia riadkov }
        {pom:= false}
        {sc:= nil}
      end;


destructor TlstACC.Done;
     begin
       inherited Done;
       disp_Popis(popis)
     end;


procedure TlstACC.Draw;
    var   bp: bool; xlm,ylm: int;
    begin
      if (APP_GUI_INIT) or (top<0) and (not NDB_NULL) then Exit;
      m_off (bp, xlm,ylm);
      FillWin(x0,y1-(item_dy+medzera), x1,y1, 0);
      TGroup.Draw;  { sb + title }
      pos_prev:= -1;
      List;
      m_on (bp, xlm,ylm);
    end;


procedure TlstACC.ActiveOn;
    var   bp: bool; xlm,ylm: int;
    begin
      m_off (bp, xlm,ylm);
      inherited ActiveOn;
      btTitle^.ct:= clKey;
      btTitle^.Draw;
      sb^.visible:= true;
      sb^.Show;
      m_on (bp, xlm,ylm);
    end;

procedure TlstACC.ActiveOff;
    var   bp: bool; xlm,ylm: int;
    begin
      m_off (bp, xlm,ylm);
      inherited ActiveOff;
      btTitle^.ct:= clItem;
      btTitle^.Draw;
      sb^.visible:= false;
      sb^.hide;
      m_on (bp, xlm,ylm);
    end;
