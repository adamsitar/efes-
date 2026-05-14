(*-------------------------------------------------------------------*)
(* LETVIS FDP - OPL 1.0                                              *)
(* (c) Ales Kosice 1993,94 (mm,ig,ab)                                *)
(* Prepocty suradnic                                                 *)
(*-------------------------------------------------------------------*)
{$I comp.h}

{
  PREROBIT NA NACITANIE z LDM.INI !
}

unit LDM;


interface

     uses   TypeDef,
            ZemSur;


     {$I LDM.h}

     const  LDM_PREFIX : char = ' '; { oznaceniu bodov moze predchadzat prefix }

     function  is_LDM_(kod: string; var LDM_: string): bool;
     function  is_LDM (kod: string): bool;

     procedure LDMtoZemSur (kod: string; var zd,zs: TZdZs);
     procedure LDMtoReal   (kod: string; var x,y: real);



implementation

uses  str0, math, sets;

{ --------------------------------------------- }
{ LDM                                           }
{ --------------------------------------------- }


function is_LDM_(kod: string; var LDM_: string): bool;
   var   r,i: int;
   begin
     LDM_:= '';
     is_LDM_:= false;
     kod:= uni_str(kod);
     if length(kod)<4 then Exit;

     if (LDM_PREFIX<>' ') and (kod[1]=LDM_PREFIX) and (kod[2] in setL) then
        begin
          kod:= copy(kod,2,length(kod)-1);
        end;
     LDM_:= kod;
     if not (kod[1] in setL) then Exit;
     delete(kod,1,1);
     if    (length(kod)<>3)
        or (not (kod[1] in setD))
        or (not (kod[2] in setD))
        or (not (kod[3] in setM))
           then Exit;
     val(kod,i,r);
     is_LDM_:= r=0
   end;

function is_LDM(kod: string): bool;
   var   LDM_ : string;
   begin
     is_LDM:= is_LDM_ (kod,LDM_)
   end;

procedure SetLDM(_pis : char; _cis : long);
   begin
     {
     LDMstr := '';
     LDMstr := _pis + IntToStr(_cis,6,0);
     LDMToGrad(LDMstr,stx,mx,sx,sty,my,sy);
     Xrealne:=ZemSurToSec(stx,mx,sx)*20.3819;
     Yrealne:=ZemSurToSec(sty,my,sy)*30.69444;
     tu by sa malo ulozit po prepocitani Xreal, yreal do mapy }
   end; { SetLDM }


{
  prepocet z minut a sekund na desatinnu cast

function ZemSurToSec(st,m,s: real): real;
   begin
      ZemSurToSec:= st+m/60+s/3600;
   end;  ZemSurToSec }

{
  prepocet z realneho cisla na stupne, minuty a sekundy
}
procedure RealtoZemSur(ZemSur: real; var st,m,s: int);
    begin
      st:= Trunc(ZemSur);
      m := Trunc(Frac(ZemSur)*60);
      s := Trunc(Frac(Frac(ZemSur)*60)*60+0.5);
    end; { RealtoZemSur }

{
  z LDM suradnic vypocita stred stvorca a da jeho zemepisne suradnice
}
procedure LDMtoZemSur(kod: string; var zd,zs: TZdZs);
    var   i,j: byte;
          d,s: byte;
          real_d,real_s: real;
          len,k  : byte;
          step_d : real;
          step_s : real;
          _LDM   : str10;
          stx,mx,sx, sty,my,sy: int;
    begin
      step_d:= krok_d; step_s:= krok_s; _LDM:='';
      kod:= UpString(kod);
      if (LDM_PREFIX<>' ') and (kod[1]=LDM_PREFIX) and (kod[2] in setL) then kod:= copy(kod,2,length(kod)-1);

      while kod[1] in ['A'..'Z'] do
        begin
           _LDM:=_LDM + kod[1];
           delete(kod,1,1);
        end;
      for j:= 0 to LDMr-1 do
        for i:= 0 to LDMs-1 do
          if LDMcod[i,j]=_LDM then begin s:= j; d:= i end;
      real_d:= ld_d + d * step_d;
      real_s:= ld_s + s * step_s;
      len:= Length(kod);
      for k:=1 to len do
      case k of
         1..2:begin
                 step_d:= step_d / 3; step_s:=step_s / 3;
                 for j:=0 to 2 do
                   for i:=0 to 2 do
                     if devat[i,j]=kod[k] then
                        begin
                          real_d:=real_d + i * step_d;
                          real_s:=real_s + j * step_s;
                        end;
              end;
         3..6:begin
                 step_d:= step_d / 2; step_s:=step_s / 2;
                 for j:=0 to 1 do
                    for i:=0 to 1 do
                      if styri[i,j]=kod[k] then
                         begin
                           real_d:= real_d + i * step_d;
                           real_s:= real_s + j * step_s;
                         end;
              end;
      end;
      { stred stvorca }
      real_d:= real_d + step_d / 2;
      real_s:= real_s + step_s / 2;
      RealtoZemSur(real_d, stx,mx,sx);
      RealtoZemSur(real_s, sty,my,sy);

      zd.st:= stx; zd.mn:= mx; zd.se:= sx;
      zs.st:= sty; zs.mn:= my; zs.se:= sy
    end; { LDMtoZemSur }


procedure LDMtoReal(kod: string; var x,y: real);
    var   zd,zs : TZdZs;
    begin
      LDMtoZemSur(kod, zd,zs);      {stx,mx,sx, sty,my,sy);}
      y:= sirka(zs.st,zs.mn,zs.se);
      x:= dlzka(zd.st,zd.mn,zd.se)  {stx,mx,sx}
    end;


(*
{
  zo zemepisnych suradnic da LDM suradnice
}
function ZemSurtoLDM(stx,mx,sx,sty,my,sy: byte): str8;
var
     i,j: byte;
     d,s: byte;
     _LDM: str8;
     zv_d,zv_s: real;
     step_d : real;
     step_s : real;

begin
     if ((stx=16) and (mx<30)) or (stx<16) then Exit;
     if ((stx=22) and (mx>30)) or (stx>22) then Exit;
     if ((sty=46) and (my>58)) or (sty<47) then Exit;
     if ((sty=49) and (my>58)) or (sty>=50) then Exit;

     step_d := 1.5;
     step_s := 1;
     _LDM := '';
     for i:=1 to 7 do
     case i of
     1:begin { pismeno }
             { zemepisna dlzka }
            d:=_div(ZemSurToSec(stx,mx,sx) - ld_d,step_d);
            zv_d:=_mod(ZemSurToSec(stx,mx,sx) - ld_d,step_d);
             { zemepisna sirka }
            s:=_div(ZemSurToSec(sty,my,sy) - ld_s,step_s);
            zv_s:=_mod(ZemSurToSec(sty,my,sy) - ld_s,1);
            _LDM:=LDMcod[d,s];
       end;
     2..3:begin { deleno 3 }
                { zemepisna dlzka }
            step_d:=step_d/3;
            d:=_div(zv_d,step_d);
            zv_d:=_mod(zv_d,step_d);
                { zemepisna sirka }
            step_s:=step_s/3;
            s:=_div(zv_s,step_s);
            zv_s:=_mod(zv_s,step_s);
            _LDM:=_LDM+devat[d,s];
       end;
     4..7:begin { deleno 2 }
                { zemepisna dlzka }
            step_d:=step_d/2;
            d:=_div(zv_d,step_d);
            zv_d:=_mod(zv_d,step_d);
                { zemepisna sirka }
            step_s:=step_s/2;
            s:=_div(zv_s,step_s);
            zv_s:=_mod(zv_s,step_s);
            _LDM:=_LDM+styri[d,s];
       end;
     end;
     ZemSurtoLDM:=_LDM;
end; { ZemSurtoLDM }


function RealtoLDM(_Xre,_Yre: real): str8;
{ z realnych cisel da LDM suradnice }
var
     i,j: byte;
     d,s: byte;
     _LDM: str8;
     zv_d,zv_s: real;
     step_d : real;
     step_s : real;

begin
     step_d := 1.5;
     step_s := 1;
     _LDM:='';
     for i:=1 to 7 do
         case i of
            1:begin { pismeno }
                    { zemepisna dlzka }
                   d:=_div(_Xre - ld_d,step_d);
                   zv_d:=_mod(_Xre - ld_d,step_d);
                    { zemepisna sirka }
                   s:=_div(_Yre - ld_s,step_s);
                   zv_s:=_mod(_Yre - ld_s,1);
                   _LDM:=LDMcod[d,s];
              end;
            2..3:begin { deleno 3 }
                       { zemepisna dlzka }
                   step_d:=step_d/3;
                   d:=_div(zv_d,step_d);
                   zv_d:=_mod(zv_d,step_d);
                       { zemepisna sirka }
                   step_s:=step_s/3;
                   s:=_div(zv_s,step_s);
                   zv_s:=_mod(zv_s,step_s);
                   _LDM:=_LDM+devat[d,s];
              end;
            4..7:begin { deleno 2 }
                       { zemepisna dlzka }
                   step_d:=step_d/2;
                   d:=_div(zv_d,step_d);
                   zv_d:=_mod(zv_d,step_d);
                       { zemepisna sirka }
                   step_s:=step_s/2;
                   s:=_div(zv_s,step_s);
                   zv_s:=_mod(zv_s,step_s);
                   _LDM:=_LDM+styri[d,s];
              end;
         end;
     RealtoLDM:=_LDM;
end; { RealtoLDM }


}
  z LDM suradnic vypocita stred stvorca a da jeho realne cisla Xreal, Yreal
}
procedure LDMtoReal(kod: str8; var _Xre,_Yre: real);
   var    i,j, d,s, len,k : byte;
          real_d,real_s   : real;
          step_d, step_s  : real;
          _LDM: str2;

    begin
      step_d:= 1.5; step_s:= 1; _LDM:= '';
      for i:= 1 to 2 do kod[i]:= UpCase(kod[i]);
      while kod[1] in ['A'..'Z'] do
         begin
           _LDM:=_LDM + kod[1];
           delete(kod,1,1);
         end;
      for j:= 0 to 2 do
         for i:= 0 to 4 do
            if LDMcod[i,j]=_LDM then
               begin
                 s:= j;
                 d:= i;
               end;
      real_d:=ld_d + d * step_d;
      real_s:=ld_s + s * step_s;
      len:=Length(kod);
      for k:=1 to len do
      case k of
      1..2:begin
              step_d:=step_d / 3;
              step_s:=step_s / 3;
              for j:=0 to 2 do
              for i:=0 to 2 do
              if devat[i,j]=kod[k] then
              begin
                 real_d:=real_d + i * step_d;
                 real_s:=real_s + j * step_s;
              end;
           end;
      3..6:begin
              step_d:=step_d / 2;
              step_s:=step_s / 2;
              for j:=0 to 1 do
              for i:=0 to 1 do
              if styri[i,j]=kod[k] then
              begin
                 real_d:=real_d + i * step_d;
                 real_s:=real_s + j * step_s;
              end;
           end;
      end;
      { stred stvorca }
      real_d:=real_d + step_d / 2;
      real_s:=real_s + step_s / 2;
      _Xre := real_d;
      _Yre := real_s;
    end; { LDMtoReal }
*)

end. { LDM }