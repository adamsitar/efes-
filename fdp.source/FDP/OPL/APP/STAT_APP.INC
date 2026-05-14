procedure STATUS_init(_App: PApp {$IFDEF DATA_WRITTEN_IN_APP}; _AppGui: PAppGui{$ENDIF});
    var   hi_    : int;
          cmXXXX : word;
          p : pointer;
          is,b : bool;

    begin
      hi_:= 163;

      btREP:= New(PTButton,Init(_App,
                  hi_, MaxY-16, Length(cbtREP) shl 3 + 4 -10,15,
                  kbNoKey, cmDefault, cbtREP, 1, clGRf,clGRc,clBUTTON_COLOR,
                  nil,true, hi_, true)
                 );
      addStatIndicator(btREP);

     {$IFDEF SPR}
      btMES:= New(PTButton,Init(_App,
                  hi_+4, MaxY-16, Length(cbtMES) shl 3 + 4 -10,15,
                  kbNoKey, cmPREHLAD_SPR_dor, cbtMES, 1, clGRf,clGRc,clBUTTON_COLOR,
                  @isSPR,true, hi_,false)
                 );
      addStatIndicator(btMES);
     {$ENDIF}

     {$IFDEF MATCA}
       cmXXXX:= cmNil;
       p:= nil; b:= true;
       is:= false;

       {$IFDEF MACC} {$IFDEF PROCESS_FPLM}
         cmXXXX:= cmREQm;
         is:= isFPLM_REQ_DLA;
         p:= @isFPLM_REQ_DLA;
       {$ENDIF} {$ENDIF}
       {$IFDEF AIRBASE} {$IFDEF PROCESS_DVZ}
         cmXXXX:= cmDVZacc;
         is:= isDVZ_REQ_DLA;
         p:= @isDVZ_REQ_DLA;
       {$ENDIF} {$ENDIF}

       if cmXXXX<>cmNil then
          begin
            btREQ:= New(PIButton,Init(_App,
                        hi_+1, MaxY-16, Length(cbtREQ) shl 3 + 4 -10,15,
                        kbNoKey,cmXXXX, cbtREQ, 1, clGRf,clGRc,clBUTTON_COLOR,
                        p,b, hi_, false)
                       );
            btREQ^.visible:= is;
            addStatIndicator(btREQ);
          end;
     {$ENDIF}

     {$IFDEF REPORT_FPLM_ARW}
       btARR:= New(PIButton,Init(_App,
                   hi_+2, MaxY-16, Length(cbtARR) shl 3 + 4 -10,15,
                   kbNoKey, cmARWm, cbtARR, 1, clGRf,clGRc,red,
                   @isFPLM_ARW,true, hi_,false)
                  );
       addStatIndicator(btARR);
     {$ENDIF}

     inc(hi_,10);

     {$IFDEF FPL0}
      {$IFDEF KRL}
        btKRL:= New(PTButton,Init(_App,
                    hi_+1, MaxY-16, Length(cbtKRL) shl 3 + 4 -10,15,
                    kbNoKey, cmPRIJATE_KRL {cmPREHLAD_KRL_dor}, cbtKRL, 1, clGRf,clGRc,clBUTTON_COLOR,
                    @isKRL,true, hi_,true)
                   );
        addStatIndicator(btKRL);
      {$ENDIF}


       btFPL:= New(PTButton,Init(_App,
                   hi_+1, MaxY-16, Length(cbtFPL) shl 3 + 4 -10,15,
                   kbNoKey, cmPRIJATY_FPLm,
                   cbtFPL, 1, clGRf,clGRc,clBUTTON_COLOR,
                   @isFPLM,true, hi_,true)
                  );
       addStatIndicator(btFPL);
      {$ENDIF}


      {$IFDEF ZAM}
       btZAM:= New(PTButton,Init(_App,
                   hi_+1, MaxY-16, Length(cbtZAM) shl 3 + 4 -10,15,   { 296 + 54 }
                   kbNoKey, cmPRIJATE_ZAM, cbtZAM, 1, clGRf,clGRc,clBUTTON_COLOR,
                   @isZAM,true, hi_,true)
                  );
       addStatIndicator(btZAM);
      {$ENDIF}


      {$IFDEF DVZ}
        btDVZ:= New(PTButton,Init(_App,
                    hi_+1, MaxY-16, Length(cbtDVZ) shl 3 + 4 -10,15,      { 296 }
                    kbNoKey, cmPRIJATE_DVZ, cbtDVZ, 1, clGRf,clGRc,clBUTTON_COLOR,
                    @isDVZ,true, hi_,true)
                   );
        addStatIndicator(btDVZ);
      {$ENDIF}


      {$IFDEF QGO}
        btQGO:= New(PTButton,Init(_App,
                    hi_+1, MaxY-16, Length(cbtQGO) shl 3 + 4 -10,15,
                    kbNoKey, cmPRIJATE_QGO, cbtQGO, 1, clGRf,clGRc,clBUTTON_COLOR,
                    @isQGO,true, hi_,true)
                   );
        addStatIndicator(btQGO);
      {$ENDIF}


      {$IFDEF PRS}
        btPRS:= New(PTButton,Init(_App,
                    hi_+1, MaxY-16, Length(cbtPRS) shl 3 + 4 -10,15,   { 296 + 54 }
                    kbNoKey, cmPRIJATE_PRS, cbtPRS, 1, clGRf,clGRc,clBUTTON_COLOR,
                    nil,true, hi_,true)
                   );
        addStatIndicator(btPRS);
      {$ENDIF}

       btDBis:=  New(PFButton,Init(_App,
                     hi_+1, MaxY-16, Length(cbtDBis) shl 3  + 20,15,
                     kbNoKey, cmDefault, cbtDBis,
                     1,white,clGRc,48)
                    );
       btDBis^.bk0:= black;
       btDBis^.visible:= false;
       cntrDB:= 0;
       addStatIndicator(btDBis);
       hi_:= btDBis^.x1;

      {$IFDEF NET}
        btNETis:= New(PFButton,Init(_App,
                      hi_+1, MaxY-16, Length(cbtNETis) shl 3 + 12,15,
                      kbNoKey, cmDefault, cbtNETis,
                      1,white,clGRc,48)
                     );
        btNETis^.bk0:= black;
        btNETis^.visible:= false;
        cntrNET:= 0;
        addStatIndicator(btNETis);
        hi_:= btNETis^.x1;
      {$ENDIF}

      {$IFDEF EXTERNAL_NET}
        btEXTis:= New(PFButton,Init(_App,
                      hi_+1, MaxY-16, Length(cbtEXTis) shl 3 + 12,15,
                      kbNoKey, cmDefault, cbtEXTis,
                      1,white,clGRc,48)
                     );
        btEXTis^.bk0:= black;
        btEXTis^.visible:= false;
        cntrEXT:= 0;
        addStatIndicator(btEXTis);
        hi_:= btEXTis^.x1;
      {$ENDIF}

      {$IFDEF CONNECT_AFTN}
        btAFTN := New(PIButton,Init(_App,
                    hi_+1, MaxY-16, Length(cbtAFTN) shl 3 + 4 - 10,15,
                    kbNoKey, cmAFTN_ERLINE, cbtAFTN, 1,white,clGRc,red,
                    @DEV_AFTN^.isTrTimeOut,true,hi_,false)
                   );
        btAFTN^.bk0:= black;
        addStatIndicator(btAFTN);
      {$ENDIF}
    end;
