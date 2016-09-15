<?php

    // configuration
    require("../includes/config.php");

    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // else render form
        render("register_form.php", ["title" => "Register"]);
    }

    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        
        // check if all fields are set
        if(empty($_POST["username"]) || empty($_POST["password"]) || empty($_POST["confirmation"]))
        {
            apologize("Fill in all the required fields");
        }
        else
        {
            //if all fields are set, check if password === confirmation
            if($_POST["password"] === $_POST["confirmation"])
            {
                //insert user into database
                $result = CS50::query("INSERT IGNORE INTO users (username, hash, cash) VALUES ( ?, ? ,10000.00)",$_POST["username"],crypt($_POST["password"]));
                                
                // if query is executed
                if($result == false)
                {
                       apologize("Username already taken. Retry using another username");
                }
                else
                {
                    //log the user in
                    $rows = CS50::query("SELECT LAST_INSERT_ID() as id");
                    
                    // extract id from the rows array
                    $id = $rows[0]["id"];
                    
                    // remember that user's now logged in by storing user's ID in session
                    $_SESSION["id"] = $id;
    
                    // redirect to portfolio
                    redirect("/");
                }

            }
            else
            {
                apologize("Password and confirmation password do not match");
            }
        }
          
    }

?>