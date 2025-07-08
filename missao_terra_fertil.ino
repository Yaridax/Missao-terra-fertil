#include <DHT.h>
#include <DHT_U.h>
#include <LiquidCrystal.h>

// Inicialização do display LCD (RS, E, D4, D5, D6, D7)
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

#define DHTPIN A1       // Pino conectado ao DHT
#define DHTTYPE DHT11   // Tipo do sensor (DHT11)

DHT sensor(DHTPIN, DHTTYPE);

// Pinos dos LEDs e sensor de umidade do solo
#define pino_Sensor A0
#define pino_LED_Verde 8
#define pino_LED_Amarelo 9
#define pino_LED_Vermelho 10

// Variáveis globais
float temperatura = 0;
float umidadeAr = 0;
int umidadeSolo = 0;
int Umid_Critica = 40;  // Umidade mínima crítica
int Temp_Critica = 65;   // Temperatura máxima crítica

// Controle do lembrete (3 minutos para demo, 20 segundos de exibição)
unsigned long ultimaVezReviramento = 0;
const unsigned long intervaloReviramento = 1 * 60 * 1000UL;  // 1 minuto em ms
const unsigned long tempoExibicaoLembrete = 20 * 1000UL;      // 20 segundos em ms
bool mostrarLembrete = false;
unsigned long tempoInicioLembrete = 0;

void setup() {
  lcd.begin(16, 2);
  Serial.begin(9600);
  sensor.begin();

  pinMode(pino_LED_Verde, OUTPUT);
  pinMode(pino_LED_Amarelo, OUTPUT);
  pinMode(pino_LED_Vermelho, OUTPUT);
  
  ultimaVezReviramento = millis();
}

void loop() {
  lerSensores();
  verificarCondicoes();
  verificarReviramento();
  
  if (mostrarLembrete) {
    mostrarLembreteReviramento();
    // Verifica se já passaram os 20 segundos
    if (millis() - tempoInicioLembrete >= tempoExibicaoLembrete) {
      mostrarLembrete = false;
      desligarLEDs();
    }
  } else {
    mostrarDisplay();
  }
  delay(2000);
}

void lerSensores() {
  umidadeAr = sensor.readHumidity();
  temperatura = sensor.readTemperature();
  umidadeSolo = map(analogRead(pino_Sensor), 1023, 0, 0, 100);
}

void verificarCondicoes() {
  // Verifica temperatura crítica (acima de 65°C)
  if (temperatura >= Temp_Critica) {
    digitalWrite(pino_LED_Vermelho, HIGH);
    digitalWrite(pino_LED_Amarelo, LOW);
    digitalWrite(pino_LED_Verde, LOW);
  } 
  // Verifica umidade crítica (abaixo de 40%)
  else if (umidadeSolo <= Umid_Critica) {
    digitalWrite(pino_LED_Amarelo, HIGH);
    digitalWrite(pino_LED_Vermelho, LOW);
    digitalWrite(pino_LED_Verde, LOW);
  } 
  // Condições ideais
  else {
    digitalWrite(pino_LED_Verde, HIGH);
    digitalWrite(pino_LED_Amarelo, LOW);
    digitalWrite(pino_LED_Vermelho, LOW);
  }
}

void verificarReviramento() {
  unsigned long tempoAtual = millis();
  
  // Verifica se passaram 3 minutos (considerando overflow)
  if (tempoAtual - ultimaVezReviramento >= intervaloReviramento || 
      tempoAtual < ultimaVezReviramento) {
    mostrarLembrete = true;
    tempoInicioLembrete = tempoAtual;
    ultimaVezReviramento = tempoAtual;
  }
}

void mostrarLembreteReviramento() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("REVIRAR COMPOSTO");
  lcd.setCursor(0, 1);
  lcd.print("AGORA!");
  
  // Piscar os LEDs para chamar atenção
  static unsigned long ultimoPiscar = 0;
  static bool estadoLEDs = false;
  
  if (millis() - ultimoPiscar > 200) {
    estadoLEDs = !estadoLEDs;
    digitalWrite(pino_LED_Verde, estadoLEDs);
    digitalWrite(pino_LED_Amarelo, estadoLEDs);
    digitalWrite(pino_LED_Vermelho, estadoLEDs);
    ultimoPiscar = millis();
  }
}

void desligarLEDs() {
  digitalWrite(pino_LED_Verde, LOW);
  digitalWrite(pino_LED_Amarelo, LOW);
  digitalWrite(pino_LED_Vermelho, LOW);
}

void mostrarDisplay() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp:");
  lcd.print(temperatura, 1);
  lcd.print("C");

  lcd.setCursor(0, 1);
  lcd.print("Umid:");
  lcd.print(umidadeSolo);
  lcd.print("%");
}