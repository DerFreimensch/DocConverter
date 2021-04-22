
#include "pch.h"
#include <string>
#include <iostream>
#include "DocConverter.h"


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
	m_thisWeek.Empty();
	m_thisWeek = buffer;
}
void CPlan::SetNext_Week(const CString &buffer) {
	m_nextWeek.Empty();
	m_nextWeek = buffer;
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
	const int pos = buffer.Find(':', i+1); // ����� ����� ��� ������ ��� ����������� :
	if (pos != -1){
		SetName(buffer.Mid(i+1, pos - i -1)); // ������ �� �������� ���������+1 �� ���������� -1
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
}

