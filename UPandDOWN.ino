//Webserver_nodemcu_IOT_keybd_01


#include <ESP8266WebServer.h>
 #include <ESP8266WiFi.h>
 #include <Servo.h>

 const char* ssid = "-";//자신의 스마트폰의 ID 입력
 const char* password = "-";//자신의 스마트 폰의 비밀번호 입력

 WiFiServer server(80);
 Servo myServo;
 Servo myServo1;
 void setup() {
   Serial.begin(115200);
   delay(10);

   // Set WiFi to station mode and disconnect from an AP if it was previously connected
   WiFi.mode(WIFI_STA);
   WiFi.disconnect();
   delay(100);

   Serial.println("Setup done");

   // Connect to WiFi network
   Serial.println();
   Serial.println();
   Serial.print("Connecting to ");
   Serial.println(ssid);

   WiFi.begin(ssid, password);

   while (WiFi.status() != WL_CONNECTED) {
     delay(500);
     Serial.print(".");
   }
   Serial.println("");
   Serial.println("WiFi connected");

   // Start the server
   server.begin();
   Serial.println("Server started");

   // Print the IP address
   Serial.print("Use this URL to connect: ");
   Serial.print("http://");
   Serial.print(WiFi.localIP());
   Serial.println("/");

 }

 void loop() {
   // Check if a client has connected
   WiFiClient client = server.available();
   if (!client) {
     return;
   }

   // Wait until the client sends some data
   Serial.println("new client");
   while(!client.available()){
     delay(1);
   }


   // Read the first line of the request
   String request = client.readStringUntil('\r');
   Serial.println(request);
  
   // 14: 정식 request, 20: ㅣLED on request  21: LED OFF request 아니면 건너뛸 것.
 if(request.length() == 14 || request.length() == 19 || request.length() == 20 || request.length() == 21) {
   client.flush();

   // Match the request
 
 // Key board input processing
   if (request.indexOf("/KEY=1") != -1)  {
     myServo.attach(D5);
     myServo.write(80);
     delay(500);
     myServo.write(120);
   }
      if (request.indexOf("/KEY=2") != -1)  {
     myServo1.attach(D6);
     myServo1.write(140);
     delay(500);
     myServo1.write(180);
   }
 // Set ledPin according to the request
 //digitalWrite(ledPin, value);

   // Return the response
   client.println("HTTP/1.1 200 OK");
   client.println("Content-Type: text/html");
   client.println(""); //  do not forget this one
   client.println("<!DOCTYPE HTML>");
   client.println("<html>");
   client.println("<head>");
//배경 색 문자 색 사이즈 HTML CSS 설정  
   client.println("<style>");
   client.println("body {");
   client.println("background-color: lightblue;");
   client.println("}");
   client.println("p {");
   client.println("color:red;");
   client.println("font-size:250%;");
   client.println("}");
  
//버튼 HTML CSS 설정  
client.println(".button {");
    client.println("background-color: white;");
    client.println("border: solid;");
    client.println("color: black;");
    client.println("padding: 15px 32px;");
    client.println("text-align: center;");
    client.println("text-decoration: none;");
    client.println("display: inline-block;");
    client.println("font-size: 50px;");
    client.println("margin: 2px 2px;");
    client.println("cursor: pointer;");
client.println("}");
   
   client.println("</style>");
   client.println("<title>Page Title</title>");
   client.println("<h1> Press the Button </h1>"); 
   client.println("</head>");
   client.println("<body>");
   client.println("<p>");
  
// Key board input
   client.println("<br>");
   client.println("<a href=\"/KEY=1\"\" class='button'> UP </button></a>");
   client.println("<br>");
   client.println("<a href=\"/KEY=2\"\" class='button'> DOWN </button></a>");
   client.println("</p>");
   client.println("</body>");
   client.println("</html>");

   delay(1);
   Serial.println("Client disonnected");
   Serial.println("");
 }// if문 괄호 닫기
 }//프로그램 끝

// references
// https://blog.daum.net/ejleep1/345
// https://blog.daum.net/rockjjy99/2629
