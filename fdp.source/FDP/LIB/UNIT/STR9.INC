function get_ind_ (data: pchars; size: word; odd: char; var posi: word): bool;
   begin
     posi:= 0;
     while (posi<size) and (data^[posi]<>odd) do inc(posi);
     get_ind_:= posi < size
   end;


function get_ind(data: pchars; size: word; pos: int; odd: TCharSet; var zac,kon: word): bool;
   var   j : int;
   begin
     get_ind:= false;
     if (data=nil) or (size=0) then Exit;
     zac:= 0; kon:= 0; j:= 0;

     while (j<pos) and (zac<size) and (zac<=high(zac)) do
       begin
         while (zac<size) and (data^[zac] in odd) do inc(zac);
         {if (zac<size) and (data^[zac] in odd) then inc(zac); -> po jednom}
         inc(j);
         if j<pos then
            begin
              while (zac<size) and (not (data^[zac] in odd)) and (zac<=high(zac)) do inc(zac)
            end;
       end;

     if j=pos then
        begin
          kon:= zac;
          while (kon<size) and (not (data^[kon] in odd)) and (kon<=high(kon)) do inc(kon);
          if (kon<size) then dec(kon)
          else kon:= size-1
        end;

     get_ind:= (j=pos) and (zac<=kon)
   end;

function get_str_items(data: pchars; size: word; odd: TCharSet): word;
   var   zac,kon, pos: word;
   begin
     pos:= 0; while get_ind(data,size,pos+1,odd,zac,kon) do inc(pos);
     get_str_items:= pos
   end;


function get_str_(data: pchars; size: word; pos: int; odd: TCharSet; var res: bool; max_size: int): string;
   var   zac,kon,dlz : word;
         dest : string;
   begin
     if get_ind(data,size, pos,odd, zac,kon) then
        begin
          dlz:= Minimum(kon-zac+1,sizeof(dest)-1);
          dest[0]:= chr(dlz);
          move(data^[zac],dest[1], dlz)
        end
     else dest:= '';
     res:= dest<>'';
     if max_size<0 then max_size:= 0;
     dest:= copy(dest,1,minimum(length(dest),max_size{-1}));
     get_str_:= dest
   end;

function get_str(data: pchars; size: word; pos: int; odd: TCharSet; max_size: int): string;
   var   res : bool;
         s   : string;
   begin
     s:= get_str_(data,size, pos,odd, res, max_size);
     if res then get_str:= s else get_str:= ''
   end;

function get_str0_(data: pchars; size: word; pos: int; odd: TCharSet; var res: bool): pchar;
   var   zac,kon : word;
         dest    : pchar;
   begin
     if get_ind(data,size, pos,odd, zac,kon) then
        begin
          GetMem(dest,kon-zac+1+1);
          move(data^[zac],dest[0], kon-zac+1);
          dest[kon-zac+1]:= NULL
        end
     else dest:= nil;
     res:= dest<>nil;
     get_str0_:= dest
   end;

function get_str0(data: pchars; size: word; pos: int; odd: TCharSet): pchar;
   var   res: bool;
   begin
     get_str0:= get_str0_(data,size, pos,odd, res)
   end;


function get_strs0(data: pchars; size: word; prvy,posledny: int; odd: TCharSet): pchar;
   var   zac0,kon0,zac1,kon1 : word;
         dest : pchar;
   begin
     dest:= nil;
     posledny:= minimum(posledny, get_str_items(data,size,odd));
     if (    get_ind(data,size, prvy,odd, zac0,kon0)
         and get_ind(data,size, posledny,odd, zac1,kon1)
        ) then
        begin
          GetMem(dest,kon1-zac0+1+1);
          move(data^[zac0],dest[0], kon1-zac0+1);
          dest[kon1-zac0+1]:= NULL
        end;
     get_strs0:= dest
   end;

function get_strs0p (data: pchars; size: word; prvy,posledny: int; odd: TCharSet): string;
   var   p: pchar;
   begin
     p:= get_strs0 (data,size, prvy,posledny, odd);
     get_strs0p:= strpas(p);
     strdispose(p)
   end;
