<?php
$max_photo_size = 50000;
$upload_require = true;

$upload_page = 'index.php';
$upload_dir = '/tmp/image/';

$err_msg = false;
do {
    if (!isset($_FILES['book_image'])) {
        $err_msg = 'The form was not sent in completely.';
        break;
    } else {
        $book_image = $_FILES['book_image'];
    }

    switch ($book_image['error']) {
        case UPLOAD_ERR_INI_SIZE:
            $err_msg = 'The size of the image is too large,' .
                    "it can not be more than $max_photo_size byte.";
            break 2;
        case UPLOAD_ERR_PARTIAL:
            $err_msg = 'An error ocurred while uploading the file, ' .
                    "Please <a href='{$upload_page}'> try again</a>.";
            break 2;
        case UPLOAD_ERR_NO_FILE:
            if ($upload_required) {
                $err_msg = 'You did not select a file to be uploaded, ' .
                        "Please do so <a href='{$upload_page}'> here </a>";
                break 2;
            }
            break 2;
        case UPLOAD_ERR_FORM_SIZE:
            $err_msg = 'The size was too large according to ' .
                    'the MAX_FILE_SIZE hideen field in the upload form.';
        case UPLOAD_ERR_OK:
            if ($book_image['size'] > $max_photo_size) {
                $err_msg = 'The size of the image is too large, ' .
                        "it can not be more then {$max_photo_size} bytes.";
            }
            break 2;
        default:
            $err_msg = "An unkonwn error occurred, " .
                    "please try again <a href='{$upload_page}'>here</a>";
    }

    if (!in_array($book_image['type'], array('image/jpeg', 'image/pjpeg', 'image/png'))) {
        $err_msg = "You need to upload a PNG or JPEG image, " .
                "please do so <a href='{$upload_page}'>here</a>";
        break;
    }
} while (false);

if (!$err_msg) {
    if (!@move_uploaded_file($book_image['tmp_name'], $upload_dir . $book_image['name'])) {
        $err_msg = "Error moving the file to its destination, " .
                "Please try again <a href='{$upload_page}'>here</a>.";
    }
}
?>

<html>
    <head><title>Test File Upload</title></head>
    <body>
        <?php echo $upload_dir . $book_image['name']; ?>
        <?php
        if ($err_msg) {
            echo $err_msg;
        } else {
            ?>
            <img src='<?php echo $book_image['name']; ?>' />
            <?php
        }
        ?>

        <form enctype="multipart/form-data" action="<?php echo $_SERVER['PHP_SELF']; ?>" method="post">
            <input type="hidden" name="MAX_FILE_SIZE" value="1600000" />
            Send this file: <input name="book_image" type="file" /> <br />
            <input type="submit" value="Upload" />
        </form>
    </body>
</html>