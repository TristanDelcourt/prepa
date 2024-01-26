let rec puiss a b = 
    if b = 1 then a else puiss a (b-1) * a
;;

let rec reste a b =
    if a < b then a else reste (a-b) b
;;

let rec pgcd a b =
    let r = reste a b in
    if r = 0 then b else pgcd b r
;;

let rec div_eucl a b =
    if a < b then (0, a) else
        let q, r = div_eucl (a-b) b in
        (q+1, r)
;;

let rec a_racine f a b =
    if (f a) = 0 then true else
    if a = b then false else
    a_racine f (a+1) b
;;