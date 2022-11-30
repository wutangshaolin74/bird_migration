#include <unistd.h>
#include <stdio.h>
#include <math.h>
#include <inttypes.h>
#include <stdlib.h>
#include <time.h>

$struct speed{
    double vitessex;
    double vitessey;
};
double convertdegreesintorad(double angleindegrees){
    double angleindegrees = angleindegrees * 2*M_1_PI /360;
    return angleindegrees;}

//if we had to convert angle in the reference of the trigonometric (the angle 0 is 90 degrees decalated)
double convertcompassintorad(angleincompass){
    double angleinrad = 2 * M_1_PI - convertdegreesintorad(angleincompass-90);
    angleinrad = mod(angleinrad, 2 * M_1_PI);}


void speedwind(double speedwind, struct speed * currentwindspeed,double windirection){
    currentwindspedd->vitessex= -sin(convertdegreesintorad(windirection))* speedwind;
    currentwindspedd->vitessey= -cos(convertdegreesintorad(windirection))* speedwind;
}

int main(int argc, char const *argv[]) {
    double speedwind = 1;
    struct speed Ventvitesse = {0,0};
    double winddirecetion= 315;
    void(speedwind, *Ventvitesse, winddirecetion);
    printf("vitesse x %.f vitesse y %.f", Ventvitesse->vitessex, Ventvitesse->vitessey);
    return 1;
}