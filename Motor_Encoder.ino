const int encPin1 = 2;            //Encoder output to Arduino input
const int encPin2 = 3;

const int controlPin1 = 4;        //Output to H-bridge. Drives motor.
const int controlPin2 = 5;

const int bridgeEnable = 6;       //H-Bridge Enable

int motorSpeed = 127;             //Initialize motor speed at half speed
int count = 0;                    //Initialize encoder count at 0
int temp = 0;                     //Initialize place holder variable at 0


void setup() {
  // put your setup code here, to run once:

  pinMode(encPin1, INPUT);                          //Initialize encoder pins as inputs, and motor control, H-Bridge pins as outputs
  pinMode(encPin2, INPUT);
  pinMode(controlPin1, OUTPUT);
  pinMode(controlPin2, OUTPUT);
  pinMode(bridgeEnable, OUTPUT);

  digitalWrite(bridgeEnable, LOW);                  //Initialize motor control and H-Bridge pins Low
  digitalWrite(controlPin1, LOW);
  digitalWrite(controlPin2, LOW);

  attachInterrupt(digitalPinToInterrupt(3), encoder_phaseB, CHANGE);      //Interrupt main function when there is a change (High-Low) on pin 3. Run encoder_phaseB function

  Serial.begin(9600);
}


void intro() {                                           //Intro function. Tells the user their choices.
  Serial.println("Choose from the following:");
  delay(1500);
  Serial.println("Press 1 to read back position from Encoder.");
  delay(1000);
  Serial.println("Press 2 to move the motor forward.");
  delay(1000);
  Serial.println("Press 3 to move the motor in reverse.");
  delay(1000);
  //Serial.println("Press 4 to enter motor speed.");
  delay(3000);

}

void motor_forward() {                         //Function to move our motor forward for an amount of time input by the user
  Serial.println("Enter the number of milliseconds you wish to move forward.");
  delay(2000);
  
  if (Serial.available()){                    //If the user has entered a time they wish to move for

    delay(10);
    int runTime = Serial.parseInt();          //Set the variable tunTime equal to the user's input.

    if (runTime == 0) {
      motor_forward();
    }
    else {
      Serial.println(runTime);
    digitalWrite(bridgeEnable, HIGH);         //H bridge enable on
    digitalWrite(controlPin1, HIGH);          //Pin1 high, Pin2 low. Motor will spin forward
    digitalWrite(controlPin2, LOW);
    delay(runTime);
    digitalWrite(bridgeEnable, LOW);          //Turn off enable to H bridge to conserve power. Turn off other inputs to motor.
    digitalWrite(controlPin1, LOW);
    digitalWrite(controlPin2, LOW);
    
  }
 }
}

void motor_backwards() {                      //Function to move our motor backwards for an amount of time input by the user
  delay(2000);
  if (Serial.available()){                    //If the user has entered a time they wish to move for

    delay(10);
    int runTime = Serial.parseInt();          //Set the variable tunTime equal to the user's input.

     if (runTime == 0) {                      //Solves issue where 0 was being seen as user input before the user had a chance to enter an input.
      motor_forward();                        //Run motor_forward() function again
    }
    else {
      Serial.println(runTime);
    
    
    digitalWrite(bridgeEnable, HIGH);
    digitalWrite(controlPin1, LOW);          //Pin1 low, Pin2 high. Motor will spin backwards
    digitalWrite(controlPin2, HIGH);
    delay(runTime);
    digitalWrite(bridgeEnable, LOW);         //Turn off enable to H bridge to conserve power. Turn off other inputs to motor.
    digitalWrite(controlPin1, LOW);
    digitalWrite(controlPin2, LOW);
    
  }
 }
}

void encoder_read(){                        //Function to read out encoder counts and convert them to degrees the motor has moved.
  Serial.print ("Encoder readout is : ");
  Serial.println((count*(45.00/2.00)));     //Converion function for counts to degrees.
  delay(4000);
}

void motor_speed(){
  
  if (Serial.available()){

    int motorSpeed = Serial.parseInt();                //Sets the motor speed to whatever the user input is.
  }
}


void encoder_phaseB(){
  if (digitalRead(encPin2) == HIGH){      //If phase B output from encoder is high and Phase A output from encoder is high
    if (digitalRead(encPin1) == HIGH) {
      count++;                            //Motor has moved forward. Add 1 to count.
    }
    else {
      count--;                            //If phase A output is low, motor has moved in reverse. Subtract one from count.
    }
  }

  if (count != temp){                               //Solves issue of count repeating itself in Serial Monitor. If counts is not repeated:
    Serial.print("Degrees moved: ");
    Serial.println((float(count*(45.00/2.00))));    //Prints counts to degree conversion
    temp = count;                                   //Sets temporary variable equal to new count value
  }

}


void loop() {

  intro();                                        //Runs intro function to tell user their options
  if (Serial.available()){                        //If user input available
    delay(10);
    int input = Serial.parseInt();                //Set input equal to user input
    if (input == 1) {                             //User Input equals 1
      encoder_read();                             //Run encoder_read() function
    }
    else if (input == 2) {                        //User Input equals 2
      Serial.println("How many milliseconds would you like to move the motor forward for?");
      delay(2000);
      motor_forward();                            //Run motor_forward() function
    }
    else if (input == 3) {                        //User Input equals 3
      Serial.println("How many milliseconds would you like to move the motor backwards for?");
      delay(2000);
      motor_backwards();                          //Run motor_backwards() function
    }
    else {
      Serial.println("Sorry, that was not one of the options. Please try again.");
      delay(1000);
    }
  }
}
