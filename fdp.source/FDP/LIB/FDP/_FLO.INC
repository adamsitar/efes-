{ najde a vrati uzivatela
}
function flo_call(code: string): string;
   var   i: int;
   begin
     code:= uni_str(code);
     while (length(code)>0) and (code[length(code)] in ['0'..'9',' ']) do code:= copy(code,1,length(code)-1);
     if length(code)=kod_FLO then
        begin
          code:= _get_line_(code, code[1]+extFLO,[],1,lst_vsetky_polozky); code:= cut_(code);
          i:= pos(icao_NXIT, code);
          if i>0 then
             begin
               code:= copy(code,i,length(code)-i+1);
               code:= cut_(code)
             end;
        end;
     flo_call:= code
   end;

{ najde a vrati uzivatela
}
function flo_name(code: string): string;
   var   i  : int;
         fn : string;
   begin
     code:= uni_str(code);
     while (length(code)>0) and (code[length(code)] in ['0'..'9',' ']) do code:= copy(code,1,length(code)-1);
     if length(code)=kod_FLO then
        begin
          fn  := code[1]+extFLO;
          code:= cut_(_get_line_(code, fn,[],1,lst_cely_riadok));
          code:= cut_(getstr(code,2, [';','/']));
          if delchar(code,[' '])=cfg_LOCKED then code:= ''
        end;
     flo_name:= code
   end;


const  max_flo_mil = MIN_NET_HEAP_SIZE div sizeof(Tflo_desc);
type   Tflo_mil_descs = array[0..max_flo_mil-1] of Tflo_desc;
       Pflo_mil_descs = ^Tflo_mil_descs;

const  p_flo_mil_descs : Pflo_mil_descs = nil;
       poc_flo_mil : int = 0;


function is_flo_mil (code: string): bool;
   var   i: int;
   begin
     i:= 0; while (i<poc_flo_mil) and (not eq_str(p_flo_mil_descs^[i].kod,code)) do inc (i);
     is_flo_mil:= (i<poc_flo_mil) and (p_flo_mil_descs^[i].typ=mil)
   end;

procedure init_FLO;
    var   f : text;
          i : int;
          s : string;
    begin
      s:= pathLST+strpas(fnPrevM.fn);
      if FExists(s)<>IORES_OK then Exit;

      Assign(f,s); Reset(f);
      while (not Eof(f)) and (poc_flo_mil<max_flo_mil) do if read_line (f,s,[],true) then inc(poc_flo_mil);
      getmem(p_flo_mil_descs,poc_flo_mil*sizeof(Tflo_desc));
      Reset(f); i:= 0;
      while (not Eof(f)) and (i<poc_flo_mil) do
        if read_line (f,s,[],true) then with p_flo_mil_descs^[i] do
           begin
             kod:= uni_str(getstr(s,1,[';']));
             s:= uni_str(getstr(s,2,[';']));
             if s = idMIL then typ:= mil
             {else if s = cfg_FLO_C then typ:= civ}
             else typ:= oth;
             inc(i)
           end;
      Close(f);
    end;

procedure done_FLO;
    begin
      if p_flo_mil_descs<>nil then
         begin
           freemem(p_flo_mil_descs,poc_flo_mil*sizeof(Tflo_desc));
           p_flo_mil_descs:= nil;
           poc_flo_mil:= 0;
         end;
    end;