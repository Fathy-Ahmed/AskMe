#pragma once

#include<string>
#include<vector>
#include<map>

using std::string;
using std::vector;
using std::map;

namespace AskMe {

	class User {
	private:
		int user_id;		// internal system ID
		string user_name;
		string password;
		string name;
		string email;
		int allow_anonymous_questions;	// 0 or 1
		vector<int> questions_id_from_me;
		// From question id to list of questions IDS on this question (thread questions) - For this user
		map<int, vector<int>> questionid_questionidsThead_to_map;

	public:

		User();

		User(string line);

		string toString() const;

		void Print() const;

		string getUserName()const;
		void setUserName(string username);

		int getUserId()const;
		void setUserId(int user_id);


		string getUserPassword()const;
		void setUserPassword(string password);

		string getName()const;
		void setName(string Name);

		int getAllow_anonymous_questions()const;
		void setAllow_anonymous_questions(int allow_anonymous_questions);

		void setEmail(string email);

		void clear_questions_id_from_me();
		int getSizeOfQuestions_id_from_me()const;
		vector<int> getQuestions_id_from_me()const;

		void clear_questionid_questionidsThead_to_map();
		int getSizeOfQuestionid_questionidsThead_to_map()const;
		map<int, vector<int>> getQuestionid_questionidsThead_to_map()const;

		void addNewQuestionIdToQuestions_id_from_me(int id);

		void addNewQuestionIdToQuestionid_questionidsThead_to_map(int questionId, int questionIdThead);

	};






}