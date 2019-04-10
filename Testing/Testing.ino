
int FirstCharacter;
String OnesCharacters = "";
int ThirdCharacter;
int FourthCharacter;

int FirstVariable;
int SecondVariable;
int ThirdVariable;
int FourthVariable;
int FifthVariable;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

}

void loop() {
  // put your main code here, to run repeatedly:
FirstVariable = 58;
FourthVariable = 8;
FifthVariable = FourthVariable;
FirstCharacter = (FirstVariable/10);
SecondVariable = (FirstCharacter*10);
ThirdVariable = (FirstVariable - SecondVariable);
//SecondCharacter = 
while (FifthVariable >= 1) {
  FifthVariable-= 1;
  OnesCharacters+="+";
}

delay(500);

Serial.print(FirstCharacter);
Serial.print("   ");
Serial.println(OnesCharacters);
}
