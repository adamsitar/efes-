 var   SaveExit : pointer;
       SaveMain : TProc;


{ Citac sa kazdu polnoc vygumuje
}
 procedure check_CISLO; far;
     const lm : byte = 60;
           lh : byte = 24;
     begin
       if @SaveMain<>nil then SaveMain;
       if (lh=hour) and (lm=min) then Exit;

       if (hour=0) and (min=0) then
          begin
            CISLO_SPRAVY:= 0;
            save_cislo(SPR_kod,CISLO_SPRAVY);
          end;
       lh:= hour;
       lm:= min
     end;

 procedure done_SPR;
     begin
       {if editor_SPR<>nil then dealloc_stranu_editora(editor_SPR, RDKV_SPR,ZNKV_SPR);}
       if form_SPRadr<>nil then disp_form(form_SPRadr,size_SPRadr);
       form_SPRadr:= nil;
       ExitProc:= SaveExit
     end;

 procedure initialize_SPR;
     var   SPR : DSPR;
           i   : int;
     begin
       write('Initialize MSG... ');
       SaveExit  := ExitProc;
       ExitProc  := @done_SPR;

       SaveMain  := ACheckProcessesD;
       ACheckProcessesD := check_CISLO;

       {kontrola_archivu;}

       {size_SPRadr:= size_TLGadr;}
       form_SPRadr:= new_form (@form_TLGadr,size_SPRadr);
       for i:= i_tlg_adr to size_SPRadr-1 do
          begin
            form_SPRadr^[i].lst:= @fnSPR;
            form_SPRadr^[i].legal:= @set_SPRadr;
          end;

       {editor_SPR:= alloc_stranu_editora(RDKV_SPR,ZNKV_SPR);}
       CISLO_SPRAVY:= read_cislo(SPR_kod);
       writeln('Done.')
     end;
