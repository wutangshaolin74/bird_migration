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


void fillWindMap(struct caseMeteo * caseMeteo){

  for (int y = 0; y < 10; y++) {
      for(int x = 0; x < 8; x++) {
          int temp_x = x + 1;
          int temp_y = y + 1;
          char y_str [10];
          char x_str [10];
          sprintf(x_str, "%d", temp_x);
          sprintf(y_str, "%d", temp_y);
          char outro[] = ".txt";
          char intro[100] = "../Data/Data_file_";
          char* file_name = strcat(strcat(strcat(intro, x_str), y_str), outro);
          printf("Le fichier utilisé pour remplir les prochaines cases est %s\n", file_name);
        

          FILE *fp;
          char buffer [100000];

          struct json_object *parsed_json;
          struct json_object *history_1h;
          struct json_object *time;
          struct json_object *wind_speed;
          struct json_object *wind_direction;

          fp = fopen (file_name, "r");

          fread (buffer, 100000, 1, fp);
          fclose(fp);

          parsed_json = json_tokener_parse(buffer);

          json_object_object_get_ex(parsed_json, "history_1h", &history_1h);
          json_object_object_get_ex(history_1h, "windspeed_80m", &wind_speed);
          json_object_object_get_ex(history_1h, "winddirection_80m", &wind_direction);
          json_object_object_get_ex(history_1h, "time", &time);

          int n_time = json_object_array_length(time);
          
          struct json_object *spe_time;
          struct json_object *spe_windspeed;
          struct json_object *spe_winddirection;



          for (int i = 0; i < n_time; i++) {
              spe_time = json_object_array_get_idx(time, i);

              spe_windspeed = json_object_array_get_idx(wind_speed, i);


              spe_winddirection = json_object_array_get_idx(wind_direction, i);

              caseMeteo[(y*8*720) + (x*720) + i].windspeed = json_object_get_double (json_object_array_get_idx(wind_speed, i));
              caseMeteo[(y*8*720) + (x*720) + i].winddirection = json_object_get_double (json_object_array_get_idx(wind_direction, i));
          }

      }

  }
}






// a function that return the orientation for the next hour 
void orientationfor1(struct vitesse * currentspeed,struct speed * currentwind,double summofforce, double * actualorientation ){
    if (currentspeed->vitessey+ currentwind->vitessey)<0 {
        *actualorientation = 2 * M_1_PI - acos((currentspeed->vitessex+currentwind->vitessex)/summofforce);}  // voir avec leo pk il rajoute une random value
    elif(currentspeed->vitessey+ currentwind->vitessey)>0 {
        *actualorientation = acos((currentspeed->vitessex+currentspeed->vitessex)/sumofforce);}
    else{
        if ((currentspeed->vitessex+currentwind->vitessex)>0) { *actualorientation=0 }
        elif ((currentspeed->vitessex+currentwind->vitessex)>0)  { *actualorientation=M_1_PI }
        else {
            printf("there is an error in the orientation of the bird");
        }
    }    }

void vectorofdeisplacement(struct point * currentposition, struct point * finalposition, double * radiustobird, double * vectorofdisplacement){
    double angletogetdistance = pow(sin((finalposition->latitude-currentposition->latitude)/2),2)+ cos(finalposition->longtiude)*cos(currentposition->longtiude)*pow(sin((finalposition->longtiude-currentposition->longtiude)/2),2);
    *vectorofdeisplacement= *radiustobird * atan2(sqrt(angletogetdistance),sqrt(1-angletogetdistance));}

double birdtrajctory(struct meteo * caseMeteo, struct vitesse * currentspeed, struct point * currentposition, struct point * finalposition, struct point * initialposition, double * birdresistance, char * nameofthefile)