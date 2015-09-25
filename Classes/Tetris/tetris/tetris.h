#ifndef TETRIS_H_
#define TETRIS_H_

class MapTetris
{// TODO: map应该可以作为嵌套类放到Tetris里去
public:
	enum{ WIDTH = 16, HEIGHT = 30 };
public:
	MapTetris(){}
	bool init()
	{
		for (int i = 0; i < HEIGHT; ++i)
			for (int j = 0; j < WIDTH; ++j)
				_map[i][j] = 0;
		return true;
	}
	// 数据接口
	static MapTetris * GetInstance()		// 单例设计模式
	{
		static MapTetris map;

		return &map;
	}
	int width()const{ return WIDTH; }
	int height()const{ return HEIGHT; }

	// 得到一个点的值
	int get(int position_x, int position_y)
	{
		if (position_x >= WIDTH || position_y >= HEIGHT)
			return -1;
		else
			return _map[position_y][position_x];
	}
	// 设置一个点的值
	void set(int position_x, int position_y, int value)
	{
		if (position_x >= WIDTH || position_y >= HEIGHT){
			return;
		}
		else{
			_map[position_y][position_x] = value;
			return;
		}
		return;
	}
	// 满行测试
	bool isFullLine(int line)
	{
		for (int i = 0; i < WIDTH; ++i)
		{
			if (!_map[line][i])					// 只要有一个点不存在就不是满行
				return false;
			else
				continue;
		}

		return true;
	}
	// 消除一个行
	void eraseLine(int line)
	{
		for (int i = 0; i < WIDTH; ++i){
			_map[line][i] = 0;
		}
		return;
	}
	// 移动一个行
	void moveLine(int from, int to)
	{
		for (int i = 0; i < WIDTH; ++i)
		{
			_map[to][i] = _map[from][i];
			_map[from][i] = 0;
		}
		return;
	}
	// 重载[]运算符
	const int* operator[](const int line)const
	{
		return _map[line];
	}
private:
	MapTetris(const MapTetris &) = delete;					// 禁用复制构造函数
	MapTetris & operator =(const MapTetris &) = delete;		// 禁用赋值操作符
private:
	int _map[HEIGHT][WIDTH];					// 主要数据
};

class Tetris
{
public:
	enum TYPES{ O, I, S, Z, L, J, T };					// 方块形态
	enum TOP{ BEGIN = 2 };								// 输出开始位在地图中的竖直位置
public:
	bool init(TYPES type)	
	{		// 初始化
		static int tetrisO[1][4][2] =					// O 型
		{
			{ { 1, 1 }, { 2, 1 }, { 1, 2 }, { 2, 2 } }
		};
		static int tetrisI[2][4][2] =					// I 型
		{
			{ { 0, 0 }, { 0, 1 }, { 0, 2 }, { 0, 3 } },
			{ { 0, 1 }, { 1, 1 }, { 2, 1 }, { 3, 1 } }
		};
		static int tetrisS[2][4][2] =					// S 型
		{
			{ { 0, 0 }, { 0, 1 }, { 1, 1 }, { 1, 2 } },
			{ { 0, 2 }, { 1, 1 }, { 1, 2 }, { 2, 1 } }
		};
		static int tetrisZ[2][4][2] =					// Z 型
		{
			{ { 1, 1 }, { 1, 2 }, { 2, 0 }, { 2, 1 } },
			{ { 0, 1 }, { 1, 1 }, { 1, 2 }, { 2, 2 } }
		};
		static int tetrisL[4][4][2] =					// L 型
		{
			{ { 0, 0 }, { 1, 0 }, { 1, 1 }, { 1, 2 } },
			{ { 0, 2 }, { 1, 2 }, { 2, 1 }, { 2, 2 } },
			{ { 1, 0 }, { 1, 1 }, { 1, 2 }, { 2, 2 } },
			{ { 0, 1 }, { 0, 2 }, { 1, 1 }, { 2, 1 } }
		};
		static int tetrisJ[4][4][2] =					// J 型
		{
			{ { 0, 2 }, { 1, 0 }, { 1, 1 }, { 1, 2 } },
			{ { 0, 2 }, { 1, 2 }, { 0, 1 }, { 2, 2 } },
			{ { 1, 0 }, { 1, 1 }, { 1, 2 }, { 2, 0 } },
			{ { 0, 1 }, { 2, 2 }, { 1, 1 }, { 2, 1 } }
		};
		static int tetrisT[4][4][2] =					// T 型
		{
			{ { 0, 1 }, { 1, 0 }, { 1, 1 }, { 1, 2 } },
			{ { 0, 2 }, { 1, 2 }, { 1, 1 }, { 2, 2 } },
			{ { 1, 0 }, { 1, 1 }, { 1, 2 }, { 2, 1 } },
			{ { 0, 1 }, { 1, 2 }, { 1, 1 }, { 2, 1 } }
		};

		// 地图必须得到
		map = MapTetris::GetInstance();
		if (!map)
			return false;
		// 形态无关变量初始化
		_id = type + 1;									// 所有id均+1,保证每个形态ID不通
		_modal = 0;										// 初始模式均为0
		_position_x = (*map).width() / 2;				// 设置初始地点
		_position_y = 0;
		_heightest_line = -1;							// 可以消除的最高行一开始不存在
		_lowest_line = -1;								// 可以消除的最低行一开始不存在
		// 不同的参数给与不通的地址,static变量程序结束是才释放
		switch (type)
		{
		case Tetris::O:									// O 型
			_modals = 1;								// 总形态数量
			_points = 4;								// 拥有"点"数
			_tetris = (int *)tetrisO;					// 取得地图
			break;
		case Tetris::I:
			_modals = 2;
			_points = 4;
			_tetris = (int *)tetrisI;
			break;
		case Tetris::S:
			_modals = 2;
			_points = 4;
			_tetris = (int *)tetrisS;
			break;
		case Tetris::Z:
			_modals = 2;
			_points = 4;
			_tetris = (int *)tetrisZ;
			break;
		case Tetris::L:
			_modals = 4;
			_points = 4;
			_tetris = (int *)tetrisL;
			break;
		case Tetris::J:
			_modals = 4;
			_points = 4;
			_tetris = (int *)tetrisJ;
			break;
		case Tetris::T:
			_modals = 4;
			_points = 4;
			_tetris = (int *)tetrisT;
			break;
		default:
			_modals = 4;
			_points = 4;
			_tetris = (int *)tetrisJ;
			break;
		}

		return true;
	}
	// 输出函数[1/1]
	int id()const	
	{	// 得到方块当前的编号,以便于个性化输出不同的方块
		return _id; 
	}
	int points()const //得到一个方块拥有的点数,现在定义的都是4个点的
	{
		return _points;
	}
	int posXInMap(int point)const	// 得到点在地图中的水平位置X
	{
		return *(_tetris + _modal*_points * D2D + point * D2D + X) + _position_x;
	}
	int posYInMap(int point)const	// 得到点在地图中的水平位置Y
	{
		return *(_tetris + _modal*_points * D2D + point * D2D + Y) + _position_y;
	}

	// 动作函数[1]:判断
	bool isLeftOK()const
	{
		for (int i = 0; i < _points; ++i)
		{
			int x = posXInMap(i);										// 点在地图中的水平位置
			int y = posYInMap(i);										// 点在地图中的竖直位置
			if (x == 0)													// 在边界上
				return false;
			else if ((*map).get(x - 1, y))								// 左边有阻碍
				return false;
			else
				continue;
		}

		return true;
	}
	bool isRightOK()const
	{
		for (int i = 0; i < _points; ++i)
		{
			int x = posXInMap(i);										// 点在地图中的水平位置
			int y = posYInMap(i);										// 点在地图中的竖直位置
			if (x == (*map).width() - 1)								// 在边界上
				return false;
			else if ((*map).get(x + 1, y))								// 右边有阻碍
				return false;
			else
				continue;
		}

		return true;
	}
	bool isDownOK()const
	{
		for (int i = 0; i < _points; ++i)
		{
			int x = posXInMap(i);										// 点在地图中的水平位置
			int y = posYInMap(i);										// 点在地图中的竖直位置
			if (y == (*map).height() - 1)								// 在边界上
				return false;
			else if ((*map).get(x, y + 1))								// 下边有阻碍
				return false;
			else
				continue;
		}

		return true;
	}
	bool isUpOK()const
	{
		int nex_modal = (_modal + 1) % _modals;							// 下一个模式
		for (int i = 0; i < _points; ++i)
		{
			int x = posXInMap(i, nex_modal);										// 点在地图中的水平位置
			int y = posYInMap(i, nex_modal);										// 点在地图中的竖直位置
			if (x <0 || x > (*map).width() - 1 || y < 0 || y > (*map).height() - 1)	// 点在边界上
				return false;
			else if ((*map).get(x, y))									// 点所在位置有阻碍
				return false;
			else
				continue;
		}

		return true;

	}
	// 动作函数[2]:移动
	void left() { _position_x--; }						// 左移
	void right(){ _position_x++; }						// 右移
	void down(){ _position_y++; }						// 下移
	void up(){ _modal = (_modal + 1) % _modals; }		// 变化
	// 动作函数[3]:交接
	int give()
	{	//	无法下移, 将方块防到地图上
		int n = 0;										// 满行的最高行与最低行, 满行数量

		for (int i = 0; i < _points; ++i)				// 求得4个点中位置最高与最低值
		{
			int x = posXInMap(i);						// 点在地图中的水平位置
			int y = posYInMap(i);						// 点在地图中的竖直位置
			(*map).set(x, y, _id);

			if ((*map).isFullLine(y))
			{
				if (n == 0)
					_heightest_line = _lowest_line = y;
				else
				{
					if (_heightest_line > y)
						_heightest_line = y;
					if (_lowest_line < y)
						_lowest_line = y;
				}
				n++;
			}
		}

		return n;
	}
	// 动作函数[4]:删除
	void removeFullLine()
	{
		if (_heightest_line == -1)
			return;
		for (int i = _heightest_line; i <= _lowest_line; ++i)
		{
			if ((*map).isFullLine(i))
			{
				int src = i - 1;
				while (src > 3)
				{
					(*map).moveLine(src, src + 1);
					src--;
				}
			}
		}
		_heightest_line = -1;
		_lowest_line = -1;
	}
	// 动作函数[5]:返回
	void reset()
	{	// 重新设定位置,可以改动为为不同形态的方块设定不同位置
		_position_x = (*map).width() / 2;
		_position_y = 0;
		return;
	}	

protected:
	enum ADDRFORMART{ D2D = 2 };						// 点集合数组坐标的纬度
	enum POSITION{ X = 0, Y = 1 };						// 在点集合数组中X为列坐标,Y为行坐标
	// 变形要用到下一个模式
	int posXInMap(int point, int mod)const
	{
		return *(_tetris + mod*_points * D2D + point * D2D + X) + _position_x;		// 点的水平位置
	}
	// 变形要用到下一个模式
	int posYInMap(int point, int mod)const
	{
		return *(_tetris + mod*_points * D2D + point * D2D + Y) + _position_y;		// 点的竖直位置
	}
private:
	int _id;					// 方块样式编号,给不通方块绘制不图案
	int _modal;					// 方块的当前形态模式
	int _modals;				// 方块拥有的总模式数量
	int _points;				// 方块拥有的小方块数量
	int *_tetris;				// 方块地址tetris[当前形态][小方块编号][小方块地址]

	MapTetris * map;					// 方块所处地图的引用
	int _position_x;			// 方块在地图上的位置: 水平方向
	int _position_y;			// 方块在地图上的位置: 竖直方向
	int _heightest_line;		// 需要消除的最高行
	int _lowest_line;			// 需要消除的最低行;
};

#endif	// TETRIS_H_

