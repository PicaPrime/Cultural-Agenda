#include <stdio.h>
#include <stdlib.h>
#include<string.h>

// Event data structures and enum (defined previously)
typedef enum {
    B6,
    B12,
    B16
} EventClassification;

typedef struct {
    char name[100];      // Event name
    char artistGroup[100]; // Artist or group name
    EventClassification classification; // Event classification
    int hour;            // Event starting hour
    int minutes;         // Event starting minutes
    int day;             // Event day
    int month;           // Event month
    int year;            // Event year
    int duration;        // Event duration in minutes
    int capacity;        // Event venue capacity
    int ticketsAvailable; // Number of tickets still available
} EventRegister;

// Function prototypes
int InsertEvent(EventRegister *events, int *numEvents) {
    if (*numEvents >= 100) {  // Assuming a maximum of 100 events
        printf("Error: Event vector is full.\n");
        return *numEvents;
    }

    // Get event information from user
    EventRegister newEvent;
    printf("Enter event name: ");
    scanf(" %[^\n]", newEvent.name);  // Read the entire line

    printf("Enter artist/group: ");
    scanf(" %[^\n]", newEvent.artistGroup);

    int classificationChoice;
    do {
        printf("Enter event classification (1 for B6, 2 for B12, 3 for B16): ");
        scanf("%d", &classificationChoice);
    } while (classificationChoice < 1 || classificationChoice > 3);
    newEvent.classification = (EventClassification)(classificationChoice - 1);

    // ... Get other event details similarly (date, time, duration, capacity) ...

    printf("Enter event Year: ");
    scanf("%d", &newEvent.year);

    printf("Enter event month: ");
    scanf("%d", &newEvent.month);

    printf("Enter event day: ");
    scanf("%d", &newEvent.day);

    printf("Enter event starting hour(in 24 hour format): ");
    scanf("%d", &newEvent.hour);

    printf("enter event starting minute:");
    scanf("%d", &newEvent.minutes);

    printf("enter the even duration in minutes: ");
    scanf("%d", &newEvent.duration);

    printf("enter the event capacity: ");
    scanf("%d", &newEvent.capacity);

    newEvent.ticketsAvailable = newEvent.capacity;  // Initially all tickets are available

    // Add the new event to the vector
    events[*numEvents] = newEvent;
    (*numEvents)++;

    printf("Event added successfully!\n");
    return *numEvents;
}


void SaveEvents(EventRegister *events, const char *filename, int numEvents) {
    FILE *fp = fopen(filename, "wb");  // Open the file in binary write mode
    if (fp == NULL) {
        printf("Error opening file: %s\n", filename);
        return;
    }

    // Write the number of events first
    fwrite(&numEvents, sizeof(int), 1, fp);

    // Write each event structure to the file
    for (int i = 0; i < numEvents; i++) {
        fwrite(&events[i], sizeof(EventRegister), 1, fp);
    }

    fclose(fp);  // Close the file
    printf("Events saved to file successfully!\n");
}

int LoadEvents(EventRegister *events, const char *filename) {
    FILE *fp = fopen(filename, "rb");  // Open the file in binary read mode
    if (fp == NULL) {
        printf("Error opening file: %s\n", filename);
        return 0;
    }

    int numEvents;
    fread(&numEvents, sizeof(int), 1, fp);  // Read the number of events from the file

    // Read each event structure from the file and store it in the vector
    int eventsRead = 0;
    for (int i = 0; i < numEvents && !feof(fp); i++) {
        if (fread(&events[i], sizeof(EventRegister), 1, fp) == 1) {
            eventsRead++;
        }
    }

    fclose(fp);  // Close the file
    printf("%d events loaded from file.\n", eventsRead);
    return eventsRead;
}

void PrintEvent(const char *eventName, EventRegister *events, int numEvents) {
    int found = 0;
    for (int i = 0; i < numEvents; i++) {
        if (strcmp(events[i].name, eventName) == 0) {
            printf("\nEvent Name: %s\n", events[i].name);
            printf("Artist/Group: %s\n", events[i].artistGroup);
            printf("Classification: %s\n", 
                  events[i].classification == B6 ? "B6" :
                  events[i].classification == B12 ? "B12" : "B16");
            printf("Date: %02d/%02d/%04d at %02d:%02d\n", events[i].day, events[i].month, events[i].year, events[i].hour, events[i].minutes);
            printf("Duration: %d minutes\n", events[i].duration);
            printf("Capacity: %d\n", events[i].capacity);
            printf("Tickets Available: %d\n", events[i].ticketsAvailable);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Event '%s' not found.\n", eventName);
    }
}


int main() {
    EventRegister events[100];  // Array to store events
    int numEvents = LoadEvents(events, "events.dat");

    int choice;
    do {
        printf("\nMENU\n");
        printf("[1] Insert information about a new event into the vector\n");
        printf("[2] List information about a specific event\n");
        printf("[0] Exit and save event information to File\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                numEvents = InsertEvent(events, &numEvents);
                break;
            case 2: {
                char eventName[100];
                printf("Enter the name of the event to list: ");
                scanf(" %[^\n]", eventName);  // Read the entire line
                PrintEvent(eventName, events, numEvents);
                break;
            }
            case 0:
                SaveEvents(events, "events.dat", numEvents);
                printf("Events saved to file. Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 0);

    return 0;
}
