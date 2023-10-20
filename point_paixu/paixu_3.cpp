#include<iostream>
#include<fstream>
#include<string>
#include <algorithm>
#include<vector>
#include<iomanip>
using namespace std;
struct ID
{
	unsigned int main_id;
	unsigned int sec_id;
	unsigned int last_id;
};
struct Point
{
	double x;
	double y;
	ID id;
	string bianhao;
	double add;
	double sec_depend;
};
bool compareweight(Point& p1, Point& p2)
{
	return p1.add < p2.add;
}

vector<Point> read_file()
{
	vector<Point> p;
	ifstream ifs;
	ifs.open("location(2).txt", ios::in);
	if (!ifs.is_open())
	{
		cout << "不能打开文件" << endl;
		system("pause");
	}
	char buf[1024];
	while (ifs.getline(buf, sizeof(buf)))
	{
		Point a = {};
		vector<string> s;
		char* next_token;
		char* token = strtok_s(buf, " ", &next_token);
		while (token != NULL) {
			s.push_back(token);
			token = strtok_s(NULL, " ", &next_token);
		}
		//cout << stod(s[1]) << endl;
		a.bianhao = s[0];
		a.x = stod(s[1]);
		//cout << stod(s[2]) << endl;
		a.y = stod(s[2]);
		p.push_back(a);
		//cout << a.type << endl;
		s.clear();
	}
	ifs.close();
	return p;
}
void write_file(vector<Point>& v, vector<string>& q)
{
	ofstream ofs;
	ofs.open("station_to_matlab.txt", ios::out);
	int i = 0;
	for (vector<Point>::iterator it = v.begin(); it != v.end(); it++)
	{
		ofs << q[i] << " " << it->bianhao << endl;
		i++;
	}
	cout << "文件写入成功！" << endl;
	ofs.close();
}
vector<Point> function_fenqu(vector<Point>& v)
{
	for (vector<Point>::iterator it = v.begin(); it != v.end(); it++)//遍历容器
	{
		//cout << *it << "  ";
		if (it->x > 0 && it->x < 9 && it->y > -1 && it->y < 3) //第一部分
		{
			it->id.main_id = 7;
		}
		else if (it->x > 9.5 && it->x < 10.5)
		{
			it->id.main_id = 6;
		}//第二部分
		else if ((it->y > 22) && (it->x > 10 && it->x < 39)) { it->id.main_id = 5; }//最上侧干道
		else if ((it->y > 10 && it->y < 22) && (it->x > 10.5 && it->x < 39)) { it->id.main_id = 4; }
		else if (it->x > 39) { it->id.main_id = 3; }//最右侧干道
		else if ((it->x > 11) && (it->x < 39) && (it->y < -20) && (it->y > -40)) { it->id.main_id = 2; }
		else {
			it->id.main_id = 1;
		}
		it->add = it->id.main_id * 1000 + 10 * it->x + it->y;
	}
	sort(v.begin(), v.end(), compareweight);//根据权值排序
	return v;
}
int main()
{
	vector<string> q;
	ifstream ifs;
	ifs.open("location(2).txt", ios::in);
	if (!ifs.is_open())
	{
		cout << "不能打开文件" << endl;
		system("pause");
	}
	char buf[1024];
	while (ifs.getline(buf, sizeof(buf)))
	{

		vector<string> s;
		char* next_token;
		char* token = strtok_s(buf, " ", &next_token);
		while (token != NULL) {
			s.push_back(token);
			token = strtok_s(NULL, " ", &next_token);
		}
		//cout << stod(s[1]) << endl;
		q.push_back(s[0]);
		//cout << a.type << endl;
		s.clear();
	}
	ifs.close();

	vector<Point> temp = read_file();
	vector<Point> p = function_fenqu(temp);
	write_file(p, q);
	system("pause");
	return 0;
}