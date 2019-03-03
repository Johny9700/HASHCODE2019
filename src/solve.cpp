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
  for(int i = 0; i < (int)in_slides.size() - 1; i++){
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
  int unions = getUnionSize(previous.mapa, current.mapa);
  int p = previous.mapa.size();
  int c = current.mapa.size();
  int intersec = p + c - unions;
  return min(intersec, min(p-intersec, c-intersec));
}

int overall_score(std::vector<Slide> s){
  if((int)s.size()==0){
    return -1;
  } else if ((int)s.size()==1){
    return 0;
  }
  int ret = 0;
  for(int i=1; i<(int)s.size();i++){
    ret+=scoring_func(s[i-1],s[i]);
  }
  return ret;
}

std::vector<Slide> solve_meta_1(std::vector<Slide> s, int max_iter, int point){

  //int max_iter = 20000;          //parameter
  int min_len = 1;                //parameter
  int max_idle_iters = 200;       //parameter

  //if(min_len > (int)s.size()) min_len = 0;

  int iter = 0;
  int idle_iters = 0;

  //int point = 15;       //parameter

  int prev = -1;        //previous size of stripes

  std::vector<std::vector<Slide>> stripes;
  std::cout << "Begin stripes meta" << std::endl;
  for(int i=0; i<(int)s.size(); i++){
    std::vector<Slide> temp;
    temp.push_back(s[i]);
    stripes.push_back(temp);
  }

  //initial shuffle
  std::random_shuffle(stripes.begin(), stripes.end());

  //metaheuristic

  while (iter < max_iter && min_len < (int)stripes.size()){
    iter ++;
    clock_t start = clock();
    for(int i=1; i<(int)stripes.size(); i++){
      if(scoring_func(stripes[i-1].back(), stripes[i].front()) >= point){
        i--;
        stripes[i].insert(stripes[i].end(), stripes[i+1].begin(), stripes[i+1].end());
        stripes[i+1] = stripes[i];
        stripes.erase(stripes.begin()+i);
      }
    }
    clock_t end = clock();

    //check if max number of idle iteratio exceeded
    if(prev == (int)stripes.size()){
      idle_iters++;
      if(idle_iters == max_idle_iters){
        idle_iters = 0;
        point--;
      }
    }
    prev = (int)stripes.size();

    if(iter%500==0 || iter ==1)
    std::cout << "Iteration:\t" << iter << "\tstripes size\t" << stripes.size() << "\tpoint\t" << point 
    << "\ttime\t" << double(end - start)/CLOCKS_PER_SEC<<std::endl;
    if(point==0) break;
    std::random_shuffle(stripes.begin(), stripes.end());
  }
  std::cout << "======================================================================" << std::endl;
  std::cout << "Processing finished\t iteration\t" << iter << "\tstripes size\t" << stripes.size() << "\tpoint\t" << point ;

  std::vector<Slide> result;
  for(int i=0; i<(int)stripes.size(); i++){
    result.insert(result.end(), stripes[i].begin(), stripes[i].end());
    stripes[i].clear();
    stripes[i].shrink_to_fit();
  }
  stripes.clear();
  stripes.shrink_to_fit();

  std::cout << "\tscore\t" << overall_score(result) << std::endl;

  std::cout << "End stripes meta" << std::endl;
  return result;
}

struct edge{
 int id = 0;
 int val = 0;
};

bool operator < (edge e, edge f){
  return (e.val < f.val);
}

std::vector<Slide> solve_graph_1(std::vector<Slide> s, int point){
  std::cout << "Begin graph\t" << s.size() << std::endl;

  /*
  point parameter is used as a treshold, 
  edges with value equal or below it ar not added to the graph
  it results in better memory usage
  */

  int length = (int)s.size();

  //inverted index

  std::cout << "Creating inverted index" << std::endl;

  std::unordered_map<string, vector<int>> ii; //inverted index

  for(int i=0; i<length; i++){
    for(auto k : s[i].mapa){
      ii[k].push_back(i);
    }
  }
  // print inverted index
  // for(auto temp : ii){
  //   std::cout << temp.first << "\t";
  //   for(auto ghj : temp.second){
  //     std::cout << ghj << " ";
  //   }
  //   std::cout<<std::endl;
  // }

  //neighbour list aggregated

  std::cout << "Creating neighbours list" << std::endl;

  std::vector<std::vector<edge>> ln; //list of neighbours aggregated

  unsigned long long ln_size = 0;

  for(int i=0; i<length; i++){ // for every slide
    if(i%1000==0)std::cout<<i<<" "<<ln_size<<endl;
    int* list; //table of connections to each slide , -1 means no connection
    std::vector<int> v; /// indexes of connected slides
    list = new int[length];
    for(int j=0; j<length; j++){
      list[j] = -1;
    }

    for(auto tag : s[i].mapa){ //go through tags
      for(auto j : ii[tag]){   //go through all indekses of single tag
        if(j!=i){
          if(list[j] == -1){ //note connected slides and number of common tags with each of connected slides
            list[j] = 1;    
            v.push_back(j);
          } else {
            list[j]++;
          }
        }
      }
    }

    std::vector<edge> neighbors;
    
    for(auto j : v){ //rewrite data of each 
      edge e;
      e.id = j;
      e.val = min({list[j], (int)s[i].mapa.size()-list[j], (int)s[j].mapa.size()-list[j]}); //scoring function
      if(e.val>point) //dirty hack to save memory in d and e
      neighbors.push_back(e);
    }

    v.clear();
    v.shrink_to_fit();
    delete [] list;

    sort(neighbors.begin(), neighbors.end());
    reverse(neighbors.begin(), neighbors.end());

    ln.push_back(neighbors);

    ln_size += neighbors.size();

    neighbors.clear();
    neighbors.shrink_to_fit();
  }
  std::cout << "List of neighbours created" << std::endl;

  //clear inverted index
  for(auto temp : ii){
    temp.second.clear();
    temp.second.shrink_to_fit();
  }
  // ii.clear();

  std::cout << "Going through the graph" << std::endl;

  //go throug graph
  bool* visited = new bool[length];

  for(int j=0; j<length; j++){
    visited[j] = false;
  }

  std::vector<Slide> result;

  int current = 0; //choose starting vertex

  while(!ln[current].empty()){
    visited[current] = true;
    result.push_back(s[current]);
    while(!ln[current].empty() && visited[ln[current][0].id]){  //remove edges to visited vertices
      ln[current].erase(ln[current].begin());
    }
    if(!ln[current].empty()){
      current = ln[current][0].id;
    } else { //chhosing new start if possible
      for(int j=0; j<length; j++){
        if(!visited[j] && !ln[j].empty()){
          current = j;
          //std::cout << "New start" << std::endl;
          break;
        }
      }
    }
  }

  //clear list of neighbours
  for(int kr=0; kr<length; kr++){
    ln[kr].clear();
    ln[kr].shrink_to_fit();
  }
  ln.clear();
  ln.shrink_to_fit();

  std::cout << "Score\t" << overall_score(result) << std::endl;

  std::cout << "End graph" << std::endl;

  delete [] visited;

  return result;
}

