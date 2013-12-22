open System
open System.Collections.Generic
open System.IO

if not <| File.Exists "run" then Directory.SetCurrentDirectory "../.."

let as1 = Array.map Path.GetFileName (Directory.GetFiles(".", "as1?.s"))
let as2 = Array.map Path.GetFileName (Directory.GetFiles(".", "as2?.s"))

type Token = None | Sym | Other

type Lexer(src:string) =
    let mutable i = 0
    let isspc ch = ch <= ' '
    let issym () =
        let start = i
        fun ch ->
            ch = '_' || Char.IsLetter ch ||
            (start < i && (
                Char.IsDigit ch || ch = '.'))
    let readWhile (f:char -> bool) =
        if i >= src.Length then "" else
        let start = i
        let sw = new StringWriter()
        while i < src.Length && f src.[i] do i <- i + 1
        src.[start .. i - 1]

    member x.read () =
        ignore <| readWhile isspc
        if i >= src.Length then None, "" else
        let ch = src.[i]
        let issym = issym ()
        if issym ch then
            Sym, readWhile issym
        else
            i <- i + 1
            Other, string ch

let getlabel srcs =
    let labels = new Dictionary<string, List<string>>()
    let usage = new Dictionary<string, List<string>>()
    let getlabel s =
        let list = new List<string>()
        let lexer = new Lexer(File.ReadAllText s)
        let rec loop prev =
            let token = lexer.read()
            if fst token = None then () else
            if fst token = Sym then
                let label = snd token
                let list =
                    if usage.ContainsKey label then usage.[label] else
                    let list = new List<string>()
                    usage.[label] <- list
                    list
                if not <| list.Contains s then list.Add s
            if fst prev = Sym && snd token = ":" then
                list.Add (snd prev)
            loop token
        loop (None, "")
        labels.[s] <- list
    for s in srcs do getlabel s
    for s in srcs do
        printfn "## %s" s
        for label in labels.[s] do
            printfn "%s: %s" label (String.Join(", ", usage.[label]))

printfn "# as1"
getlabel as1
printfn ""
printfn "# as2"
getlabel as2
