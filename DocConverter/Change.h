#pragma once
#include <string>

class Plan {
private:
	std::string Name;
	std::string This_Week;
	std::string Next_Week;
public:
	Plan();
	void Read();
	void NameFunc();
	void This_WeekFunc();
	void Next_WeekFunc();
	void SetName(std::string A);
	void SetThis_Week(std::string A);
	void SetNext_Week(std::string A);
	std::string GetName();
	std::string GetThis_Week();
	std::string GetNext_Week();
};