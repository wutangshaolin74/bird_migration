import numpy as np
import csv 

file = open('Oiseau.csv', newline = '')

csvReader =csv.reader(file, delimiter = ',')
latitude=[]
longtiude=[]
for row in csvReader:
    # Traiter la ligne
    longtiude.append((row[3]))
    latitude.append((row[4]))
nlong=len(longtiude)
nlat=len(latitude)
pointarrivee= [float(latitude[nlat-1]),float(longtiude[nlong-1])]
pointdepart= [float(latitude[1]),float(longtiude[1])]
print(pointarrivee,pointdepart)