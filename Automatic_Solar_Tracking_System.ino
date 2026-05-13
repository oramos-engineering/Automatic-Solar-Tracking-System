#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
Servo miServo;

int ldr1 = A0;
int ldr2 = A1;
int panelPin = A2;

int valor1 = 0;
int valor2 = 0;
int lecturaPanel = 0;

float voltajePanel = 0;
float lux = 0;
float irradiancia = 0;

// POSICIONES DEL SERVO
int centro = 90;
int izquierda = 45;
int derecha = 125;

int posicion = 90;

// SUBE este valor si sigue moviendose mucho
int tolerancia = 120;

// Movimiento suave por pasos
int pasoServo = 2;

unsigned long tiempoIguales = 0;
bool contandoCentro = false;

// CALIBRACION
int ajusteLDR1 = 0;
int ajusteLDR2 = 0;

void moverSuave(int destino) {
  destino = constrain(destino, izquierda, derecha);

  if (posicion < destino) {
    for (int i = posicion; i <= destino; i++) {
      miServo.write(i);
      delay(12);
    }
  } 
  else if (posicion > destino) {
    for (int i = posicion; i >= destino; i--) {
      miServo.write(i);
      delay(12);
    }
  }

  posicion = destino;
}

void calibrarLDR() {
  long suma1 = 0;
  long suma2 = 0;

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Calibrando");
  lcd.setCursor(0, 1);
  lcd.print("Misma luz");

  for (int i = 0; i < 50; i++) {
    suma1 += analogRead(ldr1);
    suma2 += analogRead(ldr2);
    delay(100);
  }

  int promedio1 = suma1 / 50;
  int promedio2 = suma2 / 50;

  int diferencia = promedio1 - promedio2;

  if (diferencia > 0) {
    ajusteLDR1 = diferencia;
    ajusteLDR2 = 0;
  } else {
    ajusteLDR1 = 0;
    ajusteLDR2 = -diferencia;
  }

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Calibrado");
  delay(2000);
  lcd.clear();
}

void setup() {
  Serial.begin(9600);

  miServo.attach(9);
  posicion = centro;
  miServo.write(centro);

  lcd.begin(16, 2);
  lcd.backlight();
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("Seguidor solar");
  lcd.setCursor(0, 1);
  lcd.print("Centro 90");

  delay(3000);

  calibrarLDR();

  posicion = centro;
  miServo.write(centro);
}

void loop() {
  valor1 = analogRead(ldr1) - ajusteLDR1;
  valor2 = analogRead(ldr2) - ajusteLDR2;

  valor1 = constrain(valor1, 0, 1023);
  valor2 = constrain(valor2, 0, 1023);

  lecturaPanel = analogRead(panelPin);
  voltajePanel = (lecturaPanel * 5.0) / 1023.0;

  int promedio = (valor1 + valor2) / 2;
  lux = map(promedio, 0, 1023, 0, 100000);
  irradiancia = lux / 120.0;

  int diferencia = valor1 - valor2;
  String movimiento = "Mant";

  // Si LDR1 tiene mas luz, se mueve hacia LDR1
  if (diferencia > tolerancia) {
    int nuevaPos = posicion - pasoServo;
    moverSuave(nuevaPos);
    movimiento = "LDR1";
    contandoCentro = false;
  }

  // Si LDR2 tiene mas luz, se mueve hacia LDR2
  else if (diferencia < -tolerancia) {
    int nuevaPos = posicion + pasoServo;
    moverSuave(nuevaPos);
    movimiento = "LDR2";
    contandoCentro = false;
  }

  // Si estan casi iguales, espera 10 segundos y vuelve al centro
  else {
    movimiento = "Mant";

    if (!contandoCentro) {
      tiempoIguales = millis();
      contandoCentro = true;
    }

    if (millis() - tiempoIguales >= 10000 && posicion != centro) {
      moverSuave(centro);
      movimiento = "Ctr";
      contandoCentro = false;
    }
  }

  Serial.print("LDR1: ");
  Serial.print(valor1);
  Serial.print(" | LDR2: ");
  Serial.print(valor2);
  Serial.print(" | Dif: ");
  Serial.print(diferencia);
  Serial.print(" | Voltaje: ");
  Serial.print(voltajePanel, 2);
  Serial.print(" V | Irradiancia: ");
  Serial.print(irradiancia, 0);
  Serial.print(" W/m2 | Pos: ");
  Serial.print(posicion);
  Serial.print(" | Mov: ");
  Serial.println(movimiento);

  lcd.setCursor(0, 0);
  lcd.print("V:");
  lcd.print(voltajePanel, 2);
  lcd.print(" P:");
  lcd.print(posicion);
  lcd.print("   ");

  lcd.setCursor(0, 1);
  lcd.print("Irr:");
  lcd.print(irradiancia, 0);
  lcd.print(" W/m2   ");

  delay(300);
}