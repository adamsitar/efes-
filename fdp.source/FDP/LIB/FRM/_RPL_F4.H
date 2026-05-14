     type   PRPLform = ^TRPLform;
            TRPLform = object(T_FPL4_form)

              RPLn : DRPL;

              constructor Init(var _x,_y, _mode: int; _tit: string;
                               _RPLi : PRPL;
                               _novy : bool
                              );
              destructor  Done; virtual;

              procedure   init_formular; virtual;
              procedure   init_formular_by_data; virtual;

              function    read_formular: bool; virtual;
              function    check_formular: bool; virtual;
            end;
