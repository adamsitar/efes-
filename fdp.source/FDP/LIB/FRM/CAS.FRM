{
‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹
€                                                          €
€ formular_CAS                                             €
€‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹€
}
const  Form_CAS: array [0..0] of TForm =
            (( item : '  :  '; title: '';
               lst  : nil; pos: 0;
               legal: @setCisl; skip : @setCas;
               dx:0 ; dy:0; font:0; color: 0
            ));

function formular_CAS_(var _plan_time: TTime;
                       formular: string; legal: PCharSet; check_CAS: pointer;
                       x,y: int; _tit: string; _info: pchar
                      ): bool;
   var   F  : PSingleForm;
         s  : string;
         d  : int;
         Ev : TEvent;
   begin
     fillchar(_plan_time,sizeof(TTime),0); d:= ord(GraphMode);
     StrPICopy(Form_CAS[0].item, formular,strlen(Form_CAS[0].item));
     Form_CAS[0].legal:= legal;
     F:= New(PSingleForm,Init(nil, x,y,d, kbEnter,cmOK,
             _tit, @Form_CAS,
             clGR2,cfText, 1,
             @_plan_time.h,nil,check_CAS,nil, nil, false)
            );
     F^.RunLocalFunc(Ev,_info);
     formular_CAS_:= F^.corr_res;
     Dispose(F,Done)
   end;


function check_CAS(p: pointer; pt: PTime): bool; far;
   begin
     check_CAS:= GetTimeStr(pt^.h,pt^.m,pt^.s,StrPas(Form_CAS[0].item))
   end;

function formular_CAS(var _plan_time: TTime;
                      _hour,_min    : byte;
                      x,y: int; _tit: string; _info: pchar
                     ): bool;
   begin
     formular_CAS:= formular_CAS_(_plan_time,
                                  TimeToStr(_hour,_min,':'), @setCisl,
                                  @check_CAS,
                                  x,y, _tit, _info
                                 );
   end;
