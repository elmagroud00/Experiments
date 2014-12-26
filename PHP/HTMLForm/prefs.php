<html>
    <head><title>Preferences Set</title></head>
    <body>
        <?php
        $color = array(
            'black' => "#000000",
            'white' => "#ffffff",
            'red' => "#ff0000",
            'blue' => "#0000ff"
        );
        $backgroundName = $_POST['background'];
        $foregroundName = $_POST['foreground'];

        setcookie('bg', $color[$backgroundName]);
        setcookie('fg', $color[$foregroundName]);
        ?>
        
        <p>Thank you. Your preferences hava been changed to: <br />
        Background: <?php echo $backgroundName; ?> <br />
        Foreground: <?php echo $foregroundName; ?> <br />
        </p>
        <p>
            Click <a href="prefs_demo.php">here</a> to see the preferences in action.
        </p>
    </body>
</html>