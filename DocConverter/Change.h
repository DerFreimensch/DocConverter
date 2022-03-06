#pragma once
#include <string>
#include <list>



class CInfo {
public:
	std::list<CString> ThisWeek;
	std::list<CString> NextWeek;
	std::list<CString> Name;
	std::list<CString> DocName;
	CInfo makeList(CString &config);
};

class CData {
private:
	int Day;
	int Month;
	CString TW, NW;
public:
	CData();
	CString MakeThisWeek();
	CString MakeNextWeek();

};
class CPlan {
private:
	CString m_name;
	CString m_thisWeek;
	CString m_nextWeek;
public:
	CPlan();
	void ReadInfo(const CString &buffer);
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

