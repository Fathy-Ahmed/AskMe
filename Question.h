#pragma once
#include <string>
using std::string;

namespace AskMe {
	class Question {
	private:
		int question_id;
		// To support thread. Each question look to a parent question
		// -1 No parent (first question in the thread)
		int parent_question_id;
		int from_user_id;
		int to_user_id;
		int is_anonymous_questions;	// 0 or 1
		string question_text;
		string answer_text;			// empty = not answered

	public:
		Question();
		Question(string line);
		string ToString()const;
		void PrintToQuestion()const;
		void PrintFromQuestion()const;
		void PrintFeedQuestion()const;

		int getParentQuestionId()const;
		void setParentQuestionId(int parent_question_id);

		//int getIs_anonymous_questions()const;
		void setIs_anonymous_questions(int is_anonymous_questions);

		string getAnswer_text()const;
		void setAnswer_text(string answer_text);

		string getQuestion_text()const;
		void setQuestion_text(string answer_text);

		int getFrom_user_id()const;
		void setFrom_user_id(int id);

		int getTo_user_id()const;
		void setTo_user_id(int id);

		int getQuestionId()const;
		void setQuestionId(int id);

	};
}