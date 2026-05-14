(*-------------------------------------------------------------------*)
(* Objects 1.0                                                       *)
(* 1994                                                              *)
(*-------------------------------------------------------------------*)
{$I comp.h}

{$X+,I-,S-,P-}

unit Objects;


interface


    uses   TypeDef,
           Events;


    const   MailBox__SIZE = 1024;         { velkost schranky pre spravy }

           { nasledujuce dve premenne moze modifikovat len program }
    var     MailBox    : pointer;         { ukazovatel na schranku      }
    const   MainAppPtr : Ppointer = nil;  { ukazuje na premennu, kde je adresa hlavnehj aplikacie }


    type    TObjectType = (obj_another,obj_view,obj_view_active);


          { ----------------------------------------------- }
          { TObject - prototyp pre clena a majitela skupiny }
          { ----------------------------------------------- }
    type    PObject  = ^TObject;
            PPObject = ^PObject;

          { zasobnik pohladov v skupine, aplikacii        }
            PObjectReg  = ^TObjectReg;
            TObjectReg  = record
              PrevReg   : PObjectReg;
              ObjectPtr : PObject;
            end;


          { Abstraktna trieda Pohlad pre odvodenie objektu na obrazovke }
            TObject = object

               ObjectType: TObjectType;

               {Next     : PView;  }
               {Options  : word;}
               Owner     : PObject;
               EventMask : word;

               Stack     : PObjectReg;  { ukazovatel na vrchol zasobnika lokalnych aplikacii }
               ObjectRP  : PObjectReg;  { ukazovatel na aktualny pohlad }


               constructor Init(_Owner: PObject);
               destructor  Done; virtual;                             { musi byt volany v odvodenom Done  }

               function    isActive: bool;

             { udalosti }
               procedure   LocalMain  (var _Event: TEvent); virtual;
               procedure   GetEvent   (var _Event: TEvent); virtual;
               procedure   HandleEvent(var _Event: TEvent); virtual;
               procedure   Idle       (var _Event: TEvent); virtual;  { dotatocna kontrola pre GetEvent }
               procedure   PutEvent   (var _Event: TEvent); virtual;
               procedure   ClearEvent (var _Event: TEvent);
               procedure   SetCommand (var _Event: TEvent; Command: word);

             { vlastnicke vztahy }
             { a) single member  }
               procedure   PushToStack(_Owner: PObject);              { zaradi Object do stacku vlastnika (Ownera) }

             { b) owner          }
               procedure   PushObject(ObjectPtr: PObject);
               procedure   RemoveObject(var ObjectPtr: PObject; disp_ObjectPtr: bool);

               function    InObject(ObjectPtr: PObject; var O: PObject): bool;

               function    GetObjectReg (V: PObject): PObjectReg;
               function    PrevObjectReg(V: PObjectReg): PObjectReg;
               function    NextObjectReg(V: PObjectReg): PObjectReg;

               {
               procedure   SetPrevObject(var V: PObjectReg; S: PObjectReg); virtual;
               procedure   SetNextObject(var V: PObjectReg; S: PObjectReg); virtual;
               }

               function    streamFN: string; virtual;
               function    streamTXT: bool; virtual;


             { odovzdavanie sprav }
               procedure   Mail (_Whom: PObject; _Command: Word; _ForAll: TNumber;
                                 _mail: pointer; _size: word
                                ); virtual;
               procedure   MailE(var _Event: TEvent;
                                 _Whom: PObject; _Command: Word; _ForAll: TNumber;
                                 _mail: pointer; _size: word
                                ); virtual;
            end;


    procedure send_mail(_From,_Whom: PObject; _Command: Word; _ForAll: TNumber;
                        _mail: pointer; _size: word
                       );

    function  read_mail_s (_Event: TEvent; var s: string): bool;


    type     TProc_vE = procedure(var _Event: TEvent);

          { ----------------------------------- }
          { Cykly s premmenymi typu TObject     }
          { ----------------------------------- }

    type  {  Procedury cyklu s premennymi typu TObject a potomkami }
          {  procedura s parametrom typu PObject }
             TProcPObject = procedure (P: PObject; V: pointer);
          {  logicka funkcia s parametrom typu PObject }
             TBFuncPObject = function (P: PObject): bool;


    procedure  ForEach   (P: pointer; S: PObjectReg; V: pointer); { pre sicke }
    function   FirstThat (F: pointer; S: PObjectReg): PObjectReg; { pre persi }


    const { Private variables }
            Pending     : TEvent = (What: evNothing); { nevybavena udalost }
            Application : PObjectReg = nil;


    type  proc_indicate_process   = procedure (is: int);
          p_proc_indicate_process = ^proc_indicate_process;



implementation

uses  mem, math, IO, CMs;


{ -----------------------------------------
   I(DEI)NICAILIZACIA
  ---------------------------------------- }

constructor TObject.Init(_Owner: PObject);
      begin
        ObjectType := obj_another;
        Stack      := nil;    { vynulovanie zasobnika pohladov   }
        ObjectRP   := nil;

        EventMask  := 0;
        PushToStack(_Owner)   { zaradi Object do stacku vlastnika (ownera) }
      end;

destructor TObject.Done;
     var   O : PObject;
     begin
       while (Stack <> nil) do
         begin
           if Stack^.ObjectPtr<>nil then Dispose(Stack^.ObjectPtr,Done);
           { ak sa bude s ObjectPtr^ znova pracovat,
             mal by sa niekde nastavit na nil
           }
           Pop(Stack)
         end;
       if Owner<>nil then
          begin
            O:= @Self;
            RemoveObject(O,false)
          end
     end;


function TObject.isActive: bool;
   begin
     isActive:= (Application<>nil) and (Application^.ObjectPtr=@Self)
   end;


procedure TObject.LocalMain(var _Event: TEvent);
    begin
    end;


{ -----------------------------------------
   OBSLUHA UDALOSTI
  ---------------------------------------- }

procedure TObject.GetEvent(var _Event: TEvent);
    begin
      if (Pending.What <> evNothing) then
         begin
           _Event:= Pending;
           ClearEvent(Pending)
         end
      else begin
             GetMouseEvent(_Event);
             if (_Event.What = evNothing) then
                begin
                  GetKeyEvent(_Event);
                  if (_Event.What = evNothing) then Idle(_Event)
                end
           end;
    end; { GetEvent }


procedure TObject.Idle(var _Event: TEvent);
    begin
    { dotatocna akcia }
    end;


procedure TObject.ClearEvent(var _Event: TEvent);
    begin
      Events.ClearEvent(_Event,@Self)
    end; { ClearEvent }


procedure TObject.PutEvent(var _Event: TEvent);
    begin
    { vlozi nevybavenu udalost do radu na vybavenie }
      Pending:= _Event;
    end; { PutEvent }


procedure TObject.SetCommand(var _Event: TEvent; Command: word);
    begin
      Events.SetCommand(_Event, @Self, Command)
    end; { TObject.SetCommand }



{ -------------
   HandleEvent
  ------------- }
{
  obsluha prveho pohladu skupiny,
  dorobit preferencie na mazanie/nemazanie Eventu
}

type  PEventRec = ^TEventRec;
      TEventRec = record
         Prev: PEventRec;
         evP : PEvent;
      end;

const EventRec : PEventRec = nil; {TempEvent: PEvent = nil;}

var   TempEvent: TEvent;


function handle_object(V: PObject): bool; far;
   var   temp_event: TEvent;
   begin
     temp_event:= TempEvent; {EventRec^.evP^;}
     V^.HandleEvent(temp_event);
     handle_object:= temp_event.What <> TempEvent.What; {EventRec^.evP^.What;}
     TEvent(TempEvent):= temp_event {EventRec^.evP^;}
   end;

procedure TObject.HandleEvent(var _Event: TEvent);
    var   Temp: PEvent;

    begin

      if (_Event.What=evNothing) then Exit;

      if ObjectRP<>nil then
         begin
           ObjectRP^.ObjectPtr^.HandleEvent(_Event);
           if (_Event.What=evNothing) then Exit
         end;

      {if TempEvent=nil then New(TempEvent);
      if @_Event = @TempEvent then
         begin
          Push(EventRec,@_Event); EventRec^.evP^:= _Event;
         end;
      }

      if Stack<>nil then
         begin
           TEvent(TempEvent):= _Event;
           FirstThat(@handle_object,Stack);
           _Event:= TempEvent
         end;

      {Dispose(TempEvent);
      if EventRec^.evP^ _Event:= EventRec^.evP^; Pop(EventRec); Dispose(Temp)
      }
    end; { TGroup.HandleEvent }





{ -----------------------------------------
   VLASTNICKE VZTAHY
  ----------------------------------------
}

{ zalozenie svojej adresy do Stack-u pohladu
}
procedure TObject.PushToStack(_Owner: PObject);
    begin
      Owner:= _Owner;
      if (Owner<>nil) and (Owner<>@Self) then Push(Owner^.Stack,@Self);
    end; { PushToStack }


{ vlozi pohlad Object alebo Group do vlastnickej skupimy
}
procedure TObject.PushObject(ObjectPtr: PObject);
    begin
      ObjectPtr^.PushToStack(@Self);  { zaradi Object do stacku vlastnika (ownera) }
    end; { PushObject }


procedure TObject.RemoveObject(var ObjectPtr: PObject; disp_ObjectPtr: bool);
    var   P,S: PObjectReg;
    begin
      if ObjectPtr=nil then Exit;

      S:= Stack; P:= S;
      while (S<>nil) and (S^.ObjectPtr<>ObjectPtr) do
        begin
          P:= S;
          S:= S^.PrevReg
        end;
      if (S=nil) then Exit;

      if S<>P then P^.PrevReg:= S^.PrevReg
      else Stack:= S^.PrevReg;                { bol posledny }

      if disp_ObjectPtr then
         begin
           Dispose(ObjectPtr,Done);
           ObjectPtr:= nil
         end;
      Dispose(S)
    end;


function TObject.InObject (ObjectPtr: PObject; var O: PObject): bool;
   var   S: PObjectReg;
   begin
     O:= nil;
     S:= Stack;
     while
            (S<>nil)
        and (S^.ObjectPtr<>ObjectPtr)
        and (not S^.ObjectPtr^.InObject(ObjectPtr,O))
        and (O=nil)
     do S:= S^.PrevReg;

     if (S<>nil) and (S^.ObjectPtr=ObjectPtr) then O:= @Self;
     InObject:= O<>nil
   end;


{
function SearchForObject(S,V: PObjectReg; var T,N: PObjectReg): bool;
   begin
     T:= S;
     while (T<>nil) and (T<>V) do
       begin
         N:= T;
         T:= T^.PrevReg;
       end;
     if T=nil then SearchForObject:= false   dosiahol poslednu polozku
     else SearchForObject:= true
   end;  SearchForObject
}


{
  zisti polohu v zasobniku pre pohlad V^ vlastnika Group
}
function TObject.GetObjectReg(V: PObject): PObjectReg;
   var   S: PObjectReg;
   begin
     if V<>nil then
        begin
          S:= Stack;
          while (S<>nil) and (S^.ObjectPtr<>V) do S:= S^.PrevReg
        end
     else S:= nil;
     GetObjectReg:= S
   end; { GetObjectReg }


{
  vyberie predchazajuci pohlad zo zasobnika pred V pohladom (aktualnym);
  ak je V dnom zasobnika, potom vrati vrchol - Stack, (pretecie)
  smerom ku dnu - ku prvemu ulozenenu pohladu
}
function TObject.PrevObjectReg(V: PObjectReg): PObjectReg;
   begin
     if V<>nil then
        if V^.PrevReg<>nil then PrevObjectReg:= V^.PrevReg
        else PrevObjectReg:= Stack
     else PrevObjectReg:= nil
   end; { PrevObjectReg }


{
  vyberie nasledujuci pohlad zo zasobnika za V pohladom (aktualnym),
  smerom ku vrcholu - ku poslednemu ulozenenu pohladu,
  ak je V poslednym ulozenym pohladom, vrati prvy ulozeny pohlad
}
function TObject.NextObjectReg(V: PObjectReg): PObjectReg;
   var   temp, ii: PObjectReg;
   begin
     if V<>nil then
        begin
          ii:= Stack;
          if V=Stack then
               begin
                 while (ii<>nil) and (ii^.PrevReg<>nil) do ii:= ii^.PrevReg;
                 NextObjectReg:= ii
               end
          else begin
                 temp:= ii;
                 while (ii<>nil) and (ii^.PrevReg<>V) do
                   begin
                     temp:= ii;
                     ii:= ii^.PrevReg
                   end;
                 NextObjectReg:= ii
               end
        end
     else NextObjectReg:= nil
   end; { NextObjectReg }



{ -------------------------------------------------------

procedure TObject.SetPrevObject(var V: PObjectReg; S: PObjectReg);
   begin
     V^.ObjectPtr^.ActiveOff;
     V:= PrevObject(S,V);
     V^.ObjectPtr^.ActiveOn;
   end; SetPrevObject

procedure TObject.SetNextObject(var V: PObjectReg; S: PObjectReg);
   begin
     V^.ObjectPtr^.ActiveOff;
     V:= NextObject(S,V);
     V^.ObjectPtr^.ActiveOn;
   end; SetNextObject
}

function TObject.streamFN: string;
   begin
     streamFN:= ''
   end;

function TObject.streamTXT: bool;
   begin
     streamTXT:= false
   end;


(*function TObject.sort_item(ind: int; p: pointer): pointer;
   begin
     sort_item:= nil
   end;

function TObject.QuickSortIA(ind  : Pints;      { pole indexov (sucast objektu) }
                             obj  : PObject;    { objekt vlastniaci indexy a data }
                             comp : pointer;    { @TBfunc_p2: bool; pre porovnanie }
                             left, right : int; { hranice }

                             data_size : int;
                             disp_data : PProc_p
                            ): bool;
    var   i,j,t : int;
          x_val,i_vaql,j_val : pointer;
          res,r : bool;
    begin
      QuickSortIA:= false;
      if (ind=nil) or (obj=nil) or (comp=nil) then Exit;

      res:= false;
      if (left<right) then
         begin
           i:= left; j:= right;
           getmem(x_val,data_size); fillchar(x_val^,data_size,0);
           getmem(i_val,data_size); fillchar(i_val^,data_size,0);
           getmem(j_val,data_size); fillchar(j_val^,data_size,0);
           x_val:= sort_item([ind^[(left+right) div 2]]);

           repeat
             while (i<=right) and (TBFunc_p2(comp)(arr^[ind^[i]],x_val)) do inc(i);
             while (j>=left ) and (TBFunc_p2(comp)(x_val,arr^[ind^[j]])) do dec(j);
             if i<=j then
                begin
                  t:= ind^[i]; ind^[i]:= ind^[j]; ind^[j]:= t;
                  inc(i); dec(j);
                  res:= true
                end
           until i > j;
           freemem(x_val,data_size);
           freemem(i_val,data_size);
           freemem(j_val,data_size);

           if left < j  then res:= QuickSort_IndArr(ind,arr,comp, left,j)  or res;
           if i < right then res:= QuickSort_IndArr(ind,arr,comp, i,right) or res
         end;
      QuickSort_IndArr:= res
    end; { QuickSort }
*)


{ -----------------------------------------
   VYSIELANIE SPRAV MEDZI OBJEKTAMI
  ---------------------------------------- }


{ adresat musi byt PObject !!!
}
procedure _send_mail(var _Event : TEvent;
                     _From,_Whom : PObject;
                     _Command : Word; _ForAll : TNumber;
                     _mail: pointer; _size: word
                    );

    var   p : pointer;
          a : PObjectReg;

    begin
      if (_Command = cmNil) then Exit;

      SetCommand(_Event,_From,_Command);
      with _Event do
        begin
          What  := evBroadcast;
          From  := _From;
          Whom  := _Whom;

          ForAll:= bool(_ForAll);
          isMail:= true;

          size  := Minimum(_size,MailBox__SIZE);
          getmem(p,_size); Box:= p;
          Move(_mail^,Box^,_size);
          Move(_mail^,MailBox^,size);
        end;

      if _Event.Whom<>nil then PObject(_Event.Whom)^.HandleEvent(_Event);

      { Prehladanie zvysnych aplikacii
      }  if (_Event.Command=_Command) and (Application<>nil) then
           begin
             a:= Application;
             repeat
               if     (a^.ObjectPtr<>nil)
                  and ((_ForAll<>One) or (a^.ObjectPtr<>_Event.Whom))
                  then PObject(a^.ObjectPtr)^.HandleEvent(_Event);
               a:= a^.PrevReg;
             until    (a=nil)
                   or ((_ForAll=One) and (    isCommand(_Event,_Command)
                                           or isCommand(_Event,cmCancel)
                                           or isCommand(_Event,cmClose)
                                         )
                      )
                   or ((_ForAll=All) and (_Event.Command=cmNil));
           end;

      with _Event do freemem(p,_size)
    end;


procedure send_mail(_From,_Whom : PObject;
                    _Command : Word; _ForAll : TNumber;
                    _mail: pointer; _size: word
                   );
    var   _Event : TEvent;
    begin
      _send_mail(_Event, _From,_Whom,_Command,_ForAll, _mail,_size);
    end;


function  read_mail_s (_Event: TEvent; var s: string): bool;
   begin
     s:= '';
     if _Event.Box<>nil then
        begin
          s[0]:= chr(minimum(_Event.size,sizeof(s)-1));
          move(pchars(_Event.box)^,s[1],ord(s[0]))
        end;
     read_mail_s:= s<>''
   end;


procedure TObject.MailE(var _Event: TEvent;
                        _Whom: PObject; _Command: Word; _ForAll: TNumber;
                        _mail: pointer; _size: word
                       );
    begin
      _send_mail(_Event, @Self,_Whom,_Command,_ForAll, _mail,_size);
    end; { TObject.MailE }

procedure TObject.Mail(_Whom: PObject; _Command: Word; _ForAll: TNumber;
                       _mail: pointer; _size: word
                      );
    begin
      send_mail(@Self,_Whom,_Command,_ForAll, _mail,_size);
    end; { TObject.Mail }



{ ------------------------------------------------------------ }
{  CYKLY PRE PREMENNE TYPU GROUP                               }
{ ------------------------------------------------------------ }
{
 cyklus pre vsetky zlozky skupiny;
   P  - lokalna far procedura hlavnej procedury popisujuca,
        ktora metoda Object bude volana;
   S  - zasobnik skupin.
}
procedure ForEach(P: pointer; S: PObjectReg; V: pointer);
    begin
      while (S<>nil) do
        begin
          if (S^.ObjectPtr<>nil) then TProcPObject(P)(S^.ObjectPtr,V);
          S:= S^.PrevReg
        end;
    end; { ForEach }


{
 cyklus pre prvu zlozku skupiny vyhovujuce podmienke;
   P1 - lokalna far procedura hlavnej procedury popisujuca,
        ktora metoda Object bude volana;
   P2 - zasobnik skupin, odovzdavat LEN KOPIU.
}
function FirstThat (F: pointer; S: PObjectReg): PObjectReg;
   begin
     {while (S<>nil) and (not TBFuncPObject(F)(S^.ObjectPtr)) do S:= S^.PrevReg;}
     while (S<>nil) do begin
       if (S^.ObjectPtr<>nil) then
          if TBFuncPObject(F)(S^.ObjectPtr) then break;
       S:= S^.PrevReg
     end;
     FirstThat:= S
   end; { FirstThat }


var SaveExit: pointer;


procedure Mail_done;
    begin
     {$IFDEF DEBUG_EXIT} writeln('Objects'); {$ENDIF}
      FreeMem(MailBox, MailBox__SIZE);
      ExitProc:= SaveExit
    end;

begin
  SaveExit:= ExitProc;
  ExitProc:= @Mail_done;
  GetMem(MailBox, MailBox__SIZE) { MUSI BYT ! }
end.