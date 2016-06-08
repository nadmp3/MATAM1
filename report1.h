#include "mtm_ex1.h"
#include <stdlib.h>
void print_train (TRAIN_Details* train, FILE* output, FILE* error) {
// the functionprint the train info details
   if (train->ptr_Line->First_Station != NULL) { //if there arent stations
    if (!mtmPrintTrainLine(output,train->Line_Number,train->Type,train->ptr_Line->First_Station->Station_Name,
    train->ptr_Line->Last_Station->Station_Name,train->price)) { //print all
                                                               if (mtmPrintErrorMessage(error,MTM_INVALID_PARAMETERS) < 0)
                                                            {exit(1);}
    }
   }
   else {if (!mtmPrintTrainLine(output,train->Line_Number,train->Type,NULL,NULL,train->price)) { //print stations null
                                                               if (mtmPrintErrorMessage(error,MTM_INVALID_PARAMETERS) < 0)
                                                            {exit(1);}
    }
   }
}
void print_bus (BUSES_Details* bus, FILE* output, FILE* error) {
// the function print the bus info details
     if (bus->ptr_Line->First_Station != NULL) { // if there are stations
      if (!mtmPrintBusLine(output,bus->Line_Number,bus->Company,bus->ptr_Line->First_Station->Station_Name,
      bus->ptr_Line->Last_Station->Station_Name,bus->price)) { //print all
                                                            if (mtmPrintErrorMessage(error,MTM_INVALID_PARAMETERS) < 0)
                                                            {exit(1);}
      }
     }
     else {if (!mtmPrintBusLine(output,bus->Line_Number,bus->Company,NULL,
           NULL,bus->price)) { //if therent stations put null
                                                            if (mtmPrintErrorMessage(error,MTM_INVALID_PARAMETERS) < 0)
                                                            {exit(1);}
           }
      }
     
}
void print_stations (TRACK* first, FILE* output, FILE* error) {
// the function print the stations of the track it got
     TRACK* track_ptr = first; //get the first station
     while (track_ptr != NULL) { //until the end of track
           if (!mtmPrintStation(output, track_ptr->Station_Name, track_ptr->Time_Of_Ride_From_First_Station)) {//print
                                       if (mtmPrintErrorMessage(error,MTM_INVALID_PARAMETERS) < 0)
                                                            {exit(1);}
           }
           track_ptr = track_ptr->Next_Station;  //next station
     }
}
int search_line_num (LINE* line, int num, char* line_type, FILE* output, FILE* error) {
//the function search for the currect line and print the line info and stations
    int i = 0;
    LINE* line_ptr = line->Next; //move to the first
    while ((line_ptr != NULL) && (i == 0)) { //until we find the line number
          if (line_ptr->Line_Number == num) { //if we got to the line number
             
             if (line_ptr->Train_or_bus == check_train_or_bus (line_type,error)) { //if its match the line_type
                                      if (line_ptr->Train_or_bus == TRAIN) { //if its train
                                                                   TRAIN_Details* train_ptr = line_ptr->Details; //get details
                                                                   print_train(train_ptr,output,error); //print train
                                                                   print_stations(line_ptr->First_Station,output,error); //print stations
                                                                   i = 1; //we got!
                                      }
                                      if (line_ptr->Train_or_bus == BUS) { // if its bus
                                                                   BUSES_Details* bus_ptr = line_ptr->Details; //get details
                                                                   print_bus(bus_ptr,output,error); //print bus
                                                                   print_stations(line_ptr->First_Station,output,error); //print
                                                                   i = 1;
                                      }
             }
          }
          line_ptr = line_ptr->Next; //next line
    }
    return i;
}
void report_stations (LINE* line, int number, char* line_type, FILE* output, FILE* error) {
	// the function for the report stations command. get the line_number and type and print the line info
	// and stations report with time of arrive
     if (check_line_number (number,error)) {// check the line number
        if (search_line_num(line,number,line_type,output,error) == 0) { //search for the line and print stations
           if (mtmPrintErrorMessage(error,MTM_LINE_DOESNT_EXIST) < 0) {/*exit(1);*/}
        }
     }
}
int search_ride (LINE* line, char* from_dest, char* to_dest) {
//search for the ride. if its find it return 1
     int i = 0;
     TRACK* ride_track = line->First_Station;// go to the first station in the line
     while (((ride_track) != NULL) && (i != 2)) {// check if we got to the end of the line or we found the ride i=2
           if (i == 1) {      // if we already passed the from_dest station 
                if (strcmp(ride_track->Station_Name,to_dest) == 0) {i = 2;}//if we got to the detanation i=2 we found ride!
           }// next time check to to_dest station
           if (i == 0) {// we didn't find yet the from_dest dtation
              if (strcmp(ride_track->Station_Name,from_dest) == 0) {i = 1;}// if we found the from_dest i =1
           }
           ride_track = ride_track->Next_Station;// next station in track line
     }
     if (i == 0) return 0;
     if (i == 1) return 0;
     if (i == 2) return 1;
     else return 0;
}
void report_rides_train (char* from_dest, char* to_dest, double max_p, TRAIN_Details* Train, FILE* output, FILE* error) {
// search rides in the trains lines
     TRAIN_Details* tr_ptr = Train->Next; //fo the first train in the chain
      while (tr_ptr != NULL) {// if its not the end of the chain = NULL
           if ((search_ride(tr_ptr->ptr_Line,from_dest,to_dest)) && ((tr_ptr->price) <= max_p)) {
           // check if contain the needed ride and the price is ok
            if (tr_ptr->ptr_Line->First_Station != NULL) {// just in case the stations exist
              if (!mtmPrintTrainLine(output,tr_ptr->Line_Number,tr_ptr->Type,tr_ptr->ptr_Line->First_Station->Station_Name,
              tr_ptr->ptr_Line->Last_Station->Station_Name,tr_ptr->price)) {
                                                               if (mtmPrintErrorMessage(error,MTM_INVALID_PARAMETERS) < 0)
                                                            {exit(1);}
              }
            }
            else {if (!mtmPrintTrainLine(output,tr_ptr->Line_Number,tr_ptr->Type,NULL,
              NULL,tr_ptr->price)) {// if station don't exit (someone search for NULL stations
                                                               if (mtmPrintErrorMessage(error,MTM_INVALID_PARAMETERS) < 0)
                                                            {exit(1);}
              }
            }
           }
           tr_ptr = tr_ptr->Next;// next train line
     }
}
void report_rides_bus (char* from_dest, char* to_dest, double max_p, BUSES_Details* Bus, FILE* output, FILE* error) {
// search rides in the buses lines
     BUSES_Details* bus_ptr = Bus->Next;// go to the first bus in the chain
             while (bus_ptr != NULL) {// loop until we get to the end of the chain = NULL
                                        if (search_ride((*bus_ptr).ptr_Line,from_dest,to_dest) && ((*bus_ptr).price <= max_p)) {
                                        // check if contain ride (the bus line) and the price is ok
                                         if (bus_ptr->ptr_Line->First_Station != NULL) {// check just in case that the stations exist and print
                                          if (!mtmPrintBusLine(output,bus_ptr->Line_Number,bus_ptr->Company,
                                          bus_ptr->ptr_Line->First_Station->Station_Name,bus_ptr->ptr_Line->Last_Station->Station_Name,bus_ptr->price)) {
                                                            if (mtmPrintErrorMessage(error,MTM_INVALID_PARAMETERS) < 0)
                                                            {exit(1);}
                                          }
                                         }
                                        }
                 bus_ptr = bus_ptr->Next;//next bus line in chain
             }
}
void report_rides (char* from_dest, char* to_dest, double max_price, BUSES_Details* Bus, TRAIN_Details* Train, FILE* output, FILE* error) {
//the function for report rides command. search for rides which stand in the condition which get by the user,
	// if its pass through the from station and go to the to-station and cost less the the max price
     report_rides_train(from_dest,to_dest,max_price,Train,output,error);//check train rides
     report_rides_bus(from_dest,to_dest,max_price,Bus,output,error);// check bus rides
}
void report_lines_train (TRAIN_Details* Train, FILE* output, FILE* error) {
     TRAIN_Details* tr_ptr = Train->Next; //move to the first bus in the list   
      while (tr_ptr != NULL) {// if its point to null its empty and we got to the end of the train list
       if (tr_ptr->ptr_Line->First_Station != NULL) {//if stations were added to the train line then print all
           if (!mtmPrintTrainLine(output,tr_ptr->Line_Number,tr_ptr->Type,tr_ptr->ptr_Line->First_Station->Station_Name,
           tr_ptr->ptr_Line->Last_Station->Station_Name,tr_ptr->price)) {
                                                               if (mtmPrintErrorMessage(error,MTM_INVALID_PARAMETERS) < 0)
                                                            {exit(1);}
           }
       }
       else {if (!mtmPrintTrainLine(output,tr_ptr->Line_Number,tr_ptr->Type,NULL,
           NULL,tr_ptr->price)) {//if stations werent added then NULL in the station's names
                                                               if (mtmPrintErrorMessage(error,MTM_INVALID_PARAMETERS) < 0)
                                                            {exit(1);}
           }
        }
       tr_ptr = tr_ptr->Next;// moving to next train
      }
}
void report_lines_bus (BUSES_Details* Bus, FILE* output, FILE* error) {
// dealing with the report lines for busses
     BUSES_Details* bus_ptr = Bus->Next;// moving to the first bus which is after the anchor
     while (bus_ptr != NULL) {//while we are not in the end of the chain (NULL) do the loop
             if (bus_ptr->ptr_Line->First_Station != NULL) {//if stations were added to the bus line then print all
                if (!mtmPrintBusLine(output,bus_ptr->Line_Number,bus_ptr->Company,bus_ptr->ptr_Line->First_Station->Station_Name,
                bus_ptr->ptr_Line->Last_Station->Station_Name,bus_ptr->price)) {
                                                            if (mtmPrintErrorMessage(error,MTM_INVALID_PARAMETERS) < 0)
                                                            {exit(1);}
                }
             }
             else {if (!mtmPrintBusLine(output,bus_ptr->Line_Number,bus_ptr->Company,NULL,
                NULL,bus_ptr->price)) {//if stations werent added then NULL in the station's names
                                                            if (mtmPrintErrorMessage(error,MTM_INVALID_PARAMETERS) < 0)
                                                            {exit(1);}
                }
             }
             bus_ptr = bus_ptr->Next;// moving to next bus
     }
           
}
void report_lines (int line_type, BUSES_Details* Bus, TRAIN_Details* Train, FILE* output, FILE* error) {
        // dealing with the report line command
        if (line_type == BUS) {// if line_type is bus sendiong to the bus dealing function
                  report_lines_bus(Bus,output,error);
          }
          else {
               if (line_type == TRAIN) {// if its train sending to the train dealing function
                      report_lines_train(Train,output,error);
               }
               else {// if its other - meaning nothing - do both the report lines for buses and for trains
                   report_lines_train(Train,output,error);
                  report_lines_bus(Bus,output,error);
               }
          }
     
     
}
