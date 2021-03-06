let chartab = [|
    -12; -12; -12; -12;  -2; -12; -12; -12
    -12; -18;  -2; -12; -12; -18; -12; -12
    -12; -12; -12; -12; -12; -12; -12; -12
    -12; -12; -12; -12; -12; -12; -12; -12
    -18; -16; -14; -12; -16; -16; -16; -10
    -16; -16; -16; -16; -16; -16;  46;  -6
    +48;  49;  50;  51;  52;  53;  54;  55
    +56;  57; -16;  -2;   0; -16; -12; -12
    -12;  65;  66;  67;  68;  69;  70;  71
    +72;  73;  74;  75;  76;  77;  78;  79
    +80;  81;  82;  83;  84;  85;  86;  87
    +88;  89;  90; -16; -20; -16; -16;  95
    -12;  97;  98;  99; 100; 101; 102; 103
    104; 105; 106; 107; 108; 109; 110; 111
    112; 113; 114; 115; 116; 117; 118; 119
    120; 121; 122; -12; -22; -12; 126; -12 |]

let keys = chartab |> Seq.sort |> Seq.distinct
let data = chartab |> Seq.mapi (fun i v -> i, v)

let convch v =
    if v < 33 || 126 < v then
        ""
    else
        (char v).ToString()

for key in keys do
    let values =
       data
    |> Seq.filter (fun (_, v) -> key = v)
    |> Seq.map fst
    |> Seq.toArray
    if not (values.Length = 1 && values.[0] = key) then
        let s1 =
           values
        |> Seq.map (fun v -> sprintf "%d%s" v (convch v))
        |> String.concat ", "
        let s2 = 
           values
        |> Seq.map convch
        |> String.concat ""
        printfn "%3d: %s; %s" key s1 s2

printf " >0: "
chartab |> Array.mapi (fun i v ->
    if i = v then
        let s = convch v
        if s = "" then
            printf "(%d)" i
        else
            printf "%s" s)
printfn ""
