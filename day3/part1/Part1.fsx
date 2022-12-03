open System
open System.IO

let args : string array = fsi.CommandLineArgs |> Array.tail
let path = args[0]

let backpacks = File.ReadAllText(path).Split("\n") |> Seq.toList

let priority (item: char) : int = 
    if item |> Char.IsLower then (item |> int) - 96
    else (item |> int) - 38

let getCommon (backpack: string) : int =
    let middle = backpack.Length / 2
    let first = Seq.toList backpack.[0..middle-1] |> Set.ofList
    let second = Seq.toList backpack.[middle..backpack.Length] |> Set.ofList

    let common = Set.intersect first second |> Set.toList |> List.head
    priority(common)

let result = backpacks |> Seq.map getCommon |> Seq.sum
printfn "%A" result
