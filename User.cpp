#include <sstream>
#include <iostream>
#include <cassert>

#include "User.h"
#include "Helper.h"

using std::ostringstream;
using std::cerr;
using std::cout;

namespace AskMe {

	User::User()
	{
		user_id = allow_anonymous_questions = -1;
	}
	User::User(string line)
	{
		vector<string> tokens = Helper::SplitString(line);

		assert(tokens.size() == 6);
		

		user_id = Helper::ToInt(tokens[0]);
		user_name = tokens[1];
		password = tokens[2];
		name = tokens[3];
		email = tokens[4];
		allow_anonymous_questions = Helper::ToInt(tokens[5]);
	}
	string User::toString() const
	{
		ostringstream oss;
		oss << user_id << "," << user_name << "," << password << "," << name << "," << email << "," << allow_anonymous_questions;

		return oss.str();
	}
	void User::Print() const
	{
		cout << "User " << user_id << ", " << user_name << " " << password << ", " << name << ", " << email << "\n";

	}

	string User::getUserName() const
	{
		return this->user_name;
	}

	void User::setUserName(string username)
	{
		this->user_name = username;
	}

	int User::getUserId() const
	{
		return this->user_id;
	}

	void User::setUserId(int user_id)
	{
		this->user_id = user_id;
	}

	string User::getUserPassword() const
	{
		return this->password;
	}

	void User::setUserPassword(string password)
	{
		this->password = password;
	}

	void User::setName(string Name)
	{
		this->name = Name;
	}

	string User::getName() const
	{
		return this->name;
	}

	void User::setEmail(string email)
	{
		this->email = email;
	}

	void User::clear_questions_id_from_me()
	{
		questions_id_from_me.clear();
	}

	int User::getSizeOfQuestions_id_from_me() const
	{
		return questions_id_from_me.size();
	}

	void User::clear_questionid_questionidsThead_to_map()
	{
		questionid_questionidsThead_to_map.clear();
	}

	vector<int> User::getQuestions_id_from_me() const
	{
		return questions_id_from_me;
	}

	int User::getSizeOfQuestionid_questionidsThead_to_map() const
	{
		return questionid_questionidsThead_to_map.size();
	}

	map<int, vector<int>> User::getQuestionid_questionidsThead_to_map() const
	{
		return questionid_questionidsThead_to_map;
	}

	void User::addNewQuestionIdToQuestions_id_from_me(int id)
	{
		questions_id_from_me.push_back(id);
	}

	void User::addNewQuestionIdToQuestionid_questionidsThead_to_map(int questionId, int questionIdThead)
	{
		questionid_questionidsThead_to_map[questionId].push_back(questionIdThead);
	}

	int User::getAllow_anonymous_questions() const
	{
		return this->allow_anonymous_questions;
	}

	void User::setAllow_anonymous_questions(int allow_anonymous_questions)
	{
		this->allow_anonymous_questions = allow_anonymous_questions;
	}

	

}
