(*-------------------------------------------------------------------*)
(* Graph_h                                                           *)
(* 19994                                                             *)
(*-------------------------------------------------------------------*)
{$I comp.h}


unit graph_h;


interface


    uses  TypeDef,
          graph;


    {$I gr_wrt.h}          { posuny pri vypise   }
    {$I gr_fnt.h}          { fonty               }
    {$I gr_cl.h}           { farby               }

    {$IFDEF BGI}
      {$I gr_bgi.h}        { zapisove mody }
    {$ENDIF}

   { premenne
   }
    const ZHASINANIE  : bool = true;      { povolenie }
    var   MaxX, MaxY  : word;             { The maximum resolution of the screen }


implementation

end.