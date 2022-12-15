//Here we do all the imports that we need so as to do the programm (the special one is the jason that allows us to use jason structures)

#include <unistd.h>
#include <stdio.h>
#include <math.h>
#include <inttypes.h>
#include <stdlib.h>
#include <time.h>
#include <json-c/json.h>
#include <string.h>
#include <stdbool.h>

//Here is the structure of a caseMeteo case that will contains in the table the windspeed and winddirection for 1h
// We will define another one because we use this one only to extract the datas of wind
struct caseMeteo{
  double windSpeed;
  double windDirection;
};

struct value{
  double value;
};

// structure of point in the planisphere (degrees)
struct point {
  double latitude;
  double longitude;
};

// structure of speed component (cartesian frame)
struct speed {
  double speedX;
  double speedY;
};

//The other structure structure of the wind
struct wind {
  double windSpeed;
  double windAngle;
};


void fillWindMap(struct caseMeteo* caseMeteo){
  for (int y = 0; y < 12; y++) {
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
/*printf("Le fichier utilisé pour remplir les prochaines cases est %s\n", file_name);*/
          FILE *fp;
          char buffer [100000];
          struct json_object *parsed_json;

struct json_object *history_1h;

struct json_object *time;

struct json_object *windSpeed;

struct json_object *windDirection;



fp = fopen (file_name, "r");



fread (buffer, 100000, 1, fp);

fclose(fp);



parsed_json = json_tokener_parse(buffer);





json_object_object_get_ex(parsed_json, "history_1h", &history_1h);

json_object_object_get_ex(history_1h, "windspeed_80m", &windSpeed);

json_object_object_get_ex(history_1h, "winddirection_80m", &windDirection);

json_object_object_get_ex(history_1h, "time", &time);



int n_time = json_object_array_length(time);




struct json_object *spe_windspeed;

struct json_object *spe_winddirection;







for (int i = 0; i < n_time; i++) {


spe_windspeed = json_object_array_get_idx(windSpeed, i);



spe_winddirection = json_object_array_get_idx(windDirection, i);



caseMeteo[(y*8*720) + (x*720) + i].windSpeed = json_object_get_double (spe_windspeed);

caseMeteo[(y*8*720) + (x*720) + i].windDirection = json_object_get_double (spe_winddirection);

}



}



}

}









// function to convert angle in degrees into radian

double deg2rad(double degAngle) {

return (degAngle * M_PI)/180;}





//if we had to convert angle in the reference of the trigonometric (the angle 0 is 90 degrees decalated)

double compass2rad(double compassAngle){

double radAngle = 2 * M_PI - deg2rad(compassAngle-90);

radAngle = fmod(radAngle, 2 * M_PI);

return radAngle;}





// function that find the alpha angle between the actual position and the final position (by using trigonometry)

// We have as an input the currentposition and the finalpoistion and we return the angle

double direction( struct point * currentPosition, struct point * finalPosition, double meter2degFactor){

double a = (finalPosition->longitude - currentPosition->longitude) * meter2degFactor ;

double b = (finalPosition->latitude - currentPosition->latitude) * meter2degFactor;

double alphaAngle = atan2(a,b);

return alphaAngle;}



// function that decompose the speed vector of the bird along the x and y component (by using trigonometry)

// We input the angle that we have calculated with the function direction and with the norm of the speed (here double speedbird)

// we can put in our pointer currentbirdspeed (that is define as a speed structure) the speed induce by the bird along the x and along the y axis

void birdSpeed(double alphaAngle, double birdSpeed, struct speed * currentBirdSpeed ){

currentBirdSpeed->speedX= sin(alphaAngle)* birdSpeed;

currentBirdSpeed->speedY = cos(alphaAngle) * birdSpeed;

}





// function that decompose the speed vector of the wind into the x and y component (by using trigonometry)

// We input the norm of the wind (double speed wind ) and it's position (double windirection)

//so as to put in our pointer currentwindspeed (that is define as a speed structure) the speed induce by the wind along the x and y axis

void windFuncSpeed(double windSpeed, struct speed * currentWindSpeed,double windDirection){

currentWindSpeed->speedX= -sin(deg2rad(windDirection))* windSpeed;

currentWindSpeed->speedY= -cos(deg2rad(windDirection))* windSpeed;}



// function that calculates the real speed along the x and y component

// By taking the speed induce by the wind and the bird (along x and y component) and by taking the factor of ponderation of the wind

//it puts in the pointer realbirdspeed the real speed of the bird along x and y component (reaalbirdspeed is define as a speed structure)

void actualFuncBirdSpeed(struct speed * currentWindSpeed, struct speed * currentBirdSpeed, struct speed * actualBirdSpeed, double deviationImpactFactor ){

actualBirdSpeed->speedX= (currentBirdSpeed->speedX + deviationImpactFactor * currentWindSpeed->speedX)/(deviationImpactFactor+1);

actualBirdSpeed->speedY= (currentBirdSpeed->speedY + deviationImpactFactor * currentWindSpeed->speedY)/(deviationImpactFactor+1);

}

// function that calculate the displacement of the bird and that actualize his position

// By taking the realbirdspeed the time of the parcour the factor from meters to degrees

//it actualize the position of the bird in a pointer currentposition (that is a point structure) that follows the current position of the point.



void traveledDistance(struct speed * actualBirdSpeed, double journeyDuration, double meter2degFactor, struct point * currentPosition){

//we calculate the distance traveled by the bird
double distanceX = actualBirdSpeed->speedX * journeyDuration;
double distanceY = actualBirdSpeed->speedY * journeyDuration;

// we multiply this distance by the factor to go from meter to degrees (in latitude and longitude)
double traveledLongitude = distanceX * meter2degFactor;
double traveledLatitude = distanceY * meter2degFactor;




//then we can actualize the position of the bird by making the sum of his actual position and the distance traveled in degrees

currentPosition->longitude = currentPosition->longitude + traveledLongitude;

currentPosition->latitude= currentPosition->latitude+ traveledLatitude;


}





// function that calculate if the bird has arrival (we initialize one square were the bird must be in order to consider that he has arrived)

//boolean buffer_arrival(struct point * currentposition, struct point * finalposition, double sizeofsquare){

// double margeofarrival = 20000 / sizeofsquare;

//double latmin= finalposition->latitude - margeofarrival; // la largeur finale du buffer est doublée

//double latmax= finalposition->latitude - margeofarrival;

// double longmin= finalposition->longitude- margeofarrival;

//double longmax= finalposition->longitude - margeofarrival;

//if (latmin<currentposition->latitude<latmax && longmin<currentposition->longitude<longmax) {return False;}

//else {return True;}

//}



// This is the function is the condition of arrival of the bird

// It takes the position of the bird and define a square if the bird is in the square we consider that the bird arrived

bool birdArrivalBuffer(struct point * currentPosition, struct point * finalPosition,double meter2degFactor){

  //firstly we define the size of the square in meters and we multiply it by the factor of meter to degrees to have it in degrees

double arrivalBuffer = 50000 * meter2degFactor;

// We define the 4 points of the square lat min and max and long min and max

double latMin= finalPosition->latitude - arrivalBuffer;

double latMax= finalPosition->latitude + arrivalBuffer;

double longMin= finalPosition->longitude - arrivalBuffer;

double longMax= finalPosition->longitude + arrivalBuffer;

//We return true or false in function of the arrival of the bird or not

if (latMin<currentPosition->latitude && currentPosition->latitude<latMax && longMin<currentPosition->longitude && currentPosition->longitude<longMax){
  printf("The bird made it with \n Latitude : %f \n Longitude : %f\n", currentPosition->latitude,currentPosition->longitude);
//  printf("The latitude and longitude of the bird are : \n %.6f and %.6f",currentPosition->latitude,currentPosition->longitude);
  return true;
}
return false;
}

void birdJourney(struct speed * currentSpeed,struct point * finalPosition,struct point * currentPosition, struct speed * currentWind, struct speed * actualBirdSpeed,
  double initialSpeed, double deviationImpactFactor, double flightDuration, double meter2degFactor, double angleIncrement, FILE * file ,struct caseMeteo* caseMeteo, int hour) {

  //initilisation of the structure bird_position with values = 0
  // comment definir que notre structure a deux parametre ?? en haut ?? latitude et longitude
  // erreur avec sizeof!!!!!!
  //struct tab_position * tab_position = calloc(1000, sizeof(struct bird_position)); // que mettre en deuxieme argument ???

  //origin (bottom left point) of our rectangle
  double originLat = -16.000;
  double originLong = -160.000;

  //Here we define the floor of the wind so as to have access to it
  int tableY = floor((currentPosition->latitude - originLat)/angleIncrement);
  int tableX = floor((currentPosition->longitude - originLong)/angleIncrement);

  // In case we would be out of the square we put limit cases
  if (tableX < 0) tableX = 0;
  if (tableY < 0) tableY = 0;

  if (tableX > 7) tableX = 7;
  if (tableY > 11) tableY = 11;

  //then we have the wind for one hour that we search in our big table
  double windSpeed = (caseMeteo[(tableY*720*8) + (tableX*8) + hour].windSpeed);
  double windOrigin = (caseMeteo[(tableY*720*8) + (tableX*8) + hour].windDirection);

  //Then we use the previous functions to reactualize the position of the bird
  //We calulate the direction of the bird
  double a=direction(currentPosition, finalPosition, meter2degFactor);

  //We calculate the speed induces by the bird
  birdSpeed(a, initialSpeed, currentSpeed);

  //We calculate the speed induces by the bird
  windFuncSpeed(windSpeed,currentWind,windOrigin);

  //We calculate the real speed of the bird
  actualFuncBirdSpeed(currentWind, currentSpeed,actualBirdSpeed,deviationImpactFactor);

  //We use the last function to get the position of the bird afte one hour
  traveledDistance(actualBirdSpeed, flightDuration, meter2degFactor, currentPosition);

  // CSV FILE
  //values of the bird position that we input in the file
  fprintf(file,"%f,  ",currentPosition->latitude);
  fprintf(file,"%f,  ",currentPosition->longitude);
  fprintf(file,"%f,  ",actualBirdSpeed->speedX);
  fprintf(file,"%f",actualBirdSpeed->speedY);
  fprintf(file,"\n");
}


int readfile(char *filename, int length,struct value * value) {

  FILE *frd = fopen(filename, "r");
  if(frd == NULL) return -1;

  int n=0;
  char buffer[100];
  while (fgets(buffer, 100, frd) != NULL) {
    if(n >= length) break;
    sscanf(buffer, "%lf \n",&value[n].value);
    n++;
  }
  return n;
}

/*
bool isthebirddansleschoux (struct point * currentposition){
  latminbis=-16.0
  latmaxbis=55.1
  longminbis=-160.0
  longmaxbis=-112.7
  if(currentposition->latitude<latminbis || currentposition->latitude>latmaxbis || currentposition->longitude<longminbis || currentposition->longitude>longmaxbis){
    return true;
  }
  return false;
}
*/

int main() {

  //We initialize all the value the we have:
  //The norm of the speed (m/s)
  double initialSpeed= 10;

  //  caseMeteo
  struct caseMeteo* caseMeteo= malloc(96 * 720 * sizeof(struct caseMeteo));


  // The time of one fly (1H )but because we are in seconds 3600
  double flightDuration = 3600;

  //We create the table with all the datas of wind ( all days and all positions)
  // erreur avec sizeof!!!!!!
  //struct wind_table wind_table = malloc(96 * 720 * sizeof(struct wind_table));

  // We initalize the position with the data we extract with our function getdata2
  struct value listvalue [4];
  char * inputfile = "../Getdata/datatest.csv";
  readfile(inputfile,4,listvalue);


  struct point currentPosition= {listvalue[0].value, listvalue[1].value};
  struct point finalPosition= {listvalue[2].value, listvalue[3].value};


  //We initialize the actual speed in x and y as 0 and same thing for the wind
  struct speed currentSpeed ={0,0};
  struct speed actualCurrentSpeed = {0,0};
  struct speed currentWind={0,0};

  //radius of each square that composed our area of study
  double angleIncrement = 5.917;

  //meter of each square that composed our area of study
  double sideSquare= 657940;

  // The impactation factor of the wind
  double deviationImpactFactor = 0.5;

  // the factor from meter to degrees
  double meter2degFactor = angleIncrement/sideSquare;

  fillWindMap(caseMeteo);


  // We initialize our hour that will be our other condition of stop because we only have 720 datas of wind
  int hour=0;

  // CSV FILE
  //"w" because we want to write in it
  char * resultingFileName = "birdData.csv";
  FILE * file = fopen(resultingFileName, "w");

  //here we print in our csv file the position of the bird (latitude and longtiude) plus the speed along the x and y axis

  //(it is done for every hour )

  if (file == NULL) {

    printf("Could not open file. Try something else.\n");}

  fprintf (file, "%s,   ", "latitude");
  fprintf (file, "%s,   ", "longitude");
  fprintf (file,"%s,     ", "speedX");
  fprintf(file,"%s","speedY");
  fprintf(file,"\n");


  // Here we initialize with the first datas (we put the initial datas in the csv)
  fprintf(file,"%f,  ",currentPosition.latitude);
  fprintf(file,"%f,  ",currentPosition.longitude);
  fprintf(file,"%f,  ",actualCurrentSpeed.speedX);
  fprintf(file,"%f",actualCurrentSpeed.speedY);
  fprintf(file,"\n");

    // We fill tha table so as to have all the positions of wind every hour

    // While we have not reach our condition of stop we continue to create our csv file with the positoin of the bird
    // Until the bird is not arrival or we have 720 iterations we will use the function birdtrip

    while (hour<720 && birdArrivalBuffer(&currentPosition,&finalPosition,meter2degFactor)==false) {
      hour=hour+1;
      birdJourney(&currentSpeed,&finalPosition,&currentPosition,&currentWind, &actualCurrentSpeed , initialSpeed, deviationImpactFactor, flightDuration, meter2degFactor, angleIncrement, file, caseMeteo, hour);}
  printf("Bird has just finished to fly. To options : \n -bird has reached arrival ; \n -bird exceeds the number of wind data and might be still flying ! \n");
  free(caseMeteo);
  fclose(file);

//free(birdPosition);
return 0;

}

// The general idea is that the function bird trip reactualize the position of the bird and put his reactualized position in the csv file but it only does it for one iteration.

// So in the main we use a while loop and while the terminaison condition is not reach we will use bird trip so as to reactualize the position of the bird and fill the csv file.
