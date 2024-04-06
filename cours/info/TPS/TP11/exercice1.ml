let rec somme (l: int list) : int = match l with
    | [] -> 0
    | x::q -> x + somme q

let rec recherche (l: 'a list) (e: 'a) : bool = match l with
    | [] -> false
    | x::q -> if x = e then true else recherche q e

let rec concatener l1 l2 = match l1 with
    | [] -> l2
    | x::q -> x::concatener q l2

let rec multi_concat l = match l with
    | [] -> []
    | l1::q -> concatener (l1) (multi_concat q)

let rec map f (l: 'a list) : 'b list = match l with
    | [] -> []
    | x::q -> (f x)::map f q

let rec rev_concat (l1: 'a list ) (l2: 'a list) : 'a list = match l1 with
    | [] -> l2
    | x::q -> rev_concat q (x::l2)

let rec range_aux (n: int) (l: int list) : int list = match n with
    | 0 -> l
    | _ -> range_aux (n-1) ((n-1)::l)

let range n = range_aux n []

let rec make_list f n = map f (range n)

let repeter s = s ^ s
let pair x = if x mod 2 = 0 then "pair" else "impair"

let rec compose_liste l e = match l with
    | [] -> e
    | f::q -> f (compose_liste q e)

let f k x = if x mod (2+k) = 0 then x/(2+k) else 3*x+k

let f_n k = compose_liste (make_list f k)

let grand_f n = somme (make_list (f_n n) n)

