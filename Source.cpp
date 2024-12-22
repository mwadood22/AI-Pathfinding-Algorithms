#include <iostream>
#include <string>
#include <fstream>
#include <Windows.h>
using namespace std;

struct Node
{
	int x;
	int y;
	int pathCost;
	int heuristic;
	int parentX;
	int parentY;
	char obstacle;
	bool moveRight;
	bool moveUp;
	bool moveDiagonal;
	bool visited;
	bool explored;
	int cost;

	Node()
	{
		x = -1;
		y = -1;
		parentX = -1;
		parentY = -1;
		heuristic = -1;
		visited = false;
		explored = false;
		cost = 0;
	}

};
int row, col;
int startRow, startCol;
int goalRow, goalCol;
Node** grid = NULL;

struct PriorityQueue
{
	Node* node[140];
	int current = -1;

	PriorityQueue()
	{
		for (int i = 0; i < 140; i++)
		{
			node[i] = NULL;
		}
	}

	void Enqueue(Node* n)
	{
		current++;
		node[current] = n;
	}

	Node* SimpleDequeue()
	{
		int index = current;
		current--;
		return node[index];
	}

	Node* Dequeue()
	{
		Node* temp = node[0];
		int minIndex = 0;
		for (int i = 0; i < 140; i++)
		{
			if (node[i] == NULL)
				break;

			if (temp->pathCost > node[i]->pathCost)
			{
				temp = node[i];
				minIndex = i;
			}
		}

		for (int i = minIndex; i < 139; i++)
		{
			node[i] = node[i + 1];
		}
		current--;
		return temp;
	}
	Node* Dequeue_Iterative_Deepening()
	{
		Node* temp = node[0];
		int minIndex = 0;
		for (int j = 0; j < 140; j++)
		{
			for (int i = 0; i < 140; i++)
			{
				if (node[i] == NULL)
					break;

				if (temp->pathCost > node[i]->pathCost)
				{
					temp = node[i];
					minIndex = i;
				}
			}
		}
		for (int i = minIndex; i < 139; i++)
		{
			node[i] = node[i + 1];
		}
		current--;
		return temp;
	}

};

void showMenu()
{
	cout << "Press:\n";
	cout << "0: Exit\n";
	cout << "1: Greedy Best First Search\n";
	cout << "2: A* Search\n";
	cout << "3: Iterative Deepening A* Search\n ";
}

bool readFile()
{
	ifstream in;
	in.open("grid.txt");
	if (!in)
	{
		return false;
	}
	in >> col;
	in >> row;
	in >> startCol;
	in >> startRow;
	in >> goalCol;
	in >> goalRow;

	startRow = row - startRow - 1;
	goalRow = row - goalRow - 1;

	grid = new Node*[row];
	for (int i = 0; i < row; i++)
	{
		grid[i] = new Node[col];
	}

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			in >> grid[i][j].obstacle;
			grid[i][j].x = i;
			grid[i][j].y = j;
		}
	}

	return true;
}

void calculateHeuristic()
{
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			grid[i][j].heuristic = abs(grid[i][j].x - grid[goalRow][goalCol].x) + abs(grid[i][j].y - grid[goalRow][goalCol].y);
			grid[i][j].pathCost = grid[i][j].heuristic;
		}
	}
}


void bfs()
{
	Node** bfsGrid = new Node*[row];
	for (int i = 0; i < row; i++)
		bfsGrid[i] = new Node[col];

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
			bfsGrid[i][j] = grid[i][j];
	}

	cout << "\t\t\t\t\tBest First Search\n";
	PriorityQueue queue;
	queue.Enqueue(&bfsGrid[startRow][startCol]);
	bool pathFound = false;
	int x;
	int y;

	while (!pathFound)	
	{


		Node* current = queue.Dequeue();
		x = current->x;
		y = current->y;

		if (x == goalRow && y == goalCol)
		{

			cout << "Goal Found" << endl;
			pathFound = true;
		}


		if (x - 1 >= 0 && bfsGrid[x - 1][y].obstacle != '1') 
		{
			bfsGrid[x - 1][y].parentX = x;
			bfsGrid[x - 1][y].parentY = y;
			bfsGrid[x - 1][y].cost = current->cost + 1;
			queue.Enqueue(&bfsGrid[x - 1][y]);
		}
		if (x - 1 >= 0 && y + 1 < col && bfsGrid[x - 1][y + 1].obstacle != '1') 
		{
			bfsGrid[x - 1][y + 1].parentX = x;
			bfsGrid[x - 1][y + 1].parentY = y;
			bfsGrid[x - 1][y + 1].cost = current->cost + 2;
			queue.Enqueue(&bfsGrid[x - 1][y + 1]);
		}

		if (y + 1 < col && bfsGrid[x][y + 1].obstacle != '1')
		{
			bfsGrid[x][y + 1].parentX = x;
			bfsGrid[x][y + 1].parentY = y;
			bfsGrid[x][y + 1].cost = current->cost + 3;;
			queue.Enqueue(&bfsGrid[x][y + 1]);
		}



	}

	Node* goal;

	while (true)
	{
		goal = &bfsGrid[x][y];
		goal->obstacle = '*';
		if (x == startRow && y == startCol)
			break;
		x = goal->parentX;
		y = goal->parentY;
	}

	bfsGrid[startRow][startCol].obstacle = 'S';
	bfsGrid[goalRow][goalCol].obstacle = 'G';
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			if (bfsGrid[i][j].obstacle == '*' || bfsGrid[i][j].obstacle == 'G' || bfsGrid[i][j].obstacle == 'S')
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);

			cout << bfsGrid[i][j].obstacle << "\t";
		}
		cout << endl;
	}

	cout << "Path Cost = " << bfsGrid[goalRow][goalCol].cost << endl;
	system("pause>0");
	system("cls");

}

void aStar()
{
	Node** aStarGrid = new Node*[row];
	for (int i = 0; i < row; i++)
		aStarGrid[i] = new Node[col];

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
			aStarGrid[i][j] = grid[i][j];
	}


	cout << "\t\t\t\t\tA* Search\n";
	PriorityQueue queue;
	queue.Enqueue(&aStarGrid[startRow][startCol]);
	bool pathFound = false;
	int x;
	int y;

	while (!pathFound)	
	{
		Node* current = queue.Dequeue();
		current->visited = true;
		current->explored = true;
		x = current->x;
		y = current->y;

		if (x == goalRow && y == goalCol)
		{
			cout << "Goal Found" << endl;
			pathFound = true;
		}

		if (y + 1 < col && aStarGrid[x][y + 1].obstacle != '1' && aStarGrid[x][y + 1].visited == false)
		{
			aStarGrid[x][y + 1].visited = true;
			aStarGrid[x][y + 1].parentX = x;
			aStarGrid[x][y + 1].parentY = y;
			aStarGrid[x][y + 1].cost = current->cost + 3;
			aStarGrid[x][y + 1].pathCost = aStarGrid[x][y + 1].cost + aStarGrid[x][y + 1].heuristic;
			queue.Enqueue(&aStarGrid[x][y + 1]);
		}

		if (x - 1 >= 0 && y + 1 < col && aStarGrid[x - 1][y + 1].obstacle != '1' && aStarGrid[x - 1][y + 1].visited == false)
		{
			aStarGrid[x - 1][y + 1].visited = true;
			aStarGrid[x - 1][y + 1].parentX = x;
			aStarGrid[x - 1][y + 1].parentY = y;
			aStarGrid[x - 1][y + 1].cost = current->cost + 2;
			aStarGrid[x - 1][y + 1].pathCost = aStarGrid[x - 1][y + 1].cost + aStarGrid[x - 1][y + 1].heuristic;
			queue.Enqueue(&aStarGrid[x - 1][y + 1]);
		}

		if (x - 1 >= 0 && aStarGrid[x - 1][y].obstacle != '1' && aStarGrid[x - 1][y].visited == false)
		{
			aStarGrid[x - 1][y].visited = true;
			aStarGrid[x - 1][y].parentX = x;
			aStarGrid[x - 1][y].parentY = y;
			aStarGrid[x - 1][y].cost = current->cost + 1;
			aStarGrid[x - 1][y].pathCost = aStarGrid[x - 1][y].cost + aStarGrid[x - 1][y].heuristic;
			queue.Enqueue(&aStarGrid[x - 1][y]);
		}
	}

	Node* goal;

	while (true)	
	{
		goal = &aStarGrid[x][y];
		goal->obstacle = '*';
		if (x == startRow && y == startCol)
			break;
		x = goal->parentX;
		y = goal->parentY;
	}

	aStarGrid[startRow][startCol].obstacle = 'S';
	aStarGrid[goalRow][goalCol].obstacle = 'G';
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			if (aStarGrid[i][j].obstacle == '*' || aStarGrid[i][j].obstacle == 'G' || aStarGrid[i][j].obstacle == 'S')
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);

			cout << aStarGrid[i][j].obstacle << "\t";
		}
		cout << endl;
	}

	cout << "Path Cost = " << aStarGrid[goalRow][goalCol].pathCost << endl;;
	system("pause>0");
	system("cls");

}
void IDAstar()
{
	Node** aStarGrid = new Node*[row];
	for (int i = 0; i < row; i++)
		aStarGrid[i] = new Node[col];

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
			aStarGrid[i][j] = grid[i][j];
	}

	cout << "\t\t\t\t\tIterative Deepening A* Search\n";
	PriorityQueue queue;
	queue.Enqueue(&aStarGrid[startRow][startCol]);
	bool pathFound = false;
	int x;
	int y;

	while (!pathFound)	
	{
		Node* current = queue.Dequeue_Iterative_Deepening();
		current->visited = true;
		current->explored = true;
		x = current->x;
		y = current->y;

		if (x == goalRow && y == goalCol)
		{
			cout << "Goal Found" << endl;
			pathFound = true;
		}

		if (y + 1 < col && aStarGrid[x][y + 1].obstacle != '1' && aStarGrid[x][y + 1].visited == false)
		{
			aStarGrid[x][y + 1].visited = true;
			aStarGrid[x][y + 1].parentX = x;
			aStarGrid[x][y + 1].parentY = y;
			aStarGrid[x][y + 1].cost = current->cost + 3;
			aStarGrid[x][y + 1].pathCost = aStarGrid[x][y + 1].cost + aStarGrid[x][y + 1].heuristic;
			queue.Enqueue(&aStarGrid[x][y + 1]);
		}

		if (x - 1 >= 0 && y + 1 < col && aStarGrid[x - 1][y + 1].obstacle != '1' && aStarGrid[x - 1][y + 1].visited == false)
		{
			aStarGrid[x - 1][y + 1].visited = true;
			aStarGrid[x - 1][y + 1].parentX = x;
			aStarGrid[x - 1][y + 1].parentY = y;
			aStarGrid[x - 1][y + 1].cost = current->cost + 2;
			aStarGrid[x - 1][y + 1].pathCost = aStarGrid[x - 1][y + 1].cost + aStarGrid[x - 1][y + 1].heuristic;
			queue.Enqueue(&aStarGrid[x - 1][y + 1]);
		}

		if (x - 1 >= 0 && aStarGrid[x - 1][y].obstacle != '1' && aStarGrid[x - 1][y].visited == false)
		{
			aStarGrid[x - 1][y].visited = true;
			aStarGrid[x - 1][y].parentX = x;
			aStarGrid[x - 1][y].parentY = y;
			aStarGrid[x - 1][y].cost = current->cost + 1;
			aStarGrid[x - 1][y].pathCost = aStarGrid[x - 1][y].cost + aStarGrid[x - 1][y].heuristic;
			queue.Enqueue(&aStarGrid[x - 1][y]);
		}
	}

	Node* goal;

	while (true)	
	{
		goal = &aStarGrid[x][y];
		goal->obstacle = '*';
		if (x == startRow && y == startCol)
			break;
		x = goal->parentX;
		y = goal->parentY;
	}

	aStarGrid[startRow][startCol].obstacle = 'S';
	aStarGrid[goalRow][goalCol].obstacle = 'G';
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			if (aStarGrid[i][j].obstacle == '*' || aStarGrid[i][j].obstacle == 'G' || aStarGrid[i][j].obstacle == 'S')
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);

			cout << aStarGrid[i][j].obstacle << "\t";
		}
		cout << endl;
	}

	cout << "Path Cost = " << aStarGrid[goalRow][goalCol].pathCost << endl;;
	system("pause>0");
	system("cls");

}


int main()
{

	if (!readFile())
	{
		cout << "File cannot be opened\n";
		system("pause");
		return 0;
	}

	calculateHeuristic();

	while (true)
	{
		showMenu();
		int opt;
		cin >> opt;
		system("cls");

		if (opt == 1) 
		{
			bfs();
		}
		
		else if (opt == 2) 
		{
			aStar();
		}
		else if (opt == 3) 
		{
		    IDAstar();
		}
			
		else
		{
			return (-1);
		}
	}

	system("pause>0");
	return 0;
}
