{$I comp.h}

uses bios, typedef, math, str0, io, db, dos, utime, keyb, crt,
     _l4_def, archiv, bod_def, body, kody,
     _FDP_def, _FPL_def, NET_def, _MTK_2,
     _FPL4;

var  s: string;


 procedure _decodeDBB0_FPL4(buff: PDB_buff; FPL: PFPL4; head: PDB_head);
     var   s,t,u : string;
           p : pchars;
           i : int;
     begin
       fillchar(FPL^,sizeof(FPL^),0);
       with FPL^ do
         begin
          { data : 7,8,9,10, 13,14,16,17, 5;
            pri zmene opravit decode_DBB_FDR...
          }
           s:= DBstr_to_str_ (buff^[db_fpl4_data]); p:= @s[1];

           get_s(p, @_7[0],sizeof(_7));

           get_s(p, @_8[0], sizeof(_8));
           get_s(p, @_9[0], sizeof(_9));
           get_s(p, @_10[0],sizeof(_10));

           get_s(p, @_13[0],sizeof(_13));
           get_s(p, @_14[0],sizeof(_14));
           get_s(p, @_16[0],sizeof(_16));

           get_s_x(p, u,sizeof(u)-1);
           _17:= strpasnew(u);

           get_s_x(p, u,sizeof(u)-1);
           _5:= strpasnew(u);

          { trat: 15
          }
           _15:= decode_line_i (DBstr_to_str(buff^[db_fpl4_15_1]), _15,[]);
           _15:= decode_line_i (DBstr_to_str(buff^[db_fpl4_15_2]), _15,[]);

          { pozn : 18,19,20
          }
           _18:= decode_line_i (DBstr_to_str(buff^[db_fpl4_18_1]), _18,[]);
           _18:= decode_line_i (DBstr_to_str(buff^[db_fpl4_18_2]), _18,[]);
           _19:= decode_line_i (DBstr_to_str(buff^[db_fpl4_19]), _19,[]);
           _20:= decode_line_i (DBstr_to_str(buff^[db_fpl4_20]), _20,[]);

          { ine udaje
          }
           s:= DBstr_to_str_ (buff^[db_fpl4_ine]); p:= @s[1];
           get_s(p, @stat, sizeof(stat));
           get_s(p, @date, sizeof(date));
           get_s(p, @eet,  sizeof(eet));
           get_s(p, @exi,  sizeof(exi));
           get_s(p, @vys_, sizeof(vys_));
           get_s(p, @vys,  sizeof(vys));
           get_s(p, @src,  sizeof(src));
           get_s(p, @rec,  sizeof(rec));
         end;
     end;


{$I arc_format.inc}         { Kontrola integrity archivnych suborov }

{$I _FPL4_plan.cod}
{$I _FPL4_archiv.inc}


begin
  kontrola_archivu_FPL4($FF,db_FPL4_RIADKOV,@_decodeDBB0_FPL4);

  writeln;
  writeln('LETVIS FDP utility to transformate FDP''s databases format.');
  writeln('Copyright by ALES (c) 1989-1999.');
end.
