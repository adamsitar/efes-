      type   TPole12 = array[0..11] of byte;

           { hlavicka v subore }
             THeadFile = record
               Magic_number : long;
               type_line,line_prior,line_color, fill_prior,fill_color, extra_prior,extra_color : word;

               pole12: TPole12
             end;


      type { suradnice bodov su prepocitane zo zemepisnych do realnych }

             PgBod = ^TgBod;
             TgBod  = record
               X,Y : real
             end;

             PgText = ^TgText;
             TgText  = record
               X,Y  : real;
               Ts   : int;
               vet  : PChar
             end;


      type   PZozBod = ^TZozBod;
             TZozBod = object(ListMan)
               procedure ZrusPointer(P: pointer); virtual;
             end;

             PZozText = ^TZozTexT;
             TZozText = object(ListMan)
               procedure ZrusPointer(P: pointer); virtual;
             end;

             PZozMap = ^TZozMap;
             TZozMap = object(ListMan)
               procedure ZrusPointer(P: pointer); virtual;
             end;

