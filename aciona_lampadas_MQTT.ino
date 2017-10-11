#include <ESP8266WiFi.h>  //essa biblioteca já vem com a IDE. Portanto, não é preciso baixar nenhuma biblioteca adicional
#include <PubSubClient.h> //Importa biblioteca MQTT

//defines
#define SSID_REDE     "saeg"  //coloque aqui o nome da rede que se deseja conectar
#define SENHA_REDE    "semsenha"  //coloque aqui a senha da rede que se deseja conectar
#define MQTT_SERVER "iot2017.nc2.iff.edu.br"
#define MQTT_USER   "saeg2017"
#define MQTT_PASS   "semsenha"
#define PORTA   443

#define TOPICOLAMP1 "/quarto/lampada/lampada1"
#define TOPICOLAMP2 "/quarto/lampada/lampada2"


//constantes e variáveis globais
WiFiClient cliente;
PubSubClient clienteMQTT(cliente);

//prototypes
boolean conectaWiFi(void);
void connectaClienteMQTT(void);
void iniciaMQTT(void);

// 
//Função: conectando ao servidor por MQTT
//Parâmetros: nenhum
//Retorno: nenhum
void connectaClienteMQTT(void) {
  // Espera até estar conectado ao servidor
  while (!clienteMQTT.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Cria cliente IP randômico
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Tentativa de conexão
    if( clienteMQTT.connect(clientId.c_str(), MQTT_USER, MQTT_PASS )) {
      Serial.println("connected");
      clienteMQTT.subscribe(TOPICOLAMP1);
      clienteMQTT.subscribe(TOPICOLAMP1);
    } else {
      Serial.print("failed, rc=");
      Serial.print(clienteMQTT.state());
      Serial.println(" try again in 2 seconds");
      // Espera 2 segundo e tenta novamente
      delay(2000);
    }
  }
}

//Função: inicializa parâmetros de conexão clienteMQTT(endereço do 
//        broker, porta e seta função de callback)
//Parâmetros: nenhum
//Retorno: nenhum
void iniciaMQTT(void){
  clienteMQTT.setServer(MQTT_SERVER, PORTA);
  clienteMQTT.setCallback(mqtt_callback); 
}

//Função: função de callback 
//        esta função é chamada toda vez que uma informação de 
//        um dos tópicos subescritos chega)
//Parâmetros: nenhum
//Retorno: nenhum
void mqtt_callback(char* topic, byte* payload, unsigned int length) 
{
    String msg;
 
    //obtem a string do payload recebido
    for(int i = 0; i < length; i++) 
    {
       char c = (char)payload[i];
       msg += c;
    }
  
    Serial.println(msg);
    
}

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
