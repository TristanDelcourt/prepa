type ab = 
    | F of int
    | N of int * ab * ab

let a1 = N(1, N(2, F(3), F(4)), N(5, F(6), F(7)))

let rec print_n_spaces n = match n with
    | 0 -> print_string " "
    | _ -> print_string " "; print_n_spaces (n-1)

let rec pretty_print_aux (a: ab) (n: int) (b: bool) = match a with
    | F(e) ->
        if b then
        begin
            print_n_spaces (4*n); print_int e
        end
        else
            print_int e

    | N(e, g, d) ->
        if b then
        begin
            print_n_spaces (4*n);
            print_int e;
            print_string "   ";
            pretty_print_aux g (n+1) false;
            print_newline ();
            pretty_print_aux d (n+1) true
        end
        else
        begin
            print_int e;
            print_string "   ";
            pretty_print_aux g (n+1) false;
            print_newline ();
            pretty_print_aux d (n+1) true
        end

let pretty_print a = pretty_print_aux a 0 true