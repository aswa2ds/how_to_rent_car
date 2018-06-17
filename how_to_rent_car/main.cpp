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

class cmp {
public:
	bool operator()(vertex &a, vertex &b) const
	{
		return a.get_weight() > b.get_weight();
	}
};

class graph {
private:
	int scale;
	color_type *color;
	vector<vertex> *dependent;
	priority_queue<vertex, vector<vertex>, cmp> heap;
	int *width;
	int wid;
	int src;
	int dst;
public:
	graph(int s, int sr, int ds) { 
		scale = s; 
		color = new color_type[s]; 
		dependent = new vector<vertex>[s]; 
		width = new int[s];
		for (int i = 0; i < s; ++i) {
			color[i] = WHITE;
			width[i] = 10000;
		}
		src = sr;
		dst = ds;
		wid = 100;
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
	//G.print();
	G.prim(s);
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

void graph::prim(int u) {
	width[u] = 0;
	for (unsigned i = 0; i < dependent[u].size(); ++i) {
		int v = dependent[u][i].get_num();
		int w = dependent[u][i].get_weight();
		int max_width = (w > width[u]) ? w : width[u];
		//cout << max_width << endl;
		width[v] = (max_width < width[v]) ? max_width : width[v];
		heap.push(dependent[u][i]);
	}
	while (!heap.empty()) {
		vertex tmp = heap.top();
		heap.pop();
		int m = tmp.get_num();
		for (unsigned i = 0; i < dependent[m].size(); ++i) {
			int n = dependent[m][i].get_num();
			int w = dependent[m][i].get_weight();
			int max_width = (w > width[m]) ?  w : width[m];
			if (width[n] > max_width) {
				width[n] = max_width;
				heap.push(dependent[m][i]);
			}
		}
	}
	/*for (int i = 0; i < scale; ++i)
		cout << width[i] << " ";
	cout << endl;*/
	cout << "I have read the rules about plagiarism punishment" << endl;
	cout << width[dst] << endl;
}