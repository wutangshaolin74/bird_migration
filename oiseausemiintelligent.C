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
};

//the structure of the informations of the wind for 1 hour
struct wind {
    double normeofthespeed;
    double angleofthewind;
};

// function to converge angle in degrees into radian
double convertdegreesintorad(double angleindegrees){
    angleindegrees = angleindegrees * 2*M_1_PI /360;
    return angleindegrees;}

//if we had to convert angle in the reference of the trigonometric (the angle 0 is 90 degrees decalated)
double convertcompassintorad(double angleincompass){
    double angleinrad = 2 * M_1_PI - convertdegreesintorad(angleincompass-90);
    angleinrad = fmod(angleinrad, 2 * M_1_PI);
    return angleinrad;}



// function that find the alpha angle between the actual position and the final position (by using trigonometry)
double direction( struct point * currentposition, struct point * finalposition,  double sizeofasquare){
    double a = (finalposition->longtiude - currentposition->longtiude) * sizeofasquare ;
    double b = (finalposition->latitude - currentposition->latitude) * sizeofasquare;
    double alphaangle = atan2(a/b);
    return alphaangle;}

// function that decompose the speed vector of the bird into the x and y component (by using trigonometry)
void speedbird(double alphaangle, double speedbird, struct speed * currentbirdspeed ){
    currentbirdspeed->vitessex= sin(alphaangle)* speedbird;
    currentbirdspeed->vitessey = cos(alphaangle) * speedbird;
}


// function that decom^pse the speed vector of the wind into the x and y component (by using trigonometry)
void speedwind(double speedwind, struct speed * currentwindspedd,double windirection){
    currentwindspedd->vitessex= -sin(convertdegreesintorad(windirection))* speedwind;
    currentwindspedd->vitessey= -cos(convertdegreesintorad(windirection))* speedwind;
}

// function that calculate the speed along the x and y component and that takes the ponderation of the wind (it takes the wind and the bird speed and direction and return the final speed vector that would be use by the bird)
void realbirdspeed(struct speed * currentwindspeedwind, struct speed * currentspeedbird, struct speed * realbirdspeed, double facteurimpactation  ){
    realbirdspeed->vitessex= (currentspeedbird->vitessex + facteurimpactation * currentwindspeedwind->vitessex)/(facteurimpactation+1);
    realbirdspeed->vitessey= (currentspeedbird->vitessey + facteurimpactation * currentwindspeedwind->vitessey)/(facteurimpactation+1);
}
// function that calculate the displacement of the bird and that actualize his position 
void distanceparcourue(struct speed * realbirdspeed, double tempsparcours, double siezofasquare, struct point * currentposition){
    double distanceinx = realbirdspeed->vitessex * tempsparcours;
    double distanceiny = realbirdspeed->vitessey * tempsparcours;
    double latparcourue = distanceiny /siezofasquare;
    double longparcourue = distanceinx/ siezofasquare;
    currentposition->latitude=currentposition->latitude+  latparcourue;
    currentposition->longtiude = currentposition->longtiude + longparcourue; 
}


// function that calculate if the bird has arrival (we initialize one square were the bird must be in order to consider that he has arrived)
double isthebirdarrival(struct point  * currentposition, struct point * finalposition,double sizeofasquare){
    double margeofarrival = 20000/ sizeofasquare;
    double latmin= finalposition->latitude - margeofarrival;
    double latmax= finalposition->latitude - margeofarrival;
    double longmin= finalposition->longtiude- margeofarrival;
    double longmax= finalposition->longtiude - margeofarrival;
    if (latmin<currentposition->latitude<latmax && longmin<currentposition->longtiude<longmax){
        printf("The bird is arrival in");
        printf("The latitude an longitude of the bird are , %.6f and , %.6f",currentposition->latitude,currentposition->longtiude); 
        return 1;  
    return 0;
    }}


double deplacement(struct point * currentposition, struct point * positionfin, double birdspeed, struct casemeteo * casemeteo,double sizeofasquare, struct speed * currentbirdspeed){ 
    //Création du fichier CSV BirdPosition et écriture du header
    //char csv[] = ".csv";
    //char* file_name = strcat(filename, csv);
    

    FILE * filename = fopen (filename, "w");
    if (filename == NULL) {
        printf("Impossible d'ouvrir le fichier à écrire.\n");
        }
    fprintf (filename "%s,", "lat");
    fprintf (filename, "%s,", "long");
    fprintf (filename, "%s\n", "speedx");
    fprintf (filename, "%s\n", "speedx");
    double count=1;
    double i =1;
    while (i==1 && count<3001){
        count=count +1;
        double a=direction(&currentposition,&positionfin,sizeofasquare);
        double b=speedbird(a,birdspeed,* currentbirdspeed);
        

        
        
        
        //Écriture de la position [i] dans le .csv
        fprintf (fichier, "%f,", currentposition->latitude);
        fprintf(fichier, "%f,", currentposition->longtiude);
        fprintf(fichier, "%f\n", realbirdspeed->vitessex);
        fprintf(fichier, "%f\n", realbirdspeed->vitessey);
        if (count ==3000){
            printf("There was already 3000 iterations the bird will not converge to the point, or there is an errro in the programm");
            return 0;
        }   

    }
    }



int main(int argc, char const *argv[]) {
    struct point * currentposition={-15.101675033569336,-147.9429931640625};
    struct point * positionfin = {21.663944244384766,-157.92161560058594};
}


