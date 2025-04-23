#pragma once
#include "UsersManager.h"
#include "QuestionsManager.h"

namespace AskMe {

	class AskMeSystem {
	private:
		UsersManager users_manager;
		QuestionsManager questions_manager;
		static AskMeSystem* askMeSystem;
		AskMeSystem() {};

	public:
		AskMeSystem(const AskMeSystem&) = delete; // Prevent copying
		AskMeSystem& operator=(const AskMeSystem&) = delete;

		static AskMeSystem *getInstance();
		static void FreeInstance();

		void LoadDatabase(bool fill_user_questions = false);
		void run();

		~AskMeSystem() {};
	};
}