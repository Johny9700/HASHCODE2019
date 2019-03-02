#include <iostream>
#include "photo.h"
#include "slide.h"
#include <thread>
#include <set>
#include <fstream>
#include <vector>
#include <algorithm>
#include "verticalHeuristic.h"
#include "solve.h"

void process(std::string filename){
	std::cout<< "Processing "+filename << std::endl;
	std::ifstream in;
	int N = -1;
	std::string tmp = "./"+filename+".txt";
	in.open(tmp.c_str());
	if(!in.is_open()){
		std::cout <<"xDDD"<<std::endl;
	}
	in >> N;
	std::cout << N <<std::endl;
	std::vector<Photo> photos;

	std::cout<< "Reading photos" <<std::endl;

	for(int i=0; i<N; i++){
		photos.emplace_back(Photo(i,in));
	}
	in.close();

	std::cout<< "Dividing photos " <<std::endl;

	std::vector<Slide> slides;
	std::vector<Photo> photosVert;

	for(int i=0; i<N; i++){
		if(photos[i].horizontal){
			slides.emplace_back(Slide(photos[i]));
		} else {
			photosVert.push_back(photos[i]);
		}
	}

	//--- processing verticals ---///

	std::cout << "Processing verticals" << std::endl;

	std::vector<Slide> sVert = simple(photosVert);
	//slides.insert(slides.end(), sVert.begin(), sVert.end());
	for(unsigned long int i=0; i<sVert.size(); i++){
		slides.push_back(sVert[i]);
	}
	std::cout << "Merging finished" << std::endl;

	//--- solving slides --///

	//std::vector<Slide> result = solve(slides);
	//std::vector<Slide> result = slides;
	std::vector<Slide> result = solve_meta_1(slides);

	std::ofstream out;
	out.open((filename+"_result.txt").c_str());
	out<<result.size()<<std::endl;
	for(unsigned long int i=0; i<result.size(); i++){
		result[i].get_id(out);
	}

	// clean up the mess
	slides.clear();
	slides.shrink_to_fit();
	result.clear();
	result.shrink_to_fit();
	sVert.clear();
	sVert.shrink_to_fit();
	photosVert.clear();
	photosVert.shrink_to_fit();
	photos.clear();
	photos.shrink_to_fit();
	
	out.close();
}

void test(){
	std::cout << "Thread" << std::endl;
}

int main() {
	std::cout << "Starting..." << std::endl;

	std::string filenames[] = {
		"a_example",
		"b_lovely_landscapes",
		"c_memorable_moments",
		"d_pet_pictures",
		"e_shiny_selfies"
	};

	/**
	std::thread threads[5];

	std::cout << "Starting threads" <<std::endl;

	for(int i=0; i<5; i++){
		//threads[i] = std::thread (process, filenames[i]);
		threads[i] = std::thread (test);
	}

	std::cout << "Joining threads" <<std::endl;

	for(int i=0; i<5; i++){
		threads[i].join();
	}
	**/

	for(int i=0; i<5; i++){
		process(filenames[i]);
	}

	std::cout << "Exit" <<std::endl;
	
}