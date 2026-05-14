{$I comp.h}

uses  bios,keyb,typedef,io,str0,mess, hodiny,
      {$I gr_unit.h},
      Body, help
      (*cm,cms, events, objects, menus, app, net_utc,
      Lists,
      _PRS,
      {$I net_unit.h}*);

(*
type  PXApp = ^TXApp;
      TXApp = object(TApp)
        procedure   HandleEvent(var _Event: TEvent); virtual;
      end;

var   Ap: PXApp;


function filter(s: string): bool;
   var   i : int;
   begin
     s:= uni_str(getstr (s,2,[';']));
     i:= pos(przn_nadriadene_letisko,s);
     if i>0 then s:= getstr(copy(s,i+1,length(s)-i),1,[' ',',']) else s:= '';
     filter:= (s='') or toto_letisko(s) or podriadene_letisko(s)
   end;

procedure TXApp.HandleEvent(var _Event: TEvent);
    var   s : string;
    begin
      {if isKey (_Event,'?') then  s:= _get_item(10,10,@fnRTE_Mlst,[],1,false,@filter);}
      _handle_event_PRS (_Event,@self,nil);
      inherited HandleEvent(_Event);
    end;


var   SERVERmenu : PBarMenu;

function SERVERmenu_init: PBarMenu;
   begin

     SERVERmenu:= New(PBarMenu);
     SERVERmenu_init:= SERVERmenu;
     SERVERmenu^.Init('',

       Item2('~ ~FDP/S ', kbCtrlF1, cmAbout,

       nil )

     );

   end;


var  cis : UNIX_time;
     dt  : TDatum;

*)


begin
  InitBGI;
  _infop('f:\3.pas', 'xx', true,false);

  {this_airbase;}

  {Ap:= New(PXApp);
  Ap^.Init(Ap,@SERVERmenu_init,nil,' ', '(c)');
  Ap^.Run(MainEvent);
  Dispose(Ap,Done)}

 {unix2dos(913946520,dt);
  cis:= dos2unix(dt);}

  {Ap:= New(PXApp);
  Ap^.Init(Ap,@SERVERmenu_init,nil,' ', '(c)');
  NET_init(nil);
  if NET<>nil then NET^.Owner:= @Ap;
  NET_init(New(PFDP_NET,Init));
  STATUS_init(Ap);
  HODINY_init(Ap,100,101);
  Ap^.Run(MainEvent);
  Dispose(Ap,Done)
 }
end.