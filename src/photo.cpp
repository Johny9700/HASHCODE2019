#include "photo.h"


Photo::Photo(int i, ifstream& input)
{
    id = i;
    char c;
    input >> c;
    //std::cout << c <<std::endl;
     if(c == 'V'){
         horizontal = false;
     } else{
         horizontal = true;
     }

    int number_of_tags;
    input >> number_of_tags;
    //std::cout<< number_of_tags <<std::endl;
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