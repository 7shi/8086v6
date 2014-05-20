let chartab = "\000abcdefghijklmnopqrstuvwxyz0123456789_."

let convs v =
    let a = v / 40
    [ a / 40; a % 40; v % 40 ]
    |> Seq.map (fun i -> string chartab.[i])
    |> String.concat ""

let show v1 v2 =
    let s = ((convs v1) + (convs v2)).Replace("\000", "")
    printfn "%06o %06o => %s" v1 v2 s

show 0o072270 0
show 0o072340 0
show 0o072410 0
show 0o072460 0
show 0o072530 0
show 0o072600 0
show 0o074500 0
show 0o062170 0
