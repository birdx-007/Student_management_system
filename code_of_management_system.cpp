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

//配置区
int Aplusgrade = 97;//A+最低分
int Agrade = 94;//A最低分
int Aminusgrade = 90;//A-最低分
int Bplusgrade = 87;//B+最低分
int Bgrade = 84;//B最低分
int Bminusgrade = 80;//B-最低分
int Cplusgrade = 77;//C+最低分
int Cgrade = 74;//C最低分
int Cminusgrade = 70;//C-最低分
int Dplusgrade = 67;//D+最低分
int Dgrade = 64;//D最低分
int Dminusgrade = 60;//D-最低分

//类区
class Entry {//抽象类
public:
	virtual ~Entry() {}
	virtual void Print() = 0;
	static int Entrycounter;
};
int Entry::Entrycounter = 0;//静态成员初始化
class Course_info :public Entry {
public:
	Course_info(int year = 0, string term = "土用", string course = "默认课程", int credit = 0) :Year(year), Term(term), Course(course), Credit(credit) { Coursecounter++; }
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
	int Year;//学年
	string Term;//学期
	string Course;//课程名
	int Credit;//学分
};
int Course_info::Coursecounter = 0;
class Stu_info :public Course_info {
public:
	Stu_info(int year = 0, string term = "土用", string course = "默认课程", int credit = 0, string name = "鸟x", int num = 0, int session = 0) :Course_info(year, term, course, credit), Name(name), Num(num), Session(session) { Stucounter++; }
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
	static int Stucounter;//学生计数器
protected:
	string Name;//名字
	int Num;//学号
	int Session;//毕业年
};
int Stu_info::Stucounter = 0;
class Grade_info :public Stu_info {
public:
	Grade_info(int year = 0, string term = "土用", string course = "默认课程", int credit = 0, string name = "鸟x", int num = 0, int session = 0, int grade = 0) :Stu_info(year,term, course, credit, name, num,session), Grade(grade), Level(this->Level_from_Grade(grade)),isFailed(this->Level_from_Grade(grade)=="F") {
		Entrycounter++; Gradecounter++;
		//cout << "√" << endl;
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
	bool isFailed;//是否不及格
private:
	int Grade;//成绩
	string Level;//等级
};
int Grade_info::Gradecounter = 0;
class Menu {
public:
	void Config_menu() {//预配置菜单
		system("cls");
		cout << "——学生成绩管理系统——" << endl << "———配置设置界面———" << endl;
		this->file.open("config.dat", ios_base::in | ios_base::binary);
		if (!file) {//配置文件不存在
			cout << "未检测到配置文件存在！是否启用默认配置？（选否则需要在本菜单自行输入配置）" << endl;
			cout << "是：请输入1以外的其他键" << endl << "否：请输入1" << endl;
			cout << endl << "注：默认配置说明" << endl;
			cout << "成绩与等级对应表如下：" << endl << "97+  94+  90+  87+  84+  80+  77+  74+  70+  67+  64+  60+  0+" << endl;
			cout << "A+   A    A-   B+   B    B-   C+   C    C-   D+   D    D-   F" << endl << endl;
			char tmp = _getch();//用户的选择
			cout << tmp << endl;
			if (tmp == '1') {//选择手动添加配置
				this->file.close();
				this->file.open("config.dat", ios_base::out | ios_base::trunc | ios_base::binary);
				cout << "手动设置配置" << endl;
				cout << "依次输入等级对应的您希望的成绩：（整数，请按照默认配置提示中的顺序输入，用空格分割）（无需输入F等级对应分数）" << endl;
				while(cin >> Aplusgrade >> Agrade >> Aminusgrade >> Bplusgrade >> Bgrade >> Bminusgrade >> Cplusgrade >> Cgrade >> Cminusgrade >> Dplusgrade >> Dgrade >> Dminusgrade,cin.fail()) {
					cout << "输入出错！请重试" << endl;
					cin.clear(); //清除std::cin对象的错误状态
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
				cout << "配置成功！新配置已保存到config.dat" << endl;
			}
			else if (tmp == 27) exit(0);
		}
		else {//配置文件存在
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
			cout << "检测到配置文件config.dat。是否启用该配置？（选否则需要在本菜单自行输入配置）" << endl;
			cout << "是：请输入1以外的其他键" << endl << "否：请输入1" << endl;
			cout << endl << "注：已有配置说明" << endl;
			cout << "成绩与等级对应表如下：" << endl << Aplusgrade << "+  " << Agrade << "+  " << Aminusgrade << "+  " << Bplusgrade << "+  " << Bgrade << "+  " << Bminusgrade << "+  " << Cplusgrade << "+  " << Cgrade << "+  " << Cminusgrade << "+  " << Dplusgrade << "+  " << Dgrade << "+  " << Dminusgrade << "+  0+" << endl;
			cout << "A+   A    A-   B+   B    B-   C+   C    C-   D+   D    D-   F" << endl << endl;
			char tmp = _getch();//用户的选择
			cout << tmp << endl;
			if (tmp == '1') {//选择手动配置
				this->file.close();
				this->file.open("config.dat", ios_base::out | ios_base::trunc | ios_base::binary);
				cout << "手动设置配置" << endl;
				cout << "依次输入等级对应的您希望的成绩：（整数，请按照默认配置提示中的顺序输入，用空格分割）（无需输入F等级对应分数）" << endl;
				while (cin >> Aplusgrade >> Agrade >> Aminusgrade >> Bplusgrade >> Bgrade >> Bminusgrade >> Cplusgrade >> Cgrade >> Cminusgrade >> Dplusgrade >> Dgrade >> Dminusgrade, cin.fail()) {
					cout << "输入出错！请重试" << endl;
					cin.clear(); //清除std::cin对象的错误状态
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
				cout << "配置成功！新配置已保存到config.dat" << endl;
			}
			else if (tmp == 27) exit(0);
		}
		this->file.close();
		cout << endl << "配置已完成！" << endl << "正在导入外部成绩信息..." << endl;
		Sleep(500);
		this->file.open("input.txt", ios_base::in);
		if (file) {
			int year, credit, num, grade, session;
			string term, course, name;
			while (true) {
				file >> year >> term >> course >> credit >> name >> num >> session >> grade;//这种方式要求course,name字符串中不得有空格或制表符
				if (this->file.fail()) break;//到达文件结尾退出循环
				Grade_info* tmpentry = new Grade_info(year, term, course, credit, name, num, session, grade);
				tmpentry->Print();
				this->base.push_back(*tmpentry);
				cout << "第" << this->base.size() << "条录入完毕" << endl;
			}
			cout << endl << "input.txt信息输入完毕，按任意键进入系统" << endl;
		}
		else {
			cout << endl << "警告！未找到外部信息文件input.txt，当前成绩信息条目库为空。如仍要继续，按任意键进入系统" << endl;
		}
		this->file.close();
		system("pause");
	}
	void Password_menu() {
		system("cls");
		cout << "——学生成绩管理系统——" << endl << "———密码与安全界面———" << endl;
		cout << "请选择：" << endl << "1）教务人员，请输入1" << endl << "2）学生，请输入2" << endl << endl;
		char tmp = _getch();//用户的选择
		cout << tmp << endl;
		while (tmp != '1' && tmp != '2' && tmp != 27) {
			cout << "无效，请重新输入" << endl;
			tmp = _getch();
			cout << tmp << endl;
		}
		if (tmp == 27) exit(0);
		else if (tmp == '1') {
			cout << "请输入系统密码：";
			string password;
			cin >> password;
			if (password == Password) {
				cout << "密码正确，将以教务人员身份进入..." << endl;
				isTeacher = 1;
			}
			else {
				cout << "密码错误，将以学生身份进入..." << endl;
			}
		}
		else {
			cout << "将以学生身份进入..." << endl;
		}
		Sleep(1000);
	}
	int Main_menu() {
		system("cls");
		cout << "——学生成绩管理系统——" << endl << "———主菜单———" << endl;
		cout << "1）输入新的学生成绩信息，请输入1";
		if (!isTeacher) cout << "（不可用）";
		cout << endl << "2）修改已有学生成绩信息，请输入2";
		if (!isTeacher) cout << "（不可用）";
		cout << endl << "3）删除已有学生成绩信息，请输入3";
		if (!isTeacher) cout << "（不可用）";
		cout << endl << "4）查询已有学生成绩信息，请输入4" << endl;
		cout << "5）退出系统，请按Esc键" << endl;
		char tmp = _getch();//用户的选择
		cout << tmp << endl;
		while (tmp != '1' && tmp != '2' && tmp != '3' && tmp != '4' && tmp != 27 || (tmp == '1' || tmp == '2' || tmp == '3') && !isTeacher) {
			cout << "无效，请重新输入" << endl;
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
		cout << "——学生成绩管理系统——" << endl << "———输入新条目界面———" << endl;
		cout << "请输入所需添加的条目的【学年 学期 课程 课程学分 姓名 学号 毕业年份 成绩】" << endl;
		cout << "例如：2020 秋 程序设计 2 张三 101 2024 89" << endl << endl;
		int year, credit, num, grade, session;
		string term, course, name;
		while (true) {
			cout << "按esc返回主菜单，按其他任意键继续输入" << endl;
			char tmp = _getch();//用户的选择
			if (tmp == 27) {
				cout << "终止输入" << endl;
				break;
			}
			else {
				cout << "继续输入" << endl;
			}
			while (cin >> year >> term >> course >> credit >> name >> num >> session >> grade, cin.fail()) {
				cout << "输入出错！请重试" << endl;
				cin.clear(); //清除std::cin对象的错误状态
				cin.ignore(114514, '\n');
			}
			Grade_info* tmpentry = new Grade_info(year, term, course, credit, name, num, session, grade);
			this->base.push_back(*tmpentry);
			cout << "第" << this->base.size() << "条录入完毕" << endl;
		}
	}
	void Change_menu() {
		system("cls");
		cout << "——学生成绩管理系统——" << endl << "———修改界面———" << endl;
		cout << "输入要修改的条目的【学年 学期 课程名 姓名】以进行检索：";
		int year; string term, course, name;
		while(cin >> year >> term >> course >> name,cin.fail()){
				cout << "输入出错！请重试" << endl;
				cin.clear(); //清除std::cin对象的错误状态
				cin.ignore(114514, '\n');
		}
		class isEqual {//仿函数
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
		int itcounter = 0;//计数检索到的条目
		while (it != this->base.end()) {
			itcounter++;
			it->Print();
			cout << "检索到第" << itcounter << "条符合条件的条目。这是否是需要被修改的条目？" << endl;
			cout << "1）是，请按1\t2）不是，请按2" << endl;
			char tmp = _getch();//用户的选择
			while (tmp != '1' && tmp != '2' && tmp != 27) {
				cout << "无效，请重新输入" << endl;
				tmp = _getch();
			}
			if (tmp == '1') {
				cout << "请输入此条目修改后的【课程学分 学号 毕业年份 成绩】" << endl;
				int credit0, num0, grade0, session0;
				while(cin >>credit0 >>num0 >> session0 >> grade0,cin.fail()){
				cout << "输入出错！请重试" << endl;
				cin.clear(); //清除std::cin对象的错误状态
				cin.ignore(114514, '\n');
				}
				it->Set(year, term, course, credit0, name, num0, session0, grade0);
				cout << "修改完毕，结果如下" << endl;
				it->Print();
				cout << "按任意键返回主菜单" << endl;
				system("pause");
				break;
			}
			else if (tmp == '2') {
				cout << "继续检索中..." << endl;
				it = find_if(it + 1, this->base.end(), isEqual(year, term, course, name));
				if (it == this->base.end()) {
					cout << "没有更多符合条件的条目！按任意键返回主菜单" << endl;
					system("pause");
				}
			}
		}
		if (itcounter == 0) {//未检索到
			cout << endl << "未检索到符合条件的条目！按任意键返回主菜单" << endl;
			system("pause");
		}
	}
	void Delete_menu() {
		system("cls");
		cout << "——学生成绩管理系统——" << endl << "———删除界面———" << endl;
		cout << "输入要删除的条目的【学年 学期 课程名 姓名】以进行检索：";
		int year; string term, course, name;
		while(cin >> year >> term >> course >> name,cin.fail()){
				cout << "输入出错！请重试" << endl;
				cin.clear(); //清除std::cin对象的错误状态
				cin.ignore(114514, '\n');
		}
		class isEqual {//仿函数
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
		int itcounter = 0;//计数检索到的条目
		while (it != this->base.end()) {
			itcounter++;
			it->Print();
			cout << "检索到第" << itcounter << "条符合条件的条目。这是否是需要被删除的条目？" << endl;
			cout << "1）是，请按1\t2）不是，请按2" << endl;
			char tmp = _getch();//用户的选择
			while (tmp != '1' && tmp != '2' && tmp != 27) {
				cout << "无效，请重新输入" << endl;
				tmp = _getch();
			}
			if (tmp == '1') {
				it=this->base.erase(it);
				cout << "删除完毕" << endl << "按任意键返回主菜单" << endl;
				system("pause");
				break;
			}
			else if (tmp == '2') {
				cout << "继续检索中..." << endl;
				it = find_if(it + 1, this->base.end(), isEqual(year, term, course, name));
				if (it == this->base.end()) {
					cout << "没有更多符合条件的条目！按任意键返回主菜单" << endl;
					system("pause");
				}
			}
		}
		if (itcounter == 0) {//未检索到
			cout << endl << "未检索到符合条件的条目！按任意键返回主菜单" << endl;
			system("pause");
		}
	}
	void Search_menu() {
		system("cls");
		cout << "——学生成绩管理系统——" << endl << "———查询界面———" << endl;
		cout << "选择查询模式：" << endl;
		cout << "1）查询某学生成绩信息，请按1" << endl;
		cout << "2）查询某课程相关成绩信息，请按2" << endl;
		char tmp = _getch();//用户的选择
		cout << tmp << endl;
		while (tmp != '1' && tmp != '2' && tmp != 27) {
			cout << "无效，请重新输入" << endl;
			tmp = _getch();
			cout << tmp << endl;
		}
		if (tmp == '1') {
			cout << endl << "——查询某学生成绩信息——" << endl;
			cout << "输入要查询的条目的【姓名 学号】以进行检索：";
			int avergrade = 0;//平均成绩
			int num; string name;
			while(cin >>name>>num,cin.fail()){
				cout << "输入出错！请重试" << endl;
				cin.clear(); //清除std::cin对象的错误状态
				cin.ignore(114514, '\n');
			}
			class isEqual {//仿函数
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
			vector<Grade_info> list;//存放查询结果
			int gradecounter = 0;//总成绩
			int itcounter = 0;//计数检索到的条目
			while (it != this->base.end()) {
				itcounter++;
				list.push_back(*it);
				it = find_if(it + 1, this->base.end(), isEqual(num, name));
			}
			if (itcounter == 0) {//未检索到
				cout << endl << "未检索到符合条件的条目！按任意键返回主菜单" << endl;
				system("pause");
			}
			else {
				cout << "查询结果如下：" << endl<<endl;
				class Compare {//仿函数
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
				cout << endl << "平均分：" << avergrade << " 平均等级："<<averlevel<<endl;
				file<< endl << "平均分：" << avergrade << " 平均等级：" << averlevel << endl;
				this->file.close();
				cout << endl << "查询结果展示完毕并已输出到文件output_searchstu.txt！按任意键返回主菜单" << endl;
				system("pause");
			}
		}
		else if (tmp == '2'){
			cout << endl << "——查询某课程相关成绩信息——" << endl;
			cout << "输入要查询的条目的【学年 学期 课程名】以进行检索：";
			int avergrade;//平均分
			int year; string term,course;
			while(cin >> year >> term>>course,cin.fail()){
				cout << "输入出错！请重试" << endl;
				cin.clear(); //清除std::cin对象的错误状态
				cin.ignore(114514, '\n');
			}
			class isEqual {//仿函数
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
			vector<Grade_info> list;//存放查询结果
			int gradecounter = 0;//总成绩
			int itcounter = 0;//计数检索到的条目
			while (it != this->base.end()) {
				itcounter++;
				list.push_back(*it);
				it = find_if(it + 1, this->base.end(), isEqual(year, term, course));
			}
			if (itcounter == 0) {//未检索到
				cout << endl << "未检索到符合条件的条目！按任意键返回主菜单" << endl;
				system("pause");
			}
			else {
				cout << "查询结果如下：" << endl << endl;
				class Compare {//仿函数
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
				cout << endl << "平均分：" << avergrade << " 平均等级：" << averlevel << endl;
				file << endl << "平均分：" << avergrade << " 平均等级：" << averlevel << endl;
				this->file.close();
				cout << endl << "查询结果展示完毕并已输出到文件output_searchcourse.txt！按任意键返回主菜单" << endl;
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
		cout << "全学生成绩信息已输出至output.txt！欢迎再次使用！" << endl;
	}
private:
	vector<Grade_info> base;//条目库
	string Password = "tsinghuaedu2021birdx";//系统密码
	bool isTeacher = 0;//是否为教务人员
	fstream file;//对外文件接口
}body;

//主函数
int main() {
	cout << setiosflags(ios_base::left);//标准输出左对齐
	//预配置
	body.Config_menu();
	//密码与安全设置
	body.Password_menu();
	//主体
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
//抽象类为Entry（条目），派生其余类√
//初次打开可以输入配置并存入文件，以后打开则询问是否使用上次配置√
//最终派生类Grade_info的成员有：学年year，学期term，课程course，课程学分credit，姓名name，学号num，毕业年份session，成绩grade，等级level√
//程序使用时一律使用Entry指针指向派生类对象×因使用vector而非基类数组构造条目库，条目vector类型必须可实例化
//根据修改、删除、查询时的输入操作，制定中间派生类层次如下：
//Entry->Course_info->Stu_info->Grade_info√
//非抽象基类成员为确保成员对派生类可见，权限应控制为protected；Grade_info类成员为private√

//发现问题：每次进入程序都要重新输入，很麻烦
//主菜单第一选项应为“用键盘追加写”，从已有文件输入的功能应在配置时即已完成
//同时系统退出时追加和修改的条目应输出到原来的文件
//已解决√

//发现问题：配置菜单工作时一旦文件存在则不能更新
//需要重新调整文件接口，计划放入Menu类中
//已解决√