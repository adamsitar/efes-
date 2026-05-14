 const  {$IFDEF SLOVAK}
          tit_i7a  = 'Identifik†cia letu :';
          tit_i13a = 'Letisko ®tartu     :';
          tit_iDAT = 'Platnosü [rr]mmdd  :';
        {$ENDIF}

        {$IFDEF CZECH}
          tit_i7a  = 'Identifikace letu  :';
          tit_i13a = 'Leti®tà startu     :';
          tit_iDAT = 'Platnost [rr]mmdd  :';
        {$ENDIF}

        {$IFDEF ENGLISH}
          tit_i7a  = 'Flight call sign   :';
          tit_i13a = 'Departure airbase  :';
          tit_iDAT = 'Validity [yy]mmdd  :';
        {$ENDIF}


        {$IFDEF GOST}  item_7a = '12345678';
        {$ELSE}        item_7a = '1234567';
        {$ENDIF}


        size_key_fpl  = 6;
        size_key_rpl  = 4;

        i_key_fpl_7a  = 1;
        i_key_fpl_13a = 3;
        i_key_fpl_DAT = 5;


        form_key_fpl : array [0..size_key_fpl-1] of TForm =

          (( item : tit_i7a ; title : tit_i7a;
             lst : nil; pos: 1; legal: @setNil; skip : @setNil;
             dx:10; dy:10; font:0; color: white
           ),
           ( item : item_7a; title : tit_i7a;
             lst : nil; pos: 1; legal: @setABC; skip : @setNil;
             dx:160; dy:10; font:0; color: white
           ),

           ( item : tit_i13a; title: tit_i13a;
             lst : nil; pos: 1; legal: @setNil; skip : @setNil;
             dx:10; dy:25; font:0; color: 0
           ),
           ( item : '2   '; title: tit_i13a;
             lst : nil{@fn_13a}; pos: 1; legal: @setABC; skip : @setNil;
             dx:160; dy:25; font:0; color: 0
           ),

           ( item : tit_iDAT; title: tit_iDAT;
             lst : nil; pos: -1; legal: @setNil;  skip : @setNil;
             dx:10; dy:40; font:0; color: 0
           ),
           ( item : '3     '; title: tit_iDAT;
             lst : nil; pos: -1; legal: @setCisl; skip : @setNil;
             dx:160; dy:40; font:0; color: 0
           )
          );


