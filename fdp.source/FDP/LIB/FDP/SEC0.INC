{
  - patri tento druh informacie na uzol ?
  - moze sa dotazovat len na jeden druh informacie !
}

function is_to_nd(nd      : int;      { cislo uzla }
                  info    : string;   { typ informacie odosielanej na uzol }
                  filter  : pointer;  { @TBfunc_pi - poslat plan na tento smer ? (sektor) }
                  data    : pointer;  { @data          }
                  initdb  : pbool
                 ): bool;
   var   node : string;
         b1,b2,b3: bool;
   begin
     if nd<0 then node:= info else node:= strpas(NODEs^[nd].desc.inf);
     b1:= (not NODE_INFO) or (pos(inf_ALL,node)>0) or (pos(info,node)>0);
     b2:= (info='') or ((info<>'') and (pos('\'+info,node)=0));
     b3:= ((filter=nil) or (data=nil)) or (TBfunc_pi(filter)(data,nd));
     if initdb<>nil then initdb^:= (info<>'') and (pos(info+'\'+info_NODB,node)=0);

     is_to_nd:= b1 and b2 and b3
   end;


{ je to uzol povoleneho typu ?
}
function is_nd_type(nd      : int;

                    typ_set : Tnd_typ_set;
                    sw_set  : Tnd_sw_set;
                    nd_set  : Tnd_nd_set
                   ): bool;
   begin
     is_nd_type:=      (     (NODEs^[nd].desc.typ <> no_typ)
                         and ((typ_set=[]) or (any_typ in typ_set) or (NODEs^[nd].desc.typ in typ_set))
                       )
                   and (     (NODEs^[nd].desc.sw <> no_sw)
                         or  ((sw_set=[]) or (any_sw in sw_set) or (NODEs^[nd].desc.sw in sw_set))
                       )
                   and (     (NODEs^[nd].desc.nd <> no_nd)
                         and ((nd_set=[]) or (any_nd in nd_set) or (NODEs^[nd].desc.nd in nd_set))
                       )
   end;
