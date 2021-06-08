#include"admin.h"
#include"globalFile.h"
#include"student.h"
#include"teacher.h"
#include<algorithm>
#include"computerRoom.h"
vector<ComputerRoom> vCom;
Manager::Manager() {

}
Manager::Manager(string name,string pwd) {
	this->m_name = name;
	this->m_Pwd = pwd;
	this->initVector();
	
	ifstream ifs;
	ifs.open(COMPUTER_FILE,ios::in);
	ComputerRoom c;
	while (ifs >> c.m_comid && ifs >> c.m_maxmum) {
		vCom.push_back(c);
	}
	cout << "当前机房数量" << vCom.size() << endl;
	ifs.close();
}
void printStudent(Student& s) {
	cout << "number:" << s.m_Id << "name:" << s.m_name << "password" << s.m_Pwd << endl;
}
void printTeacher(Teacher& t)
{
	cout << "职工号： " << t.m_EmpId << " 姓名： " << t.m_name << " 密码：" << t.m_Pwd << endl;
}
void Manager::openMenu() {
	cout << "欢迎管理员：" << this->m_name << "登录！" << endl;
	cout << "\t\t ---------------------------------\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          1.添加账号            |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          2.查看账号            |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          3.查看机房            |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          4.清空预约            |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          0.注销登录            |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t ---------------------------------\n";
	cout << "请选择您的操作： " << endl;
}
void Manager::add() {
	cout << "请输入添加账号的类型" << endl;
	cout << "1、添加学生" << endl;
	cout << "2、添加老师" << endl;
	string filename;
	string tip;
	string errorTip;
	ofstream ofs;
	int select = 0;
	cin >> select;
	if (select == 1) {
		filename = STUDENT_FILE;
		tip = "input student number";
		errorTip = "学号重复";
	}
	else {
		filename = TEACHER_FILE;
		tip = "input teacher number:";
		errorTip = "职工号重复，重新输入";

	}
	ofs.open(filename, ios::out | ios::app);
	int id;
	string name;
	string pwd;
	cout << tip << endl;
	while (true) {
		cin >> id;
		bool ret = checkRepeat(id, select);
		if (ret) {
			cout << errorTip << endl;
		}
		else
		{
			break;
		}
	}
	
	cout << "input  name" << endl;
	cin >> name;

	cout << "请输入密码： " << endl;
	cin >> pwd;

	ofs << id << " " << name << " " << pwd << " " << endl;
	cout << "添加成功" << endl;
	system("pause");
	system("cls");
	ofs.close();
	this->initVector();

}
void Manager::showPerson() {
	cout << "请选择查看内容：" << endl;
	cout << "1、查看所有学生" << endl;
	cout << "2、查看所有老师" << endl;
	int select = 0;
	cin >> select;
	if (select == 1) {
		cout << "所有学生信息如下： " << endl;
		for_each(vstu.begin(), vstu.end(), printStudent);
	}
	else 
	{
			cout << "所有老师信息如下： " << endl;
			for_each(vtea.begin(), vtea.end(), printTeacher);
	}
	system("pause");
	system("cls");
	
}
void Manager::showComputer() {
	cout << "机房信息如下： " << endl;
	for (vector<ComputerRoom>::iterator it = vCom.begin(); it != vCom.end();it++) {
		cout << "机房编号： " << it->m_comid << " 机房最大容量： " << it->m_maxmum << endl;
	}
	system("pause");
	system("cls");
}
void Manager::cleanFile() {
	ofstream ofs(ORDER_FILE, ios::trunc);
	ofs.close();
	cout << "清空成功" << endl;
	system("pause");
	system("cls");
}
void Manager::initVector() {
	ifstream ifs;
	ifs.open(STUDENT_FILE, ios::in);
	if (!ifs.is_open()) {
		cout << "file read failed" << endl;
		return;
	}
	vstu.clear();
	vtea.clear();
	Student s;
	while (ifs >> s.m_Id && ifs >> s.m_name && ifs >> s.m_Pwd) {
		vstu.push_back(s);
	}
	cout << "the number of studnet is" << vstu.size() << endl;
	ifs.close();
	Teacher t;
	while (ifs >> t.m_EmpId && ifs >> t.m_name && ifs >> t.m_Pwd)
	{
		vtea.push_back(t);
	}
	cout << "当前教师数量为： " << vtea.size() << endl;

	ifs.close();
}
bool Manager::checkRepeat(int id,int type) {
	if (type == 1) {
		for (vector<Student>::iterator it = vstu.begin(); it != vstu.end(); it++) {
			if (id == it->m_Id) {
				return true;
			}
		}
	}
	else {
		for (vector<Teacher>::iterator it = vtea.begin(); it != vtea.end(); it++) {
			if (id == it->m_EmpId) {
				return true;
			}
		}
	}
	return false;
	
}
