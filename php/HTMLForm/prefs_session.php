<html>
    <head><title>Preferences Set</title></head>
    <body>
        <?php
        session_start();
        $colors = array(
            'black' => "#000000",
            'white' => "#ffffff",
            'red' => "#ff0000",
            'blue' => "#0000ff"
        );
        
        $backgroundName = $_POST['background'];
        $foregroundName = $_POST['foreground'];
        
        $_SESSION['background'] = $colors[$backgroundName];
        $_SESSION['foreground'] = $colors[$foregroundName];
        ?>
        
        <p>
            Thank you. You preferences have been changed to: <br />
            Background: <?= $backgroundName; ?> <br />
            Foreground: <?= $foregroundName; ?>
        </p>
        <p>
            Click <a href="prefs_session_demo.php">Here</a> to see the preferences in 
            action.
        </p>
    </body>
</html>