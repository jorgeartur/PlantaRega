#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

WiFiClientSecure client;
String textFix = "GET /forms/d/e/1FAIpQLSeqvRmNyJ7IPepmgB0PAvFQwp9YfcUdSpAJI4o44zQpUdExww/formResponse?ifq&entry.457253454=123";
char auth[] = "ae0831f308cd44f28c110ee5b05ab065";  
const int sensorPin = 13; 
int sensorState = 0;
int lastState = 0;
#define    rele     12
#define    sens     13 
int cont = 0;


void setup()
{
  Serial.begin(9600);
  Blynk.begin(auth, "MiPhone", "9454xrjorge");  //wifi name and password
  /*WiFi.mode(WIFI_STA);//Habilita o modo estaçao
    WiFi.begin("MiPhone", "9454xrjorge");
    delay(2000);*/
    
  pinMode(sensorPin, INPUT);

  pinMode(rele, OUTPUT);   //configura saída para sinal do relé
  pinMode(sens,  INPUT);   //configura entrada para leitura do sensor


  digitalWrite(rele, LOW); //rele inicia desligado
}

void loop()
{ 
 if(!digitalRead(sens)) digitalWrite(rele, LOW);

  //Senão, liga relé 
  else digitalWrite(rele, HIGH);
  
  delay(741);     
  
  Blynk.run();

  sensorState = digitalRead(sensorPin);
Serial.println(sensorState);

if (sensorState == 1 && lastState == 0) {
  Serial.println("Precisa de água");
  Blynk.notify("Vai regar");
   /* if (client.connect("docs.google.com", 443) == 1)//Tenta se conectar ao servidor do Google docs na porta 443 (HTTPS)
    {
      int cont = 0;
        String toSend = textFix;//Atribuimos a String auxiliar na nova String que sera enviada
        toSend = cont++;//Adicionamos um valor aleatorio
        toSend += "&submit=Submit HTTP/1.1";//Completamos o metodo GET para nosso formulario.
 
        client.println(toSend);//Enviamos o GET ao servidor-
        client.println("Host: docs.google.com");//-
        client.println();//-
        client.stop();//Encerramos a conexao com o servidor
        Serial.println("Dados enviados.");//Mostra no monitor que foi enviado
    }
    else
    {
        Serial.println("Erro ao se conectar");//Se nao for possivel conectar no servidor, ira avisar no monitor.
    }*/
 
  lastState = 1;
  delay(1000);
    
  } 
  else if (sensorState == 1 && lastState == 1) {
  Serial.println("Ainda não foi regado");
  delay(1000);
  }
  else {
    Serial.println("Ainda não precisa de água");
    Blynk.notify("A sua planta foi regada");
    lastState = 0;
    delay(2000);
  }

  delay(100);
}
