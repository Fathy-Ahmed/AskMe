#include "Helper.h"


#include <sstream>
#include <fstream>
#include <iostream>


using std::istringstream;
using std::fstream;
using std::cout;
using std::cin;
using std::ios;
using std::string;

namespace AskMe {


	vector<string> Helper::SplitString(string s, string delimiter)
	{
		vector<string> strs;

		int pos = 0;
		string substr;
		while ((pos = (int)s.find(delimiter)) != -1) {
			substr = s.substr(0, pos);
			strs.push_back(substr);
			s.erase(0, pos + delimiter.length());
		}
		strs.push_back(s);
		return strs;
	}

	vector<string> Helper::ReadFileLines(string path)
	{
		vector<string> lines;

		fstream file_handler(path.c_str());

		if (file_handler.fail()) {
			cout << "\n\nERROR: Can't open the file\n\n";
			return lines;
		}

		string line;
		while (getline(file_handler, line)) {
			if (line.size() == 0)
				continue;
			lines.push_back(line);
		}

		file_handler.close();
		return lines;
	}

	void Helper::WriteFileLines(string path, vector<string> lines, bool append)
	{
		auto status = ios::in | ios::out | ios::app;

		if (!append)
			status = ios::in | ios::out | ios::trunc;	// overwrite

		fstream file_handler(path.c_str(), status);

		if (file_handler.fail()) {
			cout << "\n\nERROR: Can't open the file\n\n";
			return;
		}
		for (auto line : lines)
			file_handler << line << "\n";

		file_handler.close();
	}

	int Helper::ToInt(string str)
	{
		istringstream iss(str);
		int num;
		iss >> num;

		return num;
	}

	int Helper::ReadInt(int low, int high)
	{
		while (true) {
			cout << "\nEnter number in range " << low << " - " << high << ": ";
			int value;

			cin >> value;

			if (low <= value && value <= high)
				return value;

			cout << "ERROR: invalid number...Try again\n";
		}
		
	}

	int Helper::ShowReadMenu(vector<string> choices)
	{
		cout << "\nMenu:\n";
		int size = int(choices.size());
		for (int ch = 0; ch < size; ch++)
		{
			cout << "\t" << ch + 1 << ": " << choices[ch] << "\n";
		}
		return ReadInt(1, size);
	}

	string Helper::Encrypt(const string& input, const string& key) {
		string output = input;
		for (size_t i = 0; i < input.size(); ++i) {
			output[i] = input[i] ^ key[i % key.length()];
		}
		return output;
	}

}
