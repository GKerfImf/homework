module Calc =
    open System 
    open System.Text.RegularExpressions

    let properFraction (x:double) : (int * double) =
        let t = (string x).Split('.') |> Array.toList
        let t2 =
            match t.Length with 
            | 1 -> List.append [t.Head] ["0,0"]
            | 2 -> List.append [t.Head] ["0," + t.Tail.Head]
            | _ -> failwith "in properFraction t.length <>1 && <>2"
        (Int32.Parse t2.Head, Double.Parse t2.Tail.Head)

    let toReversePolishNotation string =
        let isNum c =
            match c with
            | "(" | ")" | "+" | "-" | "*" |"/" | "," | "u" -> false
            | _ -> true

        let isRightBracket c = c = ")"

        let prior c =
            match c with
            | "(" | ")" -> 2
            | "+" | "-" -> 3
            | "*" | "/" | "u" -> 4
            | _ -> failwith "smth not +-*/u in prior"

        let tokenize (expr: string) =
            let unarMinusOnTop expr = 
                match expr with
                | "-"::xs -> "u"::xs
                | x -> x
            let rec unarMinus (lst: string list) = 
                match lst with 
                | x::"-"::xs when ((x |> isNum),(x |> isRightBracket)) ||> (||) |> not -> x::"u"::unarMinus xs
                | x::xs -> x:: unarMinus xs
                | _ -> []
            expr 
                |> (new Regex("\s+|\s*([-+*/()])\s*")).Split
                |> Array.toList
                |> List.filter(fun s -> s.Length > 0)
                |> unarMinusOnTop
                |> unarMinus
        
        let shuntingYardAlgorithm (expr:string list) = 
            let mutable exp = expr
            let mutable result : string list = []
            let stack = new System.Collections.Generic.Stack<string>()

            while exp.Length > 0 do
                let h = List.head exp
                match h with
                | _ when isNum h -> result <- List.append result [h]
                | "(" -> stack.Push h
                | ")" ->
                    while (stack.Count>0) && (stack.Peek() <> "(") do
                        result <- List.append result [stack.Pop()]
                    stack.Pop() |> ignore
                | _                 -> 
                    while (stack.Count > 0) && prior (stack.Peek()) >= prior h do
                        result <- List.append result [stack.Pop()]
                    stack.Push(h)
                exp <- List.tail exp

            while (stack.Count>0) do 
                result <- List.append result [stack.Pop()]
            printf "Reverse Polish Notation: %A\n"  result      
            result

        string |> tokenize |> shuntingYardAlgorithm

    let to5System (x:double) : double =
        let rec integerPartTo5 (x:int) : string = 
            match x with 
            | 0 -> "0"
            | _ when x < 0 -> "-" + (integerPartTo5 -x)
            | _ -> (integerPartTo5 (x / 5)) + (string (x%5))

        let doublePartTo5 (x:float) : string =  
            let mutable count = 0
            let rec doublePartTo5helper (x:float) : int list = 
                let p  = properFraction (5.0 * x)
                match x with 
                | 0.0 ->  []
                | _ when count < 10 -> 
                    count <- 1 + count
                    (fst p)::(doublePartTo5helper (snd p))
                | _ -> []
            x |> doublePartTo5helper |> List.map string |> String.concat ""

        let (x1 ,x2) = x |> properFraction
        let (a,b) = x1 |> integerPartTo5, x2 |> doublePartTo5
        Double.Parse <| a + (if b = "" then "" else ","+b)

    let to10System (x:double) : double =
        let (x1,x2) = x |> properFraction

        let toDecInt x =
            let rec toDecHelp (x : int list) (n : int) =
                match x with
                | x::xs -> (x * (pown 5 n) + (toDecHelp xs (n+1)))
                | _ -> 0
            toDecHelp x 0

        let toDecDou x = 
            let rec toDecHelp (x : double list) (n : int) =
                match x with
                | x::xs -> (x * (pown 5.0 n) + (toDecHelp xs (n-1)))
                | _ -> 0.0
            toDecHelp x -1

        let a = 
            (x1 |> Math.Abs |> string).ToCharArray() 
            |> Array.rev |> Array.toList |> List.map string |> List.map Int32.Parse |> toDecInt |> string 
         
        let b2 = 
            if x2 <> 0.0 
                then 
                    let b = 
                        (x2 |> string).ToCharArray() 
                        |> Array.toList |> List.map string 
                        |> List.tail |> List.tail |> List.map Double.Parse |> toDecDou |> string 
                    b.ToCharArray() |> Array.toList |> List.map string |> List.tail |> List.tail |> String.concat ""  
                else
                    ""
        Double.Parse <| (if x < 0.0 then "-" else "") + a + (if b2 = "" then "" else ","+b2)

    let stackCalculator (expr : string list) =
        let is_operator c =
            match c with
                | "+" | "-" | "*" | "/"  | "u" -> true
                | _ -> false

        let calculate operator left  right =
            let add left right = ((left |> to10System) + (right |> to10System)) |> to5System
            let sub left right = ((left |> to10System) - (right |> to10System)) |> to5System 
            let mul left right = ((left |> to10System) * (right |> to10System)) |> to5System
            let div left right = ((left |> to10System) / (right |> to10System)) |> to5System

            match operator with
                | "+" -> add left right
                | "-" -> sub left right
                | "*" -> mul left right
                | "/" -> div left right
                | _ -> failwith "Unknown operator"
 
        let proc (item:string) (stack: System.Collections.Generic.Stack<double>) =
            match item with
            | "u" -> 
                let n = stack.Pop()
                let result = -n
                stack.Push result                
            | "+" | "-" | "*" | "/"  ->
                let r = stack.Pop()
                let l = stack.Pop()
                let result = calculate item l r
                stack.Push result
            |_ ->
                stack.Push(System.Convert.ToDouble(item))
 
        let evaluate (expression:string list ) =
            let stack = new System.Collections.Generic.Stack<double>()
            List.iter (fun i -> printf "%A <- %A\n" stack i; proc i stack) expression
            printf "%A\n" stack;
            stack.Pop()
        expr |> evaluate

    let computeInput input =
        let result =
            try
                input |> toReversePolishNotation |> stackCalculator |> string
            with
                | _ -> printfn "Oops!"; "Invalid input"
        result

module CalculatorUI =
    open System
    open System.Windows.Forms
    open System.Drawing

    type CalculatorForm() as this = 
        inherit Form()

        let mutable displayText = ""

        let margin = 20
        let buttonDimension = 50
        let buttonPadding = 10
        let doubleDimension = buttonDimension + buttonPadding + buttonDimension
        let gridSize = buttonDimension + buttonPadding

        let buttonSize = Size(buttonDimension,buttonDimension)
        let doubleWidthSize = Size(doubleDimension,buttonDimension)
        let doubleHeightSize = Size(buttonDimension,doubleDimension)
        let decimalSeparator = System.Globalization.CultureInfo.CurrentCulture.NumberFormat.CurrencyDecimalSeparator

        let DigitButtonColor = Color.White
        let OpButtonColor = Color.PeachPuff
        let DangerButtonColor = Color.Coral

        let largeFont = new Font(FontFamily.GenericSansSerif,14.f)
        let smallFont = new Font(FontFamily.GenericSansSerif,9.f)

        let mutable setDisplayedText = fun text -> ()


        let getPos(row,col) = 
            let x = margin + (col*gridSize) 
            let y = margin + (row* gridSize) 
            Point(x,y)

        let handleInput input =
            match input with
            | "=" -> displayText <- Calc.computeInput displayText
            | "C" -> displayText <- ""
            | "D" -> displayText <- displayText.Remove(displayText.Length - 1)
            | _ -> displayText <- displayText + input
            setDisplayedText displayText 
            

        do
            this.SetupForm()

        member this.SetupForm() = 
            this.Text <- "Calculator"
            this.Font <- largeFont 
            let clientSizeX = (2*margin) + (5*buttonDimension) + (4*buttonPadding)
            let clientSizeY = (2*margin) + (5*buttonDimension) + (4*buttonPadding)
            this.ClientSize <- Size(clientSizeX,clientSizeY)
            this.CenterToScreen()

            let keyPressHandler = new KeyPressEventHandler(fun obj e -> this.KeyPressHandler(e))
            this.KeyPress.AddHandler keyPressHandler 
            this.KeyPreview <- true

            this.CreateButtons()
            this.CreateDisplayLabel()

        member this.CreateDisplayLabel() = 
            let pendingOpHeight = largeFont.Height
            let displayWidth = 5*buttonDimension + 4*buttonPadding

            let pendingOpSize = Size(displayWidth,pendingOpHeight)
            let pendingOpLocation = getPos(0,0) 
            let pendingOp = new Label(Text="",Size=pendingOpSize,Location=pendingOpLocation)
            pendingOp.TextAlign <- ContentAlignment.BottomRight
            pendingOp.BackColor <- Color.White
            pendingOp.Font <- smallFont
            this.Controls.Add(pendingOp)

            let displaySize = Size(displayWidth,buttonDimension - pendingOpHeight)
            let displayLocation = getPos(0,0) 
            displayLocation.Offset(0,pendingOpHeight)
            let display = new Label(Text="",Size=displaySize,Location=displayLocation)
            display.TextAlign <- ContentAlignment.MiddleRight
            display.BackColor <- Color.White
            this.Controls.Add(display)

            setDisplayedText <- (fun text -> display.Text <- text)

        member this.CreateButtons() = 
            let addButtonControl input (button:Button) =
                button.Click.AddHandler(EventHandler(fun _ _ -> handleInput input))
                this.Controls.Add(button)

            let zeroButton = new Button(Text="0",Size=doubleWidthSize,Location=getPos(3,0),BackColor=DigitButtonColor)
            zeroButton |> addButtonControl "0"

            let oneButton = new Button(Text="1",Size=buttonSize,Location=getPos(3,2),BackColor=DigitButtonColor)
            oneButton |> addButtonControl "1"

            let twoButton = new Button(Text="2",Size=buttonSize,Location=getPos(2,0),BackColor=DigitButtonColor)
            twoButton |> addButtonControl "2"

            let threeButton = new Button(Text="3",Size=buttonSize,Location=getPos(2,1),BackColor=DigitButtonColor)
            threeButton |> addButtonControl "3"

            let fourButton = new Button(Text="4",Size=buttonSize,Location=getPos(2,2),BackColor=DigitButtonColor)
            fourButton |> addButtonControl "4"

            let addButton = new Button(Text="+",Size=buttonSize,Location=getPos(1,3),BackColor=OpButtonColor)
            addButton |> addButtonControl "+"

            let minusButton = new Button(Text="-",Size=buttonSize,Location=getPos(2,3),BackColor=OpButtonColor)
            minusButton |> addButtonControl "-"

            let multButton = new Button(Text="*",Size=buttonSize,Location=getPos(3,3),BackColor=OpButtonColor)
            multButton |> addButtonControl "*"

            let divideButton = new Button(Text="/",Size=buttonSize,Location=getPos(4,3),BackColor=OpButtonColor)
            divideButton |> addButtonControl "/"

            let pointButton = new Button(Text=decimalSeparator,Size=buttonSize,Location=getPos(4,2),BackColor=DigitButtonColor)
            pointButton |> addButtonControl ","

            let leftBracketButton = new Button(Text="(",Size=buttonSize,Location=getPos(4,0),BackColor=DigitButtonColor)
            leftBracketButton |> addButtonControl "("

            let rightBracketButton = new Button(Text=")",Size=buttonSize,Location=getPos(4,1),BackColor=DigitButtonColor)
            rightBracketButton |> addButtonControl ")"

            let equalButton = new Button(Text="=",Size=doubleHeightSize,Location=getPos(3,4),BackColor=OpButtonColor)
            equalButton |> addButtonControl "="

            let clearButton = new Button(Text="C",Size=buttonSize,Location=getPos(1,4),BackColor=DangerButtonColor)
            clearButton |> addButtonControl "C"

            let delButton = new Button(Text="Del",Size=buttonSize,Location=getPos(2,4),BackColor=DangerButtonColor)
            delButton |> addButtonControl "D"

        member this.KeyPressHandler(e:KeyPressEventArgs) =
            match e.KeyChar with
            | '0' -> handleInput "0"
            | '1' -> handleInput "1"
            | '2' -> handleInput "2"
            | '3' -> handleInput "3"
            | '4' -> handleInput "4"
            | '.' | ',' -> handleInput ","
            | '+' -> handleInput "+"
            | '-' -> handleInput "-"
            | '/' -> handleInput "/"
            | '*' -> handleInput "*"
            | '(' -> handleInput "("
            | ')' -> handleInput ")"
            | '=' | '\n' | '\r' -> handleInput "="
            | 'C' | 'c' -> handleInput "C"
            | '\b' -> handleInput "D"
            | _ -> ()
            
let form = new CalculatorUI.CalculatorForm()
form.Show() 
