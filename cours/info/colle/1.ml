let composee f g x = f (g x)

let rec add_aux k l i curr = match (curr=i, l) with
    | (true, _) -> k::l
    | (_, x::q) -> x::(add_aux k q i (curr+1))
let add k l i = add_aux k l i 0

let rec new_perm_aux k l i = match i=(List.length l +1) with
    | true -> []
    | false -> (add k l i)::new_perm_aux k l (i+1)
let new_perm k l = new_perm_aux k l 0

let rec perm n l = match l with
    | [] -> [[0]]
    | l::q -> new_perm n l @ perm n q

