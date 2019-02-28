#ifndef PHOTO_H
#define PHOTO_H
#include <set>
#include <string>

class photo
{
private:
    /* data */
public:
    photo(/* args */);
    ~photo();
    int id;
    bool horizontal;
    std::set<std::string> mapa;
};




#endif /* PHOTO_H */
