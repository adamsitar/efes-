procedure _text(x0,y0,x1,y1: int; p: pointer); far;
    begin
      bgigraph.button(x0,y0,x1,y1,clBUTTON_COLOR-1,btSmall,btON);
      inc(x0,dx_ed); inc(y0,dy_ed);

      Write_   (x0+20, y0+15,'MaxAvail:', clGRb);
      OutTextXY(x0+20, y0+30,'MemAvail:');
      Write_   (x0+122,y0+15,IntToStr(MaxAvail,9,1)+' kB',clGRd);
      OutTextXY(x0+122,y0+30,IntToStr(MemAvail,9,1)+' kB');

      Write_   (x0+20, y0+50,'DiskSize:', clGRb);
      OutTextXY(x0+20, y0+65,'DiskFree:');
      Write_   (x0+122,y0+50,IntToStr(DiskSize(0),9,1)+' kB',clGRd);
      OutTextXY(x0+122,y0+65,IntToStr(DiskFree(0),9,1)+' kB');

      {Write_  (x0+20, y0+085,'Packet MEM:', clGRb);
      OutTextXY(x0+20, y0+100,'Packet TMP:');}
      Write_   (x0+18, y0+085,'IOresult:', clGRb);

     {
      Write_   (x0+122, y0+085,IntToStr(pkt_net,9,1),clGRd);
      OutTextXY(x0+122, y0+100,IntToStr(pkt_tmp,9,1));
     }
      OutTextXY(x0+122, y0+085,IntToStr(IOErrorCode,9,1))
    end;

