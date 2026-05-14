constructor O_X25nodes.Init;
      begin
        inherited Init(maxX25_NODEs,sizeof(T_X25node));
        nodesX25  := -1; nodesX25_:= -1;
        X25node   := -1;
        X25bridge := -1;

        NODE := P_X25nodes(ap)
      end;


function O_X25nodes.Add (p: pointer): int;
   var   N : T_X25node;
         i : int;
   begin
     N:= T_X25node(p^);
     inherited Add(p);

     i:= 0; while (i<top) and (NODE^[i]^.LETVIS) do inc(i); { najde posledny LETVIS }
     if N.LETVIS then
        begin
        { Uzly ineho typu ako LETVIS su na konci zoznamu
        } if (i <= top-1) and (not NODE^[i]^.LETVIS) then
             begin
               N:= NODE^[i]^; NODE^[i]^:= NODE^[top]^; NODE^[top]^:= N
             end;
          nodesX25:= i + 1
        end;

     i:= 0;
     while     (i<=top)
           and (NODE^[i]^.ADR <>T_X25node(p^).ADR)
           and (NODE^[i]^.NAME<>T_X25node(p^).NAME)
     do inc(i);
     if i>top then i:= -1;
     nodesX25_:= top+1;
     Add:= i
   end;


function O_X25nodes.AddNode(UZOL,NAME,ADR: TX25name; PROL: bool; LETVIS: bool): int;
   var   N : T_X25node;
   begin
     FillChar(N,SizeOf(N),0);

     N.UZOL:= uni_str(UZOL);
     N.NAME:= uni_str(NAME);
     N.ADR := uni_str(DelChar(ADR,[' ','#']));

     N.LETVIS:= LETVIS;
     N.PROL:= PROL;

     AddNode:= Add(@N)
   end;


procedure O_X25nodes.read_cfg(var _err: bool);
   var   f : Text;
         s,t,n,a,c : string;
         i,p,y, uzlovX25 : int;
         b : bool;
   begin
     if Exists(X25cfg)<>0 then
        {$IFDEF X25} RunError('Can not read '+X25cfg+'.')
        {$ELSE}      Exit
        {$ENDIF};

     uzlovX25:= 0;
     Assign(f,X25cfg); Reset(f);

     Reset(f); i:= 0;
     while (not Eof(f)) and (i<maxX25_NODEs) do
       begin
         readln(f,s); s:= cut_(s);
         if (s='') or (s[1]=';') then continue;

        { vlastna adresa (moze byt len raz)
        }
         if pos(nd_THIS,s) > 0 then
            if X25node>-1 then RunError(X25cfg+' - another self address.')
            else X25node:= i;

        { adresa bridge (moze byt len raz)
        }
         if (pos(nd_BRIDGE,s)>0) then
            if X25bridge>-1 then RunError(X25cfg+' - another bridge.')
            else X25bridge:= i;

        { ...
        }
         n:= cut_(getstr(s,1,[';']));
         t:= getstr(s,2,[';']);
         a:= uni_str(getstr(t,1,[',']));
         c:= uni_str(getstr(t,2,[','])); {val(delchar(getstr(s,3,[';']),[' ','#']),p,y);}
         b:= uni_str(getstr(s,3,[';']))=pL;
         AddNode(n,a,c,b,true);
         inc(i)
       end;
     Close(f);
     i:= uzlovX25;
     if uzlovX25>maxX25_NODEs then
        MessError('To much Xú25 nodes in the '+X25cfg+'. Maximum is '+inttostr(maxX25_NODEs,1,1)+'.', true,_err);

     {$IFDEF X25}
      if X25node=-1 then RunError(X25cfg+' - Missing self address.')
      else X25address:= X25nodes^.NODE^[X25node]^.NAME
     {$ENDIF}
   end; { read_cfg }

{
  Kontroluje, ci pseudoadresa "x25_name" sa nachadza v zozname adries LETVISov X25.cfg.
  - ak je x25_name='', predpoklada "x25_name" je adresa v danom uzle
  - ak nie je, x25_name je po navrate naplnena vlastnou pseudoadresou
}
function O_X25nodes.isX25name(var X25name: TX25name): int;
   var   i: int;
   begin
     X25name:= cut_(X25name);
     if (X25name<>'') then
        begin
          if (top>-1 {X25nodes<>nil}) then
             begin
               i:= 0;
               while     (i<nodesX25)
                     and (    (X25name<>NODE^[i]^.NAME)
                          and (not eq_str(X25name,NODE^[i]^.UZOL))
                         )
               do inc(i);
               if i>=nodesX25 then i:= -1
               else X25name:= NODE^[i]^.NAME
             end
          else i:= -1;
          isX25name:= i
        end
     else begin
            {if (X25node>-1) and (top>-1) then X25name:= NODE^[X25node]^.NAME;}
            if (X25node>-1) and (X25node<=top {X25nodes<>nil}) then X25name:= NODE^[X25node]^.NAME;
            isX25name:= X25node
          end
   end; { isX25name }


function O_X25nodes.isX25adr(adr: TX25name; svc: byte): int;
   var   i,k: int;
   begin
     case svc of
       1    : begin i:= 0;           k:= nodesX25 end;
       2    : begin i:= N(nodesX25); k:= top + 1  end
       else   begin i:= 0;           k:= top + 1  end
     end;
     while (i<=top) and (i<k) and (NODE^[i]^.ADR <> adr) do inc(i);

     { ak adresa nebola identifikovana,
       ak je len jeden uzol OLDI uzol
       a je bez adresy (alebo s inou adresou),
       tisko predpokladame,
       ze je to on
     } if     ((i>=k) and (svc<>1) and (top=nodesX25+1))
          and ((not NODE^[top]^.LETVIS) {and (NODE^[top]^.adr='')})
              then i:= top;

     if i < k then isX25adr:= i
     else isX25adr:= -1
   end; { isX25adr }



function O_X25nodes.isX25chan(chan: U16BIT; svc: byte): int;
   var   i,k: int;
   begin
     case svc of
       1    : begin i:= 0;           k:= nodesX25 end;
       2    : begin i:= N(nodesX25); k:= top + 1  end
       else   begin i:= 0;           k:= top + 1  end
     end;
     while (i<=top) and (i<k) and (NODE^[i]^.CHAN<>chan) do inc(i);

     if (i < k) then isX25chan:= i
     else isX25chan:= -1
   end; { isX25chan }
