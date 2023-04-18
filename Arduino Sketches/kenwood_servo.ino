//---------------------

#include <Servo.h>



Servo servo;



int serv = 3;

float minson = 1.5; //minutes, total time on + off
int offtime = 3; //seconds, off time
int ontime = 15;  //seconds, on time
int angle = 180;  //max 180
                  //90     ~  9'500 rpm
                  //180    ~ 17'000 rpm
int overshoot = 0; // To force the start at low speeds

 

float start;
int gap;
int flip = angle;
bool called = false;





int tic(int t) {

  return round((millis()-t)/1000.);

  }

 

 

int routine(int l) {

 

  start = millis();

  servo.write(flip+overshoot);
  delay(800);
  servo.write(flip);
  
  Serial.println("- - -");
  Serial.print("Tic: ");
  Serial.println("0");

  Serial.print("Angle: ");
  Serial.println(flip);

  Serial.print("Status: ");
  Serial.println("On");

  gap = ontime;
  delay(1010);
 

  while ((float(tic(start))/(60.*l)) < 1) {

    if (tic(start)%gap == 0) {

      Serial.println("- - -");
      Serial.print("Tic: ");
      Serial.print(tic(start));
      Serial.println(" sec");

      if (flip == 0) {

          flip = angle;

        }

      else if (flip == angle) {

          flip = 0;

        }

      servo.write(flip+overshoot);
      delay(800);
      servo.write(flip);

      Serial.print("Angle: ");
      Serial.println(flip);

      if (gap == ontime) {

        Serial.print("Status: ");
        Serial.println("Off");
        
        gap = offtime + ontime;
        
        delay(1010);
        
        }

      else if (gap == offtime + ontime) {

        Serial.print("Status: ");
        Serial.println("On");
        
        gap = ontime;

        delay(1010);
        
        }

      }

    }

  servo.write(0);

  }





void setup() {

  Serial.begin(9600);

  //pinMode(led2, OUTPUT);

  servo.attach(serv);

  }



void loop() {
  
  servo.write(0);
  
  delay(3000);
  Serial.println("_________");
  Serial.println("Connected");
  Serial.print(  "Total ontime: ");
  Serial.println(ceil((minson*60/(ontime + offtime))*ontime/60));
  delay(3000);

  routine(minson);

  Serial.println("- - -");
  Serial.println("Done");

  while (true) {}

  }



//-------------------
