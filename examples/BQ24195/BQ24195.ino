#include <BQ24195.h>

// Объявление экземпляра класса
BQ24195 CHARGER(&Wire);

void setup() {

  // Инициализация порта
  Serial.begin(115200);
  
  // Инициализация
  CHARGER.begin();
  
}

void loop() {

  // Вывод информации по зарядке
  Serial.print("Version  : "); Serial.println(CHARGER.getVersion());
  Serial.print("Status   : "); Serial.println(CHARGER.getSystemStatus());
  Serial.print("Limit_I  : "); Serial.println(CHARGER.getInputCurrentLimit());
  Serial.print("Charge_I : "); Serial.println(CHARGER.getChargeCurrent());
  Serial.println();

  // Задержка в 5 секунд
  delay(5000);

}