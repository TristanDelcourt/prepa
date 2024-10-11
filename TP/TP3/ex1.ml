#require "graphics"
open Graphics

(* Boite à outils *)
let list_init (n: int) (f: int -> 'a): 'a list =
  let rec aux (i: int) =
    if i >= n then []
    else (f i) :: aux (i+1)
  in aux 0
let list_remove (x: 'a) (l: 'a list) = List.filter (fun y -> y <> x) l
let sqrt2 = sqrt 2.

(* Module de représentation des réels ou +∞ *)
module Floatb =
struct
  type t =
    | F of float
    | Infini                      (* ∞ *)
  let print (x: t) =
    match x with
    | Infini -> print_string "+∞"
    | F i  -> print_float i
  let inf (x1: t) (x2: t) =     (* x1 < x2 ? *)
    match x1, x2 with
    | Infini, _ -> false
    | _, Infini -> true
    | F i1, F i2 -> i1 < i2
  let add (x1: t) (x2: t) =     (* x1 + x2 *)
    match x1, x2 with
    | Infini, _ | _, Infini -> Infini
    | F i1, F i2 -> F (i1 +. i2)
end

(* Définition des types *)
type cell = int * int           (* x, y *)
type cell_l = int               (* version linéarisée des cellules *)

type world =
  {
    w         : int       ;
    h         : int       ;
    obstacles : cell list ;
  }

let lin (w: world) ((cx, cy): cell) : cell_l =
  cx * w.w + cy
let delin (w: world) (i: cell_l): cell =
  (i / w.w, i mod w.w)

(* Exemples de mondes *)
let w_ex_0 =
  {
    w = 4;
    h = 4;
    obstacles = [(2, 0); (2, 1); (2, 2)]
  }


let w_ex_1 =
  {
    w = 11;
    h = 11;
    obstacles = []
  }

let w_ex_2 =
  {
    w = 10;
    h = 10;
    obstacles = list_init 4 (fun i -> (3, i))
  }

let w_ex_3 =
  {
    w = 25;
    h = 25;
    obstacles = list_init 13 (fun i -> (6, i + 6))
                @ list_init 13 (fun i -> (18, i + 6))
                @ list_init 13 (fun i -> (i + 6, 6))
                @ list_init 6 (fun i -> (i + 6, 18))
                @ list_init 6 (fun i -> (i + 13, 18))
  }

(* Calcul des voisins *)
let voisin (w: world) ((cx, cy): cell): (cell * float) list =
  let possibles =
    [((cx-1, cy+1), sqrt2); ((cx  , cy+1), 1.); ((cx+1, cy+1), sqrt2);
     ((cx-1, cy  ), 1.   );                     ((cx+1, cy  ), 1.   );
     ((cx-1, cy-1), sqrt2); ((cx  , cy-1), 1.); ((cx+1, cy-1), sqrt2);
    ]
  in
  List.filter (fun ((cx, cy), _) ->
      cx >= 0 && cy >= 0 && cx < w.w && cy < w.h && (not (List.mem (cx, cy) w.obstacles))
    ) possibles


(* Graphique *)
let c_col1 = Graphics.rgb 168 27 3
let c_col2 = Graphics.rgb 210 160 4
let c_col3 = Graphics.rgb 105 105 0
let c_col4 = Graphics.rgb 109 129 98


type algo_step = {
  fini : int list;              (* la liste des sommets traités   *)
  todo : int list;              (* la liste des sommets à traités *)
  mu   : Floatb.t array;        (* le tableau des poids           *)
  pi   : int option array;      (* le tableau des prédecesseurs   *)
  src  : cell ;                 (* la source de la recherche      *)
  obj  : cell                   (* l'objectif de la recherche     *)
}

let draw_world
    (etat_algo: algo_step option)
    (w: world)
  =
  let sx = Graphics.size_x () -10 in
  let sy = Graphics.size_y () -10 in
  let c_w_x = sx / w.w in
  let c_w_y = sy / w.h in
  let ratio = min c_w_x c_w_y in
  Graphics.set_line_width 3;
  List.iter (fun (cx, cy) ->
      Graphics.set_color Graphics.black;
      Graphics.fill_rect (5+ cx * ratio) (5+cy * ratio) ratio ratio;
    ) w.obstacles;
  begin
    match etat_algo with
    | None -> ()
    | Some (algo_step) ->
      (* On colorie les sommets finis *)
      List.iter (fun i ->
          let cx, cy = delin w i in
          Graphics.set_color c_col3;
          Graphics.fill_rect (5+cx * ratio) (5+cy * ratio) ratio ratio;
        ) algo_step.fini;
      (* On relie les sommets finis à leur pères*)
      List.iter (fun i ->
          let cx, cy = delin w i in
          match algo_step.pi.(i) with
          | None -> assert false
          | Some j ->
            let cxp, cyp = delin w j in
            Graphics.set_color c_col1;
            Graphics.moveto (5+cx * ratio + ratio/2) (5+cy * ratio + ratio/2);
            Graphics.lineto (5+cxp * ratio + ratio/2) (5+cyp * ratio + ratio/2);
        ) algo_step.fini;
      (*On dessine les sommet à traiter, coloriage + père *)
      List.iter (fun i ->
          let cx, cy = delin w i in
          Graphics.set_color c_col4;
          Graphics.fill_rect (5+cx * ratio) (5+cy * ratio) ratio ratio;
          match algo_step.pi.(i) with
          | None -> assert false
          | Some j ->
            let cxp, cyp = delin w j in
            Graphics.set_color c_col2;
            Graphics.moveto (5+cx * ratio + ratio/2) (5+cy * ratio + ratio/2);
            Graphics.lineto (5+cxp * ratio + ratio/2) (5+cyp * ratio + ratio/2);
        ) algo_step.todo;
      (* on dessine la source *)
      Graphics.set_color c_col1;
      let cxd, cyd = algo_step.src in
      Graphics.fill_circle (5+cxd * ratio + ratio/2) (5+cyd * ratio + ratio/2) (ratio / 4);
      (* on dessine l'objectif *)
      Graphics.set_color c_col1;
      let cxf, cyf = algo_step.obj in
      Graphics.fill_circle (5+cxf * ratio + ratio/2) (5+cyf * ratio + ratio/2) (ratio / 4);
  end;
  Graphics.set_line_width 1;
  Graphics.set_color Graphics.black;
  for x = 0 to (w.w) do
    Graphics.moveto (5+x * ratio) (5);
    Graphics.lineto (5+x * ratio) (5+w.h * ratio);
  done;
  for y = 0 to (w.h) do
    Graphics.moveto (5) (5+y * ratio);
    Graphics.lineto (5+w.w * ratio) (5+y * ratio);
  done

let find_min (l: int list) (mu: Floatb.t array): int = 
  let min = ref mu.(0) in
  List.iter (fun i -> if Floatb.inf mu.(i) !min then min := mu.(i)) l;
  match List.find_index (fun j -> mu.(j) = !min) l with
    | None -> 0
    | Some i -> i

let dijkstra (w: world) (s: cell) (dest: cell): Floatb.t = 
  let mu = Array.make (w.h * w.w) (Floatb.Infini) in
  let pi = Array.make (w.h * w.w) None in
  mu.(lin w s) <- F(0.);
  pi.(lin w s) <- Some 0;
  let todo = ref [lin w s] in

  let relax (u: cell) ((v, c): cell * float) = 
    let u_l, v_l = lin w u, lin w v in
    if Floatb.inf (Floatb.add mu.(u_l) (F c)) mu.(v_l) then
    begin
      mu.(v_l) <- Floatb.add mu.(u_l) (F c);
      pi.(v_l) <- Some u_l;
      todo := v_l::!todo
    end
    in

    while not (!todo = []) do
      let u_l = List.nth !todo (find_min !todo mu) in
      let u = delin w u_l in
      List.iter (relax u) (voisin w u);
      todo := list_remove u_l !todo
    done;
    mu.(lin w dest)

let heuristic ((x1, y1): cell) ((x2, y2): cell) = 
  (x1-x2)*(x1-x2) + (y1-y2)*(y1-y2)

let a_star (w: world) (estimation: cell -> cell -> int) (s: cell) (dest: cell): Floatb.t = 
  let h = estimation dest in

  let mu = Array.make (w.h * w.w) (Floatb.Infini) in
  let nu = Array.make (w.h * w.w) (Floatb.Infini) in
  let pi = Array.make (w.h * w.w) None in
  mu.(lin w s) <- F(0.);
  nu.(lin w s) <- F (float_of_int (h s));
  pi.(lin w s) <- Some 0;
  let todo = ref [lin w s] in

  let relax (u: cell) ((v, c): cell * float) = 
    let u_l, v_l = lin w u, lin w v in
    if Floatb.inf (Floatb.add mu.(u_l) (F c)) mu.(v_l) then
    begin
      mu.(v_l) <- Floatb.add mu.(u_l) (F c);
      nu.(v_l) <- Floatb.add mu.(v_l) (F (float_of_int (h v)));
      pi.(v_l) <- Some u_l;
      todo := v_l::!todo
    end
    in

    let u_l = ref (lin w s) in
    while (not (!todo = [])) && (!u_l <> (lin w dest)) do
      let u = delin w !u_l in
      List.iter (relax u) (voisin w u);
      u_l := List.nth !todo (find_min !todo nu);
      todo := list_remove !u_l !todo
    done;
    mu.(lin w dest)