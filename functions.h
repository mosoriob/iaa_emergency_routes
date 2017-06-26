#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include <cmath>
#include <stdlib.h>     /* srand, rand */
#include <typeinfo>
#include <algorithm>
#include <chrono>
#include <random>
#include <cstdlib>

using namespace std;

double time_tour(vector <int> &tour);
float distance_tour(vector <int> &tour);
void  print_tour(vector <int> &tour);
void update_pheromene(int i, int j);
void best_tour_update_pheromone(vector <int> &tour, float best_tour_time);
void create_matrix(vector< vector<float> > &matrix);
void create_tau(vector< vector<float> > &matrix);
void fill(char *name);

int next_town(int town, vector<int> tour);
double random_float();
vector <int> neighbours(int town, vector<int> tour);
bool is_safe(int town);

#endif