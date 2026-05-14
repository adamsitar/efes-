    type  PScroll_lstAct = ^TScroll_lstAct;
          TScroll_lstAct = object (TScrollAct)
          end;


    type  PlstACC = ^TlstACC;
          TlstACC = object(TStripBoard)

            stl,rdk : int;            { musia byt v tomto poradi za sebou }
            popis   : TpopisSkupina;  { stacil by len P..., ale nemam istotu, ze adresa T... sa nezmeni }
            btTitle : PtitACC;

            sc_lst  : PScroll_lstAct;


            constructor Init(_Owner: PGroup; _popis: TpopisSkupina; _stl,_rdk: int);
            destructor  Done; virtual;

            procedure   HandleEvent(var _Event: TEvent); virtual;
            procedure   Draw; virtual;

            procedure   ActiveOn; virtual;
            procedure   ActiveOff; virtual;

            procedure   List;  virtual;
            procedure   reinit_(_page, _rdk: int);
            procedure   Window;

            function    sk_riadkov: int;
            function    pl_riadkov: int;

            procedure   zmen_rozmer(o,volnych: int);
            procedure   zmen_polohu(o: int);
            function    zmen_stlpec: bool;


            private

            function    get_scroller_size  (_item_dx: int; var _dxi: int): word; virtual;
            function    get_scroller_height(_page: int; _item_dy: int; var _dyi: int; _medzera: int): word; virtual;

            function    get_x: int; virtual; { vratia poziciu pre vypis item }
            function    get_yi(i: int): int; virtual;

            procedure   item_list(i, x,y: int; b: bool); virtual;
            procedure   item_erase(i: int); virtual;
            procedure   list_reinit; virtual;

            function    is_scroll: bool;
            procedure   scroll_cl;
            procedure   scroll_st;

            function    list_sort: bool; virtual;
            procedure   set_sort;
          end;
