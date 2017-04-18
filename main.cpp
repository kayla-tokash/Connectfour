#include <iostream>

#define WIDTH 7
#define HEIGHT 6

#define DEFAULT 0
#define PLAYER1 1
#define PLAYER2 2

#define MIN_CONNECTED 4
#define INVALID_COLUMN -1
#define PLAY_AGAIN "y"

using namespace std;

class ConnectFour {
private:
    int board[HEIGHT][WIDTH];
    int checkAdjacentTile(int n, int row, int col, int i, int j) {
        if (row >= WIDTH || row < 0 || col >= HEIGHT || col < 0 || board[row][col] == DEFAULT || board[row][col] != n) {
            return 0;
        }
        else {
            return checkAdjacentTile(n, row + i, col + j, i, j) + 1;
        }
    };
    int checkStreaks(int row, int col) {
        int streak[8];
        streak[0] = checkAdjacentTile(board[row][col], row, col, -1, 0);
        streak[1] = checkAdjacentTile(board[row][col], row, col, 0, 1);
        streak[2] = checkAdjacentTile(board[row][col], row, col, 1, 1);
        streak[3] = checkAdjacentTile(board[row][col], row, col, 1, 0);
        streak[4] = checkAdjacentTile(board[row][col], row, col, 0, -1);
        streak[5] = checkAdjacentTile(board[row][col], row, col, -1, -1);
        streak[6] = checkAdjacentTile(board[row][col], row, col, -1, 1);
        streak[7] = checkAdjacentTile(board[row][col], row, col, 1, -1);

        int longestStreak = 0;
        for (int i = 0; i < 8; i ++) {
            longestStreak = (longestStreak > streak[i]) ? longestStreak : streak[i];
        }

        return longestStreak;
    }
public:
    bool setBoard(int x, int y, int player);
    int checkBoard();
    void resetBoard();
    void printBoard();
    int getFreeRowInColumn(int col);
};

bool ConnectFour::setBoard(int x, int y, int player) {
    if (board[y][x] != 0)
        return false;
    board[y][x] = player;
    return true;
}

void ConnectFour::resetBoard() {
    for(int row = 0; row < HEIGHT; row++) {
        for(int col = 0; col < WIDTH; col++) {
            board[row][col] = 0;
        }
    }
}

int ConnectFour::checkBoard() {
    int playerOne = 0, playerTwo = 0;

    for(int row = 0; row < HEIGHT; row++) {
        for(int col = 0; col < WIDTH; col++) {
            int streak = checkStreaks(row, col);
            if (board[row][col] == PLAYER1) {
                playerOne = (playerOne > streak) ? playerOne : streak;
            } else if (board[row][col] == PLAYER2) {
                playerTwo = (playerTwo > streak) ? playerTwo : streak;
            }
        }
    }

    cout << "Player1 longest streak = " << playerOne << endl;
    cout << "Player2 longest streak = " << playerTwo << endl;

    return (playerOne >= MIN_CONNECTED || playerTwo >= MIN_CONNECTED) ?
           ((playerOne > playerTwo) ? PLAYER1 : PLAYER2) : DEFAULT;
}

int ConnectFour::getFreeRowInColumn(int col) {
    for (int row = 0; row < HEIGHT; row++) {
        if (board[row][col] == DEFAULT)
            return row;
    }
    return INVALID_COLUMN;
}

void ConnectFour::printBoard() {
    for(int row = HEIGHT - 1; row >= 0; row--) {
        for(int col = 0; col < WIDTH; col++) {
            if (board[row][col] != DEFAULT) {
                cout << board[row][col];
            }
            else {
                cout << '.';
            }
        }
        cout << endl;
    }
    cout << endl << "1234567" << endl;
}


int main() {
    ConnectFour *game = new ConnectFour();
    int player = DEFAULT;
    int x;
    int y;
    string confirm = PLAY_AGAIN;
    do {
        do {
            player = (player == PLAYER1) ? PLAYER2 : PLAYER1;
            game->printBoard();
            cout << "Player" << player << "'s turn." << endl;
            do {
                do {
                    int column;
                    cout << "What is the column?" << endl << "> ";
                    cin >> column;
                    x = column - 1;
                } while (!(x >= 0 && x <= WIDTH));
                y = game->getFreeRowInColumn(x);
                if (y == INVALID_COLUMN)
                    cout << "Invalid column. Please try again." << endl;
            } while (y == INVALID_COLUMN);

            game->setBoard(x, y, player);
        } while (DEFAULT == game->checkBoard());
        cout << "Player" << player << " wins!" << endl << "Play again? (y/n) ";
        cin >> confirm;
    } while (confirm == PLAY_AGAIN);

}

