#include "verticalHeuristic.h"
#include "photo.h"
#include <set>
#include <algorithm>
#include <iterator>

template <typename T>
std::set<T> getUnion(const std::set<T>& a, const std::set<T>& b)
{
  std::set<T> result = a;
  result.insert(b.begin(), b.end());
  return result;
}

std::vector<Slide> makeSlidesFromVertical(std::vector<Photo> photos)
{
    std::vector<Slide> slides;
    
    for(long unsigned int i=0; i<photos.size(); i++)
    {
        photos[i].used = true;
        long unsigned int maxNumOfTags = 0;
        int curr = -1;
        
        for(long unsigned int j=0; j<photos.size(); j++)
        {
            std::set<std::string> merged;
            
            if(photos[j].id != photos[i].id && !photos[j].used){
                // std::cout<< "xDD" << std::endl;
                merged = getUnion(photos[i].mapa, photos[j].mapa);
                if(maxNumOfTags < merged.size())
                {
                    maxNumOfTags = merged.size();
                    curr = j;
                }
            }
            //merged.clear();
        }
        
        
        if(curr != -1){
            photos[curr].used = true;
            // std::cout<<"xD2"<<std::endl;
            slides.emplace_back(Slide(photos[i], photos[curr]));
        }
    }

    for(auto slide : slides)
    {
        std::cout << slide.id1 << "\t" << slide.id2 << std::endl;
    }
    return slides;
}

std::vector<Slide> simple(std::vector<Photo> photos){
    std::vector<Slide> slides;
    for(unsigned long int i=1; i<photos.size(); i+=2){
        slides.emplace_back(photos[i-1], photos[i]);
    }
    return slides;
}

std::vector<Slide> minimize_intersect(std::vector<Photo> photos){
    std::vector<Slide> s;

    int length = (int)photos.size();

    //inverted index
    std::unordered_map<std::string, std::vector<int>> ii;

    for(int i=0; i<length; i++){
        for(auto k : photos[i].mapa){
            ii[k].push_back(i);
        }
    }

    //creating slides
    bool* used = new bool[length];
    for(int i=0; i<length; i++){
        used[i] = false;
    }

    for(int i=0; i<length; i++){
        if(!used[i]){
            used[i] = true;

            int* intersects = new int[length];
            for(int j=0; j<length; j++){
                intersects[j] = 0;
            }

            for(auto k : photos[i].mapa){ // increasing value of intersects size
                for(auto l : ii[k]){
                    if(!used[l] && l!=i){
                        intersects[l]++;
                    }
                }
            }

            //make field corresponding to current photo very big
            intersects[i] = *max_element(intersects, intersects+length) + 1;

            int mini = intersects[i];
            int miniI = i;

            for(int j=0; j<length; j++){
                if(!used[j] && intersects[j] < mini){
                    mini = intersects[j];
                    miniI = j;
                }
            }

            if(i != miniI) {
                used[miniI] = true;
                s.emplace_back(Slide(photos[i], photos[miniI]));
                //std::cout << "Double slide added" <<std::endl;
            }

            delete [] intersects;
        }
    }

    delete [] used;

    // clean inverted index
    for(auto f : ii){
        f.second.clear();
        f.second.shrink_to_fit();
    }
    ii.clear();

    return s;
}