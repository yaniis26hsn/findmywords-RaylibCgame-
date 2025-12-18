#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

bool isvalid(char answer[], int level, int length) {
    char buffer[10];
    char levelstrg[5];
    char levelstrg2[5];
    int level2 = level + 1 ;
    sprintf(levelstrg, "%d", level);
    sprintf(levelstrg2, "%d", level2);


    FILE* ansp;
    ansp = fopen("answers.txt", "r");
    if (!ansp) {
        printf("Could not open answers.txt\n");
        return false;
    }

    fscanf(ansp, "%s", buffer);
    bool entered = false;
    bool outted = false;
    bool found = false;

    while (!found && !feof(ansp) && !outted) {
    
        if (strcmp(buffer, levelstrg) == 0) {
            entered = true;

        }
        if (strcmp(buffer, levelstrg2) == 0) {
            outted = true;
        }
        if (entered && strcmp(buffer, answer) == 0 && !outted) {
            found = true;

        }
        if (!outted) {
            fscanf(ansp, "%s", buffer);
        }
    }

    fclose(ansp);
    return found;
}



char* getstr(int len){
    char* answer = (char*) malloc(len+1);

   for(int i=0;i<len;i++){
     answer[i]='_' ;
   }
   answer[len] = '\0' ;
     
    int lettercount = 0 ;
    
    while (lettercount < len) {
        int key = GetKeyPressed();
        
        if(key>=32 && key <=125 && lettercount < len){
            answer[lettercount]= (char) key ;
            lettercount ++ ;
        }
        if(key == KEY_BACKSPACE &&  lettercount>0){
            lettercount -- ;
            answer[lettercount] = '_' ;
        }
       // if(IsKeyPressed(KEY_ENTER)) break;
         
         
        // ADD THESE TWO LINES:
        BeginDrawing();
        DrawRectangle(500,400, 200, 40, BLACK);
        DrawText(answer, 505, 405, 30, WHITE);
        EndDrawing();
        
    }
    
    answer[lettercount]= '\0' ;
    return answer;
}

void openingScr(){
    BeginDrawing() ;
    ClearBackground(BLACK) ;
    DrawText("welcome to the game!",350,0,50,WHITE) ;
    DrawText("this is a words game where you are given a",0,70,50,WHITE) ;
    DrawText("bunch of charachters and you have to form ",0,140,50,WHITE) ;
    DrawText("different words using them .",0,210,50,WHITE) ;
    DrawText("the progress is saved at the end of each level",0,280,50,WHITE) ;
    DrawText("only  english words are accepted as an answer,",0,350,50,WHITE) ;
    DrawText("you should also know that the answer's length",0,420,50,WHITE) ;
    DrawText("is defined for each time so you should respect",0,490,50,WHITE) ;
    DrawText("it , thanks for playing !!!",0,560,50,WHITE) ;

    EndDrawing() ;

}

// if you want to add a local db to store the progress for each player ,
// use can use this func called "usrnainp".it uses a bin file .
/*

int usernainp() {
    player usr;
    char *var = getstr(0, 70, 10);
    strncpy(usr.username, var, 10);
    usr.username[10] = '\0';
    free(var);

    FILE *f = fopen("fil.dat", "rb+");
    if (f == NULL)
        f = fopen("fil.dat", "wb+");

    player buffer;
    bool found = false;
    while (fread(&buffer, sizeof(player), 1, f) == 1) {
        if (strcmp(buffer.username, usr.username) == 0) {
            found = true;
            break;
        }
    }

    if (found) {
        fclose(f);
        return buffer.level;
    } else {
        usr.level = 0;
        fseek(f, 0, SEEK_END);
        fwrite(&usr, sizeof(player), 1, f);
        fclose(f);
        return 0;
    }
}
*/

void makelevel(char chrs[], int level) {
    char answer[10];
    char levelText[50];
    sprintf(levelText, "current level: %d", level);
    BeginDrawing();
    ClearBackground(BLACK);
    DrawText(levelText, 350, 0, 50, WHITE);
    DrawText("the chars are : ", 0, 100, 50, WHITE);
    DrawText(chrs, 600, 100, 50, WHITE);
    DrawText("Enter a 4 chars length word : ", 0, 200, 50, WHITE);
    EndDrawing();
    
    do{
        strncpy(answer, getstr(4), sizeof(answer)-1);
        answer[sizeof(answer)-1] = '\0';
        printf("the entered answer is %s \n", answer);
        if(isvalid(answer,level,4)){
            BeginDrawing();
            DrawText("nice!!",500,700,50,WHITE);
            EndDrawing();
        }
        else{
            BeginDrawing();
            DrawText("wrong!!",500,700,50,WHITE);
            EndDrawing();
        }
        WaitTime(1);
        BeginDrawing();
            DrawRectangle(500,700,1200,100,BLACK);
            EndDrawing();

    }while(!isvalid(answer,level,4) );
    
    printf("the correct entered answer is %s \n", answer);
    
}

int main() {
    InitWindow(1200, 800, "just for the beginning");
    SetTargetFPS(60) ;
    
   
        openingScr();
        WaitTime(1) ;
        BeginDrawing();  
        DrawRectangle(0,0,1200,800,BLACK)  ;
        EndDrawing();
        makelevel("absd", 1);  
        CloseWindow();
    
       
    
    
    return 0;
}