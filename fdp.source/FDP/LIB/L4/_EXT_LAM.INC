{ ----------------------------------------------
  Odoslanie potvrdenia
  ----------------------------------------------
}
 function O_EXT._decode_LAM  (data: pchars; size: word;
                              var header: string;
                              var lam,ods,key: string;
                              var typ: TNETtyp;
                              var res: string
                             ): bool;
    var   head,adr,cislo,header_data : string;
          ires : int;
    begin
      _decode_LAM:= false; lam:= ''; ods:= ''; key:= ''; typ:= 0;
      ires:= _icao_head_type(header,res);
      if (ires>=0) and (p_heads_EXT^[ires]=hd_LAM) then
         if _decode_header (header, head,adr,ods,cislo, header_data, @res) then
            if (NODE_THIS='') or (adr=NODE_THIS) then
               begin
                 prijaty_LAM (header_data,ods, key,typ);
                 _decode_LAM:= true
               end
            else res:= err_ext_received_address
         else res:= err_ext_lam_data
    end;

 function O_EXT.decode_LAM  (data: pchars; size: word;
                             var header: string;
                             var res: string
                            ): bool;
    var   lam,ods,key : string;
          typ : TNETtyp;
    begin
      decode_LAM:= _decode_LAM (data,size, header, lam,ods,key, typ,res);
    end;


 function  O_EXT._LAM_data (header: string): string;
    begin
      _lam_data:= header
    end;

 function O_EXT._is_to_LAM (data: pchars; size: word; header: string): bool;
    var   head,res : string;
    begin
      _is_to_LAM:=
             (NODE_REMOTE<>NODE_PROMISCUITE)
         and (NODE_THIS<>NODE_PROMISCUITE)
         and decode_head (header,head,res)
         and ((head<>hd_LAM) and (icao_head_type (head,res, p_heads_LAM,heads_LAM)>=0))
    end;


 procedure O_EXT.send_LAM (data: pchars; size: word; header: string);
     var   res, head,adr,ods,cislo, header_data : string;
     begin
       res:= '';
       if not _decode_header (header, head,adr,ods,cislo, header_data, @res) then Exit;
       if (ods<>'') and (ods<>NODE_THIS) then send_data (NODE_REMOTE,hd_LAM,'', _lam_data(header), nil,0, '',0)
       else writeln_pkt(@header[1],length(header), arch_ERR,err_ext_uncorrect_address+' ('+ods+')...',cl_ERR,false,false)
     end;


 procedure O_EXT.LAM_received_pkt (data: pchars; size: word);
     var   zac,kon : word;
           header,res : string;
     begin
       if (    decode_frame  (data,size, zac,kon, res)
           and (not decode_HeartBeat (data,size))
           and decode_header (data,size, zac,kon, header, res, false)
           and _is_to_LAM (data,size,header)
          )
           then send_LAM (data,size,header);
     end;


{ ----------------------------------------------
  Evidencia ocakavanych potvrdeni
  ----------------------------------------------
}
 function eq_ack(ack1, ack2: PEXTack): bool;
    begin
      eq_ack:=  (ack1^.id=ack2^.id)
                {and eq_str0(ack1^.adr,ack2^.adr)}
                {and eq_str0(ack1^.key,ack2^.key)}
    end;

 procedure new_ack(ack1, ack2: PEXTack);
     begin
       FillChar(ack2^,SizeOf(ack2^),0);
       ack2^:= ack1^;
       if ack1<>nil then
          begin
            ack2^.adr:= StrNew(ack1^.adr);
            ack2^.key:= StrNew(ack1^.key);
          end;
     end;

 procedure disp_ack(ack: PEXTack);
     begin
       strdispose(ack^.adr);
       strdispose(ack^.key);
     end;


 constructor OEXTack.Init(_items: word);
       begin
         inherited Init(_items,SizeOf(TEXTack), @new_ack,nil,@disp_ack);
         p_eq_items:= @eq_ack;
       end;


{ ----------------------------------------------
  - zatial nie je zabezpecene, aby si system
    pamatal nepotvrdenie sprav pri vypadku,
    ich potvrdenie sa nezapisuje
    do relevantnej spravy
}


 function  O_EXT.timeout_uzla (adr: string): real;
    begin
      timeout_uzla:= LAM_TimeOut
    end;


{ zaradi LAM do ocakavaneho radu
}
 procedure  O_EXT.ocakavany_LAM (header,adr,key: string; typ: TNETtyp);
     var    res, _head,_adr,_ods,_cislo,_header_data, lam : string;
            ack : TEXTack;
     begin
       if (EXTack=nil) or (key='') or (not _decode_header (header, _head,_adr,_ods,_cislo,_header_data, @res)) then Exit;
       fillchar(ack,sizeof(ack),0);
       ack.id   := l4str (_code_header ('',_ods,_adr,_cislo,'',nil,_header_data));
       ack.head := _head;
       ack.adr  := strpasnew(adr);
       ack.key  := strpasnew(key);
       ack.typ  := typ;
       ack.sent := absTime;
       ack.tmout:= timeout_uzla(adr);
       EXTack^.add(@ack);
       disp_ack(@ack)
     end;


{ zmaze LAM z ocakavaneho radu
}
 procedure  O_EXT.prijaty_LAM (id,adr: string; var key: string; var typ: TNETtyp);
     var    ack  : TEXTack;
            ires : int;
     begin
       key:= '';
       if (EXTack=nil) or (id='') then Exit;
       fillchar(ack,sizeof(ack),0);
       ack.id:= l4str(id);
       ires:= EXTack^.find_data(@ack);
       if ires>=0 then
          begin
            key:= strpas(TEXTack(EXTack^.ap^[ires]^).key);
            typ:= TEXTack(EXTack^.ap^[ires]^).typ;
            EXTack^.del(ires);
            {Moze byt vykonana nasledna akcia...}
          end;
       disp_ack(@ack)
     end;


{ vyvola (virtualnu) reakciu na timeout pri nepotvrdeni spravy
}
 procedure O_EXT.neprijaty_LAM(id,adr,head,key: string; var res: string);
     begin
       res:= tit_sprava+' "'+id+'" '+tit_nebola+' '+tit_potvrdena;
       writeln_pkt(nil,0,{@lam[1],length(lam),}archERR+archREC,res,cl_ERR,true,false);
     end;


 procedure  O_EXT.manage_LAM;
     const  sec : byte = 60;
     var    ack : PEXTack;
            i   : int;
            res : string;
     begin
       if (EXTack=nil) or (sec=BIOS.sec) then Exit;
       sec:= BIOS.sec;
       i:= 0; while (i<=EXTack^.top) do
         begin
           ack:= PEXTack(EXTack^.ap^[i]);
           if TimeOutSec(ack^.sent, absTime, ack^.tmout) then
             begin
               neprijaty_LAM(ack^.id,strpas(ack^.adr),ack^.head,strpas(ack^.key),res);
               EXTack^.del(i);
             end
          else inc(i)
        end
     end;
