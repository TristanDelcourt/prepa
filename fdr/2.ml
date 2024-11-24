let premier_zero a = 
  let zero = ref (-1) in
  let n = Array.length a in
  let i = ref (n-1) in

  while !i > 0 do
    if a.(!i) = 0 then
      zero := !i;
    i := !i - 1
  done;

  !zero

exception TrouveZero of int
let premier_zero_exception a =
  try 
    for i = 0 to Array.length a - 1 do
      if a.(i) = 0 then
        raise (TrouveZero i)
    done;
    -1 
  with
    | TrouveZero i -> i

let dernier_zero a = 
  let zero = ref (-1) in
  let n = Array.length a in
  let i = ref (0) in

  while !i < n do
    if a.(!i) = 0 then
      zero := !i;
    i := !i + 1
  done;

  !zero

let zero_existe a = 
  let zero = ref (false) in
  let n = Array.length a in
  let i = ref (0) in

  while !i < n && not !zero do
    if a.(!i) = 0 then
      zero := true;
    i := !i + 1
  done;

  !zero

exception ZeroExist
let zero_existe_iter a =
  try
    Array.iter (fun x -> if x=0 then raise ZeroExist) a;
    false
  with
    | ZeroExist -> true

let somme a = 
  let s = ref 0 in

  for i = 0 to Array.length a -1 do
    s := !s + a.(i)
  done;

  !s

let somme_fold a = 
  Array.fold_left (+) 0 a

let ind_min a =
  match Array.length a with
    | 0 -> raise (Invalid_argument "taille de 0")
    | n -> 
      let imin = ref 0 in
      for i = 0 to n - 1 do
        if a.(i) < a.(!imin) then
          imin := i;
      done;
      !imin

let ind_max_fold a =
  if Array.length a = 0 then
    raise (Invalid_argument ("non"))
  else
    match Array.fold_left (fun (imax, i) x -> if a.(imax) < x then (i, i+1) else (imax, i+1)) (0, 0) a with
      | (imax, i) -> imax

let somme_cumule a = 
  let s = ref 0 in
  let out = Array.make (Array.length a) 0 in

  for i = 0 to Array.length a -1 do
    s := !s + a.(i);
    out.(i) <- !s
  done;

  out

let truc t =

  for i = 0 to Array.length t - 1 do
    t.(i) <- i::t.(i)
  done

let truc2 t x = 
  Array.map (fun l -> match l with | y::q -> (x+y)::q | _ -> raise (Invalid_argument"liste vide")) t


let max_m t m = 
  let occ = Array.make m 0 in
  let xmax = ref 0 in
  Array.iter (fun x -> 
    occ.(x) <- occ.(x) + 1;
    if occ.(x) > occ.(!xmax) then xmax := x) t;
  !xmax