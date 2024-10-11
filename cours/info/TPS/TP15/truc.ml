let array_range (n: int): int array = 
    let t = Array.make n 0 in
    for i = 0 to n-1 do
      t.(i) <- i
    done;
    t

let somme (t: int array): int =
  let res = [|0|] in
  let n = Array.length t in
  for i = 0 to n-1 do
    res.(0) <- res.(0) + t.(i)
  done;
  res.(0)


let somme2 (t: int array): int =
    let res = ref 0 in
    let n = Array.length t in
    for i = 0 to n-1 do
      res := !res + t.(i)
    done;
    !res

let argmax_indc_min (t: 'a array) (j: int) : int = 
  let k = ref j in
  let max = ref t.(j) in
  let n = Array.length t in
  for i = j to n-1 do
    if !max < t.(i) then
      (k := i;
      max := t.(i))
  done;
  !k

  let argmax_indc_max (t: 'a array) (j: int) : int = 
    let k = ref j in
    let max = ref t.(j) in
    for i = 0 to j do
      if !max < t.(i) then
        (k := i;
        max := t.(i))
    done;
    !k

let argmax t = argmax_indc_min t 0

let tri_selection (t: int array): unit = 
  let n = Array.length t in
  for i = 0 to n-2 do
    let k = argmax_indc_min t i in
    print_int i; print_int k; print_newline ();
    let temp = t.(k) in
    t.(k) <- t.(i);
    t.(i) <- temp
  done

let glouton_prix (c: 'a array) (n: int) : int list = 
  let i_max = Array.length c -1 in
  let k_max  = argmax c in

  let rec aux c n = 
    if n <= i_max then
      let k = argmax_indc_max c n in
        if k = n then 
          [k]
        else 
          k::(aux c (n-k))
    else
      k_max::(aux c (n-k_max))
  in
  aux c n

let ratio (t: int array) : float array =
  let n = Array.length t in 
  let out = Array.make n 0. in
  for i = 1 to n-1 do
    out.(i) <- (float_of_int t.(i))/. (float_of_int i)
  done; out

let glouton_ratio (c: int array) (n: int) : int list = 
  glouton_prix (ratio c) n

let decoupe_pro_dyn c n = 
  let grd_k = Array.length c in
  let mem = Array.make (n+1) (-1, []) in

  let rec calculer_decoupe i = 
    let mi, _ = mem.(i) in
    if mi = -1 then begin
      if i = 0 then
        mem.(i) <- (0, [])
      else 
        for k = 1 to (if i>=grd_k  then grd_k-1 else i) do
          mem.(i-k) <- calculer_decoupe (i-k);
          let (c1, l1) = mem.(i-k) in
          let (c2, l2) = mem.(i) in
          if c.(k) + c1 > c2 then 
            mem.(i) <- (c.(k) + c1, k::l1)
        done
      end;
      mem.(i)
    in calculer_decoupe n