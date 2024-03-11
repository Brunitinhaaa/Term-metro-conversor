const int ACen = 0, BCen = 3, CCen = 2, DCen = 1;
const int ADez = 4, BDez = 5, CDez = 6, DDez = 7;
const int AUni = 8, BUni = 9, CUni = 10, DUni = 11;
const int interruptor = 13;

int binUni[4] = {0, 0, 0, 0};
int binDez[4] = {0, 0, 0, 0};
int binCen[4] = {0, 0, 0, 0};

int sensorValue = 0;
int temperaturaCelsius = 0;
int temperaturaFahrenheit = 0;

int uni = 0;
int dez = 0;
int cen = 0;

void setup() {
  
  // Configurando pinos de saída para os displays com CD4511
  //(digital) para números
  pinMode(ACen, OUTPUT);
  pinMode(BCen, OUTPUT);
  pinMode(CCen, OUTPUT);
  pinMode(DCen, OUTPUT);
  
  pinMode(ADez, OUTPUT);
  pinMode(BDez, OUTPUT);
  pinMode(CDez, OUTPUT);
  pinMode(DDez, OUTPUT);
  
  pinMode(AUni, OUTPUT);
  pinMode(BUni, OUTPUT);
  pinMode(CUni, OUTPUT);
  pinMode(DUni, OUTPUT);

  pinMode(interruptor, INPUT_PULLUP);
  
  //configurando pinos de saída para o display sem CD4511
  //(analógico) para letras
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(A3, OUTPUT);
  pinMode(A4, OUTPUT);
  pinMode(A5, OUTPUT);
}

void loop() {
  
  sensorValue = analogRead(A0);
  temperaturaCelsius = map(sensorValue, 20, 358, -40, 125);
  temperaturaFahrenheit = (temperaturaCelsius * 1.8) + 32;
  int estadoInterruptor = digitalRead(interruptor);
  
  if(estadoInterruptor == HIGH){
    cen = temperaturaCelsius / 100;
  	dez = (temperaturaCelsius / 10) % 10;
  	uni = temperaturaCelsius % 10;
  }else{
  	cen = temperaturaFahrenheit / 100;
  	dez = (temperaturaFahrenheit / 10) % 10;
  	uni = temperaturaFahrenheit % 10;
  }
  
   if(estadoInterruptor == HIGH){
      // Configuração dos valores para exibir "C"
  	digitalWrite(A1, HIGH);
    digitalWrite(A2, HIGH);
    digitalWrite(A3, LOW);
    digitalWrite(A4, HIGH);
    digitalWrite(A5, HIGH);
  }else{
  	// Configuração dos valores para exibir "F"
    digitalWrite(A1, HIGH);
    digitalWrite(A2, HIGH);
    digitalWrite(A3, HIGH);
    digitalWrite(A4, HIGH);
    digitalWrite(A5, LOW);
  }
  
  // Convertendo e exibindo nos displays
  converterExibirDisplay(cen, ACen, BCen, CCen, DCen);
  converterExibirDisplay(dez, ADez, BDez, CDez, DDez);
  converterExibirDisplay(uni, AUni, BUni, CUni, DUni);

  delay(1000);
}

void converterExibirDisplay(int valor, int a, int b, int c, int d) {
  
  // Adicionamos um Display extra para representar o sinal negativo
  int negativoPin = 12;
  pinMode(negativoPin, OUTPUT);

  // Convertendo o valor absoluto para binário
  converterBinario(abs(valor));

  // Exibindo nos displays
  digitalWrite(a, binUni[0]);
  digitalWrite(b, binUni[1]);
  digitalWrite(c, binUni[2]);
  digitalWrite(d, binUni[3]);

  // Se o valor for negativo, acende o pino 12 (G)
  if (valor < 0) {
    digitalWrite(negativoPin, HIGH);
  } else {
    digitalWrite(negativoPin, LOW);
  }
}

void converterBinario(int numero) {
  for (int i = 0; i < 4; i++) {
    binUni[i] = (numero & (1 << i)) ? 1 : 0;
  }
}
