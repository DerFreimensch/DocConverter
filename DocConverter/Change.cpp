
#include "pch.h"
#include "Change.h"
#include <string>
#include <iostream>
#include "DocConverter.h"
#include <ctime>


CPlan::CPlan() {
	m_name = L"";
	m_thisWeek = L"";
	m_nextWeek = L"";
}
void CPlan::ReadInfo(const CString &buffer) {
	//NameFunc(buffer, );
	//This_WeekFunc(buffer);
	//Next_WeekFunc(buffer);
}
void CPlan::SetName(const CString &buffer) {
	m_name.Empty();
	m_name = buffer;
}
void CPlan::SetThis_Week(const CString &buffer) {
	//m_thisWeek.Empty();
	m_thisWeek = m_thisWeek + buffer;
}
void CPlan::SetNext_Week(const CString &buffer) {
	//m_nextWeek.Empty();
	m_nextWeek = m_nextWeek + buffer;
}
CString CPlan::GetName() const {
	return m_name;
}
CString CPlan::GetThis_Week() const {
	return m_thisWeek;
}
CString CPlan::GetNext_Week() const {
	return m_nextWeek;
}
int CPlan::NameFunc(const CString &buffer, int i) {
	const int pos = buffer.Find('@', i+1); // поиск места где первый раз встречается :
	int counter = 0;
	for (const auto& elem : theApp.NodeList.Name){
		int k = buffer.Mid(i + 1, pos - 1 - i).Find(elem);
			if (k != -1) {
				break;
			}
		counter++;
	}
	for (const auto& elem : theApp.NodeList.DocName) {
		if (counter == 0) {
			SetName(elem);
			break;
		}
		counter--;
	}
	return pos;
}
void CPlan::This_WeekFunc(const CString &buffer) {
	SetThis_Week(buffer);
}
void CPlan::Next_WeekFunc(const CString &buffer) {
	SetNext_Week(buffer);
}

 CInfo CInfo::makeList(CString &config) {
	std::ifstream NameConfig(config);
	std::string line;
	int Type = 0;
	if (NameConfig.is_open()) {
		while (getline(NameConfig, line)) {
			switch (Type) {
			case 1: {
				CString it(line.c_str());
				this->ThisWeek.push_back(it);
				break;
			}
			case 2: {
				CString it(line.c_str());
				this->NextWeek.push_back(it);
				break;
			}
			case 3: {
				CString it(line.c_str());
				this->Name.push_back(it);
				break;
			}
			case 4: {
				CString it(line.c_str());
				this->DocName.push_back(it);
				break;
			}
			default:
				break;
			}
			if (line == "@@Эта неделя") {
				Type = 1;
			}
			else if (line == "@@Следующая неделя") {
				Type  = 2;
			}
			else if (line == "@@Имена") {
				Type = 3;
			}
			else if (line == "@@Имена в отчет") {
				Type = 4;
			}
			else continue;
		}
	}
	return *this;
}

CData::CData(){
	struct tm nowtime;
	time_t t = time(NULL);
	localtime_s(&nowtime, &t);
	Day = nowtime.tm_mday;
	Month = (nowtime.tm_mon + 1);
}

CString CData::MakeThisWeek() {
	CString D1, D2, Mon1, Mon2;
	int k;
	if (Month == 1 || Month == 3 || Month == 5 || Month == 7 || Month == 8 || Month == 10 || Month == 12) {
		k = 31;
	}
	else if(Month ==2){
		k = 28;
	}
	else {
		k=30;
	}
	if ((Day - 4) < 1) {
		D1.Format(L"%d", Day+k-4);
		Mon1.Format(L"%d", Month-1);
	}
	else {
		D1.Format(L"%d", Day - 4);
		Mon1.Format(L"%d", Month);
	}
	D2.Format(L"%d", Day);
	Mon2.Format(L"%d", Month);
	TW = D1 + L"." + Mon1 + ' ' + '-' + ' ' + D2 + '.' + Mon2;
	return TW;
}
CString CData::MakeNextWeek() {
	CString D1, D2, Mon1, Mon2;
	int k;
	if (Month == 1 || Month == 3 || Month == 5 || Month == 7 || Month == 8 || Month == 10 || Month == 12) {
		k = 31;
	}
	else if (Month == 2) {
		k = 28;
	}
	else {
		k = 30;
	}
	if ((Day + 3) > k) {
		D1.Format(L"%d", Day - k + 3);
		Mon1.Format(L"%d", Month + 1);

	}
	else {
		D1.Format(L"%d", Day + 3);
		Mon1.Format(L"%d", Month);
	}
	if ((Day + 7) > k) {
		D2.Format(L"%d", Day - k + 7);
		Mon2.Format(L"%d", Month + 1);

	}
	else {
		D2.Format(L"%d", Day + 7);
		Mon2.Format(L"%d", Month);
	}
	NW = D1 + L"." + Mon1 + ' ' + '-' + ' ' + D2 + '.' + Mon2;
	return NW;
}
