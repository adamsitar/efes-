    type   PHelpViewer = ^THelpViewer;
           THelpViewer = object(TObject)

             hlpXXX      : PChar;

             p_keys      : PPchars;
             top_keys    : int;
             pos_keys    : int;

             title       : string;
             d_title     : bool;
             btZ,btA,btE : PView;
             fn,fnn,kluc : string;

             p_archiv    : PSFunc_s;
             p_export    : pointer;

             constructor Init(_fn,_title: string;
                              _p_archiv: PSFunc_s; _p_export: pointer; _d_title: bool;
                              _hlpXXX: pchar
                             );
             procedure   Run(_Event: TEvent); virtual;

             procedure   read_keys;
             procedure   release_keys;

             procedure   initialize_buttons(p_help: PHelp);
             procedure   HandleEvent (var _Event: TEvent); virtual;
           end;
