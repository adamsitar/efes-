{$IFDEF MET_RLI}

 const fn_MRL : string[12] = '';

 function is_SOD_MRL (data: pbytes; dlz: int): bool;
    var   typ: word;
    begin
      move(data^,typ,sizeof(word));
      is_SOD_MRL:= (dlz=SOD_MRLsize) and (typ=SOD_MRL);
    end;

 function is_EOD_MRL (data: pbytes; dlz: int): bool;
    var   typ: word;
    begin
      move(data^,typ,sizeof(word));
      is_EOD_MRL:= (dlz=EOD_MRLsize) and (typ=EOD_MRL);
    end;


{ ulozi udaje do archivacneho subora
  s nazvom rrmmddhh.mm podla minuty spracovania prvej spravy,
  kde prve dva byte obsahuju pocet byte daneho pkt,
  posledne byte (kbNL) prida fcia archive_data
}
 procedure save_MRL (data: pbytes; size: int);
     var   d: pbytes;
           f: file of byte;
     begin
       if fn_MRL='' then Exit;
       getmem (d,sizeof(size)+size);
       move(size,d^,sizeof(size));
       move(data^,d^[sizeof(size)],size);

       archive_data (pathMRL,fn_MRL, d,sizeof(size)+size,'',false,false);
       freemem (d,sizeof(size)+size);
     end;

 function  read_MRL (var f: file;
                     var data: pbytes; { zatial ocakavam alokovany buffer na vstupe }
                     var size: int;
                     data_off,         { offset od zaciatku riadku }
                     buff_size: int    { maximalny pocet byte v jednom riadku }
                    ): bool;
     var   i,p : int;
           b : byte;
     begin
       read_MRL:= false;
       size:= 0;
       if eof(f) then Exit;
       seek(f,filepos(f)+data_off);
       BlockRead(f,size,sizeof(size),p);
       BlockRead(f,data^,minimum(size,buff_size));
       if size>buff_size then seek(f,filepos(f)+size-buff_size);
       size:= minimum(size,buff_size);
       seek(f,filepos(f)+length(kbNL));
       read_MRL:= true
     end;

 procedure distribute_MRL (data: pbytes; dlz: int);
     begin
       NETsend_msg (BROADCASTaddress, spr0_MRL,pchars(data),dlz,false,net_flag_SEND);
     end;


 procedure prehlad_MRL;
     begin
     end;

 procedure prehlad_MRL_ARCH;
     begin
     end;

{$ENDIF}