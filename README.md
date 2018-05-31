# Fumaca
Smoke detection system, build with Arduino, MQTT, Hadoop, Spark, MongoDB and Flask

## Requirement
- [Vagrant Carbonifero](https://github.com/riyadh11/Carbonifero)
- Minimum 2 Nodes
- Apache Spark
- Mosquitto
- Flask
- Apache ZooKeeper
- Apache Hadoop
- MongoDB
- Python library for those application (paho-mqtt,flask,pydoop,pyspark,pymongo)

## IoT Device
Arduino with 5 Sensor which is :
- Temperature
- Ozon
- Smoke
- Nitrogen
- Carbon
- Sulfur

As well as MQTT Handler and NRF Controller

## Installation
First you must clone this Repository

`$ git clone https://github.com/riyadh11/Fumaca.git`

and then, compile IoT Firmware to your devices using Arduino IDE

Then, Configure this folder to link to your Vagrant Carbonifero shared folder

Then, Start MongoDB, Spark and Hadoop at your Virtual Machines

    $ mongod
    
    $ start-dfs.sh
    
    $ start-yarn.sh
    
    $ $SPARK_HOME/sbin/start-all.sh

Then, Start your IoT Devices and also start the Gateway and Receiver at VM

Then, Start the Storage Analysis Process

`$ python StorageAnalysis.py 10`

Then, Start the Analysis Process

`$ python AnalysisProcess.py 10`

Note the number of minute in Storage Analysis process and Analysis process must be same.

Then, Start Web server using Flask

`$ python WebServer.py`

Voila, System sucessfully Running

## Security
If you discover any security related issues, please email ahmad.riyadh.al@faathin.com instead of using the issue tracker.

## License
The GNU General Public License v2.0. Please see [License File](LICENSE) for more information.