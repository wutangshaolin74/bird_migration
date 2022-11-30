#include <unistd.h>
#include <stdio.h>
#include <math.h>
#include <inttypes.h>
#include <stdlib.h>
#include <time.h>


// the structure of a point in the planisphere in degrees with latitude and longitude
struct point  {
    double latitude;
    double longtiude;};

double convertdegresintorad(double angleindegrees){
    double angleindegrees = angleindegrees * 2*M_1_PI /360;
    return angleindegrees;}

double convertcompassintorad(double angleincompass){
    double angleinrad = 2 * M_1_PI - convertdegresintorad(angleincompass-90);
    angleinrad = mod(angleinrad, 2 * M_1_PI);}


// that function calculate the ponderation of the force of the wind by using its angle
double ponderationofforce (double * winddirection ,double * birddirection, double pourcentageimpactation){
    double factorofponderation = cos(convertcompassintorad(*winddirection)+ convertcompassintorad(*birddirection))* pourcentageimpactation;
    return(factorofponderation);}
//faire attention à si l'angle est du meme cote ou non que 



//return the speed of the bird after he has calculated the right angle to not be deported
double speedbird(double * windespeed,double * factorofponderation,double * birdspeed, double * rateoftiredness ){
    if(*birdspeed - *factorofponderation * (*birdspeed) <  *rateoftiredness){
        double realspeedbird = *birdspeed - *factorofponderation * *birdspeed;}
    else {double realspeedbird= 0;}
    return realspeedbird;}

//return the length that we have to parcour (by using pythagor theorem)
double findtrajectory(struct point * positionin, struct point * positionfinale, double sizeofasquare ){
    double x = (positionfinale->latitude-positionin->latitude) * sizeofasquare;
    double y = (positionfinale->longtiude- positionin->longtiude)* sizeofasquare;
    double trajectory = pow(x,2) + pow(y,2);
    return trajectory;}

double isthebirdarrival(struct point  * currentposition, struct point * finalposition,double sizeofasquare){
    double margeofarrival = 10000/ sizeofasquare;
    double latmin= finalposition->latitude - margeofarrival;
    double latmax= finalposition->latitude - margeofarrival;
    double longmin= finalposition->longtiude- margeofarrival;
    double longmax= finalposition->longtiude - margeofarrival;
    if (latmin<currentposition->latitude<latmax && longmin<currentposition->longtiude<longmax){
        printf("The bird is arrival in");
        printf("The latitude an longitude of the bird are , %.6f and , %.6f",currentposition->latitude,currentposition->longtiude);   
    }}




// a function that calculate the traject made by a bird
double calculationoftheparcour(double timeoftheparcour, double * realbirdspeed ){
    double distancebird = *realbirdspeed * timeoftheparcour;
    return distancebird;}



