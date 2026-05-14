 procedure prehlad_AUP(ppl: bool);
     var   FN : string;
     begin
       if ppl then FN:= allfiles else FN:= get_DBfn_(day,month,year,'',ext_all);
       FN:= get_PPL_FN_(pathAUP,FN,@is_file_FUA, tit_AUP);
       if FN<>'' then _infop(FN,tit_AUP,0,0, true,false,nil)
     end;

 procedure prehlad_AUP_ARCH;
     var   FN : string;
     begin
       FN:= get_ARCH_FN_(pathARCH_AUP,ext_all,@is_file_FUA, tit_AUP);
       if FN<>'' then _infop(FN,tit_AUP,0,0, true,false,nil)
     end;


 procedure prehlad_UUP(ppl: bool);
     var   FN : string;
     begin
       if ppl then FN:= allfiles else FN:= get_DBfn_(day,month,year,'',ext_all);
       FN:= get_PPL_FN_(pathUUP,FN,@is_file_FUA, tit_UUP);
       if FN<>'' then _infop(FN,tit_UUP,0,0, true,false,nil)
     end;

 procedure prehlad_UUP_ARCH;
     var   FN : string;
     begin
       FN:= get_ARCH_FN_(pathARCH_UUP,ext_all,@is_file_FUA, tit_UUP);
       if FN<>'' then _infop(FN,tit_UUP,0,0, true,false,nil)
     end;

