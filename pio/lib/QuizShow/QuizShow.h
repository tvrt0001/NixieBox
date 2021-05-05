#ifndef QUIZSHOW_H
#define QUIZSHOW_H

//#include <Arduino.h>
#include <time.h>

class QuizShow
	{
		private:

		public:

		QuizShow::QuizShow()
			{

			}
		QuizShow::~QuizShow() {

			}


		// QUIZ STUFF
		typedef struct quiz_message {
			const char* quiz_id;
			const char* host_id;
			const char* host_address;
			const char* player_id;
			const char* player_address;
			const char* question_id;
			const char* question_text;
			const char* options;
			const char* correct_answer;
			DateTime datetime_sent;
			DateTime datetime_received;
			} quiz_message;

		typedef struct quiz_response {
			const char* hostID;
			const char* hostAddress;
			const char* playerAddress;
			const char* question;
			DateTime datetime_sent;
			DateTime datetime_received;
			} quiz_response;

		quiz_message qMessage;
		quiz_response qResponse;

	};
#endif

