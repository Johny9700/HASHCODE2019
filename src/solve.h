#include "slide.h"
#include <vector>
#include <algorithm>
#include <ctime>
#include <unordered_map>

int getUnionSize(const set<string>& a, const set<string>& b);

vector<Slide> solve(vector<Slide> in_slides);
vector<Slide> solve_meta_1(vector<Slide> s, int max_iter, int point);
vector<Slide> solve_graph_1(vector<Slide> s, int point);