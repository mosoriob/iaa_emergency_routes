#include "functions.h"
using namespace std;

extern int N;
extern int cl;
extern int M;
extern int alpha_ant;
extern int beta_ant;
extern float q_0;
extern float ro;
extern float tau_0;

/***** Estructuras de representación *****/
extern vector< vector<int> >  ants;
extern vector< vector<float> >  alphas;
extern vector< vector<float> >  betas;
extern vector< vector<float> >  large;
extern vector< vector<float> >  ss;
extern vector< vector<float> >  tau;


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
            i =  tour[index];
            j = tour[index+1];
            if(betas[i][j]==0.0){
                t_2 = large[i][j]/(ss[i][j]*alphas[i][j]) + t_1;
            }
            else
                t_2 = -log(-(large[i][j]*betas[i][j])/(ss[i][j]*alphas[i][j]) \
                    + exp(-betas[i][j]*t_1))/betas[i][j] ;
        } 
        t_1=t_2;
    }
    return t_2;
}


/*
Calcula el tiempo que toma un tour
*/
float distance_tour(vector <int> &tour) {
    int size = (int) tour.size();
    int i;
    int j;
    float distance=0;
    for(int index = 0; index<size; index++){
        if (index < size - 1){
            i =  tour[index];
            j = tour[index+1];
            distance += large[i][j];
        } 
    }
    return distance;
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

vector <int> neighbours(int town, vector<int> tour){

    std::vector<int>::iterator it = find (tour.begin(), tour.end(), 30);
    vector <int> candidate_list; 
    //Definir si el candidate list tiene un limite.
    for(int i=0; i<N; i++){
        it = find (tour.begin(), tour.end(), i);
        if(it == tour.end() && large[town][i]!=0){
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

void update_pheromene(int i, int j){
    tau[i][j] = (1 - ro)*tau[i][j] + ro*tau_0;
}

int next_town(int town, vector<int> tour){
    int start = tour.back();
    int end;

    vector <int> candidate_list = neighbours(start, tour);
    vector <float> P(N,0);
    float denomitador = 0;
    float eta;
    float acu = 0.0;

    //Obtener el denominador
    for(std::vector<int>::iterator it = candidate_list.begin(); it != candidate_list.end(); ++it){
        vector<int> new_tour = tour;
        new_tour.push_back(*it);
        eta = 1/time_tour(new_tour);
        denomitador += pow(tau[town][*it],alpha_ant)*pow(eta,beta_ant);        
    }
    //Crear las probalidades
    for(std::vector<int>::iterator it = candidate_list.begin(); it != candidate_list.end(); ++it){
        vector<int> new_tour = tour;
        new_tour.push_back(*it);
        eta = 1/time_tour(new_tour);
        P[*it] = pow(tau[town][*it],alpha_ant)*pow(eta,beta_ant)/denomitador;
    }

    double q = RandomFloat();
    if(q < q_0){
        //El mejor es el primero del vector ordenado
        vector <size_t> order = ordered<float>(P);
        end = order[0];
    }
    else{
        //El azar dice
        double random_value = RandomFloat();
        for(std::vector<int>::iterator it = candidate_list.begin(); it != candidate_list.end(); ++it){
            acu += P[*it];
            if(random_value <= acu)
                end = *it;
        }        
    }
    update_pheromene(start, end);
    return end;

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