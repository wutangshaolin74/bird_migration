from fileinput import filename
import urllib
from urllib import parse, request
import csv 
import os 
import requests

def GetUrl (lati, longi):
    url_base = "http..."
    parameters = {"apikey" : "XXXXXXX", "latitude" : lati, "longitude" : longi, "start_date" : "XX.XX.XXXX", "end_date" : "XX.XX.XXXX"}
    querystring = parse.urlencode(parameters) 
    url = url_base + querystring
    
    #We then stock our data into a textfile 
    x_coord = str(x)
    y_coord = str(y)
    format = ".txt"
    our_file = "Data file" + x_coord + y_coord + format

    return url, our_file

#Request to get data from MeteoBlue
def GetData (url, our_file) :
    answer = requests.get(url)
    if answer.ok :
        with open ("MeteoData/" + filename, "wb") as f :
            f.write(answer.content)

    else : 
        print("An error happened during the process. Try again")

#Automatization of the code, depending on our area (a rectangle) divided in squares
increment = XXX #side of a square
lati_initial = XXX 
longi_initial = XXX  #our initial point is the botom left of the rectangle
            
if not(os.path.exists ("IterationCount.csv")) : 
    with open ("IterationCount.csv", "w", newline = "") as f :
        csvWriter = csv.writer(f, delimiter = ",")
        csvWriter.writerow([1,1])
        csvWriter.writerow([lati_initial,longi_initial])
           
with open ("IterationCount.csv", "r", newline = "") as f :
    csvReader = csv.reader(f)
    rows = []
    for row in csvReader :
        rows.append(row)
    k = int(rows[0][0])
    l = int(rows[0][1])
    lati = float(rows[1][0])
    longi = float(rows[1][1])

    i = 0
    j = 0

    for y in range (k,13) :
        for x in range (l,9) : 
            count = i + j 
            if count > 9 : 
                with open ("IterationCount.csv", "w", newline = "") as f : 
                    csvWritter = csv.writer(f)
                    cswWritter.writerow([y,x])
                    cswWriter.writerow([lati, longi])
                break
            else : 
                url, our_file = urlGenerate (lati, longi)
                GetData(url, our_file)
                longi += increment 
                j += 1
        if count > 9 : break
        lati += increment 
        i += 1
        longi  = longi_initial
        l = 1