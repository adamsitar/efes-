function znova_uloz_SPR(SPR: PSPR; p: pointer): byte; far;
   begin
     save_SPR(SPR);
     znova_uloz_SPR:= do_item__NEXT
   end;

function znova_uloz_RPL(SPR: PSPR; fn: pstring): byte; far;
   begin
     DB_oprav(SPR, FN^,db_SPR_RIADKOV,@codeDB_SPR,@codekey_SPR,nil, dbattr_SPR);
     znova_uloz_RPL:= do_item__NEXT
   end;

procedure kontrola_archivu;
    var   fn : string;
          SPR : DSPR;

    begin
      fn:= najmladsi_subor(pathMES,'*.'+extMES);
      if konvertovat_archiv(pathMES+fn,DB0) then
         begin
           konverzia_archivu (pathMES,extMES,@znova_uloz_SPR,sizeof(DSPR),@disp_SPR,db_SPR0_RIADKOV,@_decodeDB0_SPR);
         end
    end;
