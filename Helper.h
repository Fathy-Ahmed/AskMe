#pragma once
#include<string>
#include<vector>

using std::string;
using std::vector;

namespace AskMe{

	class Helper {
	private:
		Helper() {} // Private constructor to prevent instantiation
	public:
		Helper(const Helper&) = delete; // Prevent copying
		Helper& operator=(const Helper&) = delete;
		static vector<string> SplitString(string s, string delimiter = ",");
		static vector<string> ReadFileLines(string path);
		static void WriteFileLines(string path, vector<string> lines, bool append = true);
		static int ToInt(string str);
		static int ReadInt(int low, int high);
		static int ShowReadMenu(vector<string> choices);
		static string Encrypt(const string& input, const string& key = "Fathy Ahmed");

	};
}