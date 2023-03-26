// #include <Arduino.h>
// #include "KeypadHandler.h"
// #include <map>
// #include <string>

// std::string lastMorse{};
// uint32_t morseTimeout = 0;
// bool newInp = false;

// static std::map<std::string, char> morseCode{
//   {"._", 'a'},
//   {"_...", 'b'},
//   {"_._.", 'c'},
//   {"_..", 'd'},
//   {".", 'e'},
//   {".._.", 'f'},
//   {"__.", 'g'},
//   {"....", 'h'},
//   {"..", 'i'},
//   {".___", 'j'},
//   {"_._", 'k'},
//   {"._..", 'l'},
//   {"__", 'm'},
//   {"_.", 'n'},
//   {"___", 'o'},
//   {".__.", 'p'},
//   {"__._", 'q'},
//   {"._.", 'r'},
//   {"...", 's'},
//   {"_", 't'},
//   {".._", 'u'},
//   {"..._", 'v'},
//   {".__", 'w'},
//   {"_.._", 'x'},
//   {"_.__", 'y'},
//   {"__..", 'z'}
// };


// ExtendedButton butt(D2);

// void setup() {
//   Serial.begin(115200);
//   Serial.println("Hi");
//   butt.addEventListener([=](EventsEnum event){    
//     lastMorse += event == EventsEnum::CLICK ? '.' : '_';    
//     if(millis() - morseTimeout > 1000 && millis() - morseTimeout < 2500) lastMorse += ' ';
//     newInp = true;    
//     morseTimeout = millis();
//   });
// }

// void loop() {
//   if(newInp && millis() - morseTimeout > 3000){    
//     newInp = false;  
//     lastMorse += ' ';
//     std::string word = "";
//     std::string letter = ""; 
//     for (auto c : lastMorse)
//     {
//       if (c == ' ')
//       {
//         Serial.printf("|%s|", letter.c_str());
//         word += morseCode[letter];
//         letter = "";
//       }
//       else {
//           letter += c;
//       }
//     }
//     Serial.println();
//     Serial.println(lastMorse.c_str());
//     Serial.println(word.c_str());
//     lastMorse = "";
//   }
//   butt.handle();
// }