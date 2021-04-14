#pragma once
#include <string>
#include <vector>
class Plan {
private:
	CString m_name;
	CString m_thisWeek;
	CString m_nextWeek;
public:
	Plan();
	void Readinto(const CString &buffer);
	int NameFunc(const CString &buffer, int i);
	int This_WeekFunc(const CString &buffer, int i);
	int Next_WeekFunc(const CString &buffer, int i);
	void SetName(const CString &A);
	void SetThis_Week(const CString &A);
	void SetNext_Week(const CString &A);
	CString GetName();
	CString GetThis_Week();
	CString GetNext_Week();
};

bool Read(const CString &buffer);
void Output();