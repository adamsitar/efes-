
{ -------------------------------------------------------------
  Zisti typ telegramu (TEST, PLN, TLG), kategoriu naliehavosti
  a podla toho spracuje/ulozi tlg na disk, nastavi priznaky
  spracovania...
}

 function O_AFTN.is_prty (data: pchars; size: word; var res: string): string;
    begin
      is_prty:= mtk_tlg_prty (data, size, res)
    end;

{
  (Po rusky :)

   ‡–‡– †‹€273 1011     Ù
   ƒƒ “Š‡‡ƒÙ
   ƒƒ “ŠŠŠ‡„‡œ “ŠŠ“ˆœœ “ŠŠ€–ƒœœ “ŠŠ€›–›’ “Š‡‡ƒ “Š‹‹Žœœ “Š‹‹›œ›œÙ
   020850 “ŠŠ†‡’‡œÙ
   „…‘€ ‚/ 55127-782  615Ù
   ((( ‹ 0312  “ŠŠ†Ù’‚‘ € 2 ,…’Ù
   Š‚‘  33569  150• 2.0  …’Ž‚Ù
   ...
   ...
   ... 4082   )))ƒƒƒƒƒ
   Ù
}

 function O_AFTN._prty_(prty: string; var is_tlg_prty,is_tlg_en,is_tlg_prn : pbool): prtyTLG;
    var   pT: prtyTLG;
    begin
      pT:= _prtyTLG(prty);
      case pT of
         prtySS : begin
                    prty:= tlgSS; {cis_tlg:= @cis_SS;}
                    is_tlg_prty:= @is_SS; is_tlg_en:= @tlg_SS; is_tlg_prn:= @tlg_SSprint;
                  end;
         prtyFF : begin
                    prty:= tlgFF; {cis_tlg:= @cis_FF;}
                    is_tlg_prty:= @is_FF; is_tlg_en:= @tlg_FF; is_tlg_prn:= @tlg_FFprint;
                  end;
         else     begin
                    prty:= tlgKK; {cis_tlg:= @cis_KK;}
                    is_tlg_prty:= @is_KK; is_tlg_en:= @tlg_KK; is_tlg_prn:= @tlg_KKprint;
                  end
      end;
      _prty_:= pT
    end;


 function  O_AFTN._process_HeartBeat (data: pchars; size: word; prty: string): bool;
    var    s : string;
    begin
      s:= get_str(data,size,2,setNL+setNL_,sizeof(string)-1);
      _process_HeartBeat:=     (_prtyTLG(prty)=prtyKK)
                           and (get_str_items (data,size,setNL+setNL_)=2)
                           and (mtks_rus_to_lat(s)=MTK_2_EOT)
    end;


 function O_AFTN._key_data(data: pchars; size: word): string;
    begin
      _key_data:= mtk_tlg_id (data,size);
    end;

 function O_AFTN._fn_data(data: pchars; size: word): string;
    var   fn,ext: string;
          res: string;
    begin
      fn:=  mtk_tlg_id (data,size);
      ext:= mtk_tlg_prty (data,size, res);
      _fn_data:= copy(delchar(fn,[' ']),1,NAME)+'.'+ext
    end;



 function O_AFTN._fn_ERR (data: pchars; size: word; ext: string): string;
    begin
      _fn_ERR:= _fn_TLG(data,size,ext)
    end;

 function O_AFTN._fn_ERRmask (ext: string): string;
    begin
      _fn_ERRmask:= '*.'+delchar(ext,['.'])
    end;


 function O_AFTN._fn_TLG (data: pchars; size: word; prty: string): string;
    var   res : string;
    begin
      res:= getstr(_fn_data(data,size),1,['.']);
      {if res='' then res:= fn_ext+inttostr(cislo_tlg,NAME-length(fn_ext),0);}
      _fn_TLG:= res+'.'+prty;
    end;

 function O_AFTN._path_data (data: pchars; size: word): string;
    begin
      _path_data:= pathTLG
    end;

 function O_AFTN._fn_TLGmask(prty: string): string;
    begin
      _fn_TLGmask:= '*.'+delchar(prty,['.'])
    end;


{
  Telegram sa ulozi do docasneho subora, z ktoreho si ho hlavny cyklus
  vyberie na dalsie spracovanie, ak je povolene pre danu kategoriu
  telegramov...
}

 function  O_AFTN._process_TLG  (data: pchars; size: word; prty: string; distribute: bool): bool;
     var   fn : string;
           f  : file of char;
           {cis_tlg : plong; }is_tlg_prty,is_tlg_en,is_tlg_prn : pbool;
           tprty : prtyTLG;
           res, s : string;
           i : long;

     begin
       _process_TLG:= true;
       if prty='' then prty:= is_prty (data, size, res);

       if _process_HeartBeat(data,size,prty) then Exit;

       tprty:= _prty_(prty, is_tlg_prty,is_tlg_en,is_tlg_prn);
       prty:= sprtyTLG[tprty];

     { Priradenie sekvencneho cisla sprave a jej nahratie do docasneho
       subora .\TMP\TLG00001.SS, pricom v hlavicke je uvedeny "cas, datum"
     }
       is_tlg_prty^:= true;      { paket existuje }

       fn:= pathTLG+_fn_TLG(data,size, prty);
       Assign(f,fn); Rewrite(f);
       s:= prty+tlg_received+' - '+DateToStr2(day,month,year)+', '+TimeToStr2(hour,min,sec,':','.')+kbNL;
       for i:= 1 to length(s) do write(f,s[i]);
       for i:= 1 to size do write(f,data^[i-1]);
       Close(f);

       {$IFDEF PRN}
        if tlg_Print and is_tlg_prn^ then print_pkt(data,size,'');
       {$ENDIF}

       {$IFDEF SYNCHRONIZE_EXT}
        if is_distribute_pkt then distribute_pkt(data,size,'',fn,spr_tlg,'',true);
       {$ENDIF}
     end;

 function O_AFTN.process_data_TLG (src: TPKT_SRC; data: pchars; size: word; var res: string): bool;
    begin
      res:= '';
      process_data_TLG:= _process_TLG (data,size, is_prty (data, size, res), true)
    end;


{
  title je text 'xxxxxx (cas, datum) cccc'
}
 procedure O_AFTN.save_TLG(data: pchars; size: word; title,prty: string);
     var   fn : string;
           f  : text;
           r  : word;
           m,d, hh,mm,ss : byte;
           i  : long;
     begin
      { nahraje sa do archivu ako dokument prijatych a prevzatych paketov
       fn:= get_icao_streamFN(pathTLGr,extTLGr, day,month,year, hour,min);
       vytvor_novy_subor(fn);
       Assign(f,fn); Append(f);
       writeln(f,title+'/'+TimeToStr2(hour,min,sec,':','.'));
       for i:= 1 to get_str_items(data,size, setNL) do
         begin
           writeln(f,get_str(data,size, i, setNL, sizeof(string)-1))
         end;
       writeln(f,'');
       Close(f);
      }
     end;


 function O_AFTN._read_TLG(_ext: string;
                           _check_func, _init_buttons,_handle_buttons : pointer;
                           _page: int
                          ): bool;

    const tlg_f : Tcentr = (x: initX; y: initY; m: 1);

    var   ep   : type_ext_err_pkt;
          pch  : pchar;
          cis  : int;
          bres : bool;

          i,pi : int;
          s    : string;

          c    : char;

    begin
      fillchar(ep,sizeof(ep),0);
      ep.fn:= pathTLG+najstarsi_subor(pathTLG, '*.'+_ext);
      if _read_txt_file(ep.fn,true,ep.err,ep.pkt) then
         begin
         { zobrazi sa a caka na pripadne spracovanie
         } if _page=0 then
              begin
                _page:= GetPStrItems(ep.pkt, setNL+setNL_);
                while (_page>0) do
                  begin
                    s:= GetPStr(ep.pkt,_page,setNL+setNL_);
                    if cut_(s)='' then dec(_page)
                    else break
                  end;
              end;
           pch:= strnew(ep.pkt);
           bres:= _icao_editor(ep.err,
                               tlg_f.x,tlg_f.y,tlg_f.m,
                               true,
                               ed_riadkov,ed_znakov, minimum(_page+5,ed_velkost_strany),

                               nil,nil,_check_func,
                               0{dbtWIDTH+10},dbtHEIGHT+10,

                               _init_buttons,_handle_buttons,
                               @Self,
                               @ep, nil,

                               cfBack,cfText,cfActB,cfActT, {clBUTTON_COLOR+2,0,} hlp_cl_bg,hlp_cl_tx,
                               {0,clgre,0,clgre,help.cl_bg,help.cl_tx,}
                               spr_ed,spr_del,

                               nil{_hlpXXX},
                               pch
                              );
           strdispose(pch)
         end
      else bres:= true;
      strdispose(ep.pkt);

      _read_TLG:= bres
    end;


 function O_AFTN.read_TLG(prty : string): bool;

    const tlg_f : Tcentr = (x: initX; y: initY; m: 1);

    var   is_tlg_prty,is_tlg_en, is_tlg_prn: pbool;
          fn : string;
          bres: bool;

    begin
      _prty_(prty, is_tlg_prty,is_tlg_en,is_tlg_prn);
      {fillchar(ep,sizeof(ep),0);}

      bres:= _read_TLG(prty,@check_tlg_editor,@init_tlg_editor,@handle_tlg_editor,0);

      if bres then
         begin
          {save_TLG(pchars(ep.pkt),strlen(ep.pkt),ep.err,prty); DelFile(ep.fn);
           strdispose(ep.pkt);
          }
           if prty[1]<>'.' then prty:= '.'+prty;
           fn:= najmladsi_subor(pathTLG, '*'+prty);
           is_tlg_prty^:= fn<>'';
         end;

      read_TLG:= bres
    end;
