{$IFDEF SLOVAK}
  const _prop    : pchar = 'NAVRHOVANê  :';
        _acc     : pchar = 'PREVZATê    :';
        _org_by  : pchar = 'RADENIE     :';
        _sort_by : pchar = 'TRIEDENIE   :';
        _sect_by : pchar = 'SEKTORIZèCIA:';
        _hidden  : pchar = 'POTLAÄENê   :';

        _org  : array[false..true] of pchar =
                     ('BOD NA TRATI','VSTUPNù BOD');
        _sort : array[sort_ndb..high(Tsort_strip)] of pchar =
                     ('BOD','INDEX','ETO/ETD','VùõKA LETU');
        _sec  : array[false..true] of pchar =
                     ('CEZ SEKTOR','V SEKTORE');
        _seci : array[false..true] of pchar =
                     ('DO FIR','SEKTORA');
{$ENDIF}

{$IFDEF CZECH}
  const _prop    : pchar = 'NAVRHOVANê  :';
        _acc     : pchar = 'PûEVZATê    :';
        _org_by  : pchar = 'ûAZENã      :';
        _sort_by : pchar = 'TûãDEN°     :';
        _sect_by : pchar = 'SEKTORIZACE :';
        _hidden  : pchar = 'POTLAÄENã   :';

        _org  : array[false..true] of pchar =
                     ('BOD NA TRATI','VSTUPNã BOD');
        _sort : array[sort_ndb..high(Tsort_strip)] of pchar =
                     ('BOD','INDEX','ETO/ETD','VùõKA LETU');
        _sec  : array[false..true] of pchar =
                     ('PûES SEKTOR','V SEKTORU');
        _seci : array[false..true] of pchar =
                     ('DO FIR','DO SEKTORU');
{$ENDIF}

{$IFDEF ENGLISH}
  const _prop    : pchar = 'PROPOSED    :';
        _acc     : pchar = 'ACCEPTED    :';
        _org_by  : pchar = 'ORGANIZE BY :';
        _sort_by : pchar = 'SORT BY     :';
        _sect_by : pchar = 'SECTORIZE   :';
        _hidden  : pchar = 'HIDDEN      :';

        _org  : array[false..true] of pchar =
                     ('HEADING POINT','INPUT POINT');
        _sort : array[sort_ndb..high(Tsort_strip)] of pchar =
                     ('POINT','INDEX','ETO/ETD','FLIGHT LEVEL');
        _sec  : array[false..true] of pchar =
                     ('THROUGH SECTOR','IN SECTOR');
        _seci : array[false..true] of pchar =
                     ('ON FIR','ON SECTOR');
{$ENDIF}
