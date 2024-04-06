type boisson =
    | Eau
    | JDF of string
    | Cola of bool
    | Cocktail of boisson * boisson * float

let rec prix_litre b l = match b with
    | Eau -> 0.
    | JDF s -> if s="ramboutan" then 5.3*.l else 3.*.l
    | Cola _ -> 1.*.l
    | Cocktail (b1, b2, p) -> prix_litre b1 (p*.l) +. prix_litre b1 ((1.-.p)*.l)

let rec shaker (l: boisson list) : boisson = match l with
    | [] -> failwith "Non"
    | [x] -> x
    | x::q -> Cocktail (x, shaker q, 0.5)

let string_of_boisson (b: boisson) = match b with
    | Eau -> "Eau"
    | JDF s -> "Jus de " ^ s
    | Cola t -> "Breiz Cola " ^ (if t then "normal" else "lite")
    | _ -> failwith "pas une boisson de base"

let rec ingredients_aux (b: boisson) (r: float) = match b with
    | Cocktail (b1, b2, p) -> (string_of_boisson b1, r*.p)::(ingredients_aux b2 (r-.r*.p))
    | _ -> [(string_of_boisson b, r)]

let ingredients (b: boisson) = ingredients_aux b 1.

let rec agreg_sum_aux (l: (string * float) list) (curr: string) (sum: float) = match l with
    | [] -> (0., l)
    | (b, m)::q -> if b=curr then let s, t = agreg_sum_aux q curr sum in (m+.s, t) else (sum, l)

let rec agreg_sum (l: (string * float) list) = 
    let l_trie = List.sort compare l in
    match l_trie with
    | [] -> []
    | (b, m)::_ -> let x, q = agreg_sum_aux l_trie b 0. in (b, x)::agreg_sum q

let recette (b: boisson) =
    let l = agreg_sum (ingredients b) in
    let rec aff l = match l with
        | [] -> ()
        | (x, s)::q -> print_string (string_of_float s ^ "L de " ^ x ^ "\n"); aff q
    in aff l