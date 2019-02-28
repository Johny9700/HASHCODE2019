#ifndef SLIDE_H
#define SLIDE_H
#include <set>
#include <string>

class slide
{
private:
    /* data */
public:
    slide(/* args */);
    ~slide();
    int id1;
    int id2;
    std::set<std::string> mapa;
    bool used;
};

#endif /* SLIDE_H */
