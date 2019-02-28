#include "slide.h"

Slide::Slide(Photo photo)
{
    id1 = photo.id;
    id2 = -1;
    mapa = photo.mapa;
    used = false;
}

Slide::Slide(Photo photo1, Photo photo2)
{
    id1 = photo1.id;
    id2 = photo2.id;
    mapa = photo1.mapa;
    for(auto &tag : photo2.mapa){
        mapa.insert(tag);
    }
    used = false;
    //----debug
    //for(auto tag : mapa){
    //    cout << tag <<endl;
    //}
    //----debug
}

void Slide::get_id(ofstream& out_stream){
    out_stream << id1;
    if(id2 != -1){
        out_stream <<" "<< id2;
    }
    out_stream << std::endl;
}

Slide::~Slide()
{
}
