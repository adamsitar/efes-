{
  Funkcia vytvori zasobnik s velkostou 2400 byte
  a vola externu funkciu pre spracovanie prerusenia od kernelu
}

{
  premenne pre asynch_stub - musia byt globalne
}

const as_stack_size = 1200;

var   as_stack    :
        record
          _stack  : array[0..as_stack_size] of word;  { velkost zasobnika pre aplikacnu rutinu }
          {_bstack : word;}
        end;
                            { segmenty v okamihu vyvolania prerusenia }
      save_ss     : word;
      save_sp     : word;

      as_handler  : long;


procedure asynch_stub; assembler;
   var    save_ds: word;
   asm
     mov  save_ds,ds

     mov  ax,SEG @Data
     mov  ds,ax
     mov  save_ss,ss
     mov  save_sp,sp

     cli
     mov  ax,SEG as_stack[as_stack_size]      { put the_label at the end because the stack }
     mov  ss,ax                               { SS:SP <- DS:as_stack }
     mov  sp,OFFSET as_stack[as_stack_size]   { grows downward }
     sti

     push bx                                  { nd       }
     push cx                                  { event    }
     push dx                                  { argument }
     push save_ds

     mov  [word ptr as_handler],di
     mov  [word ptr as_handler+2],es
     call dword ptr [as_handler]              { as_handler (int nd, int event, char far* arg)   }
                                              { vykona add sp,8, pretoze pozna pocet premennych }
     cli
     mov ss,save_ss                           { disable interrupts to make sure we don't get }
     mov sp,save_sp                           { invoked again while we stack hack            }
     sti

     mov ds,save_ds
   end;


procedure net_asynch_handler (nd: int; event: int; arg: pointer);
    begin
     {$IFDEF AS_PCTCP}
       if (UDP_buff=nil) then Exit;

       if (event=NET_AS_RCV) then with UDP_pkt^ do
          begin
            desc:= nd;
            size:= net_read(nd, data,sizeof(data), from, NET_FLG_NONBLOCKING);
            if (size>0) {and (neterrno=0)} then UDP_buff^.save(UDP_pkt)
          end
     {$ENDIF}
    end;

