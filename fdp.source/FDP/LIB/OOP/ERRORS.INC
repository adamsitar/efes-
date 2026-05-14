{
‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹
€                                                          €
€ TErrory                                                  €
€‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹€
}

 constructor TError.Init(_title: string; _mess: PChar);
       var   m : TMess;
       begin
         m[0]:= strnew(_mess);
         if _title='' then _title:= msgERR;
         inherited Init(_title,'',
                        nil,nil,
                        0,0,
                        @m,1,
                        white,red,
                        @mess.BeepErr,nil,
                        waitERR*18, nil,nil, 0,
                        nil,nil
                       );
         strdispose(m[0])
       end;


 constructor TError.Say(_title: string; _mess: PChar);
       var   _Event : TEvent;
       begin
         Init(_title,_mess);
         Run(_Event);
         Done
       end;


 constructor TPosError.Say(_x,_y: int; _title: string; _mess: PChar);
       var   _Event : TEvent;
       begin
         inherited Init(_title,_mess);
         {MoveRel(_x-x0,_y-y0);}
         Run(_Event);
         Done
       end;
