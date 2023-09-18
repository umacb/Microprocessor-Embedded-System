// Include the libraries we need
#include <OneWire.h>
#include <DallasTemperature.h>

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4); //The LCD address and size. You can change according you yours

// Data wire is plugged into port 2 on the Arduino
#define ONE_WIRE_BUS 2 //pin for sensor

// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);
float calibration_value = 18.84;
int phval = 0; 
unsigned long int avgval; 
int buffer_arr[10],temp;

/*
   The setup function. We only start the sensors here
*/
void setup(void)
{
  // start serial port
  Serial.begin(9600);
  Serial.println("Dallas Temperature IC Control Library Demo");

  // Start up the library
  sensors.begin();
  lcd.init();
  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Project");
  lcd.setCursor(0, 1);
  lcd.print("Microprocessor");
  delay(2000);
  lcd.clear();
}

/*
   Main function, get and show the temperature
*/
void loop(void)
{
  // call sensors.requestTemperatures() to issue a global temperature
  // request to all devices on the bus
  Serial.print("Requesting temperatures...");
  sensors.requestTemperatures(); // Send the command to get temperatures
  Serial.println("DONE");
  // After we got the temperatures, we can print them here.
  // We use the function ByIndex, and as an example get the temperature from the first sensor only.
  float tempC = sensors.getTempCByIndex(0);

  // Check if reading was successful
  if (tempC != DEVICE_DISCONNECTED_C)
  {
    Serial.print("Temperature for the device 1 (index 0) is: ");
    Serial.println(tempC);
    lcd.setCursor(0, 0);
    lcd.print("T");
    lcd.setCursor(1, 0);
    lcd.print(tempC);
    lcd.print((char)223);
    lcd.print("C");
    lcd.print("|");
    lcd.print(DallasTemperature::toFahrenheit(tempC));
    lcd.print("F");
  }
  else
  {
    Serial.println("Error: Could not read temperature data");
  }

   for(int i=0;i<10;i++) 
 { 
 buffer_arr[i]=analogRead(A0);
 delay(30);
 }
 for(int i=0;i<9;i++)
 {
 for(int j=i+1;j<10;j++)
 {
 if(buffer_arr[i]>buffer_arr[j])
 {
 temp=buffer_arr[i];
 buffer_arr[i]=buffer_arr[j];
 buffer_arr[j]=temp;
 }
 }
 }
 avgval=0;
 for(int i=2;i<8;i++)
 avgval+=buffer_arr[i];
 float volt=(float)avgval*5.0/1024/6;
 float ph_act = -5.70 * volt + calibration_value;
  lcd.setCursor(0, 1);
 lcd.print("pH Val:");
 lcd.setCursor(8, 1);
 lcd.print(ph_act);
 delay(1000);
}