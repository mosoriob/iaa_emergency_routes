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
extern bool DEBUG;
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

template <typename T>
std::vector<size_t> orderedReverse(std::vector<T> const& values) {
    std::vector<size_t> indices(values.size());
    std::iota(begin(indices), end(indices), static_cast<size_t>(0));

    std::sort(
        begin(indices), end(indices),
        [&](size_t a, size_t b) { return values[a] < values[b]; }
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
                if (DEBUG)
                    cout << alphas[i][j] << endl;
                t_2 = log((alphas[i][j]*ss[i][j])/(alphas[i][j]*ss[i][j]*exp(-betas[i][j]*t_1) \
                        - betas[i][j]*large[i][j]))/betas[i][j];
            }
        } 
        t_1=t_2;
    }
    if (DEBUG){
        cout << "DEBUG: "   <<  endl;
        cout << "DEBUG: t_1 "    <<  t_1 << endl;
        cout << "DEBUG: alphas " << alphas[i][j] << endl;
        cout << "DEBUG: ss     " << ss[i][j] << endl;
        cout << "DEBUG: betas  " << betas[i][j] << endl;
        cout << "DEBUG: large  " << large[i][j] << endl;
        cout << "DEBUG: t_2    " << t_2 << endl;
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
    vector <int> candidateList; 
    for(int i=0; i<N; i++){
        std::vector<int>::iterator it = find(tour.begin(), tour.end(), i);
        if(it == tour.end() && large[town][i]!=0 && i!=0){
            candidateList.push_back(i);
        }
    }
    if (DEBUG){
        cout << "number of neighbours: " << candidateList.size() << endl;
        for(std::vector<int>::iterator it = candidateList.begin(); it != candidateList.end(); ++it){
            cout << *it << "," ;
        }
        cout << endl;
    }
    return candidateList;
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

/**
Funcion que generar la lista de candidatos de acuerdo a cl
**/
vector <int> generateCandidateList(vector<int> allNeighbours, vector<int> tour){
    vector <float> timeTour(N, -1);
    vector <int> allCandidateList;

    for(std::vector<int>::iterator it = allNeighbours.begin(); it != allNeighbours.end(); ++it){
        vector<int> new_tour = tour;
        new_tour.push_back(*it);
        timeTour[*it] = time_tour(new_tour);
    }

    vector <size_t> orderTime = orderedReverse<float>(timeTour);
    for(int j = 0; j < orderTime.size(); j++){
        if ( timeTour[orderTime[j]] > 0)
            allCandidateList.push_back(orderTime[j]);
    }

    if (allCandidateList.size() > cl)
        allCandidateList.resize(cl);

    return allCandidateList;
}

int next_town(int town, vector<int> tour){
    int start = tour.back();
    town = start;
    int end;

    vector <int> allNeighbours = neighbours(start, tour);
    vector <float> P(N,0);
    float denomitador = 0;
    float eta;
    float acu = 0.0;

    vector <int> candidateList = generateCandidateList(allNeighbours, tour);


    //Obtener el denominador
    for(std::vector<int>::iterator it = candidateList.begin(); it != candidateList.end(); ++it){
        vector<int> new_tour = tour;
        new_tour.push_back(*it);

        double time_to = time_tour(new_tour);
        eta = 1/time_to;
        if (DEBUG){
            cout << "=========================" << endl;
            cout << "Entre " << town << " y " << *it << endl;
            cout << "TAU " << tau[town][*it] << endl;
            cout << "TIME " << time_to << endl;
            cout << "ETA " << eta << endl;
            cout << "=========================" << endl;
        }

        denomitador += pow(tau[town][*it],alpha_ant)*pow(eta,beta_ant);        
    }
    //Crear las probalidades
    for(std::vector<int>::iterator it = candidateList.begin(); it != candidateList.end(); ++it){
        vector<int> new_tour = tour;
        new_tour.push_back(*it);
        eta = 1/time_tour(new_tour);
        P[*it] = pow(tau[town][*it],alpha_ant)*pow(eta,beta_ant)/denomitador;
    }

    double q = random_float();
    if(q < q_0){
        vector <size_t> order = ordered<float>(P);
        end = order[0];
    }
    else{
        double random_value = random_float();
        for(std::vector<int>::iterator it = candidateList.begin(); it != candidateList.end(); ++it){
            acu += P[*it];
            if(random_value <= acu){
                end = *it;
            }
            else{
                end = candidateList.back();
            }
        }        
    }
    if (DEBUG){
        cout << "Next node " << end << endl;
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