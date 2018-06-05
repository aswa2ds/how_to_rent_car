#include <iostream>
#include <algorithm>
#include <functional>
#include <vector>
#include <string.h>
#include <stdio.h>
#include <queue>

using namespace std;

enum color_type{WHITE, GREY, BLACK};

class vertex {
private:
	int num;
	int weight;
public:
	vertex(int n, int w) { num = n; weight = w; }
	int get_num() { return num; }
	int get_weight() { return weight; }
};

class graph {
private:
	int scale;
	color_type *color;
	vector<vertex> *dependent;
	priority_queue<vertex> heap;
	int width;
	int src;
	int dst;
public:
	graph(int s, int sr, int ds) { 
		scale = s; 
		color = new color_type[s]; 
		dependent = new vector<vertex>[s]; 
		for (int i = 0; i < s; ++i)
			color[i] = WHITE;
		src = sr;
		dst = ds;
		width = 100;
	}
	void add_edge(int, int, int);
	void print();
	void prim(int);
};

int main() {
	int num, s, t;
	cin >> num >> s >> t;
	graph G(num, s, t);
	int le, u, v;
	while (scanf_s("%d%d%d", &le, &u, &v) != EOF) {
		G.add_edge(u, v, le);
	}
	G.print();
	//G.prim(s);
	return 0;
}

void graph::add_edge(int u, int v, int w) {
	vertex u_next(v, w);
	dependent[u].push_back(u_next);
	vertex v_next(u, w);
	dependent[v].push_back(v_next);
}

void graph::print() {
	for (int i = 0; i < scale; ++i) {
		cout << i << "->";
		for (unsigned j = 0; j < dependent[i].size(); ++j)
			cout << dependent[i][j].get_num() << ":" << dependent[i][j].get_weight() << " ";
		cout << endl;
	}
}

