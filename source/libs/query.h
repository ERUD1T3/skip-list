/*****************************************
 * query.h 
 * Interface for processing commands from input file
 * Josias Moukpe
 ****************************************/


#ifndef QUERY_H
#define QUERY_H 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "sllist.h"
#include "skipList.h"


/*******************************
 * METHODS PROTOTYPES
 ******************************/

void processQuery(SList* logs, SLList* query_list);
void DisplayActivity(SList* logs, uint time);
void AddActivity(SList* logs, uint time, char* activity);
void DisplayAllActivities(SList* logs);
void PrintSkipList(SList* logs);
void DeleteActivity(SList* logs, uint time);
void DisplayActivitiesBetweenTimes(SList* logs, uint startTime, uint endTime);
void DisplayActivitiesFromStartTime(SList* logs, uint startTime);
void DisplayActivitiesToEndTime(SList* logs, uint endTime);


/************************************************
 * METHODS IMPLEMENTATION
 ***********************************************/


/* prints all entries between start and end times */
void DisplayActivitiesBetweenTimes(SList* logs, uint startTime, uint endTime) {
    printf("DisplayActivitiesBetweenTimes %d %d ", startTime, endTime);
    displayLevel(floorNode(ceilingEntry(logs, startTime)), floorNode(floorEntry(logs, endTime)));
    printf("\n");
}

/* prints all entries starting from startTime */
void DisplayActivitiesFromStartTime(SList* logs, uint startTime) {
    printf("DisplayActivitiesFromStartTime %d ", startTime);
    displayLevel(floorNode(ceilingEntry(logs, startTime)), NULL);
    printf("\n");
}

/* prints all entries from floor head to endTime */
void DisplayActivitiesToEndTime(SList* logs, uint endTime) {
    printf("DisplayActivitiesToEndTime %d ", endTime);
    displayLevel(logs->floor_head, floorNode(floorEntry(logs, endTime)));
    printf("\n");
}

/* Delete an entry from the logs */
void DeleteActivity(SList* logs, uint time) {
    printf("DeleteActivity %d ", time);
    if(removeEvent(logs, time) == NULL) printf("noTimeError");
    printf("\n");
}

/* Display an activity given a certain time */
void DisplayActivity(SList* logs, uint time) {
    char* activity = getEvent(logs, time);
    printf("DisplayActivity %d %s", time, (activity == NULL)?"None":activity);
    printf("\n");
}

/* add an activity to logs */
void AddActivity(SList* logs, uint time, char* activity) {
    printf("AddActivity %d %s", time, activity);
    putEvent(logs, time, activity);
    printf("\n");
}

/* display all the entries in floor level */
void DisplayAllActivities(SList* logs) {
    printf("DisplayAllActivities ");
    displayLevel(logs->floor_head, NULL);
    printf("\n");
}

/* display all the levels with all their entries */
void PrintSkipList(SList* logs) {
    printf("PrintSkipList");
    printList(logs);
    // printf("\n");
}

/* Executes the right query on the Taxonomy tree */ 
void processQuery(SList* logs, SLList* query_list) {
    if(!strcmp(getAt(query_list, 0), "DisplayActivity")) DisplayActivity(logs, atoi(getAt(query_list, 1)));
    else if(!strcmp(getAt(query_list, 0), "AddActivity")) AddActivity(logs, atoi(getAt(query_list, 1)), getAt(query_list, 2));
    else if(!strcmp(getAt(query_list, 0), "DeleteActivity")) DeleteActivity(logs, atoi(getAt(query_list, 1)));
    else if(!strcmp(getAt(query_list, 0), "DisplayActivitiesBetweenTimes")) DisplayActivitiesBetweenTimes(logs, atoi(getAt(query_list, 1)), atoi(getAt(query_list, 2)));
    else if(!strcmp(getAt(query_list, 0), "DisplayActivitiesFromStartTime")) DisplayActivitiesFromStartTime(logs, atoi(getAt(query_list, 1)));
    else if(!strcmp(getAt(query_list, 0), "DisplayActivitiesToEndTime")) DisplayActivitiesToEndTime(logs, atoi(getAt(query_list, 1)));
    else if(!strcmp(getAt(query_list, 0), "DisplayAllActivities")) DisplayAllActivities(logs);
    else if(!strcmp(getAt(query_list, 0), "PrintSkipList")) PrintSkipList(logs);
    else printf("Invalid command!\n");
    destroyList(query_list);
}

#endif // QUERY_H