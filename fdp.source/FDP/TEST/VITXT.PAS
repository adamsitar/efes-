{$I comp.h}

uses typedef,
     bgigraph,svga,
     help;

begin
  InitBGI;
  set_GrMode(_VESA);
  _info__ (paramstr(1),'Kuko', 0,0, nil,nil,nil, NULL,NULL,NULL, nil)
end.