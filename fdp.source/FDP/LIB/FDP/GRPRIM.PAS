{$I comp.h}

{$IFDEF MAPY}
   {$DEFINE DRAW}
{$ENDIF}

{
  Zatial sa tryp mapy odvadza od headfile.line_prior, pretoze nie je na to vyclenena zvlastna polozka.
  Oproti originalu v RDP sa meni filzofia tak, ze skoro kazdy objekt moze byt i fillovaci.

  Prerobit farbu podla farby mapy uvedenej v subore
}

unit GrPrim;


interface


   uses   TypeDef,
          dyn_zoz, DOS,
          {$I unit_gr.h},
          ZemSur, Bod_def;


   const  mark_typ: bool = true;
          mark_txt: bool = true;
          mark_8x8: bool = false;

          ext_SYM  = '.sym';
          ext_MAP  = '.map';

          MAPSCROLL : bool = false;


   var    SYMpalette : array[0..$FF] of byte;

          {$I gr_cnst.h}     { format mapy, farby            }
          {$I gr_type.h}     { typy, zoznamy                 }
          {$I gr_objects.h}  { graficke primitiva            }
          {$I gr_maps.h}     { mapa s grafickymi primitivami }

          {$I gr_func.h}


implementation

uses  str0, math, io, keyb,
      FIR_def, Body, MapyDef, Vypocty;


const mapa_cl: array[0..15] of word = (0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15);


{$I usecka.inc}     { vypocet najblizsieho bodu }

{$I gr_.inc     }   { zoznamy  }

{$I gr_obj.inc  }   { TGrOb    }
{$I gr_poly.inc }   { TPoly    }
{$I gr_krvys.inc}   { TKrVys   }
{$I gr_kruz.inc }   { TKruz    }
{$I gr_suskr.inc}   { TSusKruz }
{$I gr_susaz.inc}   { TSusAzim }
{$I gr_stsie.inc}   { TStSiet  }
{$I gr_marke.inc}   { TMarker  }

{$I gr_mapa0.inc}   { subory   }
{$I gr_mapa1.inc}   { TMapa    }


{$I regular.inc}


{$IFDEF MAPY}
begin
  BodXY:= _BodXY_;
{$ENDIF}
end.