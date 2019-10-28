#include <iostream>
#define MAX_N 100
#define WALL -2
#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3
using namespace std;

struct WARMHOLE{
	int x, y;
}wh[2][5];

struct BALL{
	int curX, curY;
	int dir, score;
}ball;

int N, Board[MAX_N+2][MAX_N+2], maxScore;
const int dx[4] = { 0, 0, -1, 1 };
const int dy[4] = { -1, 1, 0, 0 };
const int changeDir[4][6] = {
	// wall, 1, 2, 3, 4, 5
	{DOWN, DOWN, RIGHT, LEFT, DOWN, DOWN},	// UP
	{UP, RIGHT, UP, UP, LEFT, UP },	// DONW
	{RIGHT, UP, DOWN, RIGHT, RIGHT, RIGHT},	// LEFT
	{LEFT, LEFT, LEFT, DOWN, UP, LEFT}	// RIGHT
};

void reset(){
	N = 0;

	for (int i = 0; i < 2; i++){
		for (int j = 0; j < 5; j++){
			wh[i][j].x = -1;
			wh[i][j].y = -1;
		}
	}

	for (int i = 0; i < MAX_N + 2; i++)
		for (int j = 0; j < MAX_N + 2; j++)
			Board[i][j] = WALL;
}

void init(){
	cin >> N;

	for (int y = 1; y <= N; y++){
		for (int x = 1; x <= N; x++){
			cin >> Board[y][x];
			if (Board[y][x] >= 6 && Board[y][x] <= 10){
				if (wh[0][Board[y][x] - 6].x == -1){
					wh[0][Board[y][x] - 6].x = x;
					wh[0][Board[y][x] - 6].y = y;
				}
				else{
					wh[1][Board[y][x] - 6].x = x;
					wh[1][Board[y][x] - 6].y = y;
				}
			}
		}
	}
}

void goWarmhole(int whNum){
	if ((wh[0][whNum - 6].x == ball.curX) && (wh[0][whNum - 6].y == ball.curY)){
		ball.curX = wh[1][whNum - 6].x;
		ball.curY = wh[1][whNum - 6].y;
	}
	else{
		ball.curX = wh[0][whNum - 6].x;
		ball.curY = wh[0][whNum - 6].y;
	}
}

int simulation(int sx, int sy, int dir){
	ball.score = 0;
	ball.curX = sx;
	ball.curY = sy;
	ball.dir = dir;

	while (true){
		ball.curX += dx[ball.dir];
		ball.curY += dy[ball.dir];

		if ((ball.curX == sx) && (ball.curY == sy))
			break;
		else if (Board[ball.curY][ball.curX] == -1)
			break;
		else if (Board[ball.curY][ball.curX] == WALL){
			ball.score++;
			ball.dir = changeDir[ball.dir][0];
		}
		else if (Board[ball.curY][ball.curX] >= 1 && Board[ball.curY][ball.curX] <= 5){
			ball.score++;
			ball.dir = changeDir[ball.dir][Board[ball.curY][ball.curX]];
		}
		else if ((Board[ball.curY][ball.curX] >= 6 && Board[ball.curY][ball.curX] <= 10)){
			goWarmhole(Board[ball.curY][ball.curX]);
		}
	}
	return ball.score;
}

int main(int argc, char** argv){
	cin.tie(NULL);	cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	int T;
	cin >> T;

	for (int testcase = 1; testcase <= T; testcase++){
		reset();
		init();
		
		maxScore = 0;
		int score;
		for (int y = 1; y <= N; y++){
			for (int x = 1; x <= N; x++){
				if (Board[y][x] == 0){
					for (int k = 0; k < 4; k++){
						score = simulation(x, y, k);
						maxScore = maxScore >= score ? maxScore : score;
					}
				}
			}
		}

		cout << "#" << testcase << " " << maxScore << "\n";
	}

	return 0;
}