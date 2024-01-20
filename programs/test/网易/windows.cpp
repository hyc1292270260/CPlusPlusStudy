#include <iostream>
#include <vector>
#include <list>
using namespace std;

//屏幕38490*2159，输入创建窗口数量，点击屏幕点
//判断点击点在哪个窗口（没有返回-1，有判断第几个窗口并返回，后建窗口覆盖原来窗口）
struct Point
{
	int x;
	int y;
};
struct Windows
{
	struct Point origin;
	int weight;
	int hight;

};

bool in(Point p, Windows wnd);
Windows createwindow(Point p, int w, int h);


vector<Windows> wnds;
vector<Windows>::iterator it;
list<Point> click_points;
vector<int> Index;
int main(void)
{
	int n, m;
	int x, y, w, h;
	cin >> n >> m;
	if (n > 1000 || n < 0 || m>1000 || m < 0)
	{
		return -1;
	}

	Point p;
	for (int i = 0; i < n; ++i)
	{
		cin >> x >> y >> w >> h;
		if (x > 3840 || x < 0 || y>2159 || y < 0)
		{
			return -1;
		}
		p.x = x;
		p.y = y;

		wnds.emplace_back(createwindow(p, w, h));
	}
	for (int j = 0; j < m; ++j)
	{
		cin >> p.x >> p.y;
		click_points.emplace_back(p);

	}
	
	int num = 0;
	while (!click_points.empty())
	{
	    p =click_points.front();
		click_points.pop_front();
		int index = 0;		
		int final_index = -1;		
		Index.emplace_back(final_index);
		for (it = wnds.begin(); it != wnds.end(); ++it, ++index)
		{
			
			if (in(p, wnds[index]))
			{
				final_index = index + 1;
				Index[num] = final_index;
			}
			
		}
		++num;
		
		
	}
	for (auto it : Index)
	{
		cout << it << endl;
	}
	return 0;

}
Windows createwindow(Point p, int w, int h)
{

	Windows wnd;
	wnd.origin = p;
	wnd.weight = w;
	wnd.hight = h;

	return wnd;
}
bool in(Point p, Windows wnd)
{
	if (p.x > wnd.origin.x&&p.y > wnd.origin.y&&p.x < wnd.origin.x + wnd.weight&&p.y < wnd.origin.y + wnd.hight)
	{
		return true;
	}
	return false;
}