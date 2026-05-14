type  FontDef   = array[0..7] of byte;
      FontArray = array[0..255] of FontDef;

const {$IFDEF PMODE}
        FontSelector : long = 0;          { protected mode font selector }
        RealIntOfs   : word = 0;          { storage for old real mode }
        RealIntSeg   : word = 0;          { in vect when in protected mode }
      {$ENDIF}
       Old1Fptr      : pointer    = nil;  { storage for old $1f int vec }
       FontPtr       : ^FontArray = nil;  { pointer to our font table }


{ Load the font definition file
}
function LoadFont (FontFileName: string): bool;
   var   f : file of FontArray;
   begin
      LoadFont := false;
      if Exists(FontFileName)<>0 then Exit;
     {$IFDEF PMODE}                               { if pmode, alloc the data in dos memory area}
       if FontSelector = 0 then FontSelector:= GlobalDosAlloc(sizeof(FontPtr^));
       if FontSelector = 0 then Exit;
       FontPtr := ptr(loword(FontSelector),0);
     {$ELSE}
       if FontPtr = nil then
          begin
            if MaxAvail<sizeof(FontPtr^) then Exit;
            New(FontPtr);                              { if real mode just grab it off the heap}
          end;
     {$ENDIF}

     if IOResult = 0 then {nop};
     Assign(f,FontFileName);
     Reset(f);
     Read(f,FontPtr^);    {read the font into memory}
     Close(f);
     if IOResult=0 then
        begin               {if valid file point the int vec at the font}
          {$IFDEF PMODE}
            SetRealIntVec($1F,Ofs(FontPtr^[128]),hiWord(FontSelector));
          {$ENDIF}
          SetIntVec($1f,@FontPtr^[128]);
          LoadFont := true;
        end
   end;

procedure instal_FONT;
    var   s : string;
    begin
      {$IFDEF BGI}
       {$IFDEF PMODE}
        GetRealIntVec($1F,RealIntOfs,RealIntSeg);  {save current vect}
       {$ENDIF}
       GetIntVec($1F,Old1Fptr);

       s:= FontFileName;
       read_cfg_str(SYSTEMcfg,cfgFontFileName,s);
       FontFileName:= s; { len 20 znakov }
       if FontFileName<>'' then
          begin
            if not LoadFont(FontFileName) then RunError('Could not load font file: '+FontFileName+'.')
          end;
      {$ENDIF}
    end;

procedure uninstal_FONT;
    begin
     {$IFDEF BGI}
        SetIntVec($1F,Old1FPtr);    {restore old int vect ptr}
       {$IFDEF PMODE}
         SetRealIntVec($1F,RealIntOfs,RealIntSeg);
         if FontSelector <> 0 then {release font dos memory}
            FontSelector:= GlobalDosFree(sizeof(FontPtr^));
       {$ELSE}
         if FontPtr <> nil then Dispose(FontPtr); {release heap allocation for font}
       {$ENDIF}
        FontPtr:= nil;
     {$ENDIF}
    end;
