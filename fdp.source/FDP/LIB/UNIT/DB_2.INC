{
‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹
€                        €
€ Funkcie pre pracu s DB €
€‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹€
}

{ --------------------------
   vyhladanie polozky v DB,    pri neuspechu vrati -1
  --------------------------}

function DB_prehladaj({ a) funkcia pre spracovanie polozky DBF }
                           Bfunc_p2    : pointer;    { func(param_item,data_item: pointer): bool }
                           param_item  : pointer;    { ukazovatel na hladanu polozku alebo filter }
                           data_item   : pointer;    { ukazovatel na polozku typu pola ako - funkcia buffera }
                           disp_item   : pointer;    { Tproc_p odalokuje nacitany buffer }
                      { b) parametre pre DBF  }
                           FN          : string;
                           riadkov     : byte;
                           DATAdecode  : pointer;
                           KEYcode     : pointer;
                           RWClose     : bool;       { urcuje, ci otvori a zatvori DB po kazdom pristupe }
                           title       : string
                     ): long;

   var   DB      : PDB;
         res,pos : long;
         RAM_FN  : string;

   label X;

   begin
     m_set_shape(HODINY);
     res:= -1;

     if (BFunc_p2=nil) then
        begin
          if data_item<>nil then res:= DB_najdi(data_item,fn,riadkov,DATAdecode,KEYcode,false,disp_item,'');
          goto X
        end;

     if __INFO_DB or (title<>'') then
        begin
          if title='' then title:= msgSEARCH+': '+fn;
          InfoCakaj(msgWAITING,title+'...');
        end;
     RAM_FN:= FN; {copy_to_RAM(FN);}

     DB:= New(PDB,Init(RAM_FN{_FN},RWClose,riadkov,nil,DATAdecode,nil,nil, 0));

     pos:= 0;
     while (res=-1) and (pos<DB^.poloziek) do
       begin
         if DB^.citaj(pos,data_item) then
            begin
              m_restore_shape;
              if TBFunc_p2(BFunc_p2)(param_item, data_item) then res:= pos;
              m_set_shape(HODINY);
              if disp_item<>nil then Tproc_p(disp_item)(data_item)
            end;
         inc(pos);
         m_restore_shape;
         if DB^.RWClose then CheckProcesses else CheckProcesses0;
         m_set_shape(HODINY)
       end;

     Dispose(DB,Done);
     {del_from_RAM(RAM_FN);}
     if __INFO_DB or (title<>'') then InfoCakaj_zatvor;
     X: DB_prehladaj:= res;
     m_restore_shape
   end;



{ --------------------------
   alokacia pola pre DB
  --------------------------}

procedure new_DBarray (pole_adr  : pointer;  { adresa adresy pola <> nil }
                       var max_pole : int;   { maximum overdrive }
                       size_item : word      { velkost polozky }
                      );
    begin
      max_pole:= Minimum(max_pole, Minimum(MAX_ARRAY_SIZE,MaxAvail) div Maximum(1,size_item));
      GetMem(pointer(pole_adr^),max_pole*size_item);
    end;


procedure dispose_DBarray (pole_adr  : pointer;  { adresa adresy pola <> nil }
                           max_pole  : int;      { maximum overdrive }
                           size_item : word      { velkost polozky }
                          );
    begin
      FreeMem(pointer(pole_adr^),max_pole*size_item);
      pointer(pole_adr^):= nil
    end;



{ --------------------------
   nacitanie poloziek DB
  --------------------------}

{
  nacitanie a pripadna alokacia (new_item) dat DBF do pola DBF;
  alokujem cez new/dispose _item, lebo moze to by aj pole smernikov
}

function get_item(DB          : PDB;
                  pos         : int;      { index polozky na precitanie }
                  var pocet   : int;      { citac nacitanych poloziek    }

                  pole_adr    : pointer;  { adresa adresy pola <> nil }
                  top_adr     : pointer;  { adresa ukazovatela na vrchol <> nil }

                  data_item   : pointer;  { ukazovatel na polozku typu pola ako - funkcia buffera }
                  disp_item   : pointer;  { Tproc_p odalokuje nacitany buffer }

                  data_filter : pointer;  { ukazovatel na podmienku           }
                  filter      : pointer;  { TBfunc_p2: premenna, podmienky    }

                  add_item    : pointer   { Tproc_p3l alokacia, moze byt nil  }
                 ): bool;
   var   r: bool;
   begin
     r:= DB^.citaj(pos, data_item);
     if r and (filter<>nil) then
        if not Tfilter_items_DB(filter)(data_item,data_filter) then
           begin
             if disp_item<>nil then Tproc_p(disp_item)(data_item);
             get_item:= false;
             exit
           end;
     inc(pocet);
     if r then Tproc_p3l(add_item)(data_item, pointer(pole_adr^),top_adr, pos);
     { mohlo by byt radsej: if TBFunc then inc top_adr^ }
     get_item:= true
   end;


procedure new_DBitems ({ a) parametre pre pole }
                            pole_adr    : pointer;  { adresa adresy pola <> nil }
                            top_adr     : pointer;  { adresa ukazovatela na vrchol <> nil }
                            top_init    : int;      { -1, inak mozem spajat viacvero poli do seba }
                            max_pole    : word;

                            data_item   : pointer;  { ukazovatel na polozku typu pola ako - funkcia buffera }
                            disp_item   : pointer;  { Tproc_p odalokuje nacitany buffer }

                            data_filter : pointer;  { ukazovatel na podmienku           }
                            filter      : pointer;  { TBfunc_p2: premenna, podmienky    }

                            add_item    : pointer;  { Tproc_p3l alokacia, moze byt nil  }
                            vzostupne   : bool;     { smer nacitavania : true=vzostupne }

                       { b) parametre pre DBF  }
                            FN          : string;
                            riadkov     : byte;
                            DATAdecode  : pointer
                      );
    var   DB     : PDB;
          RAM_FN : string;
          pos, pocet: int;
    label X;
    begin

      int(top_adr^):= top_init; { -1 standartne }
      if (DATAdecode=nil) or (data_item=nil) or (add_item=nil) then exit;

      if __INFO_DB then InfoCakaj(msgWAITING,msgREAD+FN+'.');
      RAM_FN:= FN;  {copy_to_RAM(FN); skopirovanie na RAMdisk, ak je a je dost miesta }
      DB:= New(PDB,Init(RAM_FN,true, riadkov,nil,DATAdecode,nil,nil, 0));

      pocet:= 0;
      if vzostupne then
         begin
           pos:= 0;
           while (pocet<max_pole) and (pos<DB^.poloziek) do
              begin
                get_item(DB, pos, pocet,
                         pole_adr, top_adr, data_item, disp_item,
                         data_filter, filter, add_item
                        );
                inc(pos);
                if DB^.RWClose then CheckProcesses else CheckProcesses0
              end;
         end
      else begin
             pos:= DB^.poloziek-1;
             while (pocet<max_pole) and (pos>=0) do
                begin
                  get_item(DB, pos, pocet,
                           pole_adr, top_adr, data_item, disp_item,
                           data_filter, filter, add_item
                          );
                  dec(pos);
                  if DB^.RWClose then CheckProcesses else CheckProcesses0
                end;
           end;

      Dispose(DB,Done);
      {del_from_RAM(RAM_FN);}
      if __INFO_DB then InfoCakaj_zatvor
    end;


procedure dispose_DBitems (pole_adr  : pointer;  { adresa adresy pola <> nil }
                           top_adr   : pointer;  { pocet naplnenych poloziek-1 }
                           del_item  : pointer   { Tproc_pl dealokacia, moze byt nil }
                          );
    var   i: int;
    begin
      if (del_item<>nil) then for i:= int(top_adr^) downto 0 do Tproc_pl(del_item)(pointer(pole_adr^), i);
      int(top_adr^):= -1
    end;



{ --------------------------
   cykly nad DB
  --------------------------}

{ Urobi DFunc_p a nahraje polozku pre kazdu polozku,
  pokial DFunc_p nevrati do_item_BREAK.
  Ak prebehne vsetky polozky, vrati true.
}
function do_items_DB ({ a) funkcia pre spracovanie polozky DBF }
                           ByFunc_p2   : pointer;    { TByFunc_p2 <> nil   }
                           param       : pointer;
                      { b) parametre pre polozku }
                           data_item   : pointer;    { ukazovatel na polozku typu pola ako - funkcia buffera }
                           disp_item   : pointer;    { Tproc_p odalokuje nacitany buffer }
                      { c) parametre pre DBF  }
                           FN          : string;     { vrati nazov subora }
                           riadkov     : byte;
                           DATAcode    : pointer;
                           DATAdecode  : pointer;
                           KEYcode     : pointer;
                           DBchg       : pointer
                     ): bool;
   var   DB  : PDB;
         pos : long;
         res : byte;
         save: bool;
   begin
     do_items_DB:= false;
     if (ByFunc_p2=nil) then Exit;
    {m_set_shape(HODINY);}
     DB:= New(PDB,Init(FN, true, riadkov, DATAcode,DATAdecode,KEYcode, DBchg, 0));
     pos:= 0;
     while pos<DB^.poloziek do
        begin
          if DB^.citaj(pos,data_item) then
             begin
              {m_restore_shape;}
               res:= TByFunc_p2(ByFunc_p2)(data_item,param);
              {m_set_shape(HODINY);}
               if (res and do_item__SAVE)<>0 then DB^.zapis(data_item,pos,false);
               if disp_item<>nil then Tproc_p(disp_item)(data_item);
               if (res and do_item__NEXT)=0 then Break
             end;
          inc(pos);
         {m_restore_shape;}
          if DB^.RWClose then CheckProcesses else CheckProcesses0;
         {m_set_shape(HODINY)}
        end;
     Dispose(DB,Done);
     do_items_DB:= true;
    {m_restore_shape}
   end;

