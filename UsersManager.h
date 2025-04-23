#pragma once

#include "User.h"

using std::pair;

namespace AskMe {

	class UsersManager {
	private:
		map<string, User> userame_userobject_map;
		User current_user;
		int last_id;

	public:
		UsersManager();
		void LoadDatabase();
		void AccessSystem();
		void DoLogin();
		void DoSignUp();
		void ListUsersNamesIds()const;
		pair<int, int> ReadUserId();
		void UpdateDatabase(User& user);

		User &getCurrentUser();
	};

}