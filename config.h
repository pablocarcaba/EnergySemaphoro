//wifi

const char* ssid     = "Villacuqui";
const char* password = "PabLucIri2017";
//Poner aquí la ip gateway y mascara en caso de IP fija
IPAddress ip(192, 168, 43, 100);
IPAddress gateway(192, 168, 43, 1);
IPAddress subnet(255, 255, 255, 0);


//
const char* hostname = "ESP8266_curtains";

/*****    Mqtt   *****/
//Ejemplo usando DNS
//const char* mqtt_server = "broker.hivemq.com";

IPAddress mqtt_server(20, 107, 214, 170);
const char* mqttDeviceId = "nodeMCU_optimal_energy_hour_0001";
const char* mqttUser = "mqttuser";
const char* mqttPaswr = "nexttech";


// Topics set
const char* energyRatioTopic = "energy/ratio";
const char* energyConsumptionTopic = "energy/consumption";


// General constants
#define clockpin  D3 //CI
#define enablepin D2 // EI
#define latchpin D1 // LI
#define datapin D0 // DI
//Global variables
