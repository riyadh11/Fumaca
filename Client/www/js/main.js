// chart
window.onload = function () {
		var dataPoints = []
	      var dataPointsTemp = [];
	      var dataPointsHum = [];
	      var dataPointsOxy = [];
	      var dataPointsPh = [];
	      
	      var chart = new CanvasJS.Chart("chartContainer",{
	      	zoomEnabled: true,
	      	title :{
	      		text: "Live Data"
	      	},
	      	axisX: {						
	      		title: "Waktu"
	      	},
	      	axisY: {						
	      		title: "Tingkat Pencemaran Udara"
	      	},
	      	data: [
		      	{
		      		type: "spline",
					name: "Humidity",
					showInLegend: true,
					dataPoints: dataPointsHum
		      	},
		      	{
		      		type: "spline",  
					name: "Temperature",        
					showInLegend: true,
					dataPoints: dataPointsTemp
		      	},
		      	{
		      		type: "spline",
					name: "Oxygen",
					showInLegend: true,
					dataPoints: dataPointsOxy
		      	},
		      	{
		      		type: "spline",  
					name: "Ph",        
					showInLegend: true,
					dataPoints: dataPointsPh
		      	}
	      	]

	      });

	      var chart = new CanvasJS.Chart("chartAsap",{
	      	title :{
	      		text: "Asap"
	      	},
	      	axisX: {						
	      		title: "Waktu"
	      	},
	      	axisY: {						
	      		title: "Tingkat Asap"
	      	},
	      	data: [
		      	{
		      		type: "splineArea",
					name: "Asap",
					showInLegend: true,
					dataPoints: dataPointsHum
		      	}
	      	]
	      });

	      var chart = new CanvasJS.Chart("chartKarbon",{
	      	title :{
	      		text: "Karbon"
	      	},
	      	axisX: {						
	      		title: "Waktu"
	      	},
	      	axisY: {						
	      		title: "Tingkat Karbon"
	      	},
	      	data: [
		      	{
		      		type: "splineArea",
					name: "Karbon",
					showInLegend: true,
					dataPoints: dataPointsHum
		      	}
	      	]
	      });

	      var chart = new CanvasJS.Chart("chartNitro",{
	      	title :{
	      		text: "Nitrogen"
	      	},
	      	axisX: {						
	      		title: "Waktu"
	      	},
	      	axisY: {						
	      		title: "Tingkat Nitrogen"
	      	},
	      	data: [
		      	{
		      		type: "splineArea",
					name: "Nitrogen",
					showInLegend: true,
					dataPoints: dataPointsHum
		      	}
	      	]
	      });

	      var chart = new CanvasJS.Chart("chartAsap",{
	      	title :{
	      		text: "Asap"
	      	},
	      	axisX: {						
	      		title: "Waktu"
	      	},
	      	axisY: {						
	      		title: "Tingkat Asap"
	      	},
	      	data: [
		      	{
		      		type: "splineArea",
					name: "Asap",
					showInLegend: true,
					dataPoints: dataPointsHum
		      	}
	      	]
	      });

	     var xVal = dataPointsTemp.length + 1;
	      // var yVal = 15;	
	      // var updateInterval = 1000;
	     function addData(data) {
			for (var i = 0; i < data.length; i++) {
				dataPointsTemp.push({
					x: xVal,
					y: data[i].temperature
				});
				dataPointsHum.push({
					y: data[i].humidity
				});
				dataPointsOxy.push({
					y: data[i].oxygen
				});
				dataPointsPh.push({
					y: data[i].ph
				});

				xVal++
				if (dataPointsTemp.length >  30 )
		      	{
		      		dataPointsTemp.shift();		
		      		dataPointsHum.shift();	
		      		dataPointsOxy.shift();
		      		dataPointsPh.shift();
		      	}
			}
			chart.render();

		}

		var updateChart = function () {
	      	$.getJSON("http://13.67.76.30/sensor", function(data){
	      	for (var i = 0; i < data.length; i++) {
				dataPointsTemp.push({
					x: xVal,
					y: data[i].temperature
				});
				dataPointsHum.push({
					x: xVal,
					y: data[i].humidity
				});
				dataPointsOxy.push({
					x: xVal,
					y: data[i].oxygen
				});
				dataPointsPh.push({
					x: xVal,
					y: data[i].ph
				});
				xVal++;
				if (dataPointsTemp.length > 20 )
		      	{
		      		dataPointsTemp.shift();		
		      		dataPointsHum.shift();	
		      		dataPointsOxy.shift();
		      		dataPointsPh.shift();
		      	}
			}
	      	
	      	chart.render();
	      });

	};

// $.getJSON("http://127.0.0.1:7777/sensor", addData);
setInterval(function(){updateChart()}, 5000); 
	  
	}

	//       var updateChart = function () {
	//       	$.getJSON("http://127.0.0.1:7777/sensor", function(result){
	//       	for (var i = 0; i < result.length; i++) {
	//       		dataPoints.push({
	//       			x: xVal,
	//       			y: result[i].temperature
	//       		});
	//       		xVal++;
	//       		if (dataPoints.length >  10 )
	// 	      	{
	// 	      		dataPoints.shift();				
	// 	      	}
	//       	}
	      	
	//       	chart.render();
	//       });
	// };

