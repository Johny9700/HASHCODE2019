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
    std::set<std::string> merged;
    
    for(auto photo : photos)
    {
        photo.used = true;
        int maxNumOfTags = 0;
        Photo *candidate = nullptr;
        for(auto photo2 : photos)
        {
            if(photo2.id != photo.id && !photo2.used)
            {
                merged = getUnion(photo.mapa, photo2.mapa);
                if(maxNumOfTags < merged.size());
                {
                    maxNumOfTags = merged.size();
                    candidate = &photo2;
                }
            }
        }
        candidate->used = true;
        slides.emplace_back(Slide(photo, *candidate));
    }

    for(auto slide : slides)
    {
        std::cout << slide.id1 << "\t" << slide.id2 << std::endl;
    }
    return slides;
}