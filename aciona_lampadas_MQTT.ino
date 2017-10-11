#include <ESP8266WiFi.h>  //essa biblioteca já vem com a IDE. Portanto, não é preciso baixar nenhuma biblioteca adicional
#include <PubSubClient.h> //Importa biblioteca MQTT

//defines
#define SSID_REDE     "saeg"  //coloque aqui o nome da rede que se deseja conectar
#define SENHA_REDE    "semsenha"  //coloque aqui a senha da rede que se deseja conectar
#define MQTT_SERVER "iot2017.nc2.iff.edu.br"
#define MQTT_USER   "saeg2017"
#define MQTT_PASS   "semsenha"
#define PORTA   443


//constantes e variáveis globais
WiFiClient cliente;



//prototypes
boolean conectaWiFi(void);








//Função: faz a conexão WiFI
//Parâmetros: nenhum
//Retorno: nenhum
boolean conectaWiFi(void)
{
    
    cliente.stop();
    
    delay(500);
    Serial.println("Conectando-se à rede WiFi...");
    Serial.println();  
    delay(1000);
    WiFi.begin(SSID_REDE, SENHA_REDE);
    
    int contDelay = 0;
    while ((WiFi.status() != WL_CONNECTED) && (contDelay < 30) ) 
    {
        delay(500);
        Serial.print(".");
        contDelay++;
        
    }

    if(contDelay>=30){
       Serial.println("");
       Serial.println("WiFi não connectado");
       return false;
    }
      
    Serial.println("");
    Serial.println("WiFi connectado com sucesso!");  
    Serial.println("IP obtido: ");
    Serial.println(WiFi.localIP());

    delay(500);
    return true;
}


void setup() {
  Serial.begin(115200);
  delay(10);
  if (!conectaWiFi())
     return;

 

}

void loop() {
  

  
  
}
