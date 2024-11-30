type 'a btree =
  | E (* arbre vide *)
  | N of 'a * 'a btree * 'a btree (* noeud interne *)

type 'a gtree =
  | GN of 'a * 'a gtree list

let bt1 = N(1, 
            N(2, 
              E, 
              N(3, E, E)
            ), 
            N(4, E, E)
          )

let bt2 = N(true, 
            N(false, 
              E, 
              N(false, E, E)
            ), 
            N(false, E, E)
          )

let gt1 = GN(1, [
            GN(2, []);
            GN(3, [
              GN(4, [
                GN(7, [])
              ])
            ]);
            GN(5, [
              GN(6, [])
            ])
          ])

(* DEBUT *)
let est_vide (bt: 'a btree): bool = (bt = E)

let rec hauteur (bt: 'a btree): int = match bt with
  | E -> -1
  | N (_, g, d) -> 1 + max (hauteur g) (hauteur d)

let rec taille (gt: 'a gtree): int = match gt with
  | GN (_, l) -> 1 + iter l
and iter l = match l with
  | [] -> 0
  | a::q -> taille a + iter q

let rec taille_iter (gt: 'a gtree): int = match gt with
  | GN (_, l) -> 1 + List.fold_left (fun acc a -> acc + taille_iter a) 0 l

let taille_term (gt: 'a gtree): int = 
  let rec aux acc = function
    | GN(_, l) -> List.fold_left (fun acc a -> aux (acc + 1) a) acc l
  in
  aux 1 gt

let rec intree (bt: 'a btree) (x: 'a): bool = match bt with
  | E -> false
  | N(y, g, d) -> x=y || intree g x || intree d x

let rec minmax (bt: int btree) : (int*int) option = match bt with
  | E -> None
  | N(x, g, d) -> match minmax g, minmax d with
    | None, None -> Some (x, x)
    | Some (ming, maxg), None -> Some (min x ming, max x maxg)
    | None, Some (mind, maxd) -> Some (min x mind, max x maxd)
    | Some (ming, maxg), Some (mind, maxd) -> Some (min x (min ming mind), max x (max maxg maxd))
      
let minmax_term (bt: int btree) : (int * int) option =
  let rec aux (bt: int btree) ((mi, ma): int* int) : (int * int) =
    match bt with
    | E -> (mi, ma)
    | N(x, g, d) ->
      let (ming, maxg) = aux g (min x mi, max x ma) in
      aux d (ming , maxg)
  in
  match bt with
  | E -> None
  | N(x, g, d) -> Some (aux bt (x, x))


let rec equalshape (bt1: 'a btree) (bt2: 'b btree): bool = 
  match bt1, bt2 with
    | E, E -> true
    | N(_, g1, d1), N(_, g2, d2) -> equalshape g1 g2 && equalshape d1 d2
    | _ -> false

exception TrouvePair of int
let profondeurpair (bt: int btree): int option = 
  try 
    let rec aux i t = match t with
        | E -> ()
        | N(x, g, d) -> 
          if x mod 2 = 0 then 
            raise (TrouvePair i) 
          else
            aux (i+1) g;
            aux (i+1) d
    in
    aux 0 bt;
    None
  with
    | TrouvePair p -> Some p

let test () = 
  assert(not(est_vide bt1));
  assert(hauteur bt1 = 2);
  assert(taille gt1 = 7);
  assert(taille_iter gt1 = 7);
  assert(taille_term gt1 = 7);
  assert(intree bt1 3);
  assert(not (intree bt1 654845453));
  assert(minmax bt1 = Some (1, 4));
  assert(minmax_term bt1 = Some (1, 4));
  assert(equalshape bt1 bt2);
  assert(profondeurpair bt1 = Some 1)