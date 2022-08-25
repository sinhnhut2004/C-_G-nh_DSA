#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <ctime>
#define MAX 50
using namespace std;

struct Position
{
	int x; int y;
	Position() { x = y = 0; }
	Position(int a, int b)
	{
		x = a; y = b;
	}
};

struct Move
{
	Position pos_start, pos_end;
	Move(Position s, Position e)
	{
		pos_start = s; pos_end = e;
	}
};

int G[MAX][MAX], n, chuaxet[MAX], QUEUE[MAX], solt;
Position* arr;

///////////////////////////////////////////


// trả về danh sách quân player trên bàn cờ
vector<Position> danhSachQuanTrenBanCo(int** board, int player)
{
	vector<Position> result;
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (board[i][j] == player)
			{
				Position a(i, j);
				result.push_back(a);
			}
		}
	}
	return result;
}

// kiểm tra xem điểm b có kề điểm a không.
bool Validpoint(Position a, Position b)			// b so với a 
{
	if ((a.x + a.y) % 2 == 0)					// xét cả đường chéo        
	{
		// trên
		if (a.y + 1 == b.y && a.x == b.x)
		{
			return true;
		}
		// dưới
		if (a.y - 1 == b.y && a.x == b.x)
		{
			return true;
		}
		// phải
		if (a.x + 1 == b.x && a.y == b.y)
		{
			return true;
		}
		// trái
		if (a.x - 1 == b.x && a.y == b.y)
		{
			return true;
		}
		// chéo 1
		if (a.x - 1 == b.x && a.y + 1 == b.y)
		{
			return true;
		}
		// chéo 2
		if (a.x + 1 == b.x && a.y + 1 == b.y)
		{
			return true;
		}
		// chéo 3
		if (a.x - 1 == b.x && a.y - 1 == b.y)
		{
			return true;
		}
		// chéo 4
		if (a.x + 1 == b.x && a.y - 1 == b.y)
		{
			return true;
		}

	}
	else										// không xét trường hợp chéo
	{
		// trên
		if (a.y + 1 == b.y && a.x == b.x)
		{
			return true;
		}
		// dưới
		if (a.y - 1 == b.y && a.x == b.x)
		{
			return true;
		}
		// phải
		if (a.x + 1 == b.x && a.y == b.y)
		{
			return true;
		}
		// trái
		if (a.x - 1 == b.x && a.y == b.y)
		{
			return true;
		}
	}
	return false;
}

void Init(int** board, int player) {
	vector<Position> dsQuan = danhSachQuanTrenBanCo(board, player);
	int numCurrent = 0;
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (board[i][j] == player)
			{
				numCurrent++;
			}
		}
	}
	n = numCurrent;

	arr = new Position[n];
	for (int i = 0; i < n; i++)
	{
		arr[i] = dsQuan.at(i);
	}
	//nhập ma trận kề của đồ thị.

	for (int i = 1; i <= n; i++) {

		for (int j = 1; j <= n; j++) {

			G[i][j] = 0;
		}
	}

	for (int i = 0; i < n - 1; i++)
	{
		for (int j = i + 1; j < n; j++)
			if (Validpoint(arr[i], arr[j]))
			{
				G[i + 1][j + 1] = 1;
				G[j + 1][i + 1] = 1;
			}
	}

	//Khởi tạo giá trị ban đầu cho mảng chuaxet.
	for (int i = 1; i <= n; i++)
	{
		chuaxet[i] = 0;
	}
	solt = 0;
}

// Trả về danh sách những nhóm quân liên thông với nhau
vector<vector<Position>> Result(int* chuaxet, int n, int solt)
{
	vector<vector<Position>> v;
	for (int i = 1; i <= solt; i++)
	{
		//printf("\n Thanh phan lien thong thu %d:", i);
		vector<Position> v1;
		for (int j = 1; j <= n; j++)
		{
			if (chuaxet[j] == i)
			{
				//printf("%3d", j);
				//arr[j - 1].printPosition();
				Position var(arr[j - 1].x, arr[j - 1].y);
				v1.push_back(var);
			}
		}
		v.push_back(v1);
	}
	return v;
}

/* Breadth First Search */
void BFS(int G[][MAX], int n, int i, int& solt, int chuaxet[], int QUEUE[MAX]) {

	int u, dauQ, cuoiQ, j;

	dauQ = 1; cuoiQ = 1;

	QUEUE[cuoiQ] = i; chuaxet[i] = solt;

	while (dauQ <= cuoiQ) {

		u = QUEUE[dauQ];

		dauQ = dauQ + 1;

		for (j = 1; j <= n; j++) {

			if (G[u][j] == 1 && chuaxet[j] == 0) {

				cuoiQ = cuoiQ + 1;

				QUEUE[cuoiQ] = j;

				chuaxet[j] = solt;

			}
		}
	}

}

// trả về những nhóm quân liên thông với nhau
vector<vector<Position>> Lien_Thong(int** board, int player) {

	Init(board, player);

	for (int i = 1; i <= n; i++)

		if (chuaxet[i] == 0) {

			solt = solt + 1;

			BFS(G, n, i, solt, chuaxet, QUEUE);

		}

	return Result(chuaxet, n, solt);
}

int** init_board()
{
	int** t = new int* [5];

	for (int i = 0; i < 5; i++)
	{
		t[i] = new int[5];
		if (i == 0)
		{
			for (int j = 0; j < 5; j++)
				t[i][j] = 1;
		}
		if (i == 4)
		{
			for (int j = 0; j < 5; j++)
				t[i][j] = -1;
		}

	}
	t[1][0] = 1; t[1][4] = 1; t[2][0] = 1;
	t[2][4] = -1; t[3][0] = -1; t[3][4] = -1;

	return t;
}

int** copy_board(int** board)
{
	int** n_b = new int* [5];
	for (int i = 0; i < 5; i++)
	{
		n_b[i] = new int[5];
		for (int j = 0; j < 5; j++)
		{
			n_b[i][j] = board[i][j];
		}
	}
	return n_b;
}

//void print_board(int** board)
//{
//	for (int i = 0; i < 5; i++)
//	{
//		for (int j = 0; j < 5; j++)
//		{
//			if (board[4 - i][j] == 1)
//				cout << "X ";
//			else if (board[4 - i][j] == -1)
//				cout << "O ";
//			else
//				cout << "- ";
//		}
//		cout << endl;
//	}
//}

void print_board(int** board)
{
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (board[i][j] == 1)
				cout << "X ";
			else if (board[i][j] == -1)
				cout << "O ";
			else
				cout << "- ";
		}
		cout << endl;
	}
}

// xét xem một nhóm quân có mất khí hay không 
bool checkMatKhi(int** board, vector<Position> list)
{
	int sizeList = list.size();
	for (int i = 0; i < sizeList; i++)
	{
		if ((list.at(i).y + list.at(i).x) % 2 == 0)		// xét cả đường chéo
		{
			// trên 
			if (list.at(i).x + 1 <= 4)
			{
				if (board[list.at(i).x + 1][list.at(i).y] != 1 && board[list.at(i).x + 1][list.at(i).y] != -1)
				{
					return false;
				}
			}

			// dưới		
			if (list.at(i).x - 1 >= 0)
			{
				if (board[list.at(i).x - 1][list.at(i).y] != 1 && board[list.at(i).x - 1][list.at(i).y] != -1)
				{

					return false;
				}
			}

			// phải
			if (list.at(i).y + 1 <= 4)
			{
				if (board[list.at(i).x][list.at(i).y + 1] != 1 && board[list.at(i).x][list.at(i).y + 1] != -1)
				{

					return false;
				}
			}

			// trái
			if (list.at(i).y - 1 >= 0)
			{
				if (board[list.at(i).x][list.at(i).y - 1] != 1 && board[list.at(i).x][list.at(i).y - 1] != -1)
				{

					return false;
				}
			}

			// chéo 1
			if (list.at(i).x + 1 <= 4 && list.at(i).y - 1 >= 0)
			{
				if (board[list.at(i).x + 1][list.at(i).y - 1] != 1 && board[list.at(i).x + 1][list.at(i).y - 1] != -1)
				{
					return false;
				}
			}

			// chéo 2
			if (list.at(i).x + 1 <= 4 && list.at(i).y + 1 <= 4)
			{
				if (board[list.at(i).x + 1][list.at(i).y + 1] != 1 && board[list.at(i).x + 1][list.at(i).y + 1] != -1)
				{
					return false;
				}
			}

			// chéo 3			
			if (list.at(i).x - 1 >= 0 && list.at(i).y - 1 >= 0)
			{
				if (board[list.at(i).x - 1][list.at(i).y - 1] != 1 && board[list.at(i).x - 1][list.at(i).y - 1] != -1)
				{
					return false;
				}
			}

			// chéo 4
			if (list.at(i).x - 1 >= 0 && list.at(i).y + 1 <= 4)
			{
				if (board[list.at(i).x - 1][list.at(i).y + 1] != 1 && board[list.at(i).x - 1][list.at(i).y + 1] != -1)
				{
					return false;
				}
			}
		}

		else							// không yét đường chéo
		{
			// trên
			if (list.at(i).x + 1 <= 4)
			{
				if (board[list.at(i).x + 1][list.at(i).y] != 1 && board[list.at(i).x + 1][list.at(i).y] != -1)
				{
					return false;
				}
			}

			// dưới
			if (list.at(i).x - 1 >= 0)
			{
				if (board[list.at(i).x - 1][list.at(i).y] != 1 && board[list.at(i).x - 1][list.at(i).y] != -1)
				{
					return false;
				}
			}

			// phải
			if (list.at(i).y + 1 <= 4)
			{
				if (board[list.at(i).x][list.at(i).y + 1] != 1 && board[list.at(i).x][list.at(i).y + 1] != -1)
				{
					return false;
				}
			}

			// trái
			if (list.at(i).y - 1 >= 0)
			{
				if (board[list.at(i).x][list.at(i).y - 1] != 1 && board[list.at(i).x][list.at(i).y - 1] != -1)
				{
					return false;
				}
			}
		}
	}
	return true;
}

vector<Position> ganh(int** board, Move m, int player)
{
	vector<Position> result;
	// cập nhật lại bàn cờ
	board[m.pos_start.x][m.pos_start.y] = 0;
	board[m.pos_end.x][m.pos_end.y] = player;

	if ((m.pos_end.y + m.pos_end.x) % 2 == 0)            // xét cả đường chéo
	{
		// xét chiều dọc
		if (m.pos_end.x + 1 <= 4 && m.pos_end.x - 1 >= 0)
		{
			if (board[m.pos_end.x + 1][m.pos_end.y] == -player && board[m.pos_end.x - 1][m.pos_end.y] == -player)
			{
				Position a(m.pos_end.x + 1, m.pos_end.y), b(m.pos_end.x - 1, m.pos_end.y);
				result.push_back(a); result.push_back(b);
				// cập nhật lại bàn cờ
				board[a.x][a.y] = player;
				board[b.x][b.y] = player;
			}
		}

		// xét chiều ngang
		if (m.pos_end.y + 1 <= 4 && m.pos_end.y - 1 >= 0)
		{
			if (board[m.pos_end.x][m.pos_end.y + 1] == -player && board[m.pos_end.x][m.pos_end.y - 1] == -player)
			{
				Position a1(m.pos_end.x, m.pos_end.y + 1), b1(m.pos_end.x, m.pos_end.y - 1);
				result.push_back(a1); result.push_back(b1);
				// cập nhật lại bàn cờ
				board[a1.x][a1.y] = player;
				board[b1.x][b1.y] = player;
			}
		}

		// xet đường chéo
		if (m.pos_end.y <= 3 && m.pos_end.y >= 1 && m.pos_end.x <= 3 && m.pos_end.x >= 1)
		{
			if (board[m.pos_end.x + 1][m.pos_end.y - 1] == -player && board[m.pos_end.x - 1][m.pos_end.y + 1] == -player)
			{
				Position a2(m.pos_end.x + 1, m.pos_end.y - 1), b2(m.pos_end.x - 1, m.pos_end.y + 1);
				result.push_back(a2); result.push_back(b2);
				// cập nhật lại bàn cờ
				board[a2.x][a2.y] = player;
				board[b2.x][b2.y] = player;
			}

			if (board[m.pos_end.x - 1][m.pos_end.y - 1] == -player && board[m.pos_end.x + 1][m.pos_end.y + 1] == -player)
			{
				Position a3(m.pos_end.x - 1, m.pos_end.y - 1), b3(m.pos_end.x + 1, m.pos_end.y + 1);
				result.push_back(a3); result.push_back(b3);
				// cập nhật lại bàn cờ
				board[a3.x][a3.y] = player;
				board[b3.x][b3.y] = player;
			}
		}

	}
	else								 // không xét đường chéo
	{
		// xét chiều dọc
		if (m.pos_end.x + 1 <= 4 && m.pos_end.x - 1 >= 0)
		{
			if (board[m.pos_end.x + 1][m.pos_end.y] == -player && board[m.pos_end.x - 1][m.pos_end.y] == -player)
			{
				Position a(m.pos_end.x + 1, m.pos_end.y), b(m.pos_end.x - 1, m.pos_end.y);
				result.push_back(a); result.push_back(b);
				// cập nhật lại bàn cờ
				board[a.x][a.y] = player;
				board[b.x][b.y] = player;
			}
		}

		// xét chiều ngang
		if (m.pos_end.y + 1 <= 4 && m.pos_end.y - 1 >= 0)
		{
			if (board[m.pos_end.x][m.pos_end.y + 1] == -player && board[m.pos_end.x][m.pos_end.y - 1] == -player)
			{
				Position a1(m.pos_end.x, m.pos_end.y + 1), b1(m.pos_end.x, m.pos_end.y - 1);
				result.push_back(a1); result.push_back(b1);
				// cập nhật lại bàn cờ
				board[a1.x][a1.y] = player;
				board[b1.x][b1.y] = player;
			}
		}
	}
	return result;
}

vector<Position> vay(int** board, Move m, int player)
{
	vector<Position> result;
	vector<vector<Position>> ds = Lien_Thong(board, -player);   // lấy ds liên thông của quân địch
	int sizeDs = ds.size();

	ganh(board, m, player);	 // thực hiện nước đi

	for (int i = 0; i < sizeDs; i++)
	{
		if (checkMatKhi(board, ds.at(i)) == true)
		{
			int sizeDsCon = ds.at(i).size();
			for (int j = 0; j < sizeDsCon; j++)
			{
				Position var(ds.at(i).at(j).x, ds.at(i).at(j).y);

				board[var.x][var.y] = player;    // cập nhật lại bàn cờ
				result.push_back(var);
			}
		}
	}

	return result;
}

// tìm nước đi của player
Move timMove(int** current_board, int** previous_board, int player)
{
	Position current, previous;
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (previous_board[i][j] == player && current_board[i][j] == NULL)
			{
				previous.x = i;
				previous.y = j;
			}
			if (previous_board[i][j] == NULL && current_board[i][j] == player)
			{
				current.x = i;
				current.y = j;
			}
		}
	}
	Move result(previous, current);
	return result;
}

vector<Move> bay_or_mo(int** current_board, int** previous_board, int player)
{
	vector<Move> result;
	Move var = timMove(current_board, previous_board, -player);
	// vị trí trước và sau của quân địch
	Position current = var.pos_end, previous = var.pos_start;

	// số quân trước và sau của player thay đổi
	int numPrevious = 0;
	int numCurrent = 0;
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (previous_board[i][j] == player)
			{
				numPrevious++;
			}
		}
	}
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (current_board[i][j] == player)
			{
				numCurrent++;
			}
		}
	}

	if (numCurrent != numPrevious)// nếu quân ta có sự thay đổi tức là không xảy ra bẫy
	{
		return result;
	}
	else // số quân trước và sau của player không đổi
	{
		bool kt = false; // kiểm tra xem quân địch có trong thế bẫy hay không?

		if ((previous.x + previous.y) % 2 == 0)  // xét cả đường chéo
		{
			if (previous.x + 1 <= 4 && previous.x - 1 >= 0)     // xét chiều dọc
			{
				if (current_board[previous.x + 1][previous.y] == -player && current_board[previous.x - 1][previous.y] == -player)
				{
					kt = true;
				}
			}

			if (previous.y + 1 <= 4 && previous.y - 1 >= 0)		 // xét chiều ngang
			{
				if (current_board[previous.x][previous.y + 1] == -player && current_board[previous.x][previous.y - 1] == -player)
				{
					kt = true;
				}
			}

			if (previous.y <= 3 && previous.y >= 1 && previous.x <= 3 && previous.x >= 1)   // xét đường chéo
			{
				if (current_board[previous.x + 1][previous.y - 1] == -player && current_board[previous.x - 1][previous.y + 1] == -player)
				{
					kt = true;
				}

				if (current_board[previous.x - 1][previous.y - 1] == -player && current_board[previous.x + 1][previous.y + 1] == -player)
				{
					kt = true;
				}
			}

		}

		else             // Không xét đường chéo
		{
			if (previous.x + 1 <= 4 && previous.x - 1 >= 0)      // xét chiều dọc
			{
				if (current_board[previous.x + 1][previous.y] == -player && current_board[previous.x - 1][previous.y] == -player)
				{
					kt = true;
				}
			}

			if (previous.y + 1 <= 4 && previous.y - 1 >= 0)     // xét chiều ngang
			{
				if (current_board[previous.x][previous.y + 1] == -player && current_board[previous.x][previous.y - 1] == -player)
				{
					kt = true;
				}
			}
		}

		// nếu là bẫy thì add tất cả vị trí mà quân mình phải đi vào result
		if (kt == true)
		{
			if ((previous.x + previous.y) % 2 == 0)
			{
				if (previous.x + 1 <= 4)			// trên
				{
					if (current_board[previous.x + 1][previous.y] == player)
					{
						Move kq(Position(previous.x + 1, previous.y), Position(previous.x, previous.y));
						result.push_back(kq);
					}
				}

				if (previous.x - 1 >= 0)			// dưới
				{
					if (current_board[previous.x - 1][previous.y] == player)
					{
						Move kq(Position(previous.x - 1, previous.y), Position(previous.x, previous.y));
						result.push_back(kq);
					}
				}

				if (previous.y + 1 <= 4)			// phải
				{
					if (current_board[previous.x][previous.y + 1] == player)
					{
						Move kq(Position(previous.x, previous.y + 1), Position(previous.x, previous.y));
						result.push_back(kq);
					}
				}

				if (previous.y - 1 >= 0)			 // trái
				{
					if (current_board[previous.x][previous.y - 1] == player)
					{
						Move kq(Position(previous.x, previous.y - 1), Position(previous.x, previous.y));
						result.push_back(kq);
					}
				}

				if (previous.x + 1 <= 4 && previous.y - 1 >= 0)			// chéo 1
				{
					if (current_board[previous.x + 1][previous.y - 1] == player)
					{
						Move kq(Position(previous.x + 1, previous.y - 1), Position(previous.x, previous.y));
						result.push_back(kq);
					}
				}

				if (previous.y + 1 <= 4 && previous.x + 1 <= 4)			// chéo 2
				{
					if (current_board[previous.x + 1][previous.y + 1] == player)
					{
						Move kq(Position(previous.x + 1, previous.y + 1), Position(previous.x, previous.y));
						result.push_back(kq);
					}
				}

				if (previous.y - 1 >= 0 && previous.x - 1 >= 0)			// chéo 3
				{
					if (current_board[previous.x - 1][previous.y - 1] == player)
					{
						Move kq(Position(previous.x - 1, previous.y - 1), Position(previous.x, previous.y));
						result.push_back(kq);
					}
				}

				if (previous.y + 1 <= 4 && previous.x - 1 >= 0)			 // chéo 4
				{
					if (current_board[previous.x - 1][previous.y + 1] == player)
					{
						Move kq(Position(previous.x - 1, previous.y + 1), Position(previous.x, previous.y));
						result.push_back(kq);
					}
				}
			}
			else
			{
				if (previous.x + 1 <= 4)			// trên
				{
					if (current_board[previous.x + 1][previous.y] == player)
					{
						Move kq(Position(previous.x + 1, previous.y), Position(previous.x, previous.y));
						result.push_back(kq);
					}
				}

				if (previous.x - 1 >= 0)			// dưới
				{
					if (current_board[previous.x - 1][previous.y] == player)
					{
						Move kq(Position(previous.x - 1, previous.y), Position(previous.x, previous.y));
						result.push_back(kq);
					}
				}

				if (previous.y + 1 <= 4)			// phải
				{
					if (current_board[previous.x][previous.y + 1] == player)
					{
						Move kq(Position(previous.x, previous.y + 1), Position(previous.x, previous.y));
						result.push_back(kq);
					}
				}

				if (previous.y - 1 >= 0)			// trái
				{
					if (current_board[previous.x][previous.y - 1] == player)
					{
						Move kq(Position(previous.x, previous.y - 1), Position(previous.x, previous.y));
						result.push_back(kq);
					}
				}
			}

			return result;
		}

		else					// nếu không phải là bẫy
		{
			return result;
		}
	}
}

vector<Move> get_valid_moves(int** current_board, int** previous_board, int player)
{
	vector<Move> result;
	if (previous_board != NULL)
	{
		result = bay_or_mo(current_board, previous_board, player);
	}

	if (result.size() != 0)
	{
		return result;
	}
	else
	{
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				if (current_board[i][j] == player)
				{

					if ((j + i) % 2 == 0)			// xét cả đường chéo
					{
						if (i + 1 <= 4)			// trên
						{
							if (current_board[i + 1][j] != 1 && current_board[i + 1][j] != -1)
							{
								Position a(i, j); Position b(i + 1, j);
								result.push_back(Move(a, b));
							}
						}

						if (i - 1 >= 0)			// dưới		
						{
							if (current_board[i - 1][j] != 1 && current_board[i - 1][j] != -1)
							{
								Position a(i, j); Position b(i - 1, j);
								result.push_back(Move(a, b));
							}
						}

						if (j + 1 <= 4)			// phải			
						{
							if (current_board[i][j + 1] != 1 && current_board[i][j + 1] != -1)
							{
								Position a(i, j); Position b(i, j + 1);
								result.push_back(Move(a, b));
							}
						}

						if (j - 1 >= 0)			// trái		
						{
							if (current_board[i][j - 1] != 1 && current_board[i][j - 1] != -1)
							{
								Position a(i, j); Position b(i, j - 1);
								result.push_back(Move(a, b));
							}
						}

						if (i + 1 <= 4 && j - 1 >= 0)		// chéo 1
						{
							if (current_board[i + 1][j - 1] != 1 && current_board[i + 1][j - 1] != -1)
							{
								Position a(i, j); Position b(i + 1, j - 1);
								result.push_back(Move(a, b));
							}
						}

						if (i + 1 <= 4 && j + 1 <= 4)			// chéo 2
						{
							if (current_board[i + 1][j + 1] != 1 && current_board[i + 1][j + 1] != -1)
							{
								Position a(i, j); Position b(i + 1, j + 1);
								result.push_back(Move(a, b));
							}
						}

						if (i - 1 >= 0 && j - 1 >= 0)			// chéo 3
						{
							if (current_board[i - 1][j - 1] != 1 && current_board[i - 1][j - 1] != -1)
							{
								Position a(i, j); Position b(i - 1, j - 1);
								result.push_back(Move(a, b));
							}
						}

						if (i - 1 >= 0 && j + 1 <= 4)			// chéo 4
						{
							if (current_board[i - 1][j + 1] != 1 && current_board[i - 1][j + 1] != -1)
							{
								Position a(i, j); Position b(i - 1, j + 1);
								result.push_back(Move(a, b));
							}
						}
					}

					else				// không xét đường chéo
					{
						if (i + 1 <= 4)			// trên
						{
							if (current_board[i + 1][j] != 1 && current_board[i + 1][j] != -1)
							{
								Position a(i, j); Position b(i + 1, j);
								result.push_back(Move(a, b));
							}
						}

						if (i - 1 >= 0)			// dưới	
						{
							if (current_board[i - 1][j] != 1 && current_board[i - 1][j] != -1)
							{
								// add
								Position a(i, j);
								Position b(i - 1, j);
								result.push_back(Move(a, b));
							}

						}

						if (j + 1 <= 4)			// phải	
						{
							if (current_board[i][j + 1] != 1 && current_board[i][j + 1] != -1)
							{
								Position a(i, j); Position b(i, j + 1);
								result.push_back(Move(a, b));
							}
						}

						if (j - 1 >= 0)			// trái		
						{
							if (current_board[i][j - 1] != 1 && current_board[i][j - 1] != -1)
							{
								Position a(i, j); Position b(i, j - 1);
								result.push_back(Move(a, b));
							}
						}
					}
				}
			}
		}
	}

	return result;
}

void act_move(int** current_board, Move m, int player)
{
	vay(current_board, m, player);
}

// đếm xem player có bao nhiêu quân trên bàn cờ
int landau = 1;
int stactic(int** current_board, int player)
{
	int numta = 0, numdich = 0;
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (current_board[i][j] == player)
			{
				numta++;
			}
		}
	}

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (current_board[i][j] == -player)
			{
				numdich++;
			}
		}
	}
	int delta = numta - numdich;

	if (landau <= 4 && delta == 0)
	{
		return -4;
	}
	
	return delta;
}

int minimaxPlayer(int** current_board, int** previous_board, int player, int depth, int Max, int Min, Move& bestMove);

int minimaxOpponent(int** current_board, int** previous_board, int player, int depth, int Max, int Min, Move& bestMove)
{
	if (depth >= 7)           // điều kiện dừng
	{
		return stactic(current_board, player);
	}

	vector<Move> successors = get_valid_moves(current_board, previous_board, -player);

	int sizeSuccessors = successors.size();

	if (sizeSuccessors == 0)		// điều kiện dừng
	{
		return stactic(current_board, player);
	}

	for (int i = 0; i < sizeSuccessors; i++)
	{
		int** coppy_curren_board = copy_board(current_board);
		vay(coppy_curren_board, successors[i], -player);

		int result = minimaxPlayer(coppy_curren_board, current_board, player, depth + 1, Max, Min, bestMove);

		if (coppy_curren_board != NULL)
		{
			for (int i = 0; i < 5; i++)
			{
				delete coppy_curren_board[i];
			}
		}

		if (result < Min)
		{
			Min = result;
		}
		if (Min <= Max)
		{
			return Min;
		}
	}

	return Min;
}

int minimaxPlayer(int** current_board, int** previous_board, int player, int depth, int Max, int Min, Move& bestMove)
{
	if (depth >= 7)			// điều kiện dừng
	{
		return stactic(current_board, player);
	}
	vector<Move> successors = get_valid_moves(current_board, previous_board, player);

	int sizeSuccessors = successors.size();

	if (sizeSuccessors == 0)		// điều kiện dừng
	{
		return stactic(current_board, player);
	}
	int** coppy_curren_board;
	for (int i = 0; i < sizeSuccessors; i++)
	{
		coppy_curren_board = copy_board(current_board);

		vay(coppy_curren_board, successors[i], player);		// cập nhật bàn cờ mới

		int result = minimaxOpponent(coppy_curren_board, current_board, player, depth + 1, Max, Min, bestMove);

		if (result > Max)
		{
			if (depth == 1)
			{
				bestMove = successors[i];
			}
			Max = result;
		}

		if (Max >= Min)
		{
			return Max;
		}
			
	}
	return Max;
}

//////////////////////////////////// 

Move select_move(int** current_board, int** previous_board, int player)
{
	landau++;
	Move bestMove(Position(-1, -1), Position(-1, -1));
	minimaxPlayer(current_board, previous_board, player, 1, -100, 100, bestMove);
	return bestMove;
}


//void play(int first)
//{
//	int count = 0, limit = 70;
//	int player;
//	if (first == 1)
//		player = 1;
//	else
//		player = -1;
//
//	int** board = init_board();
//	int** pre_board = nullptr;
//	print_board(board);
//	while (count < limit)
//	{
//		count++;
//		vector<Move> valid_moves = get_valid_moves(board, pre_board, player);
//		if (valid_moves.size() != 0)
//		{
//			srand(time(NULL));
//			int index = rand() % valid_moves.size();
//			Move new_move = valid_moves[index];
//			pre_board = copy_board(board);
//			act_move(board, new_move, player);
//		}
//		else
//			break;
//		player *= -1;
//	}
//}
//void playUser(int first)
//{
//	int count = 0, limit = 25;
//	int player;
//
//	if (first == 1)
//	{
//		player = 1;
//	}
//	else
//	{
//		player = -1;
//	}
//
//	int** board = init_board();
//	int** pre_board = nullptr;
//	print_board(board);
//
//	while (count < limit)
//	{
//		count++;
//		vector<Move> valid_moves = get_valid_moves(board, pre_board, player);
//
//		if (valid_moves.size() != 0)
//		{
//			if (player == 1)
//			{
//				Move new_move2 = select_move(board, pre_board, player);
//				pre_board = copy_board(board);
//				act_move(board, new_move2, player);
//
//				//print_board(board);
//				//cout << endl;
//			}
//			else
//			{
//				srand(time(NULL));
//				int index = rand() % valid_moves.size();
//				Move new_move = valid_moves[index];
//				pre_board = copy_board(board);
//				act_move(board, new_move, player);
//			}
//		}
//		else
//		{
//			break;
//		}
//
//		player *= -1;
//	}
//
//	cout << endl;
//	print_board(board);
//}
Move select_move_random(int** current_board, int** previous_board, int player)
{
	vector<Move> ds = get_valid_moves(current_board, previous_board, player);

	int i = rand() % ds.size();

	return ds[i];
}

int demSoQuan1(int** current_board, int player)
{
	int soQuanMinh = 0;
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (current_board[i][j] == player)
			{
				soQuanMinh++;
			}
		}
	}

	return soQuanMinh;
}

int opponentRec1(int** current_board, int** previous_board, int player, int depth, Move& bestMove, int maxValue, int minValue);

int playerRec1(int** current_board, int** previous_board, int player, int depth, Move& bestMove, int maxValue, int minValue);

int opponentRec1(int** current_board, int** previous_board, int player, int depth, Move& bestMove, int maxValue, int minValue)
{
	if (depth >= 4)
	{
		return demSoQuan1(current_board, player); //Dem so quan cua minh
	}

	vector<Move> nuocPhaiDi = get_valid_moves(current_board, previous_board, -player); // Ban co doi thu
	int size_nuocPhaiDi = nuocPhaiDi.size();

	if (size_nuocPhaiDi == 0)
	{
		return demSoQuan1(current_board, player); //Dem so quan cua minh
	}

	for (int i = 0; i < size_nuocPhaiDi; i++)
	{
		Move nuocPhaiDi_i = nuocPhaiDi[i];

		int** coppy_current_board = copy_board(current_board);
		vay(coppy_current_board, nuocPhaiDi_i, -player); // Ban co doi thu

		int newValue = playerRec1(coppy_current_board, current_board, player, depth + 1, bestMove, maxValue, minValue);

		if (newValue < minValue)
		{
			minValue = newValue;
		}

		if (minValue <= maxValue)
		{
			//Giai phong vung nho rac
			for (int i = 0; i < 5; i++)
			{
				delete[] coppy_current_board[i];
			}

			delete[] coppy_current_board;

			return minValue;
		}

		//Giai phong vung nho rac
		for (int i = 0; i < 5; i++)
		{
			delete[] coppy_current_board[i];
		}

		delete[] coppy_current_board;
	}

	return minValue;
}

int playerRec1(int** current_board, int** previous_board, int player, int depth, Move& bestMove, int maxValue, int minValue)
{
	if (depth >= 4)
	{
		return demSoQuan1(current_board, player);
	}

	vector<Move> nuocPhaiDi = get_valid_moves(current_board, previous_board, player);
	int size_nuocPhaiDi = nuocPhaiDi.size();

	if (size_nuocPhaiDi == 0)
	{
		return demSoQuan1(current_board, player);
	}

	for (int i = 0; i < size_nuocPhaiDi; i++)
	{
		Move nuocPhaiDi_i = nuocPhaiDi[i];

		int** coppy_current_board = copy_board(current_board);
		vay(coppy_current_board, nuocPhaiDi_i, player);

		int newValue = opponentRec1(coppy_current_board, current_board, player, depth + 1, bestMove, maxValue, minValue);

		if (newValue > maxValue)
		{
			maxValue = newValue;

			if (depth == 1)
			{
				bestMove = nuocPhaiDi_i;
			}
		}

		if (maxValue >= minValue)
		{
			//Giai phong vung nho rac
			for (int i = 0; i < 5; i++)
			{
				delete[] coppy_current_board[i];
			}

			delete[] coppy_current_board;

			return maxValue;
		}

		// Giai phong vung nho rac
		for (int i = 0; i < 5; i++)
		{
			delete[] coppy_current_board[i];
		}

		delete[] coppy_current_board;
	}

	return maxValue;
}

Move select_move1(int** current_board, int** previous_board, int player)
{
	Move bestMove(Position(-100, -100), Position(100, 100));

	playerRec1(current_board, previous_board, player, 1, bestMove, -100, 100);

	return bestMove;
}

void playUser(int first)
{
	int count = 0, limit = 25;
	int player;

	if (first == 1)
	{
		player = 1;
	}
	else
	{
		player = -1;
	}

	int** board = init_board();
	int** pre_board = nullptr;
	print_board(board);
	cout << endl;

	while (count < limit)
	{
		count++;
		vector<Move> valid_moves = get_valid_moves(board, pre_board, player);

		if (valid_moves.size() != 0)
		{
			if (player == -1)
			{
				Move new_move = select_move(board, pre_board, player);
				pre_board = copy_board(board);
				act_move(board, new_move, player);

				system("cls");
				print_board(board);
				cout << endl;
			}
			else
			{
				Move new_move = select_move1(board, pre_board, player);
				pre_board = copy_board(board);
				act_move(board, new_move, player);

				system("cls");
				print_board(board);
				cout << endl;
			}
		}
		else
		{
			break;
		}

		player *= -1;
	}

	for (int i = 0; i < 5; i++)
	{
		delete[] board[i];
		if (pre_board != NULL)
		{
			delete[] pre_board[i];
		}
	}

	delete[] board;
	delete[] pre_board;
}

int main()
{
	srand((int)time(0));

	playUser(-1);

	system("pause");
	return 0;
}