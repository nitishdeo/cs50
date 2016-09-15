<div>
    <form action="sell.php" method="post">
    <fieldset>
        <div class="form-group">
            <select class="form-control" name="symbol">
                <option disabled selected value="">Select Symbol</option>
            <?php foreach ($symbols as $row): ?>
                    <option value="<?=$row["symbol"] ?>"><?=$row["symbol"] ?></option>
            <?php endforeach ?>
            </select>
        </div>
        <div class="form-group">
            <button class="btn btn-default" type="submit">
                Sell Stock
            </button>
        </div>
    </fieldset>
</form>
</div>
