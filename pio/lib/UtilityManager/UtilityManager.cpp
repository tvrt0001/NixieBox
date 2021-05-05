#include "UtilityManager.h"

RTC_Millis rtc = RTC_Millis();
const char* ntpServer = "pool.ntp.org";
const int LOCAL_TIME_OFFSET = -4;
const long utcOffsetInSeconds = 3600 * LOCAL_TIME_OFFSET;
bool Century = false, h12, pm;
char daysOfTheWeek[7][20] = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };
char months[12][4] = { "JAN", "FEB", "MAR", "APR", "MAY", "JUN", "JUL", "AUG", "SEP", "OCT", "NOV", "DEC" };

// // Menu Vars
// char _currentPage = '0'; // Indicates that we are at Home Screen
// char selectedUnit = '0'; // Indicates the selected unit for the first example, cms or inches

//BLE
bool deviceConnected = false;
bool oldDeviceConnected = false;

int bootCount = 0;
int result;
String message, iMsg;
bool msg_received = false;
uint8_t broadcastAddress[] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };

UtilityManager::UtilityManager() {
  rtc.begin(DateTime(F(__DATE__), F(__TIME__)));
  }

UtilityManager::~UtilityManager() {

  }

DateTime UtilityManager::getNow() {
  return rtc.now();
  }


double UtilityManager::ReadVoltage(gpio_num_t adc_pin)
  {
  double reading = analogRead(adc_pin); // Reference voltage is 3v3 so maximum reading is 3v3 = 4095 in range 0 to 4095

  if (reading < 1 || reading > 4095) return 0;
  // return -0.000000000009824 * pow(reading,3) + 0.000000016557283 * pow(reading,2) + 0.000854596860691 * reading + 0.065440348345433;

  return -0.000000000000016 * pow(reading, 4) + 0.000000000118171 * pow(reading, 3) - 0.000000301211691 * pow(reading, 2) + 0.001109019271794 * reading + 0.034143524634089;
  // Added an improved polynomial, use either, comment out as required  
  }

esp_sleep_wakeup_cause_t UtilityManager::print_wakeup_reason() {

  esp_sleep_wakeup_cause_t wakeup_reason;

  wakeup_reason = esp_sleep_get_wakeup_cause();

  switch (wakeup_reason)
    {
      case ESP_SLEEP_WAKEUP_EXT0: log_d("Wakeup caused by external signal using RTC_IO"); break;
      case ESP_SLEEP_WAKEUP_EXT1: log_d("Wakeup caused by external signal using RTC_CNTL"); break;
      case ESP_SLEEP_WAKEUP_TIMER: log_d("Wakeup caused by timer"); break;
      case ESP_SLEEP_WAKEUP_TOUCHPAD: log_d("Wakeup caused by touchpad"); break;
      case ESP_SLEEP_WAKEUP_ULP: log_d("Wakeup caused by ULP program"); break;
      default: log_d("Wakeup was not caused by deep sleep: %d\n", wakeup_reason); break;
    }
  return wakeup_reason;
  }

void UtilityManager::triggerDeepSleep(gpio_num_t wake_gpio_pin)
  {
  //Increment boot number and print it every reboot
  ++bootCount;
  log_d("Boot number: %d\n", bootCount);

  //If you were to use ext1, you would use it like 
  //esp_sleep_enable_ext1_wakeup(BUTTON_PIN_BITMASK,ESP_EXT1_WAKEUP_ANY_HIGH);

  esp_sleep_enable_ext0_wakeup(wake_gpio_pin, 1); //1 = High, 0 = Low

  //Go to sleep now
  log_d("Going to sleep now");
  esp_deep_sleep_start();
  log_d("This will never be printed");
  }

/////////////////////////////////////////////////////////////////
// Utility Functions
/////////////////////////////////////////////////////////////////

void UtilityManager::WakeUp(gpio_num_t wake_gpio_pin) {
  //Print the wakeup reason for ESP32
  esp_wake_deep_sleep();
  print_wakeup_reason();
  }

/////////////////////////////////////////////////////////////////
// Utility Functions
/////////////////////////////////////////////////////////////////
int UtilityManager::str2mac(const char* mac, uint8_t* values) {
  if (6 == sscanf(mac, "%hhx:%hhx:%hhx:%hhx:%hhx:%hhx", &values[0], &values[1], &values[2], &values[3], &values[4], &values[5])) {
    return 1;
    }
  else {
    return 0;
    }
  }

//bool UtilityManager::incrementLeakyCounter()
//  {
  // bool overflow = false;
  // /* This counter needs to be reset if the error counter has not been
  //    incremented for a long duration. The main objective is to catch
  //    a flurry of errors leading to counter overflow */
  // if ((currentTime - lastIncrementTime) > LEAK_PERIOD)
  //   {
  //   counter = 0;
  //   }
  // lastIncrementTime = currentTime;
  // counter++;
  // if (counter > OVERFLOW_THRESHOLD)
  //   {
  //   overflow = true;
  //   }
  //return overflow;
  //RETURN 0;
  //}


String UtilityManager::mac2String(byte ar[]) {
  String s;
  for (byte i = 0; i < 6; ++i)
    {
    char buf[3];
    sprintf(buf, "%02X", ar[i]); // J-M-L: slight modification, added the 0 in the format for padding
    s += buf;
    if (i < 5) s += ':';
    }
  return s;
  }

void UtilityManager::setupWifi() {
  WiFi.mode(WIFI_STA);
  bool result = WiFi.softAP(ssid, password, CHANNEL, 0);
  if (!result) { Serial.println("AP Config failed."); }
  else { Serial.println("AP Config Success. Broadcasting with AP: " + (String)ssid); }
  }

int sort() { //int& arr[])
  // int arr[] = { 1, 2, 3, 4, 5, 6, 7, 8 };
  //int n = sizeof(&arr) / sizeof(&arr[0]);
  //randomize(arr, n);
  //printArray(arr, n);
  //return arr;
  return 0;
  }