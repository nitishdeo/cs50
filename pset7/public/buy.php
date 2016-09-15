<?php

    // configuration
    require("../includes/config.php");

    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // else render form
        render("buy_form.php", ["title" => "BUY"]);
    }
    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST") 
    {
        
        if(!empty($_POST["symbol"]))
        {
            
            $symbol =$_POST["symbol"];
            $shares =$_POST["shares"];
            // check for shares to be a non negative integer
            if(preg_match("/^\d+$/", $shares) && $shares >0)
            {
                $symbol = strtoupper($symbol);
                
                //get latest price of share
                $company_details = lookup($symbol);
                if($company_details)
                {
                    $price = $company_details["price"];
                
                    //get money in the bank
                    $user_details = CS50::query("SELECT cash FROM users WHERE id = ?",$_SESSION["id"]);
                    $cash=$user_details[0]["cash"];
                    //look if the user can afford
                    if($cash >= $price*$shares)
                    {
                        //add stock to the portfolio
                        $result = CS50::query("INSERT INTO portfolios (user_id, symbol, shares) VALUES(?, ?, ?) ON DUPLICATE KEY UPDATE shares = shares + ?",$_SESSION["id"], $symbol, $shares, $shares);
                    
                        if($result)
                        {
                            // stock added to the portfolio, now update cash
                            $cash_update = $cash_update = CS50::query("UPDATE users SET cash = cash - ? WHERE id = ?", $price*$shares, $_SESSION["id"]);
                            
                            //log the transaction
                            $log_result = CS50::query("INSERT INTO history (user_id, symbol, shares, price, type) VALUES (?, ?, ?, ?, 'BUY' )", $_SESSION["id"], $symbol, $shares, $price);
                            
                            //redirect to the portfolio
                            redirect("/");
                        }
                        else
                        {
                            apologize("Couldn't buy. Try again later");
                        }
                    }
                    else
                    {
                        apologize("You can't afford that.");
                    }
                }
                else
                {
                    apologize("Invalid Stock");
                }
            }
            else
            {
                apologize("Enter valid number of shares");
            }    
        }
        else
        {
            apologize("Insert both values : stock and shares");
        }
    }

?>