#include "photo.h"


Photo::Photo(ifstream& input)
{
    char c;
    input >> c;
     if(c == 'V'){
         horizontal = false;
     } else{
         horizontal = true;
     }

    int number_of_tags;
    input >> number_of_tags;
    for(int i = 0; i < number_of_tags; i++){
        string temp;
        input >> temp;
        mapa.insert(temp);
    }
    used = false;
}

Photo::~Photo()
{
}