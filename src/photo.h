#ifndef PHOTO_H
#define PHOTO_H
#include <set>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

class Photo
{
private:
    /* data */
public:
    Photo(ifstream& in);
    ~Photo();
    int id;
    bool horizontal;
    bool used;
    std::set<std::string> mapa;
};




#endif /* PHOTO_H */
