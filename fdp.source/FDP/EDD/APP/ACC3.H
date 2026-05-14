        { ------------------------------
          tabula stripov
          ------------------------------

          Obmedzenie: vlastnit moze len lstACC
        }


    type  TTablet = array[0..max_stlpec-1,0..max_skupin-1] of PlstACC;

    type  PwinACC = ^TwinACC;
          TwinACC = object(TGroup)
            Tablet  : TTablet;
            STablet : PpopisTablet;

            SpecGroups : TSpecGroups;

            stlpcov : int;
            act_stl : int;
            act_ind : int;


            constructor Init(_Owner: PGroup; _miniSTRIP: T_strip);
            destructor  Done; virtual;

            procedure   HandleEvent(var _Event: TEvent); virtual;
            procedure   Draw; virtual;

            procedure   _stlpec_i(i: int);
            procedure   _draw(_miniSTRIP: T_strip);

            function    inView(x,y: int): bool; virtual;

          { interface pre App: }
            procedure   reinit_(var rovnake: bool);
            procedure   reinit_tablet(fn: string; _kresli: bool);

          { interface pre Data: zaradenie stripov }

            procedure   add(_iFPL: PSTRIP; _ind: int; _hladaj: bool);               {virtual;}
            procedure   del(_iFPL: PSTRIP; _ind: int; _zrus: bool);  {virtual;}

            function    zarad(_iFPL: PSTRIP; _ind: int; var NDB: string; var stl,ind: int): bool;

          { interface pre GUI }
            procedure   zapni;
            procedure   vypni;

            procedure   dalsi;
            procedure   predch;

            private
            procedure   zrus_zoznamy;
            procedure   zrus_zoznam(p: PlstACC);

           { zapinanie skupin pre prehlad }
            procedure   zapni_zoznam(stl,ind: int);
            procedure   vypni_zoznam(_sprava: bool);

           { pribudanie a ubudanie stripov }

            procedure   posun_zoznamy_v_stlpci (stl, od,o: int);
            procedure   zmaz_plochu_nad_zoznammi (p: PlstACC; stl: int);

            function    zvacsi_zoznam_v_stlpci(stl,ind: int; novy: bool): bool;
            function    zmensi_zoznam_v_stlpci(p: PlstACC; stl,ind: int; posun: bool; posun_o: int): bool;

            function    zvacsi_zoznam(p: PlstACC): bool;
            function    zmensi_zoznam(p: PlstACC): bool;

            function    zvacsil_sa_zoznam(p: PlstACC): bool;
            function    zmensil_sa_zoznam(p: PlstACC): bool;

           { presun skupiny }
            procedure   vyber_zoznam (stl,ind: int; var p: PlstACC; var bol_act: bool);
            procedure   vloz_zoznam  (p: PlstACC; stl,pstl: int; bol_act: bool);
            procedure   presun_zoznam(var _Event: TEvent);


           { pomocne funkcie }
            private

            function    najdi_skupinu(NDB: string; var stl,ind: int): bool;
            function    patri_do_zoznamu(NDB: string; stl,ind: int): bool;
            function    najdi_zoznam (NDB: string; var stl,ind: int): bool;
            function    najdi_polohu (p: PlstACC;  var stl,ind: int): bool;

            function    najdi_posledny_zoznam(stl: int): PlstACC;
            function    najdi_najvacsi_zoznam(stl,ind: int; var ind_i: int): bool;

            function    is_poloha (stl,ind: int): bool;
            function    is_active (stl,ind: int): bool;

            function    najdi_zoznam_sc(var stl,ind: int;
                                        zac_stl,kon_stl : int; { zaciatocny a koncovy stlpec }
                                        zac_ind         : int; { zaciatocny riadok }
                                        smer_ind        : int  { -1 alebo 1 }
                                       ): bool;

            function    riadkov(stl, od_,do_: int): int;



           { FPLi^[ind] }
            private
            procedure   decode_mail__iFPL_ind (var _Event: TEvent; var iFPL: PSTRIP; var ind: int);
            function    najdi_zoznam_s_planom (_iFPL: PSTRIP; _ind: int; var stl,ind: int): bool;
          end;
