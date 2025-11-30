#include <WiFi.h>
#include <WebServer.h>
#include <HTTPClient.h>

#define MODE_SWITCH 15
#define LED 4

// WiFi credentials
const char* ssid = "Saif";
const char* password = "12345678";

// Node.js endpoint for CLIENT MODE
String serverURL = "http://10.52.17.212:5000/data";

WebServer server(80);

bool isServerMode = false;

// ------------------- SEND TO ARDUINO -------------------
void sendToArduino(String cmd) {
  Serial.println(cmd);
  server.send(200, "application/json", "{\"status\":\"OK\",\"cmd\":\"" + cmd + "\"}");
}

// ------------------- SEND TO BACKEND -------------------
void sendToBackend(String incoming) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(serverURL);
    http.addHeader("Content-Type", "application/json");

    String json = "{\"data\":\"" + incoming + "\"}";
    http.POST(json);
    http.end();
  }
}

// ------------------- CORS -------------------
void handleCORS() {
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.sendHeader("Access-Control-Allow-Methods", "GET, POST, OPTIONS");
  server.sendHeader("Access-Control-Allow-Headers", "Content-Type");
}

// ------------------- REGISTER ROUTE -------------------
void addRoute(String path, String cmd) {
  // OPTIONS
  server.on(path.c_str(), HTTP_OPTIONS, [=]() {
    handleCORS();
    server.send(200, "text/plain", "");
  });

  // GET
  server.on(path.c_str(), HTTP_GET, [=]() {
    handleCORS();
    sendToArduino(cmd);
  });
}

// ------------------- SETUP -------------------
void setup() {
  Serial.begin(115200);

  pinMode(MODE_SWITCH, INPUT_PULLUP);
  pinMode(LED, OUTPUT);

  isServerMode = (digitalRead(MODE_SWITCH) == HIGH);
  digitalWrite(LED, isServerMode ? HIGH : LOW);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) delay(200);

  Serial.println("WiFi OK");
  Serial.println(WiFi.localIP());

  if (isServerMode) {
    Serial.println("SERVER MODE ENABLED");

    // Movement
    addRoute("/api/move/forward", "FORWARD");
    addRoute("/api/move/backward", "BACKWARD");
    addRoute("/api/move/left", "LEFT");
    addRoute("/api/move/right", "RIGHT");
    addRoute("/api/move/stop", "STOP");

    // Line follow
    addRoute("/api/move/linefollow", "LINEFOLLOW");

    // Lifter
    addRoute("/api/move/lift_up", "LIFT_UP");
    addRoute("/api/move/lift_down", "LIFT_DOWN");
    addRoute("/api/move/lift_stop", "LIFT_STOP");

    // QR
    addRoute("/api/move/scan", "SCAN");
    addRoute("/api/move/scan_output", "SCAN_OUTPUT");

    // Strip patterns dynamic
    for (int i = 1; i <= 30; i++) {
      String route = "/api/move/strip_" + String(i);
      String cmd = "STRIP_" + String(i);
      addRoute(route, cmd);
    }

    server.begin();
  }
  else {
    Serial.println("CLIENT MODE ENABLED");
  }
}

// ------------------- LOOP -------------------
void loop() {
  if (isServerMode) {
    server.handleClient();
  } else {
    if (Serial.available()) {
      String incoming = Serial.readStringUntil('\n');
      incoming.trim();
      if (incoming.length() > 0) sendToBackend(incoming);
    }
  }
}
