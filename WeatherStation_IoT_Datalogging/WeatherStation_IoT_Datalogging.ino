#include <Bridge.h>
#include <Temboo.h>
#include <String.h>
#include "TembooAccount.h" // contains Temboo account information, as described below
Process date;  // process used to get the date      

int calls = 1;   // Execution count, better control over your calls

void setup() {
  Serial.begin(9600); //initialising serial communication and setting the boadrate to 9600
  while(!Serial);
  Serial.println("###################Initializing##################");
  // For debugging, wait until the serial console is connected
  delay(10000);
  Bridge.begin(); //linux x arduino = linuino!
}

String tempC;
int sensorReading;
void loop() {
      //Read what so ever the sensor was
    Serial.println("###################Sensors data##################");
    sensorReading = analogRead(A0);
    Serial.println("SensorRead = " + String(sensorReading)); 
    Serial.println("#################Sensors data read###############");

    Serial.println("######Running the Weather Station - Call#" + String(calls)+"#######");

    // Adding temboo processes
    TembooChoreo AppendValuesChoreo;
    TembooChoreo GetTemperatureChoreo;

    // Invoke the Temboo client
    AppendValuesChoreo.begin();
    GetTemperatureChoreo.begin();
    
    // Set Temboo account credentials, for both google sheets api and yahoo weather
    AppendValuesChoreo.setAccountName(TEMBOO_ACCOUNT);
    AppendValuesChoreo.setAppKeyName(TEMBOO_APP_KEY_NAME);
    AppendValuesChoreo.setAppKey(TEMBOO_APP_KEY);
    GetTemperatureChoreo.setAccountName(TEMBOO_ACCOUNT);
    GetTemperatureChoreo.setAppKeyName(TEMBOO_APP_KEY_NAME);
    GetTemperatureChoreo.setAppKey(TEMBOO_APP_KEY);

    // Identify the Choreo to run
    GetTemperatureChoreo.setChoreo("/Library/Yahoo/Weather/GetTemperature");
    
    // Set Choreo inputs
    GetTemperatureChoreo.addInput("Address", "City"); //You can Change the city
    GetTemperatureChoreo.addInput("Units", "c"); //C or F?
    
    // Identify the Choreo to run
    GetTemperatureChoreo.setChoreo("/Library/Yahoo/Weather/GetTemperature");

    // Run the Choreo; when results are available, print them to serial
    GetTemperatureChoreo.run();
    while(GetTemperatureChoreo.available() > 0) {     
      char c= GetTemperatureChoreo.read();    
      tempC=tempC+c;
      Serial.print(c); //print the JSON response 
    }
    GetTemperatureChoreo.close();
    Serial.println("########Yahoo Temprature API Respond Done########");

    String rowData = "[[\"" + String(timer()) + "\",\"" + String(calls++) + "\", \"" + String(analogRead(A0)) + "\", \"" + String(tempC.substring(13,16)) + "\"]]";

    // Set Choreo inputs
    AppendValuesChoreo.addInput("RefreshToken", "xxxxxxxxxxxxx");
    AppendValuesChoreo.addInput("ClientSecret", "xxxxxxxxxx");
    AppendValuesChoreo.addInput("Values", rowData);
    AppendValuesChoreo.addInput("ClientID", "xxxxxxxx-xxxxxxxxxxxx.apps.googleusercontent.com");
    AppendValuesChoreo.addInput("SpreadsheetID", "xxxxxx-xxxxxxxxxxxxxxxxxxxx");
    
    // Identify the Choreo to run
    AppendValuesChoreo.setChoreo("/Library/Google/Sheets/AppendValues");
    
    // Run the Choreo; when results are available, print them to serial
    AppendValuesChoreo.run();
    
    while(AppendValuesChoreo.available()) {
      char c = AppendValuesChoreo.read();
      Serial.print(c);
    }
    AppendValuesChoreo.close();
  
  tempC=""; //clear the string!
  Serial.println("Resting...");
  Serial.println("#-------------------------------------------------#");
  delay(3000); // wait 30 seconds between AppendValues calls
}
String timer(){
  if (!date.running())  {
    date.begin("date");
    date.addParameter("+%D-%T");
    date.run();
  }
  String timeString;
  while (date.available()>0) {
    timeString = date.readString();  }
    return timeString;
}


