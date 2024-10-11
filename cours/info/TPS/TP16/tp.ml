type graphe = int list array

let g0 = [|
  [1];
  [2;3];
  [0;3];
  []
|]

let nb_aretes (g: graphe): int = 
  let len = Array.length g in
  let m = ref 0 in

  for i = 0 to len-1 do
    m := !m + List.length (g.(i))
  done;

  !m

let nb_aretes (g: graphe): int = 
  (nb_aretes g) / 2

let fast_exp (a: int) (b: int): int = 
  let x = ref a in
  let e = ref b in
  let y = ref 1 in

  while (!e <> 0) do
    if (!e mod 2 = 1) then(
      y := !x * !y;
      e := !e - 1)
    else(
      x := !x * !x;
      e := !e/2)
  done;

  !y

type 'a pile = 'a list ref
let pile_vide () = ref []

let empiler (p: 'a pile) (a: 'a): unit = 
  p := a::!p

let depiler (p: 'a pile): 'a = 
  match !p with
    | [] -> failwith "Pas d'éléments a dépiler"
    | x::q -> 
      p := q;
      x

let est_vide (p: 'a pile): bool = 
  !p = []
      
let noter_composante_source (g: graphe) (s: int) (k: int) (c: int array) : unit = 
  let p = pile_vide () in
  empiler p s;
  c.(s) <- k;

  while not (est_vide p) do
    let u = depiler p in

    let rec traiter_voisins list_voisins = 
      match list_voisins with
        | [] -> ()
        | x::q -> 
          if c.(x) = -1 then
            begin
            c.(x) <- k;
            empiler p x
            end;
          traiter_voisins q
    in
    traiter_voisins g.(u)

  done

let composantes_connexes (g: graphe): int array = 
  let c = Array.make (Array.length g) (-1) in

  let rec aux c k = 
    match Array.find_index (fun x -> x = -1) c with
      | None -> c
      | Some i -> 
        noter_composante_source g i k c;
        aux c (k+1)
      in
  aux c 1 

let g1 = [|
  [1;2];
  [0;2];
  [0;1];

  [4;6];
  [3;5;6];
  [4;6];
  [3;4;5];

  [8;11];
  [7;9];
  [8;10];
  [9;11];
  [7; 10]
|]