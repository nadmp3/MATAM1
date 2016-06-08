#ifndef MTM_HEAD_
#define MTM_HEAD_
////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <string.h>
#define LINES_MAX 9999
#define succses 999
//this enum is for to tell if it is a train (=0) or bus (=1) 
typedef enum {
	TRAIN,
	BUS
} VECHILE;

//this struct is to keep station for line in there correct order
//station name, time, next_station
// linked list for etch line 
typedef struct TRACK_T{
        char* Station_Name;                   //save station name
        int Time_Of_Ride_From_First_Station; //keep time it take
                                              // from first station
        struct TRACK_T* Next_Station;         //point to the next station  
        } TRACK;
         
//this struct save all exist line (bus and train)
//by number order 
//all so it hold a pointer to Vechile Details 
//linked list
typedef struct LINE_T{
        int Line_Number;                          //line number
        VECHILE Train_or_bus;                     //is it train or bus
        void* Details;                            //point to a struct holding
                                                  // line Details
        TRACK* First_Station;            //(point to TRACK_T struct)
                                                  // the first
                                                  //station for the line 
                                                  //(if the are no station
                                                  //value is null)
        TRACK* Last_Station;             //(point to TRACK_T struct)
                                                  // the last
                                                  //station for the line
                                                  // (if the are no station
                                                  //value is null)
        struct LINE_T* Next;                      //pointer to next line (linke) 
        } LINE;

//this struct save all exist train
//by TrainType order then by line number order
//keeps the TrainType, line number, price ,pointer to first station and pointer
// to last station
//keeps pointer to corect link in LINE (list)
// link list
typedef struct TRAIN_T{
        TrainType Type;             //what kind of train TRAIN_DIRECT,
                                    // TRAIN_INTERCITY, TRAIN_SUBURBAN
        int Line_Number;            //line number
        double price;               //ticket price
        LINE* ptr_Line;      //pointer to corect link in LINE
        struct TRAIN_T* Next;       //pointer to next Train_details (link) 
        } TRAIN_Details;
        
        
//this struct save all exist buses
//by company name then by line number
//keeps company name, line number, price, pointer to next bus
//keeps pointer to corect link in LINE (list)
//linked list
typedef struct BUSES_T{
        char* Company;         //company name
        int Line_Number;       //line number
        double price;          //ticket price
        LINE* ptr_Line; //pointer to corect link in LINE
        struct BUSES_T* Next;  //pointer to next BUSES_Details (link) 
        } BUSES_Details;

#endif
