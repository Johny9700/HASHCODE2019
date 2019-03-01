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

	std::cout<< "reading photos" <<std::endl;

	for(int i=0; i<N; i++){
		photos.emplace_back(Photo(i,in));
		//std::cout<<photos[i].id<<std::endl;
	}
	in.close();

	std::cout<< "reading photos finished" <<std::endl;

	std::vector<Slide> slides;
	std::vector<Photo> photosVert;

	for(int i=0; i<N; i++){
		if(photos[i].horizontal){
			slides.emplace_back(Slide(photos[i]));
		} else {
			photosVert.push_back(photos[i]);
		}
	}

	std::cout<< "dividing photos " << slides.size() <<std::endl;

	//TODO deal with verticals
	std::vector<Slide> sVert = makeSlidesFromVertical(photosVert);
	std::cout<<"first part "<< sVert.size()<<std::endl;
	//slides.insert(slides.end(), sVert.begin(), sVert.end());
	for(unsigned long int i=0; i<sVert.size(); i++){
		// std::cout<<"Hello "<<sVert[i].id1<<std::endl;
		slides.push_back(sVert[i]);
	}
	std::cout<<"merging finished"<<std::endl;

	//TODO sort slides

	std::vector<Slide> result = solve(slides);

	std::ofstream out;
	out.open((filename+"_result.txt").c_str());
	out<<result.size()<<std::endl;
	for(unsigned long int i=0; i<result.size(); i++){
		result[i].get_id(out);
	}
	
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

	for(int i=0; i<1; i++){
		process(filenames[i]);
	}

	std::cout << "Exit" <<std::endl;
	






}