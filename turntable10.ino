#include <AccelStepper.h>

#include <Adafruit_NeoPixel.h>

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(1, 2, NEO_GRB + NEO_KHZ800);

#define reset_pin 3 //reset to start pin
#define pin_manual 4 //manual shoot pin

#define pin_switch 5 //start-stop button

#define photoCount 32 //default number of photos
#define pin_focus 6 //focus pin
#define pin_shoot 7 //shoot pin
#define maxSpeed 500 //max stepper speed
#define minSpeed 100 //min stepper speed
#define steperAccel 400 //acceleration of stepper motor

#define focusDelay 1200 //holding focus button (ms)
#define shootDelay 700 //holding shoot button (ms)
#define releaseDelay 500 //delay after shoot button release (ms)

#define blink_delay 200 //reset blink delay (ms)

int turns_count = 0; //step cycles count
int step_count;
int serialByte;
int pCount = photoCount;

boolean in_progress = false; //running process variable

// initialize the stepper library on pins 8 through 11:
 AccelStepper myStepper(4, 8, 9, 10, 11);

void setup() {

  // set the speed and acceleration of stepper motor
  myStepper.setAcceleration(steperAccel);

  //assign output pins to control camera
   pinMode(pin_focus, OUTPUT); 
   pinMode(pin_shoot, OUTPUT);

 //assign inpit pin for button
   pinMode(pin_switch, INPUT);
  
  //initializes the NeoPixel library.
   pixels.begin(); 

  step_count = round(2048/pCount); 
 
 Serial.begin(9600);
// Serial.setTimeout(300);
 
 Serial.println("Turntable v1.0");
 Serial.print("Number of photos: ");
 Serial.println(pCount);
}



void turn() //turn function
{

int pot_pos = analogRead(A1);  // get potentiometer value
 int stepperSpeed = map(pot_pos, 0, 1023, maxSpeed, minSpeed);
 
 myStepper.setMaxSpeed(stepperSpeed);
 myStepper.setAcceleration(stepperSpeed);

 myStepper.move(step_count);
 myStepper.runToPosition();

}

void shoot() //shoot function
{
//focus
   pixels.setPixelColor(0, pixels.Color(0,32,0)); 
   pixels.show();
   digitalWrite(pin_focus, HIGH);
   Serial.print("Focus...");
   delay(focusDelay); //holding focus button

  //shoot
   pixels.setPixelColor(0, pixels.Color(100,32,0)); 
   pixels.show();
   digitalWrite(pin_shoot, HIGH);
   Serial.print("Shoot...");
   delay(shootDelay); //holding shoot button

  //release buttons
   digitalWrite(pin_shoot, LOW);
   digitalWrite(pin_focus, LOW); 
   
   delay(releaseDelay); //delay after shoot
}




void loop()

{

if (turns_count >= pCount)
{
  in_progress = false;
  turns_count = 0;
  Serial.println("Done");
}

if (in_progress == false)
{
 pixels.setPixelColor(0, pixels.Color(32,0,32)); 
 pixels.show();

if (Serial.available() > 0) {  
        serialByte = Serial.read();
 if ((serialByte==43) && (pCount<=360)) { //"+" key is pressed 
     pCount++;
      
      Serial.print("Number of photos: ");
      Serial.println(pCount);
      step_count = round(2048/pCount);
 
 }
 if ((serialByte==45) && (pCount>=3)) { //"-" key is pressed
     pCount--;
      Serial.print("Number of photos: ");
      Serial.println(pCount);
      step_count = round(2048/pCount);
 }
      }

 
}


if ((in_progress == false) && (digitalRead(pin_manual) == LOW) )
 //waiting button being pressed to start cycle
  in_progress = true;


if ((digitalRead(pin_switch) == LOW) && (turns_count<pCount) && (in_progress == true))
 //auto shoot mode
  {
    Serial.print("Photo # ");
    Serial.print(turns_count+1);
    Serial.print(" (");
    Serial.print(pCount-turns_count-1);
    Serial.print(" left)");
    shoot();
  
   pixels.setPixelColor(0, pixels.Color(0,0,32)); 
   pixels.show();
  Serial.println("Turning...");
  turn();
  turns_count++;

  }

  
if ((in_progress == true) && (digitalRead(pin_switch) == HIGH))
  //standby mode
  {
    pixels.setPixelColor(0, pixels.Color(32,0,0)); 
    pixels.show();

    //manual shoot if button pressed
    if (digitalRead(pin_manual) == LOW)
    
      shoot();
      
    if (digitalRead(reset_pin) == LOW) //reset to start
    {
     turns_count=0;
     in_progress = false;
     Serial.println("Reset...");
    
    for (int cnt=0; cnt<=4; cnt++) {
     pixels.setPixelColor(0, pixels.Color(0,0,0)); 
     pixels.show();
     delay(blink_delay);
     pixels.setPixelColor(0, pixels.Color(32,0,0)); 
     pixels.show();
     delay(blink_delay);
     }
     Serial.print("Number of photos: ");
     Serial.println(pCount);
    }
    }


  
}

