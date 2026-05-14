  { Telegram ma sirku MTK_2_LINE znakov
  }

   const form_TLGaftn_i : array [0..0] of TForm =

            ((item : 'Tlg                                                                  ';
              title : tit_TLGtxt;
              lst : nil; pos : -1; legal : @set_MTK_2abc; skip : @setNil;
              dx:10; dy:10; font:0; color:0
             )
            );

         form_TLGaftn   : PForms = nil;


   type   PTLG_form = ^OTLG_form;
          OTLG_form = object(OTLGi_form)

            function   _read_formular_data (var res: string; var ires: int): string; virtual;
          end;
