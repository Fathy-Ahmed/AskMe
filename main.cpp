#include "AskMeSystem.h"

int main() {

	AskMe::AskMeSystem* System = AskMe::AskMeSystem::getInstance();

	System->run();
	
	AskMe::AskMeSystem::FreeInstance();


	return 0;
}