open Hashtbl

type huffman = 
  | Leaf of int*char
  | Node of int*huffman*huffman

let freq (h: huffman): int = match h with
  | Leaf (f, _) -> f
  | Node (f, _, _) -> f

let fusion (h1: huffman) (h2: huffman): huffman =
  let f1 = freq h1 in
  let f2 = freq h2 in
  Node(f1+f2, h1, h2)

let count_freqs (s: string): (char, int)Hashtbl.t =
  let h = Hashtbl.create 10 in

  for i = 0 to (String.length s -1) do
    if Hashtbl.mem h s.[i] then
      Hashtbl.replace h s.[i] (Hashtbl.find h s.[i] + 1)
    else
      Hashtbl.replace h s.[i] 1
  done;
  h

let huffman_leaves (s: string): huffman list = 
  let h = count_freqs s in
  Hashtbl.fold (fun cle valeur res -> (Leaf(valeur, cle))::res ) h []

let merge_sort (l: huffman list): huffman list = 
  List.sort (fun (Leaf(f1, _)) (Leaf(f2, _)) -> f1-f2) l (*Ocaml utilise merge sort pour List.sort*)

let insert_huffman (h: huffman) (l: huffman list): huffman list = 
  
  let rec aux l = match l with
    | [] -> []
    | Leaf(f,_)::q | Node(f,_,_)::q -> 
      let h2 = List.hd l in
      if freq h < f then
        h::h2::q
      else
        h2::aux q
  in
  aux l

let rec fusion_huffman (l: huffman list): huffman = match l with
  | [] -> failwith "list vide"
  | [h] -> h
  | h1::h2::q ->
      let h = fusion h1 h2 in
      let l2 = insert_huffman h q in
      fusion_huffman l2