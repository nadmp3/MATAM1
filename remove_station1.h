//this function delete the station from list
void delete_station (LINE* Ptr_Search_Line,char* station_number,FILE* error)
{
    TRACK* Ptr_Search_track,*temp_to_delete;
    Ptr_Search_track=Ptr_Search_Line->First_Station;
    
    if    ((strcmp(station_number,"END")==0))//if user asked to delete last station
          {
           if (Ptr_Search_track==NULL)//there are no station in list?
          {
                if (mtmPrintErrorMessage(error, MTM_INVALID_STATION_INDEX)<0)
                exit(1);//erroe no station to delete   
                return;                        
          }
            while (Ptr_Search_track->Next_Station->Next_Station!=NULL)//go to last link point to it
          {
                  Ptr_Search_track=Ptr_Search_track->Next_Station;//go to next link
          }
            free(Ptr_Search_track->Next_Station->Station_Name);
            free(Ptr_Search_track->Next_Station);//delete last link
            Ptr_Search_track->Next_Station=NULL;//the "new" last link point to NULL
            Ptr_Search_Line->Last_Station=Ptr_Search_track;
            return ;
    }
    
    int station_index=atoi(station_number);//translate string to int and save
    if (station_index==0)//if user aked to delete the first station
    {
       if (Ptr_Search_Line->First_Station==NULL)//check if list is empty
           {
               if (mtmPrintErrorMessage(error, MTM_INVALID_STATION_INDEX)<0)
               exit(1); //error    
               return;                       
           }
         temp_to_delete=Ptr_Search_Line->First_Station;//point to link we want to delete
         Ptr_Search_Line->First_Station=Ptr_Search_Line->First_Station->Next_Station;//linl list without that link
         free(temp_to_delete->Station_Name);
         free(temp_to_delete);//delete link
         return ;
       
    }
        while (Ptr_Search_track->Next_Station->Next_Station!=NULL && station_index>1)//search list as long its not the end of list 
                                                                       //and we didnt passes station to delete stop one station before
        {
              station_index--;//dec station counter
              Ptr_Search_track=Ptr_Search_track->Next_Station;//move to next link
        }
        if (Ptr_Search_track->Next_Station==NULL && station_index!=1)//check if we found asked station
        {
            if (mtmPrintErrorMessage(error, MTM_INVALID_STATION_INDEX)<0)
            exit(MTM_INVALID_STATION_INDEX);//asked station doesnt exist error
            return;
        }
        if (Ptr_Search_track->Next_Station->Next_Station==NULL)//is the last link we want to delete
        {
            free(Ptr_Search_track->Next_Station->Station_Name);
            free(Ptr_Search_track->Next_Station);//delete last link
            Ptr_Search_track->Next_Station=NULL;//"new" last link point to NULL
            Ptr_Search_Line->Last_Station=Ptr_Search_track;
            return ;
        }
        //found the link itsnt start link or end link
        temp_to_delete=Ptr_Search_track->Next_Station;//point to link to delete
        Ptr_Search_track->Next_Station=Ptr_Search_track->Next_Station->Next_Station;//link list without that link
        free(temp_to_delete->Station_Name);
        free(temp_to_delete);  //delete link
        return ;  
}
//function remove link "respy"
int remove_station(VECHILE train_or_bus,int Line_Number,char* station_number,LINE* anchor_test_line,FILE* error)
{
    LINE* Ptr_Search_Line;//
    
    if (check_line_number(Line_Number,error) == 0) {return 1;}//check line number
    Ptr_Search_Line = walk_over_LINE_list(Line_Number, anchor_test_line);//search line list by line number

      if (Ptr_Search_Line->Next!=NULL)          //end of list?
       {
          Ptr_Search_Line=Ptr_Search_Line->Next;//move to next link
       }
    if (does_line_exist(Line_Number,Ptr_Search_Line,error)==1)//check if line exist
    	{delete_station(Ptr_Search_Line, station_number,error);//delete station link
    	}
    return 1;
}
