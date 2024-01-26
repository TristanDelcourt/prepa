let n_roots (a, b, c) = 
    let delta = b*.b -. 4.*. a *. c in
    if delta = 0. then 1 else
        if delta < 0. then 0 else 2
;;

let nom_chiffre x =
    if x<2 || x>5 then "" else
        if x = 2 then "two" else
        if x = 3 then "three" else
        if x = 4 then "four" else "five"
;;

let f x y = match (x-1, y) with
    | (0, 0) -> 0
    | (0, _) -> y+1
    | (z, 0) -> z+100
    | _ -> x * y
;;

let g x y = match (x-y, x+y) with
    | 0, _ -> 0
    | _, 0 -> 0
    | 1, _ -> (x+y) * (x+y) + 1
    | -1, _ -> (x+y) * (x+y) + 1
    | _, 1 -> (x-y) * (x-y) - 1
    | _, -1 -> (x-y) * (x-y) - 1
    | _ -> x * y
;;

let wtf n = match (n mod 3, n mod 5) with
    | (0, 0) -> "meu"
    | (_, 0) -> "ba"
    | (0, _) -> "gou"
    | _ -> string_of_int n
;;