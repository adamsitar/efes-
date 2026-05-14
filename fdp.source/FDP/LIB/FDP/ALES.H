     const  titKDE : string = '';

            titCR  = 'Copyright (c) ALES  1989,2001';

            FDP_id = 'ALESKE/ATC          ';

            {$IFDEF SERVER}
             titFDP = 'LETVIS FDP/S'
                        {$IFDEF FDP_OPL}            + '-OPL' {$ENDIF}
                        {$IFDEF CONNECT_TO_AFTN}    + ' A'    {$ENDIF}
                        {$IFDEF CONNECT_TO_ASTA}    + ' T'    {$ENDIF}
                        {$IFDEF CONNECT_TO_CAMUS}   + ' C'    {$ENDIF}
                        {$IFDEF CONNECT_TO_ASOC}    + ' S'    {$ENDIF}
                        {$IFDEF CONNECT_TO_OPL_EXT} + ' O'    {$ENDIF}
                        {$IFDEF CONNECT_TO_VERA}    + ' V'    {$ENDIF}
                        {$IFDEF ARCHIVE_DAR}        + ' R'    {$ENDIF};
             titVER = '4.XX.5';
            {$ENDIF}

            {$IFDEF BRIDGE}
              titFDP = 'LETVIS FDP/B-OPL';
              titVER = '3.9';
            {$ENDIF}

            {$IFDEF FDA}
              titFDP = 'LETVIS FDP/FDA';
              titVER = '4.XX.5';
            {$ENDIF}

            {$IFDEF OPL}
              titFDP = 'LETVIS FDP/OPL';
              titVER = '4.XX.5';
            {$ENDIF}

            {$IFDEF EDD}
             {$IFDEF IDD}
               titFDP = 'LETVIS FDP/IDD';
               {$IFDEF CZ} titVER = '3.1';
               {$ELSE}     titVER = '4.XX.5';
               {$ENDIF}
             {$ELSE}
               titFDP = 'LETVIS FDP/EDD';
               {$IFDEF CZ} titVER = '3.1';
               {$ELSE}     titVER = '4.XX.5';
               {$ENDIF}
             {$ENDIF}
            {$ENDIF}


            {$IFDEF POKUS}
              titFDP = 'LETVIS FDP';
              titVER = '4.X';
            {$ENDIF}



     const  {$IFDEF SERVER}
            {$ENDIF}

            {$IFDEF ACC}
              titSPC = 'ACC ';
            {$ENDIF}

            {$IFDEF AMC}
              titSPC = 'AMC ';
            {$ELSE} {$IFDEF MACC}
              {$IFDEF SK}
                titSPC = 'SRLP ';
              {$ELSE}
                titSPC = 'MACC ';
              {$ENDIF}
            {$ENDIF} {$ENDIF}

            {$IFDEF AIRBASE}
              {$IFDEF BRF}
                titSPC = 'BRF ';
              {$ENDIF}
              {$IFDEF TWR}
                {$IFDEF SK}
                  titSPC = 'LSRLP ';
                {$ELSE}
                  titSPC = 'TWR ';
                {$ENDIF}
              {$ENDIF}
              {$IFDEF APP}
                titSPC = 'APP ';
              {$ENDIF}
            {$ENDIF}

            {$IFDEF SAR}
              titSPC = 'SAR ';
            {$ENDIF}

            {$IFDEF PVO}
              {$IFDEF NS}
                titSPC = 'NS ';
              {$ELSE}
                titSPC = 'PVO ';
              {$ENDIF}
            {$ENDIF}


     const  titFOR =

            {$IFDEF SK}
               {$IFDEF MACC}
                   'SRLP Bratislava';
               {$ELSE}
                 {$IFDEF ACC}
                     'ATCC LZIB';
                 {$ELSE}
                 {$IFDEF PVO}
                     'VS Zvolen';
                 {$ELSE}
                     '';
               {$ENDIF}
               {$ENDIF}
               {$ENDIF}
            {$ENDIF}

            {$IFDEF CZ}
               {$IFDEF PRAHA}
                   'MACC Praha'
               {$ELSE}
                   ''
               {$ENDIF};
            {$ENDIF}

            {$IFDEF UK}
              {$IFDEF UKBB}
                'ATCC UKBB' {Š¨ù¢'};
              {$ENDIF}
            {$ENDIF}


     const  titTLFSK = '(++421) (0)831 6582580';
            titEMLSK = 'ales@ales.sk';
            titWWWSK = 'ales.www.sk';

            titTLFCZ = '(++420) (0)342 321105';
            titEMLCZ = 'tech.support@ales.cz';
            titWWWCZ = 'ales.www.cz';
