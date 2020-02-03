int RCLK = 5;
int SER = 4;
int SRCLK = 6;

#define TotalIC 2
#define TotalICPins TotalIC * 8

boolean Data[TotalICPins];

void ClearBuffer()
{
  for (int i = TotalICPins - 1; i >=  0; i--)
  {
    Data[i] = LOW;
  }
  UpdateData();
}

void UpdateData()
{
  digitalWrite(RCLK, LOW);
  for (int i = TotalICPins - 1; i >=  0; i--)
  {
    digitalWrite(SRCLK, LOW);
    digitalWrite(SER, Data[i]);
    digitalWrite(SRCLK, HIGH);

  }
  digitalWrite(RCLK, HIGH);
}

void setup()
{
  pinMode(SER, OUTPUT);
  pinMode(RCLK, OUTPUT);
  pinMode(SRCLK, OUTPUT);

  ClearBuffer();
}

void loop()
{
  for (int i = TotalICPins - 1; i >=  0; i--)
  {
    Data[i] = HIGH;
    UpdateData();
    delay(10);
    ClearBuffer();
  }

  for (int i = 1; i < TotalICPins - 1;  i++)
  {
    Data[i] = HIGH;
    UpdateData();
    delay(10);
    ClearBuffer();
  }

}
