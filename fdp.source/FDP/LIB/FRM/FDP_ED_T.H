     type  Trqst     = (_,dla,ack,chg,dcl);

     type  Tproc_r   = procedure (rqst: Trqst);
           Tproc_rp  = procedure (rgst: Trqst; p: pointer);
           Tproc_rp2 = procedure (rgst: Trqst; p1,p2: pointer);


