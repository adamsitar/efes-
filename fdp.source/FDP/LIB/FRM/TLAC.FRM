{$IFDEF PRN}

  const  Form_Tlac: array [0..0] of TForm =
              (
               ( item : '  '; title: 'Posun textu'; lst : nil; pos: 0;
                 legal: @setCisl; skip : @setPism;  dx:10 ; dy:  8; font:0; color: 0
               )
              );


  procedure System_image(x0,y0,x1,y1: int); far;
      var   bp : bool; xl,yl : int;
      begin
        m_off(bp, xl,yl);
        BGIgraph.button(x0,y0,x1,y1, clBUTTON_COLOR, btSmall, btOFF);
        SetColor(clBUTTON_COLOR+clBUTTON_DARK);
        m_on(bp, xl,yl);
      end;


  procedure Tlac__init(p: pointer); far;
      var   ch: array[0..19] of char;
            s : string;
      begin
        Str(PRN_TAB:2, s);
        StrPCopy(Form_Tlac[0].item, s);
      end;


  function Tlac__check(p: pointer): bool; far;
     begin
       PRN_TAB:= Limit(getint(strpas(Form_Tlac[0].item),1,setPism), 0,20, 0);
       Tlac__check:= true
     end;


  procedure  formular_Tlac;
      var    form : PFormular;
             _Ev  : TEvent;
      const  f    : Tcentr = (x: initX; y: initY; m:1);
      begin
        form:= New(PFormular,Init(nil, f.x,f.y, f.m, kbEnter,cmOK,
                   'Tla‡',
                   @Form_Tlac, 1,
                   0,0,0,0,
                   1, 2, 0,0,0,0,0, clBUTTON_COLOR, {clBUTTON_COLOR, cyan, cyan, clBUTTON_COLOR-1,cllightcyan,}
                   nil,  @Tlac__init,@Tlac__check,nil, @System_image, false,false,false,nil {hlp_TLAC_PREMENNE}
                  ));
        form^.ins:= false;
        form^.RunLocalFunc(_Ev,FORM_INFO);
        Dispose(form,Done)
      end;

{$ENDIF}
