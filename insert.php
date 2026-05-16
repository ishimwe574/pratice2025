
<?php
$host = "localhost";
$user = "root";
$pass = "";
$dbname = 'ishimwe';

$conn = mysqli_connect($host, $user, $pass, $dbname);

if($conn) {
    echo "connection successful";
} else {
    echo "connection failed";
}

$data = json_decode(file_get_contents("php://input"), true);

if($data) {
    $distance = $data["distanc"];
     $insert = mysqli_query($conn, "INSERT INTO motion_data(motion_detection) VALUES('$distance')");
    
    if($insert) {
        echo "data inserted successfully";
    } else {
        echo "failed to fetch data";
    }
} else {
    echo "no data retrieve from esp";
}
?>