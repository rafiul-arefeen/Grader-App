// This progrma takes commmand line arguments
// Use "help" as an argument to determine your next steps

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "CourseArray.h"

int main(int argc, char *argv[])
{
    FILE *fp;
    char arr[20];
    CourseArrayController controller = CourseArray_New();

    if (strcmp(argv[1], "add") == 0)
    {
        scanf("%s %d %f", controller.Courses[controller.Count].name, &controller.Courses[controller.Count].code, &controller.Courses[controller.Count].cgpa);
        CourseArray_Add(&controller, controller.Courses[controller.Count]);
        fp = fopen("CourseInfo.txt", "a");
        SerializeInfo(&controller, fp);
    }

    else if (strcmp(argv[1], "list") == 0)
    {
        DeserializeInfo(&controller, fp);
        CourseArray_Sort(&controller);
        CourseArray_Print(&controller);
    }

    else if (strcmp(argv[1], "find") == 0)
    {
        int index;
        CourseInfo course;

        scanf("%s %d", course.name, &course.code);
        index = CourseArray_Find(&controller, course, fp);
        printf("%s %d %.2f\n", controller.Courses[index].name, controller.Courses[index].code, controller.Courses[index].cgpa);
    }

    else if (strcmp(argv[1], "clear") == 0)
    {
        CourseArray_Clear(fp);
    }

    else if (strcmp(argv[1], "remove") == 0)
    {
        CourseInfo course;

        scanf("%s %d", course.name, &course.code);
        CourseArray_Remove(&controller, course, fp);
    }

    else if (strcmp(argv[1], "cgpa") == 0)
    {
        float cgpa;

        cgpa = Calculate_CGPA(&controller, fp);
        printf("\n\n-- CGPA -- \n\n   %.2f\n", cgpa);
    }

    else if ((strcmp(argv[1], "help") == 0))
    {
        printf("------------------------------------------------------------------------------------");
        printf("\n\nHere are the commands to be entered for specific tasks:\n\n");
        printf(">> list -- To see the list of all courses with details\n");
        printf(">> add <COURSE_NAME> <COURSE_CODE> <GPA> -- To add a new course\n");
        printf(">> find <COURSE_NAME> <COURSE_CODE> -- To find a specific course and see the GPA\n");
        printf(">> remove -- To remove a specific course from the list\n");
        printf(">> cgpa -- Calculate CGPA\n");
        printf(">> clear -- To clear all saved data\n\n");
        printf("------------------------------------------------------------------------------------\n");
    }

    return 0;
}
