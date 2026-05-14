{
‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹
€                           €
€ formular_OPRAVA_OB        €
€‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹€
}
const  Form_OB: array [0..0] of TForm =
                (( item : '                       ';
                   title: ''; lst: @fn_15M; pos: 10;
                   legal: @set_15; skip : @setNil;
                   dx:0 ; dy:0; font:0; color: 0
                ));


function _check_OB(p: pointer; T: pointer; vojensky_plan: bool): bool; far;
   var   NTRAT : string;
         _OBs  : POBxys;
         res,r : string;
   begin
     with T_TRAT4(T^) do
       begin
         r:= cut_(strpas(Form_OB[0].item));
         if (r<>'') and (not (r[1] in [',','/'])) then r:= ','+r;
         SPEC  := r;
         NTRAT := TRAT_PRED + OB + SPEC + TRAT_PO + #0;
         New(_OBs); fillchar(_OBs^,sizeof(_OBs^),0);
         with FPL^ do
           res:= _decode_FPL0_15
                    (
                     @NTRAT[1],
                     start,prist,
                     _OBs^,bodov,
                     rych,rych_, vys,vys_,
                     date,
                     vojensky_plan,false,true,true,false
                    );
         Dispose(_OBs);
         if res<>'' then begin res:= res+#0; TSingleForm(p^).Error(0,@res[1]) end;
       { cas startu by mal byt mensi ako cas na bode }
       end;
     _check_OB:= r=''
   end;

function check_OB_mil(p: pointer; T: pointer): bool; far;
   begin
     check_OB_mil:= _check_OB(p,T,true)
   end;

function check_OB(p: pointer; T: pointer): bool; far;
   begin
     check_OB:= _check_OB(p,T,false)
   end;

function formular_OB(var Trat: T_TRAT4;
                     vojensky_plan : bool;
                     x,y: int; _tit: string;
                     _info, _hlpXXX: Pchar
                    ): bool;
   var   F  : PSingleForm;
         s  : string;
         d  : int;
         p  : pointer;
         Ev : TEvent;
   begin
     d:= ord(GraphMode);
     StrPCopy(Form_OB[0].item, inschar(Trat.SPEC, strlen(Form_OB[0].item),' ',1));
     if vojensky_plan then p:= @check_OB_mil else p:= @check_OB;
     F:= New(PSingleForm,Init(nil, x,y,d,
             kbEnter,cmOK,_tit, @Form_OB,
             clGR2,cfText, 1,
             @Trat, nil,@check_OB,nil, _hlpXXX, true)
            );
     F^.RunLocalFunc(Ev,_info);
     formular_OB:= F^.corr_res;
     Dispose(F,Done)
   end;


