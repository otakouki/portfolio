int ROW1 = 25;
int ROW2 = 26;
 int ROW3 = 19;
 int ROW4 = 5;
 int ROW5 = 17;
 
 int COL1 = 34;
int COL2 = 35;
int COL3 = 14;
int COL4 = 15;
void setup()
{
  pinMode(ROW1, OUTPUT);
  pinMode(ROW2, OUTPUT);
  pinMode(ROW3, OUTPUT);
  pinMode(ROW4, OUTPUT);
  pinMode(ROW5, OUTPUT);

  pinMode(COL1, INPUT);
  pinMode(COL2, INPUT);
  pinMode(COL3, INPUT);
  pinMode(COL4, INPUT);

  digitalWrite(ROW1, LOW);
  digitalWrite(ROW2, LOW);
  digitalWrite(ROW3, LOW);
  digitalWrite(ROW4, LOW);
  digitalWrite(ROW5, LOW);

  digitalWrite(COL1, LOW);
  digitalWrite(COL2, LOW);
  digitalWrite(COL3, LOW);
  digitalWrite(COL4, LOW);

  Serial.begin(115200);
}

/*----------------------------------------------
 * 関数: loop
 * 概要:
 * ---------------------------------------------*/
void loop()
{
  digitalWrite(ROW5, LOW);
  delay(10);
  digitalWrite(ROW1, HIGH);
  int sw1 = digitalRead(COL1);
  int sw2 = digitalRead(COL2);
  int sw3 = digitalRead(COL3);
  int sw4 = digitalRead(COL4);

  digitalWrite(ROW1, LOW);
  delay(10);
  digitalWrite(ROW2, HIGH);
  int sw5 = digitalRead(COL1);
  int sw6 = digitalRead(COL2);
  int sw7 = digitalRead(COL3);
  int sw8 = digitalRead(COL4);

  digitalWrite(ROW2, LOW);
  delay(10);
  digitalWrite(ROW3, HIGH);
  int sw9 = digitalRead(COL1);
  int sw10 = digitalRead(COL2);
  int sw11 = digitalRead(COL3);
  int sw12 = digitalRead(COL4);

  digitalWrite(ROW3, LOW);
  delay(10);
  digitalWrite(ROW4, HIGH);
  int sw13 = digitalRead(COL1);
  int sw14 = digitalRead(COL2);
  int sw15 = digitalRead(COL3);
  int sw16 = digitalRead(COL4);

  digitalWrite(ROW4, LOW);
  delay(10);
  digitalWrite(ROW5, HIGH);
  int sw17 = digitalRead(COL1);
  int sw18 = digitalRead(COL2);
  int sw19 = digitalRead(COL3);
  int sw20 = digitalRead(COL4);
  Serial.println(sw1);
  Serial.println(sw2);
  Serial.println(sw3);
  Serial.println(sw4);
  Serial.println(sw5);
  Serial.println(sw6);
  Serial.println(sw7);
  Serial.println(sw8);
  Serial.println(sw9);
  Serial.println(sw10);
  Serial.println(sw11);
  Serial.println(sw12);
  Serial.println(sw13);
  Serial.println(sw14);
  Serial.println(sw15);
  Serial.println(sw16);
  Serial.println(sw17);
  Serial.println(sw18);
  Serial.println(sw19);
  Serial.println(sw20);
  Serial.println("");

  delay(100);
}