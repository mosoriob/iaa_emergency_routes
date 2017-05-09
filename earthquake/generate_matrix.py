import numpy
from scipy.spatial import distance

from pandas import DataFrame, read_csv

import pandas as pd #this is how I usually import pandas
import sys #only needed to determine Python version number

numpy.set_printoptions(threshold=numpy.nan)

connections = numpy.zeros((33, 33))


distances = pd.read_csv('nodes.csv')
#print (distances)

row = 0
column = 0
f = open('instances.txt')
contents = f.read()
file_as_list = contents.splitlines()
for line in file_as_list:
	for connection in line.split(','):
		col =  int(connection) - 1

		n1_x = distances.x[col]
		n1_y = distances.y[col]
		n2_x = distances.x[row]
		n2_y = distances.y[row]

		n1 = (n1_x,n1_y)
		n2 = (n2_x,n2_y)
		length = distance.euclidean(n1,n2)

		if length > 0:
			print ('%d %d %f' %(col, row, length))
	row += 1
#print (connections)
if (connections.transpose() == connections).all():
	print ("sym")