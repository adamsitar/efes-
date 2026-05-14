procedure save_text(path : string;
                    S : pointer;     { ukazovatel na data s typom string }
                    R : int;         { pocet riadkov }
                    get_s : pointer  { @SFunc_si }
                   );
    var   f : text;
          i : int;
    begin
      Assign(f, path);
      if vytvor_novy_subor(path) then Rewrite(f)
      else Append(f);
      if get_s<>nil then for i:= 0 to R-1 do writeln(f,SFunc_si(get_s)(S,i));
      writeln(f,'');
      Close(f)
    end;

{$IFDEF DEBUG}
 { I io_arch.inc}
{$ENDIF}

procedure archivuj_data(_path,_name: string; data: PBytes; pocet: long; ident: string; is_utc, is___: bool);
    begin
      archive_data(_path,_name, data,pocet, ident, is_utc,is___);
    end;


{
function _arch_path(_path: string): string;
   begin
     if archive_COM then _arch_path:= path_COM
     else _arch_path:= _path
   end;

function _arch_ext(_ext: string): string;
   begin
     if archive_COM then _arch_ext:= extCOM
     else _arch_ext:= _Ext
   end;
}

{ IFDEF ARCHIVE_COM}
  procedure archivuj_cmn(s: string);
      var   p: string;
            b: bool;
      begin
        if (_another_line_err_log) or ((not _another_line_err_log) and (cut_(s)<>'')) then
           begin p:= arch_SYS; b:= true end
        else begin p:= '  '; b:= false end;
        archivuj_data(path_COM,get_ARCHfn(0)+'.'+extCOM, @s[1],length(s), p,b,false)
      end;

  procedure archivuj_cfg(cfg: string);
      var   fn: string;
      begin
        fn:= path_COM+get_ARCHfn(0)+'.'+extCOM;
        archivuj_cmn('Configuration has been changed '+cfg+').');
        CopyFileI(cfg,fn,0,true,true);
        archivuj_cmn(kbNL+'End of configuration copy.'+kbNL+').');
      end;

{ ENDIF}


procedure zalohuj_archiv(_path,_name: string; _title,_mess: string; _handler: pointer);
    var   bck    : PScrollDIR;
          _Event : TEvent;
    begin
     { IFNDEF DEMO}
      if _handler=nil then _handler:= @BackupFile;
      bck:= New(PScrollDIR,Init(_path,_name,
                                _title,_mess,
                                nil,nil,true,0,
                                @comp_dir_date,0,
                                _handler,
                                nil)
                               );
      bck^.RunLocalFunc(_Event,SCROLL_NC);
      Dispose(bck,Done)
     { ENDIF}
    end;