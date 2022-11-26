#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h> 
struct vitesse1heure{
    double vteta;
    double vphi;};

struct pointsph  {
    double latitude;
    double longitude;};

double findspeed(struct pointsph  * positionfinale, struct pointsph  * currentposition , double speedbird , double speedwind, double winddirection){
    double normedev= 20;
    double vecteurpositionlatitude = positionfinale->latitude - currentposition->latitude;
    double vecteurpositionlongitude = positionfinale->longitude - currentposition->longitude;} 

double oiseaudisplacement (struct pointsph  * currentposition , struct vitesse1heure * vitesse, struct  pointsph  * tableaudedonée, int * count){
    currentposition->latitude = currentposition->latitude + vitesse->vteta;
    currentposition -> longitude = currentposition-> longitude + vitesse->vphi;
    tableaudedonée[*count].latitude= currentposition->latitude;
    tableaudedonée[*count].longitude = currentposition-> longitude;
    count=count+1;
    return 1;}


int readfile(char *filename, int length, double * point) {
    /*
    Reads in data file called "filename"
    up to "length" number of rows
    into an array of structures of struct TimeSeries called "conc".

    Returns an integer corresponding to number of rows read in.
    */

    FILE *fid = fopen(filename, "r");
    if(fid == NULL) return -1;

    int n=0;    
    char buffer[100];  
    while (fgets(buffer, 100, fid) != NULL) {
    if(n >= length) break;
    sscanf(buffer, "%.6f",&point[n]);
    n++;
    }
    return n;}



int main(int argc, char * argv[]) {
    double point[4];
    int nbPoints = readfile("data.csv", 5, point);
    struct pointsph positionin;
    int count=1;
    struct pointsph  currentposition = {positionin.latitude,positionin.longitude};
    struct pointsph  talbeaudedonnée [3000];
    FILE * file = fopen("data.txt", "r");
    printf("%.f", point[3]);
    return 0;}