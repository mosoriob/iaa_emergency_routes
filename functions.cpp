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
extern ifstream ifs;
/***** Estructuras de representación *****/
extern vector< vector<int> >    ants;
extern vector< vector<float> >  alphas;
extern vector< vector<float> >  betas;
extern vector< vector<float> >  large;
extern vector< vector<float> >  ss;
extern vector< vector<float> >  tau;
extern vector< string >  safe_areas;

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
            i = tour[index];
            j = tour[index+1];
            if(betas[i][j]==0.0){
                t_2 = large[i][j]/(ss[i][j]*alphas[i][j]) + t_1;
            }
            else{
                t_2 = log( (alphas[i][j]*ss[i][j])/( alphas[i][j]*ss[i][j]*exp(-betas[i][j]*t_1) \
                        - betas[i][j]*large[i][j]) )/betas[i][j];
            }
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
Calcula el tiempo que toma un tour
*/
void best_tour_update_pheromone(vector <int> &tour, float best_tour_time) {
    int size = (int) tour.size();
    int i, j;
    for(int index = 0; index<size; index++){
        if (index < size - 1){
            i =  tour[index];
            j = tour[index+1];
            tau[i][j] = (1 - ro)*tau[i][j] + ro*(1/best_tour_time);
        } 
    }
}

vector <int> neighbours(int town, vector<int> tour){
    for(std::vector<int>::iterator it2 = tour.begin(); it2 != tour.end(); ++it2){
        ////cout <<  *it2 << ",";       
    }
    ////cout << endl;

    vector <int> candidate_list; 
    //todo: Definir si el candidate list tiene un limite.
    for(int i=0; i<N; i++){
        std::vector<int>::iterator it = find (tour.begin(), tour.end(), i);
        if(it == tour.end() && large[town][i]!=0 && i!=0){
            candidate_list.push_back(i);
        }
    }
    return candidate_list;
}

double random_float() {
  string line = "";
  ifs >> line;

  unsigned seed = chrono::system_clock::now().time_since_epoch().count();
  default_random_engine generator (seed);
  //seed_seq seed (line.begin(),line.end());
  //minstd_rand0 generator (seed);
  uniform_real_distribution<double> distribution (0.0,1.0);
  return distribution(generator);
}

//favorecer la exploracion, haciendo menos atractivos los nodos visitados
void update_pheromene(int i, int j){
    tau[i][j] = (1 - ro)*tau[i][j] + ro*tau_0;
}

int next_town(int town, vector<int> tour){
    int start = tour.back();
    town = start;
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
        //cout << "Variables" << endl;
        //cout << "Se añade " << *it << endl;
        double time_to = time_tour(new_tour);
        eta = 1/time_to;
        //cout << "ok" << endl;
        //cout << "=========================" << endl;
        //cout << "Entre " << town << " y " << *it << endl;
        //cout << "TAU" << tau[town][*it] << endl;
        //cout << "TIME" << time_to << endl;
        //cout << "ETA" << eta << endl;
        //cout << "=========================" << endl;

        denomitador += pow(tau[town][*it],alpha_ant)*pow(eta,beta_ant);        
    }
    //Crear las probalidades
    for(std::vector<int>::iterator it = candidate_list.begin(); it != candidate_list.end(); ++it){
        vector<int> new_tour = tour;
        new_tour.push_back(*it);
        eta = 1/time_tour(new_tour);
        P[*it] = pow(tau[town][*it],alpha_ant)*pow(eta,beta_ant)/denomitador;

        //cout << *it << "-" << P[*it] << "-" << denomitador << endl;
    }

    double q = random_float();
    if(q < q_0){
        //cout << "Elite" << endl;
        //El mejor es el primero del vector ordenado
        vector <size_t> order = ordered<float>(P);
        end = order[0];
    }
    else{
        //El azar dice
        //cout << "Azar" << endl;

        double random_value = random_float();
        for(std::vector<int>::iterator it = candidate_list.begin(); it != candidate_list.end(); ++it){
            //cout << "Elige " << *it << "?";
            acu += P[*it];
            if(random_value <= acu){
                end = *it;
            }
            else{
                end = candidate_list.back();
            }
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
    vector <float> newColumn(N,q_0);
    //fill(newColumn.begin(),newColumn.end(),0);
    for(int i=0; i < N; i++)
        matrix.push_back(newColumn);
}


void fill(char *name) {
    /* Rellena arreglo con los numeros de las ciudades, poniendolas en
    el orden 1,2,...,N. Rellena el arreglo de la posicion de las ciudades. */
    ifstream infile (name);
    if ( !infile.good() ){
        cout << "Error opening file" << endl;
        exit (1);
    }

    int cnt=0;
    int l,s,i,j,n;
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
        else if(cnt == 1){
            stringstream ss(line);
            string tmp;
            while(getline(ss,tmp,' ')){
                safe_areas.push_back(tmp);
            }
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
    infile.close();
}

bool is_safe(int town){
    for (vector<string>::iterator it = safe_areas.begin(); it!=safe_areas.end(); ++it){
        if ( stoi(*it) == town ){
            return true;
        }
    }
    return false;    
}