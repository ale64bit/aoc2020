open List

let solve =
  let rec read_groups h acc = 
    try 
      let open String in
      let line = read_line () in
      if (length line) = 0 
      then read_groups "" (h :: acc)
      else read_groups (concat "" [line; h]) acc
    with End_of_file -> h :: acc
  in
  let groups = read_groups "" [] in
  let ans = fold_left (fun acc g -> 
    let xs = List.of_seq (String.to_seq g) in
    acc + (length (sort_uniq compare xs))) 0 groups 
  in
  Printf.printf "%d\n" ans
