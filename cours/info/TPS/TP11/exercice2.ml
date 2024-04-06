(*
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

let rec taille l = match l with
    | [] -> 0
    | x::q -> 1 + taille q

let rec string_cat l = match l with
    | [] -> ""
    | x::q -> x ^ string_cat q
*)

let rec fold f l a = match l with
    | [] -> a 
    | x::q -> f x (fold f q a)

let somme l = fold (+) l 0

let recherche l x = fold (fun e r -> e=x || r) l false

let concatener l1 l2 = fold (fun x r -> x::r) l1 l2

let multi_concat l = fold concatener l []

let taille l = fold (fun x r -> 1 + r) l 0

let string_cat l = fold (fun x r -> x ^ r) l ""

let compose_liste l e = fold (fun f r -> f r) l e

let filter f l = fold (fun x r -> if f x then x::r else r) l []

let rec list_of_string_aux s n l = if n = String.length s then List.rev l else list_of_string s (n+1) ((s.[n])::l)
let list_of_string s = list_of_string_aux s 0 []

(* let rec split_from_i s sep i curr = if i = String.length s then curr else *)

