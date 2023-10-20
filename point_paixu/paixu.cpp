#include<iostream>
#include<fstream>
#include<string>
#include <algorithm>
#include<vector>
using namespace std;
struct Point
{
	double x;
	double y;
	string type;
	unsigned int main_id;
	double add;
	unsigned int sec_id;
};
bool compareweight(Point &p1, Point& p2)
{
	return p1.add < p2.add;
}
vector<Point> read_file()
{
	vector<Point> p;
	ifstream ifs;
	ifs.open("agv_station.txt", ios::in);
	if (!ifs.is_open())
	{
		cout << "���ܴ��ļ�" << endl;
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
		a.x = stod(s[0]);
		a.y =stod(s[1]);
		a.type = s[2];
		p.push_back(a);
		//cout << a.type << endl;
	}	
	ifs.close();
	return p;
}
void write_file(vector<Point>& v)
{
	ofstream ofs;
	ofs.open("agv_station_c.txt", ios::out);
	for (vector<Point>::iterator it = v.begin(); it != v.end(); it++)
	{
		ofs << it->x << "\t" << it->y << "\t" << it->type<<"\t"<<it->main_id<<"-" << it->sec_id << endl;
	}
	cout <<"�ļ�д��ɹ���" << endl;
	ofs.close();
}
vector<Point> function_fenqu(vector<Point>& v)
{
	for (vector<Point>::iterator it = v.begin(); it != v.end(); it++)//��������
	{
		//cout << *it << "  ";
		if ((( it->x>0) && (it->x<9)) && ((it->y>-1) && (it->y <1))) //��һ����
		{
			it->main_id = 7;
		}
		else if ((it->x >9.5) && (it->x < 10.5)) 
		{ it->main_id = 6;
		}//�ڶ�����
		else if ((it->y >22) && (it->x>10.5 && it->x<39)) { it->main_id = 5; }//���ϲ�ɵ�
		else if ((it->y>10 && it->y<22) && (it->x > 10.5 && it->x < 39)) { it->main_id = 4; }
		else if ( it->x > 39) { it->main_id = 3; }//���Ҳ�ɵ�
		else if ((it->x>11)&&  (it->x < 39) && (it->y<-20)&&(it->y > -40)) { it->main_id = 2; }
		else {
			it->main_id = 1;
		}	
		it->add = it->main_id * 1000 + 10 * it->x + it->y;
	}
	sort(v.begin(), v.end(), compareweight);//����Ȩֵ����
	for (int i = 0; i < 7; i++) 
	{
		unsigned int a = 1;
		for (vector<Point>::iterator it = v.begin(); it != v.end(); it++)//��Ӷ�����׺
		{
			it = it - 1;
			if (it->main_id == i+1) //&& it->type == "ROUTER_STATION"
			{
				it->sec_id = a;
				a++;
			}
		}

	}
	return v;
}

int main()
{
	vector<Point> temp = read_file();
	vector<Point> p = function_fenqu(temp);
	write_file(p);
	system("pause");
	return 0;
}
