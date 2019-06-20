
int Echo = A5;
int Trig = A4;

#define enA  9
#define enB  3
#define in1  8 //f
#define in2  7 //b
#define in3  5 //f
#define in4  4
#define carSpeed 150

int Rdist = 0, Ldist = 0, Middist = 0;
int data;

void forward()
{
  analogWrite(enA, carSpeed);
  analogWrite(enB, carSpeed);
  
  digitalWrite(in1, LOW);
  digitalWrite(in3, LOW);

  digitalWrite(in2, HIGH);
  digitalWrite(in4, HIGH);

  Serial.print("Forward");
}

void back()
{
  analogWrite(enA, carSpeed);
  analogWrite(enB, carSpeed);
  
  digitalWrite(in1, HIGH);
  digitalWrite(in3, HIGH);

  digitalWrite(in2, LOW);
  digitalWrite(in4, LOW);

  Serial.print("BACK");
}

void left()
{
  analogWrite(enA, carSpeed);
  analogWrite(enB, carSpeed);
  
  digitalWrite(in1, HIGH);
  digitalWrite(in3, LOW);

  digitalWrite(in2, LOW);
  digitalWrite(in4, HIGH);

  Serial.print("LEFT");
}

void right()
{
  analogWrite(enA, carSpeed);
  analogWrite(enB, carSpeed);
  
  digitalWrite(in1, LOW);
  digitalWrite(in3, HIGH);

  digitalWrite(in2, HIGH);
  digitalWrite(in4, LOW);

  Serial.print("Right");
}

void stop()
{
  analogWrite(enA, LOW);
  analogWrite(enB, LOW);
  
  digitalWrite(in1, LOW);
  digitalWrite(in3, LOW);

  digitalWrite(in2, LOW);
  digitalWrite(in4, LOW);

  Serial.print("STOP");
}


int Dist_test()
{
  digitalWrite(Trig, LOW);
  delayMicroseconds(2);
  digitalWrite(Trig, HIGH);
  delayMicroseconds(20);
  digitalWrite(Trig, LOW);
  float Fdistance = pulseIn(Echo, HIGH);
  Fdistance = Fdistance /58;
  return (int)Fdistance;
}

void DistSens()
{
  Middist = Dist_test();

  if(Middist <= 20)
  {
    stop();
    
    delay(500);
    Rdist = Dist_test();

    delay(500);
    Ldist = Dist_test();

    delay(500);
    if(Rdist > Ldist)
    {
      right();
      delay(360);
    }
    else if(Rdist < Ldist)
    {
      left();
      delay(360);
    }
    else if((Rdist <= 20) || (Ldist <= 20))
    {
      back();
      delay(180);
    }
    else
    {
      forward();
    }
    }
    else 
    {
      forward();
    }
}

void setup()
{
  Serial.begin (9600);
  pinMode(Echo, INPUT);
  pinMode(Trig, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  stop();
  
}

void loop()
{
  data = Serial.read();
  Serial.println(data);

  if(data == 49)
  {
    back();
  }
  else if(data == 50)
  {
    forward();
  }
  else if(data == 51)
  {
    left();
  }
  else if(data == 52)
  {
    right();
  }
  else if(data ==53)
  {
    stop();
  }
  else if(data == 54)
  {
    DistSens();
  }
}
