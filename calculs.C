#include <unistd.h>
#include <stdio.h>
#include <math.h>
#include <inttypes.h>
#include <stdlib.h>
#include <time.h>


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