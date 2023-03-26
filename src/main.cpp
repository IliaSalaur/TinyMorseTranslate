#include <Arduino.h>
#include <map>
#include <string>

#define BTN D2         // пин кнопки
#define MIN_DASH 200  // мин. время тире (и макс. точки)
#define TIMEOUT 700   // таймаут

#define DEBUG(x) Serial.print(x)
#define RETURN() Serial.println()

bool btnFlag = false, receiveFlag = false, newInp = false;
uint32_t myTimer = 0, timeoutTimer = 0, debounceTimer = 0;
std::string decodeStr = "";
std::string receiveStr = "";

// я знаю, что можно и в PROGMEM
// const char *codeTable[] = {
//   "01",
//   "1000",
//   "011",
//   "110",
//   "100",
//   "0",
//   "0001",
//   "1100",
//   "00",
//   "0111",
//   "101",
//   "0100",
//   "11",
//   "10",
//   "111",
//   "0110",
//   "010",
//   "000",
//   "1",
//   "001",
//   "0010",
//   "0000",
//   "1010",
//   "1101",
//   "1011",
//   "1001",

//   "01111",
//   "00111",
//   "00011",
//   "00001",
//   "00000",
//   "10000",
//   "11000",
//   "11100",
//   "11110",
//   "11111",

//   "010101",
//   "101010",
//   "10010",
//   "100001",
//   "10001",
// };

static std::map<std::string, std::string> codeTable{
  {"._", "a"},
  {"_...", "b"},
  {"_._.", "c"},
  {"_..", "d"},
  {".", "e"},
  {".._.", "f"},
  {"__.", "g"},
  {"....", "h"},
  {"..", "i"},
  {".___", "j"},
  {"_._", "k"},
  {"._..", "l"},
  {"__", "m"},
  {"_.", "n"},
  {"___", "o"},
  {".__.", "p"},
  {"__._", "q"},
  {"._.", "r"},
  {"...", "s"},
  {"_", "t"},
  {".._", "u"},
  {"..._", "v"},
  {".__", "w"},
  {"_.._", "x"},
  {"_.__", "y"},
  {"__..", "z"},
  {"_...._", "-"},
  {"...._", "ä"},
  {"....._", "ü"},
  {"...___", "ö"},
  {"......", "ß"}
};

const char decodeTable[] = "ABWGDEVZIJKLMNOPRSTUFHCQYX1234567890.,;- ÄÖÜ";

void setup() {
  Serial.begin(115200);
  pinMode(BTN, INPUT_PULLUP);
}

void loop() {
  bool btnState = !digitalRead(BTN);
  if (btnState && !btnFlag && millis() - debounceTimer > 30) {
    debounceTimer = millis();
    btnFlag = true;
    myTimer = millis();
  }
  if (!btnState && btnFlag && millis() - debounceTimer > 30) {
    newInp = true;
    debounceTimer = millis();
    btnFlag = false;
    int signal = millis() - myTimer;
    if (signal < MIN_DASH) {
      decodeStr += ".";
    } else {
      decodeStr += "_";
    }
    timeoutTimer = millis();
    receiveFlag = true;
  }
  if (receiveFlag && millis() - timeoutTimer > TIMEOUT) {
    receiveStr += codeTable[decodeStr];
    decodeStr = "";    
    receiveFlag = false;
  }

    if(newInp == true && millis() - timeoutTimer > TIMEOUT * 2)
    {
        newInp = false;
    
        Serial.println(receiveStr.c_str());
        receiveStr = "";
    }
}