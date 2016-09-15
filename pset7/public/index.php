<?php
    // configuration
    require("../includes/config.php"); 
    
    // id of the current logged in user
    $id = $_SESSION["id"];
    
    // get user's portfolio
    $rows = CS50::query("SELECT symbol, shares FROM portfolios WHERE user_id = ?", $id);
    
    // var to be passes to portfolio view
    $positions = [];
    
    foreach($rows as $row)
    {
        // lookup the name of company
        $company_details = lookup($row["symbol"]);
        if($company_details)
        {
            // insert new tuple in positions
            $positions[] = [
                "symbol" => $row["symbol"],
                "name" => $company_details["name"],
                "shares" => $row["shares"],
                "price" => $company_details["price"]
                ];
        }
    }
    // get user's cash balance
    $user_details = CS50::query("SELECT cash from users where id = ?",$_SESSION["id"]);
    $cash=0.00;
    if($user_details)
    {
        $cash = number_format( $user_details[0]["cash"], 2, '.', ',');
    }
    /*dump($positions);  // debugging */ 
    
    // render portfolio
    render("portfolio.php", [ "cash" => $cash, "positions" =>$positions,"title" => "Portfolio"]);
?>
