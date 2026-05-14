 function O_AFTN.get_pkt_size(pkt: pointer): word;
    begin
      get_pkt_size:= TAFTNpkt(pkt^).p
    end;

 function O_AFTN.get_pkt_comprimed_size(pkt: pointer): word;
    var   p : PAFTNpkt;
    begin
      p:= pkt;
      get_pkt_comprimed_size:= sizeof(p^.p) + p^.p
    end;

 function O_AFTN.get_pkt_data(pkt: pointer): pointer;
    begin
      get_pkt_data:= @TAFTNpkt(pkt^).b
    end;


{ תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
   Identifikacia adresata :

   ZCZC VLA004 0016     Ù
   FF UKBBZUZXÙ
   FF UKOOZUZX UKKKZDZX UKFFZUZX UKBBZUZXÙ
   020012 LFPYZMFPÙ
   (FPL-DMO....../961202)
   ÙNNNN

   V hlavicke dat sa za znackou prednosti "SS"..."KK" nachadza adresat.

   Vyhladanie riadku, kde sa nachadzaju adresy prijemcov telegramu.
   V telegramoch archiv na UA je umiestnenena na druhom riadku.
   Predpoklad : nachadza sa na prvych troch riadkoch (velkost title).
}

 function O_AFTN.is_pkt_for_node(from: string; data: pchars; size: word): bool;
    var   s,adr : string;
          i,j,k, pi,pj,pk : int;
          bres : bool;
    begin
      is_pkt_for_node:= true;
      if (NODE_THIS='') or (ALIAS_NODE<>NODE_PROMISCUITE) then Exit;

      (*
      i:= 0; adr:= ''; p1:= get_str_items(data,size, setNL+setNL_);
      while (i<p1) and (adr='') do
        begin
        { najdenie riadku so zaciatkom spravy ZCZC (uz nie s priznakom priority)
          je prvy, ale mozno som schytal bordel...
        }
          inc(i); s:= get_str(data,size,i,setNL+setNL_, sizeof(s));
          if (pos(MTK_2_SOT,mtks_rus_to_lat(s))>0) and (i<p1) then
             begin
               adr:= get_str(data,size,i+1,setNL+setNL_, sizeof(s1));
               break
             end
        end;
      if (i>=p1) and (adr='') then
         begin
          { ­¥¯®«דח¨«®בל... }
           is_pkt_for_node:= false;
            Exit
         end;}
      *)

     { Prekontroluje vsetky riadky zacinajuce priznakom naliehavosti,
       ci tam nie je vlastna adresa
     }
      bres:= false;
      pi:= get_str_items(data,size, setNL+setNL_);
      i:= 1; s:= get_str(data,size,i,setNL+setNL_, sizeof(s)-1);
      while (not bres) and (i<=pi) and (is_mtkprty(s)<>'') do
        begin
         { musi sa porovnat kazda adresa zvlast, funkcia "pos" tu nemusi
           vratit jednoznacny vysledok.
         } j:= 1; pj:= getstritems(s,[icao_NXIT]);           { 1.adresa v zozname }
           while (not bres) and (j<=pj) do
             begin
               adr:= getstr(s,j,[icao_NXIT]);                { j.ta adresa }
               bres:= s=NODE_THIS;
               if not bres then
                  begin
                    k:= 2; pk:= getstritems(ALIAS_NODE,[icao_NXIT]);
                    while (not bres) and (k<=pk) do         { k-te alias meno }
                      begin
                        bres:= adr=getstr(ALIAS_NODE,k,[icao_NXIT]);
                        inc(k)
                      end
                    end;
                 inc(j)
             end;
           inc(i);
           s:= get_str(data,size,i,setNL+setNL_, sizeof(s)-1)
        end;

      is_pkt_for_node:= bres
    end;


{ תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
   Kontrola, ci to nie je paket "CH"...
   ‡–‡– †‹€314 2201     Ù
   –• ‹ ‹†€000Ù"
}

 function O_AFTN.is_system_pkt (data: pchars; size: word; res: string): bool;
    var   s : string;
    begin
      res:= '';
      s:= l4str(get_str(data,size,2,setNL+setNL_,sizeof(s)-1));
      is_system_pkt:= copy(s,1,length(MTK_2_CH))=MTK_2_CH
    end;

