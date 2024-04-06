type 'a tree = 
    Node of 'a * ('a tree list)

let rec taille (Node(x, l): 'a tree): int = 
    1 + List.fold_left (+) 0 (List.map taille l)

let rec hauteur (Node(x, l): 'a tree): int = 
    1 + List.fold_left max 0 (List.map hauteur l)

let rec etiquette (Node(x, l): 'a tree) (chemin: int list) : 'a = 
    match chemin with
    | [] -> x
    | t::q ->
        if t < 0 || t >= List.length l then
            failwith "en fait non"
        else 
            etiquette (List.nth l t) q (* on prend le t-ième élément de la liste *)

let rec liste_prefixe (Node(x, l): 'a tree) : 'a list = 
    x::List.fold_left (@) [] (List.map liste_prefixe l)

let rec liste_postfixe (Node(x, l): 'a tree) : 'a list = 
    List.fold_left (@) [] (List.map liste_postfixe l) @ [x]

let liste_largeur (a: 'a tree) : 'a list = 
    let rec aux (l_act: 'a tree list) (l_suiv: 'a tree list) : 'a list = 
        match l_act, l_suiv with
        | ([], []) -> []
        | (Node(x, l)::q , _) -> x::(aux q (l_suiv @ l))
        | ([], _) -> aux l_suiv [] in
    aux [a] []

let test () = 
    let t = Node(1, [Node(2, []); Node(3, [Node(4, []); Node(5, [])])]) in 
    let t2 = Node(1, [Node(2, [Node(5, []); Node(6, [])]); Node(3, [Node(7, []); Node(8, [])]); Node(4, [Node(9, []); Node(10, [])] ) ]) in

    assert (taille t = 5);
    assert (hauteur t = 3);

    assert (etiquette t [] = 1);
    assert (etiquette t [1; 0] = 4);

    assert (liste_prefixe t = [1; 2; 3; 4; 5]);
    assert (liste_postfixe t = [2; 4; 5; 3; 1]);

    assert (liste_largeur t = [1; 2; 3; 4; 5]);
    assert (liste_largeur t2 = [1; 2; 3; 4; 5; 6; 7; 8; 9; 10]);


    print_endline "test ok"