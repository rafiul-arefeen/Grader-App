#pragma once

#include "CourseInfo.h"

typedef struct _courseArrayController
{
    CourseInfo *Courses;
    int Count;
    int Capacity;
} CourseArrayController;

CourseArrayController CourseArray_New(void);

int CourseArray_Grow(CourseArrayController *restrict controller);

int CourseArray_Add(CourseArrayController *restrict controller, CourseInfo element);

void CourseArray_Print(CourseArrayController *restrict controller);

void SerializeInfo(CourseArrayController *controller, FILE *fp);

void DeserializeInfo(CourseArrayController *controller, FILE *fp);

int CourseArray_Find(CourseArrayController *restrict controller, CourseInfo course, FILE *fp);

void CourseArray_Clear(FILE *fp);

void CourseArray_Remove(CourseArrayController *restrict controller, CourseInfo course, FILE *fp);

float Calculate_CGPA(CourseArrayController *restrict controller, FILE *fp);

void CourseArray_Sort(CourseArrayController *restrict controller);