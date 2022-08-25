# Co_Ganh_DSA
Assignment Cờ Gánh DSA

vector<Move> get_valid_moves(int** board, int player);
-> trả về các nước đi hợp lệ với trạng thái bàn cờ hiện tại board, và lượt chơi của player (1 hoặc -1)
  
vector<Position> ganh(int** board, Move m, int player);
-> trả về danh sách vị trí của các quân của địch bị gánh

vector<Position> vay(int** board, Move m, int player);
-> trả về danh sách vị trí các quân bị vây

Hàm vector<Position> bay_or_mo(Move m, int** current_board, int** previous_board, int player);
-> trả về các nước đi phải đi theo luật bẫy mà player phải đi dựa trên current_board và previous_board
  
Dùng giải thuật minimax và adding alpha-beta cutoffs để tìm nước đi tốt nhất với độ sâu thứ n cho trước.
