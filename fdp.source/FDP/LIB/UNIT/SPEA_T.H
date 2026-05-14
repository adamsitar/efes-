    {----------------- Datentypen -------------------------}

    type   str255   = string[255];
  	   str9     = string[9];

	   pattbuff = array [0..15] of word;
	   polybuff = array [0..512] of int;
	   pixbuff  = array [0..512] of word;
           andxor   = array [0..15] of word;

           polybuff_p = ^polybuff;

	   pkunres  = record
		        pfunc : int;
	              end;

	   pkend  = record
		      pfunc : int;
                    end;

	   pkinit = record
		      pfunc  : int;
		      status : int;
	            end;

	   pkldfont = record
		        pfunc : int;
		        segment: word;
		        offset : word;
		        stat   : int;
	              end;

	   pkstfont = record
		        pfunc  : int;
		        segment: word;
		        offset : word;
		        fontnr : int;
	              end;

	   pkslfont = record
		        pfunc  : int;
		        fontnr : int;
		        stat   : int;
	              end;

	   pkrmfont = record
		        pfunc  : int;
		        fontnr : int;
		        stat   : int;
	              end;

	   pkenfont = record
    		        pfunc  : int;
    		        count  : int;
  	              end;

  	   pkinfo   = record
                        pfunc        : int;
     		        dversion     : int;
     		        card         : int;
      		        base_address : int;
     		        xsize        : int;
     		        ysize        : int;
     		        xmem         : int;
     		        ymem         : int;
  	              end;

 	   pkipage  = record
    		        pfunc     : int;
    		        max_page  : int;
    		        sel_page  : int;
    		        show_page : int;
         	      end;

  	   pkicolor = record
    		        pfunc      : int;
		        bit_planes : int;
		        max_color  : int;
		        nshades    : int;
  	              end;

  	   pkifont  = record
    		        pfunc    : int;
		        max_char : int;
		        xchar    : int;
		        ychar    : int;
  	             end;

  	   pkccolor = record
                        pfunc  : int;
		        ccolor : int;
  	              end;

  	   pkbcolor = record
    		        pfunc : int;
		        bcolor: int;
  	              end;

  	   pkopmode = record
    		        pfunc : int;
		        opmode: int;
  	              end;

  	   pklstyle = record
    		        pfunc : int;
		        pattern: word;
  	              end;

  	   pksetvlu = record
        		pfunc : int;
		        index : int;
		        red   : int;
		        green : int;
		        blue  : int;
  	              end;

  	   pkgetvlu = record
    		        pfunc : int;
		        index : int;
		        red   : int;
		        green : int;
		        blue  : int;
  	              end;

 	   pkresetvlu = record
    		          pfunc : int;
  	                end;

  	   pkselpg = record
    		       pfunc : int;
		       page  : int;
  	             end;

  	   pkshwpg = record
    		       pfunc : int;
		       page  : int;
  	             end;

  	   pksplit = record
    		       pfunc : int;
		       scr   : int;
		       px    : int;
		       py    : int;
		       ysize : int;
  	             end;


  	   pkshow  = record
    		       pfunc :int;
		       enable:int;
  	             end;

  	   pkclip  = record
    		        pfunc : int;
    		        x1    : int;
    		        y1    : int;
    		        x2    : int;
    		        y2    : int;
  	             end;

  	   pknclip = record
    		       pfunc : int;
  	             end;

  	   pkslcard = record
    		        pfunc  : int;
    		        cardnr : int;
    		        status : int;
  	              end;


	   pkspatt = record
         	       pfunc    :int;
		       xsize    :int;
		       ysize    :int;
		       zoomx    :int;
		       zoomy    :int;
		       xpointer :int;
		       ypointer :int;
		       segment	: word;
		       offset   : word;
  	             end;

  	   pkdpatt = record
    		       pfunc   :int;
		       x       :int;
		       y       :int;
		       xsize   :int;
		       ysize   :int;
		       szx     :int;
		       szy     :int;
		       zoomx   :int;
		       zoomy   :int;
		       dir     :int;
		       segment :word;
		       offset  :word;
  	             end;

  	   pkclr = record
    		     pfunc :int;
		     color :int;
  	           end;

  	   pkdot = record
    		     pfunc :int;
		     x     :int;
		     y     :int;
  	           end;

  	   pkvect = record
    		      pfunc :int;
    		      p :array [0..3] of int;
  	            end;

	   pkpoly = record
		      pfunc : int;
		      n     : int;
		      segment : word;
		      offset  : word;
	            end;

	   pkfpoly = record
		       pfunc : int;
		       segment : word;
		       offset  : word;
	             end;

	   pkfill = record
		      pfunc : int;
		      x1 : int;
		      y1 : int;
		      x2 : int;
		      y2 : int;
	            end;

	   pkpfill = record
		       pfunc : int;
		       x1 : int;
		       y1 : int;
		       x2 : int;
		       y2 : int;
	             end;

	   pktext = record
		      pfunc : int;
		      x     : int;
		      y     : int;
		      n     : int;
		      segment : word;
		      offset  : word;
	            end;


	   pktextd = record
		       pfunc : int;
		       textdir : int;
		       status : int;
	             end;

	   pktexto = record
		       pfunc : int;
		       textori : int;
		       status : int;
	             end;

	   pkcircle = record
		        pfunc : int;
		        xc    : int;
		        yc    : int;
		        radius: int;
	              end;

	   pkfcircle = record
		         pfunc : int;
		         xc    : int;
		         yc    : int;
		         radius: int;
	               end;

	   pkarc =  record
		      pfunc : int;
		      dir   : int;
		      xs    : int;
		      ys    : int;
		      xe    : int;
		      ye    : int;
		      xc    : int;
		      yc    : int;
	            end;

	   pkcopy = record
		      pfunc : int;
		      src   : int;
		      x1    : int;
		      y1    : int;
		      x2    : int;
		      y2    : int;
		      dest  : int;
		      dx    : int;
		      dy    : int;
	            end;

	   pkgetdot = record
		        pfunc : int;
		        dir   : int;
		        p1    : int;
		        p2    : int;
		        ccord : int;
		        segment	: word;
		        offset	: word;
	              end;

	   pksetdot = record
		        pfunc : int;
		        dir   : int;
		        p1    : int;
		        p2    : int;
		        ccord : int;
		        segment	: word;
		        offset	: word;
	              end;

	   pkircurs = record
 		        pfunc : int;
    		        curx  : int;
    		        cury  : int;
    		        andseg: word;
    		        andoff: word;
    		        xorseg: word;
    		        xoroff: word;
    		        xsize : int;
    		        ysize : int;
    		        xzoom : int;
    		        yzoom : int;
    		        xbuffer : int;
    		        ybuffer : int;
    		        fgcolor : int;
    		        bgcolor : int;
 	              end;

	   pkdrcurs = record
    		        pfunc : int;
    		        posx  : int;
    		        posy  : int;
  	              end;

	   pkcrcurs = record
		        pfunc : int;
  	              end;

	   pkvspos  = record
    		        pfunc :int;
		        x     :int;
		        y     :int;
  	              end;

	   pkvgpos  = record
    		        pfunc :int;
		        x     :int;
		        y     :int;
  	              end;

	   pkvswindow = record
    		          pfunc :int;
		          x1 : int;
		          y1 : int;
		          x2 : int;
		          y2 : int;
  	                end;

	   pkvgwindow = record
    		          pfunc :int;
		          x1 : int;
		          y1 : int;
		          x2 : int;
		          y2 : int;
  	                end;

	   pkvzoom  = record
    		        pfunc : int;
		        zfactor  : int;
 	              end;

	   pkvgsize = record
    		        pfunc :int;
		        x     : int;
		        y     : int;
  	              end;

	   pkvdisp  = record
   		        pfunc : int;
		        mode  : int;
  	              end;

  	   pkvgdisp = record
    		        pfunc : int;
		        mode  : int;
  	              end;

 	   pkvgzoom = record
    		        pfunc : int;
		        zfactor  : int;
  	              end;

  	   pkboxsave = record
  		         pfunc : int;
    		         id : int;
  		         x0, y0, x1, y1 : int;
    		         height : int;
    		         mode : int;
  	               end;

  	   pkboxinq  = record
    		         pfunc : int;
    		         status  : int;
    		         id : int;
  		         x0, y0, x1, y1 : int;
		         planes : int;
	               end;

	   pkboxrest = record
		         pfunc : int;
    		         status   : int;
		         id, x, y : int;
    		         dummy : int;
	               end;

	   pkboxfree = record
		         pfunc : int;
    		         status   : int;
		         id : int;
    		         dummy : int;
	               end;

  	   packet_t  = record
                         case int of
			   56:(punres    : pkunres);

			   1234:(pinit   : pkinit);
			   5678:(pend    : pkend);

			   1             : (pldfont : pkldfont);
			   202:(pstfont  : pkstfont);
			   203:(pslfont  : pkslfont);
			   205:(prmfont  : pkrmfont);
			   204:(penfont  : pkenfont);

			   11:(pinfo     : pkinfo);
			   12:(pipage    : pkipage);
			   13:(picolor   : pkicolor);
			   14:(pifont    : pkifont);

			   21:(pccolor   : pkccolor);
			   22:(pbcolor   : pkbcolor);
			   23:(popmode   : pkopmode);
			   24:(plstyle   : pklstyle);
			   25:(psetvlu   : pksetvlu);
			   725:(pgetvlu  : pksetvlu);
			   726:(presetvlu: pkresetvlu);
			   26:(pselpg    : pkselpg);
			   27:(pshwpg    : pkshwpg);
			   28:(psplit    : pksplit);
			   29:(pshow     : pkshow);

			   300:(pclip    : pkclip);
			   301:(pnclip   : pknclip);
			   302:(pslcard  : pkslcard);

			   30:(pspatt    : pkspatt);
			   31:(pdpatt    : pkdpatt);

 			   41:(pclr      : pkclr);
  			   42:(pdot      : pkdot);
 			   43:(pvect     : pkvect);
			   44:(ptext     : pktext);

			   401:(ptextd   : pktextd);
			   402:(ptexto   : pktexto);

			   45:(ppoly     : pkpoly);
			   945:(pfpoly   : pkfpoly);

			   46:(pfill     : pkfill);
			   47:(ppfill    : pkpfill);
			   48:(pcircle   : pkcircle);

			   948:(pfcircle : pkfcircle);

			   49:(parc      : pkarc);
			   50:(pcopy     : pkcopy);
			   52:(pgetdot   : pkgetdot);
			   53:(psetdot   : pksetdot);

 			   80:(pircurs   : pkircurs);
 			   81:(pdrcurs   : pkdrcurs);
			   82:(pcrcurs   : pkcrcurs);

			   801:(pvspos   : pkvspos);
			   802:(pvgpos   : pkvgpos);
			   803:(pvswindow: pkvswindow);
			   804:(pvgwindow: pkvgwindow);
			   805:(pvzoom   : pkvzoom);
			   806:(pvgsize  : pkvgsize);
			   807:(pvdisp   : pkvdisp);
			   808:(pvgdisp  : pkvgdisp);
			   809:(pvgzoom  : pkvgzoom);

		  	   901:(pboxsave : pkboxsave);
		  	   902:(pboxinq  : pkboxinq);
		  	   903:(pboxrest : pkboxrest);
		  	   904:(pboxfree : pkboxfree);

	               end;


