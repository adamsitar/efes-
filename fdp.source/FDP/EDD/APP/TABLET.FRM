{
ÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜ
Û                                                          Û
Û Settings ACC                                             Û
ÛÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÛ
}
{ - lepsie je naprogramovat do editora, ale tera nemam cas vymyslat
    citatelneu gramatiku na oddelenie strlpcov, majakov.
  - nemoze byt pouzita viacnasobne sucasne -> frm_mini_STRIP urcuje,
    s ktorym druhom stripov sa pracuje
}

type  PEdTablet = ^TEdTablet;
      TEdTablet = record
        tab_strip : TpopisTablet;
        rdk,stl   : int;

        mini      : T_strip;
        novy_rdk  : bool;
      end;

const rdk_na_skupinu = max_skupin+1;

function _write_TABLET(ET: PEdTablet; i: int; s: string): string; far;
   var   p_tab_strip : PpopisTablet;
         j : int;
   begin
     p_tab_strip:= _tab_strip(miniSTRIP);
     if i=0 then
        begin
          for j:= 0 to max_stlpec-1 do disp_Stlpec(ET^.tab_strip[j]);
          ET^.rdk:= 0; ET^.stl:= 0; ET^.novy_rdk:= false;
        end;

     _write_TABLET:= '';
     if (ET=nil) or (i<0) or (i>max_stlpec*(rdk_na_skupinu)) then Exit;

   { nacitanie z premennej/zapis do editora
   } {ET^.rdk:= ((i-ET^.stl) mod (max_skupin));
     ET^.stl:= ((i-ET^.stl) div (max_skupin));}
     if (i>0) and ((i-ET^.stl) mod max_skupin=0) then s:= ''
     else begin
            ET^.stl:= ((i-ET^.stl) div (max_skupin));
            ET^.rdk:= ((i-ET^.stl) mod (max_skupin));
            if     (ET^.stl<max_stlpec)
               and (ET^.rdk<max_skupin) then
                 s:= Popis_to_str(p_tab_strip^[ET^.stl,ET^.rdk]);
          end;
     _write_TABLET:= s
   end;

function _read_TABLET(ET: PEdTablet; i: int; s: string): string; far;
   var   p_tab_strip : PpopisTablet;
         j : int;
   begin
      p_tab_strip:= _tab_strip(miniSTRIP);
      if i=0 then
         begin
           for j:= 0 to max_stlpec-1 do disp_Stlpec(ET^.tab_strip[j]);
           ET^.rdk:= 0; ET^.stl:= 0; ET^.novy_rdk:= false;
         end;

     _read_TABLET:= '';
     if (ET=nil) or (i<0) or (i>max_stlpec*(rdk_na_skupinu)) then Exit;

   { nacitanie z editora/zapis do premennej
   } if (s='') then ET^.novy_rdk:= true
     else begin
            if (not (ET^.rdk<max_skupin)) or ET^.novy_rdk then
               begin
                 inc(ET^.stl);
                 ET^.rdk:= 0;
               end;
            ET^.novy_rdk:= false
          end;
     if (ET^.stl<max_stlpec) and (ET^.rdk<max_skupin) then
        begin
          str_to_Popis(s, ET^.tab_strip[ET^.stl,ET^.rdk]);
          inc(ET^.rdk);
        end
   end;


function _check_TABLET(E: PEditor; O: PObject; ET: PEdTablet): bool; far;
   var   p_tab_strip : PpopisTablet;
         p_str       : Pstrs;
         i : int;
   begin
     _check_TABLET:= false;

     { riadky su uz nacitane funkciu _read_TABLET, mozno by ich bolo dobre skontrolvat
     }

     { Prehodit od 1 do n a naopak...
     }
     {getmem(p_str,sizeof(string)*ET^.items); fillchar(p_str^,sizeof(string)*ET^.items,0);}

     p_tab_strip:= _tab_strip(ET^.mini);
     for i:= 0 to _stlpcov(ET^.mini)-1 do
         begin
           disp_Stlpec(p_tab_strip^[i]);
           p_tab_strip^[i]:= ET^.tab_strip[i]
         end;

     {freemem(p_str,sizeof(string)*ET^.items);}
     _check_TABLET:= true
   end;


procedure  formular_TABLET;
    const  f  : Tcentr  = (x: initX; y: initY; m:1);
    var    E  : PEditors;
           Ev : TEvent;
           ET : PEdTablet;
    begin
      New(ET); fillchar(ET^,sizeof(ET^),0);
      ET^.mini:= miniSTRIP;
      E:= New(PEditors,Init(nil, f.x,f.y,f.m,
              cmOK, 'ARRANGE TABLET', false,
              nil, (rdk_na_skupinu)*_stlpcov(ET^.mini),max_znakov_e,(rdk_na_skupinu)*_stlpcov(ET^.mini),
              @_write_TABLET, @_read_TABLET,
              pointer(ET), 0,0,false,false,
              [],[' '],' ',
              @_check_TABLET,
              dbtWIDTH+10,{dbtHEIGHT+1}0, @init_editor_bt,nil,nil,nil,
              0,clgre,0,clgre,0,clgre,
              nil
             ));
      E^.RunLocalFunc(Ev,' ~Ctrl~+~ÄÙ~ :  ARRANGE TABLET...');
      if E^.corr_res then send_mail(E,MainApp, cmACC_SETT, one,nil,0);
      Dispose(E,Done);
      Dispose(ET)
    end;
