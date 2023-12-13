#include <stdio.h>
#include <string.h>

const char* SUBJECTS[] = {"Maths            ", "Physics          ", "Computer science " ,"English          ", "French           "};
const int SUBJECTS_COUNT = 5;

int get_student_data(char* student_name){
    char path[100] = "database/";
    strcat(path, student_name);
    strcat(path, ".txt");

    FILE* f = fopen(path, "r");
    if(f == NULL){
        printf("Student not found\n");
        return 1;
    }

    float mark;
    for(int i = 0; i<SUBJECTS_COUNT; i++){
        printf("%s: ", SUBJECTS[i]);

        int nbr_of_marks;
        fscanf(f, "%d", &nbr_of_marks);
        for(int j = 0; j<nbr_of_marks; j++){
            fscanf(f, "%f", &mark);
            printf("%.2f | ", mark);
        }
        printf("\n");
    }
    return 0;
}



int main(){
    char student_name[100];
    printf("Enter student name: ");
    scanf("%s", student_name);
    get_student_data(student_name);

    return 0;
}