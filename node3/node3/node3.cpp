// Created on 17 May 2021
// Shortest Path algorith or Dijkstra Algorithm

#include <iostream>
#include <vector>
#include <time.h>

using namespace std;

// Set the size of the graph

const int SIZE = 50;

// Return random probability

inline double prob() { return (rand() % 100) / 100.0; }

// Graph using matrix representation

class Graph
{
public:
	Graph(double n, int range);
	vector<vector<int>> getMatrix() { return matrix; }
	int V() { return SIZE * SIZE; };
	int E();
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

// Queue element for storing total cost and the path taken

class queue_element {
public:
	queue_element(int n = 0, int u = 0) :node(n), cost(u) {}
	int size() { return past.size(); }
	void insert(int u) { past.push_back(u); }
	int node;
	int cost;
	vector<int> past;
};

// Queue to store the queue element

class PriorityQueue
{
public:
	void print();
	void chgPriority(int node);
	queue_element minPriority();
	queue_element contains(int q);
	void insert(int q, int c) { x.insert(x.begin(), queue_element(q, c)); };
	queue_element* top() { return &x[0]; };
	int size() { return x.size(); };

private:
	vector<queue_element> x;
};

// Functions to calculate the shortest path

class ShortestPath
{
public:
	ShortestPath(Graph g) :graph(g) {}
	void vertices();
	void path(int u, int w);
	int path_size(int u, int w);
private:
	Graph graph;
	vector<vector<int>> matrix = graph.getMatrix();
};

// Calculate and return shortest path

void ShortestPath::path(int u, int w) {
	int old_size = 0, c_size = 0;
	vector<bool> close(SIZE, false);
	vector<bool> open(SIZE, false);
	open[u] = true;
	PriorityQueue q;
	q.insert(u, 0);
	q.top()->insert(u);
	while (c_size < SIZE) {
		queue_element temp;
		if (q.size() != 0)
			temp = q.minPriority();
		else {
			cout << "No path found" << endl;
			return;
		}
		for (int i = 0; i < SIZE; ++i) {
			old_size = c_size;
			if (open[i] && close[i] == false) {
				close[i] = true;
				c_size++;
			}
			if (matrix[temp.node][i] && close[i] == false) {
				open[i] = true;
				//cout << "Path: " << temp.node << ", " << i << endl;
				q.insert(i, temp.cost + matrix[temp.node][i]);
				queue_element* top = q.top();
				top->insert(i);
				for (int j = 0; j < temp.past.size(); ++j) {
					top->insert(temp.past[j]);
				}
			}
		}
		if (q.contains(w).cost) {
			cout << "Path is ";
			for (int i = 0; i < q.contains(w).past.size(); ++i) {
				cout << q.contains(w).past[i] << ", ";
			}
			cout << endl;
			return;
		}
	}
}

// Calculate and return shortest path cost

int ShortestPath::path_size(int u, int w) {
	int old_size = 0, c_size = 0;
	vector<bool> close(SIZE, false);
	vector<bool> open(SIZE, false);
	open[u] = true;
	PriorityQueue q;
	q.insert(u, 0);
	q.top()->insert(u);
	while (c_size < SIZE) {
		queue_element temp;
		if (q.size() != 0)
			temp = q.minPriority();
		else {
			return 0;
		}
		for (int i = 0; i < SIZE; ++i) {
			old_size = c_size;
			if (open[i] && close[i] == false) {
				close[i] = true;
				c_size++;
			}
			if (matrix[temp.node][i] && close[i] == false) {
				open[i] = true;
				//cout << "Path: " << temp.node << ", " << i << endl;
				q.insert(i, temp.cost + matrix[temp.node][i]);
			}
		}
		if (q.contains(w).cost) {
			return q.contains(w).cost;
		}
	}
}

// Show all connected edges

void ShortestPath::vertices() {
	for (int i = 0; i < SIZE; ++i) {
		graph.neighbors(i);
		cout << endl;
	}
	cout << endl;
}

// Change the top element of the vector

void PriorityQueue::chgPriority(int n) {
	vector<queue_element> temp = x;
	for (int i = 1; i < x.size(); ++i) {
		x[i] = temp.at(i - 1);
	}
	x[0].node = n;
}

// Print all the nodes

void PriorityQueue::print() {
	for (int i = 0; i < x.size(); ++i) {
		cout << x[i].node << ", ";
	}
	cout << endl;
}

// Returns the element with the least cost

queue_element PriorityQueue::minPriority() {
	int min = 10000;
	for (int i = 0; i < x.size(); ++i) {
		if (x[i].cost < min)
			min = x[i].cost;
	}
	for (int i = 0; i < x.size(); ++i) {
		if (x[i].cost == min) {
			queue_element temp = x[i];
			x.erase(x.begin() + i);
			return temp;
		}
			
	}
}

// Returns the element if the Queue contains the element else return default

queue_element PriorityQueue::contains(int n) {
	queue_element temp;
	for (int i = 0; i < x.size(); ++i) {
		if (x[i].node == n) {
			return x[i];
		}
	}
	return temp;
}

// Return the number of connected edges

int Graph::E() {
	int edges = 0;
	for (int i = 0; i < SIZE; ++i) {
		for (int j = 0; j < SIZE; ++j) {
			if (matrix[i][j])
				edges++;
		}
	}
	return edges;
}

// Creates a default graph according to the density and the range

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

// Checks if two nodes are connected

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

// Show where each node can go

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

// Add a connected edge between two nodes

void Graph::add(int x, int y) {
	if (!matrix[x][y])
		matrix[x][y] = matrix[y][x] = 1;
}

// Prints the graph

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

// Check if all the nodes in the graph are connected

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

// Create two densities 20% and 40% graph and calculate the average shortest path

int main()
{
	srand(time(0));
	
	// 0.2 represent the 20% density while 10 is the distance range
	Graph a(0.2, 10), b(0.4, 10);

	// if (a.adjacent(0, 3))
		// cout << "yes" << endl;
	// else
		// cout << "no" << endl;

	// a.neighbors(1);
	// cout << endl;

	// PriorityQueue q;
	// q.print();
	// for (int i = 0; i < SIZE; ++i) {
		// q.chgPriority(i);
	// }
	// q.print();
	// q.minPrioirty();
	// q.print();

	ShortestPath d(a), e(b);
	cout << "Cost when Density at 20%:" << endl;
	int sum = 0;
	double total = 50;
	for (int i = 0; i < 50; ++i) {
		int cost = d.path_size(0, i);
		if (cost)
			sum += cost;
		else
			total -= 1;
			
	}
	cout << sum / total << endl;

	cout << "Cost when Density at 40%:" << endl;
	sum = 0;
	total = 50;
	for (int i = 0; i < 50; ++i) {
		int cost = e.path_size(0, i);
		if (cost)
			sum += cost;
		else
			total -= 1;

	}
	cout << sum / total << endl;
}