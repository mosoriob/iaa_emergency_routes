import numpy as np
from scipy.optimize import fsolve

time = 0
tour = []
tour.append(1)
tour.append(6)
tour.append(16)
tour.append(18)
tour.append(20)

for point in tour:
    print point




alphas = np.zeros(shape=(20,20), dtype=np.float)
betas = np.zeros(shape=(20,20),dtype=np.float)
ss = np.zeros(shape=(20,20),dtype=np.float)
ls = np.zeros(shape=(20,20),dtype=np.float)

alphas[0][5] = 0.63
betas[0][5] = 0.17
ss[0][5] = 60
ls[0][5] = 30

ls[5][15] = 100
ss[5][15] = 115
alphas[5][15] = 0.66
betas[5][15] = 0.19

ls[15][17] = 110
ss[15][17] = 120
alphas[15][17] = 0.63
betas[15][17] = 0.15

ls[17][19] = 120
ss[17][19] = 120
alphas[17][19] = 0.73
betas[17][19] = 0.14

size_tour = len(tour)
t_inicial=0
for index, point in enumerate(tour):
    if index < (size_tour-1):
        i =  tour[index]-1,
        j = tour[index+1]-1
        constante = (ss[i][j]*alphas[i][j])/betas[i][j]
        t_inicial = -np.log(-ls[i][j]/constante + np.exp(-betas[i][j]*t_inicial))/betas[i][j]
        print t_inicial        
        #func = lambda t_final : cons(*(-np.exp(-betas[i][j]*t_inicial) + np.exp(-betas[i][j]*t_final)) + ls[i][j]
        #t_initial_guess = 0.5
        #t_inicial =+ fsolve(func, t_initial_guess)
        #print "The solution is tau = %f" % t_inicial
