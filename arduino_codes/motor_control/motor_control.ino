// Hbridge_L293D
// Two bridges, one for each side of the robot
// Running on Arduino nano

const int motorEN = 12;
const int l_motor2= 10;
const int l_motor7= 11;
const int r_motor2= 9;
const int r_motor7= 6; 

int r_motor2_val = 50;
int r_motor7_val = 0;
int l_motor2_val = 50;
int l_motor7_val = 0;

bool turn_left = false;
bool turn_right= false;

int max_val = 255;

void setup() {
  Serial.begin(9600);
  //  Set pin modes
  pinMode(motorEN,OUTPUT);
  digitalWrite(motorEN,HIGH);
  write_speeds(); 
}
char instruct = 'n';
char direct   = 'n';
int val;
float cval;
void loop() {
  // put your main code here, to run repeatedly:

  if (Serial.available() > 0){
    Serial.println(Serial.available());
    instruct = Serial.read();
    Serial.println(instruct);
    switch(instruct) {
      case 'l' :
        val = Serial.parseInt();
        set_speed(val);
        write_speeds();
        break;
      case 'z' :
        Serial.println(Serial.available());
        cval = Serial.parseFloat();
        set_curve_l(cval);
        write_speeds();
        break;
      case 'x' :
        cval = Serial.parseFloat();
        set_curve_r(cval);
        write_speeds();
        break;
      default :
        break;
    }
    serialFlush();
  }
  
}

void serialFlush(){
  while (Serial.available() > 0) {
    Serial.read();
  }
}
void set_curve_l(float cval){
  if (cval < -1){
    cval = -1;
  }
  if (cval > 1){
    cval = 1;
  }
  int new_val = cval * val;
  
  if (val > 0){
    if (cval > 0){
      r_motor2_val = new_val;
      r_motor7_val = 0;
      l_motor2_val = val;
      l_motor7_val = 0;
    }
    if (cval < 0) {
      r_motor7_val = abs(new_val);
      r_motor2_val = 0;
      l_motor2_val = val;
      l_motor7_val = 0;
    }
  }
  if (cval == 0){
    r_motor7_val = 0;
    r_motor2_val = 0;
  }
  if (val < 0){
    if (cval > 0){
      r_motor7_val = abs(new_val);
      r_motor2_val = 0;
      l_motor2_val = 0;
      l_motor7_val = -1*val;
    }
    if (cval < 0){
      r_motor2_val = new_val;
      r_motor7_val = 0;
      l_motor2_val = 0;
      l_motor7_val = -1*val;
    }
  }
  turn_left = true;
}

void set_curve_r(float cval){
  if (cval < -1){
    cval = -1;
  }
  if (cval > 1){
    cval = 1;
  }
  int new_val = cval * val;
  
  if (val > 0){
    if (cval > 0){
      l_motor2_val = new_val;
      l_motor7_val = 0;
      r_motor2_val = val;
      r_motor7_val = 0;
    }
    if (cval < 0) {
      l_motor7_val = abs(new_val);
      l_motor2_val = 0;
      r_motor2_val = val;
      r_motor7_val = 0;
    }
  }
  if (cval == 0){
    l_motor7_val = 0;
    l_motor2_val = 0;
  }
  if (val < 0){
    if (cval > 0){
      l_motor7_val = abs(new_val);
      l_motor2_val = 0;
      r_motor2_val = 0;
      r_motor7_val = -1 * val;
    }
    if (cval < 0){
      l_motor2_val = new_val;
      l_motor7_val = 0;
      r_motor2_val = 0;
      r_motor7_val = -1 * val;
    }
  }
  turn_right = true;
}

void set_speed(int val){
  if (val > max_val){
    val = max_val;
  }
  if (val < -max_val){
    val = -max_val;
  }
  if (val > 0){
    r_motor2_val = val;
    l_motor2_val = val;
    r_motor7_val = 0;
    l_motor7_val = 0;
  }
  if (val < 0){
    r_motor7_val = -1 * val;
    l_motor7_val = -1 * val;
    r_motor2_val = 0;
    l_motor2_val = 0;
  }
  if (val == 0){
    r_motor2_val = 0;
    l_motor2_val = 0;
    r_motor7_val = 0;
    l_motor7_val = 0;
  }
}

void write_speeds(){
  analogWrite(r_motor2,(r_motor2_val));
  Serial.println(r_motor2_val);
  analogWrite(r_motor7,(r_motor7_val));
  Serial.println(r_motor7_val);
  analogWrite(l_motor2,(l_motor2_val));
  Serial.println(l_motor2_val);
  analogWrite(l_motor7,(l_motor7_val));
  Serial.println(l_motor7_val);
  Serial.println("Speed set ^^");
}
