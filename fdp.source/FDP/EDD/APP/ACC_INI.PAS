{$I comp.h}


unit ACC_ini;


interface


    uses  TypeDef,
          Ovr, DOS, IO, {$I unit_gr.h},
          Menus,
          Body, _FDP_def, _FPL_def;

    {$I acc0.h}    { stlpce }

    const {stl_strip1 = 1;}
          stl_strip2 = 2;
          stl_strip3 = 3;
          stl_strip4 = 4;

          odd_popis  = [' ',':',';',',','='];

    var   tab_strip2 : array[0..stl_strip2] of TpopisStlpec;
          tab_strip3 : array[0..stl_strip3] of TpopisStlpec;
          tab_strip4 : array[0..stl_strip4] of TpopisStlpec;

    const p_tab_stripi : array[low(T_strip)..high(T_strip)] of PpopisTablet =
                         (@tab_strip4,@tab_strip3,@tab_strip2);


    function  _stlpcov    (miniSTRIP: T_strip): byte;
    function  _tab_strip  (miniSTRIP: T_strip): PpopisTablet;

    procedure new_Popis   (Popis1,Popis2 : PpopisSkupina);
    procedure disp_Popis  (var Popis  : TpopisSkupina);
    procedure disp_Stlpec (var Stlpec : TpopisStlpec);

    procedure str_to_Popis (s : string; var Popis : TpopisSkupina);
    function  Popis_to_str (Popis : TpopisSkupina): string;

    procedure read_tablet_cfg (cfg_fn: string);
    procedure save_tablet_cfg (cfg_fn: string);

    procedure init_SORT_NDB(var SORT_NDBs: PSORT_NDBs; var pocet: int);
    procedure done_SORT_NDB(var SORT_NDBs: PSORT_NDBs; var pocet: int);
    procedure add_to_SORT_CFG(NDB: string;  sort_by: Tsort_strip);


implementation

uses  str0, math, sort,
      Help, CM;


function _stlpcov(miniSTRIP: T_strip): byte;
   begin
     _stlpcov:= 4 - ord(miniSTRIP)
   end;

function _tab_strip(miniSTRIP: T_strip): PpopisTablet;
    begin
      if miniSTRIP=full_strip then _tab_strip:= @tab_strip2
      else if miniSTRIP=short_strip then _tab_strip:= @tab_strip3
      else _tab_strip:= @tab_strip4
    end;


{ ------------------------------
   TABLET
  ------------------------------
}

procedure new_Popis(Popis1,Popis2: PpopisSkupina);
    begin
      Popis2^.NDB:= Popis1^.NDB;
      Popis2^.NDBs:= StrNew(Popis1^.NDBs)
    end;

procedure disp_Popis(var Popis: TpopisSkupina);
    begin
      Popis.NDB:= '';
      StrDispose(Popis.NDBs)
    end;

procedure disp_Stlpec(var Stlpec: TpopisStlpec);
    var   i : int;
    begin
      for i:= 0 to max_skupin-1 do disp_Popis(Stlpec[i])
    end;

(*
  ZAB, SOUTH EAST (JEL KSC NIT), NORTH-KSC KSC KSCSW KSCSC ...

procedure str_to_STLPEC(s: string; var Stlpec: TpopisStlpec);
    var   i,p,n : int;
          u : string;
    begin
      disp_Stlpec(Stlpec);
      s:= cut_(upstring(s));
      i:= 0; p:= GetStrItems(s,setTABLET_CFG);
      while (s<>'') and (i<max_skupin) do
        begin
          u:= upstring(cut_(getstr(s,i,setTABLET_CFG)));
          n:= pos('(',u);
          if n=0 then n:= pos(' ',u);
          Stlpec[i].NDB := cut_(copy(u,1,n-1));
          Stlpec[i].NDBs:= strpasnew(cut_(delchar(copy(u,n,length(u)-n+1),['(',')'])));
          s:= copy(s,length(u)+1,length(s)-length(u)+1);
          inc(i)
        end
    end;

function STLPEC_to_str(Stlpec: TpopisStlpec): string;
   var   s : string;
         i : int;
   begin
     s:= ''; i:= 0;
     while (Stlpec[i].NDB<>'') and (i<max_skupin) do
       begin
         s:= s + Stlpec[i].NDB;
         if StrLen(Stlpec[i].NDBs)>0 then s:= s + ' ('+StrPas(Stlpec[i].NDBs)+')';
         s:= s + ', ';
         inc(i)
       end;
     STLPEC_to_str:= s
   end;
*)

procedure str_to_Popis(s: string; var Popis: TpopisSkupina);
    var   j,n : int; u: string;
    begin
      disp_Popis(Popis);
      s:= upstring(s); s:= cut_(s);
      if s='' then Exit;

      n:= get_str_items (@s[1],length(s),odd_popis);
      Popis.NDB := get_str(@s[1],length(s),1,odd_popis,sizeof(s)-1); Popis.NDB := cut_(Popis.NDB);
      for j:= 2 to n do
        begin
          u:= get_str(@s[1],length(s),j,odd_popis,sizeof(u)-1); u:= cut_(u);
          Popis.NDBs:= StrNPCopy(Popis.NDBs,u+' ',true,true)
        end;
    end;

function Popis_to_str(Popis: TpopisSkupina): string;
   var   s: string;
   begin
     s:= Popis.NDB;
     if s<>'' then s:= s+inschar('',N(15-length(Popis.NDB)),' ',1)+StrPas(Popis.NDBs);
     Popis_to_str:= s
   end;


{ ---------
   Cfg
  ---------
}
procedure read_tablet_cfg (cfg_fn: string);

    procedure read_STLPEC(var f: text; var Stlpec: TpopisStlpec);
        var   i : int;
              s : string;
        begin
          i:= 0; ReadLn(f,s); s:= cut_(s);
          while {(not Eof(f)) and} (s<>'') and (i<max_skupin) do
            begin
              str_to_Popis(s, Stlpec[i]);
              ReadLn(f,s); s:= cut_(s);
              inc(i)
            end
        end;

    var   D : DirStr; N : NameStr; E : ExtStr;

          f : text;
          s : string;
          i : int;

    begin
      if cfg_fn<>TABLET_CFG then
         begin
           FSplit(cfg_fn,D,N,E);
           cfg_fn:= N+ext_tbl;
           USER_TABLET_CFG:= cfg_fn
         end
      else USER_TABLET_CFG:= APP_TABLET_CFG;

      Assign(f,cfg_fn); Reset(f);
      for i:= 0 to stl_strip2-1 do read_STLPEC(f,tab_strip2[i]);
      readln(f,s);
      for i:= 0 to stl_strip3-1 do read_STLPEC(f,tab_strip3[i]);
      readln(f,s);
      for i:= 0 to stl_strip4-1 do read_STLPEC(f,tab_strip4[i]);
      Close(f);
    end;


procedure save_tablet_cfg (cfg_fn: string);

    procedure write_STLPEC(var f: text; var Stlpec: TpopisStlpec);
        var   i : int;
              s : string;
        begin
          for i:= 0 to max_skupin-1 do
            begin
              s:= Popis_to_str(Stlpec[i]); s:= cut_(s);
              if s='' then break;
              writeln(f,s)
            end;
          writeln(f,'')
        end;

    var   D : DirStr; N : NameStr; E : ExtStr;
          f : text;
          i : int;

    begin
      ResetIOError;
      FSplit(cfg_fn,D,N,E);
      USER_TABLET_CFG:= N+ext_tbl;

      Assign(f,USER_TABLET_CFG);
      Rewrite(f);
      for i:= 0 to stl_strip2-1 do write_STLPEC(f,tab_strip2[i]);
      writeln(f,'');
      for i:= 0 to stl_strip3-1 do write_STLPEC(f,tab_strip3[i]);
      writeln(f,'');
      for i:= 0 to stl_strip4-1 do write_STLPEC(f,tab_strip4[i]);
      Close(f)
    end;


{ ------------------------------
   TRIEDENIE
  ------------------------------
}

procedure init_SORT_NDB(var SORT_NDBs: PSORT_NDBs; var pocet: int);
    var   f       : text;
          p,i,j   : int;
          s,NDB   : string;

    function get_sort_by(ch: char): Tsort_strip;
       var   j : Tsort_strip;
       begin
         get_sort_by:= sort_imp;
         for j:= Low(Tsort_strip) to High(Tsort_strip) do
             if ch = Text_sort_strip[j] then
                begin
                  get_sort_by:= j;
                  break
                end
       end;

    begin
      Assign(f,SORT_CFG);
      Reset(f); pocet:= 0;
      while not Eof(f) do
        begin
          readln(f,s); s:= cut_(s);
          if (s<>'') and (s<>';') then inc(pocet)
        end;
      pocet:= Minimum(pocet,MaxAvail-100000 div sizeof(TSORT_NDB));
      GetMem(SORT_NDBs, pocet*sizeof(TSORT_NDB));
      FillChar(SORT_NDBs^,pocet*sizeof(TSORT_NDB),0);
      i:= 0; Reset(f);
      while (i<pocet) and (not Eof(f)) do
        begin
          ReadLn(f,s); s:= upstring(s); s:= cut_(s);
          if (s='') or (s=';') then break;

          SORT_NDBs^[i].sort_by:= get_sort_by(getchar(getstr(s,2,[' '])));
          if SORT_NDBs^[i].sort_by=sort_imp then continue;

          NDB:= getstr(s,1,[' ']);
          j:= 0; while (j<i) and (SORT_NDBs^[j].NDB<>NDB) do inc(j);
          if j<i then continue;

          SORT_NDBs^[i].NDB:= NDB;
          inc(i)
        end;
      Close(f)
    end;

procedure done_SORT_NDB(var SORT_NDBs: PSORT_NDBs; var pocet: int);
    begin
      FreeMem(SORT_NDBs, pocet*sizeof(TSORT_NDB));
      SORT_NDBs:= nil; pocet:= 0
    end;


procedure add_to_SORT_CFG(NDB: string;  sort_by: Tsort_strip);
    var   f         : text;
          SORT_NDBs : PSORT_NDBs;
          pocet,i   : int;
    begin
      init_SORT_NDB(SORT_NDBs,pocet);
      Assign(f,SORT_CFG);
      Rewrite(f);
      for i:= 0 to pocet-1 do
          if (NDB <> SORT_NDBs^[i].NDB) and (SORT_NDBs^[i].sort_by<>sort_imp) then
             WriteLn(f,SORT_NDBs^[i].NDB+' '+Text_sort_strip[SORT_NDBs^[i].sort_by]);
      WriteLn(f,NDB+' '+Text_sort_strip[sort_by]);
      Close(f);
      done_SORT_NDB(SORT_NDBs,pocet)
    end;

end.