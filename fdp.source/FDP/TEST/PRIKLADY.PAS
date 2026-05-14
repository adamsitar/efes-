{ Pr. TsArea;
  -------------
}
var a   : TsArray;
    s,t : string;
    t1,t2: word;

    var i,j,k: int;
        Ai: TpArea;

begin

 for i:= 0 to AREA^.pocet-1 do
   begin
     AREA^.read(i,Ai);
     writeln(Ai.kod+', '+cstr(Ai.vys1,4)+', '+cstr(Ai.vys2,4)+', '+Ai.bodi+', '+Ai.bodc+'.')
   end;

 i:= _AREAind_ ('r49', Area, Ai);
 i:= _AREAind_ ('r249', Area, Ai);


{ Pr. TsArray;
  -------------
}
 t1:= getticks;

 a.Init(100,10,false);
 if a.ear.is_ems then writeln('ems');

 for i:= 1 to 1  do {for j:= 0 to 2  do}
   begin
     s:= '0';
     a.add(s);
     s:= '1';
     a.add(s);
     s:= '2';
     a.add(s);

     a.read(2,t);
     writeln(t);

     writeln('--------');
     writeln(a.pocet);
     writeln('--------');

     a.del(2);

     writeln('--------');
     writeln(a.pocet);
     writeln('--------');

     for k:= 0 to a.pocet-1 do
       begin
         a.read(k,t);
         writeln(t);
       end;

     s:= 'a';
     a.write(0,s);

     s:= 'b';
     a.write(1,s);

     s:= 'c';
     a.write(2,s);

     s:= 'x';
     a.add(s);

     for k:= 0 to a.pocet-1 do
       begin
         a.read(k,t);
         writeln(t);
       end;
   end;

 a.Done;

 writeln(maxavail);
 writeln(memavail);
 t2:= getticks;
 writeln(t2-t1);
 if a.ear.is_ems then writeln('ems');


{ Pr. Regularita
  ---------------
}
  var in1r, in2r, is1r, is2r: bool;
      x1r,y1r,x2r,y2r : real;


  priesecnik_usecky_s_kruznicou (-2,0, 2,0, 0,0,1, in1r, in2r, isp, x1r,y1r,x2r,y2r);
  priesecnik_usecky_s_kruznicou (-1,0, 1,0, 0,0,1, in1r, in2r, isp, x1r,y1r,x2r,y2r);
  priesecnik_usecky_s_kruznicou (-1,0, 1,0, 0,0,2, in1r, in2r, isp, x1r,y1r,x2r,y2r);

  priesecnik_usecky_s_kruznicou (-1,0, 1,1, 2,1,1, in1r, in2r, isp, x1r,y1r,x2r,y2r);
  priesecnik_usecky_s_kruznicou (-1,0, 1,1, 2,2,1, in1r, in2r, isp, x1r,y1r,x2r,y2r);
  priesecnik_usecky_s_kruznicou (-1,1, 1,1, 1,1,1, in1r, in2r, isp, x1r,y1r,x2r,y2r);
  priesecnik_usecky_s_kruznicou (-1,1, 1,1, 0,0,3, in1r, in2r, isp, x1r,y1r,x2r,y2r);

