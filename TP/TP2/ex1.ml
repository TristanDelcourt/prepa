type 'a ab = 
  | VideB
  | NdB of 'a * ('a ab) * ('a ab)
  
type 'a ab_g = 
  | Vide
  | Nd of 'a * ('a ab_g) list

let ab0 = VideB
let ab1 = NdB (1, VideB, VideB)
let ab2 = NdB (1, NdB (2, VideB, VideB), VideB)
let ab3 = NdB (1, NdB (4, NdB(5, VideB, VideB), NdB(6, VideB, VideB)), NdB(8, VideB, VideB))


let a1 = Nd ('a', [Vide; Vide; Vide])
let a2 = Nd(1, [ Nd(11, [Vide]);
                 Nd(15, [Nd(16, [Vide; Vide]); Nd(17, []); Nd(18, [Vide])])])
let a3 = Nd(1, [Nd(2, [Nd(3, [Nd(30, []); Nd(31, []); Nd(32, [])])])])
let a4 = Nd(1, [Nd(2, [Nd(5, [Vide]); Nd(6, [Vide])]);
                Nd(3, [Nd(7, [Vide])]); Nd(4, [Vide])])
let a5 = Nd(1, [Nd(2, [Nd(4, [Vide]);
                       Nd(5, [Nd(7, [Vide]); Nd(8, [Vide])]);
                       Nd(6, [Nd(9, [Vide])])]) ;
                Nd(3, [Vide]) ])
  

(*Affiche les noeuds de l'arbre a en parcours préfixe*)
let rec affiche_arbre_g_prefixe (a: int ab_g) : unit =
  match a with
    | Vide -> ()
    | Nd (k, l) -> 
      print_int k;
      print_newline ();
      let rec aux l1 = 
        match l1 with 
          | [] -> ()
          | sa::q -> affiche_arbre_g_prefixe sa; aux q
      in aux l

let rec affiche_arbre_g_prefixe_bis (a: int ab_g) : unit =
  match a with
    | Vide -> ()
    | Nd (k, l) -> 
      print_int k;
      print_newline ();
      List.iter affiche_arbre_g_prefixe_bis l;

