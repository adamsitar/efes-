      type  in_name     = long;

            TIPadr      = in_name;
            TIPname     = string[20];

            T_IPaddress = record
              fhost    : in_name;  { remote (foreign) host's Internet address }
              fsocket  : word;     { port (socket) to use on the remote host  }
              lsocket  : word;     { port (socket) to use on the local host   }
              protocol : byte;     { protocol to use }
            end;

