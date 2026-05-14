{$I comp.h}
{$R-,O-}
{$C FIXED PRELOAD PERMANENT}

unit IPXarch;


interface

    uses  TypeDef, uTime, Data_h,
          NET_def, IPX_def,
          {$I gr_unit.h},
          LoadSave;


    const {$IFDEF DEBUG}
             DAR_buff_size : int = 30;
          {$ELSE}
             DAR_buff_size : int = 50;
          {$ENDIF}


    const writeln_DAR        : bool = true;
          writeln_DAR_utc    : bool = false;
          cl_DAR             : byte = clGR5;


    const extDAR      = '.DAR';
          posRLI_ARCH : byte = 0;


    var   d,d2 : DOS_date;
          t,t2 : DOS_time;
          ut   : UNIX_time;

          InFile,OutFile : file;

          header : record_header;
         {data   : record_data;}
          st,et  : UNIX_time;

          ThisNetwork : Byte;
          EDD_Node    : Byte;
          EDD_Address, ThisNetworkZeroAddress, ThisNetworkBroadcastAddress : Word;

          SaveStrip,SaveRLI : record_header;


    procedure init_ARCH (_save_plans: pointer);

    procedure save_RLI  (data: PIPXdata; data_length: word); far;
    procedure save_plan (_plan: pointer; _code_plan: pointer; _code: word); far;

    function  backup_IPX_file(Path: string): int;


implementation

uses  BIOS, _Check, DOS,
      math, str0, mess, io,
      RTR_def, _IPX, _RTR, _NET,
      Arrays, App,
      Msg, FDP_msg, Archiv;


const inbuff   : PBuffer = nil;  { musi byt }


var   SRD_file : file;
const SRD_name : string = '';

      recorded_in_hour: int = 25;


procedure nastav_packet_cas(data: PIPXdata);
    begin
      if setTime_ then Exit;

      {$IFDEF CAS_RLI} {$IFDEF BLAVA}
         Year_:= Year;     Month_:= Month;    Day_:= Day;
         hour_:= data^[4]; min_  := data^[5]; sec_:= data^[6];

         if (hour_>=23) or (hour_<=1) then Exit;

         if     CheckTime(hour_,min_,sec_) and CheckDate(Year_,Month_,Day_,true)
            and (abs(absTime - DTtoSec(Year_,Month_,Day_, hour_,min_,sec_)) > 3) then
                 begin
                   setTime_:= true
                 end;
      {$ENDIF} {$ENDIF}
    end;


{ ---------------------------------------- }
{  subory: open, save, close               }
{ ---------------------------------------- }

const semaphor : bool = false;
var   packet   : TARCHpacket;

procedure save_IPXpacket(data: PIPXdata; data_length: word; header: record_header);
    begin
      if enRLI_ARCH and (inbuff<>nil) and (not semaphor) then
         begin
           semaphor:= true;

           if data^[0] = $90 then nastav_packet_cas(data);
           packet.header:= header; { SaveRLI, SaveStrip }
           packet.header.Tick:= TickCounter;
           packet.header.DataLength:= data_length;
           packet.data:= data^;

           inbuff^.save(@packet);
           semaphor:= false
         end
    end;

function read_ARCHpacket(var packet: TARCHpacket): bool;
   begin
     read_ARCHpacket:= inbuff^.read(@packet)
   end;


procedure close__SRD_file(wait: bool);
   var    P    : DirStr;
          N,N_ : NameStr;
          E    : ExtStr;
          FN   : string;
   var    Dummy,SavedBytes1,SavedBytes2 : Word;
          StartTime : UNIX_time;
          EndTime   : UNIX_time;
          d : DOS_date;
          t : DOS_time;
   const  semaphor: bool = false;
   begin
     if (SRD_name='') then Exit;
   { bolo by dobre nahrat vsetky zvysne pakety z buffera }

   { pockame na dalsiu minutu }
     if not semaphor then
        begin
          FN:= SRD_name;
          FSplit(FN, P,N,E);
          if wait and (not semaphor) then
             begin
               semaphor:= true;
               InfoCakaj(msgWAITING,tit_CLOSE_ARCHIVE);
               N_:= N;
               while (N = N_) do
                 begin
                   N_:= inttostr(BIOS.month,2,0)+inttostr(BIOS.day,2,0)+inttostr(BIOS.hour,2,0)+inttostr(BIOS.min,2,0);
                   Check
                 end;
               InfoCakaj_zatvor;
               semaphor:= false
             end
        end;

   { urobila to ina slucka ? }
     if FN<>SRD_name then Exit;

   { zapis casu ukoncenia do hlavicky }
     ResetIOError;
     ReadFileHeader(SRD_file, StartTime, EndTime);
     GetDatem(d.year,d.month,d.day,dummy);
     GetTimem(t.hour,t.min,t.sec);
     EndTime := dos2unix(d,t);
     SaveFileHeader(SRD_file, false, StartTime,EndTime);
     Close(SRD_file);
     ResetIOError;
     recorded_in_hour:= 25;
     SRD_name:= ''
   end;

function  backup_IPX_file(Path: string): int;
   var    D  : DirStr;
          N  : NameStr;
          E  : ExtStr;
          fn : string;
   begin
     {
     FSplit(Path, D,N,E);
     while N = inttostr(BIOS.month,2,0)+inttostr(BIOS.day,2,0)+inttostr(BIOS.hour,2,0)+inttostr(BIOS.min,2,0) do Main;
     }
     if (SRD_name=Path) then close__SRD_file(true);
     backup_IPX_file:= BackupFile(Path)
   end;


{ ---------------------------------------- }
{  ulozenie dat                            }
{ ---------------------------------------- }
const save_plans: pointer = nil; { procedura pre ulozenie vsetkytch planov na zaciatku kazdej hodiny }

procedure save_plan(_plan: pointer; _code_plan: pointer; _code: word);
    var   Np      : TNETpacket;
          Rp      : TRTRpkt_bin;
          dlz,res : word;
          len_ok  : bool;
    begin
      fillchar(Np,sizeof(Np),0);
      if (_code_plan<>nil) then TProc_p2(_code_plan)(_plan, @Np) else Np.head.dlz:= 0;
      res:= net_pck(Np, _code, NODEs^[posRLI_ARCH].desc.adr, Np.head.dlz, @Np.data);
      dlz:= code_NETpkt_to_RTRpkt(@Np,@Rp,nil,rpRTI, len_ok);
      save_IPXpacket(@Rp, dlz, SaveStrip)
    end;

procedure save_RLI(data: PIPXdata; data_length: word);
    begin
      save_IPXpacket(data, data_length, SaveRLI)
    end;


{ ---------------------------------------- }
{  hlavna slucka                           }
{ ---------------------------------------- }

var  SaveMain    : TProc;
     save_packet : TARCHpacket;

procedure check_ARCH; far;
    var   fn    : string;
          ext   : string[4];
          pocet : int;
    const semaphor1 : bool= false;
          semaphor2 : bool= false;
    begin
      if @SaveMain<>nil then SaveMain;

    { subor s nahravkou }
      if (recorded_in_hour<>hour) and (not semaphor1) then
         begin
           semaphor1:= true;
           if SRD_name<>'' then close__SRD_file(true);
         { Delay(1000); }
           recorded_in_hour:= hour;  { musi byt az za close }
           fn:= get_ARCHfn(min);
           pocet:= GetNmbOfFiles(path_IPX+fn+extDAR);
           if pocet>0 then ext:= '.D'+inttostr(sec,2,0) else ext:= extDAR;
           SRD_name:=  path_IPX + fn + ext;
           Assign (SRD_file,SRD_name);
           Rewrite(SRD_file,1);
           SaveFileHeader(SRD_file, true,0,0);
           if save_plans<>nil then Tproc(save_plans);
           semaphor1:= false
         end;

    { data do subora    }
      if (inbuff<>nil) and (inbuff^.is) and (not semaphor2) then
         begin
           semaphor2:= true;
           read_ARCHpacket(save_packet);
           {$IFDEF DEBUG}
            {
             if writeln_DAR then
                MainApp^.writeln_(@save_packet.data,save_packet.header.DataLength, cl_DAR, 'ú ',writeln_DAR_utc);
            }
           {$ENDIF}
           SaveRecord(SRD_file, true, save_packet.header,save_packet.data);
           semaphor2:= false
         end;

      semaphor:= false
    end;


var SaveExit: pointer;

procedure done_ARCH; far;
    begin
      if inbuff=nil then Exit;

      while inbuff^.is do check_ARCH;
      close__SRD_file(false);
      if inbuff<>nil then dispose(inbuff,done);
      inbuff:= nil;

      ExitProc:= SaveExit
    end;

procedure init_ARCH(_save_plans: pointer);
   var    i: int;
   begin
     save_plans:= _save_plans;
     if (DAR_buff_size=0) or (inbuff<>nil) then Exit;

     ThisNetwork := $01;
     EDD_Node    := IPXnode;
     EDD_Address := (ThisNetwork shl 8) or EDD_Node;
     ThisNetworkZeroAddress := (ThisNetwork shl 8) or $00;
     ThisNetworkBroadcastAddress := (ThisNetwork shl 8) or $FF;

     with SaveStrip do
       begin
         Tick := 0;
         FromNode := EDD_Address;
         ToNode   := ThisNetworkZeroAddress;
         DataLength := 0;
       end;

     with SaveRLI do
       begin
         Tick := 0;
         FromNode := ThisNetworkBroadcastAddress;
         ToNode   := ThisNetworkZeroAddress;
         DataLength := 0;
       end;

     inbuff:= New(PBuffer,Init(DAR_buff_size,sizeof(TARCHpacket), false));
     SaveExit:= ExitProc;
     ExitProc:= @done_ARCH;

     SaveMain:= ACheck;
     ACheck:= check_ARCH
   end;

begin
  DAR_buff_size:= Limit(read_cfg_word(SYSTEMcfg,cfg_DAR_buff_size,DAR_buff_size), 0,300, 0);
  if DAR_buff_size>0 then _IPX.save_RLI:= @save_RLI
end.
