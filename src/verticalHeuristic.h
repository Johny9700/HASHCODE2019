#ifndef VERTICALHEURISTIC_H
#define VERTICALHEURISTIC_H

#include <vector>
#include "slide.h"
#include <unordered_map>
#include <iostream>
#include <algorithm>

std::vector<Slide> makeSlidesFromVertical(std::vector<Photo> photos);
std::vector<Slide> simple(std::vector<Photo> photos);
std::vector<Slide> balanced(std::vector<Photo> photos);
std::vector<Slide> minimize_intersect(std::vector<Photo> photos);

#endif /* VERTICALHEURISTIC_H */
