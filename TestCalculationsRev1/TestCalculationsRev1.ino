
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
FourthVariable = 8;
FirstCharacter = (FirstVariable/10);
SecondVariable = (FirstCharacter*10);
ThirdVariable = (FirstVariable - SecondVariable);
//SecondCharacter = 
while (FourthVariable >= 1) {
  ThirdVariable-= 1;
  OnesCharacters+="+";
}


Serial.print(FirstVariable);
Serial.print("   ");
Serial.println(FourthVariable);
}
