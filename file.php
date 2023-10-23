<html>

<body>
    <?php
    $dbname = 'weerstation';
    $dbuser = 'root';
    $dbpass = 'ProjectWeer@';
    $dbhost = 'localhost';
    $connect = @mysqli_connect($dbhost, $dbuser, $dbpass, $dbname);
    if (!$connect) {

        echo "Error: " . mysqli_connect_error();

        exit();
    }
  
    echo "Connection Success!<br><br>";
    // Check if it's a POST request

    // Handle GET request

    $temperature = isset($_GET["temperature"]) ? $_GET["temperature"] : "";
    $pressure= isset($_GET["pressure"]) ? $_GET["pressure"] : "";
    $humidity = isset($_GET["humidity"]) ? $_GET["humidity"] : "";
    $Time = isset($_GET["Time"]) ? $_GET["Time"] : "";

    $temperature = 0.6;
    $pressure = 0.8;
    $humidity = 0.9;
  if( $Time == null){
    $Time = date("H:i:s");
   }

    // Debug output

    echo "Received temperature via GET: $temperature<br>";
    echo "Received pressure via GET: $pressure<br>";
    echo "Received humidity via GET: $humidity<br>";
    echo "Received time: $Time<br>";

    $query = "INSERT INTO weerstation (temperature,pressure,humidity,Tijd) VALUES ('$temperature', '$pressure','$humidity','$Time')";

    echo "Query: $query<br>";  // Debug output
    $Time = date("H:i:s");
    echo "current time: $Time<br>";
    $result = mysqli_query($connect, $query);



    if ($result) {

        echo "Insertion Success!<br>";
    } else {

        echo "Error: " . mysqli_error($connect);
    }



    ?>

</body>

</html>