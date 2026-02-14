#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int main() {
    int num;
    int i, iterations, count = 0;
    float accuracy, mistakes = 0, scount;
    char data[50], ch;
    double sum = 0;
    double add = 1;
    long seconds, nanoseconds;
    double elapsed;
    char again[10], name[50], viewSummary;

    FILE *summaryFile; // File pointer for saving the summary

    printf("--------------------------------------------- Welcome to the Typing tutor --------------------------------------------- ");
    printf("\nEnter your name: ");
    gets(name);

    while (strcmp(again, "No") != 0) {
        printf("\n1) Easy Text \n2) Difficult Text\nChoose any of the above: ");
        scanf("%d", &num);

        if (num == 1 || num == 2) {
            FILE *fptr;
            if (num == 1) {
                fptr = fopen("easy.txt", "r");
            } else {
                fptr = fopen("difficult.txt", "r");
            }

            if (fptr == NULL) {
                printf("Error opening the file!");
                return 1;
            }

            fgets(data, 50, fptr);
            printf("_______________________________________________\n\n");
            printf("%s", data);

            struct timespec begin, end;
            clock_gettime(CLOCK_REALTIME, &begin);
            printf("\n");

            for (i = 0; i < strlen(data); i++) {
                ch = getch();
                if (ch == data[i]) {
                    printf("%c", ch);
                } else {
                    i = i - 1;
                    mistakes = mistakes + 1;
                    printf("\a");
                }
            }

            printf("\n_______________________________________________\n\n");
            printf("\nSuccessfully executed!!\n");
            accuracy = (strlen(data) / (strlen(data) + mistakes) * 100);

            printf("\nThe length of the sentence is %d", strlen(data));
            printf("\nYour mistakes are: %.2f", mistakes);
            printf("\nYour accuracy is: %.2f", accuracy);

            iterations = 100;

            for (i = 0; i < iterations; i++) {
                sum += add;
                add /= 2.0;
            }

            clock_gettime(CLOCK_REALTIME, &end);
            seconds = end.tv_sec - begin.tv_sec;
            nanoseconds = end.tv_nsec - begin.tv_nsec;
            elapsed = seconds + nanoseconds * 1e-9;
            printf("\nTime measured: %.3f seconds.\n", elapsed);

            fclose(fptr);

            scount = 0;
            for (i = 0; i < strlen(data); i++) {
                if (data[i] == ' ') {
                    scount = scount + 1;
                }
            }

            printf("The total words you typed are: %f", scount + 1);
            printf("\nYour speed is: %f words per minute", (scount + 1) / (elapsed / 60));

            // Save the user summary to a file
            summaryFile = fopen("summary.txt", "a");
           
            fprintf(summaryFile, "\nAttempt %d Summary for %s:\n", count + 1, name);
             fprintf(summaryFile,"Mode chosen: %d",num);
            fprintf(summaryFile, "\nAccuracy: %.2f\n", accuracy);
            fprintf(summaryFile, "Mistakes: %.2f\n", mistakes);
            fprintf(summaryFile, "Time measured: %.3f seconds\n", elapsed);
            fprintf(summaryFile, "Words typed: %.1f\n", scount + 1);
            fprintf(summaryFile, "Speed: %f words per minute\n", (scount + 1) / (elapsed / 60));
            fclose(summaryFile);

            // Ask if the user wants to view the summary
            printf("\nDo you want to view your summary? (Y/N): ");
            scanf(" %c", &viewSummary);

            if (viewSummary == 'Y' || viewSummary == 'y') {
                summaryFile = fopen("summary.txt", "r");
                if (summaryFile == NULL) {
                    printf("Error opening the summary file!");
                    return 1;
                }

                char summaryLine[100];
                while (fgets(summaryLine, sizeof(summaryLine), summaryFile) != NULL) {
                    printf("%s", summaryLine);
                }

                fclose(summaryFile);
            }
        } else {
            printf("Wrong input!");
        }

        printf("\nDo you want to try again? Yes/No: ");
        scanf("%s", again);
        count = count + 1;
    }

    printf("\nGood Job %s!", name);
    printf("\nTyping tutor terminated.");
   
}
