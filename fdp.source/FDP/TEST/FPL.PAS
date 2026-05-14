{$I comp.h}

uses typedef, db, str0, _fplm;

var  fplm,fplmi: DmFPL;

begin
  fillchar(fplm,sizeof(fplm),0);
  fillchar(fplmi,sizeof(fplmi),0);
  fplm.idn:= 'F4239';
  fplm.start.kod:= 'LKKB';
  fplm.date.r:= 1998;
  fplm.date.m:= 6;
  fplm.date.d:= 6;
  read_mFPL(codekey_mFPL(@fplm),@fplmi);
  disp_FPLm(@fplm);
  disp_FPLm(@fplmi);
end.