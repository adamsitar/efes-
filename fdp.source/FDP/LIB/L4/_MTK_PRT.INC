{ - vrati prioritu, ak ju najde : na prvej pozicii riadku;
  - neporovanava sa len jednoduchy retazec, ale volajaky
    algoritmus potrebuje najst identifikator pripority,
    preto sa pocita i sa nasledujucou medzerou
}
function is_mtkprtyi(s: string): int;
   var   p : string;
         i : int;
   begin
     p:= mtks_rus_to_lat(s); p:= cut_(p);
     p:= copy(p,1,kod_MTK_2_PRTY+1);
     if length(p)=kod_MTK_2_PRTY then p:= p + icao_NXIT;
     i:= 0; while (i<max_MTK_2_PRTY) and (MTK_2_PRTY[i]+icao_NXIT<>p) do inc(i);
     if (i<max_MTK_2_PRTY) then is_mtkprtyi:= i
     else is_mtkprtyi:= -1
   end;

function is_mtkprty(s: string): string;
   var   i : int;
   begin
     i:= is_mtkprtyi(s);
     if (i<0) then is_mtkprty:= ''
     else is_mtkprty:= MTK_2_PRTY[i]
   end;

function _prtyTLG(prty: string): prtyTLG;
   var   i: int;
   begin
     prty:= uni_str(prty);
     i:= 0; while (i<max_MTK_2_PRTY) and (prty<>MTK_2_PRTY[i]) do inc(i);
     if i<2 then _prtyTLG:= prtySS
     else if i<4 then _prtyTLG:= prtyFF
     else _prtyTLG:= prtyKK
   end;


function mtk_tlg_prty (data: pchars; size: word; var res: string): string;
   var   prty : string;
         i,pi : int;
   begin
     mtk_tlg_prty:= '';
     if data=nil then Exit;
     pi:= get_str_items(data,size, setNL+setNL_);
     i:= 2; prty:= is_mtkprty (get_str(data,size,i,setNL+setNL_, sizeof(prty)-1));
     while (prty='') and (i<=pi) do
       begin
         inc(i); prty:= is_mtkprty(get_str(data,size,i,setNL+setNL_, sizeof(prty)-1))
       end;
     if prty='' then prty:= MTK_2_PRTY[max_MTK_2_PRTY-1]
     else prty:= mtks_rus_to_lat(prty);
     mtk_tlg_prty:= prty
   end;

function  mtk_tlg_id (data: pchars; size: word): string;
   var    res, s1,s2 : string;
          i,p   : int;
   begin
     res:= ''; i:= 1; p:= get_str_items (data,size, [icao_NXIT]+setNL+setNL_);
     while (i<=p) and (res='') do
       begin
         s1:= get_str (data,size, i,[icao_NXIT], sizeof(s1)-1);
         if mtks_rus_to_lat(s1)=MTK_2_SOT then
            begin
              s1:= get_str(data,size, i+1,[icao_NXIT]+setNL+setNL_, sizeof(s1)-1);
              s1:= copy(s1,_MTK_CHNL+1,length(s1)-_MTK_CHNL+1);
              s2:= get_str(data,size, i+2,[icao_NXIT]+setNL+setNL_, sizeof(s2)-1);
              res:= s1{+icao_NXIT}+s2;
              { VLA005 0018 : jednoznacna identifikacia tlg }
            end;
         inc(i)
       end;
     mtk_tlg_id:= mtks_rus_to_lat(res)
   end;


function  mtk_tlg_fdp  (typ: word{TNETtyp}): string;
   begin
     if (typ>=spri_FPL_lo) and (typ<=spri_FPL_hi) then mtk_tlg_fdp:= tlgFF
     else if (typ>=spri_ACT_lo) and (typ<=spri_ACT_hi) then mtk_tlg_fdp:= tlgGG
     else if (typ>=spri_ASM_lo) and (typ<=spri_ASM_hi) then mtk_tlg_fdp:= tlgGG
     else mtk_tlg_fdp:= tlgKK
   end;
