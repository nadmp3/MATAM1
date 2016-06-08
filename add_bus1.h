
//this function search bus list by company name and by line number
BUSES_Details* walk_over_BUS_list(int Line_Number,BUSES_Details* Bus_anchor,char* Company)
{
     BUSES_Details* Ptr_Temp_Search;
     Ptr_Temp_Search=Bus_anchor;
     while ((Ptr_Temp_Search->Next!=NULL) && 
           (strcmp(Ptr_Temp_Search->Next->Company,Company)<0) &&
           (Ptr_Temp_Search->Next->Line_Number!=Line_Number))
                                                 //check if its the last link
                                                 //or we passed the desired
                                                 // postion by type
     {
     Ptr_Temp_Search=Ptr_Temp_Search->Next; //move to next link
     }

    while ((Ptr_Temp_Search->Next!=NULL) && 
          ((strcmp(Ptr_Temp_Search->Next->Company,Company)==0) &&
          (Ptr_Temp_Search->Next->Line_Number<Line_Number)))
                                                 //check if its the last link
                                                 //or we passed the desired
                                                 // postion by number number 
                                                 //(with the same type as the
                                                 //new like)
    {
            Ptr_Temp_Search=Ptr_Temp_Search->Next;//move to next link
    }
      return Ptr_Temp_Search;  //return pointer to link before
}


//this function create space for new bus link
BUSES_Details* create_bus(FILE* error,LINE* Ptr_Line)
{
      BUSES_Details* TEMP_TO_CREATE;
      TEMP_TO_CREATE = (BUSES_Details*) malloc(sizeof(BUSES_Details));//create space 
                                                                 //for new link 
                                                                 //of line
      if (TEMP_TO_CREATE==NULL)                       //did create space fallid?
      {
         free(TEMP_TO_CREATE);//delete bus
         free(Ptr_Line);//delete line
         if (mtmPrintErrorMessage(error, MTM_OUT_OF_MEMORY)<0) 
         exit(MTM_OUT_OF_MEMORY);   // space create faild error
      }   
      return TEMP_TO_CREATE;   //return pointer to new link
}

//this function put data in new link bus
void put_data_in_link_bus (BUSES_Details* TEMP_TO_CREATE,BUSES_Details* Ptr_Temp_Search,int Line_Number,double Price,LINE* Ptr_Line,char* Company,FILE* error)
{
    TEMP_TO_CREATE->Company = (char*) malloc (sizeof(char)*MAX_LEN);
    if (TEMP_TO_CREATE->Company==NULL)                       //did create space fallid?
      {
         free(TEMP_TO_CREATE->Company);//delete string
         free(TEMP_TO_CREATE);//delete bus
         free(Ptr_Line);//delete line
         if (mtmPrintErrorMessage(error, MTM_OUT_OF_MEMORY)<0) 
         exit(MTM_OUT_OF_MEMORY);   // space create faild error
      }   
    TEMP_TO_CREATE->Line_Number=Line_Number;//put line number
    TEMP_TO_CREATE->Next=Ptr_Temp_Search->Next;//link the the next link 
    TEMP_TO_CREATE->price=Price;//put price
    TEMP_TO_CREATE->ptr_Line=Ptr_Line;//link train link to the line link
    strcpy(TEMP_TO_CREATE->Company,Company);
    Ptr_Line->Details=TEMP_TO_CREATE;//link line to train link
    Ptr_Temp_Search->Next=TEMP_TO_CREATE;//link the previos link to new link
                                                     //linked to link before  
              
}

//this is the "respy" for add bus
int add_bus(LINE* Ptr_Line, double Price,int Line_Number,char* Company,BUSES_Details* Bus_anchor,FILE* error)
{   

    BUSES_Details *Ptr_Temp_Search;//this variable is a tepmure variable
                                   //to search in the linked list trains 
    Ptr_Temp_Search = Bus_anchor;//start in the first link
    BUSES_Details *TEMP_TO_CREATE;//this variable is a tepmure variable
                                   //help to create a new link

    check_the_price_is_right(Price,error);//check price
    if (check_line_number(Line_Number,error) == 0) {return 1;}//check line number
    Ptr_Temp_Search=walk_over_BUS_list(Line_Number,Bus_anchor,Company);//search bus list
    TEMP_TO_CREATE=create_bus(error,Ptr_Line);//create space for new link
    put_data_in_link_bus(TEMP_TO_CREATE, Ptr_Temp_Search,Line_Number,Price,Ptr_Line,Company,error);//put data in new link
    return 1;
     
    
}

