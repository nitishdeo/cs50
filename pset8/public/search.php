<?php
    //inclde config file
    require(__DIR__ . "/../includes/config.php");
    
    // associative array of places
    $places = [];
    
    // get the query
    $geo = $_GET["geo"];
    
    // Search for the geo
    $result = CS50::query("SELECT * FROM places WHERE match(place_name, postal_code, country_code, admin_code1) against( ? )", $geo);
    
    // storing the result in places variable
    $places = $result;
    
    // debugging to see if it works!
    header("Content-type: application/json");
    print(json_encode($places, JSON_PRETTY_PRINT));
?>