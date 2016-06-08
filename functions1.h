//this function check if line exist
int check_if_line_exist(LINE* Ptr_Temp_Search,int Line_Number,FILE* error)
{

    if (Ptr_Temp_Search->Next!=NULL)          //end of list?
        {
         if (Ptr_Temp_Search->Next->Line_Number==Line_Number)//not end of list 
                                                             //is the next line number
                                                             //equel the new number 
                                                             //line?
         {
           if (mtmPrintErrorMessage(error, MTM_LINE_ALREADY_EXIST)<0)
           exit(MTM_LINE_ALREADY_EXIST); //line exist error
           return 0;
         }   
    	}
    else if (Ptr_Temp_Search->Line_Number==Line_Number)//not end of list 
                                                             //is the next line number
                                                             //equel the new number 
                                                             //line?
         {
           if (mtmPrintErrorMessage(error, MTM_LINE_ALREADY_EXIST)<0)
           exit(MTM_LINE_ALREADY_EXIST); //line exist error
           return 0;
         }   
    return 1;
}
int which_type(char* type) {
    if (type == "direct") return TRAIN_DIRECT;
    else {
         if (type == "intercity") return TRAIN_INTERCITY;
         else {
              if (type == "suburban") return TRAIN_SUBURBAN;
              else return -1;
         }
    }
}

void set_anchors (LINE* line,TRAIN_Details* train, BUSES_Details* bus,FILE* error)
{
    line->Details=NULL;
    line->First_Station=NULL;
    line->Last_Station=NULL;
    line->Line_Number=0;
    line->Next=NULL;
    
    
    train->Line_Number=0;
    train->Next=NULL;
    train->price=0;
    train->ptr_Line=NULL;
    train->Type=0;
    
    bus->Company=0;
    bus->Line_Number=0;
    bus->Next=NULL;
    bus->price=0;
    bus->ptr_Line=NULL;
    if (line==NULL)//malloc faild?
       {
                   free(bus);
                   free(train);
                   if (mtmPrintErrorMessage(error, MTM_OUT_OF_MEMORY)<0)
                   exit(MTM_OUT_OF_MEMORY);
                   return;
       }
    if (train==NULL)//malloc faild?
       {
                   free(line);//delete line
                   free(bus);
                    if (mtmPrintErrorMessage(error, MTM_OUT_OF_MEMORY)<0)
                   exit(MTM_OUT_OF_MEMORY);
                   return;
       }
    if (bus==NULL)//malloc faild?
       {
                   free(line);//delete line
                   free(train);//delete bus
                   if (mtmPrintErrorMessage(error, MTM_OUT_OF_MEMORY)<0)
                   exit(MTM_OUT_OF_MEMORY);
                   return;
       }
}
