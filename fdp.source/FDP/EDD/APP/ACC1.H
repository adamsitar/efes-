    { odvodeny buttonisko, ma generovat dvojaky druh prikazu podla
      miesta kliknutia ... cm_NDB_view, cm_NDB_move
    }

    type  PtitACC = ^TtitACC;
          TtitACC = object(TButton)

            is_scrollable : bool;
            sort_by       : Tsort_strip;

            constructor  Init(_Owner: PGroup; x,y, dx,dy: int; _title: string);
            procedure    HandleEvent(var _Event: TEvent); virtual;
            procedure    Draw; virtual;

            procedure    scroll_cl;
            procedure    scroll_st;
          end;
