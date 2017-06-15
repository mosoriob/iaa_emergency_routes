import csv
import random
import math 
T=4.83583
def parse():
	with open('datos_entrada.csv', 'r') as f:
	    data = [row for row in csv.reader(f.read().splitlines())]
	return data

datos = []
def generate():

	alphas = []
	betas  = []
	for i in range(1,68):
		alphas.append(random.uniform(0.9,0.9))
	 	betas.append(random.uniform(0.001,0.002))
	rowCount = 1	

	for row in parse():
		colCount = 1
		for col in row:
		 	if colCount == rowCount:
		 		colCount += 1
		 		continue
			if col != '999999' and col != '':
				i = rowCount
				j = colCount
				l = col
				ss = 100
				alpha =  alphas[rowCount-1]
				beta = betas[rowCount-1]
				datos.append([i, j, l, ss, alpha, beta])
			colCount += 1
		rowCount += 1

def printFile():
	for row in datos:
		print "%s %s %s %s %s %s"  %(row[0], row[1], row[2], row[3], row[4],row[5])

def check():
	for r in datos:
		inicial = r[0]
		target = []
		for row in datos:
			if row[0] == inicial:
				target.append(row[1])

		for t in target:
			for row in datos:
				if row[0] == inicial and row[1] == t:
					l = int(row[2])
					ss = row[3]
					alpha = row[4]
					beta = row[5]
					den1 = alpha*ss**math.exp(-beta*T)
					den2 = beta*l
					res = den2 - den1
					if res < 0:
						return True
		return True
generate()
if check():
	print "n %s" %(datos[-1][0])
	print datos[-1][0]-1
	printFile()
# t_1 = 1
# num = alphas[i][j]*ss[i][j];
# den1 = alphas[i][j]*ss[i][j]*exp(-betas[i][j]*t_1);
# den2 = betas[i][j]*large[i][j];
