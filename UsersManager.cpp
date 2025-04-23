#include <iostream>

#include "UsersManager.h"
#include "Helper.h"

using std::max;
using std::cout;
using std::cin;
using std::make_pair;

namespace AskMe {

	UsersManager::UsersManager()
	{
		last_id = 0;
		/*current_user = User();
		userame_userobject_map = map<string, User>();*/
	}

	void UsersManager::LoadDatabase()
	{
		last_id = 0;
		userame_userobject_map.clear();

		vector<string> lines = Helper::ReadFileLines("users.txt");

		for (auto& line : lines) {
			User user(line);
			userame_userobject_map[user.getUserName()] = user;
			last_id = max(last_id, user.getUserId());
		}
	}

	void UsersManager::AccessSystem()
	{
		int choice = Helper::ShowReadMenu({ "Login", "Sign Up" });
		if (choice == 1)
			DoLogin();
		else
			DoSignUp();
	}

	void UsersManager::DoLogin()
	{
		LoadDatabase();	// in case user added from other parallel run

		while (true) {
			cout << "Enter user name & password: ";
			string user_name, password;
			cin >> user_name >> password;

			password = Helper::Encrypt(password);

			current_user.setUserName(user_name);
			current_user.setUserPassword(password);

			// check if user name and password are correct
			if (!userame_userobject_map.count(current_user.getUserName())) {
				cout << "\nInvalid user name or password. Try again\n\n";
				continue;
			}

			User user_exist = userame_userobject_map[current_user.getUserName()];

			if (current_user.getUserPassword() != user_exist.getUserPassword()) {
				cout << "\nInvalid user name or password. Try again\n\n";
				continue;
			}

			current_user = user_exist;
			break;

		}
	}

	void UsersManager::DoSignUp()
	{
		while (true) {
			cout << "Enter user name. (No spaces): ";
			string user_name;
			cin >> user_name;
			current_user.setUserName(user_name);

			if (userame_userobject_map.count(current_user.getUserName()))
				cout << "Already used. Try again\n";
			else
				break;
		}

		cout << "Enter password: ";
		string password;
		cin >> password;
		password = Helper::Encrypt(password);
		current_user.setUserPassword(password);

		cout << "Enter name: ";
		string name;
		cin >> name;
		current_user.setName(name);

		cout << "Enter email: ";
		string email;
		cin >> email;
		current_user.setEmail(email);

		cout << "Allow anonymous questions? (0 or 1): ";
		int allow_anonymous_questions;
		cin >> allow_anonymous_questions;
		current_user.setAllow_anonymous_questions(allow_anonymous_questions);

		// What happens in 2 parallel sessions if they signed up?
		// They are given same id. This is wrong handling :)
		current_user.setUserId(++last_id);
		userame_userobject_map[current_user.getUserName()] = current_user;

		UpdateDatabase(current_user);
	}

	void UsersManager::ListUsersNamesIds()const
	{
		for (auto& pair : userame_userobject_map)
			cout << "ID: " << pair.second.getUserId() << "\t\tName: " << pair.second.getName() << "\n";
	}

	pair<int, int> UsersManager::ReadUserId()
	{
		while (true)
		{
			int user_id;
			cout << "Enter User id or -1 to cancel: ";
			cin >> user_id;

			if (user_id == -1)
				return make_pair(-1, -1);

			for (auto& pair : userame_userobject_map) {
				if (pair.second.getUserId() == user_id)
					return make_pair(user_id, pair.second.getAllow_anonymous_questions());
			}

			cout << "Invalid User ID. Try again\n";
		}
	}

	void UsersManager::UpdateDatabase(User& user)
	{
		string line = user.toString();

		vector<string> lines(1, line);
		Helper::WriteFileLines("users.txt", lines);
	}

	User &UsersManager::getCurrentUser()
	{
		return current_user;
		//return userame_userobject_map[current_user.getUserName()];
		//return userame_userobject_map.find(current_user.getUserName())->second;
		//return userame_userobject_map.at(current_user.getUserName());
		//return userame_userobject_map[current_user.getUserName()];
	}

	

}
