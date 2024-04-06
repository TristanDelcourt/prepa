let rec est_trie l = match l with
    | [_] | [] -> true
    | x::y::q -> if x>y then false else est_trie (y::q)

let rec partition_aux l x l1 l2 = match l with
    | [] -> (l1,l2)
    | y::q -> if y>x then partition_aux q x l1 (y::l2) else partition_aux q x (y::l1) l2
let partition l x = partition_aux l x [] []

let rec tri_rapide l = match l with
    | [_] | [] -> l
    | p::q -> 
        let l1, l2 = partition q p in
        let l1_t = tri_rapide l1 in
        let l2_t = tri_rapide l2 in
        l1_t @ (p::l2_t)

let rec fusion_aux l1 l2 l = match (l1, l2) with
    | ([], _) -> (List.rev l) @ l2
    | (_, []) -> (List.rev l) @ l1
    | (x::q1, y::q2) -> if x<y then fusion_aux q1 l2 (x::l) else fusion_aux l1 q2 (y::l)

let fusion l1 l2 = fusion_aux l1 l2 []

let rec split_aux l l1 l2 n = match (l, n mod 2 = 0) with
    | ([], _) -> (l1, l2)
    | (x::q, true) -> split_aux q (x::l1) l2 (n+1)
    | (x::q, flase) -> split_aux q l1 (x::l2) (n+1)
let split l = split_aux l [] [] 0

let rec tri_fusion l = match l with
    | [_] | [] -> l
    | _ -> 
        let l1, l2 = split l in
        let l1_t = tri_fusion l1 in
        let l2_t = tri_fusion l2 in
        fusion l1_t l2_t