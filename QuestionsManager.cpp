#include <iostream>

#include "QuestionsManager.h"
#include "Helper.h"

using std::max;
using std::cout;
using std::cin;
using std::cout;

namespace AskMe {

	QuestionsManager::QuestionsManager()
	{
		last_id = 0;
	}

	void QuestionsManager::LoadDatabase()
	{
		last_id = 0;
		questionid_questionidsThead_to_map.clear();
		questionid_questionobject_map.clear();

		vector<string> lines = Helper::ReadFileLines("questions.txt");
		for (auto& line : lines) {

			Question question(line);
			last_id = max(last_id, question.getQuestionId());

			questionid_questionobject_map[question.getQuestionId()] = question;

			if (question.getParentQuestionId() == -1) // root has no parent
				questionid_questionidsThead_to_map[question.getQuestionId()].push_back(question.getQuestionId());
			else
				questionid_questionidsThead_to_map[question.getParentQuestionId()].push_back(question.getQuestionId());
		}
	}

	void QuestionsManager::FillUserQuestions(User& user)
	{
		user.clear_questions_id_from_me();
		user.clear_questionid_questionidsThead_to_map();

		for (auto& pair : questionid_questionidsThead_to_map) {	// pair<int, vector<Question>>
			for (auto& question_id : pair.second) {		//  vector<Question>

				// Get the question from the map. & means same in memory, DON'T COPY
				Question& question = questionid_questionobject_map[question_id];

				if (question.getFrom_user_id() == user.getUserId())
					user.addNewQuestionIdToQuestions_id_from_me(question.getQuestionId());

				if (question.getTo_user_id() == user.getUserId()) {
					if (question.getParentQuestionId() == -1)
						user.addNewQuestionIdToQuestionid_questionidsThead_to_map(question.getQuestionId(), question.getQuestionId());
					else
						user.addNewQuestionIdToQuestionid_questionidsThead_to_map(question.getParentQuestionId(), question.getQuestionId());
				}
			}
		}
	}

	void QuestionsManager::PrintUserToQuestions(User& user)
	{
		cout << "\n";

		if (user.getSizeOfQuestionid_questionidsThead_to_map() == 0)
			cout << "No Questions";

		for (auto& pair : user.getQuestionid_questionidsThead_to_map()) {		// pair<int, vector<Question>>
			for (auto& question_id : pair.second) {		//  vector<Question>

				// Get the question from the map. & means same in memory, DON'T COPY
				Question& question = questionid_questionobject_map[question_id];
				question.PrintToQuestion();
			}
		}
		cout << "\n";
	}

	void QuestionsManager::PrintUserFromQuestions(User& user)
	{
		cout << "\n";
		if (user.getSizeOfQuestions_id_from_me() == 0)
			cout << "No Questions";

		for (auto& question_id : user.getQuestions_id_from_me()) {		//  vector<Question>

			// Get the question from the map. & means same in memory, DON'T COPY
			Question& question = questionid_questionobject_map[question_id];
			question.PrintFromQuestion();
		}
		cout << "\n";
	}

	// Used in Answering a question for YOU.
	// It can be any of your questions (thread or not)
	int QuestionsManager::ReadQuestionIdAny(User& user)
	{
		int question_id;
		cout << "Enter Question id or -1 to cancel: ";
		cin >> question_id;

		if (question_id == -1)
			return -1;

		if (!questionid_questionobject_map.count(question_id)) {
			cout << "\nERROR: No question with such ID. Try again\n\n";
			return ReadQuestionIdAny(user);
		}

		Question& question = questionid_questionobject_map[question_id];

		if (question.getTo_user_id() != user.getUserId()) { // not your question
			cout << "\nERROR: Invalid question ID. Try again\n\n";
			return ReadQuestionIdAny(user);
		}
		return question_id;
	}

	// Used to ask a question on a specific thread for whatever user
	int QuestionsManager::ReadQuestionIdThread(User& user)
	{
		int question_id;
		cout << "For thread question: Enter Question id or -1 for new question: ";
		cin >> question_id;

		if (question_id == -1)
			return -1;

		if (!questionid_questionidsThead_to_map.count(question_id)) {
			cout << "No thread question with such ID. Try again\n";
			return ReadQuestionIdThread(user);
		}
		return question_id;
	}

	void QuestionsManager::AnswerQuestion(User& user)
	{
		int question_id = ReadQuestionIdAny(user);

		if (question_id == -1)
			return;

		Question& question = questionid_questionobject_map[question_id];

		question.PrintToQuestion();

		if (question.getAnswer_text() != "")
			cout << "\nWarning: Already answered. Answer will be updated\n";

		cout << "Enter answer: ";	// if user entered comma, system fails :)
		string answer;
		getline(cin, answer);	// read last enter
		getline(cin, answer);

		question.setAnswer_text(answer);
	}

	void QuestionsManager::DeleteQuestion(User& user)
	{
		int question_id = ReadQuestionIdAny(user);

		if (question_id == -1)
			return;

		vector<int> ids_to_remove;	// to remove from questionid_questionobject_map

		// Let's see if thread or not. If thread, remove all of it
		if (questionid_questionidsThead_to_map.count(question_id)) { // thread
			ids_to_remove = questionid_questionidsThead_to_map[question_id];
			questionid_questionidsThead_to_map.erase(question_id);
		}
		else {
			ids_to_remove.push_back(question_id);

			// let's find in which thread to remove. Consistency is important when have multi-view
			for (auto& pair : questionid_questionidsThead_to_map) {
				vector<int>& vec = pair.second;
				for (int pos = 0; pos < (int)vec.size(); ++pos) {
					if (question_id == vec[pos]) {
						vec.erase(vec.begin() + pos);
						break;
					}
				}
			}

		}

		for (auto id : ids_to_remove) {
			questionid_questionobject_map.erase(id);
		}
	}

	void QuestionsManager::AskQuestion(User& user, pair<int, int> to_user_pair)
	{
		Question question;

		if (!to_user_pair.second) {
			cout << "Note: Anonymous questions are not allowed for this user\n";
			question.setIs_anonymous_questions(0);
		}
		else {
			cout << "Is anonymous questions?: (0 or 1): ";
			int is_anonymous_questions;
			cin >> is_anonymous_questions;
			question.setIs_anonymous_questions(is_anonymous_questions);
		}

		question.setParentQuestionId(ReadQuestionIdThread(user));

		cout << "Enter question text: ";	// if user entered comma, system fails :)
		string question_text;
		getline(cin, question_text);
		getline(cin, question_text);
		question.setQuestion_text(question_text);

		question.setFrom_user_id(user.getUserId());
		question.setTo_user_id(to_user_pair.first);

		// What happens in 2 parallel sessions who asked question?
		// They are given same id. This is wrong handling :)
		question.setQuestionId(++last_id);

		questionid_questionobject_map[question.getQuestionId()] = question;

		if (question.getParentQuestionId() == -1)
			questionid_questionidsThead_to_map[question.getQuestionId()].push_back(question.getQuestionId());
		else
			questionid_questionidsThead_to_map[question.getParentQuestionId()].push_back(question.getQuestionId());

	}

	void QuestionsManager::ListFeed()const
	{
		for (auto pair : questionid_questionobject_map) {
			Question& question = pair.second;

			if (question.getAnswer_text() == "")
				continue;

			question.PrintFeedQuestion();
		}
	}

	void QuestionsManager::UpdateDatabase()
	{
		vector<string> lines;

		for (auto pair : questionid_questionobject_map)
			lines.push_back(((pair.second)).ToString());
		
		Helper::WriteFileLines("questions.txt", lines, false);
	}

}