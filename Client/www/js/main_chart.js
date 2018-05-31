window.onload = function () {
	var datapoints = [];
	$.getJSON("http://13.67.76.30/statistik", function(data){
		
      	for (var i = 0; i < data.length; i++) {
			datapoints.push(
				data[i].average.asap,
				data[i].average.karbon,
				data[i].average.nitrogen,
				data[i].average.ozon,
				data[i].average.suhu,
				data[i].average.sulfur
			);
		}

		let myChart = document.getElementById('chartContainer').getContext('2d');

	let popChart = new Chart(myChart,{
		type:'bar',
		data:{
			labels:['Asap','Karbon','Nitrogen','Ozon','Suhu','Sulfur'],
			datasets:[{
				label: 'Kadar Pencemaran Udara',
				// data:[80,99,23,16,65,44],
				data: datapoints,
				backgroundColor:[
				'rgba(54, 162, 235, 0.6)',
	            'rgba(255, 206, 86, 0.6)',
	            'rgba(75, 192, 192, 0.6)',
	            'rgba(153, 102, 255, 0.6)',
	            'rgba(255, 159, 64, 0.6)',
	            'rgba(255, 99, 132, 0.6)']
			}
			]
		},
		options:{
			title:{
				display:true,
				text: 'Sensor Monitoring Polusi Udara',
				fontSize:23
			}
		}
	});
	var wrapper = document.getElementById("tbl-home");
	  var myHTML = "";
	  
	    myHTML = "<tr><td>Asap</td><td>"+datapoints[0]+"</td></tr>"+
	    "<tr><td>Karbon</td><td>"+datapoints[1]+"</td></tr>"+
	    "<tr><td>Nitrogen</td><td>"+datapoints[2]+"</td></tr>"+
	    "<tr><td>Ozon</td><td>"+datapoints[3]+"</td></tr>"+
	    "<tr><td>Suhu</td><td>"+datapoints[4]+"</td></tr>"+
	    "<tr><td>Sulfur</td><td>"+datapoints[5]+"</td></tr>";
	  
	  wrapper.innerHTML = myHTML;
      	
      });

	
}