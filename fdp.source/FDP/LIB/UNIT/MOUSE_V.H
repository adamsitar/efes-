     const   m_shape       : Tproc = no_action; { procedura pre nastavenie tvaru kurzora }
             m_hide_enable : bool  = true;      { povolenie skrytia mysi po timeoute     }
             mHideTicks    : word  = 200;       { po ... tickoch     }

     const   m_kresli  : bool = true; { globalne povolenie mysi, nesmie byt modifikovane 2x ! }

     var     is_mouse  : byte;        { 0-ak mys nie je instalovana, inac pocet buttonov }
             m_visible : bool;        { viditelna / neviditelna      }

             mouse_status :  record  { posledny udaj o pouziti mysi }
               stat : TMouseChar;    { udaj o suradniciach          }
               curs : TMCursor
             end;

             mbuffer: array[0..maxMouseBuff-1] of TMouseChar;  { buffer naplnany pri stlaceni tlacidla mysi,       }
             mcit: int;  { citaci index                }
             mzap: int;  { zapisovaci index            }

     const   p_zhasni   : TProc  = nil;
             p_rozsviet : TBFunc = nil;
