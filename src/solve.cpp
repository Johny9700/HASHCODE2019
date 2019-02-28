#include "solve.h"


int getUnionSize(const set<string>& a, const set<string>& b)
{
  set<string> result = a;
  result.insert(b.begin(), b.end());
  int returned_result = (int)result.size();
  return returned_result;
}

vector<Slide> solve(vector<Slide> in_slides){
  vector<Slide> final_slides;
  Slide *best_slide = nullptr;
  int best_crit = -1;
  int slide1 = -1;
  int slide2 = -1;
  int shared = -1;
  Slide current_slide = in_slides[0];//pierwszy slajd
  final_slides.push_back(current_slide);
  current_slide.used = true;
  for(int i = 0; i < in_slides.size() - 1; i++){
    for(auto my_slide : in_slides){
      if(my_slide.used == false){
        shared = getUnionSize(current_slide.mapa, my_slide.mapa);
        int intersection = current_slide.mapa.size() + my_slide.mapa.size() - shared;
        slide1 = current_slide.mapa.size() - intersection;
        slide2 = my_slide.mapa.size() - intersection;
        int mini = min(intersection, min(slide1, slide2));
        if(mini > best_crit){
            best_slide = &my_slide;
            best_crit = mini;
        }
      }

    }
    current_slide = *best_slide;
    best_slide->used = true;
    best_crit = -1;
    slide1 = -1;
    slide2 = -1;
    shared = -1;

    final_slides.push_back(current_slide);
  }
  return final_slides;
}