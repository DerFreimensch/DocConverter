
#include "pch.h"
#include <string>
#include <iostream>
#include "DocConverter.h"
#include <ctime>


CPlan::CPlan() {
	m_name = L"";
	m_thisWeek = L"";
	m_nextWeek = L"";
}
void CPlan::Readinto(const CString &buffer) {
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
	const int pos = buffer.Find('@', i+1); // ����� ����� ��� ������ ��� ����������� :
	int counter = 0;
	for (const auto& elem : theApp.m_arrWorker){
		int k = buffer.Mid(i + 1, pos - 1 - i).Find(elem);
			if (k != -1) {
				break;
			}
		counter++;
	}
	for (const auto& elem : theApp.m_arrWorkerPres) {
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
c_m_thisWeek::c_m_thisWeek() {
	m_tw1 = L"�� ���� ������";
	m_tw2 = L"��� ������";
	m_tw3 = L"��� ������";
	m_tw4 = L"���";
}
c_m_nextWeek::c_m_nextWeek() {
	m_nw1 = L"��������� ������";
	m_nw2 = L"�� ��������� ������";
	m_nw3 = L"����. ������";
	m_nw4 = L"����.������";
	m_nw5 = L"����.������";
	m_nw6 = L"���� ������";
	m_nw7 = L"�� ����. ������";
	m_nw8 = L"����. ������";
	m_nw9 = L"���������";
}
c_m_Worker::c_m_Worker() {
	m_w2 = L"����� ��� ������";
	m_w3 = L"����� ��� ����������";
	m_w4 = L"����� ��� �������";
	m_w5 = L"������ ��� ��������";
	m_w6 = L"������� ��� �������";
	m_w7 = L"������� ��� ��������";
	m_w8 = L"����� ��� ��������";
	m_w9 = L"��� ��������";
	m_w11 = L"������� ��� �������";
	m_w12= L"������ ��� ���������";
	m_w13 = L"����� ��� �������";
	m_w14 = L"������ ��� ���������";
	m_w15 = L"��������� ������";
	m_w16 = L"������ ����������";
}
c_m_WorkerPres::c_m_WorkerPres() {
	m_wp2 = L"������ �����";
	m_wp3 = L"���������� �����";
	m_wp4 = L"������� �����";
	m_wp5 = L"�������� �������";
	m_wp6 = L"������� �������";
	m_wp7 = L"�������� �������";
	m_wp8 = L"�������� �����";
	m_wp9 = L"�������� ����";
	m_wp11 = L"������� �������";
	m_wp12 = L"��������� ������";
	m_wp13 = L"������� �����";
	m_wp14 = L"��������� ������";
	m_wp15 = L"��������� ������";
	m_wp16 = L"������ ����������";
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
