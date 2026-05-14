{ ------------------------------------------------------------------------
   Igorov driver pre BGU/MPU
  ···························

   Unit obsahuje funkcie pre tlacenie stripu
   na  малогабаpитных  печатающих  устpойствaх    (в дальнейшем МПУ)
       malogabaritnych pecatajuscich ustrojstvach (v dalsom MPU)
   cez блок гpуппового упpавления                 (в дальнейшем БГУ)
       blok grupovovo upravlenia                  (v dalsom BGU)
   pocitca triedy JSEP.

   Vyzaduje specialnu kartu, pise sa pre UKBB.

  ------------------------------------------------------------------------
}

{$I comp.h}

{$X+,I-,S-,P-,F+,O-}
{$C FIXED PRELOAD PERMANENT}


unit MPU;


interface


    uses   TypeDef, IO,
           {$I oop_unit.h};


    {$I mpu.h}

    {$IFDEF MPU}
      { Funkcie aplikacie pre inicializaciu, naplnenie buffera a tlac stripu
      }
      procedure MPUclear (adr: byte);
      procedure MPUwrite (adr: byte; x,y: int; s: string);
      function  MPUprint (adr: byte): byte;

      {procedure MPUtest;
      procedure MPUstatus(adr: byte);
      procedure MPUsstatus;}

      function _BGUmenu(title: string): PSubMenu;
    {$ENDIF}


implementation

uses  Crt, BIOS, keyb, math, mess, str0, sets, msg, utime,
      _Check,
     {$I gr_unit.h},
     {$I net_unit.h},
      Hodiny, Archiv;


{$IFDEF MPU}

   const  BGU0fn = 'BGU0.tmp';
          BGU1fn = 'BGU1.tmp';

   const  cm_BGUprint = 0;
          cm_BGUtest  = 1;
          cm_BGUtrbA  = 2;
          cm_BGUreset = 3;
          cm_BGUgril  = 4;


   type   TIMPUbuff = array [0..MAX_ZNAK_MPU-1,0..MAX_RDK_MPU-1] of byte;

   procedure writeln_monitoring; forward;
   procedure writeln_data(adr: byte); forward;
   procedure writeln_status(adr: byte); forward;

   procedure display_status_bgu(bgu: byte); forward;


   {$I mpu.inc}
   {$I mpu_test.inc}
   {$I mpu_lst.inc}
   {$I bgu_dev.inc}
   {$I mpu_set.inc}

begin
  MPUinit;
{$ENDIF}
end.