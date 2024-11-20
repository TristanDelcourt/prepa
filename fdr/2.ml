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

