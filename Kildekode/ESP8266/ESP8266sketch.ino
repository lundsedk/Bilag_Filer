#include <ESP8266WiFi.h>

#define PORTN 8888;
#define SSID RPI;
#define PASSWORD standardA1;

  
WiFiServer server(PORTN);
char lastMess[255];
int count=0;

void setup() 
{
  Serial.begin(115200);
  pinMode(0,INPUT_PULLUP);  // Sætter pin til UART
  WiFi.mode(WIFI_STA);
  WiFi.begin(SSID, PASSWORD); // Forbinder til WiFi
 
  // Prøver at forbinde, blokerer indtil det er sket
  while (WiFi.status() != WL_CONNECTED) {   
    delay(1000);
    Serial.println("Trying to connect");
  }

  Serial.print("Connected to ");
  Serial.println(SSID);

  Serial.print("IP: ");
  Serial.println(WiFi.localIP());  
  Serial.print("Port:");
  Serial.println(PORTN);
  server.begin();
}



void loop() 
{
  WiFiClient client = server.available();

  while(client.connected()){      
    //Modtag
    while(client.available()>0){
      Serial.write(client.read()); 
    }

    //Send
    while(Serial.available()>0)
    {
      client.write(Serial.read());
    }
  }
  Serial.print("Disconnected");
  setup();
}