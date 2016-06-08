//this function search the line list
LINE* search_line(LINE* anchor_test_line,int Line_Number,FILE* error)
{
    LINE* Ptr_Search_Line;
    Ptr_Search_Line=anchor_test_line;               //point to first link
    while (Ptr_Search_Line->Next!=NULL &&           //search linked list as long 
    Ptr_Search_Line->Next->Line_Number!=Line_Number)//not end of list or line 
                                                    //number is found 
          {
           Ptr_Search_Line=Ptr_Search_Line->Next;//move to next link
          }      
    if (Ptr_Search_Line->Next==NULL)//end of list?
    {                           
        if (mtmPrintErrorMessage(error, MTM_LINE_DOESNT_EXIST)<0)
        exit(MTM_LINE_DOESNT_EXIST);//error line does not exist
    }
    return Ptr_Search_Line;
}
//this function delete all station from line being delete
void remove_all_station(LINE* Ptr_Search_Line)
{
    TRACK *Ptr_track_delete,*Ptr_keep;
    Ptr_keep=Ptr_Search_Line->Next->First_Station;//point the first station
    while (Ptr_keep!=NULL)//while its not end of list
    {
          Ptr_track_delete=Ptr_keep;//point link to delete
          Ptr_keep=Ptr_keep->Next_Station;//move to next link
          free(Ptr_track_delete->Station_Name);
          free(Ptr_track_delete);     //delete link 
    }     
     
}
//this function delete line link
void delete_line_link(LINE* Ptr_Search_Line)
{
     LINE* TEMP_TO_DELETE;
     TEMP_TO_DELETE=Ptr_Search_Line->Next;//point to link to delete
     Ptr_Search_Line->Next=Ptr_Search_Line->Next->Next;//link prev link to next link
                                                       //link list without link to delete   
     free(TEMP_TO_DELETE);//delete link to delete
   
}

//this is the "respy" for remove line
int remove_line(VECHILE Bus_Or_Train, int Line_Number,TRAIN_Details* Train_anchor,BUSES_Details* Bus_anchor,LINE* anchor_test_line,FILE* error)
{
    LINE* Ptr_Search_Line;//help variable to search and delete 
    if (check_line_number(Line_Number,error) == 0) {return 1;}//check line number
    Ptr_Search_Line=search_line(anchor_test_line,Line_Number,error);//found line link  
    if (Bus_Or_Train==1)//is it bus or train
    {
        remove_bus( BUS, Line_Number,Bus_anchor,error) ;   //go to remove bus
    }
    else
    {
        remove_train(TRAIN ,  Line_Number,Train_anchor,error);//go to remove train
    }
    remove_all_station(Ptr_Search_Line);//remove all station from line
    delete_line_link(Ptr_Search_Line);//delete link
    return 1;
}

