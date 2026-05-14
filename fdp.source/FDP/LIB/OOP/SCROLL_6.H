          { --------------------------------------------- }
          { TScrollDIR                                    }
          { --------------------------------------------- }


   { podla abecedy }
    function comp_Dir_name(p1,p2: PFileAttr): bool; far;

   { od najstarsieho }
    function comp_Dir_date(p1,p2: PFileAttr): bool; far;


    type  PScrollDIR = ^TScrollDIR;
          TScrollDIR = object(TScrollInd)

            path,name, mess : string;
            add_info  : bool;

            Dir       : PDir;                 { struktura s adresarom }
            Files     : int;                  { pocet suborov v ...   }
            items     : Ppchars;              { alternativne meno     }
            {         : PstreamPackedStrings;                         }
            select    : Pbools;

            comp_dir  : pointer;
            comp_by   : byte;

            fn : string;
            p_decode_fn : pointer;            { dekodovanie FN do ludskeho tvaru }
            p_filter    : PBFunc_s;


            constructor Init(_path,_name  : string;
                             _title,_mess : string;

                             _p_filter    : PBFunc_s;
                             _p_decode_fn : pointer;
                             _add_info    : bool;
                             _dx : int;

                             _comp_dir : pointer;  { @TBfunc_p2: bool; pre porovnanie  }
                             _comp_by  : byte;     { 0 - dir, 1 - items }
                             _handler  : pointer;  { TIFunc_s }

                             _hlpXXX : Pchar
                            );

            procedure  HandleEvent(var _Event: TEvent); virtual;
            procedure  item_list(i, x,y: int; b: bool); virtual;
            procedure  new_data; virtual;
            procedure  disp_data; virtual;

            function   do_it: int; virtual;
          end;
