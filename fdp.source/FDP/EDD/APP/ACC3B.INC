{
  odalokuje pole lstACC
}
procedure TwinACC.zrus_zoznamy;
    var   i,j: int;
    begin
      TObject.Done;
      for i:= 0 to stlpcov-1 do
          for j:= 0 to max_skupin-1 do
              if Tablet[i,j]<>nil then
                 begin
                   {Dispose(Tablet[i,j],Done); -> urobiu to uz TObject.Done}
                   Tablet[i,j]:= nil
                 end
    end;

{
  kontrola spravnosti
}
function TwinACC.is_poloha(stl,ind: int): bool;
   begin
     is_poloha:= (stl>=0) and (stl<stlpcov) and (ind>=0) and (ind<max_skupin)
   end;

function TwinACC.is_active(stl,ind: int): bool;
   begin
     is_active:= (Tablet[stl,ind]<>nil) and (Tablet[stl,ind]^.visible)
    {is_active:= (Tablet[stl,ind]<>nil) and (TABLET_NULL or (Tablet[stl,ind]^.top>=0))}
   end;


{ najde stl a ind pre NDB na tabuli
}

 function TwinACC.najdi_skupinu(NDB: string; var stl,ind: int): bool;
    begin
      najdi_skupinu:= true;
      stl:= 0; ind:= 0;
      while (stl<stlpcov) do
        begin
          ind:= 0;
          while (ind<max_skupin) do 
            if Tablet[stl,ind]^.popis.NDB=NDB then Exit
            else inc(ind);
          inc(stl)
        end;
      najdi_skupinu:= false;
    end;


 function TwinACC.patri_do_zoznamu(NDB: string; stl,ind: int): bool;

    var    Bn,Bi : TOBxy;
           isBn  : bool;
           bres  : bool;

    function is_OB_EQ(kod: string): bool;
       begin
         bres:=     (kod<>'')
                and (   is_NDB_eq(NDB,kod)
                     or (    (NDB_XY)
                         and (    isBn
                              and get_OB_XYM(kod,Bi)
                              and (Bn.x=Bi.x)
                              and (Bn.y=Bi.y)
                             )
                        )
                    )
             ;
         is_OB_EQ:= bres
       end;

    function _patri_do_zoznamu: bool;
       var   i : int;
             s : string;
             p1,p2 : pchar;
             res : bool;
       begin
         _patri_do_zoznamu:= false;
         if (Tablet[stl,ind]^.popis.NDBs=nil) then Exit;

         p1:= Tablet[stl,ind]^.popis.NDBs;
         repeat
           if p1=nil then break;
           while (p1<>nil) and (p1[0]=icao_NXIT) do inc(p1,1);
           if p1<>nil then p2:= strpos(p1,icao_NXIT)
           else p2:= nil;
           if p2<>nil then s:= init_str(pchars(p1),p2-p1)
           else s:= strpas(p1);
           res:= is_OB_EQ(s);
           p1:= p2;
         until (p1=nil) or (res);

         _patri_do_zoznamu:= res
       end;

    begin
      isBn:= get_OB_XY(NDB,Bn);
      patri_do_zoznamu:=     (Tablet[stl,ind]<>nil)
                         and (   {is_OB_EQ(Tablet[stl,ind]^.popis.NDB)
                              or}  _patri_do_zoznamu
                             )
    end;


 function TwinACC.najdi_zoznam(NDB: string; var stl,ind: int): bool;
    begin
      najdi_zoznam:= true;
      stl:= 0; ind:= 0;
      if najdi_skupinu(NDB, stl,ind) then Exit;
      stl:= 0; ind:= 0;
      while (stl<stlpcov) do
        begin
          ind:= 0;
          while (ind<max_skupin) do
            begin
              if patri_do_zoznamu(NDB, stl,ind) then Exit;
              inc(ind)
            end;
          inc(stl)
        end;
       najdi_zoznam:= false
    end;


{
  najde stl a ind pre NDB na tabuli
}
function TwinACC.najdi_polohu(p: PlstACC; var stl,ind: int): bool;
   begin
     najdi_polohu:= false;
     stl:= 0; ind:= 0;
     while (stl<stlpcov) do
       begin
         ind:= 0;
         while (ind<max_skupin) do
           begin
             if (p<>nil) and (p=Tablet[stl,ind]) then  { p<>nil .... nova podmienka }
                begin
                  najdi_polohu:= true;
                  Exit
                end;
             inc(ind)
           end;
         inc(stl)
       end
   end;


function TwinACC.najdi_posledny_zoznam(stl: int): PlstACC;
   var   i: int;
   begin
     i:= max_skupin-1;
     while (i>=0) and (Tablet[stl,i]=nil) do dec(i);
     if i<0 then najdi_posledny_zoznam:= nil
     else najdi_posledny_zoznam:= Tablet[stl,i]
   end;


function TwinACC.najdi_najvacsi_zoznam(stl,ind: int; var ind_i: int): bool;
  var    i, max, pocet_i : int;
  begin
   { ak nie: najdi odzhora riadok s najvacsim poctom riadkov:
     nesmie to byt "p" a hi-lo>0 a zmensi jeho rozsah (i 2x (o))
   }
     max:= 0; ind_i:= -1;
     for i:= max_skupin-1 downto 0 do
       if (Tablet[stl,i]<>nil) then
          begin
            pocet_i:= Tablet[stl,i]^.sk_riadkov;
            if pocet_i>max then begin max:= pocet_i; ind_i:= i end
          end;
     if    (ind_i=-1)   { ziadny }
        or (ind_i=ind)  { ten isty }
        or (max<=2)     { minimalna velkost }
           then najdi_najvacsi_zoznam:= false
     else begin
            najdi_najvacsi_zoznam:= true;
            ind:= ind_i
          end
   end;


{
  najde stl a ind, kde je evidovany _iFPL^[_ind]
}
function TwinACC.najdi_zoznam_s_planom(_iFPL: PSTRIP; _ind: int; var stl,ind: int): bool;
   begin
     stl:= 0; ind:= 0;
     while (stl<stlpcov) do
       begin
         ind:= 0;
         while (ind<max_skupin) do
           begin
             if (Tablet[stl,ind]<>nil) and (Tablet[stl,ind]^.find(_iFPL,_ind)<>-1) then
                begin
                  najdi_zoznam_s_planom:= true;
                  Exit
                end;
             inc(ind)
           end;
         inc(stl)
       end;
     najdi_zoznam_s_planom:= false
   end;

{
  sprava od TFPL o ADD,CHG,CNL
}
procedure TwinACC.decode_mail__iFPL_ind(var _Event: TEvent; var iFPL: PSTRIP; var ind: int);
   var    p: pointer;
   begin
     with _Event do p:= Box;
     move(p^,iFPL,sizeof(PSTRIP)); incptr(p,sizeof(PSTRIP));
     move(p^,ind,sizeof(int));
     ClearEvent(_Event)
   end;


function TwinACC.riadkov(stl, od_,do_: int): int;
   var   ind, pocet: int;
   begin
     pocet:= 0;
     for ind:= maximum(0,od_) to minimum(do_,max_skupin-1) do
         if is_active(stl,ind) then pocet:= pocet + Tablet[stl,ind]^.sk_riadkov;
     riadkov:= pocet
   end;
