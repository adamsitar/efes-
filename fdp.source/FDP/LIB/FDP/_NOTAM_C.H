    const bminiNTM : bool = true;

          max_NTM_D_rm : int  = 1;
          max_NTM_D_r_lo      = 0;
          max_NTM_D_r_hi      = 2;       { -> 1 DBriadok }

          max_NTM_E_rm : int  = 1;
          max_NTM_E_r_lo      = 0;
          max_NTM_E_r_hi      = 8;       { -> 3 DBriadky }


    const dxm_NTM = 570;
          dxf_NTM = 570;

          {off_rmk = 71 + 3;}
          dy_rmk  = 4;

          dym_NTM = 74;
          dyf_NTM = dym_NTM + dy_rmk+max_NTM_D_r_hi*10+dy_rmk + dy_rmk+max_NTM_E_r_hi*10+dy_rmk;
