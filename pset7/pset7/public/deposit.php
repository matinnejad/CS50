<?php

    // configuration
    require("../includes/config.php"); 

    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // validate submission
        if (empty($_POST["deposit"]))
        {        $transaction = 'BUY';
            apologize("You must provide an amount.");
        }
        if ($_POST["deposit"]<0)
        {        $transaction = 'BUY';
            apologize("You must provide a positive amount.");
        }
        else
        {
        $deposit = $_POST["deposit"]; 
        $transaction = 'DEPOSIT';               
        // update cash
        CS50::query("UPDATE users SET cash = cash + ? WHERE id = ?", $deposit, $_SESSION["id"]);
        // redirect to portfolio 
        CS50::query("INSERT INTO history (id, transaction, price) VALUES (?, ?, ?)", $_SESSION["id"], $transaction, $deposit);    
        redirect("/");
        }
    }
    else
    {
        render("deposit_form.php", ["title" => "Deposit"]);
    }

?>