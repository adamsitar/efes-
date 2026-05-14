{
  nacita DBF do pamate a urobi TIfunc
}
function do_alloc_DBF({ a) funkcia pre spracovanie poloziek DBF }
                           IFunc_p   : pointer;    { TIfunc <> nil }
                           parametre : pointer;    { Parmetre pre IFunc_p }

                      { b) parametre pre pole }
                           pole_adr  : pointer;    { adresa adresy pola <> nil }
                           top_adr   : pointer;    { adresa ukazovatela na vrchol <> nil}
                           max_pole  : int;        { maximum overdrive }
                           size_item : word;       { velkost polozky }

                           data_item   : pointer;  { ukazovatel na polozku typu pola ako - funkcia buffera }
                           disp_item   : pointer;  { Tproc_p odalokuje nacitany buffer }
                           data_filter : pointer;  { ukazovatel na podmienku }
                           filter      : pointer;  { TBfunc_p2: premenna, podmienky }

                           add_item    : pointer;  { Tproc_p3l alokacia, moze byt nil  }
                           del_item    : pointer;  { Tproc_p3 dealokacia, moze byt nil  }
                           vzostupne   : bool;     { smer nacitavania : true=vzostupne }

                      { c) parametre pre DBF  }
                           FN          : string;
                           riadkov     : byte;
                           DATAdecode  : pointer
                     ): int;
   begin
     m_set_shape(HODINY);
   { zistenie poctu poloziek pola }
     do_alloc_DBF:= -1;
     max_pole:= Minimum(DB_poloziek(FN,riadkov), max_pole);
     if max_pole=0 then exit;
   { alokacia }
     new_DBarray(pole_adr,max_pole,size_item);
   { nacitanie }
     new_DBitems(pole_adr,top_adr, -1, max_pole,
                 data_item,disp_item, data_filter,filter,add_item, vzostupne,
                 FN, riadkov, DATAdecode
                );
   { do it }
     if IFunc_p<>nil then do_alloc_DBF:= TIFunc_p(IFunc_p)(parametre)
     else do_alloc_DBF:= -1;
   { go to hell }
     dispose_DBitems(pole_adr,top_adr,del_item);
     dispose_DBarray(pole_adr,max_pole,size_item);
     m_restore_shape
   end;
