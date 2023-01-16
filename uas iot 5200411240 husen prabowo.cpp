#include <FirebaseESP32.h>
#include <WiFi.h>
#include <ESP32Servo.h>

static const int servoPin = 4;
Servo myservo;

#define FIREBASE_HOST "https://smart-aquamakan-default-rtdb.firebaseio.com/"
#define FIREBASE_AUTH "y049ceforhAo22QDhOwTh7fqbk719pBjEXDs0Phz"
#define WIFI_SSID "Wokwi-GUEST"
#define WIFI_PASSWORD ""

#define ldr 39
#define trigPin 13
#define echoPin 27

FirebaseData firebaseData;

String path = "/Node1";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ldr,INPUT);
  myservo.attach(servoPin);
    
  initWifi();
}

void loop() {
  delay(500);

  long duration;
  float distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(500);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
    if(distance > 255){
    tutup();
      }
    else{
    buka();
    }
if (Firebase.getString(firebaseData, path +"/relayy")) { //misal database diberikan nama relayy
    if  (firebaseData.dataType() == "string") 
    {
      String RLY = firebaseData.stringData();
      if (RLY == "1") {                                                         
        Serial.println("buka ON");                         
        buka(); }
      else if (RLY == "0") {                                                  
        Serial.println("tutup OFF");
        tutup();                                                
        }
      else {Serial.println("Salah kode! isi dengan data 0/1");}
    }
  }
  Serial.println(distance);
  Firebase.setInt(firebaseData, path + "/distance", distance);
}

  
void initWifi(){
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                           
  //Set database read timeout to 1 minute (max 15 minutes)
  Firebase.setReadTimeout(firebaseData, 1000 * 60);
  //tiny, small, medium, large and unlimited.
  //Size and its write timeout e.g. tiny (1s), small (10s), medium (30s) and large (60s).
  Firebase.setwriteSizeLimit(firebaseData, "tiny");
}
int rotasi = 0;

void tutup(){
  if(rotasi <= 90){
    myservo.write(rotasi);
    delay(500);
    rotasi--;
  }
  if(rotasi <= 90 ) rotasi = 0;
}

void buka(){
  if(rotasi <= 90){
    myservo.write(rotasi);
    delay(500);
    rotasi+=4;
  }
  if(rotasi >= 0 ) rotasi = 90;
}