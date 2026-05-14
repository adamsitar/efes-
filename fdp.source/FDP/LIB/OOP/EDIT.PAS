(*-------------------------------------------------------------------*)
(* Edit 3.9                                                          *)
(* 1993,99                                                           *)
(*-------------------------------------------------------------------*)
{$I comp.h}

{
  - polozky formulara maju pevnu dlzku,
    pouzivaju sa retazce\0 =>
    iny sposob spracovania stringov

  - Pozor pri inicializacii !
     - polozka pre editaciu nesmie mat nulovu dlzku.
     - vsetky polozky nesmu mat legal=setNil

  - Dorobit Scrollovanie ...
  -  -//-   insert sa zapne len pri novom formulari

  - ak sa ponukne list a pos<0 zapise za zapisanu hodnotu, ak >0, nahradi ju novou

  - Uz by som mohol prerobit Edits na EMS,...

}


unit Edit;


interface


     uses   TypeDef,
            {$I unit_gr.h},
            mouse,
            Events, Objects,
            Astream,
            Views, Button, Lists, Dialog, Scroll;


     {$I ed_cnst.h}
     {$I ed_typ.h}

     const  { Ak je vzdialenost dvoch riadkov medzi sebou = dy_pole,
              riadky sa spravaju ako jedno pole, vtedy ale neuvazujem,
              ze v poli sa nachadzaju skip znaky
            }
             dx_pole = 7;
             dy_pole = 10;

             xp_btList = 1;

             ask_zrus_item : bool = false;


     {$I ed_title.h}
     {$I ed_box.h}
     {$I ed_aform.h}
     {$I ed_form.h}
     {$I ed_edit.h}

     {$I ed_edits.h}
     {$I ed_file.h}

     {$I ed_functions.h}


implementation

uses  bios, dos, io, keyb, str0, math, sets, mess, mem, prnt,
      Msg, FDP_msg,
      CMs, help_def, Help, _MTK_2;


{$I edit.inc}

{$I ed_box.inc}    { TBox        }
{$I ed_sform.inc}  { TSingleForm }
{$I ed_aform.inc}  { TAForm      }
{$I ed_form.inc}   { TFormular   }
{$I ed_edit.inc}   { TEditor     }


{ I ed_dbg.inc debug }

{$I ed_edts_.inc}
{$I ed_edts0.inc}  { TEditor     }
{$I ed_edts1.inc}  {  - predefinovany objektik TScroll     }
{$I ed_edts2.inc}  {  - dodefinovane vlastnosti Edit-orov  }

{$I ed_file.inc}

{$I ed_functions.inc}

begin
  clear_form(@Form_s,1,nil)
end. { Edit }