#include "mtm_ex1.h"
//this function check and retturn if is trarin or bus
int check_train_or_bus(char* Line_type,FILE* error)
{

    if (strcmp (Line_type,"train")==0)         //is it train?
       {
               return TRAIN; //it a train!
       }
    else if (strcmp (Line_type,"bus")==0)      //is a bus?
       {

               return BUS;   //its a bus
       }      
    else
       {
            return -1;
            //if (mtmPrintErrorMessage(error,MTM_INVALID_LINE_TYPE) < 0)
              //exit(1); //not bus nor train a.k.a error
       }
}


//this function check if line number is valid
int check_line_number(int Line_Number,FILE* error)
{
     
    if ((Line_Number < 1) || (Line_Number > LINES_MAX)) //is line number make sense ?                                               //LINE_MAX>=x>=1
    {
       if (mtmPrintErrorMessage(error, MTM_INVALID_LINE_NUMBER) < 0) {
              exit(1);  // doesnt make sense error
       }
       return 0;
    }
    return 1;  
}

//this function 
void check_the_price_is_right(double Price,FILE* error)
{    
     if (Price<0)                                //is price under zero?
      {
                if (mtmPrintErrorMessage(error, MTM_INVALID_PRICE)<0) {
                exit(MTM_INVALID_PRICE);       //the price is to low error
                }
      }
}

//this function check if time is OK
int check_time (int Time,int last_station_time,FILE* error)
{
     if ((Time < 0) || (last_station_time > Time)) {  // if time is negative
        if (mtmPrintErrorMessage(error, MTM_INVALID_TIME)<0) {
        exit(MTM_INVALID_TIME);//error bad time
        }
        return 0;
     }
     return 1;
}
