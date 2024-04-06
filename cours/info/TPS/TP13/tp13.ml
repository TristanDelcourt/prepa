type couleur = Rouge | Noir

type 'a noeud_arn =
    | F of 'a
    | N of couleur * 'a * 'a noeud_arn * 'a noeud_arn

type 'a arn = 'a noeud_arn option

exception Erreur_hauteur_noire

let feuilles (a: 'a arn) : int =
    let rec feuilles_noeud (aa: 'a noeud_arn) : int = match aa with
        | F x -> 1
        | N(c, x, g, d) -> feuilles_noeud g + feuilles_noeud d
    in match a with
    | None -> 0
    | Some r -> feuilles_noeud r

let couleur_noeud (a: 'a noeud_arn) : couleur = match a with
    | F _ -> Noir
    | N(c, _, _, _) -> c

let rec noeud_rouge_consecutifs (a: 'a noeud_arn) : bool = match a with
    | F _ -> false
    | N(Rouge, _, N(Rouge, _, _, _), _) -> true
    | N(Rouge, _, _, N(Rouge, _, _, _)) -> true
    | N(_, _, g, d) -> noeud_rouge_consecutifs g || noeud_rouge_consecutifs d

let rec hauteur_noir (a: 'a noeud_arn) = match a with
    | F _ -> 1
    | N(c, _, g, d) -> 
        let hg = hauteur_noir g in
        let hd = hauteur_noir d in
        if hg = hd then 
            if c = Rouge then hg else hg + 1
        else raise Erreur_hauteur_noire

let arn_valide (a: 'a arn) : bool = match a with
    | None -> false
    | Some r -> couleur_noeud r = Noir && not (noeud_rouge_consecutifs r) && hauteur_noir r > 0

let correctionARN (a: 'a noeud_arn) : 'a noeud_arn = match a with
    | N(_, x, N(Rouge, y, N(Rouge, z, g_z, d_z), d_y), d_x) -> N(Rouge, y, N(Noir, x, g_z, d_z), N(Noir, x, d_y, d_x))
    | N(_, x, N(Rouge, y, g_y, N(Rouge, z, g_z, d_z)), d_x) -> N(Rouge, y, N(Noir, x, g_y, g_z), N(Noir, x, d_z, d_x))
    | N(_, x, g_x, N(Rouge, y, N(Rouge, z, g_z, d_z), d_y)) -> N(Rouge, y, N(Noir, x, g_x, g_z), N(Noir, x, d_z, d_y))
    | N(_, x, g_x, N(Rouge, y, g_y, N(Rouge, z, g_z, d_z))) -> N(Rouge, y, N(Noir, x, g_x, g_y), N(Noir, x, g_z, d_z))
    | _ -> a

let rec insertARNrelaxe (a: 'a noeud_arn) (x: 'a) : 'a noeud_arn = match a with
    | N(c, y, g, d) -> 
        if x<y then
            correctionARN(N(c, y, insertARNrelaxe g x, d))
        else if x>y then
            correctionARN(N(c, y, g, insertARNrelaxe d x))
        else a
    | F(y) -> 
        if x<y then 
            N(Rouge, x, F(x), F(y)) 
        else if x>y then
            N(Rouge, y, F(y), F(x))
        else a

let test () = 
    let a = Some(N(Rouge, 1, F 2, F 3)) in
    let b = Some(N(Rouge, 1, N(Rouge, 2, F 3, F 4), F 5)) in
    let c = Some(N(Noir, 1, N(Rouge, 2, F 3, F 4), F 5)) in

    assert(feuilles a = 2);
    assert(feuilles c = 3);

    assert(couleur_noeud (F 1) = Noir);
    assert(couleur_noeud (N(Rouge, 1, F 2, F 3)) = Rouge);

    assert(noeud_rouge_consecutifs (F 1) = false);
    assert(noeud_rouge_consecutifs (N(Rouge, 5, N(Rouge, 3, F 2, F 4), F 6)) = true);
    assert(noeud_rouge_consecutifs (N(Noir, 5, N(Rouge, 3, F 2, F 4), F 6)) = false);

    assert(hauteur_noir (F 1) = 1);
    assert(hauteur_noir (N(Noir, 1, F 2, F 3)) = 2);

    assert(arn_valide a = false);
    assert(arn_valide b = false);
    assert(arn_valide c = true);
