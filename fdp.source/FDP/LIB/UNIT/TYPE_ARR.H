    const  MAX_BYTEs  = MAX_ARRAY_SIZE div SizeOf(byte);
           MAX_INTs   = MAX_ARRAY_SIZE div SizeOf(int);
           MAX_WORDs  = MAX_ARRAY_SIZE div SizeOf(word);
           MAX_REALs  = MAX_ARRAY_SIZE div SizeOf(real);

           MAX_PTRs   = MAX_ARRAY_SIZE div SizeOf(pointer);

           MAX_PCHARs = MAX_ARRAY_SIZE div SizeOf(PChar);
           MAX_STR15s = MAX_ARRAY_SIZE div (SizeOf(str15)+1);
           MAX_STR40s = MAX_ARRAY_SIZE div (SizeOf(str40)+1);
           MAX_STRs   = MAX_ARRAY_SIZE div (SizeOf(string)+1);


    type { polia
         }
           Tbytes  = array[0..MAX_BYTEs-1] of byte;
           Tchars  = array[0..MAX_BYTEs-1] of char;
           Tbools  = array[0..MAX_BYTEs-1] of bool;
           Twords  = array[0..MAX_WORDs-1] of word;
           Tints   = array[0..MAX_INTs-1]  of int;
           Treals  = array[0..MAX_REALs-1] of real;

           Tptrs   = array[0..MAX_PTRs-1]  of pointer;

           TPChars = array[0..MAX_PCHARs-1] of PChar;
           Tstr15s = array[0..MAX_STR15s-1] of str15;
           Tstr40s = array[0..MAX_STR40s-1] of str40;
           Tstrs   = array[0..MAX_STRs-1]   of string;

         { ukazovatele
         }
           Pbytes  = ^Tbytes;
           Pchars  = ^Tchars;
           Pbools  = ^Tbools;
           Pwords  = ^Twords;
           Pints   = ^Tints;
           Preals  = ^Treals;

           Pptrs   = ^Tptrs;

           PPChars = ^TPChars;
           Pstr15s = ^Tstr15s;
           Pstr40s = ^Tstr40s;
           Pstrs   = ^Tstrs;

         { Character set type
         }
           PCharSet  = ^TCharSet;
           TCharSet  = set of char;

           PPCharSets = ^TPCharSets;
           TPCharSets = array[0..MAX_PTRs] of PCharSet;
