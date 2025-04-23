#include <iostream>

#include "AskMeSystem.h"
#include "Helper.h"

using std::cout;

namespace AskMe {

	AskMeSystem* AskMeSystem::askMeSystem = nullptr; // Initialize static member
	AskMeSystem* AskMeSystem::getInstance()
	{
		if (askMeSystem == nullptr) {
			cout << "Creating a new AskMeSystem instens\n\n\n";
			askMeSystem = new AskMeSystem();
		}
		return askMeSystem;
	}

	void AskMeSystem::FreeInstance()
	{
		if (AskMeSystem::askMeSystem != nullptr) {
			cout << "Free the instance\n";
			delete AskMeSystem::askMeSystem;
			AskMeSystem::askMeSystem = nullptr;
		}
		else
			cout << "The instance freed already\n";
	}

	void AskMeSystem::LoadDatabase(bool fill_user_questions)
	{
		users_manager.LoadDatabase();
		questions_manager.LoadDatabase();

		if (fill_user_questions)	// first time, waiting for login
			questions_manager.FillUserQuestions(users_manager.getCurrentUser());
	}
	void AskMeSystem::run()
	{
		LoadDatabase();
		users_manager.AccessSystem();
		questions_manager.FillUserQuestions(users_manager.getCurrentUser());

		vector<string> menu = { 
			"Print Questions To Me" ,
			"Print Questions From Me",
			"Answer Question",
			"Delete Question",
			"Ask Question",
			"List System Users",
			"Feed",
			"Logout"
		};

		while (true) {
			int choice = Helper::ShowReadMenu(menu);
			LoadDatabase(true);

			if (choice == 1)
				questions_manager.PrintUserToQuestions(users_manager.getCurrentUser());
			else if (choice == 2)
				questions_manager.PrintUserFromQuestions(users_manager.getCurrentUser());
			else if (choice == 3) {
				questions_manager.AnswerQuestion(users_manager.getCurrentUser());
				questions_manager.UpdateDatabase();
			}
			else if (choice == 4) {
				questions_manager.DeleteQuestion(users_manager.getCurrentUser());
				// Let's build again (just easier, but slow)
				questions_manager.FillUserQuestions(users_manager.getCurrentUser());
				questions_manager.UpdateDatabase();
			}
			else if (choice == 5) {
				pair<int, int> to_user_pair = users_manager.ReadUserId();
				if (to_user_pair.first != -1) {
					questions_manager.AskQuestion(users_manager.getCurrentUser(), to_user_pair);
					questions_manager.UpdateDatabase();
				}
			}
			else if (choice == 6)
				users_manager.ListUsersNamesIds();
			else if (choice == 7)
				questions_manager.ListFeed();
			else
				break;
		}
		run();	// Restart again

	}
}
