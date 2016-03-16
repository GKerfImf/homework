// Learn more about F# at http://fsharp.org
// See the 'F# Tutorial' project for more help.
#if INTERACTIVE
//#load "C:\\Users\\admin\\Google Диск\\Code\\Project\\F#\\SCP\\p3\\p3\\Script3.fsx";;
#r "C:\\Program Files (x86)\\MySQL\\Connector.NET 6.9\\Assemblies\\v2.0\\MySql.Data.dll"
#r "C:\\Program Files (x86)\\Reference Assemblies\\Microsoft\\Framework\\.NETFramework\\v4.5.2\\System.Configuration.dll"
#r "C:\\Program Files (x86)\\Reference Assemblies\\Microsoft\\Framework\\.NETFramework\\v4.5.2\\System.Transactions.dll"
#endif

module MySQL =
    open MySql.Data.MySqlClient

    let createMySqlConnection = 
        (fun (server:string) (id:string) (password:string) -> 
            new MySqlConnection("server=" + server + ";user id=" + id + "; password=" + password + "; database=mysql; pooling=false"));
                                                               
    let openMySqlConnection (mySqlConnection : MySqlConnection option) = 
        if mySqlConnection.IsSome then mySqlConnection.Value.Open() 

    let queryDatabase (mySqlConnection : MySqlConnection option) (queryString : string) =
        try
           [let cmd = new MySqlCommand(queryString, mySqlConnection.Value)
            let reader = cmd.ExecuteReader()
            while reader.Read() do
                yield reader.GetString 0
            reader.Close() ] 
            |> Some

        with
            | :? System.InvalidOperationException -> printfn "Incorrect query"; None

module DatabaseUI =
    open System
    open System.Drawing
    open System.Collections
    open System.ComponentModel
    open System.Windows.Forms
    open System.Data
    open System.Drawing

    type DatabaseForm() as this = 
        inherit Form()

        let mutable setDatabaseList = fun (text : (string list) option) -> ()
        let mutable setTablesList = fun (text : (string list) option) -> ()

        let mutable mySqlConnection : MySql.Data.MySqlClient.MySqlConnection option = None

        let mutable server:TextBox = null
        let mutable userid:TextBox = null
        let mutable password:TextBox = null

        let mutable databaseList:ComboBox = null
        let mutable tables:ComboBox = null
        let mutable dataGrid:DataGrid = null
        let mutable data:DataTable = null
        let mutable da:MySql.Data.MySqlClient.MySqlDataAdapter=null

        let handleButtons input =
            match input with
            | "connectBtn" ->
                try
                    mySqlConnection <- Some <| MySQL.createMySqlConnection server.Text userid.Text password.Text
                    MySQL.openMySqlConnection mySqlConnection
                    setDatabaseList <| MySQL.queryDatabase mySqlConnection "SHOW DATABASES"
                    MessageBox.Show( "Ok") |> ignore
                with
                    | :? MySql.Data.MySqlClient.MySqlException -> MessageBox.Show( "Incorrect server/login/pass") |> ignore
                    | _ -> MessageBox.Show( "Unknown Exception") |> ignore
            | "updateBtn" ->
                try 
                    let changes = data.GetChanges()
                    da.Update changes |> ignore
                    data.AcceptChanges()
                with
                    | :? System.NullReferenceException -> MessageBox.Show( "Select the table") |> ignore
                    | :? System.ArgumentNullException -> MessageBox.Show( "You have not changed anything") |> ignore
                    | _ -> MessageBox.Show( "Unknown Exception") |> ignore
            | "showViewBtn" ->
                try 
                    data <- new DataTable()
                    da <- new MySql.Data.MySqlClient.MySqlDataAdapter(
                        "SELECT Name, NameAut\n" +
                        "FROM\n" +
                        "	books INNER JOIN BooksToAuthors\n" +
                        "	    ON Id = IdBook\n" +
                        "	    INNER JOIN Authors\n" +
                        "	        ON IdAut = IdAuthor\n" +
                        "WHERE IdPublisher = 1;" , mySqlConnection.Value)
                    let cb = new MySql.Data.MySqlClient.MySqlCommandBuilder( da )
                    da.Fill( data ) |> ignore
                    dataGrid.DataSource <- data
                with
                    | :? MySql.Data.MySqlClient.MySqlException -> MessageBox.Show( "Select the appropriate DB") |> ignore
                    | :? System.NullReferenceException -> MessageBox.Show( "You are not logged in") |> ignore
                    | _ -> MessageBox.Show( "Unknown Exception") |> ignore
            | _ -> failwith ":("

        let handleComboBoxs input =
            match input with
            | "databaseList" ->
                try
                    mySqlConnection.Value.ChangeDatabase <| databaseList.SelectedItem.ToString() 
                    setTablesList <| MySQL.queryDatabase mySqlConnection "SHOW TABLES"
                with
                    | _ -> MessageBox.Show( "Unknown Exception") |> ignore
            | "tables" ->
                try
                    data <- new DataTable()
                    da <- new MySql.Data.MySqlClient.MySqlDataAdapter("SELECT * FROM " + tables.SelectedItem.ToString(), mySqlConnection.Value)
                    let cb = new MySql.Data.MySqlClient.MySqlCommandBuilder( da )
                    da.Fill( data ) |> ignore
                    dataGrid.DataSource <- data
                with
                    | _ -> MessageBox.Show( "Unknown Exception") |> ignore
            | _ -> failwith ":("  

        do
            this.SetupForm()
            this.CreateButtons()
            this.CreateComboBox()

        member this.SetupForm() =
            this.SuspendLayout()
            this.AutoScaleBaseSize <- new Size(5, 13)
            this.ClientSize <- new Size(560, 453)
            this.Name <- "DB_GUI"
            this.Text <- "DB_GUI"
           
            let label1 = new Label(Location=Point(8, 11), Name="label1", TabIndex=0, Text="Server:", Size=Size(48, 16))
            label1 |> this.Controls.Add

            let label2 = new Label(Location=Point(8, 37), Name="label2", TabIndex=2, Text="User Id:", Size=Size(48, 16))
            label2 |> this.Controls.Add

            let label3 = new Label(Location=Point(192, 37), Name="label3", TabIndex=4, Text="Password:", Size=Size(56, 16))
            label3 |> this.Controls.Add

            let label4 = new Label(Location=Point(8, 109), Name="label4", TabIndex=0, Text="Tables", Size=Size(64, 16))
            label4 |> this.Controls.Add

            let label5 = new Label(Location=Point(8, 85), Name="label5", TabIndex=10, Text="Databases", Size=Size(64, 16))
            label5 |> this.Controls.Add


            server <- new TextBox(Location=Point(56,8),Name="server",TabIndex=1,Text="",Size=Size(320, 20))
            server |> this.Controls.Add

            userid <- new TextBox(Location=Point(56, 32),Name="userid", TabIndex=3, Text="",Size=Size(120, 20))
            userid |> this.Controls.Add
            
            password <- new TextBox(Location=Point(260, 32),Name="password",TabIndex=5,Text="",Size=Size(116, 20), PasswordChar='*')
            password |> this.Controls.Add

            dataGrid <- new DataGrid(Location=Point(8, 136),Name="dataGrid",TabIndex=8,Size=Size(544, 312),HeaderForeColor=SystemColors.ControlText,DataMember="")
            dataGrid |> this.Controls.Add 
            
            this.ResumeLayout(false);

        member this.CreateButtons() = 
            let addButtonControl input (button:Button) =
                button.Click.AddHandler(EventHandler(fun _ _ -> handleButtons input))
                this.Controls.Add(button)

            let updateBtn = new Button(Text="Update", Name="updateBtn", TabIndex=9, Location=Point(477,104))
            updateBtn |> addButtonControl updateBtn.Name

            let connectBtn = new Button(Text="Connect", Name="connectBtn", TabIndex=6, Location=Point(400, 8))
            connectBtn |> addButtonControl connectBtn.Name

            let showViewBtn = new Button(Text="Show View", Name="showViewBtn", TabIndex=6, Location=Point(400, 104))
            showViewBtn |> addButtonControl showViewBtn.Name

        member this.CreateComboBox() = 
            let addComboBoxControl input (box:ComboBox) =
                box.SelectedValueChanged.AddHandler(EventHandler(fun _ _ -> handleComboBoxs input))
                this.Controls.Add(box)

            databaseList <- new ComboBox(Location=Point(80,80), Name="databaseList",Size=Size(296,21),TabIndex=11,DropDownStyle=ComboBoxStyle.DropDownList)
            setDatabaseList <- 
                (fun text ->
                    databaseList.Items.Clear()
                    match text with
                    | Some lst ->
                        List.iter (fun x -> databaseList.Items.Add x |> ignore) lst
                    | None -> ())
            databaseList |> addComboBoxControl databaseList.Name

            tables <- new ComboBox(Location=Point(80, 104),Name="tables",Size=Size(296, 21),TabIndex=7,DropDownStyle=ComboBoxStyle.DropDownList)
            setTablesList <- 
                (fun text ->
                    tables.Items.Clear()
                    match text with
                    | Some lst ->
                        List.iter (fun x -> tables.Items.Add x |> ignore) lst
                    | None -> ())
            tables |> addComboBoxControl tables.Name  
            
let form = new DatabaseUI.DatabaseForm()
form.Show() 