
//#include <Bridge.h>
//#include <BridgeClient.h>
//#include <BridgeServer.h>
//#include <BridgeSSLClient.h>
//#include <BridgeUdp.h>
//#include <Console.h>
//#include <FileIO.h>
//#include <HttpClient.h>
//#include <Mailbox.h>
//#include <Process.h>
//#include <YunClient.h>
//#include <YunServer.h>

/************************mq2sensor************************************/
/************************Hardware Related Macros************************************/
#include "DHT.h"
#include <SPI.h>
#include <Mirf.h>
#include <nRF24L01.h>
#include <MirfHardwareSpiDriver.h>
#define         MQ2PIN                       (0)
#define         MQ7PIN                       (1)
#define         MQ131PIN                     (2)
#define         MQ136PIN                     (4)
#define         DHTPIN                       (6)
DHT dht(DHTPIN, DHT22);
#define         RL_VALUE_MQ2                 (1)
#define         RL_VALUE_MQ7                 (1)
#define         RL_VALUE_MQ131               (1)
#define         RL_VALUE_MQ136               (1)

//define the load resistance on the board, in kilo ohms
#define         RO_CLEAN_AIR_FACTOR_MQ2      (9.577)  //RO_CLEAR_AIR_FACTOR=(Sensor resistance in clean air)/RO,
#define         RO_CLEAN_AIR_FACTOR_MQ7      (26.09)
//#define         RO_CLEAN_AIR_FACTOR_MQ2      (20)  //RO_CLEAR_AIR_FACTOR=(Sensor resistance in clean air)/RO,
//#define         RO_CLEAN_AIR_FACTOR_MQ7      (26.09)
#define         RO_CLEAN_AIR_FACTOR_MQ131    (20)
#define         RO_CLEAN_AIR_FACTOR_MQ136    (20)
//which is derived from the chart in datasheet

/***********************Software Related Macros************************************/
#define         CALIBARAION_SAMPLE_TIMES     (10)//(50)    //define how many samples you are going to take in the calibration phase
#define         CALIBRATION_SAMPLE_INTERVAL  (400)//(500)   //define the time interal(in milisecond) between each samples in the
//cablibration phase
#define         READ_SAMPLE_INTERVAL         (2)    //define how many samples you are going to take in normal operation
#define         READ_SAMPLE_TIMES            (2)     //define the time interal(in milisecond) between each samples in 
//normal operation

/**********************Application Related Macros**********************************/
#define         GAS_HYDROGEN                  (0)
#define         GAS_LPG                       (1)
#define         GAS_METHANE                   (2)
#define         GAS_CARBON_MONOXIDE           (3)
#define         GAS_ALCOHOL                   (4)
#define         GAS_SMOKE                     (5)
#define         GAS_PROPANE                   (6)
#define         GAS_O3                        (7)
#define         GAS_SO2                       (8)
#define         GAS_NO2                       (9)
#define         accuracy                      (0)   //for linearcurves
//#define         accuracy                    (1)   //for nonlinearcurves, un comment this line and comment the above line if calculations
//are to be done using non linear curve equations
/*****************************Globals************************************************/
float           Ro2 = 0, Ro7 = 0, Ro131 = 0, Ro136 = 0;                           //Ro is initialized to 10 kilo ohms
const char payload_length = 32;
byte data[payload_length];
String minta = "req";

void sendData(String sensorParam) {
  String sensorVal = String(sensorParam);
  char data[32];
  sensorVal.toCharArray(data, 32);
  Mirf.send((byte*) data);
  while (Mirf.isSending()) {
    /* code */
  }
  delay(1000);
}

void setup() {
  Serial.begin(9600);                               //UART setup, baudrate = 9600bps
  pinMode(DHTPIN, INPUT);
  dht.begin();
  Serial.print("Calibrating...\n");
  Ro2 = MQCalibration2(MQ2PIN);                       //Calibrating the sensor. Please make sure the sensor is in clean air
  Ro7 = MQCalibration7(MQ7PIN);
  Ro131 = MQCalibration131(MQ131PIN);
  Ro136 = MQCalibration136(MQ136PIN);

  Serial.print("Calibration is done...\n");
  Serial.print("Ro MQ2=");
  Serial.print(Ro2);
  Serial.print("kohm");
  Serial.print("\n");
  Serial.print("Ro MQ7=");
  Serial.print(Ro7);
  Serial.print("kohm");
  Serial.print("\n");
  Serial.print("Ro MQ131=");
  Serial.print(Ro131);
  Serial.print("kohm");
  Serial.print("\n");
  Serial.print("Ro MQ136=");
  Serial.print(Ro136);
  Serial.print("kohm");
  Serial.print("\n");

  Mirf.spi = &MirfHardwareSpi;
  Mirf.init();
  Mirf.setTADDR((byte *)"serve");
  Mirf.payload = payload_length;
  Mirf.channel = 123;
  Mirf.config();


}

void loop() {
  //  Serial.print("SMOKE MQ2:");
  //  Serial.print(MQGetGasPercentage2(MQRead2(MQ2PIN) / Ro2, GAS_SMOKE) );
  //  Serial.print( "ppm" );
  //  Serial.print("    ");
  //  Serial.print("CARBON_MONOXIDE MQ2:");
  //  Serial.print(MQGetGasPercentage2(MQRead2(MQ2PIN) / Ro2, GAS_CARBON_MONOXIDE) );
  //  Serial.print( "ppm" );
  //  Serial.print("    ");
  //  Serial.print("CARBON_MONOXIDE:");
  //  Serial.print(MQGetGasPercentage7(MQRead7(MQ7PIN) / Ro7, GAS_CARBON_MONOXIDE) );
  //  Serial.print( "ppm" );
  //  Serial.print("    ");
  //  Serial.print("\n");
  //  delay(200);

  float h = dht.readHumidity();
  float t = dht.readTemperature();
  String dataMsg = String(MQGetGasPercentage2(MQRead2(MQ2PIN) / Ro2, GAS_SMOKE) ) + " " +
                   String(MQGetGasPercentage7(MQRead7(MQ7PIN) / Ro7, GAS_CARBON_MONOXIDE) ) + " " +
                   String(MQGetGasPercentage131(MQRead131(MQ131PIN) / Ro131, GAS_O3) ) + " "  +
                   String(MQGetGasPercentage136(MQRead136(MQ136PIN) / Ro136, GAS_SO2) ) + " " +
                   String(MQGetGasPercentage131(MQRead131(MQ131PIN) / Ro131, GAS_NO2) ) + " "  +
                   String(t);
  Serial.println(dataMsg);
  Serial.println("masuk");
  sendData(dataMsg);
  //  delay(1000);
  delay(500);
}

/****************** MQResistanceCalculation ****************************************
  Input:   raw_adc - raw value read fRo2m adc, which represents the voltage
  Output:  the calculated sensor resistance
  Remarks: The sensor and the load resistor forms a voltage divider. Given the voltage
         across the load resistor and its resistance, the resistance of the sensor
         could be derived.
************************************************************************************/
float MQResistanceCalculation2(int raw_adc2)
{
  return ( ((float)RL_VALUE_MQ2 * (1023 - raw_adc2) / raw_adc2));
}

float MQResistanceCalculation7(int raw_adc7)
{
  return ( ((float)RL_VALUE_MQ7 * (1023 - raw_adc7) / raw_adc7));
}

float MQResistanceCalculation131(int raw_adc131)
{
  return ( ((float)RL_VALUE_MQ131 * (1023 - raw_adc131) / raw_adc131));
}

float MQResistanceCalculation136(int raw_adc136)
{
  return ( ((float)RL_VALUE_MQ136 * (1023 - raw_adc136) / raw_adc136));
}

/***************************** MQCalibration ****************************************
  Input:   mq_pin - analog channel
  Output:  Ro of the sensor
  Remarks: This function assumes that the sensor is in clean air. It use
         MQResistanceCalculation to calculates the sensor resistance in clean air
         and then divides it with RO_CLEAN_AIR_FACTOR. RO_CLEAN_AIR_FACTOR is about
         10, which differs slightly between different sensors.
************************************************************************************/
float MQCalibration2(int mq_pin2)
{
  int i;
  float RS_AIR_val2 = 0, r02;

  for (i = 0; i < CALIBARAION_SAMPLE_TIMES; i++) {               //take multiple samples
    RS_AIR_val2 += MQResistanceCalculation2(analogRead(mq_pin2));
    delay(CALIBRATION_SAMPLE_INTERVAL);
  }
  RS_AIR_val2 = RS_AIR_val2 / CALIBARAION_SAMPLE_TIMES;            //calculate the average value

  r02 = RS_AIR_val2 / RO_CLEAN_AIR_FACTOR_MQ2;                    //RS_AIR_val divided by Ro2_CLEAN_AIR_FACTOR yields the Ro2
  //according to the chart in the datasheet

  return r02;
}

float MQCalibration7(int mq_pin7)
{
  int i;
  float RS_AIR_val7 = 0, r07;

  for (i = 0; i < CALIBARAION_SAMPLE_TIMES; i++) {               //take multiple samples
    RS_AIR_val7 += MQResistanceCalculation7(analogRead(mq_pin7));
    delay(CALIBRATION_SAMPLE_INTERVAL);
  }
  RS_AIR_val7 = RS_AIR_val7 / CALIBARAION_SAMPLE_TIMES;            //calculate the average value

  r07 = RS_AIR_val7 / RO_CLEAN_AIR_FACTOR_MQ7;                    //RS_AIR_val divided by RO_CLEAN_AIR_FACTOR yields the Ro
  //according to the chart in the datasheet

  return r07;
}

float MQCalibration131(int mq_pin131)
{
  int i;
  float RS_AIR_val131 = 0, r0131;

  for (i = 0; i < CALIBARAION_SAMPLE_TIMES; i++) {               //take multiple samples
    RS_AIR_val131 += MQResistanceCalculation131(analogRead(mq_pin131));
    delay(CALIBRATION_SAMPLE_INTERVAL);
  }
  RS_AIR_val131 = RS_AIR_val131 / CALIBARAION_SAMPLE_TIMES;            //calculate the average value

  r0131 = RS_AIR_val131 / RO_CLEAN_AIR_FACTOR_MQ131;                    //RS_AIR_val divided by RO_CLEAN_AIR_FACTOR yields the Ro
  //according to the chart in the datasheet

  return r0131;
}

float MQCalibration136(int mq_pin136)
{
  int i;
  float RS_AIR_val136 = 0, r0136;

  for (i = 0; i < CALIBARAION_SAMPLE_TIMES; i++) {               //take multiple samples
    RS_AIR_val136 += MQResistanceCalculation136(analogRead(mq_pin136));
    delay(CALIBRATION_SAMPLE_INTERVAL);
  }
  RS_AIR_val136 = RS_AIR_val136 / CALIBARAION_SAMPLE_TIMES;            //calculate the average value

  r0136 = RS_AIR_val136 / RO_CLEAN_AIR_FACTOR_MQ136;                    //RS_AIR_val divided by RO_CLEAN_AIR_FACTOR yields the Ro
  //according to the chart in the datasheet

  return r0136;
}
/*****************************  MQRead *********************************************
  Input:   mq_pin - analog channel
  Output:  Rs of the sensor
  Remarks: This function use MQResistanceCalculation to caculate the sensor resistenc (Rs).
         The Rs changes as the sensor is in the different consentration of the target
         gas. The sample times and the time interval between samples could be configured
         by changing the definition of the macRo2s.
************************************************************************************/
float MQRead2(int mq_pin2)
{
  int i;
  float rs2 = 0;

  for (i = 0; i < READ_SAMPLE_TIMES; i++) {
    rs2 += MQResistanceCalculation2(analogRead(mq_pin2));
    delay(READ_SAMPLE_INTERVAL);
  }

  rs2 = rs2 / READ_SAMPLE_TIMES;

  return rs2;
}

float MQRead7(int mq_pin7)
{
  int i;
  float rs7 = 0;

  for (i = 0; i < READ_SAMPLE_TIMES; i++) {
    rs7 += MQResistanceCalculation7(analogRead(mq_pin7));
    delay(READ_SAMPLE_INTERVAL);
  }

  rs7 = rs7 / READ_SAMPLE_TIMES;

  return rs7;
}

float MQRead131(int mq_pin131)
{
  int i;
  float rs131 = 0;

  for (i = 0; i < READ_SAMPLE_TIMES; i++) {
    rs131 += MQResistanceCalculation7(analogRead(mq_pin131));
    delay(READ_SAMPLE_INTERVAL);
  }

  rs131 = rs131 / READ_SAMPLE_TIMES;

  return rs131;
}

float MQRead136(int mq_pin136)
{
  int i;
  float rs136 = 0;

  for (i = 0; i < READ_SAMPLE_TIMES; i++) {
    rs136 += MQResistanceCalculation136(analogRead(mq_pin136));
    delay(READ_SAMPLE_INTERVAL);
  }

  rs136 = rs136 / READ_SAMPLE_TIMES;

  return rs136;
}
/*****************************  MQGetGasPercentage **********************************
  Input:   rs_Ro2_ratio - Rs divided by Ro2
         gas_id      - target gas type
  Output:  ppm of the target gas
  Remarks: This function uses different equations representing curves of each gas to
         calculate the ppm (parts per million) of the target gas.
************************************************************************************/
int MQGetGasPercentage2(float rs_ro_ratio2, int gas_id2)
{
  if ( accuracy == 0 ) {
    if ( gas_id2 == GAS_CARBON_MONOXIDE ) {
      return (pow(10, ((-2.955 * (log10(rs_ro_ratio2))) + 4.400)));
    } else if ( gas_id2 == GAS_SMOKE ) {
      return (pow(10, ((-2.331 * (log10(rs_ro_ratio2))) + 3.596)));
    }
  }
  else if ( accuracy == 1 ) {
    if ( gas_id2 == GAS_CARBON_MONOXIDE ) {
      return (pow(10, ((-2.955 * (log10(rs_ro_ratio2))) + 4.457)));
    } else if ( gas_id2 == GAS_SMOKE ) {
      return (pow(10, (-0.976 * pow((log10(rs_ro_ratio2)), 2) - 2.018 * (log10(rs_ro_ratio2)) + 3.617)));
    }
  }
  return 0;
}

int MQGetGasPercentage7(float rs_ro_ratio7, int gas_id7)
{
  if ( accuracy == 0 ) {
    if ( gas_id7 == GAS_CARBON_MONOXIDE ) {
      return (pow(10, ((-1.525 * (log10(rs_ro_ratio7))) + 1.960)));
    }
  }
  else if ( accuracy == 1 ) {
    if ( gas_id7 == GAS_CARBON_MONOXIDE ) {
      return (pow(10, ((-1.525 * (log10(rs_ro_ratio7))) + 1.994)));
    }
  }
  return 0;
}

int MQGetGasPercentage131(float rs_ro_ratio131, int gas_id131)
{
  if ( accuracy == 0 ) {
    if ( gas_id131 == GAS_O3 ) {
      return (pow(10, ((-0.8916 * (log10(rs_ro_ratio131))) + 1.5427)));
    } else if ( gas_id131 == GAS_NO2 ) {
      return (pow(10, ((-3.8398 * (log10(rs_ro_ratio131))) + 4.386)));
    }
  }
  else if ( accuracy == 1 ) {
    if ( gas_id131 == GAS_O3 ) {
      return (pow(10, (0.2889 * pow((log10(rs_ro_ratio131)), 2) - 1.0574 * (log10(rs_ro_ratio131)) + 1.5161)));
    } else if ( gas_id131 == GAS_NO2 ) {
      return (pow(10, (-2.4248 * pow((log10(rs_ro_ratio131)), 2) - 0.0374 * (log10(rs_ro_ratio131)) + 2.9193)));
      return 0;
    }
  }
}


int MQGetGasPercentage136(float rs_ro_ratio136, int gas_id136)
{
  if ( accuracy == 0 ) {
    if ( gas_id136 == GAS_SO2 ) {
      return (pow(10, ((-0.8916 * (log10(rs_ro_ratio136))) + 1.5427)));
    }
    else if ( accuracy == 1 ) {
      if ( gas_id136 == GAS_SO2 ) {
        return (pow(10, (0.2889 * pow((log10(rs_ro_ratio136)), 2) - 1.0574 * (log10(rs_ro_ratio136)) + 1.5161)));
      }
      return 0;
    }
  }
}

