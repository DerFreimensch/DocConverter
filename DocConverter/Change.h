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
class c_m_Worker {
public:
	CString m_w1;
	CString m_w2;
	CString m_w3;
	CString m_w4;
	CString m_w5;
	CString m_w6;
	CString m_w7;
	CString m_w8;
	CString m_w9;
	CString m_w10;
	CString m_w11;
	CString m_w12;
	CString m_w13;
	CString m_w14;
	c_m_Worker();
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

