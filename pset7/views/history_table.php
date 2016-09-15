<br>
<table class="table table-striped">
<thead id="table_head">
    <tr>
        <th><b>Transaction</b></th>
        <th><b>Symbol</b></th>
        <th><b>Shares</b></th>
        <th><b>Price</b></th>
        <th><b>Date/Time</b></th>
    </tr>
</thead>
<tbody id="table_body">
    <?php foreach($transactions as $transaction): ?>
        <tr>
            <td><?=$transaction["type"]?></td>
            <td><?=$transaction["symbol"]?></td>
            <td><?=$transaction["shares"]?></td>
            <td>$<?=$transaction["price"]?></td>
            <td><?=date('M j Y g:i A',strtotime($transaction["time"]))?></td>
        </tr>
    <?php endforeach ?>
</tbody>
</table>
<br>

