#pragma once
#include <string>
#include <vector>
class Plan {
private:
	std::string Name;
	std::string This_Week;
	std::string Next_Week;
public:
	Plan();
	void Read(CString buffer);
	void NameFunc(CString buffer);
	void This_WeekFunc(CString buffer);
	void Next_WeekFunc(CString buffer);
	void SetName(std::string A);
	void SetThis_Week(std::string A);
	void SetNext_Week(std::string A);
	std::string GetName();
	std::string GetThis_Week();
	std::string GetNext_Week();
};
std::vector<Plan> Arr;