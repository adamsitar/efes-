(*-------------------------------------------------------------------*)
(* LETVIS FDP - ASTA driver...                                       *)
(* (c) Ales Kosice 1993  (ab)                                        *)
(*-------------------------------------------------------------------*)
{$I comp.h}

{$X+,I-,S-,P-,F+,O-}
{$C FIXED PRELOAD PERMANENT}


unit _ASTA_def;


interface


     uses   TypeDef, Arrays;


     const  power_ASTA : bool = {$IFDEF LKPR_MACC} false
                                {$ELSE}            true
                                {$ENDIF};

            power_ASTA_FDP : bool = true;
            power_ASTA_PRN : bool = true;


    {$IFDEF ASTA_PRN}
     const   max__ASTA_PRNmess  = 1024;

     type    TASTA_PRNbuff   = array[0..max__ASTA_PRNmess-1] of char;

             PASTA_PRNpacket = ^TASTA_PRNpacket;
             TASTA_PRNpacket = record
               b : TASTA_PRNbuff;
               t : word
             end;

     const   ASTA_PRN_buff_size = {$IFDEF LKPR_MACC} 3
                                  {$ELSE}            10
                                  {$ENDIF};

             ASTA_PRN_buff : PBuffer = nil;

     var     b_PRN : TASTA_PRNpacket;   { zach buff }


     procedure save_ASTA_PRN(buff: PASTA_PRNpacket); far;
    {$ENDIF}


    {$IFDEF ASTA_FDP}
     const   max__ASTA_FDPmess  = 512;

     type    TASTA_FDPbuff   = array[0..max__ASTA_FDPmess-1] of char;

             PASTA_FDPpacket = ^TASTA_FDPpacket;
             TASTA_FDPpacket = record
               b : TASTA_FDPbuff;
               t : word
             end;

     const   ASTA_FDP_buff_size = 10;
             ASTA_FDP_buff : PBuffer = nil;

     var     b_FDP : TASTA_FDPpacket;   { zach buff }

     procedure save_ASTA_FDP(buff: PASTA_FDPpacket); far;
    {$ENDIF}



implementation


{$IFDEF ASTA_PRN}

  procedure save_ASTA_PRN(buff: PASTA_PRNpacket);
      begin
        if ASTA_PRN_buff<>nil then ASTA_PRN_buff^.save(buff)
      end;

{$ENDIF}


{$IFDEF ASTA_FDP}

  procedure save_ASTA_FDP(buff: PASTA_FDPpacket);
      begin
        if ASTA_FDP_buff<>nil then ASTA_FDP_buff^.save(buff)
      end;

{$ENDIF}

end.
