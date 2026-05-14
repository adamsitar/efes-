    type   UserDataField = array[0..15] of byte;
           NSAP          = array[0..2]  of byte;


    const  UDF_mask : UserDataField =
                      ($84,$20,$01, $C9,6,1,1,1, $CB,6,1,1,1, 0,0,0);
                      { - Protocol identity
                        - Message code type
                        - Message code value (N CR)

                        - Parameter type = Called NSAP
                        - Parameter length
                        - AFI value
                        - ATC unit identifier
                        - ATC unit identifier

                        - Parameter type = Calling NSAP
                        - Parameter length
                        - AFI value
                        - ATC unit identifier
                        - ATC unit identifier

                        - Reserved for future use
                        - Reserved for future use
                        - Reserved for future use
                      }

           UDF_Called_NSAP_Ofs  =  6 - 1;
           UDF_Calling_NSAP_Ofs = 11 - 1;

