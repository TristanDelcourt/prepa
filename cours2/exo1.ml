type automate_d = {
  init : int; (* l'état initial *)
  trans : int array array; (* la table des transitions *)
  fin : int list (* la liste des états finaux *)
}

let auto_1 = {
  init = 0; trans =
   (*| a | b | c | d | e |*)
  [|[| 1 ; 0 ; 0 ; 4 ; 4 |]; (* état 0 *)
    [| 2 ; 4 ; 4 ; 1 ; 4 |]; (* état 1 *)
    [| 3 ; 2 ; 2 ; 4 ; 4 |]; (* état 2 *)
    [| 0 ; 4 ; 4 ; 4 ; 3 |]; (* état 3 *)
    [| 4 ; 4 ; 4 ; 4 ; 4 |]  (* état 4 *)
  |];
  fin = [2]
   }

let int_of_letter (c: char) : int = 
  let ascii = int_of_char c in
  if (ascii<97 || ascii>122) then
    failwith "non"
  else (ascii - 97)

let delta (a: automate_d) (q: int) (l: char) : int = 
  let letter = int_of_letter l in
  (a.trans).(q).(letter)

let delta_etoile (a: automate_d) (q: int) (s: string) : int =
  let n = String.length s in
  let rec aux i q1 = 
    if i<n then
      aux (i+1) (delta a q1 (String.get s i))
    else
      q1 in
  aux 0 q

let accepte (a: automate_d) (w: string) : bool = 
  let f = delta_etoile a (a.init) w in
  List.mem f (a.fin)

let rec accepte_depuis (a: automate_d) (q: int) (w: string) (i: int): bool = 
  if i == String.length w then
    List.mem q (a.fin)
  else
    accepte_depuis a (delta a q (String.get w (i))) w (i+1)

let accepte_alt (a: automate_d) (w: string) : bool =
  accepte_depuis a (a.init) w 0

type automate_nd = {
  init : int list; (* les états initiaux *)
  trans : int list array array; (* la table des transitions *)
  fin : int list (* les états finaux *)
}

let auto_2 = {
  init = [0];
  trans =
      (* a   |  b   | c  |*)
  [|[| [0; 1]; [0] ; [3] |]; (* état 0 *)
    [| [2]   ; [2] ; [3] |]; (* état 1 *)
    [| []    ; []  ; [3] |]; (* état 2 *)
    [| [3]   ; [3] ; [3] |]  (* état 3 *)
  |];
  fin = [2; 3]
}

let est_deterministe (a: automate_nd): bool = 
  
