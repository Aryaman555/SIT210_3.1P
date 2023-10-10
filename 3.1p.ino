#include <DHT.h>
#include <ThingSpeak.h>
#include <WiFiNINA.h>

#define DHTPIN 2        // Digital pin connected to the DHT sensor
#define DHTTYPE DHT22   // DHT 22 

DHT dht(DHTPIN, DHTTYPE);

char ssid[] = "Aryaman";          // Wifi Name
char password[] = "arya2703";  // wifi Password

// ThingSpeak settings
char thingSpeakApiKey[] = "Z69XOJRIPKDAKJB9";  
unsigned long channelID = 2251816; 
WiFiClient client;

 if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
    while (true) // Wait till module available
      ;
  }

  // connect to Wifi Network
  Serial.print("Connecting to ");
  Serial.println(ssid);
  while (WiFi.begin(ssid, password) != WL_CONNECTED) {
    Serial.print("Connecting to ");
    Serial.println(ssid);
    delay(1000);
  }
  Serial.println("WiFi connection established.");
}


void setup() {
  Serial.begin(9600);
  dht.begin();

  // Initialize ThingSpeak
  ThingSpeak.begin(client);
}

void loop() {
  float temperature = dht.readTemperature();  // Read temperature in Celsius

  if (isnan(temperature)) {
    Serial.println("Failed to read temperature from DHT sensor!");
    delay(2000);
    return;
  }

  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" °C");

  // Send data to ThingSpeak
  ThingSpeak.setField(1, temperature);
  int status = ThingSpeak.writeFields(channelID, thingSpeakApiKey);

  if (status == 200) {
    Serial.println("Data sent to ThingSpeak successfully!");
  } else {
    Serial.println("Failed to send data to ThingSpeak. Error code: " + String(status));
  }

  delay(20000);  
}
