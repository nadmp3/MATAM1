/* The program get input and output from user. the input contain commend which work on data. the data contains lines of
 * transportation of buses and trains. each got default details for it. the bus contain comapny name, line number, 
 * stations and price, the train contains type of train: direct, suburby... price, stations as well.
 * the program can add lines, stations to each (bus/train), can remove line or station. then we can manage
 * the data and print it. print lines which the user request with all the info. print stations which include all the 
 * stations that the user insert to the line. and print rides which find the request ride between 2 stations and print it
 * if its lower then the price which was in the command.
 */ 
#include "mtm_ex1.h" // including of headers
#include "head.h"
#include <ctype.h> // including of saved libiries of C
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "checkers1.h"
#include "functions1.h"
#include "add_bus1.h"
#include "add_train1.h"
#include "add_line1.h"
#include "add_station1.h"
#include "remove_bus1.h"
#include "remove_train1.h"
#include "remove_line1.h"
#include "remove_station1.h"
#include "report1.h"
#include "delete.h"
#define MAX_WORDS 20 // max words to save from command
#define ERROR 0 // error in the arguments
#define RUN 1 // ok arguments

int main(int argc, char* argv[]) {//get arguments to run from user
	int i=0;// help integer for the program
	char* words[MAX_WORDS];// array of strings for the command to save
	char* command; // will help us in seperate words
	char* temp_string; // will help us in cut line
	FILE * input_file = stdin; // default for input
	FILE * error_file = stderr; // default for error
	FILE * output_file = stdout; //default for output
	int Result = RUN;// hold the result for arguments recived
	int line_number;// hold the line number after change from string
	int time;// hold the time after changing from string
	double price;// hold the price after chaning from string
	char line_buff [MAX_LEN]; // will hold each line from input
	LINE* line; // pointer to the start of struct linked for lines
	TRAIN_Details* train; // pointer for start of struct linked for trains
	BUSES_Details* bus; // pointer for start of struct linked for buses
	line = (LINE*) malloc(sizeof(LINE)); // malloc for the struct
	train = (TRAIN_Details*) malloc(sizeof(TRAIN_Details)); // malloc for the struct
	bus = (BUSES_Details*) malloc(sizeof(BUSES_Details)); // maloc for the struct
	set_anchors(line,train,bus,error_file); // set the first in each struct

	while (i < argc) { // until we over all arguments
     		command = argv[i+1];
		if (!strcmp(argv[i],"-i")) {                                   
       			if ((input_file = fopen(command,"r")) == NULL) {
				if (mtmPrintErrorMessage(error_file,MTM_CANNOT_OPEN_FILE) < 0) {exit(1);} //error
				Result = ERROR; // don't run the program
			}
		}
		if (!strcmp(argv[i],"-o")) {
	    		if ((output_file = fopen(command,"w")) == NULL) {
				if (mtmPrintErrorMessage(error_file,MTM_CANNOT_OPEN_FILE) <0) {exit(1);} // error
				Result = ERROR; // don't run the program
			}
		}
		i++;
	}
	if (Result) {   //if the argument were ok
		while ((fgets(line_buff, MAX_LEN, input_file)) != NULL) { //while we didnt get to end of file
			command = NULL; // initiliaze
			temp_string = NULL; 
			i=0; //ipus
			words[0] = NULL; //initialize
			words[1] = NULL;
			words[2] = NULL;
			words[3] = NULL;
			words[4] = NULL;
			words[5] = NULL;
			command = strtok(line_buff,"\t\v \n"); //cut the line
			while (isspace(line_buff[i])) {i++;} // search for white space to ignore
			temp_string = &line_buff[i]; // put the start of the string from the place there arent white spaces
			i=0; //ipus
			words[i] = temp_string; // get the string to first word
			while (command != NULL) { // while we get to the end of the line
              		i++;
              		command = strtok(NULL,"\t\v \n"); // cut words
              		words[i] = command; // get the word
        		}
        		i++; //kidum
        		words[i] = NULL; //null
        		if (!strcmp(words[0],"AddLine")) { // if the command is ADD line
            			line_number = atoi(words[2]); // get the line number
            			price = atof(words[4]); // get the price
            			Add_Line(words[1],line_number,words[3],price,train,bus,line,error_file);  // send to function addline
        		}
        		if (!strcmp(words[0],"RemoveLine")) { // if the command is remove line
                    		line_number = atoi(words[2]);  // get line number
				remove_line(check_train_or_bus(words[1],error_file),line_number,train,bus,line,error_file); //send to function
       			}
        		if (!strcmp(words[0],"AddStation")) {//if command is add station
                    		line_number = atoi(words[2]); //get the line number
                    		time = atoi(words[4]); //get the time
				Add_Station(check_train_or_bus(words[1],error_file),line_number,words[3],time,line,error_file); //send
        		} 
        		if (!strcmp(words[0],"RemoveStation")) {// if the command is remove station               
                   		line_number = atoi(words[2]); // get line number
				remove_station(check_train_or_bus(words[1],error_file),line_number,words[3],line,error_file); //send
        		}
        		if (!strcmp(words[0],"Report")) {     // if command is report                                       
                  		if (!strcmp(words[1],"lines")) { //if its report lines
                    			if (!words[2]) {report_lines(-1,bus,train,output_file,error_file);} //if we didnt get line_type
                    			else {
                      				if (!strcmp(words[2],"bus\r")) {report_lines(BUS,bus,train,output_file,error_file);}
                      				//if its bus
                      				else {
                           				if (!strcmp(words[2],"train\r"))//if its train
                           				 {report_lines(TRAIN,bus,train,output_file,error_file);} //send
			   				else {report_lines(-1,bus,train,output_file,error_file);}    
                           			}
                    			}
                  		}
                  		else {
                       			if (!strcmp(words[1],"rides")) { //if its report rides
                                    		price = atof(words[4]); //get price
                                    		report_rides(words[2],words[3],price,bus,train,output_file,error_file); //send
                       			}
                       			else {
                            			if (!strcmp(words[1],"stations")) {   
                            				//if its report stations                             
                                        		line_number = atoi(words[3]); //get line_number
				                      	report_stations(line,line_number,words[2],output_file,error_file);//send
                            			}
                       			}
                  		}    
        		}
   		}
   	}
	if (input_file != stdin) {free(input_file);} //free the input
	if (output_file != stdout) {free(output_file);} // free the output
	delete_and_exit(train ,bus,line,error_file);     //free all the structers   
	return 0;
}
