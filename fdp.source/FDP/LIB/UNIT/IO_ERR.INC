procedure archive_err(fn, err: string);
    var   f : text;
    begin
      fn:= pathTMP+fn;
      if _filesize(fn+'.$$$') > MAX_SIZE_IOERR_FN then MoveFile(fn+'.$$$', fn+'.bak');
      ResetIOError;

      vytvor_novy_subor(fn+'.$$$');
      if Exists(fn)<>0 then Exit;

      Assign(f,fn+'.$$$'); Append(f);
      writeln(f,err);
      writeln(f,'');
      Close(f)
    end;


function IOError: bool;
   begin
     IOErrorCode:= IOResult;
     if (IOErrorCode=0) and (DosError<>0) and (DosError<>18) then IOErrorCode:= DosError;
     IOError:= (IOErrorCode<>0)
   end; { IOError }


function is_IOError(kde: string): bool;
   var   is_IOErr : bool;
         IOErr    : int;
         f        : text;
   begin
     is_IOErr:= IOError;
     is_IOError:= is_IOErr;
     IOerr:= IOErrorCode;
     ResetIOError;

     if (not is_IOErr) or (kde='') then Exit;
     archive_err(IOERR_N, kde)
   end;


procedure ResetIOError;
    begin
      IOErrorCode:= 0;                 { enables the following call }
      if IOError then IOErrorCode:= 0; { clears IOResult }
      DosError:= 0
    end; { ResetIOError }


function ErrorMessage(ErrorCode: word; FileName: string): string;
   var   ErrorNumber: string [5];
   begin
     case ErrorCode of
     {$IFDEF SLOVAK}
       2    : ErrorMessage:= 'S£bor "' + cut_(FileName) + '" nen jden˜.';
       3    : ErrorMessage:= 'Cesta "' + cut_(FileName) + '" neexistuje.';
       4    : ErrorMessage:= 'Pr¡li¨ mnoho otvoren˜ch s£borov.';
       5    : ErrorMessage:= 'Nedovolen˜ pr¡stup (Read-only, directory full ?).';
       6    : ErrorMessage:= 'Chybn  obsluha.';
       8    : ErrorMessage:= 'M lo pam„te.';
       10   : ErrorMessage:= 'Zl‚ prostredie.';
       11   : ErrorMessage:= 'Chybn˜ form t.';
       18   : ErrorMessage:= 'Neexistuj£ ƒal¨ie s£bory.';
       100  : ErrorMessage:= 'Ch˜baj£ci koniec s£bora.';
       101  : ErrorMessage:= 'Pln˜ disk.';
       150  : ErrorMessage:= 'Disk je chr nen˜ proti z pisu.';
       151  : ErrorMessage:= 'Nezn me zariadenie.';
       152  : ErrorMessage:= 'Nie je vlo‘en  disketa.';
       153  : ErrorMessage:= 'Nezn my pr¡kaz.';
       154  : ErrorMessage:= 'CRC chyba v d tach.';
       155  : ErrorMessage:= 'Bad drive request structure length';
       156  : ErrorMessage:= 'Disk seek error';
       157  : ErrorMessage:= 'Nezn my typ m‚dia.';
       158  : ErrorMessage:= 'Sektor nebol n jden˜.';
       159  : ErrorMessage:= 'V tla‡iarni nie je papier.';
       160  : ErrorMessage:= 'Chyba pri z pise.';
       161  : ErrorMessage:= 'Chyba pri ‡¡tan¡.';
       162  : ErrorMessage:= 'Chyba hardware.';

       1001 : ErrorMessage:= 'M lo miesta na disku/diskete (uvolnite/vlozte novu)...';

       io_intr_by_user : ErrorMessage:= 'Oper cia bola u‘¡vateŒom zru¨en .'

       else if ErrorCode <> 0
               then begin
                      Str(ErrorCode,ErrorNumber);
                      ErrorMessage:= 'I/O chyba (Error code ' + ErrorNumber + ').'
                    end
               else ErrorMessage := ''
     {$ENDIF}

     {$IFDEF CZECH}
          2    : ErrorMessage:= 'Soubor "' + cut_(FileName) + '" jsem nena¨el.';
          3    : ErrorMessage:= 'Cesta "' + cut_(FileName) + '" neexistuje.';
          4    : ErrorMessage:= 'P©¡li¨ mnoho otev©en˜ch soubor–.';
          5    : ErrorMessage:= 'Nepovolen˜ p©¡stup (Read-only, directory full ?).';
          6    : ErrorMessage:= 'Chybn  obsluha.';
          8    : ErrorMessage:= 'M lo pamˆti.';
          10   : ErrorMessage:= 'Zl‚ prost©ed¡.';
          11   : ErrorMessage:= 'Chybn˜ form t.';
          18   : ErrorMessage:= 'Neexistuj¡ ƒal¨¡ soubory.';
          100  : ErrorMessage:= 'Chybˆj¡c¡ konec souboru.';
          101  : ErrorMessage:= 'Pln˜ disk.';
          150  : ErrorMessage:= 'Disk je chr nˆn proti z pisu.';
          151  : ErrorMessage:= 'Nezn me za©¡zen¡.';
          152  : ErrorMessage:= 'Nen¡ vlo‘ena disketa..';
          153  : ErrorMessage:= 'Nezn my p©¡kaz.';
          154  : ErrorMessage:= 'CRC chyba v datech.';
          155  : ErrorMessage:= 'Bad drive request structure length.';
          156  : ErrorMessage:= 'Disk seek error.';
          157  : ErrorMessage:= 'Nezn my typ m‚dia.';
          158  : ErrorMessage:= 'Sektor nebyl nalezen.';
          159  : ErrorMessage:= 'V tisk rne nen¡ pap¡r.';
          160  : ErrorMessage:= 'Chyba p©i z pisu.';
          161  : ErrorMessage:= 'Chyba p©i ‡ten¡.';
          162  : ErrorMessage:= 'Chyba hardware.';

          1001 : ErrorMessage:= 'M lo prostoru na disku/diskete (uvolnete/vlozte novou)...';

          io_intr_by_user : ErrorMessage:= 'Operace byla u‘¡vatelem zru¨ena.'

          else if ErrorCode <> 0
                  then begin
                         Str(ErrorCode,ErrorNumber);
                         ErrorMessage:= 'I/O chyba (Error code ' + ErrorNumber + ').'
                       end
                  else ErrorMessage := ''
     {$ENDIF}

     {$IFDEF ENGLISH}
          2    : ErrorMessage:= 'File(s) "' + cut_(FileName) + '" not found.';
          3    : ErrorMessage:= 'Path "' + cut_(FileName) + '" not found.';
          4    : ErrorMessage:= 'To many open files.';
          5    : ErrorMessage:= 'Access denied (Read-only, directory full ?).';
          6    : ErrorMessage:= 'Invalid handle.';
          8    : ErrorMessage:= 'Not enough memory.';
          10   : ErrorMessage:= 'Invalid environment.';
          11   : ErrorMessage:= 'Invalid format.';
          18   : ErrorMessage:= 'No more files.;';
          100  : ErrorMessage:= 'Missing end of file.';
          101  : ErrorMessage:= 'Disk full.';
          150  : ErrorMessage:= 'Disk is write-protected.';
          151  : ErrorMessage:= 'Unknown device.';
          152  : ErrorMessage:= 'Floppy disk not inserted.';
          153  : ErrorMessage:= 'Unknown command.';
          154  : ErrorMessage:= 'CRC error in data.';
          155  : ErrorMessage:= 'Bad drive request structure length.';
          156  : ErrorMessage:= 'Disk seek error.';
          157  : ErrorMessage:= 'Unknown type of medium.';
          158  : ErrorMessage:= 'Sector not found.';
          159  : ErrorMessage:= 'Paper out.';
          160  : ErrorMessage:= 'Writting error.';
          161  : ErrorMessage:= 'Reading error.';
          162  : ErrorMessage:= 'Hardware failure.';

          1001 : ErrorMessage:= 'Not enough space on the disk/removable disk (clean/insert another one)...';

          io_intr_by_user : ErrorMessage:= 'Operation has been cancelled by user.'

          else if ErrorCode <> 0
                  then begin
                         Str(ErrorCode,ErrorNumber);
                         ErrorMessage:= 'I/O error (Error code ' + ErrorNumber + ').'
                       end
                  else ErrorMessage := ''
      {$ENDIF}
     end;
     ResetIOError
   end; { ErrorMesage }


