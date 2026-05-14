{$I comp.h} { D-}


unit AStream;


interface


    uses  TypeDef,
          Stream;


    type  PstreamPackedStrings = ^TstreamPackedStrings;
          TstreamPackedStrings = object

           {$IFDEF NOEMS}
            strm   : PPchars;
            poc    : int;
           {$ELSE}
            strs   : TEmsStream; { pole packovanych stringov, neumoznuje zapis }
            offs   : TEmsStream; { offs[i-1] urcuje offset pola a dlzku offs[i]-offs[i-1] }
            is_ems : bool;
           {$ENDIF}
            items  : long;       { pocet poloziek typu string }

            constructor Init;
            destructor  Done; virtual;

            function    add  (s: string): bool;
            function    read (ind: long): string;

            procedure   truncate (ind: long);
          end;


    type  PTxtFileBuffer = ^TTxtFileBuffer;
          TTxtFileBuffer = object(TstreamPackedStrings)
            fn : string;

            {is_init_read,
            is_done_save  : bool;}

            constructor Init(_fn: string);
            destructor  Done; virtual;

            procedure   ReadFile;
            procedure   SaveFile;
          end;


    type  PCopyTxtFileBuffer = ^TCopyTxtFileBuffer;
          TCopyTxtFileBuffer = object(TTxtFileBuffer)
            fn0 : string;

            constructor Init(_fn,_fn0: string);
          end;


    type  PstreamBuffer = ^TstreamBuffer;
          TstreamBuffer = object(TEmsStream)
            constructor Init(MinSize, MaxSize: Longint);

            procedure   add_to_buffer   (var buff; bdlz: word);
            function    read_buffer     (var buff: pchars; var bdlz: word; buff0: bool): bool;
            function    read_buffer_int (pos,max: long; var buff: pchars; var bdlz: word; buff0: bool): bool;
          end;


    type  PstreamArray = ^TstreamArray;
          TstreamArray = object

            is_ems      : bool;

            abuff       : TEmsStream;
            ibuff       : pchars;

            max_items,
            item_size   : word;
            pocet       : int;


            constructor Init(_max_items,_item_size: word);
            destructor  Done; virtual;

            procedure   add  (var p);
            procedure   del  (ind: int);
            procedure   read (ind: long; var p);
            procedure   write (ind: long; var p);

            function    items: int;
          end;


     procedure EMS_test;


implementation

uses  math, mess, str0, io, mem;

{$I EMS_packed_strings.inc}
{$I EMS_buffer.inc}
{$I EMS_array.inc}
{$I EMS_txt.inc}
{ I EMS_file.inc}

procedure EMS_test;
    var   E : TEmsStream;
          r : int;
          nl: bool;
    begin
      nl:= false;
      E.init(1,0);
      r:= E.status;
      E.Done;
      if r<>0 then MessError('EMS memory not avaible...',true,nl)
    end;

{begin
  EMS_test}
end.
