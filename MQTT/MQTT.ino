

#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <String.h>

// Update these with values suitable for your network.
char data[500];
int LedH = D0;
int LedM = D1;
int LedB = D2;
char* sendData(String sensorParam) {
  String sensorVal = String(sensorParam);

  sensorVal.toCharArray(data, 32);
  return data;
}

//static const char ssid[] = "Makuna Hatata";
//static const char password[] = "mbayarsek";
//
//const char* mqtt_server = "ngehubx.online";
//const char* ssid = "Makuna Hatata";
//const char* password = "mbayarsek";
const char* ssid = "Theex-HQ";
const char* password = "JuraganPeceLyeye";
//const char* ssid = "skripsi";
//const char* password = "admin123";
const char* mqtt_server = "ngehubx.online";
char temp[100];
int isi;
StaticJsonBuffer <200> jsonBuffer;

//String temp_str;


WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[32];
int value = 0;

void setup() {
  pinMode(BUILTIN_LED, OUTPUT);     // Initialize the BUILTIN_LED pin as an output
  Serial.begin(115200);
  pinMode(LedH, OUTPUT);
  pinMode(LedM, OUTPUT);
  pinMode(LedB, OUTPUT);
  digitalWrite(LedH, HIGH);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void setup_wifi() {

  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  digitalWrite(LedB, HIGH);
  digitalWrite(LedH, LOW);
}

void callback(char* topic, byte* payload, unsigned int length) {
  char inData[80];

  Serial.print("payload: ");
  for (int i = 26; i < length; i++) {
    // Serial.print((char)payload[i]);
    inData[(i - 26)] = (char)payload[i];
  }
  Serial.println();
  JsonObject& root = jsonBuffer.parseObject(inData);
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  // Serial.print(isi);
  Serial.println();
  //delay (1000);
  // Switch on the LED if an 1 was received as first character
  if ((char)payload[0] == '1') {
    digitalWrite(BUILTIN_LED, LOW);   // Turn the LED on (Note that LOW is the voltage level
    // but actually the LED is on; this is because
    // it is acive low on the ESP-01)
  } else {
    digitalWrite(BUILTIN_LED, HIGH);  // Turn the LED off by making the voltage HIGH
  }
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("ESP8266Client", "admintes", "admin123")) {
      Serial.println("connected");
      // Once connected, publish an announcement...
//      client.publish("coba/renal", "hello world");
      // ... and resubscribe
      //client.subscribe("theex/smoq/data");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      //delay(5000);
    }
  }
}

int asap, karbon, ozon, sulfur, nitro, suhu;

void loop() {


  if (!client.connected()) {
    reconnect();
  }
  //  client.loop();
  value++;
//  isi = Serial.parseFloat();

//    if (value == 1) {
//      //asap = isi
//      asap = isi;
//    } else if (value == 2) {
//      karbon = isi;
//    } else if (value == 3) {
//      ozon = isi;
//    } else if (value == 4) {
//      sulfur = isi;
//    } else if (value == 5) {
//      nitro = isi;
//    } else if (value == 6) {
//      suhu = isi;
//     value = 0;
//      String payload = "{";
//      payload += "\"asap\":"; payload += asap; payload += ",";
//      payload += "\"karbon\":"; payload += karbon; payload += "," ;
//      payload += "\"ozon\":"; payload += ozon; payload += ",";
//      payload += "\"sulfur\":"; payload += sulfur; payload += ",";
//      payload += "\"nitrogen\":"; payload += nitro; payload += ",";
//      payload += "\"suhu\":"; payload; payload += suhu;
//      //payload += "\"karbonMQ2\":"; payload += karbon7;
//      payload += "}";
//  
//      char attributes [100];
//      payload.toCharArray( attributes, 100 );
//      client.publish( "coba/renal", attributes );
//      Serial.println( attributes );
//      delay(1);
//    }


  if (Serial.available()) {
//    digitalWrite(LedM, HIGH);
//    delay(500);
//    digitalWrite(LedM, LOW);
    for (int i = 1; i < 7; i++) {
      isi = Serial.parseFloat();
      //read Data
      if (i == 1) {
        asap = isi;
      } else if (i == 2) {
        karbon = isi;
      } else if (i == 3) {
        ozon = isi;
      } else if (i == 4) {
        sulfur = isi;
      } else if (i == 5) {
        nitro = isi;
      } else if (i == 6) {
        suhu = isi;
      }
      
    }
    if(isi == 0){
      digitalWrite(LedM, LOW);
    }else{
      digitalWrite(LedM, HIGH);
    }
  } else {
    
    return;
  }
  String payload = "{";
      payload += "\"asap\":"; payload += asap; payload += ",";
      payload += "\"karbon\":"; payload += karbon; payload += "," ;
      payload += "\"ozon\":"; payload += ozon; payload += ",";
      payload += "\"sulfur\":"; payload += sulfur; payload += ",";
      payload += "\"nitrogen\":"; payload += nitro; payload += ",";
      payload += "\"suhu\":"; payload; payload += suhu;
      //payload += "\"karbonMQ2\":"; payload += karbon7;
      payload += "}";
  
      char attributes [100];
      payload.toCharArray( attributes, 100 );
      Serial.println( attributes );
      client.publish( "project/dataSensor", attributes );
      Serial.println( attributes );
      delay(1000);
      digitalWrite(LedM, LOW);
}


//client.publish("theex/smoq/data", (char*)isi);


