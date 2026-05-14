{$I comp.h}

uses typedef, bios, dos, str0;

var    s : string;
const  c : string = '(CSA/102-IDE-- TAM)';


begin

 s:= get_str (@c[1],length(c),3, ['(','-',')'],200);
 s:= get_str (@c[1],length(c),4, ['(','-',')'],200);


end.