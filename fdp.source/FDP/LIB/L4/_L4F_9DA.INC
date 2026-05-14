
 function  _9b_data (var _9: string; is_icao: bool): string;
    var    ind : int;
           ini : bool;
           res : string;
           _9a,_9b,_9c : string;
    begin
      _9b_data:= '';
      if lst_9bICAO=nil then Exit;

      _9b:= _9;
      if _check_9_by8643 (_9b,res,true,true)<>0 then Exit;
      if (not is_icao) then _9:= _9b;
      decode_l4_9 (_9,_9a,_9b,_9c);

      ini:= lst_9bICAO^.is_initialized;
      if not ini then lst_9bICAO^.InitList;
      if (lst_9bICAO^.find(_9b,res,ind)>-1) and (lst_9bICAO^._icao(res)<>ZZZZ) then _9b_data:= res;
      if not ini then lst_9bICAO^.DoneList;
    end;


 function  _9b_rychvys (_9: string; is_icao: bool;
                        var rych: single; var rych_: char; var minkmh,maxkmh: single;
                        var vys: word;    var vys_ : char; var minS,maxS: word
                       ): bool;
    var    res : string;
    begin
      _9b_rychvys:= false;
      rych:= standartna_rych; rych_:= spdK; minkmh:= 0; maxkmh:= 0;
      vys := standartna_vys;  vys_:= altS;  minS:= 0;   maxS:= 0;

      res:= _9b_data(_9,is_icao);
      if (res<>'') and (lst_9bICAO<>nil) then
         begin
           lst_9bICAO^._speed (res, rych,rych_, minkmh,maxkmh);
           lst_9bICAO^._fl (res, vys,vys_,   minS,maxS);
           _9b_rychvys:= (rych<>0) or (vys<>0)
         end;

      if rych=0 then begin rych:= standartna_rych; rych_:= spdK; end;
      if vys =0 then begin vys := standartna_vys;  vys_:= altS;  end;
    end;


 function _rychvys_rozsah
                 (rmkh: single; vS: word;
                  minr,maxr: single;
                  minv,maxv: word;

                  var res  : string;
                  var ires : int
                 ): bool;
    var   s: string;
    begin
      ires:= 0; res:= '';
      if _15a_RANGE and (rmkh<>0) then
         begin
           s:= code_l4_rych (rmkh,spdK);
           if (maxr>0) and (rmkh>maxr) then ires:= l4_err(a_15a,s+'>'+code_l4_rych(maxr,spdK),i_15a,err_15a_hi, res)
           else if (rmkh<minr) then ires:= l4_err(a_15a,s+'<'+code_l4_rych(minr,spdK),i_15a,err_15a_lo, res)
         end;
      if _15b_RANGE and (vS<>0) then
         begin
           s:= code_l4_vys (vS,altS);
           if (maxv>0) and (vS>maxv) then ires:= l4_err(a_15a,s+'>'+code_l4_vys(maxv,altS),i_15a,err_15b_hi, res)
           else if (vS<minv) then ires:= l4_err(a_15a,s+'<'+code_l4_vys(minv,altS),i_15a,err_15b_lo, res)
         end;
      _rychvys_rozsah:= ires=0
    end;


 function _9_rychvys_rozsah

                 (_9 : string;
                  rmkh: single; vS: word;
                  var res  : string;
                  var ires : int
                 ): bool;

   var    cr, minr,maxr: single;
          cv, minv,maxv: word;
          cr_,cv_: char;
   begin
     ires:= 0; res:= '';
     _9_rychvys_rozsah:=
             (_9='')
          or (not _9b_rychvys (_9,false, cr,cr_,minr,maxr, cv,cv_, minv,maxv))
          or _rychvys_rozsah (rmkh,vS, minr,maxr, minv,maxv, res,ires)
   end;


{ priradenie nezadanych hodnot rychlosti a vysky podla typu
}
 function  _9b_rychvys_fl

                (var typ: string;

                 trat, b0,bl: string;

                 var ry: single; var ry_: char;
                 var v: word; var v_: char
                ): bool;

     var   s1,s2,s3,s4 : string;
           B,B2        : TsBod;

           minr, maxr  : single;
           minv,maxv   : word;
           i           : int;

           imp_smer    : bool;
           smer,ismer  : Ts_dir;
           e,w         : Pwords;
           e_,w_       : int;
           L           : PList;

     procedure init_FL(fl_dir: char; var fl: pwords; var fl_: int);
         var   i,p : int;
               vi  : word;
               vi_ : char;
               s   : string;
         begin
           fl_:= 0; fl:= nil;
           for p:= 0 to L^.top do if cut_(getstr(L^.get(p),2,[';']))=fl_dir then inc(fl_);
           getmem(fl,sizeof(word)*fl_);
           fillchar(fl^,sizeof(word)*fl_,0);

           p:= 0; i:= 0;
           while (p<=L^.top) and (i<fl_) do
             begin
               s:= L^.get(p);;
               if cut_(getstr(s,2,[';']))=fl_dir then
                  begin
                    decode_l4_vys (getstr(s,1,[';',' ']),vi,vi_);
                    fl^[i]:= get_altM (vi_,vi) div m_S;
                    inc(i)
                  end;
               inc(p)
             end;
         end;

     begin
       _9b_rychvys_fl:= false;

     { urcenie medznych hodnot
     }
       _9b_rychvys (typ,true, ry,ry_, minr, maxr, v,v_, minv,maxv);


     { Pre urcenie letovej hladiny je podstatne, ze sa zo smeru letu daneho
       vektorom medzi prvym a poslednym bodom (pokial nie je pretazeny popisom
       za tratou 1 2 ... n ; >) a z typickej letovej hladiny v smere na vychod
       odvodi predpokladana letova hladina (o stupen mensia (na zaklade cfg
       subora, pretoze zatial nemam vztah pre vysky)
     }

     { Urcenie smeru letu
     }
       imp_smer:= true;
       if cut_(trat)<>'' then
          begin
           { vyhladanie trate
           }
            trat:= _get_line_(trat,pathDATA+_fnRTE_fir+FIRext,[],lst_vsetky_polozky,lst_cely_riadok);

           { urcenie smeru
           }
            s1:= getstr(trat,1,[';']);
            if     is_OB(getstr(s1,1,[icao_NXIT]), B, true)
               and is_OB(getstr(s1,getstritems(s1,[icao_NXIT]),[icao_NXIT]), B2,true) then
               begin
                 if B.x < B2.x then smer:= dir_east
                 else smer:= dir_west
               end
            else smer:= dir_no;

            ismer:= dir_no; s2:= cut_(getstr(trat,2,[';']));
            if (s2<>'') and (s2[1] in [dir_cwest,dir_ceast]) then
               if s4[1]=dir_cwest then ismer:= dir_west
               else ismer:= dir_east;

            imp_smer:= (ismer=dir_no) or (smer=ismer)
          end;

      smer:= dir_no;
      if is_OB(b0, B, true) and is_OB(bl, B2,true) then
         begin
           if B.x < B2.x then smer:= dir_east
           else smer:= dir_west
         end;

     { Priradenie spravnej letovej hladiny; t.j.
       implicitne su uvedene hladiny na vychod,
       ak je let na zapad, treba ju zmenit na ekvivalentnu
     }
      if (v<>0) and (imp_smer) and (smer=dir_west) then
         begin
           L:= New(PList,Init(@fnAlt,'',[],lst_cely_riadok, false,nil,true));

           init_FL(dir_cwest, w,w_);
           init_FL(dir_ceast, e,e_);

           v:= get_altM (v_,v) div m_S; v_:= altS;
           i:= 0; while (i<e_) and (v<>e^[i]) do inc(i);
           if (i<e_) and (i<w_) then v:= w^[i];

           freemem(e,sizeof(word)*e_);
           freemem(w,sizeof(word)*w_);
           Dispose(L,Done)
         end;

       _9b_rychvys_fl:= smer <> dir_no
     end;


 function  _15ab_to_9 (_9,_15ab: string): string;
    var    ry,minr, maxr   : single;
           ry_,v_,v_ab,v2_ : char;
           v,v2,minv,maxv  : word;
    begin
      if not decode_l4_rych_vys(_15ab, ry,ry_, v,v_) then
         begin
           _9b_rychvys (_9,true, ry,ry_, minr, maxr, v,v_, minv,maxv);
           _15ab:= code_l4_rych_vys (ry,ry_, v,v_, 0,true);
         end;
      _15ab_to_9:= _15ab
    end;
