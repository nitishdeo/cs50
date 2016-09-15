<?php

    // configuration
    require("../includes/config.php");

    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        $id = $_SESSION["id"];
        $rows = CS50::query("SELECT symbol from portfolios WHERE user_id = ?",$id);
        $symbols =[];
        if($rows)
        {
            foreach($rows as $row)
            {
                $symbols[] = [
                    "symbol" => $row["symbol"]
                    ];
            }
        }
        
        //  render form
        render("sell.php", ["symbols" => $symbols, "title" => "SELL"]);
    }

    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        
        if(!empty($_POST["symbol"]))
        {
            $symbol = $_POST["symbol"];
            
            // get the number of shares owned
            $stock_details = CS50::query("SELECT shares from portfolios WHERE user_id = ? and symbol = ?",$_SESSION["id"], $symbol);
            $shares = $stock_details[0]["shares"];
            
            //update portfolio
            $result = CS50::query("DELETE FROM portfolios WHERE user_id = ? and symbol = ?",$_SESSION["id"], $symbol);
            if($result)
            {
                //get latest price of share
                $company_details = lookup($symbol);
                $price = $company_details["price"];
                
                //update cash, add price*shares to cash
                $cash_update = CS50::query("UPDATE users SET cash = cash + ? WHERE id = ?",$price*$shares, $_SESSION["id"]);
                
                // log the transaction
                $log_result = CS50::query("INSERT INTO history (user_id, symbol, shares, price, type) VALUES (?, ?, ?, ?, 'SELL' )", $_SESSION["id"], $symbol, $shares, $price);
                                
                //redirect to portfolio
                redirect("/");
            }
            else
            {
                apologize("Can't sell the stock. Try again");
            }
        }
        else
        {
            apologize("No stock selected");
        }
    }
 
?>