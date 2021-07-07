#pragma once
#include<string>
#include<sstream>
// Takes two strings and asks if they are the same. Return true if so. False if not.
bool IsSameString(std::string Question, std::string Answer) { //REORGANIZE the if statements, so that we could cut out while loop early.
	unsigned int i = 0;
	while (Question[i] != '\0' && Answer[i] != '\0' && Question[i] == Answer[i]) {
		i++;
	}
	if (i == Question.length() && i == Answer.length()) {
		return true;
	}
	else {
		return false;
	}
}

// converts a hexadecimal value to an integer; necessary for reading the rgb values of transparency
int HexToInt(std::string str, int start) {
	// the string is the hexadecimal we are reading, and the integer is where we start reading the string 
	std::string temp;
	int ret; // the integer value we will be returning
	temp += str[start];
	temp += str[start + 1];
	std::stringstream ss;
	ss << std::hex << temp;
	ss >> ret; // putting the decimal integer value of the hexadecimal into ret
	return ret;
}

// Splits a string (value,value) into two globals. 
void SplitStringStream(std::string& line, int& GlobalWidth, int& GlobalHeight) {
	long long d = 0; //Modified to prevent overflow, long long = long long int, which is an 8 byte integer. Required by (I believe) substr function.
	std::string tempWidth;
	std::string tempHeight;
	//Find comma's position in the string
	while (line[d] != ',') {
		d++;
	}
	d++;
	//Create two substrings, to isolate the integer portion of each side of the comma.
	tempWidth = line.substr(0, line.length() - d);
	tempHeight = line.substr(d, line.length());
	// printf("Dimensions are %s, %s\n", tempWidth.c_str(), tempHeight.c_str());

	//Convert both substrings to integer values.
	std::istringstream iss1(tempWidth);
	std::istringstream iss2(tempHeight);

	//Assign as Globals for Window Width and Widow Height - From Text Save File.
	iss1 >> GlobalWidth;
	iss2 >> GlobalHeight;
}

// Takes a String and String and returns a char* with elements of both, the size of both, null terminated.
char* StringAndStringToCharArr(std::string& TempPath2, std::string& tempSource) {
	//CHECK - the warning might just be the byte size of size() is 8 or 32 bytes while ints are by default 4.
	int TempPath2Len = TempPath2.size();
	int TempSourceLen = tempSource.size();
	char* TempPath = new char[TempPath2Len + TempSourceLen];
	//Concatonate Repo Path and the Image.Format. 
	for (int i = 0; i < TempPath2Len; i++) {
		TempPath[i] = TempPath2[i];
	}
	for (int i = 0; i < TempSourceLen; i++) {
		TempPath[(i + TempPath2Len)] = tempSource[i];
	}
	//Mull Terminate
	TempPath[TempPath2Len + TempSourceLen] = '\0';
	return TempPath;
}