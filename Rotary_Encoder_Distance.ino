#include <LiquidCrystal.h>

const int rs=12, en=11, D4=5, D5=4, D6=3, D7=2;
LiquidCrystal lcd(rs, en, D4, D5, D6, D7);

int pinA=6;
int pinB=7;
int buttonPin=8;
int c=0;
int flag=0;
int k=0;
int lastStateA;
int currentStateA;
int btnState;
int dt=10;
double Length;
double Width;
double Perimeter;
double R=3.7;//Radius of Wheel i used.

void setup()
{
  pinMode(pinA,INPUT);
  pinMode(pinB,INPUT);
  pinMode(buttonPin,INPUT);
  Serial.begin(9600);
  lcd.begin(16,2);
  
  lastStateA=digitalRead(pinA); //for counting steps
}
void loop()
{
    currentStateA=digitalRead(pinA);
    if(lastStateA!=currentStateA) //count increses both in cw or acw rotation as it only counts steps....so if step changes coount increases.
    {
      //if last state not equal to current state...it means count has increased....now we have to check in which direction it has it has increased.
      if(digitalRead(pinB)!=currentStateA)
      {
      c++;
      }
      else
      {
        c--;
      }
      Serial.println(c);
      lcd.clear();
      delay(dt);
      lcd.print(((2*3.14*R)/30)*(c));
      delay(dt);
      lcd.setCursor(7,0);
      lcd.print("cm");
    }
   lastStateA=currentStateA; 
   
   btnState = digitalRead(buttonPin);
   //Serial.println(btnState);
if(btnState==1&&flag==0)
{
  flag=1;
}
if(btnState==0&&flag==1)
{
  flag=0;
  k++;
  if(k==1)
  {
    lcd.clear();
    //Serial.print("TurnsCount Length :");
    //Serial.println(turnsCount);
    Length=((2*3.14*R)/30)*(c);
    Serial.print("Length = ");
    Serial.println(Length);
    lcd.print("Length in cm = ");
    lcd.setCursor(0,1);
    lcd.print(Length);
    c=0;
    
  }
    if(k==2)
  {
    lcd.clear();
    //Serial.print("TurnsCount Width :");
    //Serial.println(turnsCount);
    Width=((2*3.14*R)/30)*(c);
    lcd.print("Width in cm = ");
    lcd.setCursor(0,1);
    lcd.print(Width);
    c=0;
    
  }

if(k==3)
{
   lcd.clear();
   Perimeter=2*(Length+Width);
   Serial.print("Perimeter in cm :");
   Serial.println(Perimeter);
    lcd.print("Perimeter in cm = ");
    lcd.setCursor(0,1);
    lcd.print(Perimeter);
}
if(k==4)
{
Length=0;
Width=0;
Perimeter=0;
c=0;
k=0;
}
}
}
