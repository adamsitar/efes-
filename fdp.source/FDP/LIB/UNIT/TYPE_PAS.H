    const  c_true  : boolean = true;
           c_false : boolean = false;
           c_int   : integer = 0;

           NULL = #0;


    type   short   = shortint;
           int     = integer;
           long    = longint;
           bool    = boolean;


           Pbyte    = ^byte;
           Pchr     = ^char;
           Pbool    = ^bool;
           Pint     = ^int;
           Pword    = ^word;
           Plong    = ^long;
           Preal    = ^real;
           Pstring  = ^string;
           Ppchar   = ^pchar;
           Ppointer = ^pointer;

           PText    = ^Text;
           PFile    = ^File;


           U32BIT = long;           { UNSIGNED LONG  }
           S32BIT = long;           { SIGNED  LONG   }

           U16BIT = word;           { UNSIGNED SHORT }
           S16BIT = int;            { SIGNED SHORT   }

           U8BIT  = byte;           { UNSIGNED CHAR  }
           S8BIT  = shortint;       { SIGNED CHAR    }


           str1   = string[1];
           str3   = string[3];
           str4   = string[4];
           str5   = string[5];
           str10  = string[10];
           str12  = string[12];
           str15  = string[15];
           str20  = string[20];
           str40  = string[40];

           ch255  = array [0..255] of char;

           UNIX_time = LongInt;
