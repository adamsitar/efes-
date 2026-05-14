    type   PathStr = string[79];
           ExtStr  = string[3];

           WordRec = record
             Lo, Hi: Byte;
           end;

           LongRec = record
             Lo, Hi: Word;
           end;

           PtrRec = record
             Ofs, Seg: Word;
           end;


    type   TCas = record
             h,m : byte
           end;

           PDatum = ^TDatum;
           TDatum = record
             h,m,s     : byte;    { NEMENIT VELKOSTI POLOZIEK }
             den,mes   : byte;
             rok       : word;
           end;

           PTime = ^TTime;
           TTime = record
             h,m,s: byte
           end;

           PDate = ^TDate;
           TDate = record
             d,m: byte;
             r  : word
           end;


           DOS_date = record
                   year  :word;
                   month :word;
                   day   :word;
                 end;

           DOS_time = record
                   hour  :word;
                   min   :word;
                   sec   :word;
                 end;


    type   Ppb_record = ^Tpb_record;
           Tpb_record = record
             p: pointer;
             b: bool
           end;


    type   PTZdZs = ^TZdZs;
           TZdZs  = record
             st,mn,se : byte
           end;

