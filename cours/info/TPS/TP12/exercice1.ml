type 'a ab =
    | V
    | N of 'a * 'a ab * 'a ab

let rec taille (a: 'a ab) : int =
    match a with
    | V -> 0
    | N (_, g, d) -> 1 + taille g + taille d

let rec hauteur (a: 'a ab) : int =
    match a with
    | V -> -1
    | N (_, g, d) -> 1 + max (hauteur g) (hauteur d)

let rec est_feuille (a: 'a ab) : bool =
    match a with
    | V -> false
    | N (_, V, V) -> true
    | N (_, _, _) -> false

let rec feuilles (a: 'a ab) : int =
    match a with
    | V -> 0
    | N (_, V, V) -> 1
    | N (_, g, d) -> feuilles g + feuilles d


let rec etiquette (a: 'a ab) (l: bool list): 'a = 
    match a, l with
    | V, _ -> failwith "etiquette"
    | N (x, _, _), [] -> x
    | N (_, g, d), false::q -> etiquette g q
    | N (_, g, d), true::q -> etiquette d q

let rec etiquette_opt (a: 'a ab) (l: bool list): 'a option = 
    match a, l with
    | V, _ -> None
    | N (x, _, _), [] -> Some x
    | N (_, g, d), false::q -> etiquette_opt g q
    | N (_, g, d), true::q -> etiquette_opt d q

let rec print_prefixe (a: 'a ab) : unit =
    match a with
    | V -> ()
    | N (x, g, d) -> 
        print_int x;
        print_string " ";
        print_prefixe g;
        print_prefixe d

let rec liste_prefix1 (a: 'a ab) : 'a list =
    match a with
    | V -> []
    | N (x, g, d) -> x::(liste_prefix1 g)@(liste_prefix1 d)

let rec liste_infixe (a: 'a ab) : 'a list =
    match a with
    | V -> []
    | N (x, g, d) -> (liste_infixe g)@(x :: (liste_infixe d))

let rec liste_postfixe_aux (a: 'a ab) (aux: 'a list) : 'a list = 
    match a with
    | V -> aux
    | N (x, g, d) -> liste_postfixe_aux g (liste_postfixe_aux d (x::aux))
let liste_postfixe (a: 'a ab) : 'a list = liste_postfixe_aux a []

let rec liste_prefixe2_aux (a: 'a ab) (aux: 'a list) : 'a list = 
    match a with
    | V -> aux
    | N (x, g, d) -> x::(liste_prefixe2_aux g (liste_prefixe2_aux d aux))
let liste_prefixe2 (a: 'a ab) : 'a list = liste_prefixe2_aux a []

let rec tree_map (f: 'a -> 'b) (a: 'a ab) : 'b ab =
    match a with
    | V -> V
    | N (x, g, d) -> N (f x, tree_map f g, tree_map f d)

let rec tree_sum (a: int ab) : int = 
    match a with
    | V -> 0
    | N (x, g, d) -> x + tree_sum g + tree_sum d

let rec appartient (x: 'a) (a: 'a ab) : bool =
    match a with
    | V -> false
    | N (y, g, d) -> x = y || appartient x g || appartient x d

let rec assoc_aop (cle: 'k) (a: ('k * 'v) ab) : 'v option =
    match a with
    | V -> None
    | N((k, v), g, d) -> if k = cle then Some v else 
    match assoc_aop cle g with
        | None -> assoc_aop cle d
        | Some v -> Some v

let rec assoc_all (cle: 'k) (a: ('k * 'v) ab) : 'v list =
    match a with
    | V -> []
    | N((k, v), g, d) -> if k = cle then v::(
        assoc_all cle g @ assoc_all cle d) else
        assoc_all cle g @ assoc_all cle d

let test () = 
    let a = N(1, N(2, V, V), N(3, N(4, V, V), V)) in
    let b = N(2, V, V) in
    assert (taille a = 4);

    assert (hauteur a = 2);
    assert (hauteur b = 0);

    assert (est_feuille a = false);
    assert (est_feuille b = true);
    
    assert (feuilles a = 2);

    assert (etiquette a [true; false] = 4);
    assert (etiquette_opt a [true; false] = Some 4);
    assert (etiquette_opt a [true; true] = None);

    print_prefixe a;

    assert (liste_prefix1 a = [1; 2; 3; 4]);

    assert (liste_infixe a = [2; 1; 4; 3]);

    assert (liste_postfixe a = [2; 4; 3; 1]);

    assert (liste_prefixe2 a = [1; 2; 3; 4]);

    assert (tree_map (fun x -> x + 1) a = N(2, N(3, V, V), N(4, N(5, V, V), V)));

    assert (tree_sum a = 10);

    assert (appartient 4 a = true);

    let dico = N(("a", 1), N(("b", 2), V, V), N(("c", 3), N(("c", 4), V, V), V)) in

    assert (assoc_aop "c" dico = Some 3);
    assert (assoc_all "c" dico = [3; 4]);

    print_endline "test ok"