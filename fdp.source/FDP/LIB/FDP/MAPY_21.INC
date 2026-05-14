{
‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹
€                                                          €
€ Objekt TCopyMapa                                         €
€‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹€
}

constructor TCopyMapa.Init(_Owner: PGroup; x,y,dx,dy: int; _OMapa: PMapa; _cfg: string);
      var   f   : file;
            res : int;
            b   : bool;
            _dx : real;
      begin
        TView.Init(_Owner,x,y,dx,dy);
        Active:= true; MCursor:= KRIZ; hlpXXX:= hlpmnuMMI_MAPS;

        OMapa:= _OMapa; OMapa^.reinit_(GraphMode);
        p_ciele:= nil; p_handle:= nil; p_cursor:= nil;

        zMapy := OMapa^.zMapy;
        zTrate:= New( PZozMap, {PListMan,} Init {(SizeOf(TMapData))} );
        zTrat := New( PZozMap, {PListMan,} Init {(SizeOf(TMapData))} );

        map_init:= OMapa^.map_init;
        Txx := OMapa^.Txx;  Tyy := OMapa^.Tyy;
        dTyy:= OMapa^.dTyy; dK1 := OMapa^.dK1;  dK2:= OMapa^.dK2;
        Xvystred := OMapa^.Xvystred; Yvystred := OMapa^.Yvystred;
        Ys2 := OMapa^.Ys2;  Ys1 := OMapa^.Ys1;
        Xs2 := OMapa^.Xs2;  Xs1 := OMapa^.Xs1;
        Kon1:= OMapa^.Kon1; Kon2:= OMapa^.Kon2;

        _dx:= (x1-x0); if _dx=0 then _dx:= 1;
        Rozsah := OMapa^.Rozsah * ((_OMapa^.x1-_OMapa^.x0)/_dx);
        Txx:=  OMapa^.x1; Tyy:=  OMapa^.y1;
        InvPoint(Xvystred,Yvystred);

        cfg:= _cfg;
        if pos(ext_sym,cfg)=0 then cfg:= cfg+ext_kod;
        if Exists(cfg)=0 then
           begin
           { nastavenie stredu                   }
             Assign(f,cfg);
             Reset(f,1);
             BlockRead(f,Rozsah  ,SizeOf(Real),res);
             BlockRead(f,Xvystred,SizeOf(Real),res);
             BlockRead(f,Yvystred,SizeOf(Real),res);
             Close(f)
           end
      end; { Init }


destructor TCopyMapa.Done;
     var   f   : file;
           res : int;
     begin
       Assign(f,cfg);
       Rewrite(f,1);
       BlockWrite(f,Rozsah  ,SizeOf(Real),res);
       BlockWrite(f,Xvystred,SizeOf(Real),res);
       BlockWrite(f,Yvystred,SizeOf(Real),res);
       Close(f);
     { musi byt prazdna, aby neodalokovala data rodicovskej mapy }
       done_maps(zTrat);
       done_maps(zTrate)
     end; { Done }


procedure TCopyMapa.reinit_(_mode: TGraphMode);
    var   _x0,_y0,_x1,_y1: int;
    begin
      _x0:= x0; _y0:= y0; _x1:= x1; _y1:= y1;
      inherited reinit_(_mode);
      XY(_x0,_y0,_x1-_x0,_y1-_y0)
    end;


procedure TCopyMapa.handle_target(var _Event: TEvent);
    begin
    end;
