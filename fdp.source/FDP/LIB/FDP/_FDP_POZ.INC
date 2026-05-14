{ -----------------------------
  Funkcie pre konverziu medzi
  binarnym a textovym formatom
  priznaku stavu
}

 function  decode0_stat (stat: string): string;
    begin
      stat:= ReplChar(stat,[cnst0_dec],cnst_dec);
      stat:= ReplChar(stat,[cnst0_acc],cnst_acc);
      decode0_stat:= stat
    end;

 function  code0_stat (stat: string): string;
    begin
      stat:= ReplChar(stat,[cnst_dec],cnst0_dec);
      stat:= ReplChar(stat,[cnst_acc],cnst0_acc);
      code0_stat:= stat
    end;


 function  code_l4_stat_ (stat: string; oprava: bool): string;
    begin
      case _decode_stav(stat) of
        _ukonceny   : code_l4_stat_:= rmk_END{hd_ARR};
        _zruseny    : code_l4_stat_:= hd_CNL;

        _preruseny  : code_l4_stat_:= rmk_BRK;
        _aktivovany : if oprava then code_l4_stat_:= hd_REV
                      else code_l4_stat_:= hd_ACT;

        else {_plan,_ziadost,_zamietnuty,_schvaleny,_neplatny}
                      code_l4_stat_:= rmk_PLAN;
      end;
    end;

 function  code_l4_stat(stat: string): string;
   begin
     code_l4_stat:= code_l4_stat_(stat,false);
   end;



function _decode_stav(stat: string): Tstav;
   var   stav: Tstav;
   begin
     if      { konci, pristava    }  pos(cnst_stat_arr,stat)>0 then           stav:= _ukonceny
     else if { zruseny plan       }  pos(cnst_cnl,stat)>0 then                stav:= _zruseny

     else if { plan               }  __is_stat (stat,cnst_disk) then          stav:= _fdp_def._plan
     else if { ziadost            }  __is_stat (stat,cnst_requested) then     stav:= _ziadost
     else if { zamietnuty plan    }  pos(cnst_dec,stat)>0 then                stav:= _zamietnuty
     else if { schvaleny plan     }  pos(cnst_acc,stat)>0 then                stav:= _schvaleny

     else if { preruseny, mzp     }     (pos(cnst_pause,stat)>0)
                                     or (pos(cnst_stat_mzp,stat)>0)  then     stav:= _preruseny
     else if { (pre)aktivovany    }  __is_stat (stat, cnst_stat_preact) then  stav:= _aktivovany

     else stav:= _neplatny;

     _decode_stav:= stav
   end;


{function _code_stav(stat: Tstav): string;
   begin
     case stat of
       _ukonceny      : _code_stav:= cnst_stat_arr;
       _zruseny       : _code_stav:= cnst_cnl;
       _ziadost       : _code_stav:= cnst_requested;
       _zamietnuty    : _code_stav:= cnst_dec,stat;
       _schvaleny     : _code_stav:= cnst_acc,stat;
       _preruseny     : _code_stav:= cnst_pause;
       _aktivovany    : _code_stav:= cnst_stat_preact;
       else             _code_stav:= cnst_disk;
     end;
   end;}

{ plan moze byt realizovany len v dobe
  definovanej zaciatkom a koncom
}

{$I _plan_vypocet.h}

function _platny_plan(cas: real;
                      zr: word; zm,zd, zh,zn: byte;
                      kr: word; km,kd, kh,kn: byte;
                      stt : string;
                      pred,          { preaktivovanie planu - nacitanie }
                      nepl,          { zrusenie neaktivovaneho planu    }
                      za   : real    { zrusenie aktivovaneho planu      }
                     ): TPoz;
   var   zac,z_, kon,k_ : real;
         poz  : Tpoz;
         stav : Tstav;
   begin
     stav:= _decode_stav(stt);

     z_:= DatetoSec(zr,zm,zd); zac:= z_ + TimeToSec(zh,zn,0);
     k_:= DatetoSec(kr,km,kd); kon:= k_ + TimeToSec(kh,kn,0);
     if (z_=k_) and (kon<zac) then kon:= kon + secDAY; { dalsi den }

     pred:= pred*secMIN;
     if stav<_aktivovany then za:= nepl*secMIN
     else if stav<>_ukonceny then za:= za*secMIN
     else za:= 0;

     poz:= poz_PLAN;

     { if A-dA<=T+dA  => preactived
       if A-dA<=T     => proposed/coordinated
     }

     {if       (stav<>_ukonceny)
          and ((absTime > kon+za) or (stav = _neplatny))
                                then poz:= poz_NOT_ACTUAL

     else}if stav = _zruseny    then poz:= poz_CANCELLED

     else if stav = _zamietnuty then poz:= poz_NOT_APPROVED

     else if stav in [_aktivovany,_preruseny,
                      _ukonceny
                     ] then
          begin
            if absTime+pred >= zac then
               if (absTime <= kon) then
                  begin
                    if (absTime < zac) or (stav<_aktivovany) then poz:= poz_COORDINATED
                    else if stav = _preruseny then poz:= poz_STOJI
                    else poz:= poz_LETI
                  end
               else begin
                      if (absTime <= kon+za) and (stav <> _preruseny) then poz:= poz_PRIST
                      else if (stav < _aktivovany)  then poz:= poz_NOT_ACTUAL
                      else poz:= poz_HANGAR
                    end
            else poz:= poz_COORDINATED
          end

     else if stav in [_fdp_def._plan,_ziadost,_schvaleny] then
          begin
            if absTime+pred >= zac-pred then
               begin
                 if absTime+pred < zac then poz:= poz_PREACTIVE
                 else if absTime <= kon then poz:= poz_PROPOSED
                 else poz:= poz_NOT_ACTUAL
                 { !  v skutocnsoti zatial nepocitam s parametrom
                      nepl, ktory mal povodne oznacovat neplatnost
                      planu, ak nebol realizovany do nejakeho casoveho
                      limitu
                 }
               end
          end;

     _platny_plan:= poz
   end;


function platny_plan(cas: real;
                     zac,kon : TDatum;
                     stt : string;
                     pred,          { preaktivovanie planu - nacitanie }
                     nepl,          { zrusenie neaktivovaneho planu    }
                     za   : real    { zrusenie aktivovaneho planu      }
                    ): TPoz;
   begin
     platny_plan:= _platny_plan(cas,
                                zac.rok,zac.mes,zac.den, zac.h,zac.m,
                                kon.rok,kon.mes,kon.den, kon.h,kon.m,
                                stt, pred,nepl,za
                               )
   end;


{
  kvoli vykreslovaniu polohy na planzete
}
function get_poz(plan_stat: string): Tpoz;
   begin
      if    pos(cnst_pause,plan_stat)<>0           then get_poz:= poz_STOJI
      else  if pos(cnst_stat_mzp,plan_stat)<>0 then get_poz:= poz_MZP
      else  if    (pos(cnst_stat_mzs,plan_stat)<>0)
              or (pos(cnst_active,plan_stat)<>0)
              or (pos(cnst_start,plan_stat)<>0)    then get_poz:= poz_LETI
      else  if pos(cnst_finish,plan_stat)<>0       then get_poz:= poz_SEDI
      else  if pos(cnst_warn,plan_stat)<>0         then get_poz:= poz_PATRAT
      else  if pos(cnst_CNL,plan_stat)<>0          then get_poz:= poz_HANGAR
      else  if    (pos(cnst_prop,plan_stat)<>0)    { neskor rozlisit i na poz_COORDINATED }
               or (pos(cnst_acc,plan_stat)<>0)     then get_poz:= poz_PROPOSED
      else                                              get_poz:= poz_PROPOSED
   end;
