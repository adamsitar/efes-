    {
      ---------------------------------------
       INACTIVE, PREACTIVE, COORDINATED FPLs
      תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
    }
    type  POFDR = ^TOFDR;
          TOFDR  = object(O_FPL)

            {is_to_ACTivate    : bool;
            s_ACT,s_PREACT    : bool;}

            constructor Init (_items : word);
            procedure   format_data_variables (p: pointer); virtual;

            function    get_poz(p: pointer): Tpoz; virtual;
            function    zmena_platnosti(z0,z1: Tpoz): bool; virtual;
          end;


    const oFDR : POFDR = nil;

    function  comp_xxx_FDR (FDR1,FDR2: PFDR): bool; far;
    function  _handle_o_FDR_list (var Ev: TEvent; sc: PScroller; FDR: PFDR; dx,dy: int): bool;

    function  is_FDRprop (FDR: PFDR; p: pointer): bool; far;
    function  is_FDRcoor (FDR: PFDR; p: pointer): bool; far;
