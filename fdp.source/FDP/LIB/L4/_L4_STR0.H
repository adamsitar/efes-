    function   l4ch   (ch: char): char;
    function   l4str  (s: string): string;
    function   l4line (p: pchar): pchar;

    function   eq_l4_str (s1,s2: string): bool;

    function   l4_format_s_(s: string; _nil: string): string;
    function   l4_format_s (s: string): string;
    function   decode_l4_s (s: string; is_nil: bool): string;

    function   l4_format_p (p: pchar): pchar;
    function   decode_l4_p (p: pchar; is_nil: bool): pchar;
