#include <LiquidCrystal.h>

#include <SoftwareSerial.h>
#include <FPM.h>

SoftwareSerial mySerial(8, 9);

FPM finger;

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup()  {
  lcd.begin(16, 2);
  pinMode(6,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
  Serial.begin(9600);
  Serial.println("Empezando Lectura de Huellas");
  mySerial.begin(57600);
  
  if (finger.begin(&mySerial)) {
    Serial.println("Lector FPM10A listo");
    Serial.print("Capacidad: "); Serial.println(finger.capacity);
    Serial.print("Tamaño del paquete: "); Serial.println(finger.packetLen);
  } else {
    Serial.println("No se detecta FPM10A :(");
    while (1) yield();
  }
  lcd.print("Coloque su dedo");
}

void loop()                     // Programa que se ejecutará siempre
{
  getFingerprintID();
}

int getFingerprintID() {
  int p = -1;
  Serial.println("Ponga su dedo en el lector...");
  while (p != FINGERPRINT_OK){
    p = finger.getImage();
    switch (p) {
      case FINGERPRINT_OK:
        Serial.println("Imagen tomada");
        break;
      case FINGERPRINT_NOFINGER:
        Serial.println(".");
        break;
    }
    yield();
  }
//conversion de la imagen
  p = finger.image2Tz();
  switch (p) {
    case FINGERPRINT_OK://si la imagen de la huella es tomada correctamente
      Serial.println("Imagen convertida");
      break;
    case FINGERPRINT_IMAGEMESS://si la imagen no reune las condiciones minimas
      Serial.println("Imagen muy desordenada");
      return p;
  }

  Serial.println("Favor retirar su dedo...");
  while (p != FINGERPRINT_NOFINGER){
    p = finger.getImage();//Asigna a la variable p la imagen de la huella tomada
    yield();
  }
  Serial.println();
  p = finger.fingerFastSearch();
  if (p == FINGERPRINT_OK) {//si encuentra coincidencia con alguna huella de la memoria
    Serial.println("Se encontró coincidencia con una huella del repositorio!");
  } 
  else if (p == FINGERPRINT_NOTFOUND) {//si no encuentra coincidencia con las huellas de la memoria
    Serial.println("No se encontró coincidencia");
    return p;
  } 
  
  // Cuando se encuetra una coincidencia
  Serial.print("Se encontró ID #"); Serial.print(finger.fingerID);//imprime la posicion de la huella en la memoria
  if (finger.fingerID==0){
    Serial.print("Bienvenido Admin");
    lcd.clear();
    lcd.print("Bienvenido!");
    digitalWrite(6,HIGH);
    delay(5000);
    digitalWrite(6,LOW);
    delay(50);
    lcd.clear();
    lcd.print("Coloque su dedo");
  }
   if (finger.fingerID==1){
    Serial.print("Bienvenido Nelson");
    lcd.clear();
    lcd.print("Hola Nelson");
    digitalWrite(6,HIGH);
    delay(5000);
    digitalWrite(6,LOW);
    delay(50);
    lcd.clear();
    lcd.print("Coloque su dedo");
  }
   if (finger.fingerID==2){
    Serial.print("Bienvenido Joshua");
    lcd.clear();
    lcd.print("Hola Joshua");
    digitalWrite(6,HIGH);
    delay(5000);
    digitalWrite(6,LOW);
    delay(50);   
    lcd.clear();
  }
   if (finger.fingerID==3){
    Serial.print("Bienvenido Jose");
    lcd.clear();
    lcd.print("Hola Jose");
    digitalWrite(6,HIGH);
    delay(5000);
    digitalWrite(6,LOW);
    delay(50);  
    lcd.clear();
    lcd.print("Coloque su dedo");
  }
    
  if (finger.fingerID==4){
    Serial.print("Bienvenido Carlos");
    lcd.clear();
    lcd.print("Hola Carlos");
    digitalWrite(6,HIGH);
    delay(5000);
    digitalWrite(6,LOW);
    delay(50);  
    lcd.clear();
    lcd.print("Coloque su dedo");
  }
}


