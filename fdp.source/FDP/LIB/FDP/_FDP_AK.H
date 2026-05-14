
   type    fdp_src = (user,letvis,
                      rpl_,
                      ext_, aftn,asta,camus,asoc,opl_ext,vera
                     );

           set_fdp_src = set of fdp_src;


   type    Tfdp_co_ordinate_procedure = procedure (src: fdp_src; dst: set_fdp_src;
                                                   typ: TNETtyp; head: Thead_ICAO;
                                                   zmeneny: bool;
                                                   var plan
                                                  );

   procedure _fdp_co_ordinate_procedure (src: fdp_src; dst: set_fdp_src;
                                         typ: TNETtyp; head: Thead_ICAO;
                                         zmeneny: bool;
                                         var plan
                                        );

   const   fdp_co_ordinate_procedure: Tfdp_co_ordinate_procedure = _fdp_co_ordinate_procedure;

