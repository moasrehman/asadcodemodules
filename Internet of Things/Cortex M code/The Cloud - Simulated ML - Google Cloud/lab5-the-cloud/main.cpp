#include "mbed.h"
#include "http_request.h"
#include "mbed.h"
#include "stm32l475e_iot01.h"
#include "stm32l475e_iot01_hsensor.h"
#include "stm32l475e_iot01_psensor.h"
#include "stm32l475e_iot01_tsensor.h"

// #include "BufferedSerial.h"
// #include "DigitalOut.h"
// #include "LowPowerTicker.h"
// #include "PinNameAliases.h"
// #include "mbed.h"
// #include "stm32l475e_iot01.h"
// #include "stm32l475e_iot01_tsensor.h"
// #include "stm32l475e_iot01_hsensor.h"
// #include "stm32l475e_iot01_psensor.h"
#include "stm32l475e_iot01_magneto.h"
#include "stm32l475e_iot01_accelero.h"
#include "stm32l475e_iot01_gyro.h"
// #include <cstdint>

struct SensorData {
  int16_t accel[3];
  float gyro[3];
};

static std::vector<SensorData> batchedSensorData;

static BufferedSerial serial_port(USBTX, USBRX, 9600);

FileHandle *mbed::mbed_override_console(int fd)
{
    return &serial_port;
}

static void initialiseSensors() {
//   BSP_TSENSOR_Init();
//   BSP_HSENSOR_Init();
//   BSP_PSENSOR_Init();
  BSP_ACCELERO_Init();
  BSP_GYRO_Init();
}

static SensorData readSensors() {
  printf("Reading sensors...\n");
  
  SensorData d;

  BSP_ACCELERO_AccGetXYZ(d.accel);
  BSP_GYRO_GetXYZ(d.gyro);

  return d;
}

static void sendReadings(NetworkInterface *net) {
  std::string messageData = "{ \"readings\": [";

  bool first = true;
  for (const auto &sd : batchedSensorData) {
    if (first) {
      first = false;
    } else {
      messageData += ", ";
    }

    messageData += "{ \"accel\": { ";
    messageData += "\"x\": " + std::to_string(sd.accel[0]) + ", ";
    messageData += "\"y\": " + std::to_string(sd.accel[1]) + ", ";
    messageData += "\"z\": " + std::to_string(sd.accel[2]) + " }, ";
    messageData += "\"gyro\": { ";
    messageData += "\"x\": " + std::to_string(sd.gyro[0]) + ", ";
    messageData += "\"y\": " + std::to_string(sd.gyro[1]) + ", ";
    messageData += "\"z\": " + std::to_string(sd.gyro[2]) + " } }";
  }

  messageData += "] }";

  auto *req = new HttpRequest(
      net, HTTP_POST,
      "http://europe-west1-arm-edx-lab5-410315.cloudfunctions.net/ProcessSensorData");

  req->set_header("Content-Type", "application/json");

  printf("Sending message: %s\n", messageData.c_str());
  HttpResponse *res = req->send(messageData.c_str(), messageData.length());
  if (!res) {
    printf("Http request failed (error code %d)\n", req->get_error());
  }

  delete req;
}

/********************************* //
// Lab 4 SendSensorData Function
// ******************************** //
static void sendSensorData(NetworkInterface *net) {
  const char messageFormat[] =
      "{ \"temperature\": %f, \"humidity\": %f, \"pressure\": %f }";

  char messageData[256] = {0};
  sprintf(messageData, messageFormat, BSP_TSENSOR_ReadTemp(),
          BSP_HSENSOR_ReadHumidity(), BSP_PSENSOR_ReadPressure());

  auto *req = new HttpRequest(
      net, HTTP_POST,
      "http://europe-west1-lab-global-connectivity-410214.cloudfunctions.net/StoreSensorData");

  req->set_header("Content-Type", "application/json");

  printf("Sending message: %s\n", messageData);
  HttpResponse *res = req->send(messageData, strlen(messageData));
  if (!res) {
    printf("Http request failed (error code %d)\n", req->get_error());
  }

  delete req;
}
//*/

//********************************* //
// Lab 5 SendSensorData Function
//********************************* //
static void sendSensorData(NetworkInterface *net) {
  auto sensorData = readSensors();
  batchedSensorData.push_back(sensorData);

  if (batchedSensorData.size() >= 5) {
    sendReadings(net);
    batchedSensorData.clear();
  }
}
//**********************************/

int main() {
  printf("Initialising sensors...\n");
  initialiseSensors();

  auto net = NetworkInterface::get_default_instance();

  printf("Connecting to the network...\r\n");

  // Connect to the network
  nsapi_size_or_error_t result = net->connect();

  if (result != 0) {
    printf("Error! net->connect() returned: %d\r\n", result);
    return -1;
  }

  SocketAddress ipaddr;
  net->get_ip_address(&ipaddr);

  printf("Connected with IP address: %s\r\n",
         ipaddr.get_ip_address() ? ipaddr.get_ip_address() : "(none)");

  // Transmit sensor readings every second
  while (true) {
    sendSensorData(net);
    ThisThread::sleep_for(1s);
  }
}

/*/ main() runs in its own thread in the OS
int main()
{
    while (true) {

    }
}

//*/