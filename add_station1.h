//this function check if line exist and exit if it does not exist
int does_line_exist (int Line_Number,LINE* Ptr_Search_Line,FILE* error)
{
     
         if (Ptr_Search_Line->Line_Number!=Line_Number)//not end of list 
                                                             //is the next line number
                                                             //equel the new number 
                                                             //line?
         {
         if (mtmPrintErrorMessage(error, MTM_LINE_DOESNT_EXIST)<0)
           exit(MTM_LINE_DOESNT_EXIST); //line exist error
           return 0;
         }
         return 1;
}

//this function create and put data in new link station
void bulid_station(LINE* Ptr_Search_Line, char* Station,int Time,FILE* error)
{
     TRACK* temp_to_create;
     if (Ptr_Search_Line->First_Station==NULL)//if its the first station we add
     {
        temp_to_create=(TRACK*) malloc(sizeof(TRACK));//create space for new link
        if (temp_to_create==NULL)//malloc faild?
        {
           free(temp_to_create);//delete TRACK
           if (mtmPrintErrorMessage(error, MTM_OUT_OF_MEMORY)<0)
           exit(MTM_OUT_OF_MEMORY);
        }
        temp_to_create->Next_Station=NULL;//next point ti NULL
        temp_to_create->Station_Name = (char*) malloc (sizeof(char)*MAX_LEN);
        if (temp_to_create->Station_Name==NULL)//malloc faild?
        {
           free(temp_to_create->Station_Name);//free string
           free(temp_to_create);//free TRACK
           if (mtmPrintErrorMessage(error, MTM_OUT_OF_MEMORY)<0)
           exit(MTM_OUT_OF_MEMORY);
        }
        strcpy(temp_to_create->Station_Name,Station);//put station name
        temp_to_create->Time_Of_Ride_From_First_Station=Time;//put time
        Ptr_Search_Line->Last_Station=temp_to_create;
        Ptr_Search_Line->First_Station=temp_to_create;//first station point to new link
        return;
     }
     
     
     temp_to_create=(TRACK*) malloc(sizeof(TRACK));//create space for new link
     if (temp_to_create==NULL)//malloc faild?
     {
       free(temp_to_create);//free TRACK
      if (mtmPrintErrorMessage(error, MTM_OUT_OF_MEMORY)<0)
       exit(MTM_OUT_OF_MEMORY);
     }  
     temp_to_create->Next_Station=NULL;//next point ti NULL
     temp_to_create->Station_Name = (char*) malloc (sizeof(char)*MAX_LEN);
     if (temp_to_create->Station_Name==NULL)//malloc faild?
        {
           free(temp_to_create->Station_Name);//free string
           free(temp_to_create);//free TRACK
           if (mtmPrintErrorMessage(error, MTM_OUT_OF_MEMORY)<0)
           exit(MTM_OUT_OF_MEMORY);
        }
     strcpy(temp_to_create->Station_Name,Station);//put station name
     temp_to_create->Time_Of_Ride_From_First_Station=Time;//put time
     Ptr_Search_Line->Last_Station->Next_Station=temp_to_create;
     Ptr_Search_Line->Last_Station=temp_to_create;//first station point to new link
     return;
     
}

//respy to add station
int Add_Station(VECHILE train_or_bus,int Line_Number,char* Station,int Time,LINE* anchor_test_line,FILE* error)
{
    LINE* Ptr_Search_Line;
    if (check_line_number(Line_Number,error) == 0) {return 1;}//check line number
    Ptr_Search_Line=walk_over_LINE_list(Line_Number, anchor_test_line);//search in line list the link(we get the prev link)
      if (Ptr_Search_Line->Next!=NULL)          //last link?
       {
          Ptr_Search_Line=Ptr_Search_Line->Next;//not last linnext link move to
       }   
    does_line_exist(Line_Number,Ptr_Search_Line,error);//check line exist
    if (Ptr_Search_Line->Last_Station != NULL) {
     if (check_time(Time,Ptr_Search_Line->Last_Station->Time_Of_Ride_From_First_Station,error)) {
       bulid_station( Ptr_Search_Line,  Station, Time,error);//create station link //check time
       }   
    }
    else {
    bulid_station( Ptr_Search_Line,  Station, Time,error);//create station link
    }
    return 1;
}

