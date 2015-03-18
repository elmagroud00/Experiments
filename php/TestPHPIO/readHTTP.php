#!/usr/bin/php
<?php
if($argc < 2) {
    echo "Usage: \n url (max kb/sec)\n\n";
    exit(-1);
}

$url = $argv[1];
if($argc == 3) {
    $max_kb_sec = $argv[2];
} else {
    $max_kb_sec = 1000;
}

$term_sol = "\x1b[1G";
$serverity_map = array(
    0 => 'info',
    1 => 'warning',
    2 => 'error'
);

function notifier($code, $serverity, $msg, $xcode, $sofar, $max) {
    global $term_sol, $serverity_map, $max_kb_sec, $size;

    if($code != STREAM_NOTIFY_PROGRESS) {
        echo $serverity_map[$serverity] . ": ";
    }

    switch($code) {
    case STREAM_NOTIFY_CONNECT:
        printf("Connected\n");
        $GOLBALS['begin_time'] = time() - 0.001;
        break;
    case STREAM_NOTIFY_AUTH_REQUIRED:
        printf("Authentication required: %s\n", trim($msg));
        break;
    case STREAM_NOTIFY_AUTH_RESULT:
        printf("Logged in: %s\n", trim($msg));
        break;
    case STRAM_NOTIFY_MIME_TYPE_IS:
        printf("Mime type: %s\n", $msg);
        break;
    case STREAM_NOTIFY_FILE_SIZE_IS:
        printf("Downloading %d kb\n", $max / 1024);
        $size = $max;
        break;
    case STREAM_NOTIFY_REDIRECTED:
        printf("Redirecting to %s ...\n", $msg);
        break;
    case STREAM_NOTIFY_PROGRESS:
        if($size) {
            $stars = str_repeat('*', $c = $sofar * 50 / $size);
        }  else {
            $starts = '';
        }
        $stripe = str_repeat('-', 50 - strlen($stars));

        $kb_sec = ($sofar / (time() - $GOLBALS['begin_time'])) / 1024;

        while($kb_sec > $max_kb_sec) {
            usleep(1);
            $kb_sec = ($sofar / (time() - $GOLBALS['begin_time'])) / 1024;
        }
        printf("{$term_sol}[%s] %d kb %.1f kb/sec",
            $stars.$stripe, $sofar / 1024, $kb_sec);
        break;
    case STREAM_NOTIFY_FAILURE:
        printf("Failed: %s\n", $msg);
        break;
    }
}

$url_data = parse_url($argv[1]);
$file = basename($url_data['path']);
if(empty($file)) {
    $file = "index.html";
}
printf("Saving to $file.gz\n");
$fil = "compress.zlib://$file.gz";
$context = stream_context_create();
stream_context_set_params($context, array("notification" => "notifier"));
$fp = fopen($url, "rb", false, $context);
if(is_resource($fp)) {
    $fs = fopen($fil, "wb9", false, $context);
    if(is_resource($fs)) {
        while(!feof($fp)) {
            $data = fgets($fp, 1024);
            fwrite($fs, $data);
        }
        fclose($fs);
    }
    fclose($fp);

    printf("{$term_sol}[%s] Download time: %ds\n",
    str_repeat('*', 50), time() - $GOLBALS['begin_time']);
}
?>
