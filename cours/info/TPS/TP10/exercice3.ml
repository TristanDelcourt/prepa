let print_pair n =
    if n mod 2 = 0 then print_int n else ()
;;

let print_pairs (a, b, c) = print_pair a; print_pair b; print_pair c
;;

let print_retour s = print_string s; print_newline ()
;;