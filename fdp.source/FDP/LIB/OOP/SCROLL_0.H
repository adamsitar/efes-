    const  SCROLL_BAR__SIRKA             = 2+1 +12+ 1+2;
           MEDZERA__SCROLLER__SCROLL_BAR = 4;
           dx_SCROLL_WIN = 10 + MEDZERA__SCROLLER__SCROLL_BAR + SCROLL_BAR__SIRKA + 10;

           {$IFDEF SLOVAK}
             SCROLL_INFO = '~ PgUp Home   PgDn End~ - listuj      ~Esc~ - zru¨ v˜pis';
             SCROLL_SEL  = '~ PgUp Home   PgDn End~ - listuj    ~ÄÙ~ - vyber polo‘ku   ~Esc~ - zru¨ v˜pis';
             SCROLL_ACT  = '~ PgUp PgDn Home End~ - listuj    ';
             SCROLL_NC   = '~Ins~ o(d)zna‡ polo‘ku  ~+~ ozna‡ v¨etky  ~-~ odzna‡ vybran‚  ~*~ invertuj vybran‚';

             SCROLL_ACTF1= '~F1~ - help    ~ PgUp PgDn Home End~ - listuj    ';

             INFO_SELECT = '~Ctrl+Enter~ - voŒba filtra pre na‡¡tanie / ~V~¨etky - v¨etky polo‘ky ';
           {$ENDIF}

           {$IFDEF CZECH}
             SCROLL_INFO = '~ PgUp Home   PgDn End~ - listuj      ~Esc~ - zru¨ v˜pis';
             SCROLL_SEL  = '~ PgUp Home   PgDn End~ - listuj    ~ÄÙ~ - vyber polo‘ku   ~Esc~ - zru¨ v˜pis';
             SCROLL_ACT  = '~ PgUp PgDn Home End~ - listuj    ';
             SCROLL_NC   = '~Ins~ o(d)zna‡ polo‘ku  ~+~ ozna‡ v¨echny  ~-~ zru¨ v˜bˆr  ~*~ invertuj v˜bˆr';

             SCROLL_ACTF1= '~F1~ - help    ~ PgUp PgDn Home End~ - listuj    ';

             INFO_SELECT = '~Ctrl+Enter~ - volba filtra pre na‡ten¡ / ~V~¨echny - v¨echny polo‘ky ';
           {$ENDIF}

           {$IFDEF ENGLISH}
             SCROLL_INFO = '~  PgUp Home    PgDn End~ :  scroll    ~Esc~  cancel';
             SCROLL_SEL  = '~  PgUp Home    PgDn End~ :  scroll    ~ÄÙ~  select item   ~Esc~  cancel';
             SCROLL_ACT  = '~ PgUp PgDn Home End~ - listuj    ';
             SCROLL_NC   = '~Ins~ (un)select item   ~+~ select all  ~-~ unselect all  ~*~ invert choice';

             SCROLL_ACTF1= '~F1~ : help    ~  PgUp PgDn Home End~ :  scroll';

             INFO_SELECT = '~Ctrl+Enter~ - select data filter / A~l~l - show all items ';
           {$ENDIF}


           {LIST_EMPTY_SCROLL  : bool = true;  vypise i prazdny zoznam }
           SELECT_DOWN_SCROLL : bool = true; { po stlaceni ins, ' ' ScrollDIR odroluje }


           max_page_SCROLL_DIR = 15;
           sc_dy: int = 0;

   const  __medzera = 4;
          __dxi     = 4;
          __dyi     = 4;
          __bg      = 0;

