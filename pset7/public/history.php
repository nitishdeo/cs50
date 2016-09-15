<?php

    // configuration
    require("../includes/config.php"); 
    
    // id of the current logged in user
    $id = $_SESSION["id"];
    
    // get user's transaction history
    $history = CS50::query("SELECT symbol,shares,price,type,time from history WHERE user_id = ?", $id);
    
    
    // var to be passed
    $transactions = [];
    foreach($history as $row)
    {
        // price for the stock
        $company_details = lookup($row["symbol"]);
        // insert new tuple in positions
        $transactions[] = [
            "symbol" => $row["symbol"],
            "shares" => $row["shares"],
            "price" => $company_details["price"],
            "type" => $row["type"],
            "time" => $row["time"]
                ];
    }
    
    // render history
    render("history_table.php", ["transactions" =>$transactions, "title" => "History"]);
?>
