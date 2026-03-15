<?php
$conn = new mysqli("localhost", "root", "", "iot_db");
if ($_SERVER['REQUEST_METHOD'] === 'POST') {
   $devId = $_POST['deviceId'];
   $temp  = $_POST['temp'];
   $humi  = $_POST['humi'];
   // Znajdź ID płytki
   $res = $conn->query("SELECT idtBoard FROM tboard WHERE deviceId = '$devId'");
   $board = $res->fetch_assoc();
   $idB = $board['idtBoard'];
   if ($idB) {
       // Zapisz temperaturę i wilgotność
       $conn->query("INSERT INTO treadings (value, unitType, fkBoard) VALUES ($temp, 'st. C', $idB)");
       $conn->query("INSERT INTO treadings (value, unitType, fkBoard) VALUES ($humi, '%', $idB)");
       // Pobierz polecenia dla płytki
       $resResp = $conn->query("SELECT respFieldName, value FROM tResponses WHERE fkBoard = $idB");
       $responses = [];
       while($row = $resResp->fetch_assoc()) {
           $responses[$row['respFieldName']] = $row['value'];
       }
       $responses['serverTime'] = date("H:i:s");
       echo json_encode($responses); // Wyślij odpowiedź do NodeMCU
   }
}
?>