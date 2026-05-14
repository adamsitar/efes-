 procedure disp_EXTnode(node: PEXTnode);
     begin
       strdispose(node^.desc.adr);
       strdispose(node^.desc.name);
       strdispose(node^.desc.inf);
     end;

 procedure O_EXT.initialize_NODES;
     var   node: PEXTnode;
     begin
       if (EXTs=nil) or (EXTpoc>=maxEXTs) then Exit;

       new(node);
       fillchar(node^,sizeof(node^),0);
       node^.desc.obj := @Self;
       node^.desc.adr := strpasnew(NODE_REMOTE);
       {node.desc.name:= strpasnew();}
       node^.desc.inf := strnew(coor_info);
       EXTs^[EXTpoc]:= node;
       inc(EXTpoc);
     end;
