     const {$IFDEF DEBUG}
             path_E = path_B   {$IFDEF SERVER} + 's\' {$ENDIF}
                               {$IFDEF OPL}    + 'o\' {$ENDIF}
                               {$IFDEF EDD}    + 'e\' {$ENDIF}
                               {$IFDEF FDA}    + 'a\' {$ENDIF}
                               {$IFDEF BRIDGE} + 'b\' {$ENDIF}
                      ;
           {$ELSE}
             path_E = '';
           {$ENDIF}

     const { ------------------------------------------------------------ }
           { ext                                                          }
           { ------------------------------------------------------------ }

            sub_dir      = '.\';

            extDB        = 'DB';
            extERR       = 'ERR';
            extTMP       = '$$$';


            dir_cFPL     = 'FPL-C';
            dir_mFPL     = 'FPL-M';

            extRPL       = 'RPL';
            extRPP       = 'RP@';

            extPLN       = 'PLN';

            extFPL       = 'FPL';
            extFPS       = 'FPS';    { statistika  }

            ext_cFPL     = 'FPC';
            ext_mFPL     = 'FPM';
            ext_oFPL     = 'FPO';
            ext_KRL      = 'KRL';
            ext_KRLi     = 'KRI';

            extZAM       = 'ZAM';
            extDVZ       = 'DVZ';
            extQGO       = 'QGO';
            extRTZ       = 'RTZ';
            extMES       = 'MES';

            extNTM       = 'NTM';    { notamy }

            extPRZ       = 'PRZ';    { ziadosti PRS   }
            extPRN       = 'PNT';    { notamy PRS     }
            extPRN_VLIS  = 'PNV';    { nariadenia PRS }
            extPRS       = 'PRS';
            extAUP       = 'AUP';
            extUUP       = 'UUP';

            extSYN       = 'SYN';
            extMET       = 'MET';
            extMRL       = 'MRL';

            {extTLGr      = 'TLR';
            extTLGs      = 'TLS';}


            extCOM       = 'CMN';
            extDAR       = 'DAR';

            extASTA_PRN  = 'ASP';
            extASTA_FPL  = 'ASF';



     const { ------------------------------------------------------------ }
           { path                                                         }
           { ------------------------------------------------------------ }


            pathDB         = path_A+extDB+'\';

           {pathNOTAM      = path_A+extNOTAM+'\';
            pathARCH_NOTAM = path_ARCHIVES+extNOTAM+'\';}


            pathRPL        = path_A+extRPL+'\';
            pathARCH_RPL   = path_ARCHIVES+extRPL+'\';


            pathFPL        = path_A+extFPL+'\';
            pathARCH_FPL   = path_ARCHIVES+extFPL+'\';

            pathFPS        = pathFPL;
            pathARCH_FPS   = pathARCH_FPL;

            pathFPL_C      = path_A+dir_cFPL+'\';          { civilnie  -//- }
            pathARCH_FPL_C = path_ARCHIVES+dir_cFPL+'\';   { archiv }

            pathFPL_M      = path_A+dir_mFPL+'\';          { vlastne vojenske plany na den  }
            pathARCH_FPL_M = path_ARCHIVES+dir_mFPL+'\';   { archiv }


            pathZAM        = path_A+extZAM+'\';
            pathARCH_ZAM   = path_ARCHIVES+extZAM+'\';

            pathQGO        = path_A+extQGO+'\';
            pathARCH_QGO   = path_ARCHIVES+extQGO+'\';

            pathRTZ        = path_A+extQGO+'\';
            pathARCH_RTZ   = path_ARCHIVES+extQGO+'\';

            pathDVZ        = path_A+extDVZ+'\';
            pathARCH_DVZ   = path_ARCHIVES+extDVZ+'\';


            pathNTM        = path_A+extNTM+'\';
            pathARCH_NTM   = path_ARCHIVES+extNTM+'\';


            pathPRZ        = path_A+extPRZ+'\';
            pathARCH_PRZ   = path_ARCHIVES+extPRZ+'\';

            pathPRN        = {path_A+extPRN+'\';}        pathNTM;
            pathARCH_PRN   = {path_ARCHIVES+extPRN+'\';} pathARCH_NTM;

            pathPRN_VLIS      = path_A+extPRN_VLIS+'\';        {pathPRZ;}
            pathARCH_PRN_VLIS = path_ARCHIVES+extPRN_VLIS+'\'; {pathARCH_PRZ;}

            pathPRS        = path_A+extPRS+'\';
            pathARCH_PRS   = path_ARCHIVES+extPRS+'\';

            {$IFDEF FUA_DATA}
             pathAUP       = path_A+extPRS+'\'+extAUP+'\';
             pathARCH_AUP  = path_ARCHIVES+extPRS+'\'+extAUP+'\';

             pathUUP       = path_A+extPRS+'\'+extUUP+'\';
             pathARCH_UUP  = path_ARCHIVES+extPRS+'\'+extUUP+'\';
            {$ENDIF}


            pathMES        = path_A+extMES+'\';
            pathARCH_MES   = path_ARCHIVES+extMES+'\';


            pathSYN        = path_A+extSYN+'\';
            pathARCH_SYN   = path_ARCHIVES+extSYN+'\';

            pathMET        = path_A+extMET+'\';
            pathARCH_MET   = path_ARCHIVES+extMET+'\';

            pathMRL        = path_A+#255+extMRL+'\';
            {pathARCH_MRL   = path_ARCHIVES+extMRL+'\';}




            path_ACT     = path_A+#255+'ACT\';

            archdaysCOM  : int = 31;
            path_COM     = path_A+#255+'CMN\';


           {$IFDEF ARCHIVE_DAR}
            path_DAR     = path_A+#255+'DAR\';
           {$ENDIF}

           { IFDEF ARCHIVE_NET}
            cfg_archdaysNET = 'ARCHIVE NET';
            lo_archdaysNET  = 7;
            hi_archdaysNET  = 31;
            archdaysNET  : int = hi_archdaysNET;

            extPKT       = '.pkt';
           { ENDIF}

           {$IFDEF ARCHIVE_ASTA}
            path_ASTA    = path_A+#255+'ASTA\';
            archdaysASTA : int = 31;
           {$ENDIF}

           {$IFDEF ARCHIVE_OPL}
            path_OPL        = path_A+#255+'OPL\';
            extOPL          = 'OPL';
            extOPS          = 'OPS';
            cfg_archdaysOPL = 'ARCHIVE OPL';
            lo_archdaysOPL  = 7;
            hi_archdaysOPL  = 31;
            archdaysOPL     : int = hi_archdaysOPL;
           {$ENDIF}

           {$IFDEF ARCHIVE_CAMUS}
            path_CAMUS        = path_A+#255+'CAMUS\';
            extCAMUS          = 'CMS';
            cfg_archdaysCAMUS = 'ARCHIVE CAMUS';
            lo_archdaysCAMUS  = 7;
            hi_archdaysCAMUS  = 31;
            archdaysCAMUS     : int = hi_archdaysCAMUS;
           {$ENDIF}

           {$IFDEF ARCHIVE_ASOC}
            path_ASOC        = path_A+#255+'ASOC\';
            extASOC          = 'ASC';
            cfg_archdaysASOC = 'ARCHIVE ASOC';
            lo_archdaysASOC  = 7;
            hi_archdaysASOC  = 31;
            archdaysASOC     : int = hi_archdaysASOC;
           {$ENDIF}

           {$IFDEF ARCHIVE_VERA}
            path_VERA        = path_A+#255+'VERA\';
            extVERA          = 'VR';
            cfg_archdaysVERA = 'ARCHIVE VERA';
            lo_archdaysVERA  = 7;
            hi_archdaysVERA  = 31;
            archdaysVERA     : int = hi_archdaysVERA;
           {$ENDIF}


           {$IFDEF ARCHIVE_BGU}
            path_BGU      = path_A+#255+'BGU\';
            extBGU        = 'BGU';
            archdaysBGU   : int = 30;
           {$ENDIF}

            path_AFTN    = path_A+#255+'AFTN\';
            path_TLG     = path_AFTN+'TLG\';

            {archdaysTLG  = 30;
            pathTLGr     = path_A+#255+extTLGr+'\';
            pathTLGs     = path_A+#255+extTLGs+'\';}
            archdaysAFTN : int = 31 * 3;

           spath_ERR = 'ERR\';
