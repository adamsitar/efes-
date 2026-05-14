
    type   PTLGi_form = ^OTLGi_form;
           OTLGi_form = object(TFormular)

             prty : string[kod_MTK_2_PRTY];
             head : string[kod_HEAD];
             adr  : string;
             data : pchar;

             {res : string;
             ires : int;}

             p_form_ADR : PForms;
             i_form_ADR : int;

             p_form_XXX : PForms;
             i_form_XXX : int;

             o_f  : int;       { posun oproti polu adries }
             n_a  : string;    { oddelovac riadkov        }


             constructor Init (_tit : string; var f : Tcentr;
                               _head : string; _n_a : string;
                               _form_ADR : PForms; _size_ADR: int;
                               _form_XXX : PForms; _size_XXX: int;
                               _first_pos: int;
                               _adr_var: pointer;
                               _init_form, _check_func, _done_form, _image_form: pointer;
                               _inc_dy : int; _hlpXXX: Pchar
                              );

             destructor  Done; virtual;


             procedure   init_itemd  (_form_ADR : PForms; _size_ADR: int;
                                      _form_XXX : PForms; _size_XXX: int
                                     );

             procedure   init_tlg_adr; virtual;
             procedure   init_tlg_data; virtual;
             procedure   form_init  (var x,y: int; dx,dy: int;
                                     _kbHot: char; _cmXXXX: word; _title: string;
                                     _tit : byte;  _inc_dx,_inc_dy: int
                                    ); virtual;
             procedure   init_formular; virtual;

             function    _read_tlg_prty (var _prty: string;
                                         var _res: string; var _ires: int
                                        ): string; virtual;
             function    _read_tlg_adr  (size_adr: int; var _adr: string;
                                         var _res: string; var _ires: int
                                        ): string; virtual;
             function    read_tlg_adr   (size_adr: int; var _prty,_adr: string;
                                         var _res: string; var _ires: int
                                        ): string; virtual;

             function    _read_formular_data (var res: string; var ires: int): string; virtual;
             function    read_formular_data  (var res: string; var ires: int): string; virtual;
             function    read_formular       (var res: string; var ires: int) : string; virtual;

             function    check_formular_data (var res: string; var ires: int): string; virtual;
             function    check_formular: bool; virtual;

             function    send_formular (var res: string; var ires: int): string; virtual;
           end;
