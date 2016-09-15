<?php

    // configuration
    require("../includes/config.php");

    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // else render form
        render("quote_form.php", ["title" => "Quote"]);
    }
    
    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
     // get the symbol
     if(!empty($_POST["symbol"]))
     {
         $symbol = strtoupper($_POST["symbol"]);
        
        // lookup the symbol
        $symbol_arr = lookup($symbol);
        
        if($symbol_arr)
        {
            // get symbol name
            $symbol_name = $symbol_arr["name"];
            
            //get symbol price
            $symbol_price = number_format($symbol_arr["price"], 4, '.' , ',');
            
            //render the output        
            render("quote.php", ["price" => $symbol_price, "name" => $symbol_name, "symbol"=> $symbol]);
        }
        else
        {
            apologize("No such symbol found");
        }
     }
     else
     {
         apologize("No symbol entered");
     }
        
    }

?>