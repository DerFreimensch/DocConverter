
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
	const int pos = buffer.Find('@', i+1); // поиск места где первый раз встречается :
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
	m_tw1 = L"На этой неделе";
	m_tw2 = L"Эта неделя";
	m_tw3 = L"эта неделя";
	m_tw4 = L"Эта";
}
c_m_nextWeek::c_m_nextWeek() {
	m_nw1 = L"Следующая неделя";
	m_nw2 = L"На следующей неделе";
	m_nw3 = L"След. неделя";
	m_nw4 = L"След.нeделя";
	m_nw5 = L"След.Неделя";
	m_nw6 = L"След неделя";
	m_nw7 = L"На след. неделе";
	m_nw8 = L"след. неделя";
	m_nw9 = L"Следующая";
}
c_m_Worker::c_m_Worker() {
	m_w1 = L"Настя КИТ Норина";
	m_w2 = L"Игорь КИТ Ефимов";
	m_w3 = L"Борис КИТ Рубинштейн";
	m_w4 = L"Роман КИТ Арнольд";
	m_w5 = L"Наташа КИТ Чубарова";
	m_w6 = L"Алексей Кит Романов";
	m_w7 = L"Дмитрий КИТ Городжий";
	m_w8 = L"Вадим КИТ Бородуля";
	m_w9 = L"Юра Глазырин";
	m_w10 = L"Сергей Григорьев";
	m_w11 = L"Алексей КИТ Пузанов";
	m_w12= L"Степан КИТ Загосткин";
	m_w13 = L"Антон КИТ Падалко";
	m_w14 = L"Сергей КИТ Поздникин";
	m_w15 = L"Герасимов Андрей";
	m_w16 = L"Марков Константин";
}
c_m_WorkerPres::c_m_WorkerPres() {
	m_wp1 = L"Норина Анастасия";
	m_wp2 = L"Ефимов Игорь";
	m_wp3 = L"Рубинштейн Борис";
	m_wp4 = L"Арнольд Роман";
	m_wp5 = L"Чубарова Наталья";
	m_wp6 = L"Романов Алексей";
	m_wp7 = L"Городжий Дмитрий";
	m_wp8 = L"Бородуля Вадим";
	m_wp9 = L"Глазырин Юрий";
	m_wp10 = L"Григорьев Сергей";
	m_wp11 = L"Пузанов Алексей";
	m_wp12 = L"Загосткин Степан";
	m_wp13 = L"Падалко Антон";
	m_wp14 = L"Поздникин Сергей";
	m_wp15 = L"Герасимов Андрей";
	m_wp16 = L"Марков Константин";
}

