     type   PTxtFileEditor = ^TTxtFileEditor;
            TTxtFileEditor = object(TEditors)

              fn,ini  : pchar; { uchovanie nazvu povodneho subora }

              TxtFile : PTxtFileBuffer;

              constructor Init(_Owner : PGroup;
                               var _x,_y, _mode: int; _cmXXXX: word;
                               _title   : string;

                               _win_en  : bool;
                               _viewer  : bool;
                               _strana  : pointer; _riadkov,_znakov, _velkost_strany: int;

                               _fn,_tmp,_ini : string;

                               _odd_rdk,                 { oddelovac riadkov na vstupe }
                               _odd_slv : TCharSet;
                               _odd_rdkr: string;        { oddelovac riadkov na vystupe }

                               _check_func : pointer;    { TBFunc_p3(@Self,handler_owner,text_adr) }

                               _dxb,_dyb       : int;
                               _init_buttons,

                               _handle_buttons : pointer;
                               _handler_owner  : PObject;
                               _handler_data   : pointer;

                               _bge,_cle, _bga,_cla, _bgv,_clv : byte;
                               _hlpXXX : Pchar
                              );

              destructor  Done; virtual;

              procedure   __write_in_editor (_text_adr: pointer; _text_len: word); virtual;
              procedure   __read_from_editor; virtual;

              procedure   handle_buttons(var _Event: TEvent); virtual;
              {procedure   make_message; virtual;}
            end;
