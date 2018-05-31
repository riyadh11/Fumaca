<?php

?>

<!DOCTYPE html>
<html>
<head>
	<title></title>
	<meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <meta http-equiv="X-UA-Compatible" content="ie=edge">
    <link rel="stylesheet" href="css/all.css" >
	<link rel="stylesheet" href="css/semantic.min.css">
</head>
<body>
	<div class="ui sidebar inverted vertical menu">
		<a class="padded item">
			<i class="fas fa-home fa-3x">SMOQ</i>
		</a>
		<a class="item">
			menu 1
		</a>
		<a class="item">
			menu 2
		</a>
		<a href="logout.php" class="red item">
			Logout
		</a>
	</div>
	<div class="pusher">
		<div class="ui container">
			<div class="ui secondary menu">
				<a class="active item" id="openmenu">
					Menu
				</a>
				
			</div>
			<div class="ui teal inverted segment">
				<h1>Selamat Datang, <?php echo "$username";?></h1>
			</div>
			<div class="ui segments">
				<div class="ui segment">
				<a class="ui big header" href="#">Berita 1</a>
			  	<p>Lorem ipsum dolor sit amet, consectetur adipisicing elit, sed do eiusmod
			  	tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam,
			  	quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo
				</p>
				<a href="#">Read More...</a>
			</div>
			<div class="ui segment">
				<a class="ui big header" href="#">Berita 2</a>
			  	<p>Lorem ipsum dolor sit amet, consectetur adipisicing elit, sed do eiusmod
			  	tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam,
			  	quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo
				</p>
				<a href="#">Read More...</a>
			</div>
			<div class="ui segment">
				<a class="ui big header" href="#">Berita 3</a>
			  	<p>Lorem ipsum dolor sit amet, consectetur adipisicing elit, sed do eiusmod
			  	tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam,
			  	quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo
				</p>
				<a href="#">Read More...</a>
			</div>
			</div>
		</div>

		<footer>
			<div class="ui segment">
				<p>
					<center>SMOQ &copy 2018</center>
				</p>
			</div>
			
		</footer>
	</div>
</body>
</html>