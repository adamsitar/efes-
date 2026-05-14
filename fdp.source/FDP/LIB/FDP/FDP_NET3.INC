{ Opakovane by sa mali vysielat len spravy, ktore boli odoslane
  a uplynul timeout pre ne... Tym sa vyhnem tomu, aby spracovana
  sprava bola prijata este raz.

  Zabezpecit sa to da tak, ze neposiela spravu, ktorej kluc je v bufferi
  ocakavanych potvrdeni NETack. Kluce musia byt jednoznacne (Priestor
  LZ11 moze byt planovany kazdy den inak...)
  (... NETack^.is_for_ack ... )

}


{ Rozoslanie neaktivnych... planov ulozenych v suboroch
}

function is_nd_init_db(nd: int): bool; far;
   begin
     is_nd_init_db:= is_nd_type(nd, [FDP,FDP0NX,FDP0],set_nd_FDP,set_nd_NODE)
                     {or ((desc.sw in [SRD]) and (not stat.NodeON_))}
                     {or (desc.wp  in [MASTER,SLAVE])}
                     {or (strpos(desc.inf,inf_Init)<>nil)}
   end;

function is_ndr_init_db(nd: int): bool; far;
   begin
     is_ndr_init_db:= is_nd_init_db(nd)
                       (*{IFDEF MATCA}
                       { na RDPecko sa posielaju udaje zo subora len
                         pri strate informacie, lebo vtedy mozu
                         potrebovat odmazat alebo zmenit udaje
                         vedene ako (pre)aktivovane
                       }
                         or (    (    EN_RDP_ZO_SUBORA
                                  and (NODEs^[nd].desc.typ in [RDP,RDP0,RDP0NX])
                                 )
                             and (not NODEs^[nd].stat.NodeON_)
                            )
                       {ENDIF}*)
   end;


function nd_init_DB(path,ext  : string;

                    nd   : int;

                    info : string;
                    typs : Tnd_typ_set;
                    sws  : Tnd_sw_set;
                    nds  : Tnd_nd_set;

                    item_size  : word;
                    disp_item  : pointer;

                    riadkov    : byte;
                    DATAdecode : pointer;

                    nd_init    : pointer
                   ): bool; far;

   var   dir   : PDir;
         fls,i : int;
         item  : pointer;
         b,initdb : bool;

   begin
     nd_init_DB:= NODEs^[nd].stat.TrasaOK;
     if not (    (NODEs^[nd].stat.TrasaOK)
             and (is_nd_type(nd, typs,sws,nds))
             and (is_to_nd  (nd, info,nil,nil,@initdb))
             and (initdb)
            ) then Exit;

     getmem(item,item_size); fillchar(item^,item_size,0);
     if NODEs^[nd].desc.typ in [FDP,FDP0NX,FDP0] then
        begin
          if GetDirFiles(path,'*.'+ext,dir,fls)<>-1 then
             begin
               for i:= 0 to fls-1 do
                   begin
                    { Caka sa na potvrdenie kazdeho paketu }
                     b:= WAIT_INIT_NODE;
                     do_items_DB (nd_init,@nd,
                                  item,disp_item,
                                  path+dir^[i]^.name,
                                  riadkov, nil,DATAdecode,nil,
                                  nil
                                 );
                     WAIT_INIT_NODE:= b;
                     if {WAIT_INIT_NODE and} (not (NODEs^[nd].stat.TrasaOK)) then break
                   end;
               FreeDirFiles(dir,fls)
             end
        end
     else begin
          { aktualizacia dennymi planmi, zatial sa nepocita
            s prechodom medzi dnami, vid "Formaty"...
          }
            do_items_DB (nd_init,@nd,
                         item,disp_item,
                         get_DBfn_(day,month,year,path,ext),
                         riadkov, nil,DATAdecode,nil,
                         nil
                        );
          end;
     freemem(item,item_size);
     nd_init_DB:= NODEs^[nd].stat.TrasaOK;
   end;


function nd_init_files(path,ext : string;

                       nd   : int;
                       typ  : word;

                       info : string;
                       typs : Tnd_typ_set;
                       sws  : Tnd_sw_set;
                       nds  : Tnd_nd_set;

                       ispath,isext : bool;
                       isrec,isrecdb : bool;
                       isbmode : bool
                      ): bool; far;

   var   dir    : PDir;
         fls,i  : int;
         rec    : Tplan_rec;
         initdb : bool;

   begin
     nd_init_files:= NODEs^[nd].stat.TrasaOK;
     if  not (    (NODEs^[nd].stat.TrasaOK)
              and (is_nd_type (nd, typs,sws,nds))
              and (is_to_nd   (nd, info,nil,nil,@initdb))
              and initdb
             ) then Exit;

     if GetDirFiles(path,'*.'+ext,dir,fls)=-1 then Exit;
     i:= 0; while (i<fls) and (NODEs^[nd].stat.TrasaOK) do
       begin
         if     (read_file_rec (path+dir^[i]^.name,isrecdb,rec))
            and (rec[nd]=no_ack)
            then NETsend_file ( NODEs^[nd].desc.adr,
                                typ,path+dir^[i]^.name,
                                info,net_flag_NIL,
                                ispath,isext,
                                isrec,isrecdb,
                                isbmode
                              );
         inc(i)
       end;
     FreeDirFiles(dir,fls);
     nd_init_files:= NODEs^[nd].stat.TrasaOK
   end;


{$I FDP_nd_initialize.inc}

function TFDP_NET.node_initialize_est (nd: int): bool;
   begin
     node_initialize_est:= false;

    { Funkcia inicializuje a nastavi pre RDP priznak, ze ziadny udaj
      nebol prevzaty a teda potrdeny. Potom sa mu obnoveni spojenia,
      ktore mohlo vypadnut nahodou pri inicializacii urcite dostanu
      vsetky stripy;
      Konstrukcia je znacke archicka, vyhladom ku sucasnym moznostima
      i spolohalivosti pouzitu\ych algoritmov pouzit zoznamy...
    }
     {$IFDEF FPL0}
       {$IFDEF EDD}
         if (PROP_cFPL<>nil) then
            begin
              if not PROP_cFPL^.Inicializacia(nd,inf_FPLC,@is_cFPL_to_nd) then Exit;
              {if not PROP_cFPL^.Inicializacia(nd,inf_CPL,@is_CPL_to_nd) then Exit}
            end;
         if (PROP_mFPL<>nil) and (not PROP_mFPL^.Inicializacia(nd,inf_FPLM,@is_mFPL_to_nd)) then Exit;
         if (PROP_oFPL<>nil) and (not PROP_oFPL^.Inicializacia(nd,inf_FPLO,@is_mFPL_to_nd)) then Exit;
       {$ENDIF}
       if (cFPL<>nil) then
          begin
            if not cFPL^.Inicializacia(nd,inf_FPLC,@is_cFPL_to_nd) then Exit;
            {if not cFPL^.Inicializacia(nd,inf_CPL,@is_CPL_to_nd) then Exit}
          end;

      {$IFNDEF FPLM_DISABLED}
       if (mFPL<>nil) and (not mFPL^.Inicializacia(nd,inf_FPLM,@is_mFPL_to_nd)) then Exit;
      {$IFDEF FPLO}
       if (oFPL<>nil) and (not oFPL^.Inicializacia(nd,inf_FPLO,@is_mFPL_to_nd)) then Exit;
      {$ENDIF}
      {$ENDIF}
     {$ENDIF}

     {$IFDEF ZAM}
       if (ZAMs<>nil) then if not ZAMs^.Inicializacia(nd,inf_ZAM,nil) then Exit;
     {$ENDIF}

     {$IFDEF PRS}
       if (PRSs<>nil) then if not PRSs^.Inicializacia(nd,inf_PRS,nil) then Exit;
     {$ENDIF}

     node_initialize_est:= true
   end;


function TFDP_NET.node_initialize_plan(nd: int): bool;
   begin
     node_initialize_plan:= false;

     {$IFDEF INIT_PLANY_ZO_SUBORA}

      {$IFDEF FPL0}
      {$IFNDEF FPLM_DISABLED}
        if is_ndr_init_db(nd) then
           begin
             if not nd_init_DB(pathFPL_M,ext_mFPL,
                               nd, inf_FPLM, [FDP,FDP0NX,FDP0{,RDP,RDP0,RDP0NX}],set_nd_FDP,set_nd_NODE,
                               sizeof(DmFPL), @disp_mFPL,
                               db_mFPL_RIADKOV,@decodeDB_FPLM,
                               @nd_init_mFPL
                              ) then Exit;

             {if not nd_init_DB(pathFPL_M,ext_mFPL,
                               nd, inf_FPLO, [FDP,RDP,FDP0,RDP0,RDP0NX],set_nd_FDP,set_nd_NODE,
                               sizeof(DmFPL), @disp_mFPL,
                               db_mFPL_RIADKOV,@decodeDB_FPLM,
                               @nd_init_mFPL
                              ) then Exit;}

             {$IFDEF KRL}
               if not nd_init_DB(pathFPL_M,ext_KRL,
                                 nd, inf_KRL, [FDP,FDP0],set_nd_OPL,set_nd_NODE,
                                 sizeof(DmFPL), @disp_mFPL,
                                 db_mFPL_RIADKOV,@decodeDB_FPLM,
                                 @nd_init_KRL
                                ) then Exit;

             {$ENDIF}
           end;
      {$ENDIF}
      {$ENDIF}


      {$IFDEF ZAM}
        if is_ndr_init_db(nd) then
           if not nd_init_DB(pathZAM,extZAM,
                             nd, inf_ZAM, [FDP,FDP0NX,FDP0{,RDP0,RDP,RDP0NX}],set_nd_FDP,set_nd_NODE,
                             sizeof(TZAM), @disp_ZAM,
                             db_ZAM_RIADKOV,@decodeDB_ZAM,
                             @nd_init_ZAM
                            ) then Exit;
      {$ENDIF}


      {$IFDEF DVZ}
        if not nd_init_DB(pathDVZ,extDVZ,
                          nd, inf_DVZ, [FDP,FDP0NX,FDP0{,RDP0,RDP,RDP0NX}],set_nd_FDP,set_nd_NODE,
                          sizeof(TDVZ), @disp_DVZ,
                          db_DVZ_RIADKOV,@decodeDB_DVZ,
                          @nd_init_DVZ
                         ) then Exit;
      {$ENDIF}


      {$IFDEF QGO}
        if is_nd_init_db(nd) then
           if not nd_init_DB(pathQGO,extQGO,
                             nd, inf_QGO, [FDP,FDP0NX,FDP0{,RDP0,RDP,RDP0NX}],set_nd_FDP,set_nd_NODE,
                             sizeof(TQGO), @disp_QGO,
                             db_QGO_RIADKOV,@decodeDB_QGO,
                             @nd_init_QGO
                            ) then Exit;
      {$ENDIF}

      {$IFDEF RTZ}
        if is_nd_init_db(nd) then
           if not nd_init_DB(pathRTZ,extRTZ,
                             nd, inf_RTZ, [FDP,FDP0NX,FDP0],set_nd_FDP,set_nd_NODE,
                             sizeof(TRTZ), @disp_RTZ,
                             db_RTZ_RIADKOV,@decodeDB_RTZ,
                             @nd_init_RTZ
                            ) then Exit;
      {$ENDIF}


      {$IFDEF PRZ}
        if is_nd_init_db(nd) then
           if not nd_init_DB(pathPRZ,extPRZ,
                             nd, inf_PRZ, [FDP,FDP0NX,FDP0],set_nd_OPL,set_nd_NODE,
                             sizeof(TPRZ), @disp_PRZ,
                             db_PRZ_RIADKOV,@decodeDB_PRZ,
                             @nd_init_PRZ
                            ) then Exit;

        if is_nd_init_db(nd) then
           if not nd_init_DB(pathPRN,extPRN,
                             nd, inf_PRN, [FDP,FDP0NX,FDP0],set_nd_FDP,set_nd_NODE,
                             sizeof(TPRN), @disp_PRN,
                             db_PRN_RIADKOV,@decodeDB_PRN,
                             @nd_init_PRN
                            ) then Exit;
      {$ENDIF}

      {$IFDEF PRS}
        if is_ndr_init_db(nd) then
           if not nd_init_DB(pathPRS,extPRS,
                             nd, inf_PRS, [FDP,FDP0NX,FDP0{,RDP,RDP0,RDP0NX}],set_nd_FDP,set_nd_NODE,
                             sizeof(TPRS), @disp_PRS,
                             db_PRS_RIADKOV,@decodeDB_PRS,
                             @nd_init_PRS
                            ) then Exit;
      {$ENDIF}


      {$IFDEF MET}
        if is_nd_init_db(nd) then
           if not nd_init_DB(pathSYN,'*',
                             nd, inf_SYN, [FDP,FDP0NX,FDP0],set_nd_FDP,[SLAVE],
                             sizeof(TSYN), @disp_SYN,
                             db_SYN_RIADKOV,@decodeDB_SYN,
                             @nd_init_SYN
                            ) then Exit;
      {$ENDIF}


      {$IFDEF FPL4}
        if is_nd_init_db(nd) then
           begin
             if not nd_init_DB(pathFPL,extFPL,
                               nd, inf_FPL4, [FDP,FDP0NX,FDP0],set_nd_FDP,set_nd_NODE,
                               sizeof(DFPL4), @disp_FPL4,
                               db_FPL4_RIADKOV,@decodeDB_FPL4,
                               @nd_init_FPL4
                              ) then Exit;
           end;
      {$ENDIF}


      {$IFDEF PLN}
        if is_nd_init_db(nd) then
           begin
             if not nd_init_DB(pathFPL,extPLN,
                               nd, inf_PLN, [FDP,FDP0NX,FDP0],set_nd_FDP,set_nd_NODE,
                               sizeof(DPLN), @disp_PLN,
                               db_PLN_RIADKOV,@decodeDB_PLN,
                               @nd_init_PLN
                              ) then Exit;
           end;
      {$ENDIF}


    {$ENDIF}
     node_initialize_plan:= true
   end;


function TFDP_NET.node_initialize_files(nd: int): bool;
   var   initdb: bool;
         b: bool;
   begin
     node_initialize_files:= false;

     {$IFDEF SYNCHRONIZE_EXT}
     {$IFDEF AFTN}
       {if (NODEs^[nd].desc.sw in [SERVER,BSERVER]) then
          if (DEV_AFTN<>nil) then
             if not DEV_AFTN^.node_initialize_files(nd) then Exit;
       }
     {$ENDIF}
     {$ENDIF}

     {$IFDEF PRZ}
       nd_init_files (pathPRN_VLIS,extPRN_VLIS,
                      nd,spr_PRN_VLIS,inf_VLIS,
                      [FDP,FDP0NX],set_nd_FDP,set_nd_NODE,
                      ispath_VLIS,isext_VLIS,true,false,true
                     );
     {$ENDIF}

     {$IFDEF FUA_DATA}
       nd_init_files (pathAUP,extAUP,
                      nd,spr_AUP,inf_FUA,
                      [FDP,FDP0NX],set_nd_FDP,set_nd_NODE,
                      ispath__UP,isext__UP,true,true,true
                     );

       nd_init_files (pathUUP,extAUP,
                      nd,spr_UUP,inf_FUA,
                      [FDP,FDP0NX],set_nd_FDP,set_nd_NODE,
                      ispath__UP,isext__UP,true,true,true
                     );
     {$ENDIF}

     {$IFDEF MET}
      {$IFDEF MET_RLI}
        if     {(NODEs^[nd].stat.Node_ON)
           and} (NODEs^[nd].stat.TrasaOK)
           and (is_nd_type (nd, [RDP,RDP0NX,RDP0],[],[]))
           and (is_to_nd   (nd, inf_MRL,nil,nil,@initdb))
           and initdb
           then initialize_MRL (nd);
      {$ENDIF}
     {$ENDIF}

     node_initialize_files:= true
   end;


{
  Moze byt volana len z jedneho miesta, caka sa na potvrdenie,
  tym sa predide zahlteniu systemu.

  Mal by sa rozlisovat typ inicializovanej stanice a informacia
  ku nej odosielana.

  Okrem civilnych planov (a EDD) su odosielane data i zo suborov.

  WAIT_INIT_NODE...
}

procedure TFDP_NET.initialize_node(nd: int);

    var   pkt : TNETpkt;
          data : pchars;
          size, i : word;
          kod : TNETtyp;
          s : string;
          res,b : bool;

    label X;

    procedure Kecy1;
        begin
          s:= NODEs^[nd].desc.adr+tit_INIT;
          {$IFDEF DOCUMENT_NET}
           {$IFDEF WRITELN_NET}
             MainApp^.writeln_(@s[1],length(s), cl_NODE_ON, arch_MESS,true,false);
           {$ENDIF}
           {$IFDEF ARCHIVE_NET}
             if archive_NET_SEND then archivuj_data(path_NET,get_ARCHfn(0)+'.'+extNET,@s[1],length(s),arch_MESS,true,false);
           {$ENDIF}
          {$ENDIF}
          if NODE_WIN {$IFDEF STATUS} and (btNETis=nil) {$ENDIF} then InfoCakaj(msgWAITING,s);
        end;

    procedure Kecy2;
        begin
          if NODE_WIN {$IFDEF STATUS} and (btNETis=nil) {$ENDIF} then InfoCakaj_zatvor;

          {if not WAIT_INIT_NODE then Exit;}
          s:= tit_DONE;
          if res then begin {s:= NODEs^[nd].desc.adr+tit_INIT_DONE;} i:= cl_NODE_ON end
          else begin {s:= NODEs^[nd].desc.adr+tit_INIT_FAIL;} i:= cl_ERR {NODE_OFF} end;
          {$IFDEF DOCUMENT_NET}
           {$IFDEF WRITELN_NET}
             MainApp^.writeln_(@s[1],length(s), i, arch_MESS,true,false);
           {$ENDIF}
           {$IFDEF ARCHIVE_NET}
             if archive_NET_SEND then archivuj_data(path_NET,get_ARCHfn(0)+'.'+extNET,@s[1],length(s),arch_MESS,true,false)
           {$ENDIF}
          {$ENDIF};
          {if not res then Say2(msgERR,s)}
        end;

    begin
      Kecy1;

     { -----------------------------------
        Odoslanie systemovych parametrov    ; nastavenie spracovania dat, synchronizacia spolocnych parametrov
       תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
     } if Owner<>nil then
          begin
            Owner^.get_app_config (NODEs^[nd].desc.typ, NODEs^[nd].desc.sw, NODEs^[nd].desc.nd, data,size);
            if size>0 then NETsend_msg (NODEs^[nd].desc.adr, spr_CONFIG, data,size, true,net_flag_SEND);
            FreeMem (data,size)
          end;

       res:= true;
       if NODEs^[nd].desc.sw in [PRN] then goto X; { neInicializaciau sa, MON moze poziadat o data ako SRD ... }

       NETsend_msg (NODEs^[nd].desc.adr,spr_INITIALIZE,nil,0,false,0);

       {$IFDEF CONNECT_TO_FDA}
        if nd = FDAnode then testFDAnodes;
       {$ENDIF}


     { --------------------------------------
        Inicializovanie aktivovanymi datami
       תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
     }
       {b:= WAIT_INIT_NODE; WAIT_INIT_NODE:= false;}
       res:= node_initialize_est(nd);
       {WAIT_INIT_NODE:= b;}

     { --------------------------------------
        Inicializovanie datami zo subora         ; ak sa posielaju na stanicu, tie, co sumomentalne aktivne, boli prave teraz..
       תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
     } res:= res and node_initialize_plan(nd);

     { --------------------------------------
        Inicializovanie subormi
       תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
     } res:= res and node_initialize_files(nd);


      X: NODEs^[nd].stat.sendtick:= getticks; { nastavi, aby sa hned nepokusal inicializovat }
         if res then kod:= spr_INITIALIZED
         else kod:= spr_INIT_FAILED;
         NETsend_msg (NODEs^[nd].desc.adr,kod,nil,0,false,0);

      Kecy2
    end;
