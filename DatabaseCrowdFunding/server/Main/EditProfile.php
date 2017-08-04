<?php
	session_start();
	$loginname = $_SESSION["username"];
	if (!isset($loginname)){
		echo "<script>location.href='../index.html';</script>";
	}
	require_once("../connect.php");
?>

<html>
<title>Profile</title>
  <head>
    <!-- Bootstrap CSS -->
    <link rel="stylesheet" href="http://netdna.bootstrapcdn.com/bootstrap/3.1.0/css/bootstrap.min.css">
    <link href="http://127.0.0.1/css/styles.css" rel="stylesheet">

  </head>
	
	<!-- bar -->
	<div "col-md-12 barContainer" id="barView">
		<div id="navBar">
				<ul>
					<li><button id="Main" class="btn-link" onclick="location.href='http://127.0.0.1/Main/Main.php'">
						<span>Projects</span></button></li>
					<li><button id="profile" class="btn-link" onclick="location.href='http://127.0.0.1/Main/Profile.php'">
						<span><?php echo $loginname ?></span></button></li>
					<li><button id="Log_out" class="btn-link" style="float: right;" onclick="location.href='http://127.0.0.1/logout.php'">
						<span>Log out</span></button></li>
				</ul>
		</div>
    </div>
	
	<!--Form for edited profile information-->
	<div style = "margin-top:10px; margin-left:10px">
		<form enctype="multipart/form-data" action="EditProfileUpload.php"
				method="post">
		<ul>
			<li><label for="uploadedfile">Select Protrait</label>
				<input type="file" size="35" name="uploadedfile" /></li>
			<li><label for="email">Email</label>
				<input type="text" name="email"></li>
			<li><input type="submit" name="submit" value="submit" /></li>
		</ul>
		</form>
	</div>
	
</html>