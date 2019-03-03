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

void process(std::string filename, int max_iter, int point){
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

	//std::vector<Slide> sVert = simple(photosVert);
	std::vector<Slide> sVert = minimize_intersect(photosVert);
	//slides.insert(slides.end(), sVert.begin(), sVert.end());
	for(unsigned long int i=0; i<sVert.size(); i++){
		slides.push_back(sVert[i]);
	}
	std::cout << "Merging finished" << std::endl;

	// for(auto temp : slides){
	// 	std::cout << temp.id1 << "\t" << temp.id2 << "\t";
	// 	for(auto ghj : temp.mapa){
	// 		std::cout << ghj << " ";
	// 	}
	// 	std::cout << std::endl;
	// }

	//--- solving slides --///

	//std::vector<Slide> result = solve(slides);
	//std::vector<Slide> result = slides;
	//std::vector<Slide> result = solve_meta_1(slides, max_iter, point);
	std::vector<Slide> result = solve_graph_1(slides, point);

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

int main() {
	std::cout << "Starting..." << std::endl;

	std::string filenames[] = {
		"a_example",
		"b_lovely_landscapes",
		"c_memorable_moments",
		"d_pet_pictures",
		"e_shiny_selfies"
	};

	// do not run graph solution in paralell (memory usage) 
	
	std::thread threads[5];
	std::thread aT, bT, cT, dT, eT;

	std::cout << "Starting threads" <<std::endl;

	// auto starting threads, some might be badly parametrized
	// for(int i=0; i<5; i++){
	// 	threads[i] = std::thread (process, filenames[i], 20000, 15);
	// }

	//parametrize each set
	// aT = std::thread (process, filenames[0], 20000, 15);
	// bT = std::thread (process, filenames[1], 20000, 4);
	// cT = std::thread (process, filenames[2], 20000, 6);
	// dT = std::thread (process, filenames[3], 20000, 15);
	// eT = std::thread (process, filenames[4], 20000, 15);

	// std::cout << "Joining threads" <<std::endl;

	// auto joining threads
	// for(int i=0; i<5; i++){
	// 	threads[i].join();
	// }

	// aT.join();
	// bT.join();
	// cT.join();
	// dT.join();
	// eT.join();

	// sequential loops 
	for(int i=0; i<3; i++){ //first 3 instances (low memory usage)
		process(filenames[i],0,0);
	}
	for(int i=3; i<5; i++){ //rest of instances
		process(filenames[i],0,2);
	}

	std::cout << "Exit" <<std::endl;
	
}