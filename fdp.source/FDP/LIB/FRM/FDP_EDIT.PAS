(*-------------------------------------------------------------------*)
(* LETVIS FDP - Formulare pre EDD                                    *)
(* (c) Ales Kosice 1994  (ab)                                        *)
(*-------------------------------------------------------------------*)
{$I comp.h}

{ Formular pre FDP ponukne Save a Send.
  Po potvrdeni sa vola i funkcia add, ktora rozosle plan na EST stanice (EDD,IDD,SRD).
  Send sposobi odoslanie planu na nadriadeny server (moze byt len jeden).
  V pripade OPL sa na podriadne stanice rozosle len, ak sa posle na server,
  zatial nemoze byt OPL nadriadne inemu OPL, ak bude, potom sa dodefinuje
         -----------------------------------
  do TFDP_form ($IFDEF OPL) distribute ($ENDIF) a bude sa volat po send
  alebo po save, podla nastavenia globalnej premennej.

  Teraz na OPL su ako podriadene pripojitelne len EST stanice.

  Save sa vykona vzdy po potvrdeni.
}


unit FDP_edit;

interface


     uses  TypeDef,
           sets,
           {$I unit_gr.h},
           {$I unit_net.h},
           Views, Events, Edit, Button, Lists,
           Body,
           _FDP_def;


     {$I FDP_ed_i.h} { info        }
     {$I FDP_ed_t.h} { info        }

     {$I FDP_ed1.h}  { TFDP_AForm0 }
     {$I FDP_ed2.h}  { TFDP_AForm  }
     { I FDP_ed3.h}  { TREQ_FDP    }


implementation

uses mouse, keyb, str0, math, mess, utime,
     DOS, BIOS, IO, DB,
     CMs, CM, Objects, Dialog, help_def, Help, Scroll, Menus, App, Msg,
     _L4_def, _MTK_2,
     Archiv, form_SYS,
     FDP_msg;


{$I FDP_ed1.inc}  { TFDP0_AForm }
{$I FDP_ed2.inc}  { TFDP_AForm  }
{ I FDP_ed3.inc}  { TFDP_REQ    }


end.