#include <unistd.h>
#include <stdio.h>
#include <math.h>
#include <inttypes.h>
#include <stdlib.h>
#include <time.h>
#include <json-c/json.h>
#include <string.h>
#include "migrations.h"

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

int main(int argc, char const *argv[]) {

    struct caseMeteo * caseMeteo = malloc(96 * 720 * sizeof(struct caseMeteo));
    fillWindMap(caseMeteo);
}