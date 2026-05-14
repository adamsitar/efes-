{ Funkcia skontroluje integritu archivnych suborov :
  a) zmena hlavicky pri povodnom formate :
      - stary ma 3 polozky oddelene znakmi podla LET_1_1
      - novy  ma 4 polozky oddelene znakmi podla ICAO
  b) zmena sposobu kodovania, ak su dovolene dlhe stripy
      - v starom protokole sa koduje
}

function addDirExt (dirn,extn: string): string;
   begin
     if (length(dirn)>0) and (dirn[length(dirn)]='\') then
        begin
          dirn:= copy(dirn,1,length(dirn)-1);
          {if (length[extn]>0) and (extn[length(extn)]='\') then
          if (s<>'') and (s[length(s)]<>'\') then s:= s+'\';}
        end;
     if (extn<>'') and (extn[1]<>'.') then extn:= '.'+extn;
     if (extn<>'') and (extn[length(extn)]<>'\') then extn:= extn+'\';
     addDirExt:= dirn+extn
   end;


function konvertovat_archiv (fn: string; attr: byte): bool;
   var   head : TDB_head;
   begin
     konvertovat_archiv:=  DB_head(fn,head) and (head.attr = attr)
   end;


procedure konverzia_archivu(path,ext    : string;

                            resave_p2   : pointer;    { TByFunc_p2 <> nil   }
                            item_size   : word;
                            disp_item   : pointer;    { Tproc_p odalokuje nacitany buffer }

                            riadkov     : byte;
                            {DATAcode    : pointer;}
                            DATAdecode  : pointer
                            {KEYcode     : pointer}
                           );
    var   path0   : string;
          item    : pointer;
          Dir     : PDir;
          Files,i,x,y : int;
          ftime   : Longint; { For Get/SetFTime}
          f       : file;
    begin
      path0:= addDirExt(path,'0');
      {MoveDir(path+'*.'+ext, path0);-> riesi sa nizsie }
      getmem(item,item_size);
      fillchar(item^,item_size,0);
      GetDir(path+'*.'+ext, Dir,ReadOnly+Archive,Files);
      for i:= 0 to Files-1 do
        begin
          if i=0 then _mkdir(path0);
          Assign(f, path+Dir^[i]^.name); Reset(f); GetFTime(f,ftime); Close(f);
          MoveFile(path+Dir^[i]^.name,path0+Dir^[i]^.name);
          if not InGraphMode then
             begin
               if i=0 then begin x:= wherex; y:= wherey end else gotoxy(x,y);
               write('Converting data of '+path0+Dir^[i]^.name+'... ');
             end;
          do_items_DB(resave_p2,nil,
                      item,disp_item,
                      path0+Dir^[i]^.name,
                      riadkov,nil{DATAcode},DATAdecode,nil{KEYcode},nil
                     );
          if FExists(path+Dir^[i]^.name)=0 then
             begin
               Assign(f, path+Dir^[i]^.name); Reset(f); SetFTime(f,ftime); Close(f);
             end;
          if not InGraphMode then
             begin
               gotoxy(x,y); clreol;
               {writeln('  Done.');}
             end
        end;
      FreeDir(Dir,Files);
      freemem(item,item_size);
      archivuj_stare_plany
    end;
