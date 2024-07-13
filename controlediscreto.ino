# include <TimerOne.h>

// Definições de pinos para o motor e encoder
const int ENCA = 2;  // Pino A do encoder
const int ENCB = 3;  // Pino B do encoder

const int IN1 = 9;   // Pino IN1 da ponte H (controle de direção)
const int IN2 = 8;   // Pino IN2 da ponte H (controle de direção)
const int ENA = 5;   // Pino ENA da ponte H (controle de velocidade)



float rpm, uk_1 = 0, ek_1 = 0, rk = 1000 , yk , ek, uk;
const int pulsesPerRevolution = 200;
unsigned long pulseCount = 0;
unsigned long count = 0;


const int max_samples = 200;
float data_values[max_samples][2];
int sample_index = 0;


void rotinaControladorDiscreto(){
  yk = rpm;
  ek=rk-yk;
  uk= (1*uk_1*100 + 0.0032*ek*100 + 0.0032*ek_1*100);
  uk = uk*0.01;

  if (uk>=255){
    analogWrite(ENA, 120);
  }
  else{
    analogWrite(ENA, uk);
  }
  if (sample_index < max_samples) {
    data_values[sample_index][0] = rpm;
    data_values[sample_index][1] = millis() / 1000.0;
    sample_index++;
  }
  // Atualizo as variáveis:
  uk_1=uk;
  ek_1=ek;
}

void countPulse() {
  pulseCount++;
}

void pwmInterrupt(){
  count = pulseCount;
  pulseCount = 0;
  rpm = (count * 6000.0) / pulsesPerRevolution;
  rotinaControladorDiscreto();
}



void setup() {
  Serial.begin(115200);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENCA, INPUT);
  pinMode(ENCB, INPUT);

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);


  attachInterrupt(digitalPinToInterrupt(ENCA), countPulse, RISING);


  Timer1.initialize(10000); // Inicializa o Timer1 com período de 10000 microssegundos = 0.01s ou seja f = 100hz
  Timer1.attachInterrupt(pwmInterrupt); // Anexa a função de interrupção
}

void loop() {
  // Vasco da Gama


  if (sample_index == max_samples) {
    for (int i = 0; i < max_samples; i++) {
      Serial.print(data_values[i][1], 3); // Imprimindo com três casas decimais
      Serial.print(",");
      Serial.println(data_values[i][0], 3); // Imprimindo com três casas decimais
    }
    sample_index = 0;
    // Serial.print("printou tudo");
  }

}
