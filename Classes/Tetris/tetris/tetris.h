#ifndef TETRIS_H_
#define TETRIS_H_

class MapTetris
{// TODO: mapӦ�ÿ�����ΪǶ����ŵ�Tetris��ȥ
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
	// ���ݽӿ�
	static MapTetris * GetInstance()		// �������ģʽ
	{
		static MapTetris map;

		return &map;
	}
	int width()const{ return WIDTH; }
	int height()const{ return HEIGHT; }

	// �õ�һ�����ֵ
	int get(int position_x, int position_y)
	{
		if (position_x >= WIDTH || position_y >= HEIGHT)
			return -1;
		else
			return _map[position_y][position_x];
	}
	// ����һ�����ֵ
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
	// ���в���
	bool isFullLine(int line)
	{
		for (int i = 0; i < WIDTH; ++i)
		{
			if (!_map[line][i])					// ֻҪ��һ���㲻���ھͲ�������
				return false;
			else
				continue;
		}

		return true;
	}
	// ����һ����
	void eraseLine(int line)
	{
		for (int i = 0; i < WIDTH; ++i){
			_map[line][i] = 0;
		}
		return;
	}
	// �ƶ�һ����
	void moveLine(int from, int to)
	{
		for (int i = 0; i < WIDTH; ++i)
		{
			_map[to][i] = _map[from][i];
			_map[from][i] = 0;
		}
		return;
	}
	// ����[]�����
	const int* operator[](const int line)const
	{
		return _map[line];
	}
private:
	MapTetris(const MapTetris &) = delete;					// ���ø��ƹ��캯��
	MapTetris & operator =(const MapTetris &) = delete;		// ���ø�ֵ������
private:
	int _map[HEIGHT][WIDTH];					// ��Ҫ����
};

class Tetris
{
public:
	enum TYPES{ O, I, S, Z, L, J, T };					// ������̬
	enum TOP{ BEGIN = 2 };								// �����ʼλ�ڵ�ͼ�е���ֱλ��
public:
	bool init(TYPES type)	
	{		// ��ʼ��
		static int tetrisO[1][4][2] =					// O ��
		{
			{ { 1, 1 }, { 2, 1 }, { 1, 2 }, { 2, 2 } }
		};
		static int tetrisI[2][4][2] =					// I ��
		{
			{ { 0, 0 }, { 0, 1 }, { 0, 2 }, { 0, 3 } },
			{ { 0, 1 }, { 1, 1 }, { 2, 1 }, { 3, 1 } }
		};
		static int tetrisS[2][4][2] =					// S ��
		{
			{ { 0, 0 }, { 0, 1 }, { 1, 1 }, { 1, 2 } },
			{ { 0, 2 }, { 1, 1 }, { 1, 2 }, { 2, 1 } }
		};
		static int tetrisZ[2][4][2] =					// Z ��
		{
			{ { 1, 1 }, { 1, 2 }, { 2, 0 }, { 2, 1 } },
			{ { 0, 1 }, { 1, 1 }, { 1, 2 }, { 2, 2 } }
		};
		static int tetrisL[4][4][2] =					// L ��
		{
			{ { 0, 0 }, { 1, 0 }, { 1, 1 }, { 1, 2 } },
			{ { 0, 2 }, { 1, 2 }, { 2, 1 }, { 2, 2 } },
			{ { 1, 0 }, { 1, 1 }, { 1, 2 }, { 2, 2 } },
			{ { 0, 1 }, { 0, 2 }, { 1, 1 }, { 2, 1 } }
		};
		static int tetrisJ[4][4][2] =					// J ��
		{
			{ { 0, 2 }, { 1, 0 }, { 1, 1 }, { 1, 2 } },
			{ { 0, 2 }, { 1, 2 }, { 0, 1 }, { 2, 2 } },
			{ { 1, 0 }, { 1, 1 }, { 1, 2 }, { 2, 0 } },
			{ { 0, 1 }, { 2, 2 }, { 1, 1 }, { 2, 1 } }
		};
		static int tetrisT[4][4][2] =					// T ��
		{
			{ { 0, 1 }, { 1, 0 }, { 1, 1 }, { 1, 2 } },
			{ { 0, 2 }, { 1, 2 }, { 1, 1 }, { 2, 2 } },
			{ { 1, 0 }, { 1, 1 }, { 1, 2 }, { 2, 1 } },
			{ { 0, 1 }, { 1, 2 }, { 1, 1 }, { 2, 1 } }
		};

		// ��ͼ����õ�
		map = MapTetris::GetInstance();
		if (!map)
			return false;
		// ��̬�޹ر�����ʼ��
		_id = type + 1;									// ����id��+1,��֤ÿ����̬ID��ͨ
		_modal = 0;										// ��ʼģʽ��Ϊ0
		_position_x = (*map).width() / 2;				// ���ó�ʼ�ص�
		_position_y = 0;
		_heightest_line = -1;							// ���������������һ��ʼ������
		_lowest_line = -1;								// ���������������һ��ʼ������
		// ��ͬ�Ĳ������벻ͨ�ĵ�ַ,static������������ǲ��ͷ�
		switch (type)
		{
		case Tetris::O:									// O ��
			_modals = 1;								// ����̬����
			_points = 4;								// ӵ��"��"��
			_tetris = (int *)tetrisO;					// ȡ�õ�ͼ
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
	// �������[1/1]
	int id()const	
	{	// �õ����鵱ǰ�ı��,�Ա��ڸ��Ի������ͬ�ķ���
		return _id; 
	}
	int points()const //�õ�һ������ӵ�еĵ���,���ڶ���Ķ���4�����
	{
		return _points;
	}
	int posXInMap(int point)const	// �õ����ڵ�ͼ�е�ˮƽλ��X
	{
		return *(_tetris + _modal*_points * D2D + point * D2D + X) + _position_x;
	}
	int posYInMap(int point)const	// �õ����ڵ�ͼ�е�ˮƽλ��Y
	{
		return *(_tetris + _modal*_points * D2D + point * D2D + Y) + _position_y;
	}

	// ��������[1]:�ж�
	bool isLeftOK()const
	{
		for (int i = 0; i < _points; ++i)
		{
			int x = posXInMap(i);										// ���ڵ�ͼ�е�ˮƽλ��
			int y = posYInMap(i);										// ���ڵ�ͼ�е���ֱλ��
			if (x == 0)													// �ڱ߽���
				return false;
			else if ((*map).get(x - 1, y))								// ������谭
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
			int x = posXInMap(i);										// ���ڵ�ͼ�е�ˮƽλ��
			int y = posYInMap(i);										// ���ڵ�ͼ�е���ֱλ��
			if (x == (*map).width() - 1)								// �ڱ߽���
				return false;
			else if ((*map).get(x + 1, y))								// �ұ����谭
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
			int x = posXInMap(i);										// ���ڵ�ͼ�е�ˮƽλ��
			int y = posYInMap(i);										// ���ڵ�ͼ�е���ֱλ��
			if (y == (*map).height() - 1)								// �ڱ߽���
				return false;
			else if ((*map).get(x, y + 1))								// �±����谭
				return false;
			else
				continue;
		}

		return true;
	}
	bool isUpOK()const
	{
		int nex_modal = (_modal + 1) % _modals;							// ��һ��ģʽ
		for (int i = 0; i < _points; ++i)
		{
			int x = posXInMap(i, nex_modal);										// ���ڵ�ͼ�е�ˮƽλ��
			int y = posYInMap(i, nex_modal);										// ���ڵ�ͼ�е���ֱλ��
			if (x <0 || x > (*map).width() - 1 || y < 0 || y > (*map).height() - 1)	// ���ڱ߽���
				return false;
			else if ((*map).get(x, y))									// ������λ�����谭
				return false;
			else
				continue;
		}

		return true;

	}
	// ��������[2]:�ƶ�
	void left() { _position_x--; }						// ����
	void right(){ _position_x++; }						// ����
	void down(){ _position_y++; }						// ����
	void up(){ _modal = (_modal + 1) % _modals; }		// �仯
	// ��������[3]:����
	int give()
	{	//	�޷�����, �����������ͼ��
		int n = 0;										// ���е�������������, ��������

		for (int i = 0; i < _points; ++i)				// ���4������λ����������ֵ
		{
			int x = posXInMap(i);						// ���ڵ�ͼ�е�ˮƽλ��
			int y = posYInMap(i);						// ���ڵ�ͼ�е���ֱλ��
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
	// ��������[4]:ɾ��
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
	// ��������[5]:����
	void reset()
	{	// �����趨λ��,���ԸĶ�ΪΪ��ͬ��̬�ķ����趨��ͬλ��
		_position_x = (*map).width() / 2;
		_position_y = 0;
		return;
	}	

protected:
	enum ADDRFORMART{ D2D = 2 };						// �㼯�����������γ��
	enum POSITION{ X = 0, Y = 1 };						// �ڵ㼯��������XΪ������,YΪ������
	// ����Ҫ�õ���һ��ģʽ
	int posXInMap(int point, int mod)const
	{
		return *(_tetris + mod*_points * D2D + point * D2D + X) + _position_x;		// ���ˮƽλ��
	}
	// ����Ҫ�õ���һ��ģʽ
	int posYInMap(int point, int mod)const
	{
		return *(_tetris + mod*_points * D2D + point * D2D + Y) + _position_y;		// �����ֱλ��
	}
private:
	int _id;					// ������ʽ���,����ͨ������Ʋ�ͼ��
	int _modal;					// ����ĵ�ǰ��̬ģʽ
	int _modals;				// ����ӵ�е���ģʽ����
	int _points;				// ����ӵ�е�С��������
	int *_tetris;				// �����ַtetris[��ǰ��̬][С������][С�����ַ]

	MapTetris * map;					// ����������ͼ������
	int _position_x;			// �����ڵ�ͼ�ϵ�λ��: ˮƽ����
	int _position_y;			// �����ڵ�ͼ�ϵ�λ��: ��ֱ����
	int _heightest_line;		// ��Ҫ�����������
	int _lowest_line;			// ��Ҫ�����������;
};

#endif	// TETRIS_H_

