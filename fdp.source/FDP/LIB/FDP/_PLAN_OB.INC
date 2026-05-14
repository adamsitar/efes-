constructor TPLAN.Init(_items,_data_size: word;
                       _new_item,
                       _format_item,
                       _disp_item : pointer;

                       _eq,
                       _id,
                       _chg,
                       _poz,
                       _est{,
                       _act } : pointer;

                       _distribute : pointer;  { TNET_distribute_rdp_pkt  }
                       _send       : pointer;  { TNET_send_pkt }

                       _item_list  : pointer;
                       _item_dx,_item_dy : int;
                       _get_item_dx,_get_item_dy : pointer;
                       _p_viewer : PScrollInd;
                       {$IFDEF MAPY}
                         _p_kresli : pointer;
                       {$ENDIF}

                       var _p_PRN  : bool;
                       _p_print    : pointer;

                       _save       : pointer;
                       _zobraz     : pointer;
                       _formular   : pointer;
                       _p_comp     : pointer;  { @TBfunc_p2: bool; pre porovnanie  }
                       _p_handler  : pointer;

                       {_fn_ext : string;}
                       _p_nameDB, _p_decodeDB : pointer;
                       _riadkovDB : byte;
                       _p_codekey : pointer;

                       {_limit_act,} _limit_add, _limit_cnl, _limit_del : pint;
                       _preaktivovanie : bool;

                       _hlpXXX    : Pchar
                      );
      begin
        inherited Init(_items,_data_size, _new_item,_format_item,_disp_item);

        p_eq  := _eq;
        p_id  := _id;
        p_chg := _chg;
        p_poz := _poz;
        p_est := _est;

        p_distribute:= _distribute;
        p_send:= _send;
        p_message:= nil;

        item_list:= _item_list;
        item_dx:= _item_dx; item_dy:= _item_dy;
        get_item_dx:= _get_item_dx; get_item_dy:= _get_item_dy;
        item_dxi:= __dxi; item_dyi:= __dyi;
        item_medzera:= __medzera;
        item_bg:= __bg;

        p_viewer:= _p_viewer;
        viewer:= nil;

        {$IFDEF MAPY}
          is_map:= false;
          is_map:= true;
          p_kresli:= _p_kresli;
          {p_id_map:= nil;}
          p_GrOb:= nil;
          l4_err(a_FUA,'',0,err_MAP_NOT_FOUND,tit_GrOb);
          cl_trat:= cyan;
          typ_mapy:= map_PRSp;
          map_wrng:= true;
        {$ENDIF}

        {$IFDEF PRN} p_PRN:= @_p_PRN;  p_print:= _p_print;
        {$ELSE}      p_PRN:= @c_false; p_print:= nil;
        {$ENDIF}


        p_save:= _save;
        p_zobraz:= _zobraz;
        p_formular:= _formular;
        p_spracuj:= nil;
        p_comp:= _p_comp;

        p_handler_type:= _TBFunc_vEp3;
        p_handler:= _p_handler;


        fn_dir:= ''; fn_ext:= '';
        p_nameDB:= _p_nameDB;

        p_decodeDB:= _p_decodeDB;
        riadkovDB:= _riadkovDB;
        p_codekey:= _p_codekey;

        add_pos:= pozEST;
        {$IFDEF FDP_EDD} {$IFNDEF IDD}
          add_pos:= pozACT;
        {$ENDIF} {$ENDIF}

        p_limit_add:= _limit_add;
        p_limit_cnl:= _limit_cnl;
        p_limit_del:= _limit_del;
        {$IFDEF DB_DATA} preaktivovanie:= _preaktivovanie;
        {$ELSE}          preaktivovanie:= false;
        {$ENDIF}
        preaktivujesa:= false;

       { - implcitne bolo zmenene na false; pretoze moze dojst ku suhre
           nahod a pri nacitani moze prist sprava o spracovani planu,
           ktora sa zaradi do pamate a nacitavane plany uz nekontroluju,
           ci neexistuju v pamati
         - premmenna denny subor mala za ucel uryclit preaktivovanie,
           ale ak na danu stanicu moze dojst dany plan i z NET, EXT hrozi
           riziko zdvojenia planov, preto je od 15.6. povolena opat len pre
           plany typu FDR
       }
        denny_subor:= false;

        den_nacitania:= 0;
        last_addTime:= 0;
        tit_preactivate:= '';

        p_act:= nil;
        next_addTime:= absTime;

        last_limit_add:= 0;
        last_limit_cnl:= 0;
        last_limit_del:= 0;

        p_is_in_S:= nil;

        s_pocitam := false;
        s_loadDB  := false;

        {lst_chg := 0;}

        rozoslat  := true;
        tlacit    := true;
        vypisovat := true;

        hidding   := false;

        hlpXXX:= _hlpXXX
      end;


destructor TPLAN.Done;
     begin
       rozoslat:= false;
       vypisovat:= false;

       inherited Done;
     end;


procedure TPLAN.inicializacia_udajov(zac: bool);
    begin
    end;
