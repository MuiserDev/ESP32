//250525B
// GPIO 2 built-in LED on ESP32
// Hosts a Wi-Fi AP defined by *ssid
// Serves a page with a "Hello, world!" label and a "Blink LED" button.
// Clicking the button sends a POST request to /blink, which flashes the LED.


#include <WiFi.h>
#include <WebServer.h>

// Access Point credentials
const char *ssid = "ESP32-AP250525B";
const char *password = "12345678";

// Create a web server on port 80
// 192.168.4.1
WebServer server(80);

// GPIO for LED
const int ledPin = 2;

// HTML content
const char *htmlPage = R"rawliteral(
<!DOCTYPE html>
<html>
  <head>
    <title>ESP32 Web Server</title>
  </head>
  <body>
<h1 style="font-size: 88px;">Hello, world!</h1>
    <form action="/blink" method="POST">
      <button type="submit" style="padding: 68px 88px; font-size: 58px;">Blink LED</button>
    </form>
  </body>
</html>
)rawliteral";

// Blink handler
void handleBlink() {
  digitalWrite(ledPin, HIGH);
  delay(200);  // LED on for 200ms
  digitalWrite(ledPin, LOW);
  server.send(200, "text/html", htmlPage);
  Serial.println("Blink button pressed");

}

// Root handler
void handleRoot() {
  server.send(200, "text/html", htmlPage);
}

void setup() {
  Serial.begin(115200);

  // Initialize LED pin
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

  // Start the Access Point
  WiFi.softAP(ssid, password);
  Serial.print("Access Point IP address: ");
  Serial.println(WiFi.softAPIP());

  // Define routes
  server.on("/", handleRoot);
  server.on("/blink", HTTP_POST, handleBlink);

  // Start the server
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
}
