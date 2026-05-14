{$I comp.h}

uses typedef, bios, dos, str0,
     bgigraph,svga,
     help;


var i : int;
    f : text;
    bres : bool;
    _Year : real;

const hlp_U = 'UPGRADE - OPL';

{begin
 InitBGI;
 _help (hlp_U);}


var
 A: array[0..79] of Char;
 S: string[79];
begin
 Readln(S);
 StrPCopy(A, S);
 Writeln(A);

 {HelpViewer('\xe\d\STA\08-02-99.÷TD', @get_sta_archiv,nil);}
 {formular_PRZ(nil,true,false,'.','xxxxxxxxxxxxxxx');}
 {formular_SPR(nil);}
end.