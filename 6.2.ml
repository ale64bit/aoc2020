module S = Set.Make(Char)

let solve =
  let rec read_groups cur acc = 
    let open List in
    let count xs = 
      let ss = map (fun s -> S.of_list (of_seq (String.to_seq s))) xs in
      S.cardinal (fold_left S.inter (hd ss) ss)
    in
    try 
      let line = read_line () in
      if (String.length line) = 0 
      then read_groups [] ((count cur) + acc)
      else read_groups (line :: cur) acc
    with End_of_file -> (count cur) + acc
  in
  let ans = read_groups [] 0 in
  Printf.printf "%d\n" ans
