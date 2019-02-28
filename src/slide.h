#ifndef SLIDE_H
#define SLIDE_H
#include <set>
#include <string>
#include "photo.h"

class Slide
{
private:
    /* data */
public:
    Slide(Photo photo);
    Slide(Photo photo1, Photo photo2);
    ~Slide();
    void get_id(ofstream& out_stream);
    void calculate_criteria(Slide slide);
    int id1;
    int id2;
    std::set<std::string> mapa;
    bool used;
    int kryterium;
};

#endif /* SLIDE_H */
