type   PHelp = ^THelp;
       THelp = object(OViewerStreamFile)

         is_comment : bool;
         is_sorry   : bool;

         max_len    : byte;

         constructor Init(_fn: string; _sorry: bool);
         destructor  Done; virtual;

         procedure   Help(key : string);
         procedure   Info(tit: string);

         function    items : word;
         function    get_item(i: word) : string;
         function    find_item(_fn: string; key: string): string;

       end;


constructor THelp.Init(_fn: string; _sorry: bool);
      begin
        inc(help_open);

        is_comment:= true;
        is_sorry:= _sorry
      end;

destructor  THelp.Done;
     begin
       dec(help_open)
     end;

procedure THelp.Help(key : string);
    begin
    end;

procedure THelp.Info(tit: string);
    begin
    end;


function THelp.items : word;
   begin
   end;

function THelp.get_item(i: word) : string;
   begin
   end;

function THelp.find_item(_fn: string; key: string): string;
   begin
   end;
