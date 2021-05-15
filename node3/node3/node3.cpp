#include <iostream>
#include <vector>
#include <time.h>

using namespace std;

const int SIZE = 6;

inline double prob() { return (rand() % 100) / 100.0; }

class Graph
{
public:
	Graph(double n, int range);
	int V() { return SIZE * SIZE; };
	int E() { return (SIZE * (SIZE - 1)) / 2; }
	bool adjacent(int x, int y);
	void neighbors(int x);
	void add(int x, int y);
	void del(int x, int y) { matrix[x][y] = matrix[y][x] = 0; }
	int get_edge_value(int x, int y) { return matrix[x][y]; }
	void set_edge_value(int x, int y, int v) { matrix[x][y] = matrix[y][x] = v; }
	void print();
	bool is_connected();

private:
	vector<vector<int>> matrix;
};

class PriorityQueue
{
public:
	void chgPriority(int priority);
	void minPrioirty();
	bool contains(int queue_element);
	void insert(int queue_element);
	int top();
	int size();

private:
	vector<int> x;
};

class ShortestPath
{
public:
	void vertices();
	void path(int u, int w);
	int path_size(int u, int w);
};

Graph::Graph(double n, int range)
{

	for (int i = 0; i < SIZE; ++i)
	{
		vector<int> y;
		for (int j = 0; j < SIZE; ++j)
		{
			y.push_back(0);
		}
		matrix.push_back(y);
	}

	for (int i = 0; i < SIZE; ++i)
	{
		for (int j = i; j < SIZE; ++j)
		{
			if (i == j)
				matrix[i][j] = 0;
			else
			{
				if (prob() < n)
					matrix[i][j] = matrix[j][i] = (rand() % range) + 1;
				else
					matrix[i][j] = matrix[i][j] = 0;
			}
		}
	}
}

bool Graph::adjacent(int x, int y)
{
	int old_size = 0, c_size = 0;
	vector<bool> close(SIZE);
	vector<bool> open(SIZE);
	if (matrix[x][y])
	{
		return true;
	}
	for (int i = 0; i < SIZE; ++i)
	{
		open[i] = close[i] = false;
	}
	open[x] = true;
	while (c_size < SIZE) {
		for (int i = 0; i < SIZE; ++i)
		{
			old_size = c_size;
			if (open[i] && (close[i] == false))
			{
				close[i] = true;
				c_size++;
			}
			for (int j = 0; j < SIZE; ++j) {
				if (open[i]) {
					open[j] = open[j] || matrix[i][j];
				}
			}
		}
		if (open[y] == true)
			return true;
		if (old_size == c_size)
			return false;
	}
}

void Graph::neighbors(int x) {
	int old_size = 0, c_size = 0;
	vector<bool> close(SIZE);
	vector<bool> open(SIZE);
	for (int i = 0; i < SIZE; ++i)
	{
		open[i] = close[i] = false;
	}
	open[x] = true;
	while (c_size < SIZE) {
		for (int i = 0; i < SIZE; ++i)
		{
			old_size = c_size;
			if (open[i] && (close[i] == false))
			{
				close[i] = true;
				c_size++;
			}
			for (int j = 0; j < SIZE; ++j) {
				if (open[i]) {
					open[j] = open[j] || matrix[i][j];
				}
			}
		}
		if (c_size == SIZE || old_size == c_size) {
			for (int i = 0; i < SIZE; ++i) {
				if (open[i])
					cout << i << ", ";
			}
			return;
		}
	}
	cout << endl;
}

void Graph::add(int x, int y) {
	if (!matrix[x][y])
		matrix[x][y] = matrix[y][x] = 1;
}



void Graph::print()
{
	for (int i = 0; i < SIZE; ++i)
	{
		for (int j = 0; j < SIZE; ++j)
		{
			cout << matrix[i][j] << ", ";
		}
		cout << endl;
	}
}

bool Graph::is_connected()
{
	int old_size = 0, c_size = 0;
	vector<bool> close(SIZE);
	vector<bool> open(SIZE);
	for (int i = 0; i < SIZE; ++i)
	{
		open[i] = close[i] = false;
	}
	open[0] = true;
	while (c_size < SIZE) {
		for (int i = 0; i < SIZE; ++i)
		{
			old_size = c_size;
			if (open[i] && (close[i] == false))
			{
				close[i] = true;
				c_size++;
			}
			for (int j = 0; j < SIZE; ++j)
			{
				open[j] = open[j] || matrix[i][j];
			}
		}
		if (SIZE == c_size)
			return true;
		if (c_size == old_size)
			return false;
	}
}

int main()
{
	srand(time(0));
	Graph a(0.3, 5);
	a.print();

	if (a.adjacent(0, 3))
		cout << "yes" << endl;
	else
		cout << "no" << endl;

	a.neighbors(1);
}