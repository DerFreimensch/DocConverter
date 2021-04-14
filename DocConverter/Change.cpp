
#include "pch.h"
#include <string>
#include <iostream>
#include "DocConverter.h"

void Output() {
	std::ofstream out("C:\\Users\\MKD\\Desktop\\Output.csv");
	for (int i = 0; i < theApp.Arr.size(); i++) {
		out << std::string(CW2A(theApp.Arr[i].GetName().GetString())) << ';' << '"'
			<< std::string(CW2A(theApp.Arr[i].GetThis_Week())) << '"' << ';' << '"'
			<< std::string(CW2A(theApp.Arr[i].GetNext_Week())) << '"' << '\n';
	}
}
Plan::Plan() {
	m_name = L"Empty";
	m_thisWeek = L"Empty";
	m_nextWeek = L"Empty";
}
void Plan::Readinto(const CString &buffer) {
	//NameFunc(buffer, );
	//This_WeekFunc(buffer);
	//Next_WeekFunc(buffer);
}
void Plan::SetName(const CString &buffer) {
	m_name.Empty();
	m_name = buffer;
}
void Plan::SetThis_Week(const CString &buffer) {
	m_thisWeek.Empty();
	m_thisWeek = buffer;
}
void Plan::SetNext_Week(const CString &buffer) {
	m_nextWeek.Empty();
	m_nextWeek = buffer;
}
CString Plan::GetName() {
	return m_name;
}
CString Plan::GetThis_Week() {
	return m_thisWeek;
}
CString Plan::GetNext_Week() {
	return m_nextWeek;
}
int Plan::NameFunc(const CString &buffer, int i) {

	const int pos = buffer.Find(':', i+1);
	if (pos != -1){
		SetName(buffer.Mid(i+1, pos - i -1));
	}

	return i;
}
int Plan::This_WeekFunc(const CString &buffer, int i) {
	std::cout << "It works2" << std::endl;
	return 0;
}
int Plan::Next_WeekFunc(const CString &buffer, int i) {
	std::cout << "It works3" << std::endl;
	return 0;
}

bool Read(const CString &buffer) {
	for (int i = 0; i < buffer.GetLength(); i++) {
		if (buffer[i] == '[') {
			 Plan Node;
			 theApp.Arr.push_back(Node);
		}
		if (buffer[i] == ']') {
			i = theApp.Arr.back().NameFunc(buffer, i);
		}
	}
	return true;
}