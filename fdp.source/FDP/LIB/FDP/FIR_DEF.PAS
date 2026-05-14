{$I comp.h}


unit FIR_def;


interface


    uses   TypeDef;


    const  kod_FIR = 2;

           FIR =    {$IFDEF LZ}   'LZ' {$ENDIF}
                    {$IFDEF LK}   'LK' {$ENDIF}
                    {$IFDEF UK}   'UK' {$ENDIF}
                    ;

           kod_ACC = 2;

           ACC =    {$IFDEF LZ}   'IB' {$ENDIF}
                    {$IFDEF LK}   'PR' {$ENDIF}
                    {$IFDEF UKBB} 'BB' {$ENDIF}
                    ;


           firDir  = FIR+'\';
           firExt  = '.'+ACC;

           FIR_adr  = FIR+ACC;
           FIR_adr2 : string [kod_FIR+kod_ACC] = FIR_adr;


    const  cfg_FIR_ADR = 'FIR';

    const  language =  {$IFDEF SLOVAK}  'sk'  {$ENDIF}
                       {$IFDEF CZECH}   'cz'  {$ENDIF}
                       {$IFDEF RUSSIAN} 'rus' {$ELSE}
                       {$IFDEF ENGLISH} 'en'  {$ENDIF}
                       {$ENDIF}
                      ;


    const  {$IFDEF DEBUG} pathLST_ = '\FDPÿDATA\LIST\';
                          pathLST  = pathLST_+firDir;
           {$ELSE}        pathLST  = '.\LIST\';
           {$ENDIF}

           lstExt   = '.lst';


    const  zsN  =  'N';
           zsS  =  'S';
           zdE  =  'E';
           zdW  =  'W';

           firZS =  {$IFDEF LZ} zsN {$ENDIF}
                    {$IFDEF LK} zsN {$ENDIF}
                    {$IFDEF UK} zsN {$ENDIF}
                    ;

           firZD =  {$IFDEF LZ} zdE {$ENDIF}
                    {$IFDEF LK} zdE {$ENDIF}
                    {$IFDEF UK} zdE {$ENDIF}
                    ;


    const  hd_TSA = 'TSA';
           hd_R   = 'R';       { obmedzene priestory }
           hd_P   = 'P';       { zakazane priestory  }
           hd_D   = 'D';       { docasne priestory   }


    function  is_TSA (kod: string): bool;
    function  is_R   (kod: string): bool;
    function  is_P   (kod: string): bool;

    function  _unique_area_code(kod: string): string;
    function  _is_area_code(kod: string): bool;


implementation

uses  io, str0, sets;

{ Nastavi jednotny identifikator priestoru, ktory sa moze zadat
  roznymi sposobami : LZR13,R13,LZ_R13,LZ-R13,R-13,R 13,...
  do tvaru R13.
}
  function _unique_area_code(kod: string): string;
     begin
       kod:= upstring(delcharn(kod, setPism+setDig));
       if pos(FIR,kod)=1 then kod:= copy(kod,length(FIR)+1,length(kod)-length(FIR));
       _unique_area_code:= kod
     end;

  function _is_area_code(kod: string): bool;
     begin
       _is_area_code:= is_TSA(kod) or is_R(kod) or is_P(kod)
     end;


{ Urcenie typu priestoru
}
  function is_TSA(kod: string): bool;
     begin
       is_TSA:= pos(hd_TSA,_unique_area_code(kod)) = 1
     end;

  function is_R(kod: string): bool;
     begin
       is_R:= pos(hd_R,_unique_area_code(kod)) = 1
     end;

  function is_P(kod: string): bool;
     begin
       is_P:= pos(hd_P,_unique_area_code(kod)) = 1
     end;


begin
{ Nazov FIR-u
}
   FIR_adr2:= _read_cfg(SYSTEMcfg,cfg_FIR_ADR,true);
   if FIR_adr2='' then FIR_adr2:= FIR_adr
end.
