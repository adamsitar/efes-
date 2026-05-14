{$I comp.h}

uses bios, typedef, math, str0,  db, dos,
     _l4_def, archiv, _FPLM;

var  s: string;


 procedure _decodeDB0_FPLM(buff: PDB_buff; FPL: PDmFPL; head: PDB_head); far;
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

           vu:= '';
           i:= 0; while (i<=sizeof(vu)-1) and (p^[i]>=' ') do
             begin
               vu:= vu + p^[i];
               inc(i);
             end;
           p:= @p^[i];
           for i:= 0 to 2 do
             begin
               get_s(p, @ulohy[i],sizeof(Tuloha_FPLM));
             end;


           {
           get_s(p, @ulohy,sizeof(ulohy));}


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
           get_s(p, @TRG,sizeof(TRG));
           get_s(p, @RDP,sizeof(RDP));
           get_s(p, @LAM,sizeof(LAM));

          { prevzatie spravy
          }
           s:= DBstr_to_str_ (buff^[db_mFPL_ine]); p:= @s[1];
           get_s(p, @rec,sizeof(rec));
         end;
     end;


function znova_uloz_FPL(FPL: PDmFPL; p: pointer): byte; far;
   begin
     save_mFPL(FPL);
     znova_uloz_FPL:= do_item__NEXT
   end;

function znova_uloz_RPL(FPL: PDmFPL; fn: pstring): byte; far;
   begin
     DB_oprav(FPL, FN^,db_mFPL_RIADKOV,@codeDB_FPLM,@codekey_FPLM,nil, dbattr_FPM);
     znova_uloz_RPL:= do_item__NEXT
   end;

procedure kontrola_archivu;
    var   fn : string;
          P: PathStr; D: DirStr; N: NameStr; E: ExtStr;
          FPL : DmFPL;
          is : bool;

    begin
      konverzia_archivu (pathFPL_M,ext_mFPL,@znova_uloz_FPL,
                         sizeof(DmFPL),@disp_mFPL,db_mFPL_RIADKOV,
                         @_decodeDB0_FPLM
                        );
      konverzia_archivu (pathARCH_FPL_M,ext_mFPL,@znova_uloz_FPL,
                         sizeof(DmFPL),@disp_mFPL,db_mFPL_RIADKOV,
                         @_decodeDB0_FPLM
                        );

      konverzia_archivu (pathFPL_M,ext_KRL,
                         @znova_uloz_FPL,sizeof(DmFPL),@disp_mFPL,
                         db0_mFPL_RIADKOV,@_decodeDB0_FPLM
                        );

      konverzia_archivu (pathARCH_FPL_M,ext_KRL,
                         @znova_uloz_FPL,sizeof(DmFPL),@disp_mFPL,
                         db0_mFPL_RIADKOV,@_decodeDB0_FPLM
                        );
    end;


begin
  kontrola_archivu;
end.






     {s:= 'ODNEM BNO'#0;
  fillchar(start,sizeof(start),0);
  fillchar(prist,sizeof(prist),0);
  init_date(date,1999,04,24);

  s:= _decode_FPL0_15
        (@s[1],
         start,prist,
         Trat,bodov,

         rych,rych_,
         vys,vys_,

         date,
         false,false,false,false
        )
  }

  InitBGI;
  formular_cFPL_(nil,'');


end.

vyber si testovacie ->priklady<-