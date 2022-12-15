#ifndef LESFONCTIONS
#define LESFONCTIONS

//STRUCTURES
struct caseMeteo{
  double windspeed;
  double winddirection;};

// structure of point in the planisphere (degrees)
struct point {
  double latitude;
  double longitude;
};

// structure of speed component (cartesian frame)
struct speed {
  double vitessex;
  double vitessey;
};

//The other structure structure of the wind
struct wind {
double wind_speed;
double wind_angle;
};

//FONCTIONS migrations
double convertdegreesintorad(double angle_deg);
double convertcompassintorad(double angleincompass);
double direction( struct point * currentposition, struct point * finalposition, double facteurmetreendegre);
void speedbird(double alphaangle, double speedbird, struct speed * currentbirdspeed );
void speedwind(double speedwind, struct speed * currentwindspedd,double windirection);
void realbirdspeed(struct speed * currentwindspeedwind, struct speed * currentspeedbird, struct speed * realbirdspeed, double facteurimpactation );
void distanceparcourue(struct speed * realbirdspeed, double tempsparcours, double facteurdemetreendegre, struct point * currentposition);
bool isthebirdarrival(struct point * currentposition, struct point * finalposition,double facteurmetreeendegre);
void bird_trip(struct speed * vitesseactuelle,struct point * positionfinale,struct point * positionactuelle, struct wind * ventactuelle, struct speed * vraivitessebird,
  double initialspeed,double facteurimpactation, double tempsvol, double facteurmetredegre, double angle_increment, FILE * file ,struct caseMeteo * caseMeteo, int count);

//FONCTIONS mapcreation
void fillWindMap(struct caseMeteo * caseMeteo);

#endif
