<?php
header('WWW-Authenticate: Basic realm="Top Secret Files"');
header("HTTP/1.0 401 Unauthorized");

$name = $_POST['name'];
$mediaType = $_POST['media_type'];
$filename = $_POST['filename'];
$caption = $_POST['status'];
$tried = ($_POST['tried'] == 'yes');

if ($tried) {
    $validate = (!empty($name) && !empty($mediaType) && !empty($filename));
    if (!validate) {?>
        <p>The name, media type, 
            and filename are required fields. Please fill them out to continue.</p>
    <?php
    }
}

if ($tried && $validate) {
    echo "<p>The item has been created.</p>";
}

//was this type if media selected? print "selected" if so
function mediaSelected($type) {
    global $mediaType;
    if ($mediaType == $type) {
        echo "selected";
    }
}
?>

<form action="<?php echo $_SERVER['PHP_SELF']; ?>" medthod="POST">
    Name: <input type="text" name="name" value="<?php $name; ?>" /> <br />
    Status: <input type="checkbox" name="status" value="active"
<?php if ($status = "active") {
    echo "checked";
} ?> />Active <br />
    
    Media: <select name="media_type">
        <option value="">Chooe one</option>
        <option value="picture" <?php             mediaSelected("picture");?> >Picture</option>
        <option value="audio" <?php             mediaSelected("audio");?> >Audio</option>
        <option value="movie" <?php             mediaSelected("movie");?> >Movie</option>
    </select>  <br />

    File: <input type="text" name="filename" value="<?php $filename;?>" /><br />
    Caption: <textarea name="caption"><?php $caption ?></textarea> <br />
    <input type="hidden" name="tried" value="yes" />
    <input type="submit" value="<?php echo $tried ? "Continue" : "Create"; ?>" />
</form>