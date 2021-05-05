#ifndef __QUIZMASTER_H__
#define __QUIZMASTER_H__

#include <ArduinoJson-v6.17.3.h>

class QuizMaster {

private:

      char* input;
      size_t inputLength; ///(optional)

      StaticJsonDocument<0> filter;
      filter.set(true);
      DynamicJsonDocument doc(3072);
      DeserializationError error = deserializeJson(doc, input, inputLength, DeserializationOption::Filter(filter));

      if (error) {
            Serial.print(F("deserializeJson() failed: "));
            Serial.println(error.f_str());
            return;
            }

      int response_code = doc["response_code"]; // 0

      for (JsonObject elem : doc["results"].as<JsonArray>()) {

            const char* quiz_id = elem["quizid"];
            const char* category = elem["category"]; // "Sports", "Sports", "Entertainment: Film", "Geography", ...
            const char* type = elem["type"]; // "multiple", "multiple", "multiple", "multiple", "multiple", ...
            const char* difficulty = elem["difficulty"]; // "easy", "medium", "easy", "easy", "medium", "medium", ...
            const char* question = elem["question"]; // "Which of the following sports is not part of the ...
            const char* correct_answer = elem["correct_answer"]; // "Horse-Riding", "Putney", "Tommy Lee Jones", ...

            JsonArray options = elem["incorrect_answers"];
            const char* option_1 = options[0]; // "Cycling", "Hammersmith", "Harrison Ford", ...
            const char* option_2 = options[1]; // "Swimming", "Vauxhall ", "Harvey Keitel", ...
            const char* option_3 = options[2]; // "Running", "Battersea", "Martin Landau", ...
            }

      options.add(correct_answer);

public:


      };
#endif // __QUESTIONS_H__
#endif // __QUIZMASTER_H__