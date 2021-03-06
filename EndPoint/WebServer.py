#!/usr/bin/python
### Ahmad Riyadh Al Faathin - 155150207111052 - SKT C - Faathin.com ###
# Import library Flask, Database Handler and Bson
from sys import path
from flask import Flask,jsonify,json
from flask_cors import CORS
from bson.json_util import dumps
path.insert(0,"../Common/")
from DatabaseHandler import DatabaseHandler

app = Flask("Sensor App")
CORS(app)

DATABASE_IP = "10.11.12.13"
DATABASE_PORT = 27171

@app.route('/sensor', methods=['GET'])
def handleSensor():
    Database = DatabaseHandler(DATABASE_IP, DATABASE_PORT,"smartSystem")
    logs = list(Database.findBulkDocument("sensor", select={"_id":False}, sort=[("datetime",-1)], limit=60))
    return jsonify(logs)

@app.route('/sensor/<int:get>', methods=['GET'])
def handleSensorLimit(get):
    Database = DatabaseHandler(DATABASE_IP, DATABASE_PORT,"smartSystem")
    logs = list(Database.findBulkDocument("sensor", select={"_id":False}, sort=[("datetime",-1)], limit=get))
    return jsonify(logs)

@app.route('/statistik', methods=['GET'])
def handleStatistik():
    Database = DatabaseHandler(DATABASE_IP, DATABASE_PORT,"smartSystem")
    logs = list(Database.findBulkDocument("statistik", select={"_id":False}, sort=[("datetime",-1)], limit=1))
    return jsonify(logs)

app.run(port=80, host="0.0.0.0")