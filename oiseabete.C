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
// the structure of the two components of the speed in a cartesian repere
struct speed{
    double vitessex;
    double vitessey;
}

// function to converge angle in degrees into radian
double convertdegressintorad(double angleindegrees){
    double angleindegrees = angleindegrees * 2*M_1_PI /360;
    return angleindegrees;}


// function that find the alpha angle between the actual position and the final position
double direction( struct point * currentposition, struct point * finalposition,  double sizeofasquare){
    double a = (finalposition->longtiude - currentposition->longtiude) * sizeofasquare ;
    double b = (finalposition->latitude - currentposition->latitude) * sizeofasquare;
    double alphaangle = atan2(a/b);
    return alphaangle;}

// function that decompose the speed vector of the bird into the x and y component
void speedbird(double alphaangle, double speedbird, struct speed * currentbirdspeed ){
    currentbirdspeed->vitessex= sin(convertdegreesintorad(alphaangle))* speedbird;
    currentbirdspeed->vitessey = cos(convertdegressintorad(alphaangle)) * speedbird;
}


// function that decom^pse the speed vector of the wind into the x and y component
void speedwind(double speedwind, struct speed * currentwindspeed,double windirection){
    currentwindspedd->vitessex= sin(convertdegressintorad(windirection))* speedwind;
    currentwindspedd->vitessey= cos(convertdegressintorad(windirection))* speedwind;
}

// function that calculate the speed along the x and y component and that takes the ponderation of the wind
void realbirdspeed(struct speed * currentwindspeedwind, struct speed * currentspeedbird, struct speed * realbirdspeed, double facteurimpactation ){
    realbirdspeed->vitessex= (currentspeedbird->vitessex + facteurimpactation * currentwindspeedwind->vitessex)/(facteurimpactation+1);
    realbirdspeed->vitessey= (currentspeedbird->vitessey + facteurimpactation * currentwindspeedwind->vitessey)/(facteurimpactation+1);
    
}
// function that calculate the displacement of the bird and that actualize his position 
void distanceparcourue(struct speed * realbirdspeed, double tempsparcours, double siezofasquare, struct point * currentposition){
    double distanceinx = realbirdspeed->vitessex * tempsparcours;
    double distanceiny = realbirdspeed->vitessey * tempsparcours;
    double latparcourue = distanceinx /siezofasquare;
    double longparcourue = distanceiny/ siezofasquare;
    currentposition->latitude=currentposition->latitude+  latparcourue;
    currentposition->longtiude = currentposition->longtiude + longparcourue; 
}


// function that calculate if the bird has arrival 
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
