#include <iostream>
#include <limits>
#include <iomanip>
#include <fstream>
#include <stdio.h>
#include <conio.h>
#include <Windows.h>
#include <iterator>
#include <algorithm>
#include <functional>
#include <vector>
using namespace std;

//������
int Aplusgrade = 97;//A+��ͷ�
int Agrade = 94;//A��ͷ�
int Aminusgrade = 90;//A-��ͷ�
int Bplusgrade = 87;//B+��ͷ�
int Bgrade = 84;//B��ͷ�
int Bminusgrade = 80;//B-��ͷ�
int Cplusgrade = 77;//C+��ͷ�
int Cgrade = 74;//C��ͷ�
int Cminusgrade = 70;//C-��ͷ�
int Dplusgrade = 67;//D+��ͷ�
int Dgrade = 64;//D��ͷ�
int Dminusgrade = 60;//D-��ͷ�

//����
class Entry {//������
public:
	virtual ~Entry() {}
	virtual void Print() = 0;
	static int Entrycounter;
};
int Entry::Entrycounter = 0;//��̬��Ա��ʼ��
class Course_info :public Entry {
public:
	Course_info(int year = 0, string term = "����", string course = "Ĭ�Ͽγ�", int credit = 0) :Year(year), Term(term), Course(course), Credit(credit) { Coursecounter++; }
	Course_info(const Course_info&x):Year(x.Year), Term(x.Term), Course(x.Course), Credit(x.Credit) { Coursecounter++; }
	virtual ~Course_info() { Coursecounter--; }
	virtual void Print() {
		cout << setw(5) << Year <<setw(3)<<Term<< setw(16) << Course << setw(2) << Credit << endl;
	}
	void Set(int year,string term, string course, int credit) {
		Year = year;
		Term = term;
		Course = course;
		Credit = credit;
	}
	int GetYear() { return Year; }
	string GetTerm() { return Term; }
	string GetCourse() { return Course; }
	int GetCredit() { return Credit; }
	static int Coursecounter;
protected:
	int Year;//ѧ��
	string Term;//ѧ��
	string Course;//�γ���
	int Credit;//ѧ��
};
int Course_info::Coursecounter = 0;
class Stu_info :public Course_info {
public:
	Stu_info(int year = 0, string term = "����", string course = "Ĭ�Ͽγ�", int credit = 0, string name = "��x", int num = 0, int session = 0) :Course_info(year, term, course, credit), Name(name), Num(num), Session(session) { Stucounter++; }
	Stu_info(const Stu_info& x) :Course_info(x), Name(x.Name), Num(x.Num), Session(x.Session) { Stucounter++; }
	virtual ~Stu_info() { Stucounter--; }
	virtual void Print() {
		cout << setw(5) << Year << setw(3) << Term << setw(16) << Course << setw(2) << Credit << setw(8) << Name << setw(10) << Num <<setw(5)<<Session<< endl;
	}
	void Set(int year, string term,string course, int credit, string name, int num,int session) {
		Course_info::Set(year,term, course, credit);
		Name = name;
		Num = num;
		Session = session;
	}
	string GetName() { return Name; }
	int GetNum() { return Num; }
	int GetSession() { return Session; }
	static int Stucounter;//ѧ��������
protected:
	string Name;//����
	int Num;//ѧ��
	int Session;//��ҵ��
};
int Stu_info::Stucounter = 0;
class Grade_info :public Stu_info {
public:
	Grade_info(int year = 0, string term = "����", string course = "Ĭ�Ͽγ�", int credit = 0, string name = "��x", int num = 0, int session = 0, int grade = 0) :Stu_info(year,term, course, credit, name, num,session), Grade(grade), Level(this->Level_from_Grade(grade)),isFailed(this->Level_from_Grade(grade)=="F") {
		Entrycounter++; Gradecounter++;
		//cout << "��" << endl;
	}
	Grade_info(const Grade_info& x) :Stu_info(x), Grade(x.Grade), Level(x.Level), isFailed(x.isFailed) {
		Entrycounter++; Gradecounter++;
	}
	virtual ~Grade_info() {
		Entrycounter--; Gradecounter--;
	}
	virtual void Print() {
		if(isFailed) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
		cout << setw(5) << Year << setw(3) << Term << setw(20) << Course << setw(2) << Credit << setw(8) << Name << setw(10) << Num << setw(5) << Session << setw(3) << Grade << setw(3) << Level << endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	}
	static string Level_from_Grade(int grade) {
		if (grade >= Aplusgrade) return "A+";
		else if (grade >= Agrade) return "A";
		else if (grade >= Aminusgrade) return "A-";
		else if (grade >= Bplusgrade) return "B+";
		else if (grade >= Bgrade) return "B";
		else if (grade >= Bminusgrade) return "B-";
		else if (grade >= Cplusgrade) return "C+";
		else if (grade >= Cgrade) return "C";
		else if (grade >= Cminusgrade) return "C-";
		else if (grade >= Dplusgrade) return "D+";
		else if (grade >= Dgrade) return "D";
		else if (grade >= Dminusgrade) return "D-";
		else return "F";
	}
	void Set(int year, string term, string course, int credit, string name, int num, int session, int grade) {
		Stu_info::Set(year, term,course, credit, name, num,session);
		Grade = grade;
		Level = this->Level_from_Grade(grade);
		isFailed = (Level == "F");
	}
	int GetGrade() { return Grade; }
	string GetLevel() { return Level; }
	static int Gradecounter;
	bool isFailed;//�Ƿ񲻼���
private:
	int Grade;//�ɼ�
	string Level;//�ȼ�
};
int Grade_info::Gradecounter = 0;
class Menu {
public:
	void Config_menu() {//Ԥ���ò˵�
		system("cls");
		cout << "����ѧ���ɼ�����ϵͳ����" << endl << "�������������ý��桪����" << endl;
		this->file.open("config.dat", ios_base::in | ios_base::binary);
		if (!file) {//�����ļ�������
			cout << "δ��⵽�����ļ����ڣ��Ƿ�����Ĭ�����ã���ѡ������Ҫ�ڱ��˵������������ã�" << endl;
			cout << "�ǣ�������1�����������" << endl << "��������1" << endl;
			cout << endl << "ע��Ĭ������˵��" << endl;
			cout << "�ɼ���ȼ���Ӧ�����£�" << endl << "97+  94+  90+  87+  84+  80+  77+  74+  70+  67+  64+  60+  0+" << endl;
			cout << "A+   A    A-   B+   B    B-   C+   C    C-   D+   D    D-   F" << endl << endl;
			char tmp = _getch();//�û���ѡ��
			cout << tmp << endl;
			if (tmp == '1') {//ѡ���ֶ��������
				this->file.close();
				this->file.open("config.dat", ios_base::out | ios_base::trunc | ios_base::binary);
				cout << "�ֶ���������" << endl;
				cout << "��������ȼ���Ӧ����ϣ���ĳɼ������������밴��Ĭ��������ʾ�е�˳�����룬�ÿո�ָ����������F�ȼ���Ӧ������" << endl;
				while(cin >> Aplusgrade >> Agrade >> Aminusgrade >> Bplusgrade >> Bgrade >> Bminusgrade >> Cplusgrade >> Cgrade >> Cminusgrade >> Dplusgrade >> Dgrade >> Dminusgrade,cin.fail()) {
					cout << "�������������" << endl;
					cin.clear(); //���std::cin����Ĵ���״̬
					cin.ignore(114514, '\n');
				}
				this->file.write((char*)&Aplusgrade, sizeof Aplusgrade);
				this->file.write((char*)&Agrade, sizeof Agrade);
				this->file.write((char*)&Aminusgrade, sizeof Aminusgrade);
				this->file.write((char*)&Bplusgrade, sizeof Bplusgrade);
				this->file.write((char*)&Bgrade, sizeof Bgrade);
				this->file.write((char*)&Bminusgrade, sizeof Bminusgrade);
				this->file.write((char*)&Cplusgrade, sizeof Cplusgrade);
				this->file.write((char*)&Cgrade, sizeof Cgrade);
				this->file.write((char*)&Cminusgrade, sizeof Cminusgrade);
				this->file.write((char*)&Dplusgrade, sizeof Dplusgrade);
				this->file.write((char*)&Dgrade, sizeof Dgrade);
				this->file.write((char*)&Dminusgrade, sizeof Dminusgrade);
				cout << "���óɹ����������ѱ��浽config.dat" << endl;
			}
			else if (tmp == 27) exit(0);
		}
		else {//�����ļ�����
			this->file.read((char*)&Aplusgrade, sizeof Aplusgrade);
			this->file.read((char*)&Agrade, sizeof Agrade);
			this->file.read((char*)&Aminusgrade, sizeof Aminusgrade);
			this->file.read((char*)&Bplusgrade, sizeof Bplusgrade);
			this->file.read((char*)&Bgrade, sizeof Bgrade);
			this->file.read((char*)&Bminusgrade, sizeof Bminusgrade);
			this->file.read((char*)&Cplusgrade, sizeof Cplusgrade);
			this->file.read((char*)&Cgrade, sizeof Cgrade);
			this->file.read((char*)&Cminusgrade, sizeof Cminusgrade);
			this->file.read((char*)&Dplusgrade, sizeof Dplusgrade);
			this->file.read((char*)&Dgrade, sizeof Dgrade);
			this->file.read((char*)&Dminusgrade, sizeof Dminusgrade);
			cout << "��⵽�����ļ�config.dat���Ƿ����ø����ã���ѡ������Ҫ�ڱ��˵������������ã�" << endl;
			cout << "�ǣ�������1�����������" << endl << "��������1" << endl;
			cout << endl << "ע����������˵��" << endl;
			cout << "�ɼ���ȼ���Ӧ�����£�" << endl << Aplusgrade << "+  " << Agrade << "+  " << Aminusgrade << "+  " << Bplusgrade << "+  " << Bgrade << "+  " << Bminusgrade << "+  " << Cplusgrade << "+  " << Cgrade << "+  " << Cminusgrade << "+  " << Dplusgrade << "+  " << Dgrade << "+  " << Dminusgrade << "+  0+" << endl;
			cout << "A+   A    A-   B+   B    B-   C+   C    C-   D+   D    D-   F" << endl << endl;
			char tmp = _getch();//�û���ѡ��
			cout << tmp << endl;
			if (tmp == '1') {//ѡ���ֶ�����
				this->file.close();
				this->file.open("config.dat", ios_base::out | ios_base::trunc | ios_base::binary);
				cout << "�ֶ���������" << endl;
				cout << "��������ȼ���Ӧ����ϣ���ĳɼ������������밴��Ĭ��������ʾ�е�˳�����룬�ÿո�ָ����������F�ȼ���Ӧ������" << endl;
				while (cin >> Aplusgrade >> Agrade >> Aminusgrade >> Bplusgrade >> Bgrade >> Bminusgrade >> Cplusgrade >> Cgrade >> Cminusgrade >> Dplusgrade >> Dgrade >> Dminusgrade, cin.fail()) {
					cout << "�������������" << endl;
					cin.clear(); //���std::cin����Ĵ���״̬
					cin.ignore(114514, '\n');
				}
				this->file.write((char*)&Aplusgrade, sizeof Aplusgrade);
				this->file.write((char*)&Agrade, sizeof Agrade);
				this->file.write((char*)&Aminusgrade, sizeof Aminusgrade);
				this->file.write((char*)&Bplusgrade, sizeof Bplusgrade);
				this->file.write((char*)&Bgrade, sizeof Bgrade);
				this->file.write((char*)&Bminusgrade, sizeof Bminusgrade);
				this->file.write((char*)&Cplusgrade, sizeof Cplusgrade);
				this->file.write((char*)&Cgrade, sizeof Cgrade);
				this->file.write((char*)&Cminusgrade, sizeof Cminusgrade);
				this->file.write((char*)&Dplusgrade, sizeof Dplusgrade);
				this->file.write((char*)&Dgrade, sizeof Dgrade);
				this->file.write((char*)&Dminusgrade, sizeof Dminusgrade);
				cout << "���óɹ����������ѱ��浽config.dat" << endl;
			}
			else if (tmp == 27) exit(0);
		}
		this->file.close();
		cout << endl << "��������ɣ�" << endl << "���ڵ����ⲿ�ɼ���Ϣ..." << endl;
		Sleep(500);
		this->file.open("input.txt", ios_base::in);
		if (file) {
			int year, credit, num, grade, session;
			string term, course, name;
			while (true) {
				file >> year >> term >> course >> credit >> name >> num >> session >> grade;//���ַ�ʽҪ��course,name�ַ����в����пո���Ʊ��
				if (this->file.fail()) break;//�����ļ���β�˳�ѭ��
				Grade_info* tmpentry = new Grade_info(year, term, course, credit, name, num, session, grade);
				tmpentry->Print();
				this->base.push_back(*tmpentry);
				cout << "��" << this->base.size() << "��¼�����" << endl;
			}
			cout << endl << "input.txt��Ϣ������ϣ������������ϵͳ" << endl;
		}
		else {
			cout << endl << "���棡δ�ҵ��ⲿ��Ϣ�ļ�input.txt����ǰ�ɼ���Ϣ��Ŀ��Ϊ�ա�����Ҫ�����������������ϵͳ" << endl;
		}
		this->file.close();
		system("pause");
	}
	void Password_menu() {
		system("cls");
		cout << "����ѧ���ɼ�����ϵͳ����" << endl << "�����������밲ȫ���桪����" << endl;
		cout << "��ѡ��" << endl << "1��������Ա��������1" << endl << "2��ѧ����������2" << endl << endl;
		char tmp = _getch();//�û���ѡ��
		cout << tmp << endl;
		while (tmp != '1' && tmp != '2' && tmp != 27) {
			cout << "��Ч������������" << endl;
			tmp = _getch();
			cout << tmp << endl;
		}
		if (tmp == 27) exit(0);
		else if (tmp == '1') {
			cout << "������ϵͳ���룺";
			string password;
			cin >> password;
			if (password == Password) {
				cout << "������ȷ�����Խ�����Ա��ݽ���..." << endl;
				isTeacher = 1;
			}
			else {
				cout << "������󣬽���ѧ����ݽ���..." << endl;
			}
		}
		else {
			cout << "����ѧ����ݽ���..." << endl;
		}
		Sleep(1000);
	}
	int Main_menu() {
		system("cls");
		cout << "����ѧ���ɼ�����ϵͳ����" << endl << "���������˵�������" << endl;
		cout << "1�������µ�ѧ���ɼ���Ϣ��������1";
		if (!isTeacher) cout << "�������ã�";
		cout << endl << "2���޸�����ѧ���ɼ���Ϣ��������2";
		if (!isTeacher) cout << "�������ã�";
		cout << endl << "3��ɾ������ѧ���ɼ���Ϣ��������3";
		if (!isTeacher) cout << "�������ã�";
		cout << endl << "4����ѯ����ѧ���ɼ���Ϣ��������4" << endl;
		cout << "5���˳�ϵͳ���밴Esc��" << endl;
		char tmp = _getch();//�û���ѡ��
		cout << tmp << endl;
		while (tmp != '1' && tmp != '2' && tmp != '3' && tmp != '4' && tmp != 27 || (tmp == '1' || tmp == '2' || tmp == '3') && !isTeacher) {
			cout << "��Ч������������" << endl;
			tmp = _getch();
			cout << tmp << endl;
		}
		if (tmp == '1') return 1;
		else if (tmp == '2') return 2;
		else if (tmp == '3') return 3;
		else if (tmp == '4') return 4;
		else exit(0);
	}
	void Input_menu() {
		system("cls");
		cout << "����ѧ���ɼ�����ϵͳ����" << endl << "��������������Ŀ���桪����" << endl;
		cout << "������������ӵ���Ŀ�ġ�ѧ�� ѧ�� �γ� �γ�ѧ�� ���� ѧ�� ��ҵ��� �ɼ���" << endl;
		cout << "���磺2020 �� ������� 2 ���� 101 2024 89" << endl << endl;
		int year, credit, num, grade, session;
		string term, course, name;
		while (true) {
			cout << "��esc�������˵����������������������" << endl;
			char tmp = _getch();//�û���ѡ��
			if (tmp == 27) {
				cout << "��ֹ����" << endl;
				break;
			}
			else {
				cout << "��������" << endl;
			}
			while (cin >> year >> term >> course >> credit >> name >> num >> session >> grade, cin.fail()) {
				cout << "�������������" << endl;
				cin.clear(); //���std::cin����Ĵ���״̬
				cin.ignore(114514, '\n');
			}
			Grade_info* tmpentry = new Grade_info(year, term, course, credit, name, num, session, grade);
			this->base.push_back(*tmpentry);
			cout << "��" << this->base.size() << "��¼�����" << endl;
		}
	}
	void Change_menu() {
		system("cls");
		cout << "����ѧ���ɼ�����ϵͳ����" << endl << "�������޸Ľ��桪����" << endl;
		cout << "����Ҫ�޸ĵ���Ŀ�ġ�ѧ�� ѧ�� �γ��� �������Խ��м�����";
		int year; string term, course, name;
		while(cin >> year >> term >> course >> name,cin.fail()){
				cout << "�������������" << endl;
				cin.clear(); //���std::cin����Ĵ���״̬
				cin.ignore(114514, '\n');
		}
		class isEqual {//�º���
		public:
			isEqual(int year, string term, string course, string name) :Year(year), Term(term), Course(course), Name(name) {}
			bool operator()(Grade_info& x) {
				return (x.GetYear() == this->Year && x.GetTerm() == this->Term && x.GetCourse() == this->Course && x.GetName() == this->Name);
			}
		private:
			int Year;
			string Term, Course, Name;
		};
		auto it = find_if(this->base.begin(), this->base.end(), isEqual(year, term, course, name));
		int itcounter = 0;//��������������Ŀ
		while (it != this->base.end()) {
			itcounter++;
			it->Print();
			cout << "��������" << itcounter << "��������������Ŀ�����Ƿ�����Ҫ���޸ĵ���Ŀ��" << endl;
			cout << "1���ǣ��밴1\t2�����ǣ��밴2" << endl;
			char tmp = _getch();//�û���ѡ��
			while (tmp != '1' && tmp != '2' && tmp != 27) {
				cout << "��Ч������������" << endl;
				tmp = _getch();
			}
			if (tmp == '1') {
				cout << "���������Ŀ�޸ĺ�ġ��γ�ѧ�� ѧ�� ��ҵ��� �ɼ���" << endl;
				int credit0, num0, grade0, session0;
				while(cin >>credit0 >>num0 >> session0 >> grade0,cin.fail()){
				cout << "�������������" << endl;
				cin.clear(); //���std::cin����Ĵ���״̬
				cin.ignore(114514, '\n');
				}
				it->Set(year, term, course, credit0, name, num0, session0, grade0);
				cout << "�޸���ϣ��������" << endl;
				it->Print();
				cout << "��������������˵�" << endl;
				system("pause");
				break;
			}
			else if (tmp == '2') {
				cout << "����������..." << endl;
				it = find_if(it + 1, this->base.end(), isEqual(year, term, course, name));
				if (it == this->base.end()) {
					cout << "û�и��������������Ŀ����������������˵�" << endl;
					system("pause");
				}
			}
		}
		if (itcounter == 0) {//δ������
			cout << endl << "δ������������������Ŀ����������������˵�" << endl;
			system("pause");
		}
	}
	void Delete_menu() {
		system("cls");
		cout << "����ѧ���ɼ�����ϵͳ����" << endl << "������ɾ�����桪����" << endl;
		cout << "����Ҫɾ������Ŀ�ġ�ѧ�� ѧ�� �γ��� �������Խ��м�����";
		int year; string term, course, name;
		while(cin >> year >> term >> course >> name,cin.fail()){
				cout << "�������������" << endl;
				cin.clear(); //���std::cin����Ĵ���״̬
				cin.ignore(114514, '\n');
		}
		class isEqual {//�º���
		public:
			isEqual(int year, string term, string course, string name) :Year(year), Term(term), Course(course), Name(name) {}
			bool operator()(Grade_info& x) {
				return (x.GetYear() == this->Year && x.GetTerm() == this->Term && x.GetCourse() == this->Course && x.GetName() == this->Name);
			}
		private:
			int Year;
			string Term, Course, Name;
		};
		auto it = find_if(this->base.begin(), this->base.end(), isEqual(year, term, course, name));
		int itcounter = 0;//��������������Ŀ
		while (it != this->base.end()) {
			itcounter++;
			it->Print();
			cout << "��������" << itcounter << "��������������Ŀ�����Ƿ�����Ҫ��ɾ������Ŀ��" << endl;
			cout << "1���ǣ��밴1\t2�����ǣ��밴2" << endl;
			char tmp = _getch();//�û���ѡ��
			while (tmp != '1' && tmp != '2' && tmp != 27) {
				cout << "��Ч������������" << endl;
				tmp = _getch();
			}
			if (tmp == '1') {
				it=this->base.erase(it);
				cout << "ɾ�����" << endl << "��������������˵�" << endl;
				system("pause");
				break;
			}
			else if (tmp == '2') {
				cout << "����������..." << endl;
				it = find_if(it + 1, this->base.end(), isEqual(year, term, course, name));
				if (it == this->base.end()) {
					cout << "û�и��������������Ŀ����������������˵�" << endl;
					system("pause");
				}
			}
		}
		if (itcounter == 0) {//δ������
			cout << endl << "δ������������������Ŀ����������������˵�" << endl;
			system("pause");
		}
	}
	void Search_menu() {
		system("cls");
		cout << "����ѧ���ɼ�����ϵͳ����" << endl << "��������ѯ���桪����" << endl;
		cout << "ѡ���ѯģʽ��" << endl;
		cout << "1����ѯĳѧ���ɼ���Ϣ���밴1" << endl;
		cout << "2����ѯĳ�γ���سɼ���Ϣ���밴2" << endl;
		char tmp = _getch();//�û���ѡ��
		cout << tmp << endl;
		while (tmp != '1' && tmp != '2' && tmp != 27) {
			cout << "��Ч������������" << endl;
			tmp = _getch();
			cout << tmp << endl;
		}
		if (tmp == '1') {
			cout << endl << "������ѯĳѧ���ɼ���Ϣ����" << endl;
			cout << "����Ҫ��ѯ����Ŀ�ġ����� ѧ�š��Խ��м�����";
			int avergrade = 0;//ƽ���ɼ�
			int num; string name;
			while(cin >>name>>num,cin.fail()){
				cout << "�������������" << endl;
				cin.clear(); //���std::cin����Ĵ���״̬
				cin.ignore(114514, '\n');
			}
			class isEqual {//�º���
			public:
				isEqual(int num,  string name) :Num(num),  Name(name) {}
				bool operator()(Grade_info& x) {
					return (x.GetNum() == this->Num &&  x.GetName() == this->Name);
				}
			private:
				int Num;
				string Name;
			};
			auto it = find_if(this->base.begin(), this->base.end(), isEqual(num, name));
			vector<Grade_info> list;//��Ų�ѯ���
			int gradecounter = 0;//�ܳɼ�
			int itcounter = 0;//��������������Ŀ
			while (it != this->base.end()) {
				itcounter++;
				list.push_back(*it);
				it = find_if(it + 1, this->base.end(), isEqual(num, name));
			}
			if (itcounter == 0) {//δ������
				cout << endl << "δ������������������Ŀ����������������˵�" << endl;
				system("pause");
			}
			else {
				cout << "��ѯ������£�" << endl<<endl;
				class Compare {//�º���
				public:
					bool operator()(Grade_info& x, Grade_info& y) {
						if (x.GetYear() != y.GetYear())
							if (x.GetYear() < y.GetYear()) return true;
							else return false;
						else
							if (x.GetGrade() > y.GetGrade()) return true;
							else return false;
					}
				};
				sort(list.begin(), list.end(), Compare());
				this->file.open("output_searchstu.txt", ios_base::out| ios_base::trunc);
				file << setiosflags(ios_base::left);
				for (int i = 0; i < list.size(); i++) {
					gradecounter += list[i].GetGrade();
					list[i].Print();
					file << setw(5) << list[i].GetYear() << setw(3) << list[i].GetTerm() << setw(20) << list[i].GetCourse() << setw(2) << list[i].GetCredit() << setw(8) << list[i].GetName() << setw(10) << list[i].GetNum() << setw(5) << list[i].GetSession() << setw(3) << list[i].GetGrade() << setw(3) << list[i].GetLevel() << endl;
				}
				avergrade = gradecounter / itcounter;
				string averlevel = Grade_info::Level_from_Grade(avergrade);
				cout << endl << "ƽ���֣�" << avergrade << " ƽ���ȼ���"<<averlevel<<endl;
				file<< endl << "ƽ���֣�" << avergrade << " ƽ���ȼ���" << averlevel << endl;
				this->file.close();
				cout << endl << "��ѯ���չʾ��ϲ���������ļ�output_searchstu.txt����������������˵�" << endl;
				system("pause");
			}
		}
		else if (tmp == '2'){
			cout << endl << "������ѯĳ�γ���سɼ���Ϣ����" << endl;
			cout << "����Ҫ��ѯ����Ŀ�ġ�ѧ�� ѧ�� �γ������Խ��м�����";
			int avergrade;//ƽ����
			int year; string term,course;
			while(cin >> year >> term>>course,cin.fail()){
				cout << "�������������" << endl;
				cin.clear(); //���std::cin����Ĵ���״̬
				cin.ignore(114514, '\n');
			}
			class isEqual {//�º���
			public:
				isEqual(int year, string term, string course) :Year(year), Term(term),Course(course) {}
				bool operator()(Grade_info& x) {
					return (x.GetYear() == this->Year && x.GetTerm() == this->Term && x.GetCourse()==this->Course);
				}
			private:
				int Year;
				string Term;
				string Course;
			};
			auto it = find_if(this->base.begin(), this->base.end(), isEqual(year,term,course));
			vector<Grade_info> list;//��Ų�ѯ���
			int gradecounter = 0;//�ܳɼ�
			int itcounter = 0;//��������������Ŀ
			while (it != this->base.end()) {
				itcounter++;
				list.push_back(*it);
				it = find_if(it + 1, this->base.end(), isEqual(year, term, course));
			}
			if (itcounter == 0) {//δ������
				cout << endl << "δ������������������Ŀ����������������˵�" << endl;
				system("pause");
			}
			else {
				cout << "��ѯ������£�" << endl << endl;
				class Compare {//�º���
				public:
					bool operator()(Grade_info& x, Grade_info& y) {
						if (x.GetGrade() != y.GetGrade())
							if (x.GetGrade() > y.GetGrade()) return true;
							else return false;
						else 
							if (x.GetNum() < y.GetNum()) return true;
							else return false;
					}
				};
				sort(list.begin(), list.end(), Compare());
				this->file.open("output_searchcourse.txt", ios_base::out |ios_base::trunc);
				file << setiosflags(ios_base::left);
				for (int i = 0; i < list.size(); i++) {
					gradecounter+= list[i].GetGrade();
					list[i].Print();
					file << setw(5) << list[i].GetYear() << setw(3) << list[i].GetTerm() << setw(20) << list[i].GetCourse() << setw(2) << list[i].GetCredit() << setw(8) << list[i].GetName() << setw(10) << list[i].GetNum() << setw(5) << list[i].GetSession() << setw(3) << list[i].GetGrade() << setw(3) << list[i].GetLevel() << endl;
				}
				avergrade = gradecounter / itcounter;
				string averlevel = Grade_info::Level_from_Grade(avergrade);
				cout << endl << "ƽ���֣�" << avergrade << " ƽ���ȼ���" << averlevel << endl;
				file << endl << "ƽ���֣�" << avergrade << " ƽ���ȼ���" << averlevel << endl;
				this->file.close();
				cout << endl << "��ѯ���չʾ��ϲ���������ļ�output_searchcourse.txt����������������˵�" << endl;
				system("pause");
			}
		}
	}
	~Menu() {
		this->file.open("output.txt", ios_base::out | ios_base::trunc);
		file << setiosflags(ios_base::left);
		for (int i = 0; i < base.size(); i++) {
			file << base[i].GetYear() <<' '<< base[i].GetTerm() <<' '<< base[i].GetCourse() <<' '<< base[i].GetCredit() <<' '<< base[i].GetName() <<' '<< base[i].GetNum() <<' '<< base[i].GetSession() <<' '<< base[i].GetGrade() <<' '<< base[i].GetLevel() << endl;
		}
		this->file.close();
		cout << "ȫѧ���ɼ���Ϣ�������output.txt����ӭ�ٴ�ʹ�ã�" << endl;
	}
private:
	vector<Grade_info> base;//��Ŀ��
	string Password = "tsinghuaedu2021birdx";//ϵͳ����
	bool isTeacher = 0;//�Ƿ�Ϊ������Ա
	fstream file;//�����ļ��ӿ�
}body;

//������
int main() {
	cout << setiosflags(ios_base::left);//��׼��������
	//Ԥ����
	body.Config_menu();
	//�����밲ȫ����
	body.Password_menu();
	//����
	while (true) {
		int menu_choice = body.Main_menu();
		if (menu_choice == 1) body.Input_menu();
		else if (menu_choice == 2) body.Change_menu();
		else if (menu_choice == 3) body.Delete_menu();
		else if (menu_choice == 4) body.Search_menu();
	}
	return 0;
}
//IDEAS
//������ΪEntry����Ŀ���������������
//���δ򿪿����������ò������ļ����Ժ����ѯ���Ƿ�ʹ���ϴ����á�
//����������Grade_info�ĳ�Ա�У�ѧ��year��ѧ��term���γ�course���γ�ѧ��credit������name��ѧ��num����ҵ���session���ɼ�grade���ȼ�level��
//����ʹ��ʱһ��ʹ��Entryָ��ָ��������������ʹ��vector���ǻ������鹹����Ŀ�⣬��Ŀvector���ͱ����ʵ����
//�����޸ġ�ɾ������ѯʱ������������ƶ��м������������£�
//Entry->Course_info->Stu_info->Grade_info��
//�ǳ�������ԱΪȷ����Ա��������ɼ���Ȩ��Ӧ����Ϊprotected��Grade_info���ԱΪprivate��

//�������⣺ÿ�ν������Ҫ�������룬���鷳
//���˵���һѡ��ӦΪ���ü���׷��д�����������ļ�����Ĺ���Ӧ������ʱ�������
//ͬʱϵͳ�˳�ʱ׷�Ӻ��޸ĵ���ĿӦ�����ԭ�����ļ�
//�ѽ����

//�������⣺���ò˵�����ʱһ���ļ��������ܸ���
//��Ҫ���µ����ļ��ӿڣ��ƻ�����Menu����
//�ѽ����