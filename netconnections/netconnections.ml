let readline f =
   try Some (input_line f)
   with End_of_file -> None;;

let line_count filename =
   let f = open_in filename in
   let rec loop count =
     match (readline f) with
       | Some(_) -> loop (count+1)
       | None -> count in
   loop 0;;

let filename = process_arg(0)
Printf.printf "args: %s\n" filename
(*let count = line_count filename in*)
Printf.printf "Done: %d\n" count;; 

