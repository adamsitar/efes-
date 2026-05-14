 type  PSwitchB = ^TSwitchB;
       TSwitchB = object(TSwitch2)
         bgu : byte;

         constructor Init(_title: string; _check_adr: pointer; _bgu: byte; _Next: PItem);

         procedure   read_check_adr; virtual;
         procedure   writeto_check_adr; virtual;
       end;


 constructor TSwitchB.Init(_title: string; _check_adr: pointer; _bgu: byte; _Next: PItem);
     begin
       inherited Init(_title,_check_adr,_Next);
       bgu:= _bgu
     end;

 procedure TSwitchB.read_check_adr;
     begin
       stat:= TbtStat((check_adr<>nil) and (TBGUind(check_adr^)=bgu))
     end;

 procedure TSwitchB.writeto_check_adr;
     var   i: int;
     begin
       if (check_adr<>nil) then
          if bool(stat) then TBGUind(check_adr^):= bgu
          else if TBGUind(check_adr^)=bgu then TBGUind(check_adr^):= NOBGU
     end;



 function _BGUmenu(title: string): PSubMenu;
    var   BGUmenu,Bi : PSubMenu;
          {Bi   : POptMenu_S;}
          it   : PSwitchB;
          i,j  : int;
          s    : string;
    begin
      BGUmenu:= SubMenu(title, WinMenu('ÅÉì', nil,nil),nil);

      for i:= lo_BGUadr to hi_BGUadr do
        begin
          s:= ' ÅÉì '+cstr(i,1)+' ';
          Bi:= SubMenu(s, OptMenu_S(s,nil,cmDefault,15,nil),nil);
          POptMenu(Bi^.PMenu)^.PConfirmed:= @MPUcfg_save;
          AddItemToMenu (BGUmenu,Bi);

          for j:= lo_MPUadr to hi_MPUadr do
            begin
              s:= delchar(ByteToHex(j),['$']);
              if s[1]='0' then s:= copy(s,2,1)+' ';
              it:= New(PSwitchB,Init(' åèì '+s+' ', @MPUs^[j].bgu,i,nil));
              AddItemToMenu (Bi,it)
            end
        end;

      _BGUmenu:= BGUmenu
    end;