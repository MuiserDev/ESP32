#include <WiFi.h>
#include <WebServer.h>

// Access Point credentials
const char *ssid = "Frank250525A";
const char *password = "12345678";

// Create a web server on port 80
// default IP: 192.168.4.1
WebServer server(80);

// HTML content to serve
const char *htmlPage = R"rawliteral(
<!DOCTYPE html>
<html>
  <head>
    <title>ESP32 Web Server</title>
  </head>
  <body>
    <h1>Hello, world!</h1>
  </body>
</html>
)rawliteral";

void handleRoot() {
  server.send(200, "text/html", htmlPage);
}

void setup() {
  Serial.begin(57600);

  // Start the Access Point
  WiFi.softAP(ssid, password);
  Serial.println();
  Serial.print("Access Point IP address: ");
  Serial.println(WiFi.softAPIP());

  // Define routes
  server.on("/", handleRoot);

  // Start the server
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
}
