int Led=13;
int Shock=3;
int val;
void setup()
{
    pinMode(Led,OUTPUT);
    pinMode(Shock,INPUT);
}
void loop()
{
    val=digitalRead(Shock);
    if(val==HIGH)
        digitalWrite(Led,HIGH);
    else
        digitalWrite(Led,LOW);
}


