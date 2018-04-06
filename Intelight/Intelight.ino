
#include <SoftwareSerial>

SoftwareSerial SIM900(7, 8); //Configuración del puerto serie para el SIM900
String numeroRespuesta1 = "+573017182250";//probar codigo
String numeroRespuesta2 = "";
String numeroRespuesta3 = "";
String mensaje = "Welcome to Intelight";
int led = 10;

void setup() {
  pinMode(led, OUTPUT);
  digitalWrite(led, LOW);
  delay(1000); //tiempo para encender el gprs y la alimetancion de la tarjeta
  SIM900.begin(19200); //velocidad del puerto serie del puerto SIM900
  Serial.begin(19200); //velocidad del puerto serie del puerto Arduino
  SIM900.print("AT+CMGF=1\r");  //Configura el modo texto para enviar o recibir mensajes
  delay(1000);
  Serial.print("AT+CNMI=2,2,0,0,0\r"); // El módulo enviará los mensaje directamente al puerto serial del dispositivo.
  delay(1000);
  Serial.print("OK");
  //SIM900.println("AT+CPIN=\"XXXX\"");  //Comando AT para introducir el PIN de la tarjeta
  //delay(25000);  //Tiempo para que encuentre una RED
}

void loop() {
  if(Serial.available() > 0){
      delay(1000);
      //char[]valores = Serial.read();
       
  }

}

//metodo para llamar
void llamar() {
  Serial.println("Realizando llamada...");
  SIM900.println("ATD" + numeroRespuesta1); //comando AT para realizar una llamada
  delay(30000); //espera de 30 seg mientras realiza la llamada
  SIM900.println("ATH");
  delay("1000");
  Serial.println("Llamada finalizada");
}

//metodo para enviar mesaje sms
void enviar_mensaje() {
  Serial.println("Enviando sms...");
  SIM900.println("AT+CMGS=\"" + numeroRespuesta1 + "\"");
  delay(1000);
  SIM900.println(mensaje);  // Texto del SMS
  delay(100);
  SIM900.println((char)26); //Comando de finalización ^Z
  delay(100);
  SIM900.println();
  delay(5000);  // Esperamos un tiempo para que envíe el SMS
  Serial.println("SMS enviado");
}



