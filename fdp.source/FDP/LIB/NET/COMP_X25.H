{$DEFINE RTR2}

{ IFNDEF DD_EXE}
  {$IFDEF X25}    {$DEFINE _X25} {$ENDIF}
{ ENDIF}

{ DEFINE X25_BUFFER}


{ תתתתתתתתתתתתתתתתתתתתתת
   Direktivy v comp.h
  תתתתתתתתתתתתתתתתתתתתתת

     X25                    siet X25 s niekolkymi stanicami podla X25.cfg (napr OPL)
     _X25                   jeden specializovamy uzol (napr CAMUS)
     _X25_CONNECT_TIME_OUT  hovori, ci po neuspesnom nadviazeni spojenia
                            pri inicializacii sa zastrelim, alebo este
                            chvilu vydrzim
}
