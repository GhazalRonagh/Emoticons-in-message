/*Ghazal Ronagh  */
/* As we live in technological world, I wrote this project about message and 
emoticons that might be in each message. In each stage, I explained the things
I wanted to do. This program can be tested by test0 and test1 that I uploaded */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define STAGE_NUM_ONE 1			                  /* stage numbers */ 
#define STAGE_NUM_TWO 2
#define STAGE_NUM_THREE 3
#define STAGE_NUM_FOUR 4
#define STAGE_NUM_FIVE 5
#define STAGE_HEADER "Stage %d\n==========\n"	/* stage header format string */

#define MAX_MSG_LENGTH 280					    /* maximum message length */
#define MAX_NUM_MSGS 100					    /* maximum number of messages */
#define MAX_EMTCN_LENGTH 50					    /* maximum emot. line length */
#define MAX_NUM_EMTCN 50				    	/* maximum number of emot. */
				
typedef char msg_t[MAX_MSG_LENGTH+1];			/* a message */
typedef char emtcn_t[MAX_EMTCN_LENGTH+1];		/* an emoticon */

/****************************************************************/
/* function prototypes */
void read_one_msg(msg_t one_msg, int max_len);
void read_one_emtcn(msg_t emtcn, int max_len); 
void print_stage_header(int stage_num);
int count_tokens(msg_t one_msg);

void stage_one(msg_t one_msg);
void stage_two(msg_t msgs[], int *num_msgs);
void stage_three(msg_t msgs[], int num_msgs);
void stage_four(emtcn_t emtcns[], int *num_emtcns);
void stage_five(msg_t msgs[], int num_msgs, emtcn_t emtcns[], int num_emtcns);

/* add your own function prototypes here */	
void copy_non_alphanums(msg_t msg);       //stage 2
void remove_extra_comma(msg_t mesg);      //stage 3
void remove_emotion_txt(emtcn_t emotc);   //stage4
int valid_emtcn(emtcn_t emtcn, emtcn_t emtcns[] , int num_emtcns); //stage 5
/****************************************************************/

/* main function controls all the action*/
int
main(int argc, char *argv[]) {
	/* to hold all input messages */
	 msg_t msgs[MAX_NUM_MSGS];	
	/* to hold the number of input messages */
	int num_msgs = 0;	
	/* to hold all input emoticons in the dictionary */
	emtcn_t emtcns[MAX_NUM_EMTCN];
	/* to hold the number of emoticons in the dictionary */
	int num_emtcns = 0;	
	/* stage 1: reading the first message */
	stage_one(msgs[num_msgs]); 
	 num_msgs++;
	/* stage 2: removing alphanumeric characters */
	stage_two(msgs, &num_msgs); 
	/* stage 3: removing extra commas */ 
	stage_three(msgs, num_msgs);
	
	/* stage 4: reading the dictionary and finding the longest emoticon */
	stage_four(emtcns, &num_emtcns);
	
	/* stage 5: removing invalid emoticons with the help of the dictionary */
	stage_five(msgs, num_msgs, emtcns, num_emtcns);
	
	/* all done; take some rest */
	return 0;
}
/************************************************************************/

/* read a line of input into one_msg */
void
read_one_msg(msg_t one_msg, int max_len) {
	int i = 0, c;
	while (((c = getchar()) != EOF) && (c != '\n') && (c != '\r')) {
		if (i < max_len) {
			one_msg[i++] = c;
		} else {
			printf("Invalid input line, toooooooo long.\n");
			exit(EXIT_FAILURE);
		}
	}
	one_msg[i] = '\0';
}
 


/*read a line of input into emtcn (add this part for ease of use in stage 4*/

void
read_one_emtcn(msg_t emtcn, int max_len) {
	int i = 0, c;
	while (((c = getchar()) != EOF) && (c != '\n') && (c != '\r')) {
		if (i < max_len) {
			emtcn[i++] = c;
		} else {
			printf("Invalid input line, toooooooo long.\n");
			exit(EXIT_FAILURE);
		}
	}
	emtcn[i] = '\0';
}


/* print stage header given stage number */
void 
print_stage_header(int stage_num) {
	printf(STAGE_HEADER, stage_num);
}

/****************************************************************/

/* stage 1: reading the first message */
void 
stage_one(msg_t one_msg) {
	/* print stage header */
	print_stage_header(STAGE_NUM_ONE);
	
	/*read the first message */
	read_one_msg (one_msg, MAX_MSG_LENGTH);
	

	/* print the number of tokens */	
	printf("Number of tokens: %d\n\n", count_tokens(one_msg));
    
}
/******************************/

/* count the number of tokens (separated by commas) in it */

int 
count_tokens(msg_t one_msg) {
	   
        int i, count = 0;
        	for(i=0; (unsigned)i<strlen(one_msg) ; i++){
	   	   		if (','== one_msg[i]){
                    count++;
			}
	  }
   
	return count+1 ; 
}
/****************************************************************/

/* stage 2: removing alphanumeric characters */
void 
stage_two(msg_t msgs[], int *num_msgs) {
	int i = *num_msgs;
	
	print_stage_header(STAGE_NUM_TWO);
	
/*read the first message until it reach the separating line*/
	read_one_msg(msgs[i], MAX_MSG_LENGTH);
	while (strcmp(msgs[i], "###")){	
		i++;
		read_one_msg(msgs[i], MAX_MSG_LENGTH);
	}
	
	(*num_msgs) = i;

/*remove alphanumeric characters and print the rest */
	for (i =0; i < *num_msgs ; i++){
    
		copy_non_alphanums(msgs[i]);  
		printf("%s\n", msgs[i]);
	}
	printf("\n");
}

/*********************************/
	
/*This function removes the alphanumeric characters */
void 
copy_non_alphanums(msg_t msg){ 
	int i, j = 0; 		
	for ( i = 0 ; (unsigned)i< strlen(msg); i++){
		if (!isalnum (msg[i])){
			msg[j++] = msg[i];
		}
	}
	msg[j] = '\0';

}

/*********************************************************************/
/* stage 3: removing extra commas */ 

void 
stage_three(msg_t msgs[], int num_msgs){
	
	print_stage_header(STAGE_NUM_THREE);	
  /*remove extra commas and print the rest */  
    int i;
	for (i = 0; i < num_msgs; i++){
		remove_extra_comma( msgs[i]);
		printf("%s\n", msgs[i]);
	
	}
	
	printf("\n");
		
}

/******************************/

/*This function cleanse the message by removing extra commas */

void remove_extra_comma(msg_t mesg){  
	int i = 0, j = 0;
	while (mesg[i] != '\0'){
		
		/*read commas */
		while (mesg[i] == ','){ 
			i++;
		}
		
         /* removing leading, trailing, and consecutive commas. */
		while ( (mesg[i] !='\0') &&(mesg[i] != ',' )){ 
			mesg[j++] = mesg[i++];	
		}	
		if (mesg[i] != '\0') {	   
			mesg[j++] = ',';
		}
	
	}
	if (mesg[j-1] == ','){
		j--;
	}
		
	mesg[j] = '\0';
		
}		

/**************************************************/
/* stage 4: reading the dictionary and finding the longest emoticon */ 
void stage_four(emtcn_t emtcns[], int *num_emtcns) {
	int i = 0; 
	int longest_emtcn_pos = 0;   
    
	print_stage_header(STAGE_NUM_FOUR);
    
	/*find the number of emtcns that is the number of lines */
	read_one_emtcn(emtcns[i],  MAX_EMTCN_LENGTH) ;
	
	while (emtcns[i][0] != '\0'){
		i++;
    	read_one_emtcn(emtcns[i],  MAX_EMTCN_LENGTH) ;
	}
	
	*num_emtcns = i;

    
/*skipping the emotion corresponding text,
then find the longest emtcn and its length*/

	for (i = 0; i < *num_emtcns; i++){
		remove_emotion_txt(emtcns[i]);
		
		if (strlen(emtcns[i]) > strlen(emtcns[longest_emtcn_pos])){
				longest_emtcn_pos = i;
		}
	
	}
	
	printf("Emoticon total: %d\n", *num_emtcns);
	printf("Longest: %s\n",(emtcns[longest_emtcn_pos] ));
	printf("Length: %d\n", strlen(emtcns[longest_emtcn_pos] ));

printf("\n");
}
	
/***********************************************/
void remove_emotion_txt(emtcn_t emotc){
	int i ;
	
 /*skips the alphabetic characters (skip texts that show the meaning of emtc)*/ 
  	  for (i = 0; (unsigned)i< strlen(emotc) ;i++){ 	  	  
  	  	  if (emotc[i] == ','){
  	  	  	  emotc[i] = '\0';
  	  	  	  return;
  	  	  	 
  	  	   }
  	  }
}	  
  	     		 	  	
/**************************************************************/

 /* stage 5: removing invalid emoticons with the help of the dictionary */
void 
stage_five(msg_t msgs[], int num_msgs, emtcn_t emtcns[], int num_emtcns) {
	int i , j, k;
	int is_empty;
	emtcn_t emtcn="";
	
	print_stage_header(STAGE_NUM_FIVE);
    
	/* search for the valid emtcns in msgs[i] and print valid emoticons */
	
	for (i = 0; i < num_msgs; i++){
		k=0;
		is_empty=1;
        
		/* For each message, copy every emoticons (every token) to emtcn
        and print it if valid */
		for(j = 0; msgs[i][j] != '\0'; j++) {
			if(msgs[i][j] == ',') {
				emtcn[k] = '\0';
				if(valid_emtcn(emtcn,emtcns,num_emtcns)) {
					printf("%s",emtcn);
				}
				printf(",");
				is_empty=0;
				k=0;
			}
			else {
				emtcn[k++]=msgs[i][j];
			}
		}
		/* Check and print last emoticon in the message */
		emtcn[k]='\0';
		if(valid_emtcn(emtcn,emtcns,num_emtcns)) {
			printf("%s",emtcn);
			is_empty=0;
		}
		if(!is_empty) {	
			printf("\n");
		}
	}
}
	
/*****************************/
	
/*this function do a smiliar job to strcmp by comparing two emtcns (a and b) */			
int is_emtcn_equal(emtcn_t a, emtcn_t b) { 
	int i;
	for (i = 0; a[i] != '\0'; i++){
		if(a[i] != b[i]){
			return 0;
		}
	}
	if (b[i] != '\0'){
		return 0;
	}
	return 1;
}

/*This seq pattern search checks if the "pattern emoticon" 
is in target dictionary (including emotion and the corresponding text) */

int valid_emtcn(emtcn_t emtcn, emtcn_t emtcns[] , int num_emtcns) {

	int i;
	
	/*it returns "True " for all the valid emoticons */
	for (i = 0; i < num_emtcns; i++){
		if (is_emtcn_equal (emtcn, emtcns[i])){  
			return 1; 
		}
	}
	
	return 0; 
}