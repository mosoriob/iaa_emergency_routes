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

using namespace std;


float time_tour(vector <int> &tour);
float distance_tour(vector <int> &tour);
float time_neighbour(int start, int end, float t_1);
vector <int> neighbours(int town, vector<int> tour);
double RandomFloat();
void update_pheromene(int i, int j);
int next_town(int town, vector<int> tour);
void create_matrix(vector< vector<float> > &matrix);
void create_tau(vector< vector<float> > &matrix);
void fill(char *name);

#endif