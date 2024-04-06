let rec puiss a b = 
    if b = 1 then a else puiss a (b-1) * a
;;

let rec reste a b =
    if a < b then a else reste (a-b) b
;;

let rec pgcd a b =
    let r = reste a b in
    if r = 0 then b else pgcd b r
;;

let rec div_eucl a b =
    if a < b then (0, a) else
        let q, r = div_eucl (a-b) b in
        (q+1, r)
;;

let rec a_racine f a b =
    if (f a) = 0 then true else
    if a = b then false else
    a_racine f (a+1) b
;;

let rec concat l1 l2 = match l1 with
    | [] -> l2
    | x::q -> x::concat q l2

type fourniture =
    | Stylo of string
    | Regle of int*bool
    | Gomme

type trousse = fourniture list

let prix (x: fourniture) = 
    match x with
    | Gomme -> 1.5
    | Stylo "bleu" -> 1.2
    | Stylo _ -> 1.0
    | Regle (l, _) -> 1. +. float_of_int l /. 15.

let rec prix_trousse (tr: trousse): float =
    match tr with
    | [] -> 5.
    | f ::q -> prix(f) +. prix_trousse q

type 'a liste = 
    | Vide
    | Cons of 'a * 'a liste

let rec longueur (l: 'a liste) : int = 
    match l with
    | Vide -> 0
    | Cons (_, q) -> 1 + longueur q