#include "Change.h"
#include "pch.h"
#include <string>
Plan::Plan() {
	Name = "Empty";
	This_Week = "Empty";
	Next_Week = "Empty";
}
void Plan::Read() {
	NameFunc();
	This_WeekFunc();
	Next_WeekFunc();
}
void Plan::SetName(std::string A) {
	Name.clear();
	Name = A;
}
void Plan::SetThis_Week(std::string A) {
	This_Week.clear();
	This_Week = A;
}
void Plan::SetNext_Week(std::string A) {
	Next_Week.clear();
	Next_Week = A;
}
std::string Plan::GetName() {
	return Name;
}
std::string Plan::GetThis_Week() {
	return This_Week;
}
std::string Plan::GetNext_Week() {
	return Next_Week;
}
void Plan::NameFunc() {

}
void Plan::This_WeekFunc() {

}
void Plan::Next_WeekFunc() {

}