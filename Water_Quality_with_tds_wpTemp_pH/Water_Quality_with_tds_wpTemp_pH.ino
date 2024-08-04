// #include <Wire.h>
// #include <Adafruit_GFX.h>
// #include <Adafruit_SSD1306.h>
#include <OneWire.h>
#include <DallasTemperature.h>
// #include <BlynkSimpleEsp32.h>
// #include <SimpleTimer.h>

// WiFi and Blynk credentials
// char auth[] = "3vbf7rpD6vqpvve23wX3LcgknUqh_L31";
// char ssid[] = "AndroidAP7DF8";
// char pass[] = "electroniclinic";

// TDS sensor pin and constants
#define TdsSensorPin 2
#define VREF 3.3
#define SCOUNT 30

int analogBuffer[SCOUNT];
int analogBufferTemp[SCOUNT];
int analogBufferIndex = 0;

float averageVoltage = 0;
float tdsValue = 0;
float temperature = 25; // Default temperature for compensation

// pH sensor pin and constants
#define pHSensorPin 35
float calibration_value = 20.24 - 0.7;
int buffer_arr[10], temp;
float ph_act;

// DS18B20 temperature sensor
const int oneWireBus = 4;
OneWire oneWire(oneWireBus);
DallasTemperature sensors(&oneWire);

// OLED display
// #define SCREEN_WIDTH 128
// #define SCREEN_HEIGHT 64
// #define OLED_RESET -1
// Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// // Timer for periodic updates
// SimpleTimer timer;

// Function to get the median value for TDS
int getMedianNum(int bArray[], int iFilterLen) {
  int bTab[iFilterLen];
  for (byte i = 0; i < iFilterLen; i++)
    bTab[i] = bArray[i];
  int i, j, bTemp;
  for (j = 0; j < iFilterLen - 1; j++) {
    for (i = 0; i < iFilterLen - j - 1; i++) {
      if (bTab[i] > bTab[i + 1]) {
        bTemp = bTab[i];
        bTab[i] = bTab[i + 1];
        bTab[i + 1] = bTemp;
      }
    }
  }
  if ((iFilterLen & 1) > 0) {
    bTemp = bTab[(iFilterLen - 1) / 2];
  } else {
    bTemp = (bTab[iFilterLen / 2] + bTab[iFilterLen / 2 - 1]) / 2;
  }
  return bTemp;
}

void setup() {
  Serial.begin(115200);
  Serial.println("Setup started");
  // Blynk.begin(auth, ssid, pass);
  sensors.begin();
  Serial.println("Temperature sensor started");
  // display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  // display.clearDisplay();
  // display.setTextColor(WHITE);
  pinMode(TdsSensorPin, INPUT);

  // timer.setInterval(500L, readSensors);
  // timer.setInterval(1000L, displayData);
  Serial.println("Setup completed");
}

void loop() {
  // Blynk.run();
  // timer.run();
  readSensors();
  displayData();
}

void readSensors() {
  Serial.println("Reading sensors...");
  // Read TDS sensor
  for (int i = 0; i < SCOUNT; i++) {
    analogBuffer[i] = analogRead(TdsSensorPin);
    delay(30);
  }
  averageVoltage = getMedianNum(analogBuffer, SCOUNT) * (float)VREF / 4096.0;
  float compensationCoefficient = 1.0 + 0.02 * (temperature - 25.0);
  float compensationVoltage = averageVoltage / compensationCoefficient;
  tdsValue = (133.42 * compensationVoltage * compensationVoltage * compensationVoltage - 255.86 * compensationVoltage * compensationVoltage + 857.39 * compensationVoltage) * 0.5;

  // Read pH sensor
  for (int i = 0; i < 10; i++) {
    buffer_arr[i] = analogRead(pHSensorPin);
    delay(30);
  }
  for (int i = 0; i < 9; i++) {
    for (int j = i + 1; j < 10; j++) {
      if (buffer_arr[i] > buffer_arr[j]) {
        temp = buffer_arr[i];
        buffer_arr[i] = buffer_arr[j];
        buffer_arr[j] = temp;
      }
    }
  }
  unsigned long avgval = 0;
  for (int i = 2; i < 8; i++) {
    avgval += buffer_arr[i];
  }
  float volt = (float)avgval * 3.3 / 4096.0 / 6;
  ph_act = -5.70 * volt + calibration_value;

  // Read temperature sensor
  sensors.requestTemperatures();
  temperature = sensors.getTempCByIndex(0);
  Serial.println("Sensors read");
}

void displayData() {
  Serial.print("TDS: ");
  Serial.print(tdsValue, 0);
  Serial.println(" ppm");

  Serial.print("pH: ");
  Serial.println(ph_act);

  Serial.print("Temp: ");
  Serial.print(temperature);
  Serial.println(" C");

  // display.display();

  // Send data to Blynk
  // Blynk.virtualWrite(V1, tdsValue);
  // Blynk.virtualWrite(V2, ph_act);
  // Blynk.virtualWrite(V3, temperature);
}
