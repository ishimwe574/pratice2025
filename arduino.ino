#include <HTTPClient.h>
#include <ArduinoJson.h>
#include<ESP8266WiFi.h>

const char* servername = "http://192.168.137.1/php.php";
const char* ssid = "beni";
const char* pass = "alice2006";

// Ultrasonic pins
#define trigpin D1
#define echopin D2

// LED pins
#define greenpin D5
#define redpin D6
#define bluepin D7

void setup()
{
  Serial.begin(115200);

  pinMode(trigpin, OUTPUT);
  pinMode(echopin, INPUT);

  pinMode(greenpin, OUTPUT);
  pinMode(redpin, OUTPUT);
  pinMode(bluepin, OUTPUT);

  WiFi.begin(ssid, pass);

  Serial.print("Connecting");

  while(WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("Connected to WiFi");

  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}

void loop()
{
  // Ultrasonic trigger
  digitalWrite(trigpin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigpin, HIGH);
  delayMicroseconds(10);

  digitalWrite(trigpin, LOW);

  // Read echo
  long duration = pulseIn(echopin, HIGH);

  // Calculate distance
  float distance = duration * 0.034 / 2;

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // WiFi check
  if(WiFi.status() == WL_CONNECTED)
  {
    HTTPClient Alice;

    Alice.begin(servername);

    Alice.addHeader("Content-Type", "application/json");

    // Create JSON
    StaticJsonDocument<200> ishimwe;

    ishimwe["device_name"] = "ESP8266";
    ishimwe["distance"] = distance;

    // Convert JSON to String
    String jsonDoc;

    serializeJson(ishimwe, jsonDoc);

    // Send POST request
    int responsecode = Alice.POST(jsonDoc);

    Serial.print("Response Code: ");
    Serial.println(responsecode);

    if(responsecode == 200)
    {
      Serial.println("Data inserted successfully");
    }
    else
    {
      Serial.println("Server failed");
    }

    Alice.end();
  }
  else
  {
    Serial.println("Failed to connect to WiFi");
  }

  // LED Logic
  if(distance <= 20)
  {
    digitalWrite(greenpin, HIGH);
    digitalWrite(redpin, LOW);
    digitalWrite(bluepin, LOW);

    Serial.println("Very Near");

    delay(1000);
  }
  else if(distance <= 40)
  {
    digitalWrite(greenpin, LOW);
    digitalWrite(redpin, HIGH);
    digitalWrite(bluepin, LOW);

    Serial.println("Near");

    delay(1000);
  }
  else if(distance <= 60)
  {
    digitalWrite(greenpin, LOW);
    digitalWrite(redpin, LOW);
    digitalWrite(bluepin, HIGH);

    Serial.println("Far");

    delay(1000);
  }
  else
  {
    digitalWrite(greenpin, LOW);
    digitalWrite(redpin, LOW);
    digitalWrite(bluepin, LOW);

    Serial.println("Safe on gate");
  }

  delay(500);
}
 
