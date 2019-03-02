#include "slide.h"
#include <vector>
#include <algorithm>
#include <ctime>

int getUnionSize(const set<string>& a, const set<string>& b);

vector<Slide> solve(vector<Slide> in_slides);
vector<Slide> solve_meta_1(vector<Slide> s);
