  {
   Vyber BGU <0,1> po vybrati sa doporucuje spustenie testing-u.
  }
  function BGUgril (bgu: byte): byte;
    var   MyCon: byte;
    begin
      BGUgril:= NOBGU;
      if not (bgu in [lo_BGUadr..hi_BGUadr]) then Exit;

      BGUactive:= bgu;
      asm
        push    ds
        push    ax
        push    dx
        mov     cx,0fh

        mov     ah,cm_BGUgril  { Назначение Горячего комплекта }
        mov     al,BGUactive   { Vyber BGU }
        int     17h

        mov     MyCon,ah
        pop     dx
        pop     ax
        pop     ds
      end;
      BGUgril:= MyCon
    end;

  {
   Funkcia testuje tlaciaren MPU podla adresy <0-F>
   Testovanie popisane v MPU.DOC
   Vracia: to co print a nastavuje byty...
  }
  function MPUdiagnose (adr: byte): byte;
    var    MyCon : byte;
           b1,b2,b3 : byte;
    begin
      MPUdiagnose:= NOBGU;
      if    (adr<lo_MPUadr) or (adr>hi_MPUadr)
         or (not (MPUs^[adr].bgu in [lo_BGUadr..hi_BGUadr]))
            then Exit;

      { Malo by sa prepnut spravne BGU
      } if BGUactive<>MPUs^[adr].bgu then BGUgril(MPUs^[adr].bgu);

      asm
        push    ds
        push    ax
        push    dx

        mov     ah,cm_BGUtest    { Команда "Уточнить состояние"}
        mov     al,adr           { Адpес устpойства  }
        int     17h
        cmp     ah,cm_BGUprint
        mov     MyCon,ah
        mov     b1,al
        mov     b2,dl
        mov     b3,dh

        pop     dx
        pop     ax
        pop     ds
     end;
     with MPUs^[adr] do begin bus0:= b1; bus1:= b2; bus2:= b3 end;
     MPUdiagnose:= MyCon
   end;


  (*
   Funkcia testuje tlaciaren BGU
  }
  function BPUdiagnose (bgu: byte): byte;
    var    MyCon : byte;
           b1,b2,b3 : byte;
    begin
      BPUdiagnose:= NOBGU;
      if (not (bgu in [lo_BGUadr..hi_BGUadr])) then Exit;

      { Malo by sa prepnut spravne BGU
      } if BGUactive<>bgu then BGUgril(bgu);

      asm
        push    ds
        push    ax
        push    dx

        mov     ah,cm_BGUtest    { Команда "Уточнить состояние"}
        mov     al,adr           { Адpес устpойства             }
        int     17h
        mov     MyCon,ah
        mov     b1,al            {   0 БУС  (БГУ)              }
        mov     b2,dl            { 1-й БУС  (МПУ)              }
        mov     b3,dh            { 2-й БУС  (МПУ)              }

        pop     dx
        pop     ax
        pop     ds
     end;
     with MPUs^[adr] do begin bus0:= b1; bus1:= b2; bus2:= b3 end;
     MPUdiagnose:= MyCon
   end;*)


  {
   Funkcia pre spracovanie poziadavky od abonenta (signal TRB_A)
   nemusi sa volat pri tlaci, je zahrnuta v jej algoritme
  }

  function Trb_A(var adr: byte):byte;
    var    MyCon : byte;
           MyAdr : byte;
    begin
      if    (adr<lo_MPUadr) or (adr>hi_MPUadr)
         or (not (MPUs^[adr].bgu in [lo_BGUadr..hi_BGUadr]))
            then Exit;

      { Malo by sa prepnut spravne BGU
      } if BGUactive<>MPUs^[adr].bgu then BGUgril(MPUs^[adr].bgu);

      asm
          push    ds
          push    ax
          push    dx
          push    cx
          mov     cx,02h

  @TRB_A:
          mov     ah,2     { Ожидание ТРБ-А }
          mov     al,0     { Ocakavanie TRB_A }
          int     17h
          cmp     al,NOBGU
          loopz   @TRB_A
          mov     MyCon,ah
          mov     MyAdr,al

  @tfor1: pop     cx
          pop     dx
          pop     ax
          pop     ds

     end;
     adr := MyAdr;
     Trb_A := MyCon
   end;


  {
   Systemovy reset aktualneho BGU;
   nemusi sa volat pri tlaci, je v nom zahrnuty
  }
  function BGUreset: byte;
     var   MyCon: byte;
     begin
       asm
         push    ds
         push    ax
         push    dx

         mov     ah,3   { Команда "системный сброс"}
         int     17h

         mov     MyCon,ah
         pop     dx
         pop     ax
         pop     ds
       end;
       BGUreset:= MyCon
     end;


  { lokalny buffer pre zapis stripu
  var  buff : TMPUbuff;
  }

  {
  Funkcia inicializuje CharBufffer, ktory obsahuje nekodovane data
  Mala by sa volat pred kazdym novym naplnanim buffera
  }
  procedure IMPUclear (var buff: TIMPUbuff);
     begin
       fillchar(buff,sizeof(buff),0)
     end;

  procedure MPUclear (adr: byte);
     begin
       if (adr<lo_MPUadr) or (adr>hi_MPUadr) then Exit;

       fillchar(MPUs^[adr].buff,sizeof(MPUs^[adr].buff),' ')
     end;


  {
   Funkcia naplna CharBuffer na pozicii x,y / zacina 0..0
  }
  procedure MPUwrite (adr: byte; x,y: int; s: string);
     begin
       if (adr<lo_MPUadr) or (adr>hi_MPUadr) then Exit;

       x:= minimum(x,MAX_ZNAK_MPU-1); y:= minimum(y,MAX_RDK_MPU-1);
       move(s[1],MPUs^[adr].buff[y,x],Minimum(MAX_ZNAK_MPU-x,length(s)))
     end;


  {
   Kodovanie ASCII do kodu MPU,
   vracia  true - OK alebo false, ak je prazdny strip
  }

  const mpuSPC = $40;
        mpuPRN = $26;


  const lo_32_175 = 32;
        hi_32_175 = 175;

        Code32To175 : array [lo_32_175..hi_32_175] of byte =

        {' ','!','"','#','$','%','&',''','(',')','','+',',','-','.','/',}
        ($40,$4F,$7F,$7B,$5B,$6C,$50,$40,$4D,$5D,$5C,$4E,$6B,$60,$4B,$61,

        {'0','1','2','3','4','5','6','7','8','9',}
         $F0,$F1,$F2,$F3,$F4,$F5,$F6,$F7,$F8,$F9,

        {':',';','<','=','>','?','@',}
         $7A,$5E,$4C,$7E,$6E,$6F,$7C,

        {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P',}
         $C1,$C2,$C3,$C4,$C5,$C6,$C7,$C8,$C9,$D1,$D2,$D3,$D4,$D5,$D6,$D7,
        {'Q','R','S','T','U','V','W','X','Y','Z',}
         $D8,$D9,$E2,$E3,$E4,$E5,$E6,$E7,$E8,$E9,

        {'[','\',']','^','_','`',}
         $4A,$E0,$5A,$60,$60,$40,

        {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p',}
         $C1,$C2,$C3,$C4,$C5,$C6,$C7,$C8,$C9,$D1,$D2,$D3,$D4,$D5,$D6,$D7,
        {'q','r','s','t','u','v','w','x','y','z',}
         $D8,$D9,$E2,$E3,$E4,$E5,$E6,$E7,$E8,$E9,

      (*'{','|','}','~',DEL*)
        $4A,$7D,$5A,$40,$40,

        {'А','Б','В','Г','Д','Е','Ж','З','И','Й','К','Л','М','Н','О','П',}
         $B9,$BA,$ED,$BF,$BC,$BD,$EC,$FA,$CB,$CC,$CD,$CE,$CF,$DA,$DB,$DC,

        {'Р','С','Т','У','Ф','Х','Ц','Ч','Ш','Щ','Ъ','Ы','Ь','Э','Ю','Я',}
         $DE,$DF,$EA,$EB,$BE,$CA,$BB,$FE,$FB,$FD,$EE,$EF,$EE,$FC,$B8,$DD,

        {'а','б','в','г','д','е','ж','з','и','й','к','л','м','н','о','п',}
         $B9,$BA,$ED,$BF,$BC,$BD,$EC,$FA,$CB,$CC,$CD,$CE,$CF,$DA,$DB,$DC);


  const lo_224_239 = 224;
        hi_224_239 = 239;

        Code224To239 : array [lo_224_239..hi_224_239] of byte =

        {'р','с','т','у','ф','х','ц','ч','ш','щ','ъ','ы','ь','э','ю','я' }
        ($DE,$DF,$EA,$EB,$BE,$CA,$BB,$FE,$FB,$FD,$EE,$EF,$EE,$FC,$B8,$DD);


  function code_IMPUbuff(const MPUbuff: TMPUbuff; var IMPUbuff: TIMPUbuff): bool;
     var   lastEmpty, ind : byte;
           r,s : int;
     begin

       for r:= 0 to MAX_RDK_MPU-1 do
         for s:= 0 to MAX_ZNAK_MPU-1 do
             IMPUbuff[s,r]:= ord(MPUbuff[r,s]);

       for r:= 0 to MAX_ZNAK_MPU-1 do
         for s:= 0 to MAX_RDK_MPU-1 do
           begin
             ind:= IMPUbuff[r,s];
             if ind in[lo_32_175..hi_32_175] then IMPUbuff[r,s]:= Code32To175[ind]
             else if ind in [lo_224_239..hi_224_239] then IMPUbuff[r,s]:= Code224To239[ind]
             else IMPUbuff[r,s]:= mpuSPC;
           end;

       r:= MAX_ZNAK_MPU; { najdenie posledneho stlpca rozneho od ' ' }
       repeat
         dec(r);
         lastEmpty:= $0;
         for s:= 0 to MAX_RDK_MPU-1 do lastEmpty:= lastEmpty or IMPUbuff[r,s];
       until (lastEmpty<>mpuSPC) or (r=0);

       if ((r=0) and (lastEmpty=mpuSPC)) then { prazdny strip } code_IMPUbuff:= false
       else begin
              IMPUbuff[minimum(MAX_ZNAK_MPU-1,r+1),0]:= mpuPRN;
              code_IMPUbuff:= true
            end
     end;

  {
   Funkcia tlaci na vybranu adresu (adr <0-F>) obsah buffera.
   Vola Funkciu code_IMPUbuff, ktora obsh prekoduje pre tlaciaren,
   ak code_IMPUbuff vrati false, buffer je prazdny a je zbytocne tlacit.

   Vracia 0, ak OK:
  }

  function MPUprint (adr: byte): byte;
     var   this   : byte;
           that   : byte;
           count  : word;

           segDat : word;          { segment a     }
           offDat : word;          { offset stripu }

           buff   : TIMPUbuff;

     label QUIT;

     begin
       MPUprint:= NOBGU;

       if    (adr<lo_MPUadr) or (adr>hi_MPUadr)
          or (not (MPUs^[adr].bgu in [lo_BGUadr..hi_BGUadr]))
             {and (code_IMPUbuff(MPUs^[adr].buff,buff))}
             then Exit;

       code_IMPUbuff(MPUs^[adr].buff,buff);
       writeln_data(adr);

      { Malo by sa prepnut spravne BGU
      } if BGUactive<>MPUs^[adr].bgu then BGUgril(MPUs^[adr].bgu);

       count  := 0;
       this   := NOBGU;
       that   := NOBGU;

       segDat := Seg(buff);
       offDat := Ofs(buff);

       asm

           { Отсюда начинается печать первых 5-и байтов, включая время }
           { на разгон двигателя }

                push    ds          { pridu o obsah... }
                push    ax
                push    dx

                mov     ah,03       { Системный сброс }
                int     17h


                mov     ds,SegDat
                mov     dx,OffDat
                mov     ah,0        { Команда "отпечатать" }
                mov     al,adr      { Адpес устpойства     }
                int     17h
                cmp     ah,0
                jz      @L1

                mov     this,ah
                mov     that,al
                pop     dx
                pop     ax
                pop     ds
                jmp     QUIT        { ErrorExit }


       @L1:     add     OffDat,5
                push    cx
                mov     cx,0fh      { push cx        }
       @T1:     mov     ah,2        { Ожидание ТРБ-А }
                mov     al,0
                int     17h
                cmp     al,NOBGU
                loopz   @T1

                cmp     al,NOBGU
                jnz     @TL1

                pop     cx
                pop     dx
                pop     ax
                pop     ds
                mov     this,NOBGU
                jmp     QUIT        { ErrorExit }

       @TL1:    cmp     ah,0
                jz      @P1

                pop     cx
                pop     dx
                mov     this,ah
                mov     that,al
                pop     ax
                pop     ds
                jmp     QUIT        { ErrorExit }

       @P1:     pop     cx


       { Дальше идет печать более быстро }

       @NEXT:   pop     dx          { vlozenie hlavnej slucky programu }
                pop     ax
                pop     ds
                call    Check
                push    ds
                push    ax
                push    dx

                mov     ds,SegDat
                mov     dx,OffDat
                mov     ah,0        { Команда "отпечатать" }
                mov     al,adr      { Адpес устpойства     }
                int     17h
                push    cx
                mov     cx,0fh

       @WAIT:   mov     ah,2        { v tejto casti by mohlo byt testovanie }
                mov     al,adr      { preplnenia buffera tlaciarne          }
                int     17h         { a opatovne tlacenie                   }
                cmp     al,NOBGU
                loopz   @WAIT

                cmp     al,NOBGU    { nevznikla chyba ? }
                jnz     @OK1
                pop     cx
                pop     dx
                pop     ax
                pop     ds
                mov     this,NOBGU
                jmp     QUIT        { ErrorExit }

       @OK1:    cmp     ah,0
                jz      @OK2
                pop     cx
                pop     dx
                mov     this,ah
                mov     that,al
                pop     ax
                pop     ds
                jmp     QUIT        { ErrorExit }

       @OK2:    pop     cx
                add     Offdat,5
                push    di
                mov     di,Offdat
                mov     ds,Segdat
                mov     al,ds:[di]
                cmp     al,026h
                jz      @OK3
                pop     di
                jmp     @NEXT

       @OK3:    pop     di
                mov     ds,SegDat
                mov     dx,OffDat
                mov     ah,0        { Команда "отпечатать"}
                mov     al,adr      { Адpес устpойства    }
                int     17h
                push    cx
                mov     cx,0fh

       @LOOP1:  mov     ah,2
                mov     al,adr
                int     17h
                cmp     al,NOBGU
                loopz   @LOOP1

                cmp     al,NOBGU
                jnz     @OK4
                pop     cx
                pop     dx
                pop     ax
                pop     ds
                mov     this,NOBGU
                jmp     QUIT

       @OK4:    cmp     ah,0
                jz      @OK5
                pop     cx
                pop     dx
                mov     this,ah
                mov     that,al
                pop     ax
                pop     ds
                jmp     QUIT

       @OK5:    pop     cx
                pop     dx
                pop     ax
                pop     ds
                mov     this,0

       end;

       QUIT:    MPUprint:= this;

                with MPUs^[adr] do
                  begin
                    if st<>this then st:= this;
                    if st<>0 then writeln_status(adr);
                    {$IFDEF STATUS}
                      if bt<>nil then bt^.visibility(st<>0);
                      display_status_bgu(MPUs^[adr].bgu)
                    {$ENDIF}
                  end;

                if BGU_DEL<>0 then Delay(BGU_DEL);
     end;


function BGU_MPUstat(_bgu: byte): string;
   begin
     case _bgu of
       $0  : BGU_MPUstat:= 'Status O.K.';
       $80 : BGU_MPUstat:= 'Отсутствует ВБР-А';
       $40 : BGU_MPUstat:= 'Отсутствует РАБ-А';
       $20 : BGU_MPUstat:= 'Отсутствует АДР-А';
       $10 : BGU_MPUstat:= 'Отсутствует УПР-А';
       $50 : BGU_MPUstat:= 'Отсутствуют УПР-А и РАБ-А';
       $08 : BGU_MPUstat:= 'Отсутствует ИНФ-А';
       $18 : BGU_MPUstat:= 'Отсутствуют УПР-А и ИНФ-А';
       $04 : BGU_MPUstat:= 'Отработано  ТРБ-А';
       $02 : BGU_MPUstat:= 'Сбой в устройстве';
       $01 : BGU_MPUstat:= 'Вернулся чужой адрес';
       $2E : BGU_MPUstat:= 'Выброс по короткой выборке';
       $F2 : BGU_MPUstat:= 'Плохой отчет по ТРБ-А';
       $22 : BGU_MPUstat:= 'Ошибка четности (parity check error)';
       else  BGU_MPUstat:= 'BGU/MPU error..';
     end
   end;

{
  Пеpвый байт уточненного состояния ВУ:
}
const BUS1res: array[0..7] of pchar =
      ( nil,
        nil,
        'Пеpеполнение буфеpа >5 символов в МПУ',
        'Ошибка данных',
        'Сбой обоpудования',
        'Ошибка на шинах интеpфейса (непpавильная четность)',
        'Тpебуется вмешательство',
        'Указание отвеpгнуто - код указания <-> контpольный pазpяд'
        {'Указание отвеpгнуто - непpавильный код указания с пpавильным контpольным pазpядом'}
      );

{
 Втоpой байт уточненного состояния ВУ:
}
const BUS2res: array[0..7] of pchar =
      ( nil,
        nil,
        'Неpазгон двигателя',
        'Конец бумаги',
        'Неиспpавен пpедохpанитель',
        'Неиспpавность печати',
        nil,
        'Сбой печати (отпечатано с ошибкой)'
      );
