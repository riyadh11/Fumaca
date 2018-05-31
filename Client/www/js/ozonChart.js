window.onload = function () {
	var datapoints = [];
	var labels = [];
	function updateChart(){
	$.getJSON("http://13.67.76.30/sensor/300", function(data){
		
      	for (var i = 0; i < data.length; i++) {
			datapoints.push(
				data[i].ozon
			);
			labels.push(
				new Date(data[i].datetime).getMinutes() + " Menit"
			);
			if (datapoints.length >  10 )
	      	{
	      		datapoints.shift();
	      		labels.shift();				
	      	}
		}
		console.log(labels);
		let myChart = document.getElementById('chartContainer').getContext('2d');

	let popChart = new Chart(myChart,{
		type:'line',
		data:{
			labels:labels,
			datasets:[{
				label: 'Kadar Pencemaran Udara',
				data: datapoints,
				backgroundColor:'rgba(153, 102, 255, 0.6)'
	   //          'rgba(255, 159, 64, 0.6)',
	   //          'rgba(255, 99, 132, 0.6)']
			}
			]
		},
		options:{
			title:{
				display:true,
				text: 'Sensor Ozon',
				fontSize:23
			}
		}
	});
      	
      });
	$.getJSON("http://13.67.76.30/statistik", function(data){
		var wrapper = document.getElementById("tbl-home");
	  var myHTML = "";
		var myHTML = "<tr><td>Nilai</td><td>"+data[0].max.ozon+"</td><td>"+data[0].min.ozon+"</td><td>"+data[0].average.ozon+"</td></tr>"
		wrapper.innerHTML = myHTML;
	});

	}

	updateChart();
	
	setInterval(updateChart(), 1000); 
}