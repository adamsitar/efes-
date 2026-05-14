    const  send_OLDI_LAM         : bool = true;
           cl_OLDI_system_mess   : byte = 41;   { clGR7; }


    type   stat_OLDI  = ( IDLE_STATE,
                          READY_STATE,
                          CONNECTION_PENDING_STATE,
                          DATA_READY_STATE
                        );

           p_stat_OLDI =^stat_OLDI;


           event_OLDI = ( VC_Setup,    { nastavenie virt. chann }
                          VC_Clear,
                          X25_Error,

                          L_Startup,   { lokalny ... }
                          L_Shutdown,
                          L_Data,

                          R_Startup,   { prijate spravy }
                          R_Shutdown,
                          R_Data,
                          R_Heartbeat,

                          Ts_TimeOut,
                          Tr_TimeOut
                        );


    const  mess_stat_OLDI  : array[Low(stat_OLDI)..High(stat_OLDI)] of string [7] =

                           {$IFDEF SLOVAK}  ( ' IDLE  ',' READY ','PENDING',' DATA  ');
                           {$ENDIF}

                           {$IFDEF CZECH}   ( ' IDLE  ',' READY ','PENDING',' DATA  ');
                           {$ENDIF}

                           {$IFDEF ENGLISH} ( ' IDLE  ',' READY ','PENDING',' DATA  ');
                           {$ENDIF}


           message_stat_OLDI : array[Low(stat_OLDI)..High(stat_OLDI)] of pchar =

                           {$IFDEF SLOVAK}  ( 'IDLE STATE','READY STATE','CONNECTION PENDING STATE','DATA READY STATE');
                           {$ENDIF}

                           {$IFDEF CZECH}   ( 'IDLE STATE','READY STATE','CONNECTION PENDING STATE','DATA READY STATE');
                           {$ENDIF}

                           {$IFDEF ENGLISH} ( 'IDLE STATE','READY STATE','CONNECTION PENDING STATE','DATA READY STATE');
                           {$ENDIF}



