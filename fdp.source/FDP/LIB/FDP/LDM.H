      { Neskor napisat cfg subor pre ich nacitanie
      }


      type   str8 = string[8];
             str2 = string[2];

      const devat  : array[0..2,0..2] of char = (('7','8','1'),('6','9','2'),('5','4','3'));
            styri  : array[0..1,0..1] of char = (('4','1'),('3','2'));

            setD   : TcharSet = ['1'..'9'];
            setM   : TcharSet = ['1'..'4'];


      { -------------------
         S L O V E N S K O
        -------------------
      }

      {$IFDEF LZ}
       const  setL  : TcharSet = ['N','H','M',
                                  'P','D','V',
                                      'Z','A',
                                      'Q','G',
                                          'Y'
                                 ];

              krok_s   = 1.0;
              krok_d   = 1.5;

              ld_s     = 47;
              ld_d     = 16.5;

       type   stupne_d = 16..24;
              stupne_s = 47..50;
              minsek   = 0..59;

       const  LDMs   = 5; { stlpcov }
              LDMr   = 3; { riadkov }
              LDMcod : array[0..LDMs-1,0..LDMr-1] of str2 =
                       (('N','H','M'),
                        ('P','D','V'),
                        ('?','Z','A'),
                        ('?','Q','G'),
                        ('?','?','Y')
                       );
      {$ENDIF}



      { -------------------
         C E S K O
         ------------------
      }

      {$IFDEF LK}
       const  setL  : TcharSet = ['X','B','R',
                                  'I','E','F','U',
                                  'O','L','C','W',
                                  'H','M','K',
                                  'D','V','T'
                                 ];

              krok_s   = 1.0;
              krok_d   = 1.5;

              ld_s     = 48;  { X }
              ld_d     = 12;

       type   stupne_d = 12..20;
              stupne_s = 48..52;
              minsek   = 0..59;

       const  LDMs   = 5; { stlpcov }
              LDMr   = 4; { riadkov }
              LDMcod : array[0..LDMs-1,0..LDMr-1] of str2 =
                      (('X','B','R','?'),
                       ('I','E','F','U'),
                       ('O','L','C','W'),
                       ('H','M','K','?'),
                       ('D','V','T','?')
                      );
     {$ENDIF}


     { -------------------
       U K R A J I N A
       -------------------
     }
     {$IFDEF UKBB}
      const  setL  : TcharSet = ['X','B','R',
                                 'I','E','F','U',
                                 'O','L','C','W',
                                 'H','M','K',
                                 'D','V','T'
                                ];

             krok_s   = 1.0;
             krok_d   = 1.5;

             ld_s     = 48;  { X }
             ld_d     = 12;

      type   stupne_d = 12..25;
             stupne_s = 48..51;
             minsek   = 0..59;

      const  LDMs   = 5; { stlpcov }
             LDMr   = 4; { riadkov }
             LDMcod : array[0..LDMs-1,0..LDMr-1] of str2 =
                     (('X','B','R','?'),
                      ('I','E','F','U'),
                      ('O','L','C','W'),
                      ('H','M','K','?'),
                      ('D','V','T','?')
                     );
     {$ENDIF}
