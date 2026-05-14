{
ÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜ
Û                                                          Û
Û TDynamic2                                                Û
ÛÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÛ
}

 constructor TDynamic2.Init(_items,_data_size: word;
                            _new_item,_format_item,_disp_item: pointer
                           );
       begin
         inherited Init(_items,_data_size);
         new_item:= _new_item;
         format_item:= _format_item;
         disp_item:= _disp_item;
         semaphor:= false
       end;


 function TDynamic2.NewData(p: pointer): pointer;
    var   _p: pointer;
    begin
      if (maxavail>data_size) then
         begin
           GetMem(_p,data_size); {FillChar(_p^,data_size,0); !@#$}
           if new_item<>nil then Tproc_p2(new_item)(p,_p)
           else Move(p^,_p^,data_size);
           format_data(_p)
         end
      else _p:= nil;
      NewData:= _p
    end;


 procedure TDynamic2.DispData(var p: pointer);
     begin
       if p<>nil then
          begin
            if disp_item<>nil then Tproc_p(disp_item)(p);
            FreeMem(p,data_size)
          end;
       p:= nil
     end;


 { nacitanie a pripadna alokacia (new_item) dat DBF do pola DBF;
   alokujem cez new/dispose _item, lebo moze to by aj pole smernikov
 }
 function TDynamic2.include_DBitem (data     : pointer;     { udaje }
                                    p_filter : pointer;     { zaznam s udajmi podmienok pre nacitanie }
                                    p_data   : PBFunc_p2    { kontrola pripustnosti nacitania }
                                   ): bool;
    begin
      include_DBitem:= (p_data=nil) or (p_filter=nil) or TBFunc_p2(p_data)(data,p_filter)
    end;


 procedure TDynamic2.read_DBitems (FN        : string;
                                   riadkov   : byte;
                                   p_decode  : pointer;

                                   p_filter : pointer;     { zaznam s udajmi podmienok pre nacitanie }
                                   p_kluc   : PBFunc_p2;   { porovnanie identifikacnych udajov }
                                   p_stav   : PBFunc_p2;   { porovnanie inych udajov }
                                   p_data   : PBFunc_p2;   { porovnanie dekodovanych udajov }

                                   vzostupne : bool        { smer nacitavania : true=vzostupne }
                                  );
     var   db   : PDB;
           data : pointer;
           pos,pocet,poloziek : int;
           kluc : string;
           p : pointer;

     procedure read_data;
        var    bres : bool;
               _top : int;
        begin
          fillchar(data^,data_size,0);

          if p_kluc<>nil then
             begin
               kluc:= db^.citaj_kluc(pos);
               bres:= TBFunc_p2(p_kluc)(@kluc[0],p_filter)
             end
          else bres:= true;
          if not bres then Exit;

          db^.citaj_vetu(pos);
          if p_stav<>nil then bres:= TBFunc_p2(p_stav)(@db^.buff^[1],p_filter);
          if not bres then Exit;

          db^.dekoduj_vetu(data);
          if p_data<>nil then bres:= TBFunc_p2(p_data)(data,p_filter);
          if not bres then
             begin
               if disp_item<>nil then Tproc_p(disp_item)(data);
               Exit
             end;

          _top:= top;
          Add(data);
          if _top>top then inc(pocet);
        end;

     begin
       if (p_decode=nil) then Exit;

       semaphor := true;
       if __INFO_DB then InfoCakaj('Info',msgREAD+FN+'.');
       GetMem(data,data_size);
       db:= New(PDB,Init(FN,false, riadkov,nil,p_decode,nil,nil,0));

       p:= new_item; new_item:= nil;
       poloziek:= db^.poloziek;
       pocet:= 0;

       if vzostupne then
          begin
            pos:= 0;
            while (pocet<items) and (pos<poloziek) do
              begin
                read_data;
                inc(pos);
                CheckProcesses0
              end
          end
       else begin
              pos:= poloziek-1;
              while (pocet<items) and (pos>=0) do
                begin
                  read_data;
                  dec(pos);
                  CheckProcesses0
                end
            end;

       new_item:= p;
       Dispose(db,Done);
       FreeMem(data,data_size);

       if __INFO_DB then InfoCakaj_zatvor;
       semaphor := false
     end;




 constructor TAPChar.Init(_items: word);
       begin
         inherited Init(_items,sizeof(pchar))
       end;

 function TAPchar.NewData (p: pointer): pointer;
    var   pch: pchar;
    begin
      pch:= StrNew(pchar(p));
      NewData:= pch
    end;

 procedure TAPchar.DispData (var p: pointer);
    begin
      StrDispose(pchar(p))
    end;

