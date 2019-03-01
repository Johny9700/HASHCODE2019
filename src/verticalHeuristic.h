#ifndef VERTICALHEURISTIC_H
#define VERTICALHEURISTIC_H

#include <vector>
#include "slide.h"
std::vector<Slide> makeSlidesFromVertical(std::vector<Photo> photos);
std::vector<Slide> simple(std::vector<Photo> photos);
std::vector<Slide> balanced(std::vector<Photo> photos);

#endif /* VERTICALHEURISTIC_H */
