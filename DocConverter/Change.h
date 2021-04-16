#pragma once
#include <string>
#include <list>
class c_m_thisWeek {
public:
	CString m_W1 = L"На этой неделе:";
	CString m_W2 = L"Эта неделя:";
};
class c_m_nextWeek {
public:
	//CString 
};

class CPlan {
private:
	CString m_name;
	CString m_thisWeek;
	CString m_nextWeek;
public:
	CPlan();
	void Readinto(const CString &buffer);
	int NameFunc(const CString &buffer, int i);
	int This_WeekFunc(const CString &buffer, int i);
	int Next_WeekFunc(const CString &buffer, int i);
	void SetName(const CString &A);
	void SetThis_Week(const CString &A);
	void SetNext_Week(const CString &A);
	CString GetName() const;
	CString GetThis_Week() const;
	CString GetNext_Week()const;
};

