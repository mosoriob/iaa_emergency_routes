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

    if( argc != 2){
        cout << "usage: " << argv[0] << "<filename>\n";
        exit(0);
    }
    else{
        int i;
        fill(argv[1]);
    }

    ifs.open("seeds.txt", ifstream::in);

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
            } while(!while_exit);


            if(imposible){
                imposible=false;
                break;
            }

            ant_time = time_tour(ants[i]);
            ant_size = ants[i].size();

            if (best_size == 0 || ant_size < best_size){
                best_size = ant_size;
                best_tour_size = ants[i];
            }


            ants[i].clear();

        }
    }

    cout << best_tour_size.size()-1 << endl;

    return 0;
}