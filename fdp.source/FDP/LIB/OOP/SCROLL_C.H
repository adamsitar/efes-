
    const max_itFileScroll = 150;
          win_FileScroll   : byte = 3; { pacet stranok v pamati }


    type  PPOScrollStream = ^POScrollStream;
          POScrollStream  = ^OScrollStream;        { Txt subor sa meni len sekvencnym sposobom, pribudaju data }
          OScrollStream   = object(TScrollWin)

            DataOb        : PPObject;       { object spracovavajuci data }

            is_win        : bool;           { vypis do standartneho okna nad ... }
            is_browser    : bool;           { povolenie prehliadat pred/nasl subory }
            is_scroll     : bool;           { true -> listuje nove spravy, false -> stoji nastaveny na zvolenej pozicii }
            is_txt_stream : bool;           { subor je txt/data }

            is_to_init    : bool;           { vypoctova premenna, pre inicializaciu obsahu az po vykresleni scrolleru }
            is_to_changed : bool;

            fn        : string;             { nazov zobrazeneho subora    }
            fa        : SearchRec;          { atributy zobrazeneho subora }
            fi        : word;               { pocet zobrazenych prvkov    }

            cl_SEND,cl_REC: byte;

            dxp,dyp   : int;

            private
            strs      : TstreamPackedStrings;

            public
            function    streamFN: string; virtual;
            function    streamTXT: bool; virtual;

            procedure   init_win(_title: string; x,y, dx,dy: int;
                                 _kbHot: char; _cmXXXX: word
                                ); virtual;

            constructor Init(_Owner  : PGroup;
                             _DataOb : PPObject;

                             _title  : string;

                             _x,_y, _item_dx : int;
                             _dxi,_dyi, _medzera : int; _bg : byte;
                             _page : int;
                             {_pos_en,} _sb_sam, _sb_vzdy : bool;

                             _dxb,_dyb : int;

                             _init_buttons,_handle_buttons : pointer;
                             _handler_owner : PObject;

                             _cl_SEND,_cl_REC: byte;

                             {_handler_type : TScrollAct_handler_type;
                             _handler      : pointer;
                             _handler_par  : pointer;
                             }
                             _is_win     : bool;
                             _is_browser : bool;

                             _hlpXXX : Pchar
                            );

            destructor Done; virtual;
            procedure  ReInit(x,y,dx,dy : int); virtual;

            procedure  HandleEvent(var _Event: TEvent); virtual;
            procedure  Idle(var _Event: TEvent); virtual;
            procedure  Draw; virtual;

            procedure  _active(_active_: bool);
            procedure  ActiveOn; virtual;
            procedure  ActiveOff; virtual;

            procedure  item_list_proc(i, x,y: int; b: bool); virtual;

            function   get_top: int; virtual;
            function   is_changed: bool; virtual;
            procedure  set_scrollable;

            procedure  add_data(s: string);
            procedure  new_data; virtual;
            procedure  disp_data; virtual;

            procedure  fwrite_data (data: pchars; size: word; prompt,message: string; is_utc,is_tab,is_nl: bool);
            procedure  fwrite_nl;

            function   state: bool;
          end;



    const OViewerStreamFile_decode_fn_date : TSFunc_s = nil;

    type  POViewerStreamFile  = ^OViewerStreamFile;        { Txt subor sa meni len sekvencnym sposobom, pribudaju data }
          OViewerStreamFile   = object(OScrollStream)

            fnv    : string;
            vtitle : string;

            function    streamFN: string; virtual;
            function    streamTXT: bool; virtual;


            constructor Init(_Owner  : PGroup;
                             {_DataOb : PPObject; -> ukazuje na seba, StreamViewer do okna treba naprogramovat }

                             _title  : string;
                             _fnv    : string;
                             _is_txt_stream : bool;

                             _item_dx  : int;
                             _page     : int;
                             _dxb,_dyb : int;
                             _init_buttons,_handle_buttons,_handler_owner : pointer;

                             _cl_SEND,_cl_REC: byte;

                             _is_browser : bool;

                             _hlpXXX : Pchar
                            );

            procedure  new_data; virtual;

          end;