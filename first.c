#include <stdio.h>

// Enumerated type for event classification
typedef enum {
    B6,
    B12,
    B16
} Classification;

// Structure for date
typedef struct {
    int hour;
    int minutes;
    int day;
    int month;
    int year;
} Date;

// New data type EventRegister
typedef struct {
    char name[50];
    char artist[50];
    Classification classification;
    Date date;
    int duration;
    int capacity;
    int ticketsAvailable;
} EventRegister;


// Function to insert a new event
void InsertEvent(EventRegister events[], int *numEvents, EventRegister newEvent) {
    // Set the available tickets to the capacity of the theater
    newEvent.ticketsAvailable = newEvent.capacity;

    // Insert the new event into the array
    events[*numEvents] = newEvent;

    // Increment the number of events
    (*numEvents)++;
}

int main() {
    // Array of events
    EventRegister events[100];

    // Number of events
    int numEvents = 0;

    // New event
    EventRegister newEvent = {"Concert", "Band", B12, {20, 30, 15, 7, 2023}, 120, 500, 0};

    // Insert the new event
    InsertEvent(events, &numEvents, newEvent);

    return 0;
}
