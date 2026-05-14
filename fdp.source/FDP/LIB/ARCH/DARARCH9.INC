{ ---------------------------------------- }
{  subory: open, save, close               }
{ ---------------------------------------- }

procedure save_DARpacket(data: pbytes; size: word; header: record_header);
    const semaphor : bool = false;
    var   pkt : TDARpkt;
    begin
      if archive_DAR and (DARbuff<>nil) and (not semaphor) then
         begin
           semaphor:= true;
           {$IFDEF IPX}
             decode_ASTERIX_time(data,size);
           {$ENDIF}

           pkt.header:= header; { SaveRLI, SaveStrip }
           pkt.header.Tick:= TickCounter;
           pkt.header.DataLength:= minimum(size,sizeof(pkt.data));
           move(data^,pkt.data,pkt.header.DataLength);

           DARbuff^.save(@pkt);
           semaphor:= false
         end
    end;

function read_DARpacket(var pkt: TDARpkt): bool;
   begin
     read_DARpacket:= archive_DAR and (DARbuff<>nil) and (DARbuff^.read(@pkt))
   end;


procedure close__DAR_file(wait: bool);
   var    P    : DirStr;
          N,N_ : NameStr;
          E    : ExtStr;
          FN   : string;

   var    Dummy,SavedBytes1,SavedBytes2 : Word;
          StartTime : UNIX_time;
          EndTime   : UNIX_time;
          d : DOS_date;
          t : DOS_time;
          dt : TDatum;

   const  semaphor: bool = false;
   begin
     if (DAR_name='') then Exit;
   { bolo by dobre nahrat vsetky zvysne pakety z buffera }

   { pockame na dalsiu minutu }
     if not semaphor then
        begin
          FN:= DAR_name;
          FSplit(FN, P,N,E);
          if wait and (not semaphor) then
             begin
               semaphor:= true;
               InfoCakaj(msgWAITING,tit_CLOSE_ARCHIVE);
               N_:= N;
               while (N = N_) do
                 begin
                   N_:= inttostr(BIOS.month,2,0)+inttostr(BIOS.day,2,0)+inttostr(BIOS.hour,2,0)+inttostr(BIOS.min,2,0);
                   CheckProcesses
                 end;
               InfoCakaj_zatvor;
               semaphor:= false
             end
        end;

   { urobila to ina slucka ? }
     if FN<>DAR_name then Exit;

   { zapis casu ukoncenia do hlavicky }
     ResetIOError;
     ReadFileHeader(DAR_file, StartTime, EndTime);
     GetDatem(d.year,d.month,d.day,dummy);
     GetTimem(t.hour,t.min,t.sec);
     datum_init (dt, d.day,d.month,d.year, t.hour,t.min,t.sec);
     EndTime:= dos2unix(dt);
     SaveFileHeader(DAR_file, false, StartTime,EndTime);
     Close(DAR_file);
     ResetIOError;
     recorded_in_hour:= 25;
     DAR_name:= ''
   end;


function  backup_DAR_file(Path: string): int;
   var    D  : DirStr;
          N  : NameStr;
          E  : ExtStr;
          fn : string;
   begin
     {
     FSplit(Path, D,N,E);
     while N = inttostr(BIOS.month,2,0)+inttostr(BIOS.day,2,0)+inttostr(BIOS.hour,2,0)+inttostr(BIOS.min,2,0) do Main;
     }
     if (DAR_name=Path) then close__DAR_file(true);
     backup_DAR_file:= BackupFile(Path)
   end;
