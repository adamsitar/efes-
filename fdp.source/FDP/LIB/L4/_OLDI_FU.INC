procedure _info_OLDI(x0,y0,x1,y1: int; _DEV_OLDI: P_OLDI);
    begin
      bgigraph.button(x0,y0,x1,y1,clBUTTON_COLOR-1,btSmall,btON);
      inc(x0,dx_ed); inc(y0,dy_ed);

      Write_   (x0+20, y0+15,'UDF :', clGRb);
      Write_   (x0+120,y0+15,_UDFstr(_DEV_OLDI^.UDF), yellow);

      Write_   (x0+20, y0+35,'This   NODE :', clGRb);
      OutTextXY(x0+20, y0+47,'       X25  :');
      OutTextXY(x0+20, y0+59,'       NSAP :');
      Write_   (x0+150,y0+35,_DEV_OLDI^.NODE_THIS, yellow);
      OutTextXY(x0+150,y0+47,_DEV_OLDI^.X25adr_THIS);
      OutTextXY(x0+150,y0+59,_read_cfg(_DEV_OLDI^.cfg_FN,cfg_NSAP_THIS,true));

      Write_   (x0+20, y0+70,'Remote NODE :', clGRb);
      OutTextXY(x0+20, y0+82,'       X25  :');
      OutTextXY(x0+20, y0+94,'       NSAP :');
      Write_   (x0+150,y0+70,_DEV_OLDI^.NODE_REMOTE, yellow);
      OutTextXY(x0+150,y0+82,_DEV_OLDI^.X25adr_MASTER);
      {$IFDEF OLDI_BACKUP}
       OutTextXY(x0+150,y0+94,_DEV_OLDI^.X25adr_BACKUP);
       OutTextXY(x0+150,y0+102,_read_cfg(_DEV_OLDI^.cfg_FN,cfg_NSAP_REMOTE,true));
      {$ENDIF}

      Write_   (x0+20, y0+120 ,'Time Out Ts :', clGRb);
      OutTextXY(x0+20, y0+132,'Time Out Tr :');
      Write_   (x0+150,y0+120 ,cstr(trunc(_DEV_OLDI^.TsTimeOut),2),clGRe);
      OutTextXY(x0+150,y0+132, cstr(trunc(_DEV_OLDI^.TrTimeOut),2));

      Write_   (x0+20, y0+148,'Send StratUp:', clGRb);
      Write_   (x0+150,y0+148,cfg_OFF_ON[_DEV_OLDI^.send_StartUp],clGRe);
    end;
