{$I comp.h}

{$IFDEF IDD}
  {$DEFINE  EDD}
{$ENDIF}


unit ParStr;


interface


    const   psIGNORE_PASSWORD = 'IPW';

            psNDB_RTE         = 'CHECK_NDB_RTE';

           {$IFDEF EDD}
            psLOAD_PROPOSED   = 'LOAD_PROPOSED';
           {$ENDIF}

           {$IFDEF MAPY}
            psINIT_SYM        = 'INIT_SYM';
            psINIT_MAP        = 'INIT_MAP';
           {$ENDIF}

            psDATA_FORMAT     = 'DATA_FORMAT';    { Povolenie kontrolovat a nasledne konvertovat format udajov pri starte }
          {
          psNONET           = 'NONET';
          psNOINIT          = 'NOINIT';
          psNOSAVE          = 'NOSAVE';
          }


implementation

end.


