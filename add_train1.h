

//this function search train list by type then by line number
TRAIN_Details* walk_over_TRAIN_list(int Line_Number,TRAIN_Details* Train_anchor,TrainType type)
{
             TRAIN_Details*  Ptr_Temp_Search;
             Ptr_Temp_Search=Train_anchor;//point to anchor of train list
              
             while ((Ptr_Temp_Search->Next!=NULL) && 
                   (Ptr_Temp_Search->Next->Type<type) &&
                   (Ptr_Temp_Search->Next->Line_Number!=Line_Number))
                                                 //check if its the last link
                                                 //or we passed the desired
                                                 // postion by type stop a link before
             {
                       Ptr_Temp_Search=Ptr_Temp_Search->Next;//move to next link
             }

             while ((Ptr_Temp_Search->Next!=NULL) && 
                   ((Ptr_Temp_Search->Next->Type==type) &&
                   (Ptr_Temp_Search->Next->Line_Number<Line_Number)))
                                                 //check if its the last link
                                                 //or we passed the desired
                                                 // postion by number number 
                                                 //(with the same type as the
                                                 //new like stop a link before
             {
                       Ptr_Temp_Search=Ptr_Temp_Search->Next;//move to next link
             }

             return Ptr_Temp_Search;//return pointer to the link before 
               
}

//this function create a new train link
TRAIN_Details* create_train(FILE* error,LINE* Ptr_Line)
{
      TRAIN_Details* TEMP_TO_CREATE;
      TEMP_TO_CREATE = (TRAIN_Details*) malloc(sizeof(TRAIN_Details));//create space 
                                                                 //for new link 
                                                                 //of line
      if (TEMP_TO_CREATE==NULL)                       //did create space fallid?
      {
         free(TEMP_TO_CREATE);//delete train
         free(Ptr_Line);//delete line
         if (mtmPrintErrorMessage(error, MTM_OUT_OF_MEMORY)<0)
         exit(MTM_OUT_OF_MEMORY);   // space create faild error
      }   
      return TEMP_TO_CREATE;   //return pointer to new link
}

//this function put data in new link
void put_data_in_link_train (TRAIN_Details* TEMP_TO_CREATE,TRAIN_Details* Ptr_Temp_Search,int Line_Number,double Price,LINE* Ptr_Line,TrainType Type)
{
    TEMP_TO_CREATE->Line_Number=Line_Number;//put line number
    TEMP_TO_CREATE->Next=Ptr_Temp_Search->Next;//link the the next link 
    TEMP_TO_CREATE->price=Price;//put price
    TEMP_TO_CREATE->ptr_Line=Ptr_Line;//link train link to the line link
    TEMP_TO_CREATE->Type=Type;//put type
    Ptr_Line->Details=TEMP_TO_CREATE;//link line to train link
    Ptr_Temp_Search->Next=TEMP_TO_CREATE;//link the previos link to new link             
}

//this function transalte string to Train Type
TrainType get_Train_Type (char* Type)
{
    if (strcmp (Type,"direct")==0)    //if type is TRAIN_DIRECT 
       return TRAIN_DIRECT;
    if (strcmp (Type,"intercity")==0) //if type is TRAIN_INTERCITY  
       return TRAIN_INTERCITY;
    if (strcmp (Type,"suburban")==0)  //if type is TRAIN_SUBURBAN 
       return TRAIN_SUBURBAN;
       
    exit(1);//error
           
}

//this the "respy' to add train
int add_train(LINE* Ptr_Line, double Price,int Line_Number,char* Type,TRAIN_Details* Train_anchor,FILE* error)
{   
    TRAIN_Details *Ptr_Temp_Search;//this variable is a tepmure variable
                                   //to search in the linked list trains 
    
    TRAIN_Details *TEMP_TO_CREATE;//this variable is a tepmure variable
                                  //help to create a new link
    TrainType keep_train_type;    

    check_the_price_is_right(Price,error);//check the price
    if (check_line_number(Line_Number,error) == 0) {return 1;}//check line number
    keep_train_type=get_Train_Type(Type);//get train type         
    Ptr_Temp_Search=walk_over_TRAIN_list(Line_Number,Train_anchor,keep_train_type);//search train list
    TEMP_TO_CREATE =  create_train(error,Ptr_Line);//create space for new link 
    put_data_in_link_train (TEMP_TO_CREATE,Ptr_Temp_Search,Line_Number,Price,Ptr_Line,keep_train_type);//insert data to link
    return 1;  
}

