//importando bibliotecas
#include <WiFi.h>                          //importa biblioteca para conectar esp32 com wifi
#include <IOXhop_FirebaseESP32.h>          //importa biblioteca para esp32 se comunicar com firebase
#include <ArduinoJson.h>                //importa biblioteca para colocar informação no formato json, utilizado no firebase (intalar versão 5)
#include <U8g2lib.h>    //display esp32
#include "DHT.h" //sensor de temp.

//fazendo definições para não repetir muito texto durante o código 
#define WIFI_SSID "Millnitz_2G"                  //substitua "Nome_do_seu_wifi" pelo nome da sua rede wifi 
#define WIFI_PASSWORD "millnitz159"             //substitua "Senha_do_seu_wifi" pela senha da sua rede wifi 
#define FIREBASE_HOST "https://tccdiogo-e7753-default-rtdb.firebaseio.com/"    //substitua "Link_do_seu_banco_de_dados" pelo link do seu banco de dados 
#define FIREBASE_AUTH "CABia9sAvdgaWspKWw8zM9eYmzGLHnebAOVgrrV8"   //substitua "Senha_do_seu_banco_de_dados" pela senha do seu banco de dados
#define DHTTYPE DHT11 //temperatura

//pin luz
const int Pin_Quarto_luz = 13;
const int Pin_Varanda_Quarto_luz = 26; // trocar para sótão
////const int Pin_Varanda_Sala_luz = 25; // varanda cozinha retirado
const int Pin_Sala_luz = 33;
const int Pin_Cozinha_luz = 32; //**** pode estar invertido
const int Pin_Garagem_luz = 15;
const int Pin_Externo_luz = 25; // varana cozinha


const int Pin_Externo_sensor = 12;
const int Pin_Cozinha_fumaca = 14;
const int Pin_Sala_temperatura = 27; 


//estado luz
bool Estado_quarto_luz;
bool Estado_Varanda_Quarto_luz;
bool Estado_Varanda_Sala_luz;
bool Estado_Sala_luz;
bool Estado_Cozinha_luz;
bool Estado_Garagem_luz;
bool Estado_Externo_luz;


bool Estado_externo_sensor;
bool Estado_Cozinha_fumaca;

DHT dht(Pin_Sala_temperatura, DHTTYPE);

void setup() {
  //pin luz
  pinMode(Pin_Quarto_luz, OUTPUT);
  pinMode(Pin_Varanda_Quarto_luz, OUTPUT);
  //pinMode(Pin_Varanda_Sala_luz, OUTPUT);
  pinMode(Pin_Sala_luz, OUTPUT);
  pinMode(Pin_Cozinha_luz, OUTPUT);
  pinMode(Pin_Garagem_luz, OUTPUT);
  pinMode(Pin_Externo_luz, OUTPUT);

  pinMode(Pin_Externo_sensor, INPUT);
  pinMode(Pin_Cozinha_fumaca, INPUT);
  pinMode(Pin_Sala_temperatura, INPUT);

  
  Serial.begin(115200);      //inicia comunicação serial
  Serial.println();          //imprime pulo de linha

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);     //inicia comunicação com wifi com rede definica anteriormente
  
  Serial.print("Conectando ao wifi");       //imprime "Conectando ao wifi"
  while (WiFi.status() != WL_CONNECTED)     //enquanto se conecta ao wifi fica colocando pontos
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();                         //imprime pulo de linha

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);   //inicia comunicação com firebase definido anteriormente
  dht.begin();
}


void loop() {
///////LUZES

// QUARTO LUZ
  Estado_quarto_luz = Firebase.getBool("/Quarto/Luz");
  Serial.print("Quarto Luz:");
  Serial.print(Estado_quarto_luz);
  Serial.println();
  if(Estado_quarto_luz == false)
  {
    digitalWrite(Pin_Quarto_luz, LOW);
  }
  else
  {
    digitalWrite(Pin_Quarto_luz, HIGH);
  }

  // VARANDA QUARTO LUZ
  Estado_Varanda_Quarto_luz = Firebase.getBool("/Varanda/Quarto/Luz");
  Serial.print("Varanda Quarto Luz:");
  Serial.print(Estado_Varanda_Quarto_luz);
  Serial.println();
  if(Estado_Varanda_Quarto_luz == false)
  {
    digitalWrite(Pin_Varanda_Quarto_luz, LOW);
  }
  else
  {
    digitalWrite(Pin_Varanda_Quarto_luz, HIGH);
  }

  //SALA LUZ
  Estado_Sala_luz = Firebase.getBool("/Sala/Luz");
  Serial.print("Sala Luz:");
  Serial.print(Estado_Sala_luz);
  Serial.println();
  if(Estado_Sala_luz == false)
  {
    digitalWrite(Pin_Sala_luz, LOW);
  }
  else
  {
    digitalWrite(Pin_Sala_luz, HIGH);
  }

  //Cozinha LUZ
  Estado_Cozinha_luz = Firebase.getBool("/Cozinha/Luz");
  Serial.print("Cozinha Luz:");
  Serial.print(Estado_Cozinha_luz);
  Serial.println();
  if(Estado_Cozinha_luz == false)
  {
    digitalWrite(Pin_Cozinha_luz, LOW);
  }
  else
  {
    digitalWrite(Pin_Cozinha_luz, HIGH);
  }

   //Garagem LUZ
  Estado_Garagem_luz = Firebase.getBool("/Garagem/Luz");
  Serial.print("Garagem Luz:");
  Serial.print(Estado_Garagem_luz);
  Serial.println();
  if(Estado_Garagem_luz == false)
  {
    digitalWrite(Pin_Garagem_luz, LOW);
  }
  else
  {
    digitalWrite(Pin_Garagem_luz, HIGH);
  }

  //EXTERNO LUZ
  Estado_Externo_luz = Firebase.getBool("/Externo/Luz");
  Serial.print("Externo Luz:");
  Serial.print(Estado_Externo_luz);
  Serial.println();
  if(Estado_Externo_luz == false)
  {
    digitalWrite(Pin_Externo_luz, LOW);
  }
  else
  {
    digitalWrite(Pin_Externo_luz, HIGH);
  }

//EXTERNO SENSOR
  Estado_externo_sensor = digitalRead(Pin_Externo_sensor);
  Serial.print("Externo sensor:");
  Serial.print(Estado_externo_sensor);
  Serial.println();
  if(Estado_externo_sensor == 1)
  {
    Firebase.setBool("/Externo/Sensor", true);
  }
  else
  {
    Firebase.setBool("/Externo/Sensor", false);
  }

 //COZINHA FUMAÇA
  Estado_Cozinha_fumaca = digitalRead(Pin_Cozinha_fumaca);
  Serial.print("Cozinha fumaca:");
  Serial.print(Estado_Cozinha_fumaca);
  Serial.println();
  if(Estado_Cozinha_fumaca == 1)
  {
    Firebase.setBool("/Cozinha/Fumaca", true);
  }
  else
  {
    Firebase.setBool("/Cozinha/Fumaca", false);
  }



//SALA TEMPERATURA
float Valor_Sala_umidade = dht.readHumidity();
Firebase.setFloat("/Sala/Umidade", Valor_Sala_umidade);
float Valor_Sala_temperatura = dht.readTemperature();
Firebase.setFloat("/Sala/Temperatura", Valor_Sala_temperatura);
// Check if any reads failed and exit early (to try again).
  if (isnan(Valor_Sala_umidade) || isnan(Valor_Sala_temperatura)) {
    Serial.println(F("Leitura de temperatura e umidade falhou!"));
    return;
  }

  Serial.print(F("Umidade: "));
  Serial.print(Valor_Sala_umidade);
  Serial.print(F(" Temperatura: "));
  Serial.print(Valor_Sala_temperatura);
  Serial.println();
  

/*
  /////////////////////////
  //exemplo da função Set//
  /////////////////////////

  Firebase.setString("/quarto/dono", "Rebeca");
  Firebase.setInt("/quarto/luminosidade", 300);
  Firebase.setBool("/quarto/ocupado", false);
  Firebase.setFloat("/quarto/dono", 24.7);
  Firebase.setInt("/sala/luminosidade", 200);
  delay(3000);
  Firebase.setString("/quarto/dono", "Matteo");
  Firebase.setInt("/quarto/luminosidade", 500);
  Firebase.setBool("/quarto/ocupado", true);
  Firebase.setFloat("/quarto/dono", 35.3);
  Firebase.setInt("/sala/luminosidade", 500);
  delay(3000);
*/

/*
  //////////////////////////
  //exemplo da função Push//
  //////////////////////////

  Firebase.pushString("/quarto/registro", "Matteo");
  delay(3000);
  Firebase.pushString("/quarto/registro", "Rebeca");
  delay(3000);
  Firebase.pushString("/quarto/registro", "Vanderson");
  delay(3000);
  Firebase.pushString("/quarto/registro", "Raquel");
  delay(3000);
*/
}
