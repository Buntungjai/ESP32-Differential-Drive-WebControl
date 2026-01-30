#include <WiFi.h>
#include <ESPAsyncWebServer.h>

const char* ap_ssid = "MyRobot_Speed_AP";
const char* ap_password = "password123";

const int enA = 14; const int in1 = 12; const int in2 = 13;
const int enB = 18; const int in3 = 19; const int in4 = 21;

AsyncWebServer server(80);

String moveStatus = "STOP";
int motorSpeed = 150; // เริ่มต้นที่โหมดกลางๆ

// เพิ่มหน้าเว็บที่มีปุ่มปรับความเร็ว
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html><head>
  <title>Robot Control Pro</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <style>
    body { text-align:center; font-family: Arial; background-color: #2c3e50; color: white; }
    .button { background-color: #27ae60; border: none; color: white; padding: 20px; 
              font-size: 20px; margin: 5px; cursor: pointer; border-radius: 12px; width: 100px; }
    .button:active { background-color: #2ecc71; }
    
    .speed-btn { background-color: #34495e; border: 2px solid #ecf0f1; width: 80px; padding: 10px; font-size: 14px; }
    .speed-btn.active { background-color: #e67e22; border-color: #d35400; }
    
    .control-area { margin-top: 20px; }
    .speed-area { margin-bottom: 20px; padding: 10px; background: #34495e; border-radius: 15px; }
  </style>
</head><body>
  <h2>Robot Controller</h2>
  
  <div class="speed-area">
    <p>Speed Mode</p>
    <button class="speed-btn" onclick="setSpeed(100, this)">SLOW</button>
    <button class="speed-btn active" onclick="setSpeed(180, this)">MID</button>
    <button class="speed-btn" onclick="setSpeed(255, this)">FAST</button>
  </div>

  <div class="control-area">
    <button class="button" onmousedown="sendCommand('forward')" onmouseup="sendCommand('stop')" ontouchstart="sendCommand('forward')" ontouchend="sendCommand('stop')">UP</button><br>
    <button class="button" onmousedown="sendCommand('left')" onmouseup="sendCommand('stop')" ontouchstart="sendCommand('left')" ontouchend="sendCommand('stop')">LEFT</button>
    <button class="button" onmousedown="sendCommand('right')" onmouseup="sendCommand('stop')" ontouchstart="sendCommand('right')" ontouchend="sendCommand('stop')">RIGHT</button><br>
    <button class="button" onmousedown="sendCommand('backward')" onmouseup="sendCommand('stop')" ontouchstart="sendCommand('backward')" ontouchend="userId('stop')">DOWN</button>
  </div>
  
  <p>Status: <span id="state">STOP</span> | Speed: <span id="speedVal">180</span></p>

  <script>
    function sendCommand(cmd) {
      document.getElementById('state').innerHTML = cmd.toUpperCase();
      fetch(`/move?dir=${cmd}`);
    }
    function setSpeed(val, btn) {
      document.getElementById('speedVal').innerHTML = val;
      fetch(`/speed?val=${val}`);
      
      // เปลี่ยนสีปุ่มที่เลือก
      let btns = document.getElementsByClassName('speed-btn');
      for(let i=0; i<btns.length; i++) btns[i].classList.remove('active');
      btn.classList.add('active');
    }
  </script>
</body></html>
)rawliteral";

void setup() {
  Serial.begin(115200);
  pinMode(enA, OUTPUT); pinMode(in1, OUTPUT); pinMode(in2, OUTPUT);
  pinMode(enB, OUTPUT); pinMode(in3, OUTPUT); pinMode(in4, OUTPUT);

  WiFi.softAP(ap_ssid, ap_password);
  Serial.println("AP Started. IP: 192.168.4.1");

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html);
  });

  server.on("/move", HTTP_GET, [](AsyncWebServerRequest *request){
    if(request->hasParam("dir")) moveStatus = request->getParam("dir")->value();
    request->send(200, "text/plain", "OK");
  });

  // เพิ่ม Endpoint รับค่าความเร็ว
  server.on("/speed", HTTP_GET, [](AsyncWebServerRequest *request){
    if(request->hasParam("val")) {
      motorSpeed = request->getParam("val")->value().toInt();
      Serial.print("New Speed: "); Serial.println(motorSpeed);
    }
    request->send(200, "text/plain", "OK");
  });

  server.begin();
  xTaskCreatePinnedToCore(dashboardTask, "DashTask", 10000, NULL, 1, NULL, 0);
}

void loop() {
  if (moveStatus == "forward") {
    moveMotors(HIGH, LOW, HIGH, LOW, motorSpeed);
  } else if (moveStatus == "backward") {
    moveMotors(LOW, HIGH, LOW, HIGH, motorSpeed);
  } else if (moveStatus == "left") {
    moveMotors(LOW, HIGH, HIGH, LOW, motorSpeed);
  } else if (moveStatus == "right") {
    moveMotors(HIGH, LOW, LOW, HIGH, motorSpeed);
  } else {
    moveMotors(LOW, LOW, LOW, LOW, 0);
  }
  delay(10);
}

void moveMotors(int a1, int a2, int b1, int b2, int spd) {
  digitalWrite(in1, a1); digitalWrite(in2, a2); analogWrite(enA, spd);
  digitalWrite(in3, b1); digitalWrite(in4, b2); analogWrite(enB, spd);
}

void dashboardTask(void * pvParameters) {
  for(;;) { vTaskDelay(100 / portTICK_PERIOD_MS); }
}
