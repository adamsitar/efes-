{
‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹
€                                                          €
€ Definicia stuktur adresarov                              €
€‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹€
}

type   TypeOfArchive = (not_archive, by_hours,by_days,by_months);

       Tarch_nmb = pint;

       Tdata_dir = record
         d : pchar;           { directory          }
         a : pchar;           { archive directory  }
         i : bool;            { podla mena         }
         t : TypeOfArchive;   { sposob zalohovania }
         n : Tarch_nmb        { pocet jednotiek    }
       end;


const  max_data_dir =                          2
                         { IFDEF RPL}        + 1
                         { ENDIF}

                         {$IFDEF FPL}        + 1  {$ENDIF}
                         {$IFDEF FPL0}       + 2  {$ENDIF}

                         {$IFDEF ZAM}        + 1  {$ENDIF}
                         {$IFDEF QGO}        + 1  {$ENDIF}
                         {$IFDEF RTZ}        + 1  {$ENDIF}
                         {$IFDEF DVZ}        + 1  {$ENDIF}

                         {$IFDEF PRZ}        + 3  {$ENDIF}
                         {$IFDEF PRS}        + 1
                           {$IFDEF FUA_DATA} + 2
                           {$ENDIF}
                         {$ENDIF}

                         {$IFDEF SPR}        + 1  {$ENDIF}

                         {$IFDEF MET}        + 2
                           {$IFDEF MET_RLI} {+ 1}
                           {$ENDIF}
                         {$ENDIF}
                         ;

       data_dir : array[0..max_data_dir-1] of Tdata_dir =

                       (                    (d : path_A+#255+'\';
                                             a : path_ARCHIVES;
                                             i : false;
                                             t : not_archive;
                                             n : nil
                                            ),


                                            (d : pathDB;
                                             a : pathDB;
                                             i : false;
                                             t : not_archive;
                                             n : nil
                                            )


                         { IFDEF RPL},      (d : pathRPL;
                                             a : pathRPL;
                                             i : false;
                                             t : not_archive;
                                             n : nil
                                            )
                         { ENDIF}

                         {$IFDEF FPL},      (d : pathFPL;
                                             a : pathARCH_FPL;
                                             i : true;
                                             t : by_days;
                                             n : @ArchDays
                                            )
                         {$ENDIF}

                         {$IFDEF FPL0},     (d : pathFPL_C;
                                             a : pathARCH_FPL_C;
                                             i : true;
                                             t : by_days;
                                             n : @ArchDays
                                            ),

                                            (d : pathFPL_M;
                                             a : pathARCH_FPL_M;
                                             i : true;
                                             t : by_hours;
                                             n : @ArchDays
                                            )
                         {$ENDIF}

                         {$IFDEF ZAM},      (d : pathZAM;
                                             a : pathARCH_ZAM;
                                             i : true;
                                             t : by_days;
                                             n : @ArchDays
                                            )
                         {$ENDIF}

                         {$IFDEF QGO},      (d : pathQGO;
                                             a : pathARCH_QGO;
                                             i : true;
                                             t : by_days;
                                             n : @ArchDays
                                            )
                         {$ENDIF}

                         {$IFDEF RTZ},      (d : pathQGO;
                                             a : pathARCH_QGO;
                                             i : true;
                                             t : by_days;
                                             n : @ArchDays
                                            )
                         {$ENDIF}

                         {$IFDEF DVZ},      (d : pathDVZ;
                                             a : pathARCH_DVZ;
                                             i : true;
                                             t : by_days;
                                             n : @ArchDays
                                            )
                         {$ENDIF}


                         {$IFDEF PRZ},
                                            (d : pathPRZ;
                                             a : pathARCH_PRZ;
                                             i : true;
                                             t : by_months;
                                             n : @ArchMonths
                                            ),

                                            (d : pathPRN;
                                             a : pathARCH_PRN;
                                             i : true;
                                             t : by_months;
                                             n : @ArchMonths
                                            ),

                                            (d : pathPRN_VLIS;
                                             a : pathARCH_PRN_VLIS;
                                             i : true;
                                             t : by_months;
                                             n : @ArchMonths
                                            )
                         {$ENDIF}

                         {$IFDEF PRS},      (d : pathPRS;
                                             a : pathARCH_PRS;
                                             i : true;
                                             t : by_days;
                                             n : @ArchDays
                                            )
                          {$IFDEF FUA_DATA}
                                           ,(d : pathAUP;
                                             a : pathARCH_AUP;
                                             i : true;
                                             t : by_days;
                                             n : @ArchDays
                                            )
                                           ,(d : pathUUP;
                                             a : pathARCH_UUP;
                                             i : true;
                                             t : by_days;
                                             n : @ArchDays
                                            )
                          {$ENDIF}
                         {$ENDIF}


                         {$IFDEF SPR},      (d : pathMES;
                                             a : pathARCH_MES;
                                             i : true;
                                             t : by_days;
                                             n : @ArchDays
                                            )
                         {$ENDIF}

                         {$IFDEF MET},      (d : pathSYN;
                                             a : pathARCH_SYN;
                                             i : true;
                                             t : by_hours;
                                             n : @ArchDays
                                            ),

                                            (d : pathMET;
                                             a : pathARCH_MET;
                                             i : true;
                                             t : by_hours;
                                             n : @ArchDays
                                            )
                          (*{$IFDEF MET_RLI}  ,
                                            (d : pathMRL;
                                             a : pathARCH_MRL;
                                             i : false;
                                             t : by_days;
                                             n : @ArchDays
                                            )
                          {$ENDIF}*)
                         {$ENDIF}
                       );


const  max_stream_dir =   { IFDEF ARCHIVE_COM}   + 1
                          { ENDIF}

                          {$IFDEF ARCHIVE_NET}   + 1
                          {$ENDIF}
                          {$IFDEF ARCHIVE_DAR}   + 1
                          {$ENDIF}

                          {$IFDEF ARCHIVE_AFTN}  + 1
                          {$ENDIF}
                          {$IFDEF ARCHIVE_ASTA}  + 1
                          {$ENDIF}
                          {$IFDEF ARCHIVE_CAMUS} + 1
                          {$ENDIF}
                          {$IFDEF ARCHIVE_ASOC}  + 1
                          {$ENDIF}
                          {$IFDEF ARCHIVE_VERA}  + 1
                          {$ENDIF}

                          {$IFDEF ARCHIVE_OPL}   + 1
                          {$ENDIF}
                          {$IFDEF ARCHIVE_BGU}   + 1
                          {$ENDIF}

                          {$IFDEF MET}
                            {$IFDEF MET_RLI}     + 1
                            {$ENDIF}
                          {$ENDIF}
                          ;


       stream_dir : array[0..max_stream_dir-1] of Tdata_dir =

                       (
                         { IFDEF ARCHIVE_COM}   (d : path_COM;
                                                 a : nil;
                                                 i : false;
                                                 t : by_days;
                                                 n : @archdaysCOM
                                                )
                         { ENDIF}

                         {$IFDEF ARCHIVE_NET}  ,(d : path_NET;
                                                 a : nil;
                                                 i : false;
                                                 t : by_days;
                                                 n : @archdaysNET
                                                )
                         {$ENDIF}
                         {$IFDEF ARCHIVE_DAR}  ,(d : path_DAR;
                                                 a : nil;
                                                 i : false;
                                                 t : by_days;
                                                 n : @ArchDays
                                                )
                         {$ENDIF}

                         {$IFDEF ARCHIVE_AFTN} ,(d : path_AFTN;
                                                 a : nil;
                                                 i : false;
                                                 t : by_days;
                                                 n : @archdaysAFTN
                                                )
                         {$ENDIF}

                         {$IFDEF ARCHIVE_ASTA} ,(d : path_ASTA;
                                                 a : nil;
                                                 i : false;
                                                 t : by_days;
                                                 n : @archdaysASTA
                                                )
                         {$ENDIF}

                         {$IFDEF ARCHIVE_CAMUS},(d : path_CAMUS;
                                                 a : nil;
                                                 i : false;
                                                 t : by_days;
                                                 n : @archdaysCAMUS
                                                )
                         {$ENDIF}

                         {$IFDEF ARCHIVE_ASOC},(d : path_ASOC;
                                                 a : nil;
                                                 i : false;
                                                 t : by_days;
                                                 n : @archdaysASOC
                                                )
                         {$ENDIF}

                         {$IFDEF ARCHIVE_OPL}  ,(d : path_OPL;
                                                 a : nil;
                                                 i : false;
                                                 t : by_days;
                                                 n : @archdaysOPL
                                                )
                         {$ENDIF}

                         {$IFDEF ARCHIVE_VERA},(d : path_VERA;
                                                 a : nil;
                                                 i : false;
                                                 t : by_days;
                                                 n : @archdaysVERA
                                                )
                         {$ENDIF}

                         {$IFDEF ARCHIVE_BGU}  ,(d : path_BGU;
                                                 a : nil;
                                                 i : false;
                                                 t : by_days;
                                                 n : @archdaysBGU
                                                )
                         {$ENDIF}

                         {$IFDEF MET}
                          {$IFDEF MET_RLI}  ,
                                                (d : pathMRL;
                                                 a : nil;
                                                 i : false;
                                                 t : by_days;
                                                 n : @ArchDays
                                                )
                          {$ENDIF}
                         {$ENDIF}
                       );
