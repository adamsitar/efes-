{$I comp.h}

{comp.h pre "rte_sec"}

{$DEFINE DEBUG}
{$DEFINE POKUS}

{$DEFINE UK}
{$DEFINE UKBB}
{$DEFINE ENGLISH}

{$DEFINE BGI}

{$I comp_exe.h}

{$DEFINE DB_DBASE}

{$DEFINE RLP}

{$DEFINE FDP}        {$DEFINE RLP}
{$DEFINE ATCA}       {$DEFINE RLP}
{$DEFINE ACC}

{$DEFINE UKBB}
{$DEFINE KIEV}

{$DEFINE RUSSIAN}
{$DEFINE A36YKA}

{$DEFINE FPL4}

{$I comp_net.h}
{$I comp_ext.h}
{$I comp_fdp.h}



uses  ovr, bios, typedef, math, str0, io,
      mess,
      _l4_def,
      fir_def,bod_def,body,zemsur,
      sector, grprim, mapydef, mapy;

var   s1,s2, res: string;
      i : int;
      R : TRTE;
      M : PMapy;
      x0,y0,x1,y1 : real;
      err : bool;
      B1,B2: TsBod;
      zd,zs: Tzdzs;
      in1,in2,is1,is2: bool;

begin
  writeln;

  write('AWY code    : '); readln(s1); s1:=cut_(upstring(s1));
  if not is_RTE (s1,R) then RunError('Unknown route.');

  repeat

    PathToSEC:= uni_str(read_cfg_str_(SECcfg, cfg_SECTORs, PathToSEC));
    if PathToSEC[length(PathToSEC)]<>'\' then PathToSEC:= PathToSEC+'\';
    write('SECTOR name : '); readln(s2); s2:=cut_(upstring(s2));

    M:= New(PMapy,Init);
    if M^.najdi_a_nacitaj_subor(PathToSEC+s2+ext_map)<>nil then
       begin
         for i:= 0 to R.top-1 do
           begin
             if not (is_OB(R.rte^[i].kod,B1,true) and is_OB(R.rte^[i+1].kod,B2,true)) then continue;
             if M^.priesecnik_xy(B1.x,B1.y,B2.x,B2.y, in1,in2,is1,is2, x0,y0,x1,y1) then
                begin
                  res:= '';
                  if is1 then
                     begin
                       xy_zdzs(x0,y0, zd,zs);
                       res:=  inttostr(zs.st,2,0)+inttostr(zs.mn,2,0)+inttostr(zs.se,2,0)
                              + ' ' + inttostr(zd.st,2,0)+inttostr(zd.mn,2,0)+inttostr(zd.se,2,0);
                       if (B1.x=x0) and (B1.y=y0) then res:= res+' ('+B1.kod+')'
                     end;
                  if is2 then
                     begin
                       if res<>'' then res:= res+', ';
                       xy_zdzs(x1,y1, zd,zs);
                       res:=  res + inttostr(zs.st,2,0)+inttostr(zs.mn,2,0)+inttostr(zs.se,2,0)
                              + ' ' + inttostr(zd.st,2,0)+inttostr(zd.mn,2,0)+inttostr(zd.se,2,0);
                       if (B2.x=x0) and (B2.y=y0) then res:= res+' ('+B2.kod+')'
                     end;
                  if res<>'' then writeln(B1.kod+'-'+B2.kod+' :  '+res);
                end;
           end
         end
    else writeln('Unknown sector.');
    Dispose(M,Done);
    writeln;

  until s2='';

  writeln('LETVIS FDP utility to find coordinates of sector crossing points.');
  writeln('Copyright by ALES (c) 1989-1999.');
end.
