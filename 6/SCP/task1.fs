type MoneyChanger (amount:int, value:list<int>) = class
    let mutable result:list<list<int>> = []

    let dot_product (a:list<int>) (b:list<int>) =
        if List.length a <> List.length b then failwith "vectors must have the same lengths"
        List.fold2 (fun acc i j -> acc + (i * j)) 0 a b

    let all_zero a = a |> List.exists (fun x -> x <> 0) |> not 

    let incFirstElem a = match a with [] -> [] | x::xs -> (x+1)::xs

    let rec next_val (a:list<int>) = 
        match a with
        | _ when all_zero a -> a
        | 0::xs -> 0:: (next_val xs)
        | x::xs -> 0::(incFirstElem xs)
        | [] -> failwith "??"

    let rec next exch =
        if (dot_product exch value = amount |> not) && (exch |> all_zero |> not) 
        then if dot_product exch value > amount then next (next_val exch) else next (incFirstElem exch)
        else exch
    
    let rec beautiful exch value = 
        match exch, value with
        | x::xs, y::ys -> (List.replicate x y ) :: beautiful xs ys
        | _, _ -> []

    member x.Execute = 
        let mutable exchange = List.replicate (Seq.length value) 0
        exchange <- exchange |> incFirstElem |> next
        result <- result |> List.append [exchange]
        while all_zero exchange |> not do
            exchange <- exchange |> incFirstElem |> next
            result <- result |> List.append [exchange]
        result |> List.tail |> List.map (fun x -> beautiful x value) |> List.map List.concat
end


[<EntryPoint>]
let main argv = 
    let input = 
        System.Console.ReadLine() 
        |> (fun line -> line.Split([|' '|])) 
        |> Seq.map System.Int32.TryParse |>  List.ofSeq 

    if Seq.length input < 2 then failwith "Incorrect input"
    if input |> Seq.exists (fun (x,y) -> not x) |> not
        then printfn "%A" ((new MoneyChanger(input |> Seq.head |> snd, input |> List.tail |> List.map snd)).Execute)
        else printfn "Incorrect input" 
    0