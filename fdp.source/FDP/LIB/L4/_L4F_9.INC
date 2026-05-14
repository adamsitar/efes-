{ vyhlada typ podla ICAO Doc.8643
  pre typ zodpovedajuci ciselniku
}
 function _9c_data(_9b: string): string;
    var   ind: int;
          s: string;
    begin
      if (lst_9bICAO<>nil) and (_9b<>ZZZZ) and (lst_9bICAO^.find(_9b, s,ind)<>-1) then
          _9c_data:= lst_9bICAO^._wtc(s)
      else _9c_data:= ''
    end;

 function _code_9abc_by8643 (var _9: string; _9a,_9b,_9c: string; _lst: PList_9b_icao; _zzzz: bool): string;
    var   _9b0 : string;

    function assign_9bc(__lst: PList_9b_icao): string;
       var   s   : string;
             ind : int;
       begin
         if __lst^.find(_9b0, s,ind)>-1 then
            begin
              _9b:= __lst^._icao(s);
              _9c:= __lst^._wtc(s);
              if (_9c='') and (lst_9bICAO^.find(_9b, s,ind)>-1) then _9c:= lst_9bICAO^._wtc(s);
            end
         else _9b:= ZZZZ;
         assign_9bc:= _9b
       end;

    begin
      if (_lst<>nil) and (lst_9bICAO<>nil) then
        begin
          _9b0:= _9b;
          if (assign_9bc(_lst)=ZZZZ) and _zzzz then assign_9bc(lst_9bZZZZ);
          if _9c<>'' then _9c:= icao_NXT+_9c;
          _9:= _9a+_9b+_9c
        end;
      _code_9abc_by8643:= _9b
    end;


 function _code_9MIL_by8643 (var _9: string): string;
    var   _9a,_9b,_9c, s : string;
          ind : int;
    begin
      {$IFDEF LZ}
       if (lst_9bMIL<>nil) and (length(_9)<=kod_9b) and (delchar(_9,setCisl)='') then
          begin
           { je to vojensky typ
           }_9a:= ''; _9b:= ''; _9c:= '';
            _9a:= copy(_9,1,length(_9)-kod_9bM);
            _9b:= copy(_9,length(_9)-kod_9bM+1,kod_9bM);
            _9b:= _code_9abc_by8643(_9, _9a,_9b,_9c,lst_9bMIL,false);
          end
       else
      {$ENDIF}
        begin
          decode_l4_9 (_9, _9a,_9b,_9c);
          if (lst_9bICAO<>nil) and (lst_9bICAO^.find(_9b, s,ind)=-1) then _9b:= ZZZZ
        end;
      _code_9MIL_by8643:= _9b
    end;


{ vyhlada typ podla ICAO Doc.8643
  pre typ zodpovedajuci ruskemu ciselniku
}
 function  _code_9TSGA_by8643 (var _9: string): string;
    var    _9a,_9b,_9c: string;
    begin
      decode_l4_9 (_9, _9a,_9b,_9c);
      _9b:= _code_9abc_by8643 (_9, _9a,_9b,_9c,lst_9bTSGA,true);
    end;


 function  _code_9_by8643_ (var _9: string; _afil_9: bool; var err9b,err9c: bool): string;
    var    _90,_9b0,_9c0, _9a,_9b,_9c, s: string;
           ind: int;
    begin
      _90:= _9;
      decode_l4_9 (_9, _9a,_9b,_9c);
      _9b0:= _9b; _9c0:= _9c;

      if _afil_9 then
        begin
          if (lst_9bICAO<>nil) and (lst_9bICAO^.find(_9b0, s,ind)=-1) then _9b:= ZZZZ;

          if _9b_CHECK_TSGA and (_9b=ZZZZ) and (lst_9bTSGA<>nil) then
             _9b:= _code_9abc_by8643 (_9, _9a,_9b0,_9c,lst_9bTSGA,false);

          if _9b_CHECK_ZZZZ and (_9b=ZZZZ) and (lst_9bZZZZ<>nil) then
             _9b:= _code_9abc_by8643 (_9, _9a,_9b0,_9c,lst_9bZZZZ,false);

          if _9b_CHECK_MIL  and (_9b=ZZZZ) and (lst_9bMIL <>nil) then
             _9b:= _code_9MIL_by8643 (_9);

          _9c:= _9c_data(_9b);
        end;

      err9b:= _9b_CHECK_ICAO and (_9b=ZZZZ)  and (_9b0<>_9b);
      err9c:= _9c_CHECK_ICAO and (_9b<>ZZZZ) and (_9c0<>_9c);
      if not (_9c_CHECK_ZZZZ and (_9b<>ZZZZ) and ((_9c0='') or (_9c0<>_9c))) then _9c:= _9c0;

      if _9c<>'' then _9c:= icao_NXT+_9c;    { Mam tu zmatok nad zmatok }
      if _9b=ZZZZ then _9b:= _9b0;
      _9:= _9a+_9b+_9c;

      _code_9_by8643_:= _9b
    end;


 function  _code_9_by8643 (var _9: string; _zzzz: bool): string;
    var    err9b,eer9c: bool;
           _90: string;
    begin
      _90:= _9;
      _code_9_by8643:= _code_9_by8643_ (_9,_AFIL_9, err9b,eer9c);
      _AFIL_9:= true;
      if (not _zzzz) and (err9b{_9b=ZZZZ}) then _9:= _90;
    end;


 function  _check_9_by8643 (var _9: string; var res: string; _ever,_zzzz: bool): int;
    var    ires : int;
           b1,b2, err9b,err9c : bool;
    begin
      ires:= 0; res:= '';
      if _ever then
         begin
           b1:= _9b_CHECK_TSGA; _9b_CHECK_TSGA:= true;
           b2:= _9b_CHECK_ZZZZ; _9b_CHECK_ZZZZ:= true;
         end;
      _code_9_by8643_ (_9, _AFIL_9, err9b,err9c);
      if err9b then ires:= l4_err(a_9b,a_9b,i_9b,err_9b_neznamy, res)
      else if err9c and (not _9c_CHECK_ZZZZ) then ires:= l4_err(a_9c,a_9c,i_9c,err_9c_odlisny, res);
      if _ever then
         begin
           _9b_CHECK_TSGA:= b1;
           _9b_CHECK_ZZZZ:= b2;
         end;
      _check_9_by8643:= ires
    end;
