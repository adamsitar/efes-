          { doplni a nahradi TDynamic, ak bude cas }

     type  PDynamic2 = ^TDynamic2;
           TDynamic2 = object(TDynamic)

              new_item, disp_item: pointer;
              semaphor: bool;

              constructor Init    (_items,_data_size: word;
                                   _new_item,_format_item,_disp_item: pointer
                                  );

              function    NewData (p: pointer): pointer; virtual;
              procedure   DispData(var p: pointer); virtual;

              function    include_DBitem (data     : pointer;     { udaje }
                                          p_filter : pointer;     { zaznam s udajmi podmienok pre nacitanie }
                                          p_data   : PBFunc_p2    { kontrola pripustnosti nacitania }
                                         ): bool;

              procedure   read_DBitems  (FN        : string;
                                         riadkov   : byte;
                                         p_decode  : pointer;

                                         p_filter : pointer;     { zaznam s udajmi podmienok pre nacitanie }
                                         p_kluc   : PBFunc_p2;   { porovnanie identifikacnych udajov }
                                         p_stav   : PBFunc_p2;   { porovnanie inych udajov }
                                         p_data   : PBFunc_p2;   { porovnanie dekodovanych udajov }

                                         vzostupne : bool        { smer nacitavania : true=vzostupne }
                                        );
           end;



     type  PAPchar = ^TAPchar;
           TAPchar = object(TDynamic)
             constructor  Init     (_items: word);
             function     NewData  (p: pointer): pointer; virtual;
             procedure    DispData (var p: pointer); virtual;
           end;
