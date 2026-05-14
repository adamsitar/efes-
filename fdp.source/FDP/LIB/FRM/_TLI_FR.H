    const  setNXTPISM : TCharSet = [icao_NXT,'a'..#255];

    const  size_TLGadr = _MTK_ADR_LINEs;
           form_TLGadr : array [0..size_TLGadr-1] of TForm =

            (
             ( item : 'SS';
               title : tit_TLGtlg;
               lst : @fn_aftnTLG; pos : 1;  legal : @set_MTK_2tlg; skip : @setNil;
               dx:11; dy:10; font:0; color:0
             ),
             ( item : 'Adr1                                                              ';
               title : tit_TLGadr;
               lst : @fn_aftnADR; pos : -1; legal : @set_MTK_2adr; skip : @setNil;
               dx:35; dy:12; font:0; color:0
             ),
             ( item : 'Adr2                                                                 ';
               title : tit_TLGadr;
               lst : @fn_aftnADR; pos : -1; legal : @set_MTK_2adr; skip : @setNil;
               dx:11; dy:22; font:0; color:0
             ),
             ( item : 'Adr3                                                                 ';
               title : tit_TLGadr;
               lst : @fn_aftnADR; pos : -1; legal : @set_MTK_2adr; skip : @setNil;
               dx:11; dy:32; font:0; color:0
             )

            );
