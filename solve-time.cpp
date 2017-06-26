#include "functions.h"

using namespace std;

bool DEBUG=false;
int N;
/***** Parametros del problema *****/
/*
loops: numbers of iterations
cl: size of candidate list
M: numbers of ants
alpha_ant: alpha
beta_ant beta
q_0: evaportation param
tau_0: initial pheronome
*/ 
int loops=2000;
int cl=15;
int M=10;
int alpha_ant=1;
int beta_ant=2;
float q_0=0.5;
float ro=0.5;
float tau_0=1/(10);
double R1=1, R2=1-R1;
int seedInt;
ifstream ifs;

/***** Estructuras de representación *****/
vector< vector<int> >    ants;
vector< vector<float> >  alphas;
vector< vector<float> >  betas;
vector< vector<float> >  large;
vector< vector<float> >  ss;
vector< vector<float> >  tau;
vector<string>  safe_areas;

int main(int argc, char* argv[]) {

    if( argc != 11){
        cout << "usage: " << argv[0] << "<filename>\n";
        exit(0);
    }
    else{
        int i;
        fill(argv[1]);
        loops=atoi(argv[2]);
        cl=atoi(argv[3]);
        M=atoi(argv[4]);
        alpha_ant=atoi(argv[5]);
        beta_ant=atoi(argv[6]);
        q_0=atof(argv[7]);
        ro=atof(argv[8]);
        tau_0=atof(argv[9]);
        seedInt=atoi(argv[10]);
    }
    srand(seedInt);

    int best_size = 0, ant_size;
    float best_time = 0, ant_time;
    float best_heuristic=0, ant_heuristic;

    vector <int> best_tour;
    vector <int> best_tour_size;
    vector <int> best_tour_time;


    create_tau(tau);

    bool while_exit=false, imposible=false;
    int next, old_next=0;
    vector <int> column;
    for(int i=0; i < M; i++){
       ants.push_back(column);
    }

    for(int j=0; j<loops; j++){

        for(int i=0; i<M;i++){
            //starting point
            ants[i].push_back(0);

            old_next=0;
            while_exit=false;
            do{
                //select next point
                next = next_town(0, ants[i]);
                ants[i].push_back(next);

                //is safe the point?
                if(is_safe(next))
                    while_exit=true;
                else if(old_next == next){
                    while_exit=true;
                    imposible=true;
                }
                old_next = next;
            }while(!while_exit);


            if(imposible){
                if (DEBUG)
                    cout << "imposible" << endl;
                imposible=false;
                ants[i].clear();
                continue;
            }

            //cout << "Hormiga " << i  << " iteracion " << j << endl;
            //cout << time_tour(ants[i]) << endl;

            ant_time = time_tour(ants[i]);
            ant_size = ants[i].size();

            if (best_time == 0 || ant_time < best_time ){
                best_time = ant_time;
                best_tour_time = ants[i];
                best_tour_update_pheromone(best_tour_time, best_time);
            }
            ants[i].clear();

        }

    }
    cout << best_time << endl;

    //cout << time_tour(best_tour_time) << endl;
    //print_tour(best_tour_time);
    // vector<int> test_array;
    // // test_array.push_back(0);
    // // test_array.push_back(1);


    // test_array.push_back(0);
    // test_array.push_back(5);
    // test_array.push_back(6);
    // test_array.push_back(7);
    // test_array.push_back(12);
    // test_array.push_back(8);
    // test_array.push_back(13);
    // test_array.push_back(14);
    // test_array.push_back(19);

    // cout  << time_tour(test_array) << endl;

    return 0;
}
