(*-------------------------------------------------------------------*)
(* LETVIS FDP - COM                                                  *)
(* (c) Ales Kosice 1993  (ab)                                        *)
(*-------------------------------------------------------------------*)
{$I comp.h}

{$X+,I-,S-,P-,F+,O-}
{$C FIXED PRELOAD PERMANENT}


unit _COM;


interface


     uses  TypeDef, Arrays,
           NET_def;


    {$IFDEF COM}

     const size_of_COMdata = sizeof(TNETpkt_head)+2*sizeof(TNETadr)+size_of_NETpkt+100;

     type  PCOMpkt = ^TCOMpkt;
           TCOMpkt = record
             p : int;
             b : array[0..size_of_COMdata-1] of char
           end;


     var   COMbuffer     : TCOMpkt;

     const COMznakov     : int = 0;

           COM_buff      : PBuffer = nil;
           COM_buff_size = {$IFDEF DEBUG} 3 {$ELSE} 10 {$ENDIF};

           COMi          : byte = 2;

           ZAC_SPR_COM   = #1;
           KON_SPR_COM   = #10;


     procedure COM_initialize(handler: pointer);

     procedure COM_init;

     procedure COMsave  (pkt: PCOMpkt); far;
     function  COMread  (var pkt: TNETpkt): bool;
     function  COMsend  (const pkt: TNETpkt): int;

    {$ENDIF}


implementation

{$IFDEF COM}

uses  Crt, BIOS, COMs, DOS, IO,
      str0, mess,
      Kody;


const COMcfg          = 'com'+ext_ini;

      COM_initialized : bool = false;
      COMhandler      : pointer = nil;

      COMrych         : word = 1200;


var   Port21          : byte;
      SaveExit        : pointer;


procedure COMsave(pkt: PCOMpkt);
   begin
     if COM_buff<>nil then COM_buff^.save(pkt);
   end;

{
  Sprava je kodovana "1" + pkt.head,pkt.data + "0". Znaky "1" ani "0"
  sa v prenasanej sprave nesmu vyskytovat, vsetko musi byt zakodovane
  ako strings...
}

{ I _COM.int}

function code_NETpkt_to_COMpkt(const pkt: TNETpkt; var Cpkt: TCOMpkt): int;
   var   s     : string;
         dlz,i : int;
         w     : word;
   begin
     s:=   ZAC_SPR_COM
               + IntToStr(pkt.head.typ,5,1)

         + '-' + pkt.adr
         + '-' + pkt.ods

         + '-' + IntToStr(pkt.head.cis,5,1)
         + '-' + IntToStr(pkt.pkt.dlz, 5,1)

         ;

     if is_proL(pkt.adr) then
        begin
          s:= s + '-' + IntToStr(pkt.head.ind,3,1)
                + '-' + IntToStr(pkt.head.poc,3,1)
        end;

     s:= s + ODD_SPR;

     dlz:= length(s);
     Move(s[1],Cpkt.b, dlz);
     Move(pkt.pkt.data,Cpkt.b[dlz],pkt.pkt.dlz);
     inc(dlz,pkt.pkt.dlz);

    { vypocet kontrolneho suctu
    }{$IFOPT R+} {$DEFINE R} {$R-} {$ENDIF}
      w:= 0; for i:= 0 to dlz-1 do inc(w,ord(Cpkt.b[i]));
      Cpkt.b[dlz]:= chr(lo(w));
     {$IFDEF R} {$R+} {$ENDIF}

     Cpkt.b[dlz+1]:= KON_SPR_COM;
     Cpkt.p:= dlz+2;

     code_NETpkt_to_COMpkt:= Cpkt.p
   end;


function code_COMpkt_to_NETpkt(const Cpkt: TCOMpkt; var pkt: TNETpkt): bool;
   var   i,c : int;
         s   : string;
         w   : word;
   begin
     fillchar(pkt, sizeof(pkt), 0);

     code_COMpkt_to_NETpkt:= false;
     {$IFOPT R+} {$DEFINE R} {$R-} {$ENDIF}
      w:= 0; for i:= 0 to Cpkt.p-3 do inc(w,ord(Cpkt.b[i]));
     {$IFDEF R} {$R+} {$ENDIF}
     if (lo(w)<>ord(Cpkt.b[Cpkt.p-2])) {or (Cpkt.b[0]<>ZAC_SPR_COM) or (Cpkt.b[Cpkt.p-1]<>KON_SPR_COM)} then exit;

     i:= 0; while (i<Cpkt.p) and (Cpkt.b[i]<>ODD_SPR) do inc(i);
     if (i<2) or (i>=Cpkt.p) or (i>sizeof(s)) then Exit;

     move(Cpkt.b[1],s[1],i-1);
     s[0]:= chr(i-1);

     pkt.head.typ := GetInt(s,1,['-']);

     pkt.adr := GetStr(s,2,['-']);
     pkt.ods := GetStr(s,3,['-']);

     pkt.head.cis := GetInt(s,4,['-']);
     pkt.pkt.dlz  := GetInt(s,5,['-']);

     if is_proL(pkt.ods) then
        begin
          pkt.head.ind := GetInt(s,6,['-']);
          pkt.head.poc := GetInt(s,7,['-'])
        end;

     new_NETpkt_data (@Cpkt.b[i+1],pkt.pkt.dlz, pkt.pkt);

     code_COMpkt_to_NETpkt:= true
   end;



function COMread (var pkt: TNETpkt): bool;
   var   Cpkt: TCOMpkt;
         res : bool;
   begin
     res:= (COM_buff<>nil) and COM_buff^.read(@Cpkt);
     if res then
        begin
          res:= code_COMpkt_to_NETpkt(Cpkt,pkt);
          if not res then disp_NETpkt(@pkt)
        end;
     COMread:= res
   end;


function  COMsend (const pkt: TNETpkt): int;
   var    Cpkt : PCOMpkt;
          dlz  : int;
   begin
     New(Cpkt);
     dlz:= code_NETpkt_to_COMpkt(pkt, Cpkt^);
     if SendCOMib(COMi, Pbytes(@Cpkt^.b), dlz, false) then COMsend:= netRES_OK else COMsend:= netTIME_OUT;
     Dispose(Cpkt);
   end;


procedure Read_COMcfg;
    var   f : Text;
          s : string;
          i : int;
          nl: bool;
    begin
      nl:= false;
      if Exists(COMcfg)<>0 then MessError(COMcfg+' - > can not read, used default parameters (COM=2, IRQ=3, 1200Bd).',true,nl)
      else begin
             COMi:= read_cfg_word(COMcfg,cfg_COM_0X,COMi);
             COMrych:= read_cfg_word(COMcfg,cfg_COM_MODE,COMrych);
             INT_COM[COMi]:= read_cfg_word(COMcfg,cfg_COM_INT,INT_COM[COMi]{-INT_OFF}) {+ INT_OFF};
             if not INT_COM[COMi] in [2..5] then RunError('Invalid COM interrupt number...')
           end
    end;


procedure COM_initialize(handler: pointer);
    var   Bd : word;
    begin
      write('Initializing COM...  ');
      Read_COMcfg;

      COM_buff:= New(PBuffer,Init(COM_buff_size,sizeof(TCOMpkt), false));

      asm cli end;
      SaveCOMi (COMi);
      Bd:= _MODE(COMrych,true);
      SetCOMi  (COMi, lo(Bd),hi(Bd),$1B,$01,$0B);
      GetIntVec(COMi,COMhandler);
     {if COM_intr=nil then COM_intr:= @ReadCOM;}
      SetIntVec(INT_COM[COMi],handler);

      Port21:= Port[$21];
      Port[$21]:= Port[$21] and $E7; { 0xE8 && 0xF7 }
      asm sti end;

      COMaddress:= NETaddress;
      writeln('Done. (COM='+IntToStr(COMi,1,1)
                  +', IRQ='+IntToStr(INT_COM[COMi]{-INT_OFF},1,1){+'['+IntToStr(INT_COM[COMi],1,1)+']'+}
                  +', MODE='+IntToStr(COMrych,1,1)+')'
             );
      {$IFDEF DEBUG} {readln} {$ELSE} Delay(3000); {$ENDIF}

      COM_initialized:= true
    end;


procedure COM_init;
    begin
      COMaddress:= NETaddress;
    end;


procedure COM_done; far;
    begin
     {$IFDEF DEBUG_EXIT} writeln('COM'); {$ENDIF}

      if COM_initialized then
         begin
           asm cli end;
           SetCOMi(COMi, LoBd[COMi],HiBd[COMi],Bits[COMi],inte[COMi],Modem[COMi]);
           SetIntVec(COMi,COMhandler);
           Port[$21]:= Port21;
           asm sti end;

           Dispose(COM_buff,Done)
         end;

      ExitProc:= SaveExit
    end;

{$ENDIF}

begin
 {$IFDEF COM}
  SaveExit:= ExitProc;
  ExitProc:= @COM_done;
 {$ENDIF}
end. { _COM }