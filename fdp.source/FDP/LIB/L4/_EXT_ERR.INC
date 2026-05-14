{ תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
   spracovanie alertov...
  תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
}

{
  funkcia pre ulozenie vystrahy do subora a nastavenie priznaku
}
 (*
 procedure O_EXT.process_ALR(data: pchars; size: word; head: string);
     begin
       is_ALR:= true;
     end;
 *)

 function O_EXT.read_ALR: bool;
    begin
      { opravit i v kontrole check ... stare vystrahy ...
      }
    end;



{ תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
   spracovanie chybovych sprav
  תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת

 Ak su detekovane chyby v syntaxi prijatych sprav vyhodnotia sa
 v zavislosti na nastaveni prepinaca icao_ERR_DISP -> ak je povoleny,
 zaradi sa do chyboveho radu a program si ich automaticky nacitava.
 V opacnom pripade sa vkladaju do radu odlozenych/nespracovanych chyb
 a cakaju na povolenie spracovania...

 Funkcia pre ulozenie chybovej spravy do subora a nastavenie priznaku.
 Chybova sprava obsahuje dve polozky :
  - popis chyby
  - paket

 ? Spravit kontrolu na prepis iny paketom ?
}

 function O_EXT._key_data (data: pchars; size: word): string;
    var   s: string;
    begin
      s[0]:= chr(minimum(size,sizeof(s)-1));
      move(data^,s[1],ord(s[0]));
      _key_data:= s
    end;

 function O_EXT._fn_data (data: pchars; size: word): string;
    begin
      _fn_data:= copy(getstr(_key_data(data,size),1,['.']),1,8)
    end;

 function O_EXT._path_data (data: pchars; size: word): string;
    begin
      _path_data:= pathTMP
    end;

{
}
 function O_EXT._fn_ERR(data: pchars; size: word; ext: string): string;
    begin
       {fn_ext+inttostr(cislo_err,8-length(ext),0)}
      _fn_ERR:= _fn_data(data,size)+'.'+delchar(ext,['.'])
    end;

 function O_EXT._fn_ERRmask(ext: string): string;
    begin
      {_fn_ERRmask:= fn_ext+'*.'+delchar(ext,['.'])}
      _fn_ERRmask:= '*.'+delchar(ext,['.'])
    end;


 procedure O_EXT._save_ERR (data: pchars; size: word; msg: string;
                            _fn_ext: string;
                            var is_pkt: bool;
                            delete,distribute: bool
                           );
     var   fn: string;
     begin
      {$IFDEF ERR}
        if not process_err_en then Exit;

       {$IFOPT R+} {$DEFINE RPLUS} {$R-} {$ENDIF}
        {inc(cislo_err); if cislo_err=0 then inc(cislo_err);}
       {$IFDEF RPLUS} {$R+} {$ENDIF}

        fn:= pathERR+_fn_ERR(data,size,_fn_ext);
        if delete then io.del(getstr(fn,1,['.'])+ext_all);
        _save_txt_file(fn, msg, data,size, true);
       {$IFDEF SYNCHRONIZE_EXT}
        if distribute then error_pkt (data,size,msg,fn,false);
       {$ENDIF}
      {$ELSE}
        fn:= '';
      {$ENDIF}

       is_pkt:= true
     end;


 procedure O_EXT.process_ERR_HEAD (src: TPKT_SRC; data: pchars; size: word; res: string);
    begin
      if icao_HEAD_ERR then process_ERR_DATA (src, data,size,res, true,true,true)
      else writeln_pkt(nil,0,arch_SYS,res,cl_SYS,false,true);
    end;

 procedure O_EXT.process_ERR_DATA (src: TPKT_SRC;
                                   data: pchars; size: word; res: string;
                                   err_save,err_show,distribute: bool
                                  );
     var   f : file;
           s,prompt : string;
     begin
      {$IFDEF ERR}
       if err_save and (process_err_en and (data<>nil) and (size>0)) then
          begin
            if { IFDEF BACKUP} is_receive_pkt and { ENDIF} err_show and icao_ERR_DISPLAY then
               begin
                { chyba sa nerozosiela, naco aj, hned sa spracovava
                }
                 _save_ERR (data,size,res,ext_ERR,is_ERR, true,distribute)
               end
            else begin
                  { distribuje sa kazdy odlozeny paket,
                    ak je to dovolene,
                    aby bolo mozne spracovat ho na
                    podriadenej stanici
                  }
                   _save_ERR (data,size,res,ext_ERS,is_ERS, false,distribute)
                 end;
            is_ERR:= true
          end
       else
      {$ENDIF}
            begin
              s:= ''; {s[0]:= chr(minimum(20,size)); move(data^,s[1],ord(s[0]));s:= cut_(s)+'...';}
              if src=src_ext then prompt:= archERR+archREC
              else if src=src_net then prompt:= archNET+archERR
              else prompt:= archED+archERR;
              writeln_pkt(@s[1],length(s),prompt{arch_ERR},res,cl_ERR,true,false)
            end;
       if src=src_ext then
          begin
            {s[0]:= chr(Minimum(N(120-length(s)),size));
            move(data^,s[0],ord(s[0]));
            if s<>'' then
               begin
                 res:= res+' '+s;
                 if length(s)<size then res:= res+'...'
               end;}
            write_err_log(res);
          end;
     end;


 const  err_f : Tcentr = (x: initX; y: initY; m: 1);

 function O_EXT._read_ERR (_ext : string;
                            _init_buttons,_handle_buttons : pointer;
                            _hlpXXX : pchar;
                            var is_pkt : bool
                           ): bool;
    var   ep   : type_ext_err_pkt;
          pch  : pchar;
          cis  : int;
          bres : bool;
          page : int;
          s    : string;
    begin
      _read_ERR:= false;
      fillchar(ep,sizeof(ep),0);

     {$IFDEF ERR}
       ep.fn:= pathERR+najstarsi_subor(pathERR,_fn_ERRmask(_ext));
       if _read_txt_file(ep.fn,true,ep.err,ep.pkt) then
          begin
            page:= GetPStrItems(ep.pkt, setNL+setNL_);
            while (page>0) do
              begin
                s:= GetPStr(ep.pkt,page,setNL+setNL_);
                if cut_(s)='' then dec(page)
                else break
              end;
            pch:= strnew(ep.pkt);
            {s:= ep.err; if length(s)<80 then s:= 'Error :  '+s;}
            bres:= _icao_editor({'Error :  '+}ep.err,
                                 err_f.x,err_f.y,err_f.m,
                                 false,
                                 ed_riadkov,ed_znakov, minimum(page+5,ed_velkost_strany),

                                 nil,nil, @check_icao_editor_err,
                                 0{dbtWIDTH+10},dbtHEIGHT+10,
                                 _init_buttons,_handle_buttons,
                                 @Self,
                                 @ep, nil{@handle_end_state_editor_bt_ers},

                                 clBUTTON_COLOR,clgre,0,clgre, clBUTTON_COLOR,hlp_cl_tx,
                                 {0,clgre,0,clgre,help.cl_bg,help.cl_tx,}
                                 spr_err_ed,spr_err_del,
                                 _hlpXXX,
                                 pch
                               );
            strdispose(pch)
          end
       else bres:= true;

       strdispose(ep.pkt);
       if not bres then Exit;

       ep.fn:= najmladsi_subor(pathERR,_fn_ERRmask(_ext));
       is_pkt:= ep.fn<>'';
       _read_ERR:= true
     {$ENDIF}
    end;