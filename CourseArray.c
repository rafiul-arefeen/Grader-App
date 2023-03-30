#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include "CourseArray.h"

int CourseArray_Grow(CourseArrayController *restrict controller);

CourseArrayController CourseArray_New(void)
{
    CourseArrayController controller = (CourseArrayController){
        .Courses = NULL,
        .Count = 0U,
        .Capacity = 2};

    controller.Courses = (CourseInfo *)malloc(controller.Capacity * sizeof(CourseInfo));

    if (controller.Courses == NULL)
        exit(1);

    return controller;
}

int CourseArray_Grow(CourseArrayController *restrict controller)
{
    CourseInfo *requested = (CourseInfo *)realloc(
        controller->Courses,
        controller->Capacity * 2 * sizeof(CourseInfo));
    if (requested == NULL)
    {
        return 0;
    }
    else
    {
        controller->Courses = requested;
        controller->Capacity *= 2;
        return 1;
    }
}

int CourseArray_Add(CourseArrayController *restrict controller, CourseInfo element)
{
    if (controller->Capacity == 0U)
        return -1;
    if (controller->Count < controller->Capacity)
    {
        controller->Courses[controller->Count++] = element;
    }
    else
    {
        if (!CourseArray_Grow(controller))
            return 0;
        controller->Courses[controller->Count++] = element;
    }
    return 1;
}

void CourseArray_Print(CourseArrayController *restrict controller)
{
    printf("\n   Name Code GPA\n\n");
    for (size_t i = 0U; i < controller->Count; i++)
    {
        printf(">> %s %d %.2f\n", controller->Courses[i].name, controller->Courses[i].code, controller->Courses[i].cgpa);
    }
}

void SerializeInfo(CourseArrayController *controller, FILE *fp)
{

    for (int i = 0; i < controller->Count; i++)
    {
        fprintf(fp, "%s %d %.2f\n", controller->Courses[i].name, controller->Courses[i].code, controller->Courses[i].cgpa);
    }
    fclose(fp);
}

void DeserializeInfo(CourseArrayController *controller, FILE *fp)
{
    CourseInfo Info;
    fp = fopen("CourseInfo.txt", "r");
    while (fscanf(fp, "%s %d %f", Info.name, &Info.code, &Info.cgpa) != EOF)
    {
        strcpy(controller->Courses[controller->Count].name, Info.name);
        controller->Courses[controller->Count].code = Info.code;
        controller->Courses[controller->Count].cgpa = Info.cgpa;
        controller->Count++;
    }

    fclose(fp);
}

int CourseArray_Find(CourseArrayController *restrict controller, CourseInfo course, FILE *fp)
{
    DeserializeInfo(controller, fp);
    for (size_t i = 0; i < controller->Count; i++)
    {
        if ((strcmp(controller->Courses[i].name, course.name) == 0) && (controller->Courses[i].code) == course.code)
        {
            return i;
        }
    }
    return -1;
}

void CourseArray_Clear(FILE *fp)
{
    fp = fopen("CourseInfo.txt", "w");
}

void CourseArray_Remove(CourseArrayController *restrict controller, CourseInfo course, FILE *fp)
{
    int index;
    index = CourseArray_Find(controller, course, fp);
    controller->Count--;
    if (index == -1)
        printf("\n\n-- Element does not exist --\n\n");
    else
    {
        for (int i = index; i < controller->Count; i++)
        {
            strcpy(controller->Courses[index].name, controller->Courses[index + 1].name);
            controller->Courses[index].code = controller->Courses[index + 1].code;
            controller->Courses[index].cgpa = controller->Courses[index + 1].cgpa;
        }
        printf("\n\n-- Element removed --\n");
    }
    fp = fopen("CourseInfo.txt", "w");
    SerializeInfo(controller, fp);
}

float Calculate_CGPA(CourseArrayController *restrict controller, FILE *fp)
{
    float total = 0, cgpa;
    DeserializeInfo(controller, fp);
    for (int i = 0; i < controller->Count; i++)
    {
        total += controller->Courses[i].cgpa;
    }
    cgpa = total / (controller->Count);

    return cgpa;
}

void CourseArray_Sort(CourseArrayController *restrict controller)
{
    CourseInfo tempInfo;
    for (int i = 0; i < controller->Count - 1; i++)
    {
        for (int j = i + 1; j < controller->Count; j++)
        {
            if (strcmp(controller->Courses[i].name, controller->Courses[j].name) > 0)
            {
                tempInfo = controller->Courses[i];
                controller->Courses[i] = controller->Courses[j];
                controller->Courses[j] = tempInfo;
            }

            else if (strcmp(controller->Courses[i].name, controller->Courses[j].name) == 0)
            {
                if (controller->Courses[i].code > controller->Courses[j].code)
                {
                    tempInfo = controller->Courses[i];
                    controller->Courses[i] = controller->Courses[j];
                    controller->Courses[j] = tempInfo;
                }
            }
        }
    }
}