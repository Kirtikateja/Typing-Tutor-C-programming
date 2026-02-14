                              //* TYPING TUTOR PROJECT //*
//C Header Files                                 
#include<stdio.h>   // Used for standard Input/Output functions
#include<stdlib.h>  //General Purpose Library
#include<string.h>  //Used for Sting Functions
#include<conio.h>   //to provide console input/output
#include<time.h>   //Time related function

//Function to display progress from a file
void displayProgress() {
    FILE *progressFile = fopen("progress.txt", "r");
    printf("\n\n--- Progress Summary ---\n");
    char line[100];
    while (fgets(line, sizeof(line), progressFile) != NULL) { //size of line specifies the maximum number of characters to read in one iteration.
        printf("%s", line);
    }
    fclose(progressFile);
}
//Program execution starts from main
main(){    
 double sum = 0;
    double add = 1,elapsed;
	int choice,i,iterations;
	long seconds, nanoseconds;
	float accuracy=1, error=0,scount=0,wpm=1;
	FILE *fptr, *progressFile;
	char data[50];
	char name[20];
	char ch;
	//Inputting users name
	printf("\nEnter your name: ");
	gets(name);
	do{
		//Displaying Typing Tutor Menu
		printf("\n\n\t--- Typing Tutor Menu ---\n");
	    printf("\t1. Start Easy Lesson\n");
	    printf("\t2. Start Difficult Lesson\n");
	    printf("\t3. View Performance Summary\n");
	    printf("\t4. Exit\n");
	    printf("________________________________________________\n");
	    printf("\nEnter your choice: ");
	    scanf("%d",&choice);
	    //choice handling
	    if(choice==1){ //EASY LESSON
    	printf(" \n\t\" YOU SELECTED AN EASY LESSON\"\n\n");
    	fptr=fopen("easy.txt","r");
    	printf("\t");
    	fgets(data,50,fptr); //fgets will read character present in the file
    	printf("%s",data); 
    	printf("\n\n\tTYPE THE ABOVE TEXT CORRECTLY: \n\n\t");
    	
     struct timespec begin, end; //structure declaration
     //Time measurement starts..
    clock_gettime(CLOCK_REALTIME, &begin);
    //Loop to count mistakes/errors
    	for(i=0;i<strlen(data);i++) 
		{
			ch=getch(); //it will get input from the user
			if(ch==data[i]){
			printf("%c",ch);
			}
			else {
				i=i-1;
				error=error+1;
				printf("\a");
			}
		}
	accuracy=(strlen(data)/(error+strlen(data))*100); //Accuracy Calculation
	printf("\n\n Your accuracy is: %.1f%\n",accuracy);
	printf("\n The length of the sentence is  %d\n",strlen(data)); //string function
    printf("\n You have entered %.1f incorrect characters \n",error);
	iterations = 100;
	for ( i=0; i<iterations; i++) {
        sum += add;
        add /= 2.0;
    }
    //Time measurement ends..
    clock_gettime(CLOCK_REALTIME, &end);
     seconds = end.tv_sec - begin.tv_sec;
     nanoseconds = end.tv_nsec - begin.tv_nsec;
     elapsed = seconds + nanoseconds*1e-9;
	 printf("\n Result: %.5f\n", sum);
    printf("\n Time measured: %.3f seconds\n", elapsed);
		scount=0; //Counting words
		for(i=0;i<strlen(data);i++)
		{
			if(data[i]==' ')
			{
				scount=scount+1; 
			} 
	    }
	   //Displaying WPM (word count) 	
    printf("\n The total words you typed are: %f\n",scount+1);
    wpm = (scount+1)/(elapsed / 60.0);
	printf("\n Your speed is %.2f words per minute\n", wpm); //Speed of inputted words per minute
        fclose(fptr);
	}
		else if (choice==2){ //choice handling
		//Declarations for a DIFFICULT LESSON
    	printf(" \n\t\" YOU SELECTED A DIFFICULT LESSON\"\n\n");
    	fptr=fopen("difficult.txt","r");
    	printf("\t");
    	fgets(data,50,fptr);
    	printf("%s",data);
    	printf("\n\n\tTYPE THE ABOVE TEXT CORRECTLY: \n\n\t");
    	struct timespec begin, end; //structure declaration
    	//Time measurement starts..
    clock_gettime(CLOCK_REALTIME, &begin);
	for(i=0;i<strlen(data);i++) //Loop to calculate mistakes
		{
			ch=getch();
			if(ch==data[i])
			{
			printf("%c",ch);
			}
			else 
			{
			i=i-1;
				error=error+1;
				printf("\a");
			}
	}
	accuracy=(strlen(data)/(error+strlen(data)))*100; //Calculating the Accuracy
	scount=0; //word count
		for(i=0;i<strlen(data);i++)
		{
			if(data[i]==' ')
			{
				scount=scount+1;
			} 
	    }
	    //Displaying WPM (word count)
    printf("\n\n Your accuracy is: %.1f%\n",accuracy);
    printf("\n The length of the sentence is  %d\n",strlen(data));
	printf("\n You have entered %.1f incorrect characters \n",error); //calculating no. of mistakes we did
		iterations = 100;
	for ( i=0; i<iterations; i++) {
        sum += add;
        add /= 2.0;
    }
    //Time measurement ends..
    clock_gettime(CLOCK_REALTIME, &end);
     seconds = end.tv_sec - begin.tv_sec;
     nanoseconds = end.tv_nsec - begin.tv_nsec;
     elapsed = seconds + nanoseconds*1e-9;
	 printf("\n Result: %.5f\n", sum);
    printf("\n Time measured: %.3f seconds.\n", elapsed); //displays measured time
    printf("\n The total words you typed are: %f\n",scount+1);
    wpm = (scount+1)/(elapsed / 60.0);
	printf("\n Your speed is %.2f words per minute\n", wpm); //displays words count per minute
	}
	else if(choice==3){ //choice handling
	//View Perfomance Summary
		printf("Choose which progress to display:\n");
                printf("1. Easy Lesson\n");
                printf("2. Difficult Lesson\n");
                int progresschoice;
                printf("Enter your choice: ");
                scanf("%d", &progresschoice);
		progressFile = fopen("progress.txt", "a"); //opening progress file for appending
		//"a" is for append it will keep the previous data save
            if (progressFile == NULL) { //check if file opening was successful
                printf("Error opening the progress file."); //Exits if file opening failed.
                return;
            }
            //Displaying Perfomance Summary to the progress file
            fprintf(progressFile, "\nName: %s, Lesson: %s, Accuracy: %.1f%%, WPM: %.2f, Mistakes: %.2f", name,
            (progresschoice == 1) ? "Easy" : "Difficult", accuracy, wpm, error);
            fclose(progressFile); //closes the progress file
            displayProgress(); //displays summary by calling this function we created above
	}
	
	else if(choice==4){
		printf("\nYour program has terminated!!");
	}
	}
	while(choice!=4);
	//Close file and displays success message..	
	fclose(fptr);
	printf("\n\nFile sucessfully created!!");
}
