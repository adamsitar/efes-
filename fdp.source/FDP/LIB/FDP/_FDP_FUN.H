    procedure PLANY_init;
    procedure PLANY_done;
    procedure PLANY_load;


    {$IFDEF DEMO}
      const  initialize_fdp_records : bool = true;
    {$ENDIF}


    {$IFDEF FPL0}

      {$IFDEF MAPY}
        procedure mapa_handle_target(var _Event: TEvent); far;
        procedure imit_targets(mapa_init: bool); far;
        procedure mapa_cursor_shape; far;

        procedure show_targets; far;
        procedure hide_targets; far;
      {$ENDIF}

    {$ENDIF}

