     type  Tsort_strip     = (sort_imp, sort_ndb, sort_idn, sort_eto, sort_fl);

     const Text_sort_strip : array[low(Tsort_strip)..high(Tsort_strip)] of char = (' ','P','I','T','F');
           dx_mnu_zozstrip = 150;

           STRIP_SORT : Tsort_strip = sort_idn;



     {function  _is_mini_strip: T_strip;

     function  dx_sc_iFPL: int;
     function  dy_sc_iFPL: int;}

     function  _idn_bk(est_,cor_: bool; bk: byte): int;
     procedure write_ACK(x,y, dx: int; bk: byte; rec: Tplan_rec);


     {$IFDEF MAPY}
       procedure _tgrt_label_xy(idn: string; x,y: int; var sur: Tsur);
       procedure draw_trgt(idn,ssr: string; x,y: int; var sur: Tsur; maz: bool; cl: byte);

       procedure draw_trgt_history(sur: Tsur; maz: bool; cl: byte); far;
       procedure draw_trgt_history_point(x,y: int; maz: bool; cl: byte); far;
     {$ENDIF}

