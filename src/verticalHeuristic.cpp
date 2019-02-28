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