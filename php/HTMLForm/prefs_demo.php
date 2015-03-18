<html>
    <head><title>Front Door</title></head>
    <?php
    $backgroundName = $_COOKIE['bg'];
    $foregroundName = $_COOKIE['fg'];
    ?>
    <body bgcolor="<?php $backgroundName; ?>" text="<?php $foregroundName; ?>">
        <h1>Welcome to the Store</h1>
        <p>We hava many fine products for you to View.</p>
        <p>Would you like to <a href="colors.php">change your preferences?</a></p>
    </body>
</html>