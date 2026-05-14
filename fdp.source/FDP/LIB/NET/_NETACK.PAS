(*-------------------------------------------------------------------*)
(* LETVIS FDP - ack 2.0                                              *)
(* (c) Ales Kosice 1995  (ab)                                        *)
(*-------------------------------------------------------------------*)
{$I comp.h}
{$I comp_net.h}

{ DEFINE NET_ack_ADR} { prerobit adr na typ pchar }
{ Pokec dole }

unit _NETack;


interface

   uses  TypeDef,
         Arrays, AStream,
         NET_def;


   const max_NETack = {$IFDEF SERVER} 1000 {$ELSE} 500 {$ENDIF};
         NODE_DELETE_ALL_NETack : bool = false;

   type  PProc_node_off = ^TProc_node_off;
         TProc_node_off = procedure (nd: int; _node_off: bool; id: PNETpkt_head);

   type  PNETack = ^TNETack;
         TNETack = record
           nd   : int;           { cislo uzla v poli NODEs  } {$IFDEF NET_ack_ADR} adr: TNETadr; {$ENDIF}

           key  : pchar;         { kluc pre identifikaciu odoslanych dat }
           head : TNETpkt_head;  { kluc pre identifikaciu paketu }
           id   : PNETpkt_head;  { kluc pre identifikaciu distribucie paketu }

           pkt  : TNETpkt_data;  { vyrovnavacia pamat pre spracovanie potvrdeni... }
           tick : long;          { informacia pre urcenie timeout-u }
           {rec : bool;           bool uz potvrdeny ? }
         end;

         TNETack_buff = array[0..max_PTRs-1] of PNETack;
         PNETack_buff = ^TNETack_buff;

   procedure  new_ack  (ack1, ack2: PNETack); far;
   procedure  disp_ack (ack: PNETack); far;
   function   eq_ack   (ack1, ack2: PNETack): bool; far;


   type  PONETack = ^TONETack;
         TONETack = object(TDynamic2)

           buff : PNETack_buff;
           sec  : byte;                    { posledna sekunda na kontroly timeoutu  }
           p_node_off : PProc_node_off;    { -> cislo uzla, ktory je out  }

          public
           constructor Init (_p_node_off: PProc_node_off);

           function    add_pkt_ack (const pkt: TNETpkt; key: string; id: PNETpkt_head): PNETack;
           procedure   del_pkt_ack (const pkt: TNETpkt; is_key,is_ind: bool);

           procedure   check;

           function    get_ack_pkt (const pkt: TNETpkt): PNETack;
           function    get_ack_key (const pkt: TNETpkt): string;

           function    is_ack      (ack: PNETack): bool;
           function    is_for_ack  (nd: int; key: string): bool;

          private
           function    find_pkt_ack (const pkt: TNETpkt; is_key,is_ind: bool): int;
           procedure   ack_time_out (i: int);
         end;


implementation

uses  BIOS, _Check, mem, io, str0, math,
      Kody,
      App, Archiv;


{ totozne hlavne parametre paketu,a lebo skupiny paketov jednej spravy ?
}
 function eq_pkt_id (ack1, ack2: PNETack): bool;
    begin
      eq_pkt_id:=     (ack1^.nd        = ack2^.nd)  {$IFDEF NET_ack_ADR} and (ack1^.adr  = ack2^.adr) {$ENDIF}
                  and (ack1^.head.typ  = ack2^.head.typ)
                  and (ack1^.head.cis  = ack2^.head.cis)
                  and (strcomp(ack1^.key,ack2^.key)=0)
    end;

{ totozne vsetkie parametre paketu ?
}
 function eq_ack(ack1, ack2: PNETack): bool;
    begin
      eq_ack:=      (eq_pkt_id (ack1, ack2))
                and (ack1^.head.ind = ack2^.head.ind)
                and (ack1^.head.poc = ack2^.head.poc)
                and (ack1^.tick     = ack2^.tick)
    end;


 procedure new_ack(ack1, ack2: PNETack);
     begin
       FillChar(ack2^,SizeOf(ack2^),0);
       if ack1<>nil then
          begin
            ack2^:= ack1^;
            if (ack1^.id<>nil) then
               begin
                 getmem(ack2^.id,sizeof(ack1^.id^));
                 ack2^.id^:= ack1^.id^;
               end;
            ack2^.key:= StrNew(ack1^.key)
          end;
       fillchar(ack2^.pkt,sizeof(ack2^.pkt),0)
     end;

 procedure disp_ack(ack: PNETack);
     begin
       strdispose(ack^.key);
       if ack^.id<>nil then freemem(ack^.id,sizeof(ack^.id^));
       disp_NETpkt_pkt(ack^.pkt)
     end;


{ -------------------------
   Object of NETack
  -------------------------
}
 constructor TONETack.Init(_p_node_off: PProc_node_off);
       begin
         inherited Init(max_NETack,SizeOf(TNETack), nil,nil,@disp_ack);
         p_node_off:= _p_node_off;
         buff:= arr;
         sec:= 60
       end;


{ Hlada potvrdenie pre danu spravu
}
 function  TONETack.find_pkt_ack(const pkt: TNETpkt; is_key,is_ind: bool): int;
    var    nd,i : int;
           adr  : TNETadr;
           key  : string;
    begin
      find_pkt_ack:= -1;
      adr:= uni_str(pkt.ods);
      nd:= is_NETadr(adr);
      if nd<0 then Exit;

      if is_key then
         begin
           key[0]:= chr(minimum(pkt.pkt.dlz,sizeof(string)-2));
           move(pkt.pkt.data^,key[1],ord(key[0]));
           key:= key+#0
         end
      else key:= NULL;

      i:= 0;
      while
            (i<=top)
        and (not (    (buff^[i]^.nd = nd) {$IFDEF NET_ack_ADR} and (buff^[i]^.adr=adr) {$ENDIF}
                  and (buff^[i]^.head.typ+1 = pkt.head.typ)
                  and (buff^[i]^.head.cis   = pkt.head.cis)
                  and ((not is_ind) or ((buff^[i]^.head.ind = pkt.head.ind) and (buff^[i]^.head.cis = pkt.head.cis)))
                  and ((key=NULL) or (strcomp(buff^[i]^.key,@key[1])=0))
                 )
            )
      do inc(i);
      if i>top then i:= -1;

      find_pkt_ack:= i
    end;


{ zaradenie ocakavaneho potvrdenia paketu
}
 function  TONETack.add_pkt_ack (const pkt: TNETpkt; key: string; id: PNETpkt_head): PNETack;
     var   ack  : TNETack;
           i,nd : int;
     begin
       add_pkt_ack:= nil;
       nd:= is_NETadr(pkt.adr);
       if (nd<0) or (MaxAvail<=MIN_NET_HEAP_SIZE) then Exit;

       fillchar(ack,sizeof(ack),0);

       ack.nd   := nd; {$IFDEF NET_ack_ADR} ack.adr := uni_str(pkt.adr); {$ENDIF}
       ack.key  := strpasnew(key); { nemusim odalokovat, adresu prevezme buff, neinicializoval som @new_ack }
       ack.head := pkt.head;
       if id<>nil then
          begin
            getmem(ack.id,sizeof(id^));
            ack.id^:= id^;
          end;

       fillchar(ack.pkt,sizeof(ack.pkt),0); { dolezite }
       if (ack.head.poc>0) then
          begin
          { Do EMS pamate sa skopiruje cely paket, ktory ma byt odoslany,
            aby mohli byt postupne odoslane vsetky jeho casti.
            Cela datova struktura je ulozena v "buff" alebo v "data"...s
          }
            if (pkt.pkt.bufe<>nil) and (pkt.pkt.bufe^.is) then
               begin
                 ack.pkt.bufe:= New(PstreamBuffer,Init(1,pkt.pkt.bufe^.getsize));
                 if ack.pkt.bufe^.is then
                    begin
                      pkt.pkt.bufe^.seek(0);
                      ack.pkt.bufe^.seek(0);
                      ack.pkt.bufe^.CopyFrom (pkt.pkt.bufe^,pkt.pkt.bufe^.getsize)
                    end
                 else begin
                        disp_NETpkt_pkt (ack.pkt);
                        if pkt.pkt.bufe^.getsize<MIN_NET_HEAP_SIZE then
                           pkt.pkt.bufe^.read_buffer (ack.pkt.data,ack.pkt.dlz,false)
                      end
               end
            else begin
                   ack.pkt.bufe:= New(PstreamBuffer,Init(1,pkt.pkt.dlz));
                   if ack.pkt.bufe^.is then
                      begin
                        ack.pkt.bufe^.seek(0);
                        ack.pkt.bufe^.add_to_buffer(pkt.pkt.data^,pkt.pkt.dlz)
                      end
                   else begin
                          disp_NETpkt_pkt (ack.pkt);
                          if pkt.pkt.dlz<MIN_NET_HEAP_SIZE then
                             new_NETpkt_data (pkt.pkt.data,pkt.pkt.dlz,ack.pkt)
                        end
                 end
          end;

       ack.tick := getticks;
       {ack.rec := false;}

       i:= Add(@ack);
       if i=-1 then
          begin
 {[!]}      Del(0);      { Time_out_node(0); -> mohol by vyvolat retazovu reakciu }
            i:= Add(@ack)
          end;

       add_pkt_ack:= buff^[i];
       Diagnose
     end;


{ zrusenie ocakavaneho potvrdenia paketu
}
 procedure TONETack.del_pkt_ack(const pkt: TNETpkt; is_key,is_ind: bool);
     var   nd, i : int;
     begin
       nd:= is_NETadr(pkt.ods);
       if nd<0 then Exit;

       repeat
         i:= find_pkt_ack(pkt,true,is_ind);
         if i>-1 then Del(i)
       until i<=-1;
       Diagnose
     end;


{ Ocakava sa este potvrdenie ?
}
 function  TONETack.is_ack(ack: PNETack): bool;
    var    i : int;
    begin
      i:= 0;
      while (i<=top) and (not eq_ack(buff^[i],ack)) do inc(i); { Neporovnavam comp compstr }
      is_ack:= i<=top
    end;


{ Ocakava sa potvrdenie na data klucovane "_key" ?
  Co ak sa v ktratkom case zmeni obsah dat ? ha ? Pouzivat len pri inicializaci
}
 function  TONETack.is_for_ack(nd: int; key: string): bool;
    var    i : int;
    begin
      i:= 0;
      while (i<=top) and ((buff^[i]^.nd<>nd) or (strpas(buff^[i]^.key)<>key)) do inc(i);
      is_for_ack:= i<=top
    end;


 function  TONETack.get_ack_pkt(const pkt: TNETpkt): PNETack;
    var    i : int;
    begin
      i:= find_pkt_ack(pkt,false,true);          { is_ind }
      if i>-1 then get_ack_pkt:= buff^[i]
      else get_ack_pkt:= nil
    end;

{ vyhladanie kluca pre vyhladanie dat podla odpamatanych
  parametrov odoslaneho paketu
}
 function  TONETack.get_ack_key(const pkt: TNETpkt): string;
    var    i : int;
    begin
      i:= find_pkt_ack(pkt,false,false);
      if (i>-1) and (buff^[i]^.key<>nil) then get_ack_key:= strpas(buff^[i]^.key)
      else get_ack_key:= ''
    end;


{ pri inicializacii uzla sa caka na potvrdenie,
  tym nenarastie pocet ocakavanych potvrdeni,
  na ktore sa caka...
}
 procedure TONETack.ack_time_out(i: int);
     var   nd   : int;
           id   : PNETpkt_head;
     begin
       nd:= buff^[i]^.nd; { ! nepamatam si premenne pchar }
       id:= buff^[i]^.id;
       buff^[i]^.id:= nil;
       Del(i);
       if nd>=0 then
          begin
            {if NODE_DELETE_ALL_NETack then
               begin
                 i:= 0;
                 while i<=top do
                   if (buff^[i]^.nd=nd) then Del(i)
                   else inc(i)
               end;}
            if p_node_off<>nil then
               begin
                 TProc_node_off(p_node_off)(nd,false,id);
               end;
            NODEs^[nd].stat.NodeInit:= true
          end;
       if id<>nil then freemem(id,sizeof(id^));
     end;

 procedure TONETack.check;
     var   i : int;
           s : string;
     begin
       if sec=BIOS.sec then Exit;
       sec:= BIOS.sec;

       i:= 0;
       while (i<=top) do
         begin
           if {(not buff^[i]^.rec) and} TimeOut(buff^[i]^.tick, getticks, time_out_nd(buff^[i]^.nd)) then
              begin
                if NODEs^[i].stat.InitEn then
                   begin
                    {$IFDEF DOCUMENT_NET}
                     s:=   NODEs^[buff^[i]^.nd].desc.adr+' - TIME OUT'+
                         + ' (' + cstr(buff^[i]^.head.typ,1)
                         + ', ' + cstr(buff^[i]^.head.cis,1)
                         + ', ' + cstr(buff^[i]^.head.ind,1)
                         + ', (' + StrPas(buff^[i]^.key)
                         + '), ' + cstr(GetTicks,1) + ' ' + cstr(buff^[i]^.tick,1)
                         +   ')';
                     {$IFDEF WRITELN_NET}
                       if writeln_NET_REC then MainApp^.writeln_(@s[1],length(s),cl_NODE_OFF,arch_MESS,true,false);
                     {$ENDIF}
                     {$IFDEF ARCHIVE_NET}
                       if archive_NET_REC then
                          archivuj_data(path_NET, get_ARCHfn(0)+'.'+extNET,@s[1],length(s),arch_SYS,true,false);
                     {$ENDIF}
                    {$ENDIF}
                   end;

                ack_time_out(i);

                if NODE_DELETE_ALL_NETack then break
              end
           else inc(i)
         end
     end;

end.

{
  Modul pre zabezpecenie udrzania informacie o stave pripojenych uzlov:

  Vacsina sprav by mala by potvrdenych. Ak nechcem cakat v slucke na
  ack, musim po odoslani pustit program dalej, a pamatat, si cas
  "o kolko" SendTick som odoslal pkt. Ak vyprsi TimeOut na ack, sprava
  nebola potvrdena, zrusim stav TrasaOK a vyhlasim testovanie.

  Ale ak by sm medzitym poslal dalsiu spravu, SendTick sa mi posunie
  a nedorucenie predcadzajucej spravy uz nezistim. Preto si musim pamatat
  vsetky odoslane spravy do limitu TimeOut pre kazdu a mat sposob, ktorym
  detekujem, ze potvrdenie patri tejto sprave :

            uzol(adresa) stanice
            typ spravy
            kod + cislo spravy
            index + z poctu sprav
            odoslana o ticks
            a kluc.

  Poznamka:

   - Adresy, ktore nie su v user.ini sa nevyhodnocuju...
     (Zatial netreba. Direktiva DEFINE NET_ack_ADR)

   - [!] Krizovou je velkost buffera a ack_TIME_OUT. Ak je zaplneny,
     tak sa zrusi najstarsia sprava, a ta nebude opat vysielana,
     pretoze sa to nevyhodnoti.

   - Main testuje timeouty. V pripade vyprsania moze volat proceduru
     pre opatovne vyslanie paketu, alebo vyhlasi preusenie spojenia.

   - V pripade, ze uzol ma priznak nd_Wack, nekoduje sa kluc a caka sa
     na potvrdenie.

   - Pri inicializacii sa caka na potvrdenie, tym nenarastie
     pocet potvtrdeni, na ktore sa caka...
}

{procedure updata_ack(var ack: TNETack; ind: TNETind; tick: long;       { informacia pre urcenie timeout-u }

           {typ  : TNETtyp;
           cis  : TNETcis;
           ind  : TNETind;
           poc  : TNETpoc;}

{ vrati data paketu odlozene v EMS pamati kvoli
  rychlejsiemu vyhladaniu a odoslaniu

function  TONETack.get_ack_data (const pkt: TNETpkt; key: string): pchar;
   var    i : int; data: pchars; dlz: word;
   begin
     data:= nil;
     i:= find_pkt_ack(pkt,false,false);
     if (i>-1) and (buff^[i]^.buff<>nil) then buff^[i]^.buff^.read_buffer (data,dlz,true);
     get_ack_data:= pchar(data)
   end;
}
