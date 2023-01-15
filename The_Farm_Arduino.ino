#include<SoftwareSerial.h>
#include <Servo.h>
Servo myservo; 
 
#define led_with 2
#define led_blue 3
#define fan_heat 4
#define fan_frez 5
#define heat 6
#define street_lamp 7
#define food_motor 8
#define water_pump 9

int pump_swich = A0; 
int pump_swich_Value = 0;

int solar_pin = A1;
int solar_value = 0 ;

bool send_on = true ;
bool send_off = true ;

//Bluetooth serial 
const int txpin = 13;       
const int rxpin = 12;


SoftwareSerial blue(txpin, rxpin);
char Command = 'o'  ;


void setup() {

  myservo.attach(10); 
   blue.begin(9600);
   // Serial.begin(115200); 
  blue.setTimeout(10);
  digitalWrite(led_with,HIGH);
digitalWrite(led_blue,HIGH);
digitalWrite(fan_heat,HIGH);
digitalWrite(fan_frez,HIGH);
digitalWrite(heat,HIGH);
digitalWrite(street_lamp,HIGH);
digitalWrite(food_motor,HIGH);
digitalWrite(water_pump,HIGH);
analogWrite(pump_swich,LOW);
analogWrite(solar_pin,LOW);

pinMode(solar_pin,INPUT);
pinMode(pump_swich,INPUT);
  pinMode(led_with,OUTPUT); 
  pinMode(led_blue,OUTPUT); 
  pinMode(fan_heat,OUTPUT); 
 pinMode(fan_frez,OUTPUT); 
 pinMode(heat,OUTPUT); 
 pinMode(street_lamp,OUTPUT); 
 pinMode(food_motor,OUTPUT); 
 pinMode(water_pump,OUTPUT); 

 
}

void loop() {

int analogValue1 = analogRead(A5);
 int analogValue2 = analogRead(A4);
 int analogValue3 = analogRead(A3);
 
 Serial.println(analogValue1);
 Serial.println(analogValue2);
 Serial.println(analogValue3);
  Serial.println("   ");

  Serial.println(solar_value);
  Serial.println(pump_swich_Value);

  Serial.println("   ");
 

 if (analogValue1 > 800) {
  for(int i = 45 ; i <= 90 ; i++){
 myservo.write(i); 
 delay(100);
  }
 delay(100); 
  }

 else if (analogValue3 > 800) {
     for(int i = 45 ; i >= 0 ; i--){
 myservo.write(i); 
 delay(100);
  }
 delay(100); 
  }
  else{
     myservo.write(45); 
     delay(100); 
    }
  
    pump_swich_Value = analogRead(pump_swich);
    solar_value = analogRead(solar_pin);

   if(pump_swich_Value <1000){
        digitalWrite(water_pump,HIGH);
        blue.println(pump_swich_Value);       
            }


    if(solar_value >700 && send_on == true){
        delay(1000);
        blue.println("1الطاقه الشمسيه تعمل يتم شحن البطاريات"); 
        send_on = false ; 
        send_off = true ;        
      }
    if(solar_value <700 && send_off == true){
        delay(1000);
        blue.println("0الواح الطاقة الشمسية لا تشحن");
        send_off = false ; 
        send_on = true ; 
        }


    if (blue.available()) {
       Command = blue.read();

     // LED WHITE CONTROL  
     if(Command == 'W'){
        digitalWrite(led_with,LOW);
        blue.println("تم تشغيل المصابيح البيضاء");       
            }
      if(Command == 'w'){
         digitalWrite(led_with,HIGH);
         blue.println("تم ايقاف المصابيح البيضاء"); 
            } //END

      // LED blue CONTROL  
     if(Command == 'B'){
        digitalWrite(led_blue,LOW);
        blue.println("تم تشغيل المصابيح الزرقاء");       
            }
      if(Command == 'b'){
         digitalWrite(led_blue,HIGH);
         blue.println("تم أيقاف المصابيح الزرقاء"); 
            } //END


            // fan_heat CONTROL  
     if(Command == 'H'){
        digitalWrite(fan_heat,LOW);
        blue.println("تم تشغيل مراوح التسخين راقب ارتفاع الحرارة");       
            }
      if(Command == 'h'){
         digitalWrite(fan_heat,HIGH);
         blue.println("تم ايقاف مراوح التسخين");     
            } //END


                // fan_frez CONTROL  
     if(Command == 'C'){
        digitalWrite(fan_frez,LOW);
        blue.println("تم تشغيل مراوح التبريد راقب انخفاض الحرارة");       
            }
      if(Command == 'c'){
         digitalWrite(fan_frez,HIGH);
         blue.println("تم ايقاف مراوح التبريد");     
            } //END



                       // street_lamp CONTROL  
     if(Command == 'L'){
        digitalWrite(street_lamp,LOW);
        blue.println("تم تشغيل مصابيح الشارع");       
            }
      if(Command == 'l'){
         digitalWrite(street_lamp,HIGH);
         blue.println("تم ايقاف مصابيح الشارع");     
            } //END
            
    
                      
              
            
     
            
              // water_pump CONTROL  
     if(pump_swich_Value > 200 && Command == 'P'){
        digitalWrite(water_pump,LOW);
        blue.println("تم تشغيل مواتير احواض الشرب سيتم ابقافها تلقائيا عند الأمتلاء");       
            }

          
    

                       // motor food CONTROL  
     if(Command == 'F'){
        digitalWrite(food_motor,LOW);
        blue.println("تم تقديم جرعة الغذاء الخزانات ممتلئة");   
        delay(500);    
        digitalWrite(food_motor,HIGH);
            }
            //END
            





            

            
    }

}
