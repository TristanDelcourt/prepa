type graphe =  (* graphes par table de listes de successeurs *)
  int list array

let g0: graphe =
  [|
    [1; 2; 3]; (* 0 *)
    [4];       (* 1 *)
    [];        (* 2 *)
    [];        (* 3 *)
    [5];       (* 4 *)
    []         (* 5 *)
  |]

let g1: graphe =
  [|
    [1; 2; 3]; (* 0 ou a*)
    [4];       (* 1 ou b*)
    [3; 4];    (* 2 ou c*)
    [5];       (* 3 ou d*)
    [5];       (* 4 ou e*)
    []         (* 5 ou f*)
  |]


let g2: graphe =
  [|
    [1];       (* 0 ou a*)
    [2; 4];    (* 1 ou b*)
    [3];       (* 2 ou c*)
    [];        (* 3 ou d*)
    [0];       (* 4 ou e*)
    [3]        (* 5 ou f*)
  |]

let g3: graphe =
  [|
    [1; 4];    (* 0 ou a*)
    [5; 6];    (* 1 ou b*)
    [1];       (* 2 ou c*)
    [0];       (* 3 ou d*)
    [3; 5];    (* 4 ou e*)
    [6];       (* 5 ou f*)
    [2; 7];    (* 6 ou g*)
    [2]        (* 7 ou h*)
  |]

let g4: graphe =
  [|
    [5];       (* 0 ou a*)
    [0; 2];    (* 1 ou b*)
    [3];       (* 2 ou c*)
    [1];       (* 3 ou d*)
    [0; 3];    (* 4 ou e*)
    [4]        (* 5 ou f*)
  |]

let g5 =
  [|
    [2; 3];    (* 0 ou a*)
    [0];       (* 1 ou b*)
    [5];       (* 2 ou c*)
    [2; 4];    (* 3 ou d*)
    [];        (* 4 ou e*)
    []         (* 5 ou f*)
  |]


let g6 =
  [|
    [];        (* 0 *)
    [0; 2];    (* 1 *)
    [1; 3];    (* 2 *)
    [4];       (* 3 *)
    [2];       (* 4 *)
    [3];       (* 5 *)
    [4; 7];    (* 6 *)
    [5; 6];    (* 7 *)
  |]

(*non orienté 2 composantes connexe*)
let g7 =
  [|
    [1];        (* 0 *)
    [0; 2];     (* 1 *)
    [1];        (* 2 *)
    [4; 5];     (* 3 *)
    [3; 6];     (* 4 *)
    [3];        (* 5 *)
    [4; 7];     (* 6 *)
    [6];        (* 7 *)
  |]

(*non orienté non biparti*)
let g8 =
  [|
    [1];        (* 0 *)
    [0; 2];     (* 1 *)
    [1; 3];     (* 2 *)
    [2; 4; 5];  (* 3 *)
    [3; 6];     (* 4 *)
    [3; 7];     (* 5 *)
    [4; 7];     (* 6 *)
    [5; 6];     (* 7 *)
  |]

(*non orienté biparti*)
let g9 =
  [|
    [1];        (* 0 *)
    [0; 2];     (* 1 *)
    [1; 3];     (* 2 *)
    [2; 5];     (* 3 *)
    [6];        (* 4 *)
    [3; 7];     (* 5 *)
    [4; 7];     (* 6 *)
    [5; 6];     (* 7 *)
  |]

let imprime_parcours_profondeur_1 (g: graphe) = 
  let rec aux i = 
    print_int i;
    print_newline ();
    List.iter aux g.(i)
  in aux 0

  let imprime_parcours_profondeur_2 (g: graphe) = 
    let vu = ref [] in
    let rec aux i = 
      vu := i::!vu;
      print_int i;
      print_newline ();
      let rec iter_liste l = match l with
        | [] -> ()
        | j::q ->
          if List.mem j !vu then 
            () 
          else 
            aux j; iter_liste q
      in
      iter_liste g.(i)
    in
    aux 0

let imprime_parcours_profondeur_2_bool (g: graphe) = 
  let vu = ref (Array.make (Array.length g) false) in
  let rec aux i = 
    !vu.(i) <- true;
    print_int i;
    print_newline ();
    let rec iter_liste l = match l with
      | [] -> ()
      | j::q ->
        if !vu.(j) then 
          () 
        else 
          aux j; iter_liste q
    in
    iter_liste g.(i)
  in
  aux 0

let imprime_parcours_profondeur_2_bis (g: graphe) = 
  let vu = ref (Array.make (Array.length g) false) in
  let rec aux (i: int) = 
    !vu.(i) <- true;
    print_int i;
    print_newline ();
    List.iter (fun j -> if !vu.(j) then () else aux j) g.(i)
  in
  aux 0

let imprime_parcours_profondeur_3 (g: graphe) = 
  let trouver_premier_false = Array.find_index (fun x -> not x) in

  let vu = ref (Array.make (Array.length g) false) in
  let rec recherche (i: int) = 
    !vu.(i) <- true;
    print_int i;
    print_newline ();
    List.iter (fun j -> if !vu.(j) then () else recherche j) g.(i)
  in

  let rec loop () = match trouver_premier_false !vu with
    | None -> ()
    | Some(i) -> recherche i; loop ();
  in
  loop ()

let imprime_parcours_profondeur_3_bis (g: graphe) = 
  let vu = ref (Array.make (Array.length g) false) in

  let rec recherche (i: int) = 
  if not !vu.(i) then
  begin
    !vu.(i) <- true;
    print_int i;
    print_newline ();
    List.iter (fun j -> if !vu.(j) then () else recherche j) g.(i)
  end
  in

  let n = Array.length g in
  for i=0 to n-1 do
    recherche i
  done

let composantes_connexes (g: graphe): int array = 
  let trouver_premier_false = Array.find_index (fun x -> x = 0) in
  let vu = ref (Array.make (Array.length g) 0) in

  let rec recherche (i: int) (ind: int) = 
  if !vu.(i) = 0 then
  begin
    !vu.(i) <- ind;
    List.iter (fun j -> if !vu.(j) = 0 then recherche j ind else ()) g.(i)
  end
  in

  let ind = ref 1 in
  let rec loop () = match trouver_premier_false !vu with
    | None -> !vu
    | Some(i) ->
      recherche i !ind;
      ind := !ind + 1;
      loop ()
  in
  loop ()

let biparti (g: graphe) = 
  let n = Array.length g in
  let vu = ref (Array.make n 0) in
  
  let rec recherche (dist: int) (origine: int) (i: int)  = 
    if !vu.(i) = 0 then
    begin
      !vu.(i) <- dist;
      List.exists (fun x -> x) (List.map (recherche (dist+1) origine) g.(i))
    end
    else if i = origine && dist mod 2 = 1 then true else false
  in

  let res = ref false in
  for i=0 to n-1 do
    res := (!res || recherche 0 i i);
    vu := Array.make n 0
  done;

  not !res

let distance (g: graphe) (s1: int) (s2: int) = 
  let n = Array.length g in
  let vu = ref (Array.make n 0) in
  
  let rec recherche (dist: int) (i: int)  = 
    if dist < !vu.(i) || !vu.(i) = 0 then 
    begin
      !vu.(i) <- dist;
      List.iter (recherche (dist + 1)) g.(i)
    end
  in

  recherche 0 s1;
  !vu.(s2)

(*Q13 Un grahe orienté admet un tri topologique ssi il est acyclique*)

let acyclique (g: graphe): bool = 
  let n = Array.length g in
  let vu = ref (Array.make n 0) in
  
  let rec recherche (dist: int) (origine: int) (i: int)  = 
    if !vu.(i) = 0 then
    begin
      !vu.(i) <- dist;
      List.exists (fun x -> x) (List.map (recherche (dist+1) origine) g.(i))
    end
    else if i = origine then true else false
  in

  let res = ref false in
  for i=0 to n-1 do
    res := (!res || recherche 0 i i);
    vu := Array.make n 0
  done;

  not !res