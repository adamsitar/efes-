(*-------------------------------------------------------------------*)
(* Dynamicky zoznam                                                  *)
(* (c) Ales-aci Kosice 1993,94 (kt,ig,ab)                            *)
(*-------------------------------------------------------------------*)

{$I comp.h}

unit dyn_zoz; { obousmerny dynamicky seznam prvku }


interface


    uses  crt, typedef;


         { -------------------------- }
         { 1. typ                     }
         { -------------------------- }

    type  NodePtr=^Node;
          Node= object
            Fwd,Back: NodePtr;
            constructor Init;
            destructor  Done; virtual;
          end; { Node }

          ListPtr=^List;
          List=object
            Top,Bot,Curr: NodePtr;

            constructor Init;
            destructor  Done; virtual;

            procedure   LinkTop( N: NodePtr);
            procedure   LinkBot( N: NodePtr);
            procedure   LinkCurr(N: NodePtr); { Novy zaznam bude aktualnim }

            { Trideni metodou Bubble Sort }
            function    Less(N1,N2: NodePtr): boolean; virtual; { Kriterium }
            procedure   Sort;

            { Odstrani zaznam ze seznamu, a neuvolni pamet, pro staticke promenne }
            procedure   Unlink(N: NodePtr);

            procedure   Delete; { Deletes current record }

            { Traverse projde cely seznam a pro kazdy uzel provede Action }
            procedure   Action(Node: NodePtr); virtual;
            procedure   Traverse;

            procedure   GoUp;
            procedure   GoDown;
            procedure   GoTop;
            procedure   GoBot;
          end; { List }



         { -------------------------- }
         { 2. typ                     }
         { -------------------------- }

    type  PrvSeznPtr=^PrvSezn;
          PrvSezn=record
	     MujPrv:pointer;
	     Predch,Dalsi:PrvSeznPtr;
          end;

         {⁄ƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒø}
         {≥  LISTMAN       ≥}
         {¿ƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒŸ}

          PListMan = ^ListMan;
          ListMan  = object

	    Prvni,Posl,Akt: PrvSeznPtr;
	    PocetPrvku    : int;
           {size_of_me    : word;}


	    constructor Init;
           {constructor Init(_size_of_me: word);}
	    destructor  Done; virtual;

            function    is: bool;

	    procedure   PridejNaKonec  (P: pointer);
	    procedure   PridejNaZacatek(P: pointer);

	    procedure   JdiNaZacatek;
	    procedure   JdiNaKonec;

	    procedure   JdiNaDalsi (var Konec: bool);
            function    JdiNaDalsi_: bool;
	    procedure   JdiNaPredch(var Zacatek: bool);

	    function    DejPrvni: pointer;
	    function    DejZrusPrvni: pointer;
	    procedure   ZrusPrvni;

	    function    DejDalsi: pointer;
	    function    DejPredch: pointer;
	    function    DejPrvek(P: pointer): pointer;
	    function    DejPrvekCislo(I: int): pointer;
	    procedure   JdiNaCislo(I: int);

	    procedure   VlozPredAkt(P: pointer);
	    procedure   VlozZaAkt  (P: pointer);

	    procedure   ZrusPointer(P: pointer); virtual;  { zrusi obsah pointeru }
	    procedure   ZrusAktualni;
	    procedure   ZrusVsechny;
	    procedure   ZrusPrvek  (P: pointer);
	    function    VyjmiAktPrvek: pointer; { vrat P a zrus }
	    function    VyjmiPrvek(Ja:pointer): pointer;

	    function    DejPocet: int;
	    function    NajdiPrvek(Ukaz:pointer): bool;

	    function    DejAktPrvek: pointer; virtual;
	    procedure   UlozAktPrvek(P: pointer);virtual;
	    procedure   Vypis;
          end;


implementation


{
‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹
€                                                          €
€ 1. List                                                  €
€‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹€
}


{
‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹
€                               €
€ Node                          €
€‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹€
}

constructor Node.Init;
begin
  Fwd:=Nil; Back:=Nil;
end;

destructor Node.Done;
begin
  Abstract;
end;



{
‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹
€                               €
€ List                          €
€‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹€
}

constructor List.Init;
begin
  Top:=Nil; Bot:=Nil; Curr:=Nil;
end;

destructor List.Done;
begin
  while Top<>Nil do
  begin
    Curr:=Top;
    Top :=Top^.Fwd;
    Dispose(Curr,Done);
  end;
  Curr:=Nil;
  Bot :=Nil;
end;

function List.Less;
begin
  Abstract;
end;

procedure List.Sort;
var
  EOS: boolean;
  Tmp: NodePtr;
begin
  if Top<>Nil then
  repeat
    EOS:= True;
    Curr:=Top;
    while Curr^.Fwd<>Nil do
    begin
      if Less(Curr^.Fwd,Curr) then
      begin
        Tmp:=Curr^.Fwd;
        Unlink(Curr^.Fwd);
        LinkCurr(Tmp);
        EOS:=False;
      end;
      Curr:=Curr^.Fwd;
    end;
  until EOS;
end; { Sort }

procedure List.LinkTop(N: NodePtr);
begin
  if Top=Nil then
  begin
    Top:=N;
    Top^.Back:=Nil;
    Top^.Fwd:=Nil;
    Curr:=Top;
    Bot:=Top;
  end else
  begin
    N^.Back:=  Nil;
    N^.Fwd :=  Top;
    Top^.Back:=N;
    Top:=N;
  end;
end; { LinkTop }

procedure List.LinkBot(N: NodePtr);
begin
  if Bot=Nil then
  begin
    Bot:=N;
    Bot^.Back:=Nil;
    Bot^.Fwd:=Nil;
    Top:=Bot;
    Curr:=Bot;
  end else
  begin
    N^.Fwd :=Nil;
    N^.Back:=Bot;
    Bot^.Fwd:=N;
    Bot:=N;
  end;
end; { List.LinkBot }

procedure List.LinkCurr(N: NodePtr);
begin
  if Curr=Nil then
  begin
    Curr:=N;
    Curr^.Back:=Nil;
    Curr^.Fwd:=Nil;
    Top:=Curr;
    Bot:=Curr;
  end else
  begin
    N^.Back:=Curr^.Back;
    N^.Fwd:=Curr;
    Curr^.Back^.Fwd:=N;
    Curr^.Back:=N;
    Curr:=N;
    if Curr^.Back=nil then Top:=Curr;
  end;
end; { List.LinkCurr }

procedure List.Traverse;
var C: NodePtr;
begin
  C:=Top;
  while C<>Nil do
  begin
    Action(C); C:=C^.Fwd;
  end;
end;

procedure List.Unlink(N: NodePtr);
begin
  if N<>Nil then
  begin
    if N^.Fwd <>Nil then
    begin
      N^.Fwd^.Back:=N^.Back;
    end;
    if N^.Back<>Nil then
    begin
      N^.Back^.Fwd:=N^.Fwd;
    end;
    if N=Curr then Curr:=N^.Fwd;
    if N=Top  then Top:= N^.Fwd;
    if N=Bot  then Bot:= N^.Back;
    if (Top=Nil) or (Curr=Nil) or (Bot=Nil) then
    begin
      Top:=Nil; Curr:=Nil; Bot:=Nil;
    end;
  end;
end; { Unlink }

procedure List.Delete;
var Tmp: NodePtr;
begin
  Tmp:=Nil;
  if Curr<>Nil then
  begin
    if Curr^.Fwd <>Nil then
    begin
      Curr^.Fwd^.Back:=Curr^.Back;
      Tmp:=Curr^.Fwd;
    end;
    if Curr^.Back<>Nil then
    begin
      Curr^.Back^.Fwd:=Curr^.Fwd;
      if Tmp=Nil then Tmp:=Curr^.Back;
    end;
    if Curr=Top then Top:=Curr^.Fwd;
    if Curr=Bot then Bot:=Curr^.Back;
    Dispose(Curr,Done);
    Curr:=Tmp;
    if (Top=Nil) or (Curr=Nil) or (Bot=Nil) then
    begin
      Top:=Nil; Curr:=Nil; Bot:=Nil;
    end;
  end;
end; { Delete }

procedure List.GoUp;
begin
{  POVODNE if (Curr<>Nil) and (Curr^.Back<>Nil) then Curr:=Curr^.Back;}
  if (Curr<>Nil)  then Curr:=Curr^.Back;
end;

procedure List.GoDown;
begin
{  if (Curr<>Nil) and (Curr^.Fwd<>Nil) then Curr:=Curr^.Fwd;}
  if (Curr<>Nil) then Curr:=Curr^.Fwd;
end;

procedure List.GoTop;
begin
  if Top<>Nil then Curr:=Top;
end;

procedure List.GoBot;
begin
  if Bot<>Nil then Curr:=Bot;
end;

procedure List.Action;
begin
  Abstract
end;


{
‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹
€                                                          €
€ 2. List                                                  €
€‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹€
}
{
 ⁄ƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒø
 ≥ METODY OBJ. LISTMAN           ≥
 ¿ƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒŸ
}

constructor ListMan.Init;
begin
  Prvni:= nil; Posl:= nil; Akt:= nil;
  PocetPrvku:= 0;
  {size_of_me:= 0}
end; {proc}

{constructor ListMan.Init;
begin
  Init0;
  size_of_me:= _size_of_me
end;  proc}

destructor ListMan.Done;
begin
  if not(Prvni=nil) then ZrusVsechny;
end; {proc}


function ListMan.is: bool;
   begin
     is:= PocetPrvku>0
   end;


procedure ListMan.PridejNaKonec(P:pointer);
var Novy:PrvSeznPtr;
begin
  new(Novy);
  Novy^.Dalsi:=nil;
  if Prvni=nil then
     begin
       Prvni:=Novy;
       Posl:=Novy;
       Novy^.Predch:=nil;
     end
  else begin
	 Posl^.Dalsi:=Novy;
	 Novy^.Predch:=Posl;
	 Posl:=Novy;
       end;
  Akt:=Novy;
  PocetPrvku:=PocetPrvku+1;
  self.UlozAktPrvek(P);
end; {proc}

procedure ListMan.PridejNaZacatek(P:pointer);
var Novy:PrvSeznPtr;
begin
  new(Novy);
  Novy^.Predch:=nil;
  if Prvni=nil then begin
	  Prvni:=Novy;
	  Posl:=Novy;
	  Novy^.Dalsi:=nil;
  end
  else begin
	  Prvni^.Predch:=Novy;
	  Novy^.Dalsi:=Prvni;
	  Prvni:=Novy;
  end;
  Akt:=Novy;
  Self.UlozAktPrvek(P);
  PocetPrvku:=PocetPrvku+1;
end; {proc}


procedure ListMan.JdiNaZacatek;
    begin
      if Akt=nil then Exit;
      Akt:=Prvni;
    end; {proc}

procedure ListMan.JdiNaKonec;
    begin
      if Akt=nil then Exit;
      Akt:=Posl;
    end; { proc}

procedure ListMan.JdiNaDalsi(var Konec: boolean);
    begin
      Konec:= (Akt=nil) or ((Akt<>nil) and (Akt^.Dalsi=nil));
      if not Konec then Akt:= Akt^.Dalsi
    end; { proc }

function ListMan.JdiNaDalsi_: bool;
   var   konec: bool;
   begin
     JdiNaDalsi(konec);
     JdiNaDalsi_:= konec
   end;

procedure ListMan.JdiNaPredch(var Zacatek: boolean);
    begin
      if Akt=nil then Exit;
      if Akt^.Predch=nil then Zacatek:=true
      else begin
	     Zacatek:=false;
	     Akt:=Akt^.Predch;
 	   end;
    end; {proc}


function ListMan.DejPrvni:pointer;
var P:pointer;
begin
	DejPrvni:=Prvni;
	if not(Prvni=nil) then begin
		Akt:=Prvni;
		DejPrvni:=Akt^.MujPrv;
	end;
end;

function ListMan.DejZrusPrvni:pointer;
var P:pointer;
begin
	DejZrusPrvni:=Prvni;
	if not(Prvni=nil) then begin
		DejZrusPrvni:=Prvni^.MujPrv;
		ZrusPrvni;
	end;
end;

procedure ListMan.ZrusPrvni;
var Pom:PrvSeznPtr;
begin
	if Prvni=nil then Exit;
	Pom:=Prvni^.Dalsi;
	if not(Pom=nil) then Pom^.Predch:=nil;
	ZrusPointer(Prvni^.MujPrv);
	dispose(Prvni);
	Akt:=Pom;
	Prvni:=Pom;
	dec(PocetPrvku);
end; {proc}



function ListMan.DejDalsi:pointer;
begin
	if Prvni=nil then DejDalsi:=nil
	else begin
		DejDalsi:=Akt^.Dalsi;
		if not(Akt^.Dalsi=nil) then begin
			Akt:=Akt^.Dalsi;
			DejDalsi:=Akt^.MujPrv;
		end;
	end;
end;

function ListMan.DejPredch:pointer;
begin
	if Prvni=nil then DejPredch:=nil
	else begin
		DejPredch:=Akt^.Predch;
		if not(Akt^.Predch=nil) then begin
			Akt:=Akt^.Predch;
			DejPredch:=Akt^.MujPrv;
		end;
	end;
end;

{ najde prvek }
function ListMan.DejPrvek(P:pointer):pointer;
var Pom:pointer;
begin
	Pom:=DejPrvni;
	while (not(Pom=nil)) and (not(Pom=P)) do
		Pom:=DejDalsi;
	DejPrvek:=Pom;
end;

function ListMan.DejPrvekCislo(I:int):pointer;
var Pom:pointer;
	I1:int;
begin
	I1:=1;
	Pom:=DejPrvni;
	while (not(Pom=nil)) and (not(I=I1)) do begin
		Pom:=DejDalsi;
		inc(I1);
	end;
	DejPrvekCislo:=Pom;
end;


procedure ListMan.JdiNaCislo(I:int);
var I1:int;
	 Konec:boolean;
begin
	JdiNaZacatek;
	if Prvni=nil then Exit;
	I1:=1;
	Konec:=false;
	while (I1<I) and (not(Konec)) do begin
		JdiNaDalsi(Konec);
		inc(I1);
	end;
end;


procedure ListMan.ZrusAktualni;
    var   Pom: PrvSeznPtr;
    begin
      if Akt=nil then Exit;
      if Akt^.Predch=nil then
         begin
	   Prvni:= Akt^.Dalsi;
	   Pom:= Akt^.Dalsi;
         end
      else begin
	     Akt^.Predch^.Dalsi:= Akt^.Dalsi;
	     Pom:= Akt^.Predch;
           end;
      if Akt^.Dalsi=nil then Posl:= Akt^.Predch
      else Akt^.Dalsi^.Predch:= Akt^.Predch;
      ZrusPointer(Akt^.MujPrv);
      dispose(Akt);
      Akt:= Pom;
      PocetPrvku:= PocetPrvku-1;
    end;

procedure ListMan.ZrusVsechny;
    var   Pom: PrvSeznPtr;
    begin
      if Akt=nil then Exit;
      while not (Prvni=nil) do
        begin
          Pom:= Prvni;
          Prvni:= Prvni^.Dalsi;
          ZrusPointer(Pom^.MujPrv);
          dispose(Pom);
        end;
      Posl:=nil;
      Akt:=nil;
      PocetPrvku:=0;
    end; {proc}

procedure ListMan.ZrusPointer(P:pointer);  { zrusi obsah pointeru }
begin
  {if size_of_me<>0 then FreeMem(P,SizeOf(size_of_me))}
end;

procedure ListMan.ZrusPrvek(P:pointer);
    begin
      if NajdiPrvek(P) then ZrusAktualni;
    end;

function ListMan.VyjmiAktPrvek:pointer;
var Pom:PrvSeznPtr;
begin
	if Akt=nil then Exit;
	if Akt^.Predch=nil then begin
		Prvni:=Akt^.Dalsi;
		Pom:=Akt^.Dalsi;
	end
	else begin
		Akt^.Predch^.Dalsi:=Akt^.Dalsi;
		Pom:=Akt^.Predch;
	end;
	if Akt^.Dalsi=nil then Posl:=Akt^.Predch
	else Akt^.Dalsi^.Predch:=Akt^.Predch;
	VyjmiAktPrvek:=DejAktPrvek;
	dispose(Akt);
	Akt:=Pom;
	PocetPrvku:=PocetPrvku-1;
end; {proc}

function ListMan.VyjmiPrvek(Ja:pointer):pointer;
var Pom:PrvSeznPtr;
begin
	if NajdiPrvek(Ja) then VyjmiPrvek:=VyjmiAktPrvek
	else VyjmiPrvek:=nil
end;

function ListMan.DejPocet:int;
   begin
     DejPocet:=0;
     if Akt=nil then Exit;
     DejPocet:= PocetPrvku;
   end;

procedure ListMan.VlozPredAkt(P:pointer);
var Novy:PrvSeznPtr;
begin
	if (Prvni=nil) then Exit;
	new(Novy);
	if Akt^.Predch=nil then Prvni:=Novy
				else Akt^.Predch^.Dalsi:=Novy;
	Novy^.Predch:=Akt^.Predch;
	Novy^.Dalsi:=Akt;
	Akt^.Predch:=Novy;
	Novy^.Dalsi:=Akt;
	Akt:=Novy;
	Self.UlozAktPrvek(P);
	PocetPrvku:=PocetPrvku+1;
end;

procedure ListMan.VlozZaAkt(P:pointer);
var Novy:PrvSeznPtr;
begin
	if (Prvni=nil) then Exit;
	new(Novy);
	if Akt^.Dalsi=nil then Posl:=Novy
			  else Akt^.Dalsi^.Predch:=Novy;
	Novy^.Dalsi:=Akt^.Dalsi;
	Novy^.Predch:=Akt;
	Akt^.Dalsi:=Novy;
	Akt:=Novy;
	Self.UlozAktPrvek(P);
	PocetPrvku:=PocetPrvku+1;
end;

function ListMan.DejAktPrvek:pointer;
   begin
     if (Akt=nil) then DejAktPrvek:=nil
     else DejAktPrvek:= Akt^.MujPrv;
   end;

procedure ListMan.UlozAktPrvek(P:pointer);
begin
	if not(Akt=nil) then Akt^.MujPrv:=P;
end;


function ListMan.NajdiPrvek(Ukaz:pointer):boolean;
var Pom:PrvSeznPtr;
begin
	if Prvni=nil then begin
		NajdiPrvek:=false;
		Exit;
	end;
	Pom:=Prvni;
	while (not(Pom=nil)) and (not(Pom^.MujPrv=Ukaz)) do
		Pom:=Pom^.Dalsi;
	if not(Pom=nil) then begin
		 Akt:=Pom;
		 NajdiPrvek:=true;
	end
	else NajdiPrvek:=false;
end;

procedure ListMan.Vypis;
var Pom:PrvSeznPtr;
	I1:int;
begin
	if Prvni=nil then begin
		Exit;
	end;
	ClrScr;
	gotoxy(20,10);
	write('HLEDAM PRVEK,vypis vsech');
	Pom:=Prvni;
	I1:=1;
	while (not(Pom=nil)) do begin
		gotoxy(20,11);write(I1:4);
		inc(I1);
		Pom:=Pom^.Dalsi;
	end;
end;


end.