
#include <WiFi.h>
#include <WebServer.h>
#include <HTTPClient.h>

#define MODE_SWITCH 15  // switch pin
#define LED 4           // for indication

// WiFi credentials
const char* ssid = "Saif";
const char* password = "12345678";

// Node server endpoint (used in CLIENT mode)
String serverURL = "http://10.126.186.212:5000/data";

// Web server instance for SERVER MODE
WebServer server(80);

bool isServerMode = false;

// ------------ SERVER MODE: Send commands to Arduino ---------------
void sendToArduino(String cmd) {

  Serial.println(cmd);
  server.send(200, "application/json", "{\"status\":\"OK\",\"cmd\":\"" + cmd + "\"}");
}

// ------------ CLIENT MODE: Send received serial to Node.js --------
void sendToBackend(String incoming) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(serverURL);
    http.addHeader("Content-Type", "application/json");

    String json = "{\"data\":\"" + incoming + "\"}";
    int code = http.POST(json);

    Serial.print("POST -> ");
    Serial.println(json);
    Serial.print("Response: ");
    Serial.println(code);

    http.end();
  }
}

// CORS middleware for ESP32 WebServer
void handleCORS() {
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.sendHeader("Access-Control-Allow-Methods", "GET, POST, OPTIONS");
  server.sendHeader("Access-Control-Allow-Headers", "Content-Type");
}


// ------------ Setup ----------------
void setup() {
  Serial.begin(9600);
  pinMode(MODE_SWITCH, INPUT_PULLUP);
  pinMode(LED, OUTPUT);

  // Read mode only once at startup
  isServerMode = (digitalRead(MODE_SWITCH) == HIGH);

  // LED INDICATION
  digitalWrite(LED, isServerMode ? HIGH : LOW);

  // Connect WiFi
  WiFi.begin(ssid, password);
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) { delay(300); Serial.print("."); }

  Serial.println("\nWiFi Connected");
  Serial.print("ESP IP: ");
  Serial.println(WiFi.localIP());

  // Setup API routes ONLY in SERVER MODE
 if (isServerMode) {
    Serial.println("Mode: SERVER MODE");

    // Handle OPTIONS preflight for all routes
    server.on("/api/move/forward", HTTP_OPTIONS, []() {
        handleCORS();
        server.send(200, "text/plain", "");
    });
    server.on("/api/move/backward", HTTP_OPTIONS, []() {
        handleCORS();
        server.send(200, "text/plain", "");
    });
    server.on("/api/move/left", HTTP_OPTIONS, []() {
        handleCORS();
        server.send(200, "text/plain", "");
    });
    server.on("/api/move/right", HTTP_OPTIONS, []() {
        handleCORS();
        server.send(200, "text/plain", "");
    });
    server.on("/api/move/stop", HTTP_OPTIONS, []() {
        handleCORS();
        server.send(200, "text/plain", "");
    });
    server.on("/api/move/linefollow", HTTP_OPTIONS, []() {
        handleCORS();
        server.send(200, "text/plain", "");
    });

    // Normal GET routes with CORS
    server.on("/api/move/forward", HTTP_GET, []() {
        handleCORS();
        sendToArduino("FORWARD");
    });
    server.on("/api/move/backward", HTTP_GET, []() {
        handleCORS();
        sendToArduino("BACKWARD");
    });
    server.on("/api/move/left", HTTP_GET, []() {
        handleCORS();
        sendToArduino("LEFT");
    });
    server.on("/api/move/right", HTTP_GET, []() {
        handleCORS();
        sendToArduino("RIGHT");
    });
    server.on("/api/move/stop", HTTP_GET, []() {
        handleCORS();
        sendToArduino("STOP");
    });
    server.on("/api/move/linefollow", HTTP_GET, []() {
        handleCORS();
        sendToArduino("LineFollow");
    });

    server.begin();
}

  else {
    Serial.println("Mode: CLIENT MODE");
  }
}

// ------------ LOOP ----------------
void loop() {
  
  if (isServerMode) {
    // SERVER MODE → Handle frontend requests
    server.handleClient();
  } 
  else {
    // CLIENT MODE → Read Arduino serial & send to Node.js
    if (Serial.available()) {
      String incoming = Serial.readStringUntil('\n');
      incoming.trim();
      if (incoming.length() > 0) {
        sendToBackend(incoming);
      }
    }
  }
}
