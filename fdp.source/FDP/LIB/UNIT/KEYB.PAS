(*-------------------------------------------------------------------*)
(* Ovladac klavesnice 1.0                                            *)
(* 1993                                                              *)
(*-------------------------------------------------------------------*)
{$I comp.h}


unit Keyb;


interface


     uses  TypeDef;


     const kbNoKey = #0;
           kbNUL   = #0;
           kbEsc   = #27;
           kbEOF   = #26;

           kbLF    = #10;     kbLF_ = #217;
           kbCR    = #13;     kbCR_ = #17;

           kbNL    = #13#10;
           kbNL_   = #17#217;
           kbCRLF  = #255;    { pseudoNL }

           kbEnter = #13;     kbAltEnter = #151;    kbCtrlEnter = #10;
           kbBell  = #7;
           kbBS    = #8;      kbAltBS    = #137;    kbCtrlBS    = #127;
           kbIns   = #205;    kbAltIns   = #162;    kbCtrlIns   = #146;
           kbDel   = #206;    kbAltDel   = #163;    kbCtrlDel   = #147;

           kbTab   = #9;      kbShiftTab = #138;

           kbUp    = #195;    kbAltUp    = #152;    kbCtrlUp    = #141;
           kbDown  = #203;    kbAltDown  = #160;    kbCtrlDown  = #145;
           kbLeft  = #198;    kbAltLeft  = #155;    kbCtrlLeft  = #238;
           kbRight = #200;    kbAltRight = #157;    kbCtrlRight = #239;

           kbHome  = #194;    kbCtrlHome = #242;
           kbEnd   = #202;    kbCtrlEnd  = #240;
           kbPgUp  = #196;    kbCtrlPgUp = #132; {255;}
           kbPgDn  = #204;    kbCtrlPgDn = #241;

           kbCtrlPrScr = #237;

           kbF1 = #182; kbF2  = #183; kbF3  = #184; kbF4  = #185;
           kbF5 = #186; kbF6  = #187; kbF7  = #188; kbF8  = #189;
           kbF9 = #190; kbF10 = #191; kbF11 = #133; kbF12 = #134;

           kbAltF1 = #227; kbAltF2  = #228; kbAltF3  = #229; kbAltF4  = #230;
           kbAltF5 = #231; kbAltF6  = #232; kbAltF7  = #233; kbAltF8  = #234;
           kbAltF9 = #235; kbAltF10 = #236; kbAltF11 = #139; kbAltF12 = #140;
           {-139,-140}

           kbCtrlF1 = #217; kbCtrlF2  = #218; kbCtrlF3  = #219; kbCtrlF4  = #220;
           kbCtrlF5 = #221; kbCtrlF6  = #222; kbCtrlF7  = #223; kbCtrlF8  = #224;
           kbCtrlF9 = #225; kbCtrlF10 = #226; kbCtrlF11 = #137; kbCtrlF12 = #138;
           {137,-138}

           kbShiftF1 = #207; kbShiftF2  = #208; kbShiftF3  = #209; kbShiftF4  = #210;
           kbShiftF5 = #211; kbShiftF6  = #212; kbShiftF7  = #213; kbShiftF8  = #214;
           kbShiftF9 = #215; kbShiftF10 = #216; kbShiftF11 = #135; kbShiftF12 = #136;

           kbAltQ = #139; kbAltW = #140; kbAltE = #141; kbAltR = #142; kbAltT = #143;
           kbAltY = #144; kbAltU = #145; kbAltI = #146; kbAltO = #147; kbAltP = #148;
           kbAltA = #153; kbAltS = #154; kbAltD = #155; kbAltF = #156; kbAltG = #157;
           kbAltH = #158; kbAltJ = #159; kbAltK = #160; kbAltL = #161; kbAltZ = #167;
           kbAltX = #168; kbAltC = #169; kbAltV = #170; kbAltB = #171; kbAltN = #172;
           kbAltM = #173;

           kbAlt1 = #243; kbAlt2 = #244; kbAlt3 = #245; kbAlt4 = #246; kbAlt5 = #247;
           kbAlt6 = #248; kbAlt7 = #249; kbAlt8 = #250; kbAlt9 = #251; kbAlt0 = #252;


     const kbLavyHorny       = #218 {'Ú'};
           kbLavyDolny       = #192 {'À'};
           kbPravyHorny      = #191 {'¿'};
           kbPravyDolny      = #217 {'Ù'};

           kbVodorovny       = #196 {'Ä'};
           kbVodorovnyDole   = #194 {'Â'};
           kbVodorovnyHore   = #193 {'Á'};

           kbZvisly          = #179 {'³'};
           kbZvislyDolava    = #180 {'´'};
           kbZvislyDoprava   = #195 {'Ã'};

           kbKriz            = #197 {'Å'};


           kbLavy2Horny2     = #201 {'É'};
           kbLavy2Dolny2     = #200 {'È'};
           kbPravy2Horny2    = #187 {'»'};
           kbPravy2Dolny2    = #188 {'¼'};

           kbVodorovny2      = #205 {'Í'};
           kbVodorovny2Dole2 = #203 {'Ë'};
           kbVodorovny2Hore2 = #202 {'Ê'};

           kbZvisly2         = #186 {'º'};
           kbZvisly2Dolava2  = #185 {'¹'};
           kbZvisly2Doprava2 = #204 {'Ì'};

           kbKriz22          = #206 {'Î'};


           kbZvisly2Dolava   = #182 {'¶'};
           kbZvisly2Doprava  = #199 {'Ç'};

           kbVodorovny2Dole  = #209 {'Ñ'};
           kbVodorovny2Hore  = #207 {'Ï'};
           kbVodorovnyDole2  = #210 {'Ò'};
           kbVodorovnyHore2  = #208 {'Ğ'};

           kbZvislyDolava2   = #181 {'µ'};
           kbZvislyDoprava2  = #198 {'Æ'};

           kbKrizZvisly2     = #215 {'×'};
           kbKrizVodorovny2  = #216 {'Ø'};


           kbLavy2Horny      = #214 {'Ö'};
           kbLavy2Dolny      = #211 {'Ó'};
           kbPravy2Horny     = #183 {'·'};
           kbPravy2Dolny     = #189 {'½'};

           kbLavyHorny2      = #213 {'Õ'};
           kbLavyDolny2      = #212 {'Ô'};
           kbPravyHorny2     = #184 {'¸'};
           kbPravyDolny2     = #190 {'¾'};


     {const kbAlfa            = 224  à
           kbBeta            = 225  :á
           kbGama            = 226  :â
           kbPi              = 227  :ã
           kbSuma            = 228  :ä
           kbOmega           = 229  :å
           kmMikro           = 230  :æ
           i:= 231  :ç
           i:= 232  :è
           i:= 233  :é
           i:= 234  :ê
           i:= 235  :ë
           i:= 236  :ì
           i:= 237  :í
           i:= 238  :î
           i:= 239  :ï
           i:= 240  :ğ
           i:= 241  :ñ
           i:= 242  :ò
           i:= 243  :ó
           i:= 244  :ô
           i:= 245  :õ
           i:= 246  :ö
           i:= 247  :÷
           i:= 248  :ø
           i:= 249  :ù
           i:= 250  :ú
           i:= 251  :û
           i:= 252  :ü
           i:= 253  :ı
           i:= 254  :ş
           i:= 255  :ÿ
     }


     const { Keyboard state and shift masks
           }
           kbRightShift  = $01; { if the Right Shift key is currently down    }
           kbLeftShift   = $02; { if the Left Shift key is currently down     }
           kbCtrlShift   = $04; { if the Ctrl key is currently down           }
           kbAltShift    = $08; { if the Alt key is currently down            }
           kbScrollState = $10; { if the keyboard is in the Scroll Lock state }
           kbNumState    = $20; { if the keyboard is in the Num Lock state    }
           kbCapsState   = $40; { if the keyboard is in the Caps Lock state   }
           kbInsState    = $80; { if the keyboard is in the Ins Lock state    }


     const legal_keys = [' '.. 'z' {$IFDEF A36YKA} ,'€'..'¯','à'..'ù' {$ENDIF}];


     const last_kbhit: real = 0;



     function  kbhit: bool;
     function  GetKey: char;
     function  ReadKey(loops: longint; Proc: TProc): char;
     function  GetShiftState: byte;

     function  GetAltChar (kbXXX: char): char;
     function  GetAltCode (kbXXX: char): char;
     function  CtrlToArrow(kbXXX: char): char;

     const     is_kblayout : bool = false; { narodnie znaky }
     function  kblayout (kbXXX: char): char;
     function  upcase (ch: char): char;



implementation

uses DOS, Crt, BIOS, keyb_int {$IFDEF DISPLAY_ZHASNI} , SVGA {$ENDIF};

{
 KeyPressed pre vsetky klavesy. Teda skoro vsetky.
}
function kbhit: bool;
   var   Reg : Registers;
         b   : bool;
   begin
     Reg.AH:= $11;
     Intr($16,Reg);
     b:= ((Reg.Flags and FZero)=0);
     if b then last_kbhit:= AbsTime;
     {$IFDEF DISPLAY_ZHASNI}
      if b and Rozsviet then
         begin
           b:= false;
           kb_clear
         end;
     {$ENDIF}
     kbhit:= b
   end; { kbhit }

{
 Caka na stlacenie klavesy, vrati jej kod
}
function GetKey: char;
   var   Reg : Registers;
         ch  : char;
   begin
     Reg.AH:= $10;
     Intr($16,Reg);
     if Reg.AL in[0,224] then
        begin
          if Reg.AH<130 then GetKey:= Chr(Reg.AH+123)
          else GetKey:= Chr(Reg.AH);
          last_kbhit:= AbsTime;
        end
     else GetKey:= Chr(Reg.AL);
     {$IFDEF DISPLAY_ZHASNI}
      if Rozsviet then
         begin
           GetKey:= NULL;
           kb_clear
         end;
     {$ENDIF}
   end; { GetKey }

{
Caka loops cyklov na stlacenie klavesnice,
ak sa tak stalo, tak vrati kod klavesy, inak NULL
}
function ReadKey(loops: longint; Proc: TProc): char;
   begin
     if not WaitForEvent(loops,kbhit,Proc) then ReadKey:= GetKey
     else ReadKey:= kbNoKey
   end; { ReadKey }

{
vrati hodnotu Shift
}
function GetShiftState: Byte; assembler;
     var ShiftState: Byte absolute $40:$17;
     asm
	  MOV	ES,Seg0040
          MOV	AL,ES:ShiftState
     end;

{
  vrati kod klavesy bez kombinacie s Alt
}
function GetAltChar(kbXXX: char): char;
   const AltCodes1: array[139..173] of Char = 'QWERTYUIOP'#0#0#0#0'ASDFGHJKL'#0#0#0#0#0'ZXCVBNM';
         AltCodes2: array[243..252] of Char = '1234567890';
   begin
     case ord(kbXXX) of
       139..173: GetAltChar := AltCodes1[ord(kbXXX)];
       243..252: GetAltChar := AltCodes2[ord(kbXXX)];
       else GetAltChar:= #0
     end;
   end;

{
 vrati kod klavesy s kombinaciou s Alt
}
function GetAltCode(kbXXX: char): char;
   const AltCodes1: array['A'..'Z'] of Char =  kbAltA+kbAltB+kbAltC+kbAltD+kbAltE
                                              +kbAltF+kbAltG+kbAltH+kbAltI+kbAltJ
                                              +kbAltK+kbAltL+kbAltM+kbAltN+kbAltO
                                              +kbAltP+kbAltQ+kbAltR+kbAltS+kbAltT
                                              +kbAltU+kbAltV+kbAltW+kbAltX+kbAltY
                                              +kbAltZ;
         AltCodes2: array['0'..'9'] of Char =  kbAlt1+kbAlt2+kbAlt3+kbAlt4+kbAlt5
                                              +kbAlt6+kbAlt7+kbAlt8+kbAlt9+kbAlt0;
   begin
     kbXXX:= upcase(kbXXX);
     case kbXXX of
       'A'..'Z': GetAltCode := AltCodes1[kbXXX];
       '0'..'9': GetAltCode := AltCodes2[kbXXX]
       else GetAltCode:= kbXXX
     end;
   end;


{
CtrlToArrow - konvertuje WordStar normu na sipky
}
function CtrlToArrow(kbXXX: char): char;
   const NumCodes = 11;
         CtrlCodes : array[0..NumCodes-1] of char = ^S^D^E^X^A^F^G^V^R^C^H;
         ArrowCodes: array[0..NumCodes-1] of char =
                        (kbLeft, kbRight, kbUp, kbDown, kbHome, kbEnd,
                         kbDel, kbIns, kbPgUp, kbPgDn, kbBS
                        );
   var   i: int;
   begin
     CtrlToArrow:= kbXXX;
     for i:= 0 to NumCodes - 1 do
       if kbXXX = CtrlCodes[I] then
          begin
            CtrlToArrow:= ArrowCodes[I];
            Exit
          end;
   end;  { CtrlToArrow }


function kblayout(kbXXX: char): char;
        {$IFDEF A36YKA}
   const kb_QWERTY : string[77] =  '!@#$%^&*()_|'
                                  +'QWERTYUIOP{}'
                                  +'qwertyuiop[]'
                                  +'ASDFGHJKL:"'
                                  +'asdfghjkl;'''
                                  +'ZXCVBNM<>?'
                                  +'zxcvbnm,./';
        
         kb_A36YKA : string[77] =  '!":/%,.;()_?'
                                  +'‰–“Š…ƒ˜™‡•š'
                                  +'©æãª¥­£èé§åê'
                                  +'”›‚€‹„†'
                                  +'äë¢ ¯à®«¤¦í'
                                  +'Ÿ—‘Œˆ’œ,'
                                  +'ïçá¬¨âì¡î.';
        {$ENDIF}
   var   i : int;
   begin
    {$IFDEF A36YKA}
     if is_kblayout then
        begin
          i:= 1; while (i<=length(kb_QWERTY)) and (kbXXX<>kb_QWERTY[i]) do inc(i);
          if i<=length(kb_QWERTY) then kblayout:= kb_A36YKA[i]
          else kblayout:= kbXXX
        end
     else
    {$ENDIF}
     kblayout:= kbXXX
   end;

function upcase(ch: char): char;
   begin
     {$IFDEF A36YKA}
       if ord(ch) in [160..175] then upcase:= chr(ord(ch)-32)
       else if ord(ch) in [224..239] then upcase:= chr(ord(ch)-80)
       else upcase:= system.UpCase(ch)
     {$ELSE}
       upcase:= system.UpCase(ch)
     {$ENDIF}
   end;


begin
  kb_clear
end. { Keyb }

(*
  ASCII:

  
  
   !"#$%&'()
  *+,-./  0123456789:;<=>?@
  ABCDEFGHIJKLMNOPQRSTUVWXYZ[\]^_`
  abcdefghijklmnopqrstuvwxyz{|}
  ~€‚ƒ„…†‡ˆ‰Š‹Œ‘’“”•–—˜™š›œŸ ¡¢£¤¥¦§¨
  ©ª«¬­®¯°±²³´µ¶·¸¹º»¼½¾¿ÀÁÂÃÄÅÆÇÈÉÊËÌÍÎÏĞÑÒÓÔÕÖ×ØÙÚÛÜİŞß
  àáâãäåæçèéêëìíîïğñòóôõö÷øùúûüışÿ

  ABCDEFGHIJKLMNOPQRSTUVWXYZ[\]^_`abcdefghijklmnopqrstuvwxyz{|}~
  €‚ƒ„…†‡ˆ‰Š‹Œ‘’“”•–—˜™š›œŸ ¡¢£¤¥¦§¨©ª«¬­®¯°±²³´µ¶·¸¹º»¼½¾
  ¿ÀÁÂÃÄÅÆÇÈÉÊËÌÍÎÏĞÑÒÓÔÕÖ×ØÙÚÛÜİŞßàáâãäåæçèéêëìíîïğñòóôõö÷øùúûüış

  KBLAYOUT
  1234567890-=	©æãª¥­£èé§åê
 ÿäë¢ ¯à®«¤¦í'ÿ\ïçá¬¨âì¡î.!":/%,.;()_+ ‰–“Š…ƒ˜™‡•š
 ÿ”›‚€‹„†~ÿ|Ÿ—‘Œˆ’œ.1234567890-=	©æãª¥­£èé§åù
 ÿä÷¢ ¯à®«¤¦õ'ÿ\ïçá¬¨âì¡î.!":/%,.;()_+ ‰–“Š…ƒ˜™‡•ø
 ÿ”ö‚€‹„†ô~ÿ|Ÿ—‘Œˆ’œ,1234567890-=	qwertyuiop[]
 ÿasdfghjkl;'`ÿ\zxcvbnm,./!@#$%^&*()_+ QWERTYUIOP{}
 ÿASDFGHJKL:"~ÿ|ZXCVBNM<>?
*)