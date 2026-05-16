
<?php
$conn=mysqli_connect("localhost","root","","ishimwe");
$select=mysqli_query($conn,"select *from motion_data");
if(mysqli_num_rows($select)>0){
    ?>
    <table border="1">
        <tr>
            <th>id</th>
            <th>motion_detected</th>
            <th>create_at</th>
        </tr>
        <?php
        while($rows = mysqli_fetch_array($select)) {
            ?>
            <tr>
                <td><?php echo $rows['id']; ?></td>
                <td><?php echo $rows['motion_detection']; ?></td>
                <td><?php echo $rows['created_at']; ?></td>
            </tr>
            <?php
        }
        ?>
    </table>
    <?php
} else {
    echo "No data available in database";
}
?>