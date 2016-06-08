

//this function search LINE list
LINE* walk_over_LINE_list(int Line_Number,LINE* anchor_test_line)
{
       LINE* Ptr_Search_Line = anchor_test_line;
       while ((Ptr_Search_Line->Next!=NULL) &&  (Ptr_Search_Line->Next->Line_Number < Line_Number))
                                                 //check if its the last link
                                                 //or we passed the desired
                                                 // postion
       {
             Ptr_Search_Line=Ptr_Search_Line->Next;//move to next link
       }
      return Ptr_Search_Line;//return pointer to link before 
}


//this function take as to add tarin or train bus
void go_to_bus_or_train(VECHILE Vechile_Type_of_New_Line,char* String_Data,double Price,LINE* Ptr_Line,int Line_Number,TRAIN_Details* Train_anchor,BUSES_Details* Bus_anchor,FILE* error)
{
     if ( Vechile_Type_of_New_Line==TRAIN )//if we need to add a
                                           //Train go to function
     {
         add_train(Ptr_Line, Price,Line_Number, String_Data,Train_anchor,error);//go to add tarin
     }
     else
     {
         add_bus(Ptr_Line, Price,Line_Number,String_Data,Bus_anchor,error);//go to add bus
     }
                       
}

//this function create space for new link LINE
LINE* create_line(FILE* error)
{
      LINE* TEMP_TO_CREATE;
      TEMP_TO_CREATE = (LINE*) malloc(sizeof(LINE));//create space 
                                                    //for new link 
                                                    //of line
      if (TEMP_TO_CREATE==NULL)                       //did create space fallid?
      {
      free(TEMP_TO_CREATE);
      if (mtmPrintErrorMessage(error, MTM_OUT_OF_MEMORY)<0)
         exit(MTM_OUT_OF_MEMORY);   // space create faild error
      }   
      return TEMP_TO_CREATE;  //return pointer to new link 
}

//this function put data in new link LINE
void put_data_in_link_LINE (LINE* TEMP_TO_CREATE,LINE* Ptr_Search_Line,int Line_Number,VECHILE Vechile_Type_of_New_Line)
{
     TEMP_TO_CREATE->First_Station=NULL;      //First_Station=NULL
     TEMP_TO_CREATE->Last_Station=NULL;       //Last_Station=NULL
     TEMP_TO_CREATE->Line_Number=Line_Number; //put line number         
     TEMP_TO_CREATE->Train_or_bus=Vechile_Type_of_New_Line;
                                                              //save train or bus
     TEMP_TO_CREATE->Next=Ptr_Search_Line->Next;//point to next
     Ptr_Search_Line->Next=TEMP_TO_CREATE;                    //linked to the
                                                              //link before  
              
}


//this is the "respy" for add line
int Add_Line(char* Line_type, int Line_Number, char* String_Data, double Price,TRAIN_Details* Train_anchor,BUSES_Details* Bus_anchor,LINE* anchor_test_line,FILE* error)
{
    LINE* Ptr_Search_Line, *TEMP_TO_CREATE;
    VECHILE Vechile_Type_of_New_Line;          //save train or bus  
        
    Vechile_Type_of_New_Line=check_train_or_bus(Line_type,error);//get train or bus
    if (check_line_number(Line_Number,error) == 0) {return 1;}//check line number
    check_the_price_is_right(Price,error);//check price
    Ptr_Search_Line=walk_over_LINE_list(Line_Number,anchor_test_line);//search LINE list
    if (check_if_line_exist(Ptr_Search_Line, Line_Number,error)==1)//check ilne exist
   { TEMP_TO_CREATE=create_line(error);//make space for new link
    go_to_bus_or_train(Vechile_Type_of_New_Line,String_Data,Price,TEMP_TO_CREATE,Line_Number,Train_anchor,Bus_anchor,error);//go to add train or bus
    put_data_in_link_LINE (TEMP_TO_CREATE,Ptr_Search_Line,Line_Number,Vechile_Type_of_New_Line);//put data in new link
    }
    return 1; //ok!!!

}

