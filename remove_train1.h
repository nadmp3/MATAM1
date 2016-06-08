//this function search train list for link to delete
TRAIN_Details* search_trains(TRAIN_Details* Train_anchor,int Line_Number,FILE* error)
{
    TRAIN_Details* Ptr_Search_train;
    Ptr_Search_train=Train_anchor;
    while (Ptr_Search_train->Next!=NULL &&           //search linked list as long 
    Ptr_Search_train->Next->Line_Number!=Line_Number)//not end of list or line 
                                                    //number is found 
    {
          Ptr_Search_train=Ptr_Search_train->Next;//move to next link
    }      

    if (Ptr_Search_train->Next==NULL)//end of list?
    {                           
        if (mtmPrintErrorMessage(error, MTM_LINE_DOESNT_EXIST)<0)
        exit(MTM_LINE_DOESNT_EXIST);//error line does not exist
    }
    return Ptr_Search_train;//return pointer to link train before the one to delete
}

//this function delete link train
void delete_link_train (TRAIN_Details* Ptr_Search_Train)
{
    TRAIN_Details* TEMP_TO_DELETE=Ptr_Search_Train->Next;//point to link to delete
    Ptr_Search_Train->Next=Ptr_Search_Train->Next->Next;//link prev link to next link
                                                      //link list without link to delete
    free(TEMP_TO_DELETE);//delete link to delete   
}

//this is the "respy" to remove train
int remove_train(VECHILE Bus_Or_Train, int Line_Number,TRAIN_Details* Train_anchor,FILE* error)
{    
    TRAIN_Details* Ptr_Search_Line;//help variable to search and delete 
    if (check_line_number(Line_Number,error) == 0) {return 1;}//check line number  
    
    Ptr_Search_Line=search_trains(Train_anchor,Line_Number,error);     
    delete_link_train (Ptr_Search_Line);
    return 1;
}

