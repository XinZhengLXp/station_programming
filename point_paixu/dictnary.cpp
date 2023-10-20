#include<iostream>
#include<fstream>
#include<string>
#include <algorithm>
#include<vector>
using namespace std;
struct ID
{
	unsigned int main_id;
	unsigned int sec_id;
	unsigned int last_id;
};
struct Point
{
	string origin_id;
	double x;
	double y;
	string type;
	ID id;
	double add;
	double sec_depend;
};
bool compareweight(Point& p1, Point& p2)
{
	return p1.add < p2.add;
}
bool bijiao_sec(Point& p1, Point& p2)
{
	return p1.sec_depend < p2.sec_depend;
}
vector<Point> read_file()
{
	vector<Point> p;
	ifstream ifs;
	ifs.open("agv_station_dic.txt", ios::in);
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
		a.y = stod(s[1]);
		a.type = s[2];
		a.origin_id = s[3];
		p.push_back(a);
		//cout << a.type << endl;
	}
	ifs.close();
	return p;
}
void write_file(vector<Point>& v)
{
	ofstream ofs;
	ofs.open("xy_index.txt", ios::out);
	int i = 0;
	for (vector<Point>::iterator it = v.begin(); it != v.end(); it++)
	{
		ofs <<it->x <<" " <<it->x << " " << i << endl;
		i++;
	}
	cout << "�ļ�д��ɹ���" << endl;
	ofs.close();
}
vector<Point> function_fenqu(vector<Point>& v)
{
	for (vector<Point>::iterator it = v.begin(); it != v.end(); it++)//��������
	{
		//cout << *it << "  ";
		if (it->x > 0 && it->x < 9 && it->y > -1 && it->y < 3) //��һ����
		{
			it->id.main_id = 7;
		}
		else if (it->x > 9.5 && it->x < 10.5)
		{
			it->id.main_id = 6;
		}//�ڶ�����
		else if ((it->y > 22) && (it->x > 10.5 && it->x < 39)) { it->id.main_id = 5; }//���ϲ�ɵ�
		else if ((it->y > 10 && it->y < 22) && (it->x > 10.5 && it->x < 39)) { it->id.main_id = 4; }
		else if (it->x > 39) { it->id.main_id = 3; }//���Ҳ�ɵ�
		else if ((it->x > 11) && (it->x < 39) && (it->y < -20) && (it->y > -40)) { it->id.main_id = 2; }
		else {
			it->id.main_id = 1;
		}
		it->add = it->id.main_id * 1000 + 10 * it->x + it->y;
	}
	sort(v.begin(), v.end(), compareweight);//����Ȩֵ����
	vector<Point> V;
	for (int i = 0; i < 7; i++)//���ݴ���������
	{
		unsigned int a = 1;

		vector<Point> R_S;
		vector<Point> S;
		//���ô���Ԫ����ȡ��R_S��
		for (vector<Point>::iterator it = v.begin(); it != v.end(); it++)
		{
			if (it->id.main_id == i + 1 && it->type == "ROUTER_STATION")
			{
				R_S.push_back(*it);
			}
		}
		for (vector<Point>::iterator it = v.begin(); it != v.end(); it++)
		{
			if (it->id.main_id == i + 1 && it->type != "ROUTER_STATION")
			{
				S.push_back(*it);
			}
		}
		//�����ɵ�վ������
		for (vector<Point>::iterator it = R_S.begin(); it != R_S.end(); it++)
		{
			it->id.sec_id = a;
			it->id.last_id = 0;
			a++;
		}
		for (vector<Point>::iterator it = R_S.begin(); it != R_S.end(); it++)
		{
			V.push_back(*it);//���ɵ�վ�����V
		}
		//�������ɵ�station�μ����
		for (vector<Point>::iterator it = S.begin(); it != S.end(); it++)
		{
			vector<Point> bijiao;
			for (int iu = 0; iu < R_S.size(); iu++)
			{
				if (abs(R_S[iu].x - it->x )< 0.2 || abs(R_S[iu].y - it->y) < 0.2)
				{
					R_S[iu].sec_depend = abs(R_S[iu].x - it->x) + abs(R_S[iu].y - it->y);
					bijiao.push_back(R_S[iu]);
				}
			}
			sort(bijiao.begin(), bijiao.end(), bijiao_sec);//���ݾ�������
			it->id.sec_id = bijiao[0].id.sec_id;
			bijiao.clear();
		}
		/*for (vector<Point>::iterator it = S.begin(); it != S.end(); it++)
		{
			V.push_back(*it);
		}*/
		//�����ɵ�վ�����last_id
		for (int t = 0; t < R_S.size(); t++)//a-1Ϊÿ�����������ɵ�վ������
		{
			vector<Point> bijiao;
			for (vector<Point>::iterator it = S.begin(); it != S.end(); it++)
			{
				if (it->id.sec_id == t + 1)
				{
					it->sec_depend = abs(R_S[t].x - it->x) + abs(R_S[t].y - it->y);//�븽�����ɵ��ľ���
					bijiao.push_back(*it);
				}
			}
			if (!bijiao.empty())
			{
				sort(bijiao.begin(), bijiao.end(), bijiao_sec);
				unsigned int s = 1;
				for (vector<Point>::iterator it = bijiao.begin(); it != bijiao.end(); it++)
				{
					it->id.last_id = s;
					s++;
				}
				for (vector<Point>::iterator it = bijiao.begin(); it != bijiao.end(); it++)
				{
					V.push_back(*it);
				}
				bijiao.clear();
			}
		}
	}
	sort(v.begin(), v.end(), compareweight);
	return V;
}

int main()
{
	vector<Point> temp = read_file();
	vector<Point> p = function_fenqu(temp);
	write_file(p);
	system("pause");
	return 0;
}
