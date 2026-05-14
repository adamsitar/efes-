{
‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹
€                                                          €
€ TcFPLform - civilny FPL                                  €
€‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹€
}
function  formular_cFPL(FPLi  : PDcFPL;
                        _src  : fdp_src;
                        _novy : bool;
                        _tit  : string;
                        _pos  : int;
                        _ssr,_viewer,_copy_data : bool
                       ): bool;
   const  f    : Tcentr = (x: initX; y: initY; m: 1);
   var    form : PcFPLform;
          E    : TEvent;
   begin
     formular_cFPL:= false;

     if not _viewer then
        begin
         {$IFNDEF DEBUG} {$IFNDEF ATCA}
          if not ENABLE_FPLC then Exit;
         {$ENDIF} {$ENDIF}
         {$IFDEF DISABLED_ETO_FPLc}
          Exit;
         {$ENDIF}
        end;

     if _tit='' then
         if (FPLi<>nil) and (not _viewer) then _tit:= msg_FPLc_CHG
         else _tit:= msg_FPLc_EST;

     form:= New(PcFPLform,Init(f.x,f.y, f.m,_tit,
                FPLi,
                _src,
                _novy,
                _tit,
                _pos,
                _ssr,
                _viewer,_copy_data
                )
               );
     form^.upcas:= true;
     form^.RunLocalFunc(E,FDPFormLocalMenu);
     formular_cFPL:= form^.corr_res;
     Dispose(form,Done)
   end;


function  formular_cFPL_(p: pointer; tit: string): bool;
   begin
     formular_cFPL_:= formular_cFPL(p,letvis,false,tit,pos_frm_FPLC,false,false,false);
     pos_frm_FPLC:= -1;
   end;

function info_cFPL (p: pointer; tit: string): bool; far;
   begin
     info_cFPL:= formular_cFPL (p,letvis,false,tit,pos_frm_FPLC,false,true,false)
   end;