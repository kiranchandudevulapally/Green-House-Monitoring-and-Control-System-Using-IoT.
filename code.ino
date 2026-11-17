#include <SoftwareSerial.h>//iot
#include <LiquidCrystal.h>//lcd
LiquidCrystal lcd(13,12,11,10,9,8);//lcd pins
int soil = A0;
int tem = A1;
int ldr =A2;
int light=7;
int motor=6;
char res[130];
void upload1(unsigned char *chr,unsigned char *chr1,unsigned char *chr2,unsigned char *chr3);
void serialFlush(){
  while(Serial.available() > 0) {
    char t = Serial.read();
  }
} 
const char* ssid = "greenhouse";
const char* password = "greenhouse";
int T;
int tt;
void setup() {
  // put your setup code here, to run once:
   pinMode(tem,INPUT); 
   pinMode(soil,INPUT);
   pinMode(ldr,INPUT);
    pinMode(light,OUTPUT); 
pinMode(motor,OUTPUT);
     digitalWrite(light,LOW);
       digitalWrite(motor,LOW);
  Serial.begin(9600);
  lcd.begin(16,2);
  lcd.clear();lcd.setCursor(0, 0);lcd.print("Green house");   
  lcd.setCursor(0, 0);lcd.print("monitoring");  
  Serial.println("Green house monitoring system");
  delay(1000);


  Serial.println("ATE0");
  Serial.println("ATE0"); delay(1000);
  Serial.println("AT");
  Serial.println("AT"); delay(1000);

  lcd.clear();lcd.setCursor(0, 0);lcd.print("CONNECTING");  
 delay(1000);
  Serial.println("AT+CWMODE=1"); delay(1000);
  Serial.println("AT+CWMODE=1"); delay(1000);
  serialFlush(); delay(1000);
  Serial.print("AT+CWJAP=\""); delay(1000);
  Serial.print("AT+CWJAP=\""); delay(1000);
  Serial.print(ssid); delay(1000);
  Serial.print(ssid); delay(1000);
  Serial.print("\",\""); delay(1000);
  Serial.print("\",\"");
  Serial.print(password); delay(1000);
  Serial.print(password); delay(1000);
  Serial.println("\"");
  Serial.println("\""); 
  Serial.println("AT+CIPMUX=1"); delay(1000);
  Serial.println("AT+CIPMUX=1");
  delay(1000);
 
lcd.clear();lcd.setCursor(0, 0);lcd.print("WAITING"); 
delay(500);
lcd.clear();lcd.setCursor(0, 0);lcd.print("Connected"); 
    delay(1000);

}

void loop() {

 int sd =analogRead(soil);
int td =analogRead(tem);
int ld =analogRead(ldr);
  lcd.setCursor(0, 0);lcd.print("H:");lcd.print(sd);lcd.print("    ");
  lcd.setCursor(7, 0);lcd.print("T:");lcd.print(td);lcd.print("    ");
  lcd.setCursor(8, 1);lcd.print("L:");lcd.print(ld);lcd.print("     ");delay(500);


if(sd > 500 )
{
  lcd.clear();
  lcd.setCursor(0, 0);lcd.print("LESS WATER M-ON");
  delay(1000);
  digitalWrite(motor,HIGH);delay(1000);
    upload1(td,sd,ld);
  delay(1000);
  }
 
  if(td > 500 )
{
  lcd.clear();
  lcd.setCursor(0, 0);lcd.print("high Temperature ");
 
  delay(1000);
    upload1(td,sd,ld);
  delay(1000);
  }

   
 
if(ld > 500 )
{
  lcd.clear();
  lcd.setCursor(0, 0);lcd.print("HIgh Intensity");
  digitalWrite(light,LOW);
  delay(500);
    upload1(td,sd,ld);
  delay(2000);
  }
  else
        {
          digitalWrite(light,HIGH);
           digitalWrite(motor,LOW);
       delay(1000);
          
          }
delay(1000);
      
}//loop

char buff[200];
char bf2[100];
void upload1(unsigned char *chr,unsigned char *chr1,unsigned char *chr2)
{
  delay(2000);
  lcd.clear();lcd.setCursor(0, 1);lcd.print("UPLOADING");
  serialFlush();
Serial.println("AT+CIPSTART=4,\"TCP\",\"api.thingspeak.com\",80");
//   Serial.println("AT+CIPSTART=4,\"TCP\",\"embeddedspot.top\",80");
      delay(2000);
      sprintf(buff,"GET https://api.thingspeak.com/update?api_key=RG5QR6MSVHVALQJF&field1=%u&field2=%u&field3=%u&field4=%u&\r\n\r\n",chr,chr1,chr2);
      //sprintf(buff,"GET http://embeddedspot.top/iot/storedata.php?name=sensors010&s1=%u&s2=%u&s3=%u\r\n\r\n",chr,chr1,chr2);
      serialFlush();
      sprintf(bf2,"AT+CIPSEND=4,%u",strlen(buff));
      Serial.println(bf2);
      
         delay(5000);
          
          
          serialFlush();
          Serial.print(buff);
          Serial.print(buff);
              delay(2000);
              
              Serial.println("AT+CIPCLOSE");
              Serial.println("AT+CIPCLOSE");
              lcd.setCursor(0, 1);lcd.print("UPLOADDED");   lcd.clear();

}
    
