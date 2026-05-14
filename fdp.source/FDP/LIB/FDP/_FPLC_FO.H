          {
           ‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹
           €                      €
           € TcFPLform            €
           €‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹€
          }
     type   PcFPLform = ^TcFPLform;
            TcFPLform = object(TFDP_AForm)
              {kresli: pointer;}

              FPL,FPLp  : DcFPL;
              copy_data : bool;

              btSSR,
              btSSU,
              btNDB,
              btRTE,
              btIns,
              btDel : PButton;

              public
              check_ssr : bool;

              procedure   init_buttons(x,y: int); virtual;

              constructor Init(var _x,_y, _mode: int; _title: string;

                               FPLi  : PDcFPL;
                               _src  : fdp_src;
                               _novy : bool;

                               _tit  : string;
                               _pos  : int;
                               _ssr, _viewer,_copy_data : bool
                              );

              destructor  Done; virtual;

              procedure   HandleEvent(var _Event: TEvent); virtual;
              procedure   draw_buttons;  virtual;

              procedure   vlozeny_text(kde: int; s: string); virtual;
              procedure   vloz_trat;
            end;


