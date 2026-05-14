{$I comp.h}

uses bios, typedef, math, str0, crt, msg,
     {$I unit_gr.h},
     _ssr;

begin
end.
     dialog, FIR_DEF, Lists, help_def, help,
     _l4_def, _l4_func,


var  i: int;
     s,t,res: string;
     _9, _9a,_9b,_9c: string;

     rych: single; var rych_: char;
     minkmh,maxkmh: single;
     vys: word; var vys_: char;
     minS,maxS: word;
     ini: bool;

var _13a: string; var h,m,h_,m_: byte;

function _do_it (data: pointer; item: pint; items: int; d: PProcess): bool;
   begin
     delay(1000);
     inc(item^);
     _do_it:= item^ >= items
   end;

var  L: PList;

  InitBGI;
  set_GrMode(_SVGA);
  _help();

  {_info_TYP('C130',0,0);}
  {_infop('.\LIST\'+_fn_9b+lstExt,'tit_typy_icao', 0,0,true,false,nil);}

  _info_TYP('',0,0);
  s:= _get_item(10,10, @fn_15a,[],1,false,nil);

  L:= New(PList,Init(@fn_15a,'',[],1,false,nil,true));

  writeln(' ');
  {$IFDEF NOEMS}
   writeln('NOEMS');
  {$ELSE}
  if ((l^.stre=nil) or (not l^.stre^.is_ems)) then writeln('NOEMS !');
  {$ENDIF}
  writeln(' ');
  writeln('lo  ',l^.lo);
  writeln('hi  ',l^.hi);
  writeln('top ',Minimum(l^.top,200));
  writeln('poz ',Minimum(l^.poz,l^.hi));


  {s:= L^.get_item(100,100);}

  for i:= 0 to l^.top do writeln(l^.get(i));

  Dispose(L,Done)
 s:= 'DATE/990707 EET/SADKO/1700S0630S0630  FLS0630 EXI/PIMEN/1736S0630S0630  FDP/FPL SRC/8'#0;
 t:= _item_18_1(@s[1],rmk_EET);
 l4_err('RPL','',1,0,res);
 l4_err('15c','B -> X ',31,38, res);

(*
begin
  InitBGI;

  _9:= '_data';
  i:= 1;
  ini:= InfoProcess ('tit_PLN_ITEM+',titDLA,
                   '','cut_(get_str(data,size, riadok,setNL,sizeof(string)-1))',
                   @_do_it, @_9[0],
                   10,@i
                  );


end.

(*
begin
 s:= 'AN24/M';
 _9b_rychvys (s,true, rych,rych_,minkmh,maxkmh, vys,vys_,minS,maxS);
end.


  s:= 'xx';
  l4_err (a_RTE,'',0,30,res);
  InitBGI;
  s:= _get_item(100,100,@fn_9bICAO,[], 1, false,nil);
  formular_cFPL_(nil,'');
  _check_13_by4444 ('',s,h,m,h_,m_,res);
 _9:= 'T154';
  s:= _code_9_by8643(_9);
 for i:= 100 to 255 do writeln(i,chr(i));

  xy_in_range(1000,1000);

vyber si testovacie ->priklady<-

  _9:= '19';
  s:= _code_9MIL_by8643(_9);

  s:= _code_9TSGA_by8643(_9);
  _9:= '€74';
  s:= _code_9_by8643(_9);

  _9:= '€74/M';
  _check_9_by8643 (_9,res);

  _9:= '02O410';
  s:= _code_9_by8643(_9);
  _9:= 'A1';
  s:= _code_9_by8643(_9);
  _9:= '0219';
  s:= _code_9_by8643(_9);

  (*ini:= lst_9bICAO^.is_initialized;

  _9:= 'A300';
   lst_9bICAO^.find(_9,s,i);
  lst_9bICAO^._speed (s, rych,rych_, minkmh,maxkmh);
  lst_9bICAO^._fl    (s, vys,vys_,   minS,maxS);

  _9:= 'AN24';
  lst_9bICAO^.find(_9,s,i);
  lst_9bICAO^._speed (s, rych,rych_, minkmh,maxkmh);
  lst_9bICAO^._fl    (s, vys,vys_,   minS,maxS);

  lst_9bICAO^.was_initialized(ini);*)
