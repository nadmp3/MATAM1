#include "mtm_ex1.h"
void delete_and_exit (TRAIN_Details* train, BUSES_Details* bus, LINE* line, FILE* error)
{
     BUSES_Details* bus_ptr = bus;
     BUSES_Details* bus_tmp = NULL;
     TRAIN_Details* tr_ptr = train;
     TRAIN_Details* tr_tmp = NULL;
     LINE* line_ptr = line;
     LINE* line_tmp = NULL;
     TRACK* track_ptr = NULL;
     TRACK* track_tmp = NULL;
     while (bus_ptr != NULL) {
     	bus_tmp = bus_ptr;
     	bus_ptr = bus_ptr->Next;
     	free (bus_tmp->Company);
     	free(bus_tmp);
     }
     while (tr_ptr != NULL) {
     	tr_tmp = tr_ptr;
     	tr_ptr = tr_ptr->Next;
     	free(tr_tmp);
     }
     while (line_ptr != NULL) {
     	if (line_ptr->First_Station != NULL) {
     		track_ptr = line_ptr->First_Station;
     		while (track_ptr != NULL) {
     			track_tmp = track_ptr;
     			track_ptr = track_ptr->Next_Station;
     			free(track_tmp->Station_Name);
     			free(track_tmp);
     		}
     	}
     	line_tmp = line_ptr;
     	line_ptr = line_ptr->Next;
     	free(line_tmp);
     }
}
