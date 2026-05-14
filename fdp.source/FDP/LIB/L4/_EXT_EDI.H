   { EXT editor
   }
    type  p_type_ext_err_pkt = ^type_ext_err_pkt;
          type_ext_err_pkt = record
            fn  : string[80];         { ak pribudne nejaka alokovana polozka }
            err : string;             { treba vyhladat a prepisat vsetky odalokovania }
            pkt : pchar;              { poloziek premennej type_icao_... }
          end;


    type   PEXTEd = ^TEXTEd;
           TEXTEd = object(TEditors)

             spr_ed,spr_del : TNETtyp;

             constructor Init(_title: string;
                              var _x,_y, _mode: int;
                              _viewer : bool;
                              _riadkov,_znakov, _velkost_strany: int;

                              _write_txt,_read_txt : pointer;
                              _check_func : pointer;

                              _dxb,_dyb : int;
                              _init_buttons,_handle_buttons : pointer;
                              _handler_owner : PO_EXT;
                              _handler_data : p_type_ext_err_pkt;
                              _handle_end_state : pointer;

                              _bge,_cle, _abg,_acl, _bgv,_clv : byte;
                              _spr_ed,_spr_del : TNETtyp;
                              _hlpXXX : Pchar;

                              var _pkt : pchar
                             );

             destructor  Done; virtual;
           end;



    procedure _init_icao_editor_err_
                      (E: PEXTEd;
                       _titOK : string;
                       _ine : bool;
                       _pend,_del,_edit : TEvCmnd;
                       _a36yka : bool;
                       var yi: int
                      );

    function  _icao_editor_cancel (E : PEXTEd;
                                   O : PO_EXT;

                                   hd : p_type_ext_err_pkt
                                  ): TAnswer;

    function  _icao_editor_load   (_smer : int;
                                   _novy : bool;

                                   E : PEXTEd;
                                   O : PO_EXT;

                                   hd : p_type_ext_err_pkt;

                                   path,mask : string
                                  ): bool;

    function  _icao_editor_handle (var Ev : TEvent;

                                   E : PEXTEd;
                                   O : PO_EXT;

                                   path,mask : string;
                                   hd : p_type_ext_err_pkt;

                                   load : bool
                                  ): bool;

    function  _icao_editor_check  (E : PEXTEd;
                                   O : PO_EXT;

                                   text_adr: pchar;

                                   path,mask : string  { parameter navyse }
                                  ): bool;


    function   _icao_editor (_title: string;
                             var _x,_y, _mode: int;
                             _viewer : bool;
                             _riadkov,_znakov, _velkost_strany: int;

                             _write_txt,_read_txt : pointer;
                             _check_func : pointer;

                             _dxb,_dyb : int;
                             _init_buttons,_handle_buttons : pointer;
                             _handler_owner : PO_EXT;
                             _handler_data : p_type_ext_err_pkt;
                             _handle_end_state : pointer;

                             _bge,_cle, _abg,_acl, _bgv,_clv : byte;
                             _spr_ed,_spr_del : TNETtyp;
                             _hlpXXX : Pchar;

                             var _pkt : pchar
                            ): bool;

