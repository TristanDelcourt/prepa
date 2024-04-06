type couleur = Coeur | Pique | Carreau | Trefle ;;

let couleur1 = Pique ;;


let est_rouge c = match c with
	| Coeur   -> true
	| Carreau -> true
	| Pique   -> false
	| Trefle  -> false ;;

assert (est_rouge Carreau);; (* vaut true *)

type carte = 
	| Nombre of (int * couleur) (* Cartes 2 à 10 *)
	| Valet of couleur
	| Dame of couleur
	| Roi of couleur
	| As of couleur

let carte_1 = Valet Coeur
let carte_2 = Nombre (9, Pique)

(* Renvoie la couleur d'une carte *)
let couleur_de_carte ca = match ca with
	| Nombre (_, c)  | Valet c 
	| Dame c | Roi c | As c -> c 
;;

assert (couleur_de_carte (Roi Trefle) = Trefle) ;;

let string_of_courleur (c: couleur) = match c with
    | Coeur -> "Coeur"
	| Carreau -> "Carreau"
	| Pique   -> "Pique"
	| Trefle  -> "Trefle" ;;

let string_of_carte ca = match ca with
    | Nombre (n, c) -> print_int n; print_string " de "; print_string (string_of_courleur c)
    | Valet c -> print_string "Valet de "; print_string (string_of_courleur c)
    | Dame c -> print_string "Dame de "; print_string (string_of_courleur c)
    | Roi c -> print_string "Roi de "; print_string (string_of_courleur c)
    | As c -> print_string "As de "; print_string (string_of_courleur c)