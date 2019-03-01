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

int scoring_func(Slide previous, Slide current){
  int shared = getUnionSize(previous.mapa, current.mapa);
  int p = previous.mapa.size();
  int c = current.mapa.size();
  int intersec = p + c - shared;
  return min(intersec, min(p-intersec, c-intersec));
}

std::vector<Slide> solve_meta_1(std::vector<Slide> s){

  int max_iter = 10;
  int min_len = min(5, (int)s.size());

  int iter = 0;

  int point = 2;

  std::vector<std::vector<Slide>> stripes;
  std::cout << "Begin stripes meta" << std::endl;
  for(int i=0; i<s.size(); i++){
    std::vector<Slide> temp;
    temp.push_back(s[i]);
    stripes.push_back(temp);
  }

  //metaheuristic

  while (iter < max_iter && min_len < stripes.size()){
    iter ++;
    for(int i=1; i<stripes.size(); i++){
      if(scoring_func(stripes[i-1].back(), stripes[i].front()) >= point){
        i--;
        stripes[i].insert(stripes[i].end(), stripes[i+1].begin(), stripes[i+1].end());
        stripes[i+1] = stripes[i];
        stripes.erase(stripes.begin()+i);
      }
    }
    std::cout << "Iteration:\t" << iter << "\tstripes size\t" << stripes.size() <<std::endl;
    std::random_shuffle(stripes.begin(), stripes.end());
  }

  std::vector<Slide> result;
  for(int i=0; i<stripes.size(); i++){
    result.insert(result.end(), stripes[i].begin(), stripes[i].end());
    stripes[i].clear();
    stripes[i].shrink_to_fit();
  }

  std::cout << "End stripes meta" << std::endl;
  return result;
}