  {$IFDEF ABI_COORDINATION}
    procedure O_FPL.set_ABI (p: pointer);
        var   przn: byte;
        begin
        { predpokladam, ze abi je vymaskovany priznak
        } przn:= get_priznak (p);
          set_priznak (p, przn xor sp_abi, true)
        end;

    procedure O_FPL.coordinate_ABI (p: pointer);
        var   ind: int;
        begin
          ind:= find(p); if ind<0 then Exit;
          set_ABI(ap^[ind]);
          vypis_plan(ind, false, false);
          uloz(ap^[ind]);
          posli(p,SERVERaddress,false)
        end;
  {$ENDIF}

