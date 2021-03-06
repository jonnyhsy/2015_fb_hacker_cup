#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <cassert>
#include <queue>
using namespace std;

typedef struct Node{
	int x;
	int y;
	Node(){}
	Node(int xx, int yy):x(xx), y(yy){}
}Node;

char board[100][100];
int M, N;
int direction[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}}; // 0:^ | 1:> | 2:v | 3:< 
char board_step[4][100][100];

bool is_laser(char ch)
{
	if(ch == '^' || ch == '>' || ch == 'v' || ch == '<')
		return true;
	return false;
}

bool could_place(char ch)
{
	if(ch == '.' || ch == 'S' || ch == 'G')
		return true;
	return false;
}

int parse_direction(char ch)
{
	switch(ch)
	{
		case '^':
			return 0;
		case '>':
			return 1;
		case 'v':
			return 2;
		case '<':
			return 3;
		default:
			assert(false);
	}
}

void print_board()
{
	for(int i = 0; i < M; i++)
	{
		for(int j = 0; j < N; j++)
			printf("%c", board[i][j]);
		printf("\n");
	}
}

void print_board_step(int k)
{
	printf("board step %d:\n", k);
	for(int i = 0; i < M; i++)
	{
		for(int j = 0; j < N; j++)
			printf("%c", board_step[k][i][j]);
		printf("\n");
	}
}

void BFS(Node &start)
{
	int step = 0;
	int tx, ty;
	queue<Node> Q;
	Q.push(start);
	board_step[0][start.x][start.y] = '#';  // mark entry point in board_step[0] as visited...
	while(!Q.empty())
	{
		int num = Q.size();
		for(int i = 0; i < num; i++)
		{
			Node u = Q.front();
			Q.pop();
			if(board[u.x][u.y] == 'G')
			{
				cout << step << endl;
				return;
			}
			for(int j = 0; j < 4; j++)
			{
				tx = u.x + direction[j][0];
				ty = u.y + direction[j][1];
				if(tx >= 0 && tx < M && ty >= 0 && ty < N && could_place(board_step[(step+1) % 4][tx][ty]))
				{
					board_step[(step+1) % 4][tx][ty] = '#'; // mark as visited, couldn't be placed any more.
					Q.push(Node(tx, ty));
				}
			}
		}
		step++;
	}
	cout << "impossible" << endl; // not possible
}

int main(int argc, char *argv[])
{
	int T;
	char ch;
	scanf("%d", &T);
	for(int i = 1; i <= T; i++)
	{
		memset(board, 0, sizeof(board));
		Node start(-1, -1);
		scanf("%d %d", &M, &N);
		for(int j = 0; j < M; j++)
		{
			scanf("%s", board[j]);
			if(start.x == -1 && start.y == -1) // retrieve entry point
			{	
				for(int k = 0; k < N; k++)
				{
					if(board[j][k] == 'S')
					{
						start.x = j;
						start.y = k;
						break;
					}
				}
			}
		}
		// generate 4 boards...
		for(int j = 0; j < 4; j++)
		{
			memcpy(board_step[j], board, sizeof(board));
			for(int s = 0; s < M; s++)
				for(int t = 0; t < N; t++)
				{
					ch = board_step[j][s][t];
					if(is_laser(ch))
					{
						int dir = (parse_direction(ch) + j) % 4;
						board_step[j][s][t] = '#';
						int tx = s + direction[dir][0];
						int ty = t + direction[dir][1];
						while(tx >= 0 && tx < M && ty >= 0 && ty < N && could_place(board[tx][ty]))
						{
							board_step[j][tx][ty] = '#';
							tx += direction[dir][0];
							ty += direction[dir][1];
						}
					}
				}
			print_board_step(j);
		}
		cout << "Case #" << i << ": ";
		BFS(start);
	}
	return 0;
}
