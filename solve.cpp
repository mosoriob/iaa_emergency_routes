
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

template <typename T>
std::vector<size_t> ordered(std::vector<T> const& values) {
    std::vector<size_t> indices(values.size());
    std::iota(begin(indices), end(indices), static_cast<size_t>(0));

    std::sort(
        begin(indices), end(indices),
        [&](size_t a, size_t b) { return values[a] > values[b]; }
    );
    return indices;
}



/***** Parametros del problema *****/
int N;
int cl=15;
int M=10;
int alpha_ant=1;
int beta_ant=2;
float q_0=0.9;


/***** Estructuras de representación *****/
vector< vector<int> >  ants;
vector< vector<float> >  alphas;
vector< vector<float> >  betas;
vector< vector<float> >  large;
vector< vector<float> >  ss;
vector< vector<float> >  tau;


/*
Calcula el tiempo que toma un tour
*/
float time_tour(vector <int> &tour) {
    int size = (int) tour.size();
    int i;
    int j;
    float t_1=0;
    float t_2=0;
    vector <float> times;
    for(int index = 0; index<size; index++){
        if (index < size - 1){
            i =  tour[index]-1;
            j = tour[index+1]-1;
            if(betas[i][j]==0.0){
                t_2 = large[i][j]/(ss[i][j]*alphas[i][j]) + t_1;
            }
            else
                t_2 = -log(-(large[i][j]*betas[i][j])/(ss[i][j]*alphas[i][j]) \
                    + exp(-betas[i][j]*t_1))/betas[i][j];
            
            cout << i+1 << " "  << j+1  << " t_1: " << t_1 << " t_2: " << t_2 << endl;
            t_1=t_2;
        } 
    }
    return t_2;
}

/*
Calcula el tiempo del necesario para ir entre
la ciudad start y end.
Considera el tiempo inicial.
*/
/*
Params:
start: la ciudad de inicio
end: la ciudad destino
t_1 el tiempo inicial
*/
float time_neighbour(int start, int end, float t_1) {
    float t_2=0;
    //start=start-1;
    //end=end-1;
    if(betas[start][end]==0.0)
        t_2 = large[start][end]/(ss[start][end]*alphas[start][end]) + t_1;
    else
        t_2 = -log(-(large[start][end]*betas[start][end])/(ss[start][end]*alphas[start][end]) \
            + exp(-betas[start][end]*t_1))/betas[start][end];
    return t_2;
}

vector <int> neighbours(int town){
    vector <int> candidate_list; 
    //Definir si el candidate list tiene un limite.
    for(int i=0; i<N; i++){
        if(large[town][i]!=0){
            candidate_list.push_back(i);
        }
    }
    return candidate_list;

}

double RandomFloat() {
  unsigned seed = chrono::system_clock::now().time_since_epoch().count();
  default_random_engine generator (seed);
  uniform_real_distribution<double> distribution (0.0,1.0);
  return distribution(generator);
}


int next_town(int town){
    vector <int> candidate_list = neighbours(town);
    vector <float> P(N,0);
    float denomitador = 0;
    float eta;
    float acu = 0.0;

    //Obtener el denominador
    for(std::vector<int>::iterator it = candidate_list.begin(); it != candidate_list.end(); ++it){
        eta = 1/time_neighbour(town,*it,0);
        denomitador += pow(tau[town][*it],alpha_ant)*pow(eta,beta_ant);        
    }
    
    //Crear las probalidades
    for(std::vector<int>::iterator it = candidate_list.begin(); it != candidate_list.end(); ++it){
        eta = 1/time_neighbour(town,*it,0);
        P[*it] = pow(tau[town][*it],alpha_ant)*pow(eta,beta_ant)/denomitador;
    }

    double q = RandomFloat();
    cout << q << endl;
    if(q < q_0){
        //El mejor es el primero del vector ordenado
        vector <size_t> order = ordered<float>(P);
        return order[0];
    }
    else{
        //El azar dice
        double random_value = RandomFloat();
        for(std::vector<int>::iterator it = candidate_list.begin(); it != candidate_list.end(); ++it){
            eta = 1/time_neighbour(town,*it,0);
            P[*it] = pow(tau[town][*it],alpha_ant)*pow(eta,beta_ant)/denomitador;
            acu += P[*it];
            if(random_value <= acu)
                return *it;
        }        
    }




}

/**
Encuentra al mejor vecino por tiempo de un nodo
¿DEBE ELIMINARSE A BUSCAR EN LA BUSQUEDA DE LA LISTA CANTIDAD

**/
int best_neighbour(int town){
    vector <int> candidate_list;
    vector <float> t;
    vector <float> d;
    vector <float> f_dr;
    vector <float> f_tr;
    vector <float> z_r;
    float best_time=-1.0;
    int best_id;
 
    //Definir si el candidate list tiene un limite.
    for(int i=0; i<N; i++){
        if(large[town][i]!=0){
            float town_time = time_neighbour(town, i, 0);
            if (time_neighbour(town, i, 0) < best_time || best_time == -1.0){
                best_time = town_time; 
                best_id = i;
            }
        }
    }
    return best_id;
}


void cprint_r(){
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++)
            cout << large[i][j] << " ";
        cout << "\n";  
    }

}

void create_matrix(vector< vector<float> > &matrix){
    vector <float> newColumn(N,0);
    //fill(newColumn.begin(),newColumn.end(),0);
    for(int i=0; i < N; i++)
        matrix.push_back(newColumn);
}

void create_tau(vector< vector<float> > &matrix){
    vector <float> newColumn(N,0.000001);
    //fill(newColumn.begin(),newColumn.end(),0);
    for(int i=0; i < N; i++)
        matrix.push_back(newColumn);
}


void fill(char *name) {
    /* Rellena arreglo con los numeros de las ciudades, poniendolas en
    el orden 1,2,...,N. Rellena el arreglo de la posicion de las ciudades. */
    ifstream infile (name);


    int cnt=0,n;

    int l,s,i,j;
    float alpha, beta;
    char caracter, c_t_max[3];

    istringstream lin;
    for (string line; getline(infile, line); ) {
        lin.clear();
        lin.str(line);

        if (cnt == 0){
            lin >> caracter >> N;
            create_matrix(alphas);
            create_matrix(betas);
            create_matrix(ss);
            create_matrix(large);
        }
        else{
            if (lin >> i >> j >> l >> s >> alpha >> beta) {
                i = i-1;
                j = j-1;
                alphas[i][j] = alpha;
                betas[i][j] = beta;
                large[i][j] = l;
                ss[i][j] = s;
            }
            else {
                cout << "WARNING: failed to decode line '" << line << "'\n";
            }
        }
        cnt++;
    }
}


int main(int argc, char* argv[]) {

    if( argc != 2){
        cout << "usage: " << argv[0] << "<filename>\n";
        exit(0);
    }
    else{
        int i;
        fill(argv[1]);
    }

    create_tau(tau);


//Para k=1 hasta m haga
    //Ubique la hormiga k en una ciudad elegida aleatoriamente
//fin para


//Sea T+ el tour mas corto encontrado desde el inicio, y L+ su largo
//Para t=1 hasta el numero de ciclos haga
//Inicio
    //Para k=1 hasta m do
        //Inicio
        //Repetir
            //seleccionar la siguiente ciudad a visitar con probalidad p_{ij}^k
        //hasta que la hormiga complete su tour
        //calcular largo L_k de tour de la hormiga k
    //fin para
    //Salvar la mejor solucion T+, L+, encontrada hasta el momento

    //Para cada arco (i, j) haga
    //Modifique los niveles τij de feromona aplicando la siguiente regla:
    //τij (t) = (1 − ρ)τij(t) + ∆τij(t) + e ∗ ∆τ_{ij}(t)
    //fin para
//fin

    vector <int> column;
    for(int i=0; i < M; i++){
       ants.push_back(column);
    }

    cout << next_town(0);
/*   for(i=0; i < M; i++){
        q = RandomFloat()
        if(q <= q_0){

        }
        else{
            probalidad()
        }

    }*/

    
    return 0;
}