#include <ESP8266WiFi.h>
#include <String.h>

int count = 1;
const int port = 8080;
const char* ssid = "SSID";
const char* password = "PASSWORD";

WiFiServer dataServer(port);

void setup() 
{
    Serial.begin(9600);
    Serial.println();

    Serial.print("Connecting");
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print(">");
        delay(500);
    }
    Serial.print("Connected to ");
    Serial.print(ssid);
    Serial.println();
    Serial.println();
    dataServer.begin();
    Serial.print("Server started on port ");
    Serial.print(port);
    Serial.print(" at ");
    Serial.print(WiFi.localIP());
}

String prepareHtmlPage()
    {
        String htmlPage =
        String("HTTP/1.1 200 OK\r\n") +
            "Content-Type: text/html\r\n" +
            "Connection: close\r\n" +  // the connection will be closed after completion of the response
            "Refresh: 1\r\n" +  // refresh the page automatically every 5 sec
            "\r\n" +
            "<!DOCTYPE HTML>" +
            "<html>" +
            "Count:  " + count +
            "</html>" +
            "\r\n";
            return htmlPage;
    }

void loop()
{
  WiFiClient client = dataServer.available();
  // wait for a client (web browser) to connect
  if (client)
  {
    Serial.println("\n[Client connected]");
    while (client.connected())
    {
      // read line by line what the client (web browser) is requesting
      if (client.available())
      {
        String line = client.readStringUntil('\r');
        Serial.print(line);
        // wait for end of client's request, that is marked with an empty line
        if (line.length() == 1 && line[0] == '\n')
        {
          client.println(prepareHtmlPage());
          break;
        }
      }
    }
    delay(1); // give the web browser time to receive the data
    count++;
    // close the connection:
    client.stop();
    Serial.println("[Client disonnected]");
  }
}
