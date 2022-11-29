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
long1=pointdepart[0]
lat1=pointdepart[1]
long2=pointarrivee[0]
lat2=pointarrivee[1]
L=[str(long1)+"\n",str(lat1)+"\n",str(long2)+"\n",str(lat2)+"\n"]
file1 = open("data.csv", "w")
file1.writelines(L)
file1.close()





