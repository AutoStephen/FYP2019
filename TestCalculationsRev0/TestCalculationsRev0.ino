
int FirstCharacter;
String OnesCharacters = "";
int ThirdCharacter;
int FourthCharacter;

int FirstVariable;
int SecondVariable;
int ThirdVariable;
int FourthVariable;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

}

void loop() {
  // put your main code here, to run repeatedly:
FirstVariable = 58;
FirstCharacter = (FirstVariable/10);
SecondVariable = (FirstCharacter*10);
ThirdVariable = (FirstVariable - SecondVariable);
//SecondCharacter = 
for (FourthVariable = ThirdVariable; FourthVariable != 0; FourthVariable--) {
  OnesCharacters = (OnesCharacters + "+");
}


Serial.print(FirstCharacter);
Serial.print("   ");
Serial.println(OnesCharacters);
}
