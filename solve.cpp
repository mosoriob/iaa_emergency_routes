#include "functions.h"

using namespace std;


/***** Parametros del problema *****/
int N=20;
int loops=2000;
int cl=15;
int M=10;
int alpha_ant=1;
int beta_ant=2;
float q_0=0.5;
float ro=0.5;
float tau_0=1/(10);
double R1=1, R2=1-R1;
ifstream ifs;

/***** Estructuras de representación *****/
vector< vector<int> >  ants;
vector< vector<float> >  alphas;
vector< vector<float> >  betas;
vector< vector<float> >  large;
vector< vector<float> >  ss;
vector< vector<float> >  tau;



int main(int argc, char* argv[]) {


    int best_size = 0, ant_size;
    float best_time = 0, ant_time;
    float best_heuristic=0, ant_heuristic;


    if( argc != 5){
        cout << "usage: " << argv[0] << "<filename>\n";
        exit(0);
    }
    else{
        R1=atof(argv[2]);
        best_time=atof(argv[3]);
        best_size=atoi(argv[4]);
        R2=1-R1;
        fill(argv[1]);
    }

    ifs.open("seeds.txt", ifstream::in);

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
    //ants[0] = {0,5,11,7,12,8,13,14,19};
    //cout << time_tour(ants[0]);
    //return 0;
    for(int j=0; j<loops; j++){

        for(int i=0; i<M;i++){
            ants[i].push_back(0);

            old_next=0;
            while_exit=false;
            do{
                next = next_town(0, ants[i]);
                ants[i].push_back(next);
                if(next==19)
                    while_exit=true;
                else if(old_next == next){
                    while_exit=true;
                    imposible=true;
                }
                old_next = next;
            }while(!while_exit);


            if(imposible){
                imposible=false;
                break;
            }

            ant_time = time_tour(ants[i]);
            ant_size = ants[i].size();


            ant_heuristic = R1*(ant_time - best_time )/best_time + R2*(ant_size - best_size)/best_size;
            if (best_heuristic == 0 || ant_heuristic < best_heuristic){
                best_heuristic = ant_heuristic;
                best_tour = ants[i];
            }

            ants[i].clear();
        }
    }

    cout <<  best_heuristic << " " << time_tour(best_tour) << " " << best_tour.size() << endl;
    
    return 0;
}