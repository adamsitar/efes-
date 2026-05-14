(*-------------------------------------------------------------------*)
(* LETVIS LIS - Praca so Zemepisnymi suradnicami                     *)
(* (c) Ales Kosice 1993  Igor, mm, ab                                *)
(*-------------------------------------------------------------------*)
{$I comp.h}
{$X+,I-,S-,P-}

unit ZemSur;


interface


    uses   TypeDef;


    const  cnstSIRKA = 30.6944;  { ak je zadana desatinami }
           cnstDLZKA = 20.3819;
           _gr_ = '-';


    function  sirka(st,min,sec: real): real;
    function  dlzka(st,min,sec: real): real;
    function  sirka_(st: real): real;
    function  dlzka_(st: real): real;

    procedure xy_zdzs(x,y: real; var _zd,_zs: Tzdzs);
    procedure zdzs_xy(_zd,_zs: Tzdzs; var x,y: real);

    {function  ZemSurToSec (st,min,sec: real): real;}
    function  ZemSurToReal(kod: string; var x,y: real): bool;

    {procedure desatiny_na_stupne(des: real; var z: TZdZs);
    procedure stupne_na_desatiny(z: TZdZs; var des: real);}

    function  is_ZemSur(kod: string): bool;


implementation

uses  BIOS,
      str0, sets,
      {_MTK_2,} _L4_def;


function CheckZemSur(st,min,sec: int): bool;
   begin
     CheckZemSur:= ((st>=0) and (st<360)) and (min in[0..59]) and (sec in[0..59])
   end; { CheckZemSur }


function sirka(st,min,sec: real): real;
   begin
     sirka:= (st*3600 + min*60 + sec)*cnstSIRKA
   end;

function dlzka(st,min,sec: real): real;
   begin
     dlzka:= (st*3600 + min*60 + sec)*cnstDLZKA
   end;

function sirka_(st: real): real;
   begin
     sirka_:= (st*3600)*cnstSIRKA
   end;

function dlzka_(st: real): real;
   begin
     dlzka_:= (st*3600)*cnstDLZKA
   end;


procedure xy_st(r: real; var st: TZdZs);
   begin
     st.st:= trunc(r/3600);
     st.mn:= trunc((((r/3600)-st.st )*3600)/60);
     st.se:= trunc(0.5+(((((r/3600)-st.st )*3600)/60)-st.mn)*60);
     if st.se=60 then
        begin
          st.se:= 0; inc(st.mn);
          if st.mn=60 then begin st.mn:= 0; inc(st.st); end
        end
   end;

procedure xy_zdzs(X,Y: real; var _Zd,_Zs: TZdZs);
    var   lw : real;
    begin
      lw := X/cnstDLZKA;
      _Zd.st:= trunc(lw/3600);
      _Zd.mn:= trunc((((lw/3600)-_Zd.st )*3600)/60);
      _Zd.se:= trunc(0.5+(((((lw/3600)-_Zd.st )*3600)/60)-_Zd.mn)*60);

      lw := Y/cnstSIRKA;
      _Zs.st:= trunc(lw/3600);
      _Zs.mn:= trunc((((lw/3600)-_Zs.st )*3600)/60);
      _Zs.se:= trunc(0.5+(((((lw/3600)-_Zs.st )*3600)/60)-_Zs.mn)*60)
    end;

procedure zdzs_xy(_zd,_zs: Tzdzs; var X,Y: real);
    begin
      X:= dlzka(_Zd.st,_Zd.mn,_Zd.se);
      Y:= sirka(_Zs.st,_Zs.mn,_Zs.se)
    end;

{
procedure desatiny_na_stupne(des: real; var z: TZdZs);
    var   s,m,d: real;
    begin
      s:= trunc(des);
      m:= trunc((des-s)*60);
      d:= (des-s-m/60)*3600;
      z.st:= trunc(s);
      z.mn:= trunc(m);
      z.se:= trunc(d)
    end;

procedure stupne_na_desatiny(z: TZdZs; var des: real);
    var   s,m,d: real;
    begin
      s:= z.st; m:= z.mn; d:= z.se;
      des:= s + m/60 + d/60/60
    end;
}


function ZemSurToStr(st,min,sec: byte; ch: char): string;
   begin
     if ch<>' ' then ZemSurToStr:= IntToStr(st,2,0)+'ø'+IntToStr(min,2,0)+#39+IntToStr(sec,2,0)+#39+#39
     else ZemSurToStr:= IntToStr(st,2,0)+IntToStr(min,2,0)+IntToStr(sec,2,0)
   end;

{function ZemSurToSec(st,min,sec: real): real;
   begin
     ZemSurToSec:= sec + min*60 + st*3600
   end;}


function ZemSurToReal(kod: string; var x,y: real): bool;
   var   s1,s2 : string;
         c1,c2 : int;
         zs,zd : TZdZs;
   begin
     ZemSurToReal:= false;

     if decode_l4_ZemSur(kod, zd.st,zd.mn,zd.se, zs.st,zs.mn,zs.se) then
        begin
          x:= dlzka(zd.st,zd.mn,zd.se);
          y:= sirka(zs.st,zs.mn,zs.se);
          ZemSurToReal:= true
        end
     else begin
            kod:= cut_(kod);
            c1:= pos(_gr_,kod);
            if c1=0 then c1:= length(kod) div 2;
            s1:= delchar(copy(kod,1,c1),setPism_+[_gr_]);
            s2:= delchar(copy(kod,c1+1,length(kod)-c1),setPism_);

            c1:= 0;
            if pos('.',s1)<>0 then
               begin
                 val(s1, y,c1);
                 if c1<>0 then Exit;
                 y:= sirka_(y)
               end
            else begin
                   if length(s1)>6 then s1:= copy(s1,length(s1)-6+1,6);
                   s1:= delchar(s1,setPism_);
                   if not (length(s1) in [4,6]) then Exit;
                   zs.st:= scis(s1,1,2); zs.mn:= scis(s1,3,2); zs.se:= scis(s1,5,2);
                   y:= sirka(zs.st,zs.mn,zs.se)
                 end;

            c2:= 0;
            if pos('.',s2)<>0 then
               begin
                 val(s2, x,c2);
                 if c2<>0 then Exit;
                 x:= dlzka_(x)
               end
            else begin
                   if length(s2)>6 then s2:= copy(s2,length(s2)-6+1,6);
                   s2:= delchar(s2,setPism_);
                   if not (length(s2) in [4,6]) then Exit;
                   zd.st:= scis(s2,1,2); zd.mn:= scis(s2,3,2); zd.se:= scis(s2,5,2);
                   x:= dlzka(zd.st,zd.mn,zd.se)
                 end;

            ZemSurToReal:= (    ((pos('.',kod)<>0) and (c1=0) and (c2=0))
                             or ((pos('.',kod)=0) and CheckZemSur(zs.st,zs.mn,zs.se) and CheckZemSur(zd.st,zd.mn,zd.se))
                           )
          end
   end;


function is_ZemSur(kod: string): bool;
   var   x,y  : real;
   begin
     is_ZemSur:= ZemSurToReal(kod, x,y)
   end;


end.
