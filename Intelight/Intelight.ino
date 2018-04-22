
#include <SoftwareSerial.h>

SoftwareSerial SIM900(7, 8); //Configuración del puerto serie para el SIM900
String numeroRespuesta1 = "+573017182250";//probar codigo
String numeroRespuesta2 = "";
String numeroRespuesta3 = "";
String mensaje = "Welcome to Intelight";
int led = 13;
int pin1;
int pin2;
int pin3;
int pin4;

void setup() {
  pinMode(led, OUTPUT);
  digitalWrite(led, LOW);
  delay(1000); //tiempo para encender el gprs y la alimetancion de la tarjeta
  SIM900.begin(19200); //velocidad del puerto serie del puerto SIM900
  Serial.begin(19200); //velocidad del puerto serie del puerto Arduino
  delay(1000);
  SIM900.println("ATE1");//activar eco
  delay(1000);
  SIM900.print("AT+CMGF=1\r"); //Configuración del módulo GSM en modo texto
  delay(1000);
  SIM900.println("AT+CNMI=2,2,0,0,0\r"); // El módulo enviará los mensaje directamente al puerto serial del dispositivo.
  delay(1000);
  Serial.println(SIM900.read());
  //SIM900.println("AT+CPIN=\"XXXX\"");  //Comando AT para introducir el PIN de la tarjeta
  //delay(25000);  //Tiempo para que encuentre una RED
}

void loop() {

  if (Serial.available() > 0) {
    //delay(1000);
    char valores = Serial.read();
    switch (valores) {
      case '1': llamar();
        break;
      case '2': enviar_mensaje();
        break;
      case '3': hablarAlSim();
        break;
    }
    if (SIM900.available() > 0) {
      while (SIM900.available() > 0) {
        Serial.println((char)SIM900.read());
      }
      digitalWrite(led, HIGH);
      delay(5000);
      digitalWrite(led, LOW);
    }
    //digitalWrite(led, HIGH);
    //delay(5000);
    //llamar();
  }


}

//metodo para llamar
void llamar() {
  Serial.println("Realizando llamada...");
  SIM900.println("ATD +573017182250;"); //comando AT para realizar una llamada
  Serial.println("Imprimi en puerto ATD");
  delay(30000); //espera de 30 seg mientras realiza la llamada
  SIM900.println("ATH");
  Serial.println("Imprimi en puerto ATH"); //cuelga la llamada
  delay(1000);
  Serial.println("Llamada finalizada");
  SIM900.println();
}

//metodo para enviar mesaje sms
void enviar_mensaje() {
  Serial.println("Enviando sms...");
  SIM900.println("AT+CMGF=1\r");  //Configura el modo texto para enviar o recibir mensajes
  delay(1000);
  SIM900.println("AT+CMGS=\"+573017182250\"");
  delay(1000);
  SIM900.println(mensaje);  // Texto del SMS
  delay(100);
  SIM900.println((char)26); //Comando de finalización ^Z
  delay(100);
  SIM900.println();
  delay(5000);  // Esperamos un tiempo para que envíe el SMS
  Serial.println("SMS enviado");
}

void hablarAlSim() {
  Serial.println("hablando al puerto sim...");
  SIM900.println("ATI4"); //mostrar configuracion del modem
  if (SIM900.available() > 0) {
    while (SIM900.available() > 0) {
      Serial.println(SIM900.read());
    }

    Serial.println("Hay datos");
  } else {
    Serial.println("No hay datos");
  }

}



