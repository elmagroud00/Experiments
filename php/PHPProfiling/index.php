<!DOCTYPE html>
<!--
To change this license header, choose License Headers in Project Properties.
To change this template file, choose Tools | Templates
and open the template in the editor.
-->
<html>
    <head>
        <meta charset="UTF-8">
        <title>PHP Profiling</title>
    </head>
    <body>
        <?php
        ob_start();
        $start = microtime();
        phpinfo();
        $end = microtime();
        ob_end_clean();

        echo "phpinfo() took " . ($end - $start) . " seconds to run.\n";
        ?>
        <h1>Use Benchmark</h1>
        <?php
        require_once 'PEAR.php';
        require_once 'Benchmark/Timer.php';
        $time = new Benchmark_Timer;
        $timer->start();
        sleep(1);
        $timer->setMarker('Marker1');
        sleep(2);
        $timer->stop();
        
        $profiling = $timer->getProfiling();
        
        foreach($profiling as $time) {
            echo 'Total: ' . $time['total'] . "<br>\n";
        }
        ?>
    </body>
</html>
