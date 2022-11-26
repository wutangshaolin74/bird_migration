#include <unistd.h>
#include <stdio.h>
#include <math.h>
#include <inttypes.h>
#include <stdlib.h>
#include <time.h>

//a point in latitude and longtiude
struct point  {
    double latitude;
    double longtiude;};

// a speed with the x coordinate and the y coordinate
struct vitesse {
    double vitessex;
    double vitessey;};



// function to convert angle in radian into degrees
double convertradintodegrees(double angleinrad){
    double angleindegreees = angleinrad * 360/ (2* M_1_PI);
    return angleindegreees;}

// function to converte angle in degrees into radian
double convertdegressintorad(double angleindegrees){
    double angleindegrees = angleindegrees * 2*M_1_PI /360;
    return angleindegrees;}

// function to convert radian into compass angle
double convertradintocompass(angleinrad) {
   double compassangle = convertradintodegrees((2*M_1_PI - (angleinrad)))+90;
   compassangle = mod(compassangle,360);}

// function to convert compass into radian angle 
double convertcompassintorad(angleincompass){
    double angleinrad = 2 * M_1_PI - convertdegressintorad(angleincompass-90);
    angleinrad = mod(angleinrad, 2 * M_1_PI);}

// a function that takes the current position and the final position so as to return the direction of the bird
double directionfor1H (struct point * currentposition, struct point * finalposition){
   double var1 = sin(convertdegressintorad(finalposition->longtiude ))* cos(convertcompassintorad(finalposition->latitude));
   double var2 = sin(convertdegressintorad(finalposition->latitude))*cos(convertdegressintorad(currentposition->latitude))-sin(convertradintodegrees(currentposition->latitude));
   double angle = asin(var1)/acos(var2);
   double returnangle = mod(convertradintodegrees(angle),360);
   return returnangle;}

// a function that takes the postion of a point and the norm of the speed to return the vitesse in x and in y
void speedbird (struct vitesse * currentspeed, double pointedposition, double speedvector){
    currentspeed->vitessex = cos(pointedposition) * speedvector;
    currentspeed->vitessey= sin(pointedposition) * speedvector;}

// a function that return the real norm of the speed vector that is applied on the bird
double sumofforce(struct vitesse * currentspeed, struct vitesse * currentwind){
    double vectortoreturn = sqrt((currentspeed->vitessex+currentwind->vitessex)*(currentspeed->vitessex+currentwind->vitessex)+(currentspeed->vitessey+currentwind->vitessey)*(currentspeed->vitessey+currentwind->vitessey));
    return vectortoreturn;}


// a function that return the orientation for the next hour 
double orientationfor1(struct vitesse * currentspeed,struct speed * currentwind,double summofforce){
    if (currentspeed->vitessey+ currentwind->vitessey)<0 {
        double orientationtoreturn = 2 * M_1_PI - acos((currentspeed->vitessex+currentwind->vitessex)/summofforce);}  // voir avec leo pk il rajoute une random value
    elif(currentspeed->vitessey+ currentwind->vitessey)>0 {
        double orientationtoreturn = acos((currentspeed->vitessex+currentspeed->vitessex)/sumofforce);}
    else{
        if ((currentspeed->vitessex+currentwind->vitessex)>0) {}

    }
    }

