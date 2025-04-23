#pragma once
#include "Question.h"
#include "User.h"

using std::pair;

namespace AskMe {

	class QuestionsManager {
	private:
		// From question id to list of questions IDS on this question (thread questions) - All users
		map<int, vector<int>> questionid_questionidsThead_to_map;

		// Map the question id to question object. Let's keep one place ONLY with the object
		//map<int, Question> questionid_questionobject_map;
		map<int, Question> questionid_questionobject_map; // using pointers More efficient storage and Avoids copying big objects

		int last_id;

	public:
		QuestionsManager();
		void LoadDatabase();
		void FillUserQuestions(User& user);
		void PrintUserToQuestions(User& user);
		void PrintUserFromQuestions(User& user);
		// Used in Answering a question for YOU.
		// It can be any of your questions (thread or not)
		int ReadQuestionIdAny(User& user);
		// Used to ask a question on a specific thread for whatever user
		int ReadQuestionIdThread(User& user);
		void AnswerQuestion(User& user);
		void DeleteQuestion(User& user);
		void AskQuestion(User& user, pair<int, int> to_user_pair);
		void ListFeed()const;
		void UpdateDatabase();


		
	};

}