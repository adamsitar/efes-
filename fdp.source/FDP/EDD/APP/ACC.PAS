(*-------------------------------------------------------------------*)
(* ACC  - uz schvalene plany                                         *)
(* 1992,96                                                           *)
(*-------------------------------------------------------------------*)
{$I comp.h}


unit ACC;


interface


    uses  TypeDef,
          IO, {$I unit_gr.h},
          {$I unit_oop.h}, Lists,
          Bod_def, Body,
          _L4_def, _FDP_def, _FPL_def, _PLAN, _STRIP,
          Board, ACC_ini;


    {$I acc_cnst.h}
    {$I acc_title.h}

    {$I acc1.h}    { TtitACC }
    {$I acc2.h}    { TlstACC }
    {$I acc3.h}    { TwinACC }

    function   GROUPs_menu_init(title: string): PSubMenu;
    procedure  mnuGROUPs_done(O: PObject; var _Event: TEvent); far;

    var   winACC: PwinACC;

    procedure  formular_TABLET;


implementation

uses  _check, bios, mem, dos, keyb, mouse, str0, math, sort, sets, msg,

      NET_def,

      {$IFDEF SECTORS}    Sector,
      {$ENDIF}

      {$IFDEF FPL0}       _FPL, _FPLc, _FPLm,
      {$ENDIF}

      {$IFDEF TABLET_ZAM} _ZAM,
      {$ENDIF}
      {$IFDEF TABLET_PRS} _PRS,
      {$ENDIF}
      {$IFDEF TABLET_MET} _MET,
      {$ENDIF}

      FDP_ap, PROP, GUI;


{ ------------------------------
  suradnice na tabuli stripov
  ------------------------------
}
const clLstItem  = Cyan;
      clLstSc    = LightCyan;
      clLstAct   = Yellow;


const { Niektore konstanty natrepane natvrdo a niektore zdanlivo bez suvislosti,
        ale co ked nie je cas ?
      }

      dx_lista    = {$IFNDEF EDD_20} 20 {$ELSE} 23 {$ENDIF};  { lista medzi stlpcami }
      dy_medzera  = {$IFNDEF EDD_20} 3  {$ELSE} 4  {$ENDIF};
      dxof_strip  = {$IFNDEF EDD_20} 23 {$ELSE} 26 {$ENDIF};  { posun stripu oproti zaciatku stlpca ...  }

      dx_stlpca   : array[low(T_strip)..high(T_strip)] of int  =  { sirka medzi stlpcami }
                    (dx_lista+1+2+dx_mstrip+2, { 313 /  }
                     dx_lista+1+2+dx_sstrip+2, { 418 /  }
                     dx_lista+1+3+dx_fstrip+3  { 628 /  }
                    );

      dxof_stlpca : array[low(T_strip)..high(T_strip)] of byte =  { vystredenie stlpcov  }
                    (1,1,0);
      dxof_sbu    : array[low(T_strip)..high(T_strip)] of int  =  { posun sb v stlpci    }
                    {$IFNDEF EDD_20} (1,1,1) {$ELSE} (1,0,-1) {$ENDIF};


var   max_rdk     : int;

      dx_stlpec   : int;  { sirka stlpca podla mini - full         }
      dxof_stlpec : byte;
      dxof_sb     : int;

      _x_strip    : int;  { zaciatok vypisu stripov - AKTUALIZOVAT ! }
      _y_strip    : int;  {  ( urcuje poziciu Header - majaka )      }

      dy_strip    : int;  {const dy_strip    = _FDP_def.dy_strip;}

const dx_strip    : int = 0;  { sirka stripu                             }


function stlpec_xi(stl: int): int;
   begin
     stlpec_xi:= stl*dx_stlpec + dxof_stlpec
   end;


{ ------------------------------
  polozka NDB na tabuli stripov
  ------------------------------
}
 {$I ACC1.inc}  { nadpis zoznamu  }
 {$I ACC2.inc}  { polozka zoznamu }

{ ------------------------------
  tabula stripov
  ------------------------------
}
 { I tablet.frm}
 {$I board.frm}
 {$I ACCcfg.inc}

 {$I ACC3.inc}  { zoznam }


{$IFDEF SECTORS}
begin
  proc_SECTOR_chg:= ACC.SECTOR_chg;
{$ENDIF}
end.