
      const  gr_Poly    = 1;
             gr_FPoly   = 2;
             gr_KrVys   = 3;
             gr_FKrVys  = 4;
             gr_Kruz    = 5;
             gr_FKruz   = 6;
             gr_SusKruz = 7;
             gr_SusAzim = 8;
             gr_StSiet  = 9;
             gr_Mark10  = 10;
             gr_Mark11  = 11;

             gr_TPoly   = 101;
             gr_Mark13  = 113;



      const { a) Priority vykreslenia map, su pouzivane aj ako ich kody,
                 pretoze takato polozka zatial v datach nie je,
                 a... zisla by sa

              b) Priorita niektorych map nie je dobre navrhnuta, preto
                 sa programovo meni
            }

             { fill :     FIR(FIR)        ciary: FIR+1
                          SEC                    SEC+1
                          SEC.APP                SEC.APP+1
                          TMA                    >P
                          CTR
                          AWY
                          R
                          P

             }

              map_FIRf   = 100;         {  ... typ mapy         }
              map_FIR    = 1100;

              map_ACCf   = 200;
              map_ACC    = 1200;
              map_ACCsecf= 210;
              map_ACCsec = 1210;

              map_APPf   = 300;
              map_APP    = 1300;
              map_APPsecf= 310;
              map_APPsec = 1310;

              map_AWYf   = 400;         {  ... koridory, stredy koridorov }
              map_AWY    = 1400;
              map_AWY_   = 1410;
              map_ILS_   = 1420;


              map_TMAf   = 500;
              map_TMA    = 1500;

              map_CTRf   = 600;
              map_CTR    = 1600;


              map_Rf     = 700;
              map_R      = 1700;

              map_Pf     = 800;         { ... zakazany priestor P  }
              map_P      = 1800;


              map_ZAMp   = 600;
              map_ZAMa   = 601;

              map_PRSp   = 710;         { ... aktivovany a planovany priestor R alebo D }
              map_PRSa   = 711;

              map_TSAp   = 720;         { ... aktivovany a planovany priestor TSA }
              map_TSAa   = 721;


              map_PAV0   = 5510;        { ... pavuk jemny, hruby }
              map_PAV1   = 5500;

              map_LDM0   = 5620;
              map_LDM1   = 5610;
              map_LDM2   = 5600;

              map_MARK   = 8000;


            { Povodne hodnoty,
              nenastavene spravne sa musia transformovat
              kvoli spravnemu poradiu map
            }

      const   cfg_PRTY0 = 'OBSOLETE PRIORITY';
              PRTY0: bool = {$IFDEF UA} false {$ELSE} true {$ENDIF};


      const   _map_FIRf   = 100;         {  ... typ mapy         }
              _map_FIR    = 200;

              _map_AWYf   = 750;         {  ... koridory, stredy koridorov }
              _map_AWY    = 1000;
              _map_ILS_   = 1300;
              _map_AWY_   = 1400;

              _map_TMAf   = 400;
              _map_TMA    = 500;

              _map_CTRf   = 600;
              _map_CTR    = 700;

              _map_Rf     = 800;         { AMC spracovane priestory }
              _map_R      = 900;

              _map_Pf     = 1000;        { ... zakazany priestor P  }
              _map_P      = 1100;

              _map_PAV0   = 8000;        { ... pavuk jemny, hruby }
              _map_PAV1   = 8010;

              _map_LDM2   = 8100;
              _map_LDM1   = 8110;
              _map_LDM0   = 8120;

              _map_MARK   = 1700;


      const  map_DESC     =  9900;
             map_FPL      = 10000;


      const { Farby typov map
            }

             cl_FIRf    : byte =  33;     cfg_cl_FIRf    = 'FIR F';
             cl_FIR     : byte =  clGR6;  cfg_cl_FIR     = 'FIR';

             cl_ACCf    : byte =  34;     cfg_cl_ACCf    = 'ACC F';
             cl_ACC     : byte =  clGR6;  cfg_cl_ACC     = 'ACC';
             cl_ACCsecf : byte =  35;     cfg_cl_ACCsecf = 'ACC SEC F';
             cl_ACCsec  : byte =  clGR6;  cfg_cl_ACCsec  = 'ACC SEC';

             cl_APPf    : byte =  34;     cfg_cl_APPf    = 'APP F';
             cl_APP     : byte =  clGR6;  cfg_cl_APP     = 'APP';
             cl_APPsecf : byte =  36;     cfg_cl_APPsecf = 'APP SEC F';
             cl_APPsec  : byte =  clGR6;  cfg_cl_APPsec  = 'APP SEC';

             cl_AWYf    : byte =  35;         cfg_cl_AWYf = 'AWY F';
             cl_AWY     : byte =  clGR7{36};  cfg_cl_AWY  = 'AWY';
             cl_AWY_    : byte =  clGR6;      cfg_cl_AWY_ = 'AWY_';
             cl_ILS_    : byte =  clGR5;      cfg_cl_ILS_ = 'ILS_';


             cl_TMAf    : byte =  36;         cfg_cl_TMAf = 'TMA F';
             cl_TMA     : byte =  clGR5{37};  cfg_cl_TMA  = 'TMA';

             cl_CTRf    : byte =  37;         cfg_cl_CTRf = 'CTR F';
             cl_CTR     : byte =  clGR5{38};  cfg_cl_CTR  = 'CTR';

             cl_Rf      : byte =  45;         cfg_cl_Rf   = 'R F';
             cl_R       : byte =  clGR6{46};  cfg_cl_R    = 'R';

             cl_Pf      : byte =  Red;        cfg_cl_Pf   = 'P F';
             cl_P       : byte =  Red;        cfg_cl_P    = 'P';


             cl_ZAMp    : byte =  41;     cfg_cl_ZAMp = 'ACT P';
             cl_ZAMa    : byte =  39;     cfg_cl_ZAMa = 'ACT A';

             cl_PRSp    : byte =  48;     cfg_cl_PRSp = 'PRS P';
             cl_PRSa    : byte =  47;     cfg_cl_PRSa = 'PRS A';
             cl_TSAp    : byte =  49;     cfg_cl_TSAp = 'TSA P';
             cl_TSAa    : byte =  47;     cfg_cl_TSAa = 'TSA A';


             cl_PAV0    : byte =  clGR3;  cfg_cl_PAV0 = 'PAV0';
             cl_PAV1    : byte =  clGR4;  cfg_cl_PAV1 = 'PAV1';

             cl_LDM0    : byte =  clGR7;  cfg_cl_LDM0 = 'LDM0';
             cl_LDM1    : byte =  clGR5;  cfg_cl_LDM1 = 'LDM1';
             cl_LDM2    : byte =  clGR4;  cfg_cl_LDM2 = 'LDM2';

             cl_MARK    : byte =  clGR8;  cfg_cl_MARK = 'MARK';
             cl_DESC    : byte =  yellow; cfg_cl_DESC = 'DESC';



      const  GRP_magic_number_KRASOVSKIJ = $ADECADEF;
             GRP_magic_number_WGS84      = $FFFFADEF;

