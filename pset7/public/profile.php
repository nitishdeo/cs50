<?php

    // configuration
    require("../includes/config.php");

    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // else render form
        render("profile_form.php", ["title" => "Change Password"]);
    }

    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        
        // check if all fields are set
        if(empty($_POST["old_password"]) || empty($_POST["new_password"]) || empty($_POST["confirmation"]))
        {
            apologize("Fill in all the required fields");
        }
        else
        {
            // retrieve old password from database
            $user_profile = CS50::query("SELECT hash FROM users WHERE id = ? ", $_SESSION["id"]);
            $old_pwd_crypt = $user_profile[0]["hash"];
            
            if(password_verify($_POST["old_password"], $old_pwd_crypt))
            {
                if($_POST["new_password"] === $_POST["confirmation"])
                {
                    // update the password
                    $result = CS50::query("UPDATE users SET hash = ? WHERE id=?", crypt($_POST["new_password"]), $_SESSION["id"]);
                                    
                    // if query is not executed
                    if($result == false)
                    {
                           apologize("Could not complete password update. Try again");
                    }
                    else
                    {
                        logout();
                        
                        // redirect to login
                        redirect("/");
                    }
    
                }
                else
                {
                    apologize("Password and confirmation password do not match");
                }
            }
            else
            {
                apologize("Wrong password");
            }
        }
    }

?>