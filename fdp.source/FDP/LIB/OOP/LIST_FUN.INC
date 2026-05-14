procedure new_ListDesc (var lst: TListDesc; fn: string);
     begin
       fillchar(lst,sizeof(lst),0);
       lst.fn:= strpasnew(fn)
     end;

 procedure disp_ListDesc(var lst: TListDesc);
     begin
       strdispose(lst.fn)
     end;


{ ---------------------------------------------
  aplikacne procedury
  ---------------------------------------------
}

 function _get_item(x,y: int; _lst: PListDesc; _odd: TcharSet; _pos: int; _sort: bool; _filter: PBFunc_s): string;
    var   L: PList;
    begin
      {test:= true;}
      L:= New(PList,Init(_lst,'',_odd,_pos,_sort,_filter,false));
      _get_item:= L^.get_item(x,y);
      Dispose(L,Done);
      {test:= false;}
    end;

 function _get_item_(x,y: int ; fn: string; _odd: TcharSet; _pos: int; _sort: bool; _filter: PBFunc_s): string;
    var   _lst : TListDesc;
    begin
      fillchar(_lst,sizeof(_lst),0); fn:= fn+NULL; _lst.fn:= @fn[1];
      _get_item_:= _get_item(x,y, @_lst,_odd, _pos,_sort,_filter)
    end;


 function _get_line (s: string; _lst: PListDesc; _odd: TcharSet; _pos,_rdk: int): string;
    var   L : PList;
    begin
      L:= New(PList,Init(_lst,'',_odd,_rdk{lst_cely_riadok},false,nil,true));
      _get_line:= L^.get_line(s,_pos,nil);
      Dispose(L,Done)
    end;

 function _get_line_(s,fn: string; _odd: TcharSet; _pos,_rdk: int): string;
    var   _lst : TListDesc;
    begin
      fillchar(_lst,sizeof(_lst),0); fn:= fn+#0; _lst.fn:= @fn[1];
      _get_line_:= _get_line(s,@_lst,_odd, _pos,_rdk)
    end;


 function _get_comment(s: string; _lst: PListDesc; _odd: TcharSet; _pos: int): string;
    var   L: PList;
    begin
      L:= New(PList,Init(_lst,'',_odd,lst_cely_riadok, false,nil,true));
      _get_comment:= L^.get_comment(s,nil);
      Dispose(L,Done)
    end;

 function _get_comment_(s,fn: string; _odd: TcharSet; _pos: int): string;
    var   _lst : TListDesc;
    begin
      fillchar(_lst,sizeof(_lst),0); fn:= fn+NULL; _lst.fn:= @fn[1];
      _get_comment_:= _get_comment(s,@_lst,_odd,_pos)
    end;


 { indikuje, ci je s je v listingu _fname
 }
 function _in_list_(s: string; _lst: PListDesc; _odd: TcharSet; _pos: int; _filter: PBFunc_s): int;
    var   L: PList;
    begin
      L:= New(PList,Init(_lst,'',_odd,_pos, false, _filter,true));
      _in_list_:= L^.is_in(s);
      Dispose(L,Done)
    end;

 function _in_list(s: string; _lst: PListDesc; _odd: TcharSet; _pos: int; _filter: PBFunc_s): bool;
    begin
      _in_list:= _in_list_(s,_lst,_odd,_pos, _filter)<>-1
    end;

 {
 function show_item(x,y: int ; _lst: PListDesc; _pos: int; _sort: bool): string;
    var   L: PList;
    begin
      L:= New(PList,Init(_lst,_pos,_sort));
      get_item:= L^.get_item(x,y);
      Dispose(L,Done)
    end;
 }


{ ---------------------------------------------
  nacitanie chyby
  ---------------------------------------------
}
 function _find_err(fn: string; arrpos,arrspec: string; errpos, errspec: word; var errs: string): bool;
    var   is,nis: bool;
          err : string;
    begin
      err:= arrpos+'-'+cstr(errspec,1);
      errs:= cut_(getstr(_get_comment_(err,fn,[],lst_vsetky_polozky),2,setKomen));
      _find_err:= errs<>'';
      nis:= errs='';
      if nis then errs:= 'Error...';
      is:= errs[length(errs)] in [',','.',';','?','!'];
      if cut_(arrspec)<>'' then errs:= errs + ' ('+arrspec+')';
      if not is then errs:= errs+'.';
      if nis or disp_ERRCODE then errs:= errs+' ['+err+']';
    end;

 function _get_err(fn: string; arrpos,arrspec: string; errpos, errspec: word; var errs: string): word;
    begin
      _find_err(fn, arrpos,arrspec, errpos,errspec, errs);
      _get_err:= errpos;
    end;
