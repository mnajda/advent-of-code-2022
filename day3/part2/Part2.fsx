open System
open System.IO

let args : string array = fsi.CommandLineArgs |> Array.tail
let path = args[0]

let backpacks = File.ReadAllText(path).Split("\n") |> Seq.toList |> Seq.chunkBySize 3

let priority (item: char) : int = 
    if item |> Char.IsLower then (item |> int) - 96
    else (item |> int) - 38

let getCommon (backpacks: _ array) : int =
    let common =
        backpacks
        |> Seq.map Seq.toList
        |> Seq.map Set.ofList
        |> Seq.reduce Set.intersect
        |> Set.toList
        |> List.head

    priority(common)

let result = backpacks |> Seq.map getCommon |> Seq.sum
printfn "%A" result
