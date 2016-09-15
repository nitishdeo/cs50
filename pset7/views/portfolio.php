<br>
<table class="table table-striped">
<thead id ="table_head">
    <tr>
        <th>Symbol</th>
        <th>Name</th>
        <th>Shares</th>
        <th>Current Price</th>
        <th>TOTAL</th>
    </tr>
</thead>
<tbody id="table_body">
    <?php foreach ($positions as $position): 
        $total =$position["shares"]*$position["price"];?>
        <tr>
            <td><?php echo $position["symbol"]; ?></td>
            <td><?php echo $position["name"]; ?></td>
            <td><?php echo $position["shares"]; ?></td>
            <td>$<?php echo$position["price"]; ?></td>
            <td>$<?php echo $total; ?></td>
        </tr>
    <?php endforeach ?>
    <tr>
        <td><b>CASH IN HAND</b></td>
        <td></td>
        <td></td>
        <td></td>
        <td><b>$<?=$cash?></b></td>
    </tr>
</tbody>
</table>
<br>

