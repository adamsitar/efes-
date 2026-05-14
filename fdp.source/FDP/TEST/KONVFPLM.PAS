{$I comp.h}

{$DEFINE FDP}
{$DEFINE FDP_OPL}
{$DEFINE OPL}
{$DEFINE MATCA}     { MILITARY_ATC_AUTHORITY   }
{$DEFINE MACC}

{ Zamerne prazdne
}
{$DEFINE DEBUG}

{$DEFINE LZ}
{$DEFINE SK}
{$DEFINE CZECH}
{$DEFINE HELP_CZ}

{$DEFINE BGI}
{$DEFINE PRN}
{ DEFINE STATUS}

{$DEFINE MAPY}

  {$DEFINE PPL}
  {$DEFINE FPL}
  {$DEFINE FPL0}
  {$DEFINE KRL}
    {$DEFINE FPLM_L}
    {$DEFINE FPLM_PLAN}
    {$DEFINE PROCESS_FPLM}


{$DEFINE DB_BIN}
{$DEFINE DATA_BIN}
{$DEFINE RDP}

{$DEFINE ODOSLI_ULOZ}


{ DEFINE SPr}

{$DEFINE NET}
{$DEFINE ARCHIVE_NET}
{ DEFINE PCTCP}
{ DEFINE UDP}

uses  typedef, str0, db, dos, io, 
      _l4_def,
      bod_def, body,
      _fdp_def, _fpl_def, archiv,
      _fplm,
      {$I net_unit.h},
      {$I map_unit.h};


{*******************************
  Povodne deklaracie
 *******************************
}

type      PDmFPL0 = ^DmFPL0;
          DmFPL0  = record

          { plan ------------------------------------------------
                 ak je DB_BIN, potom pozor na zmenu
                               struktury a DB zapisu
          }
            idn   : string[kod_MIDN];  { identifikacia      }
            { IFNDEF L4444M}
             idn_ : char;     { priznak hromadneho letu     }
            { ENDIF}
            ssr   : string[kod_7c];  { SSR kod              }

            _8a   : char;     { pravidla letu:  P-pristroje, V-vid }
            _8b   : char;     { typ planu podla ICAO        }

            com_  : string[kod_10a]; { vybavenie            }
            ssr_  : string[kod_10b]; { priznak SSR: A-ano, N-nie   }

            typ   : string[kod_9];   { typ -> kodom alebo znackou  }
            typ2  : string[kod_9];   { typ -> kodom alebo znackou  }

            rych  : single;   { rychlost                    }
            rych_ : char;     { velicina rychlosti          }

            vys   : word;     { vyska - spodna hladina      }
            vys_  : char;     { velicina vysky              }

            vys2  : word;     { vyska - horna hladina       }
            vys2_ : char;     { velicina vysky              }

            start : TAP;      { letisko startu              }
            prist : TAP;      { letisko pristatia           }
            prist_: string[KOD_AP]; { zalozne -//-          }

            vu    : string[kod_FLO]; { VU - prevadzkovatel  }
            ulohy : Tulohy_FPLM;

            trat  : Pchar;
            pozn  : Pchar;


          { parametre platnosti
          }
            date  : TDate;                   { datum realizacie planu }
            dap   : TDatum;                  { datum podania/opravy   }
            let   : string[kod_AP];          { letisko podania planu  }
            stat  : string[kod_plan_status];


          { vypoctove premenne
          }
            cor_  : byte;      { oprava : kolkokrat ?        }

            trat_ : POBxys;
            bodov : int;       { pocet bodov na trati }
	    na_bod: byte;      { bod, na ktory leti   }

            poz   : Tpoz;
            sur   : Tsur;
            cl    : byte      { farba, akou sa vypisuje plan, aby sa nezdrziavalo jej urcenim }

            (*{$IFDEF MAPY};
              mapa : PMapData
            {$ENDIF}

            {IFDEF RDP};           { FDP_EDD musi byt vo vsetkych prepojenych staniciach FDP }
              TRG : TTRG_stat;
              RDP : TRTRadr;        { accept na RDP stanici }
              LAM : word            { Tplan_rec }
            {ENDIF}*)

            {IFDEF NET};
              rec  : Tplan_rec
            {ENDIF}
          end;


 procedure disp_mFPL0(FPL0: PDmFPL0); far;
     begin
       with FPL0^ do
         begin
           StrDispose(trat);
           StrDispose(pozn);
           if trat_<>nil then begin FreeMem(trat_, sizeof(TOBxy)*bodov); trat_:= nil end;
         end;
     end;


 procedure format_mFPL0(FPL: PDmFPL0);
     var   OBs   : TOBxys;
           bod,i : int;
           zmena : bool;
     begin
       with FPL^ do
         begin
           idn:= format_s(idn);
           idn_:= format_(idn_);

           ssr:= code_l4_7c(ssr);
           ssr_:= format_s_(ssr_);
           {if (ssr_[1]=' ') and (ssr<>code_l4_7c('')) then ssr_:= mod_A+cut_(ssr_);}

           _8a:= format_(_8a);
           _8b:= format_(_8b);

           typ:= cut_(typ); typ2:= cut_(typ2);
           rych_:= format_(rych_);
           vys_ := format_(vys_);
           vys2_:= format_(vys2_);
         end
     end;

 procedure _decodeDBB_FPLM0(buff: PDB_buff; FPL: PDmFPL0; desc: PDB_desc); far;
     var   s,t : string;
           i : int;
           p : pchars;
     begin
       fillchar(FPL^,sizeof(FPL^),0);
       with FPL^ do
         begin
          { data
          }
           s:= DBstr_to_str_ (buff^[db_mFPL_data]); p:= @s[1];

           get_s(p, @idn[0],sizeof(idn));
           get_s(p, @idn_, sizeof(idn_));
           get_s(p, @ssr[0],sizeof(ssr));

           get_s(p, @_8a,sizeof(_8a));
           get_s(p, @_8b,sizeof(_8b));

           get_s(p, @com_[0],sizeof(com_));
           get_s(p, @ssr_[0],sizeof(ssr_));

           get_s(p, @typ[0],sizeof(typ));
           get_s(p, @typ2[0],sizeof(typ2));

           get_s(p, @rych,sizeof(rych));
           get_s(p, @rych_,sizeof(rych_));

           get_s(p, @vys,sizeof(vys));
           get_s(p, @vys_,sizeof(vys_));
           get_s(p, @vys2,sizeof(vys2));
           get_s(p, @vys2_,sizeof(vys2_));

           get_s(p, @start,sizeof(start));
           get_s(p, @prist,sizeof(prist));
           get_s(p, @prist_[0],sizeof(prist_));

           get_s(p, @vu,sizeof(vu));
           get_s(p, @ulohy,sizeof(ulohy));


          { trat
          }
           FPL^.trat:= decode_line_i (DBstr_to_str(buff^[db_mFPL_15_1]), FPL^.trat,[]);
           FPL^.trat:= decode_line_i (DBstr_to_str(buff^[db_mFPL_15_2]), FPL^.trat,[]);


          { pozn
          }
           {FPL^.pozn:= decode_line_i (DBstr_to_str(buff^[db_mFPL_18]), FPL^.pozn,[]);}
           FPL^.pozn:= strpasnew (DBstr_to_str(buff^[db_mFPL_18]));


          { ine udaje
          }
           s:= DBstr_to_str_ (buff^[db_mFPL_19]); p:= @s[1];
           get_s(p, @date,sizeof(date));
           get_s(p, @dap,sizeof(dap));
           get_s(p, @let[0],sizeof(let));

           get_s(p, @stat[0],sizeof(stat));

           get_s(p, @cor_,sizeof(cor_));
           {get_s(p, @TRG,sizeof(TRG));
           get_s(p, @RDP,sizeof(RDP));
           get_s(p, @LAM,sizeof(LAM));}

          { prevzatie spravy
          }
           s:= DBstr_to_str_ (buff^[db_mFPL_ine]); p:= @s[1];
           get_s(p, @rec,sizeof(rec));
         end;

       format_mFPL0(FPL);
     end;


 procedure decodeDB_FPLM0(buff: PDB_buff; FPL0: PDmFPL0; desc: PDB_desc);
     begin
       fillchar(FPL0^,sizeof(FPL0^),0);
       if desc^.attr and DBbin <> 0 then _decodeDBB_FPLM0(buff,FPL0,desc);
       {else if desc^.attr and DBtxt = 0 then _decodeDB0_FPLM(buff,FPL,desc)
       else _decodeDBT_FPLM(buff,FPL,desc);}
     end;


{*******************************
  Funkcie pre prepis
 *******************************
}

procedure FPL0toFPL(FPL0: PDmFPL0; FPL: PDmFPL);
    begin
      fillchar(FPL^,sizeof(FPL^),0);

      FPL^.idn   := FPL0^.idn;
      FPL^.idn_  := FPL0^.idn_;
      FPL^.ssr   := FPL0^.ssr;

      FPL^._8a   := FPL0^._8a;
      FPL^._8b   := FPL0^._8b;

      FPL^.com_  := FPL0^.com_;
      FPL^.ssr_  := FPL0^.ssr_;

      FPL^.typ   := FPL0^.typ;
      FPL^.typ2  := FPL0^.typ2;

      FPL^.rych  := FPL0^.rych;
      FPL^.rych_ := FPL0^.rych_;

      FPL^.vys   := FPL0^.vys;
      FPL^.vys_  := FPL0^.vys_;

      FPL^.vys2  := FPL0^.vys2;
      FPL^.vys2_ := FPL0^.vys2_;

      FPL^.start := FPL0^.start;
      FPL^.prist := FPL0^.prist;
      FPL^.prist_:= FPL0^.prist_;

      FPL^.vu    := FPL0^.vu;
      FPL^.ulohy := FPL0^.ulohy;

      FPL^.trat  := FPL0^.trat;
      FPL^.pozn  := FPL0^.pozn;


      FPL^.date  := FPL0^.date;
      FPL^.dap   := FPL0^.dap;
      FPL^.let   := FPL0^.let;
      FPL^.stat  := FPL0^.stat;
    end;



function znova_uloz_FPL(FPL0: PDmFPL0; p: pointer): byte; far;
   var   FPL: DmFPL;
   begin
     FPL0toFPL(FPL0,@FPL);
     save_mFPL(@FPL);
     znova_uloz_FPL:= do_item__NEXT
   end;

function znova_uloz_RPL(FPL0: PDmFPL0; fn: pstring): byte; far;
   var   FPL: DmFPL;
   begin
     FPL0toFPL(FPL0,@FPL);
     save_mFPL_RPL_(@FPL,true);
     znova_uloz_RPL:= do_item__NEXT
   end;

function konvertovat_archiv (fn: string): bool;
   var   desc : TDB_desc;
   begin
     konvertovat_archiv:= DB_desc(fn,desc) and (desc.attr = DBBIN)
   end;

procedure kontrola_archivu;
    var   fn : string;
          P: PathStr; D: DirStr; N: NameStr; E: ExtStr;
          FPL0 : DmFPL0;
          is : bool;

    begin
      if    konvertovat_archiv(pathFPL_M+najmladsi_subor(pathFPL_M,'*.'+ext_mFPL))
         or konvertovat_archiv(pathARCH_FPL_M+najmladsi_subor(pathARCH_FPL_M,'*.'+ext_mFPL))
            then
        begin
          konverzia_archivu
            (pathFPL_M,     ext_mFPL,@znova_uloz_FPL,sizeof(DmFPL),@disp_mFPL0,db_mFPL_RIADKOV,@decodeDB_FPLM0);
          konverzia_archivu
            (pathARCH_FPL_M,ext_mFPL,@znova_uloz_FPL,sizeof(DmFPL),@disp_mFPL0,db_mFPL_RIADKOV,@decodeDB_FPLM0);
          konverzia_archivu
            (pathFPL_M,     ext_KRL, @znova_uloz_FPL,sizeof(DmFPL),@disp_mFPL0,db_mFPL_RIADKOV,@decodeDB_FPLM0);
          konverzia_archivu
            (pathARCH_FPL_M,ext_KRL, @znova_uloz_FPL,sizeof(DmFPL),@disp_mFPL0,db_mFPL_RIADKOV,@decodeDB_FPLM0);
        end;

      fn:= get_fn_mFPL_RPL_let;
      if konvertovat_archiv (fn) then
          begin
            FSplit(fn,D,N,E);
            MoveFile(fn,D+N+'.0');
            fn:= D+N+'.0';
            fillchar(FPL0,sizeof(FPL0),0);
            do_items_DB(@znova_uloz_RPL,@fn,
                        @FPL0,@disp_mFPL0,
                        fn, db_mFPL_RIADKOV,nil,@decodeDB_FPLM0,nil,
                        nil
                       )
          end;
    end;

begin
  kontrola_archivu;
end.
