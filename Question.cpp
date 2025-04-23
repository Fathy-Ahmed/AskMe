#include <cassert>
#include <sstream>
#include <iostream>

#include "Question.h"
#include "Helper.h"

using std::ostringstream;
using std::cout;

namespace AskMe {
	Question::Question()
	{
		question_id = parent_question_id = from_user_id = to_user_id = -1;
		is_anonymous_questions = 1;
	}
	Question::Question(string line)
	{
		vector<string> tokens = Helper::SplitString(line);
		assert(tokens.size() == 7);

		question_id = Helper::ToInt(tokens[0]);
		parent_question_id = Helper::ToInt(tokens[1]);
		from_user_id = Helper::ToInt(tokens[2]);
		to_user_id = Helper::ToInt(tokens[3]);
		is_anonymous_questions = Helper::ToInt(tokens[4]);
		question_text = tokens[5];
		answer_text = tokens[6];
	}
	string Question::ToString() const
	{
		ostringstream oss;
		oss << question_id << "," << parent_question_id << "," << from_user_id << "," << to_user_id << "," << is_anonymous_questions << "," << question_text << "," << answer_text;

		return oss.str();
	}
	void Question::PrintToQuestion() const
	{
		string prefix = "";

		if (parent_question_id != -1) prefix = "\tThread: ";

		cout << prefix << "Question Id (" << question_id << ")";

		if (!is_anonymous_questions)
			cout << " from user id(" << from_user_id << ")";

		cout << "\t Question: " << question_text << "\n";

		if (answer_text != "")
			cout << prefix << "\tAnswer: " << answer_text << "\n";
		cout << "\n";
	}
	void Question::PrintFromQuestion() const
	{
		cout << "Question Id (" << question_id << ")";
		if (!is_anonymous_questions)
			cout << " !AQ";

		cout << " to user id(" << to_user_id << ")";
		cout << "\t Question: " << question_text;

		if (answer_text != "")
			cout << "\tAnswer: " << answer_text << "\n";
		else
			cout << "\tNOT Answered YET\n";
	}
	void Question::PrintFeedQuestion() const
	{
		if (parent_question_id != -1)
			cout << "Thread Parent Question ID (" << parent_question_id << ") ";

		cout << "Question Id (" << question_id << ")";
		if (!is_anonymous_questions)
			cout << " from user id(" << from_user_id << ")";

		cout << " To user id(" << to_user_id << ")";

		cout << "\t Question: " << question_text << "\n";
		if (answer_text != "")
			cout << "\tAnswer: " << answer_text << "\n";
	}
	int Question::getQuestionId() const
	{
		return this->question_id;
	}
	void Question::setQuestionId(int id)
	{
		this->question_id = id;
	}
	int Question::getParentQuestionId() const
	{
		return this->parent_question_id;
	}
	void Question::setParentQuestionId(int parent_question_id)
	{
		this->parent_question_id = parent_question_id;
	}
	int Question::getFrom_user_id() const
	{
		return this->from_user_id;
	}
	void Question::setFrom_user_id(int id)
	{
		this->from_user_id = id;
	}
	int Question::getTo_user_id() const
	{
		return this->to_user_id;
	}
	void Question::setTo_user_id(int id)
	{
		this->to_user_id = id;
	}
	void Question::setIs_anonymous_questions(int is_anonymous_questions)
	{
		this->is_anonymous_questions = is_anonymous_questions;
	}
	string Question::getAnswer_text() const
	{
		return this->answer_text;
	}
	void Question::setAnswer_text(string answer_text)
	{
		this->answer_text = answer_text;
	}
	string Question::getQuestion_text() const
	{
		return this->question_text;
	}
	void Question::setQuestion_text(string answer_text)
	{
		this->question_text = answer_text;
	}
}
