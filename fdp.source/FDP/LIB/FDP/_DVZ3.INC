{ DVZ schvalene, odmietnute, ... sa vracaju s priznakom cnst_read
}

{ -------------------------------
  oprava ziadosti
}
function _is_CHG(DVZ: PDVZ; s: Pstring): bool; far;
    var   cond: string;
    begin
      cond:= cnl_stat(cnst_all_valid);
      _is_CHG:= _vlastne(DVZ,@cond)
    end;

function _DVZ_CHG(DVZ: PDVZ): bool; far;
   begin
     formular_DVZ(DVZ, false,false,true, del_cnl_stat(DVZ^.stat), tit_dvz_chg);
     _DVZ_CHG:= false;
   end;

procedure DVZ_oprava;
    begin
      spracuj_DVZ(get_PPL_FN(pathDVZ,extDVZ,tit_dvz_chg),
                  '', @_is_CHG,
                  @_DVZ_CHG, _TBFunc_p,
                  false,
                  tit_dvz_chg,nil
                 )
    end;


{ -------------------------------
   odoslanie ziadosti o diverziu
}
function _is_REQ(DVZ: PDVZ; s: Pstring): bool; far;
    var   cond: string;
    begin
      cond:= cnst_disk+cnst_sended + cnst_dvz_req;
      if DEC_VYPIS then cond:= cond + cnst_dec;
      _is_REQ:= _vlastne(DVZ,@cond)
    end;

function _DVZ_REQ(DVZ: PDVZ): bool; far;
   begin
     formular_DVZ(DVZ, false,false,true, cnst_dvz_req, tit_dvz_req);
     _DVZ_REQ:= false;
   end;

procedure DVZ_poziadavka;
    begin
      spracuj_DVZ(get_dbDVZfn,
                  '', @_is_REQ,
                  @_DVZ_REQ, _TBFunc_p,
                  false,
                  tit_dvz_req,nil
                 )
    end;


{ -------------------------------
   Spracovanie ziadosti
}
function _is_ACC(DVZ: PDVZ; s: Pstring): bool; far;
    var   cond: string;
    begin
      cond:= cnst_prop;
      if DEC_VYPIS then cond:= cond + cnst_dec;
      _is_ACC:= _drzane(DVZ,@cond)
    end;

function _DVZ_ACC(DVZ: PDVZ): bool; far;
   begin
     formular_so_ziadostou_o_DVZ (DVZ,false);
     _pozri_odlozene_ziadosti_o_DVZ(nil);
     _DVZ_ACC:= false
   end;

procedure DVZ_spracuj_ziadost;
    begin
      spracuj_DVZ(get_dbDVZfn,
                  '', @_is_ACC,
                  @_DVZ_ACC, _TBFunc_p,
                  false,
                  tit_dvz_acc,nil
                 );
    end;


{ -------------------------------
  V˜straha pred zru¨en¡m diverzie
}
function _is_ALR(DVZ: PDVZ; s: Pstring): bool; far;
    var   cond: string;
    begin
      cond:= {cnst_prop+} cnst_acc + cnst_active;
      _is_ALR:= _drzane(DVZ,@cond)
    end;

function _DVZ_ALR(DVZ: PDVZ): bool; far;
   begin
     {formular_pre_spracovanie_DVZ (DVZ,false, add_stat(DVZ^.stat,cnst_dvz_alr),tit_dvz_alr);}
     formular_DVZ(DVZ, false,false,false, add_stat(DVZ^.stat,cnst_dvz_alr),tit_dvz_alr+rep_dvz_for+DVZ^.pre);
     _DVZ_ALR:= false;
   end;

procedure DVZ_vystraha_pred_zrusenim;
    begin
      spracuj_DVZ(get_dbDVZfn,
                  '', @_is_ALR,
                  @_DVZ_ALR, _TBFunc_p,
                  false, tit_dvz_alr,nil
                 )
    end;


{ -------------------------------
  Zrusenie v˜strahy
}
function _is_CLN(DVZ: PDVZ; s: Pstring): bool; far;
    var   cond: string;
    begin
      cond:= cnst_dvz_alr;
      _is_CLN:= _drzane(DVZ,@cond)
    end;

function _DVZ_CLN(DVZ: PDVZ): bool; far;
   begin
     {formular_pre_spracovanie_DVZ (DVZ,false, del_stat(DVZ^.stat,cnst_dvz_alr),tit_dvz_cln);}
     DVZ^.stat:= delchar(DVZ^.stat,[cnst_dvz_alr]);
     if DVZ^.stat='' then DVZ^.stat:= cnst_acc;
     formular_DVZ(DVZ, false,false,false, DVZ^.stat, tit_dvz_cln+rep_dvz_for+DVZ^.pre);
     _DVZ_CLN:= false
   end;

procedure DVZ_zrusenie_vystrahy;
    begin
      spracuj_DVZ(get_dbDVZfn,
                  '', @_is_CLN,
                  @_DVZ_CLN, _TBFunc_p,
                  false, tit_dvz_cln,nil
                 )
    end;


{ -------------------------------
   odoslanie na diverziu
   (aktivovanie)
}
function _is_ACT(DVZ: PDVZ; s: Pstring): bool; far;
    var   cond: string;
    begin
      cond:= cnst_acc;
      _is_ACT:= _vlastne(DVZ,@cond)
    end;

function _DVZ_ACT(DVZ: PDVZ): bool; far;
   begin
     formular_DVZ(DVZ, false,false,true, cnst_dvz_zac, tit_dvz_act);
     _DVZ_ACT:= false
   end;

procedure DVZ_odosli_na_diverziu;
    begin
      spracuj_DVZ(get_dbDVZfn,
                  '', @_is_ACT,
                  @_DVZ_ACT, _TBFunc_p,
                  false,
                  tit_dvz_act,nil
                 )
    end;


{ -------------------------------
   ukoncenie/zrusenie
}
function _is_CNL(DVZ: PDVZ; s: Pstring): bool; far;
    var   cond: string;
    begin
      cond:= cnst_disk + cnst_prop + cnst_acc;
      _is_CNL:= _vlastne(DVZ,@cond)
    end;

function _is_END(DVZ: PDVZ; s: Pstring): bool; far;
    var   cond: string;
    begin
      cond:= cnst_stat_act + cnst_dvz_alr;
      _is_END:= _vlastne(DVZ,@cond)
    end;

function _is_ACN (DVZ: PDVZ; s: Pstring): bool; far;
    var   cond: string;
    begin
      cond:= cnst_dvz_alr {cnst_acc + cnst_stat_act};
      _is_ACN := _drzane(DVZ,@cond)
    end;


function _DVZ_CNL(DVZ: PDVZ): bool; far;
   var   s,stt: string;
         b: bool;
   begin
     _DVZ_CNL:= false;
     b:= pos(cnst_disk,DVZ^.stat)=0;
     s:= ask_dvzCNL;
     if _vlastne(DVZ,nil) then
        begin
          s:= s+' '+tit_na_u+' ('+DVZ^.kym+') ';
          if _is_CNL(DVZ,nil) then stt:= cnst_cnl
          else if _is_END(DVZ,nil) then stt:= cnst_dvz_kon
          else Exit
        end
     else begin
            s:= s+' '+tit_pre+' ('+DVZ^.pre+') ';
            if _is_ACN (DVZ,nil) then stt:= cnst_dvz_acn
            else Exit
          end;
     if b then s:= s+ask_rozoslat+' ';
     s:= s + '?';
     if (Ask2(msgVERIPHY,s, titNO,White,clBUTTON_COLOR,waitASK*18) = ansAno) then
        zarad_DVZ(DVZ, stt, b, letvis);
   end;


procedure DVZ_zrusenie(plan,vlastne: bool);
    var   FN,tit: string;
          p: pointer;
    begin
      if plan then
         begin
           FN:= get_PPL_FN(pathDVZ,extDVZ,tit);
           tit:= tit_dvz_cnl;
           p:= @_is_CNL;
         end
      else begin
             FN:= get_dbDVZfn;
             if vlastne then
                begin
                  tit:= tit_dvz_end;
                  p:= @_is_END
                end
             else begin
                    tit:= tit_dvz_acn;
                    p:= @_is_ACN
                  end

           end;
      spracuj_DVZ(FN,
                  '', p,
                  @_DVZ_CNL, _TBFunc_p,
                  false,
                  tit,nil
                 )
    end;

{procedure DVZ_zrusenie;
    var   tit: string;
    begin
      tit:= 'Zru¨enie diverzie';
      spracuj_DVZ(get_dbDVZfn,
                  cnst_warn, @_is_drzane,
                  @CNL_DVZ, _TBFunc_p,
                  false,
                  tit,nil
                 )
    end;}



{ -------------------------------
  ukoncenie/zrusenie
}
(*
 function _is_SEND(DVZ: PDVZ; s: Pstring): bool; far;
    var   cond: string;
    begin
      cond:= cnst_disk;
      _is_SEND:= (SERVERnode>-1) and (DVZ^.rec[SERVERnode]=no_ack) and _is_stat_DVZ(DVZ,@cond)
    end;

 function _SEND_DVZ(DVZ: PDVZ): bool; far;
    begin
      if pos(cnst_disk,DVZ^.stat)<>0 then _SEND_DVZ:= zmen_stat_DVZ(DVZ,cnst_sended,true)
      else _SEND_DVZ:= distribute_DVZ(DVZ,[],[]){send_DVZ(DVZ,SERVERaddress,WAIT_INIT_NODE)}
    end;

 procedure send_DVZs(DVZs: Pptrs; top: pointer);
    var   i : int;
          b : bool;
    begin
      if int(top^)<0 then Exit;

      i:= 0; b:= true;
      while b and (i<=int(top^)) do
        begin
          if _is_SEND(DVZs^[i],nil) then
             begin
               b:= _SEND_DVZ(DVZs^[i]);
               {if not WAIT_INIT_NODE then} Wait(3,Check)
             end;
          inc(i)
        end;
      say_data_sended(b)
   end;
*)