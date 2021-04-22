#pragma once
#include <string>
#include <list>
class c_m_thisWeek {
public:
	CString m_tw1;
	CString m_tw2;
	CString m_tw3;
	c_m_thisWeek();
};
class c_m_nextWeek {
public:
	CString m_nw1;
	CString m_nw2;
	CString m_nw3;
	CString m_nw4;
	CString m_nw5;
	CString m_nw6;
	CString m_nw7;
	CString m_nw8;

	c_m_nextWeek();
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
	void This_WeekFunc(const CString &buffer);
	void Next_WeekFunc(const CString &buffer);
	void SetName(const CString &A);
	void SetThis_Week(const CString &A);
	void SetNext_Week(const CString &A);
	CString GetName() const;
	CString GetThis_Week() const;
	CString GetNext_Week()const;
};

