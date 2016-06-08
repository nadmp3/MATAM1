#include <stdio.h>

//this function search bus list by lne number
BUSES_Details* search_buses(BUSES_Details* Bus_anchor,int Line_Number,FILE* error)
{
    //search the list for requsted link
    BUSES_Details* Ptr_Search_Bus;    
    Ptr_Search_Bus=Bus_anchor;   //point to anchor 
    while (Ptr_Search_Bus->Next!=NULL &&           //search the list as long as
    Ptr_Search_Bus->Next->Line_Number!=Line_Number)//not end of list or find link
          {

                       Ptr_Search_Bus=Ptr_Search_Bus->Next;//move to next link
          }      
    
    if (Ptr_Search_Bus->Next==NULL)//end of list?
    {                           
         if (mtmPrintErrorMessage(error, MTM_LINE_DOESNT_EXIST)<0)
         exit(MTM_LINE_DOESNT_EXIST);//error line does not exist
    }
    return Ptr_Search_Bus;
}

//this function delete link bus from bus list
void delete_link_bus (BUSES_Details* Ptr_Search_Line)
{
    BUSES_Details* TEMP_TO_DELETE=Ptr_Search_Line->Next;//point to link to delete
    Ptr_Search_Line->Next=Ptr_Search_Line->Next->Next;//link the prev link to the link after                                             //when the link to delete is not conccted in the list  
    free(TEMP_TO_DELETE->Company);
    free(TEMP_TO_DELETE);//free space delete link
}
//this is the "respy" for remove bus
int remove_bus(VECHILE Bus_Or_Train, int Line_Number,BUSES_Details* Bus_anchor,FILE* error)
{    
    BUSES_Details* Ptr_Search_Bus; //help variable to search and delete
    if (check_line_number(Line_Number,error) == 0) {return 1;}//check line number
    Ptr_Search_Bus=search_buses(Bus_anchor,Line_Number,error);//found bus link  
    delete_link_bus (Ptr_Search_Bus);//delete bus link
    return succses;
}
