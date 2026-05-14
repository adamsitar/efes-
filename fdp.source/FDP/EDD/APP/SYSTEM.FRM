{
‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹
€                                                          €
€ System                                                   €
€‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹€
}

{$IFDEF ACC} {$IFDEF BLAVA} {$DEFINE ACC_BLAVA} {$ENDIF} {$ENDIF}

{$IFDEF ACC_BLAVA}

  const  size_Form_System = 1;

  const  Form_System: array [0..size_Form_System-1] of TForm =
              (
               ( item : '1     '; title: 'Archiv†cia na '; lst : nil; pos: 0;
                 legal: @setCisl; skip : @setPismCS;  dx:10 ; dy: 10; font:0; color: 0
               )
              );

  procedure System__init(p: pointer); far;
      var   ch: array[0..19] of char;
            s : string;
      begin
        Str(ArchDays:2, s);
        StrPCopy(Form_System[0].item, s+' dn°');
      end;


  procedure System_image(x0,y0,x1,y1: int); far;
      var   bp: bool; xlm,ylm: int;
      begin
        m_off (bp, xlm,ylm);
        BGIgraph.button(x0,y0,x1,y1, clBUTTON_COLOR, btSmall, btOFF);
        SetColor(clBUTTON_COLOR+clBUTTON_DARK);
        m_on (bp, xlm,ylm);
      end;


  function System__check(p: pointer): bool; far;
     var   w: word;
           b: bool;
     begin
       ArchDays := Limit(getint(strpas(Form_System[0].item),1,setPism),  7, 31, 0);
       System__check:= true
     end;


{$ELSE}

  {$IFDEF PRN} {$IFNDEF PRN_SERVER} {$DEFINE PRN_SETUP} {$ENDIF} {$ENDIF}

  {$IFDEF DEFINE PRN_SETUP}
    const size_Form_System = 2;
  {$ELSE}
    const size_Form_System = 1;
  {$ENDIF}

  const  Form_System: array [0..size_Form_System-1] of TForm =
              (
               ( item : '1      '; title: 'Down bright periode '; lst : nil; pos: 0;
                 legal: @setCisl; skip : @setPism;  dx:10 ; dy: 10; font:0; color: 0
               )
              {$IFDEF DEFINE PRN_SETUP},
               ( item : '2      '; title: 'Printer connected on'; lst : nil; pos: 0;
                 legal: @setCisl; skip : @setPism;  dx:10 ; dy: 30; font:0; color: 0
               )
              {$ENDIF}
              );

  procedure System__init(p: pointer); far;
      var   ch: array[0..19] of char;
            s : string;
      begin
        Str(ZHASNI_PO div 60:3, s);
        StrPCopy(Form_System[0].item, s+' min');
       {$IFDEF DEFINE PRN_SETUP}
         Str(PRINTER_COM:1, s);
         StrPCopy(Form_System[1].item, 'COM '+s);
       {$ENDIF}
      end;


  procedure System_image(x0,y0,x1,y1: int); far;
      var   bp: bool; xlm,ylm: int;
      begin
        m_off (bp, xlm,ylm);
        BGIgraph.button(x0,y0,x1,y1, clBUTTON_COLOR, btSmall, btOFF);
        SetColor(clBUTTON_COLOR+clBUTTON_DARK);
        m_on  (bp, xlm,ylm);
      end;


  function System__check(p: pointer): bool; far;
     var   w: word;
           b: bool;
     begin
       ZHASNI_PO   := Limit(getint(strpas(Form_System[0].item),1,setPism),  1, 60, 0)*60;
      {$IFDEF DEFINE PRN_SETUP}
        PRINTER_COM := Limit(getint(strpas(Form_System[1].item),1,setPism),  1, 4, 0);
      {$ENDIF}
       System__check:= true
     end;

  {$UNDEF DEFINE PRN_SETUP}

{$ENDIF}


procedure  formular_System;
    var    form: PFormular;
           _Event : TEvent;
    const  f   : Tcentr = (x: initX; y: initY; m:1);
    begin
      form:= New(PFormular,Init(nil, f.x,f.y, f.m, kbCtrlEnter,cmOK,
                 ' System variable ',
                 @Form_System, size_Form_System,
                 0,0,0,0,
                 1, 2, 0,0,0,0,0, clBUTTON_COLOR, {clBUTTON_COLOR, cyan, cyan, clBUTTON_COLOR-1,cllightcyan,}
                 nil,  @System__init,@System__check,nil, @System_image,
                 hlp_mnuPRGVAR)
                );
      form^.ins:= false;
      form^.RunLocalFunc(_Event,FORM_INFO);
      Dispose(form,Done)
    end;

