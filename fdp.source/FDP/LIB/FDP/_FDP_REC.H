        function   rectostr  (rec: Tplan_rec): string;
        procedure  strtorec  (s: string; var rec: Tplan_rec);

        procedure  write_rec (rec: bool; xi,yi: int);

        function   send2node (stat: string; nd: int): bool; far;


