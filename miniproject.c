#include <stdio.h>
#include <string.h>

#define MAX_SEATS 5
#define MAX_BUSES 2

typedef struct {
    int seat_number;
    int is_booked;
    char passenger_name[50];
} Seat;

typedef struct {
    int bus_id;
    char route[50];
    Seat seats[MAX_SEATS];
} Bus;

Bus buses[MAX_BUSES];

void initialize_buses() {
    for (int i = 0; i < MAX_BUSES; i++) {
        buses[i].bus_id = i + 1;
        sprintf(buses[i].route, "Route %d", i + 1);
        for (int j = 0; j < MAX_SEATS; j++) {
            buses[i].seats[j].seat_number = j + 1;
            buses[i].seats[j].is_booked = 0;
        }
    }
}

void display_seats(int bus_id) {
    printf("\nBus %d (%s):\n", bus_id, buses[bus_id - 1].route);
    for (int i = 0; i < MAX_SEATS; i++) {
        printf("Seat %d: %s\n", buses[bus_id - 1].seats[i].seat_number,
               buses[bus_id - 1].seats[i].is_booked ? "Booked" : "Available");
    }
}

void book_seat() {
    int bus_id, seat_num;
    char name[50];
    printf("Enter Bus ID (1-%d): ", MAX_BUSES);
    scanf("%d", &bus_id);
    if (bus_id < 1 || bus_id > MAX_BUSES) { printf("Invalid Bus ID!\n"); return; }
    display_seats(bus_id);
    printf("Enter Seat Number (1-%d): ", MAX_SEATS);
    scanf("%d", &seat_num);
    if (seat_num < 1 || seat_num > MAX_SEATS || buses[bus_id - 1].seats[seat_num - 1].is_booked) {
        printf("Invalid or Already Booked Seat!\n");
        return;
    }
    printf("Enter Passenger Name: ");
    scanf(" %[^\n]", name);
    buses[bus_id - 1].seats[seat_num - 1].is_booked = 1;
    strcpy(buses[bus_id - 1].seats[seat_num - 1].passenger_name, name);
    printf("Seat %d booked successfully for %s!\n", seat_num, name);
}

void cancel_seat() {
    int bus_id, seat_num;
    printf("Enter Bus ID (1-%d): ", MAX_BUSES);
    scanf("%d", &bus_id);
    if (bus_id < 1 || bus_id > MAX_BUSES) { printf("Invalid Bus ID!\n"); return; }
    printf("Enter Seat Number (1-%d): ", MAX_SEATS);
    scanf("%d", &seat_num);
    if (seat_num < 1 || seat_num > MAX_SEATS || !buses[bus_id - 1].seats[seat_num - 1].is_booked) {
        printf("Invalid or Unbooked Seat!\n");
        return;
    }
    buses[bus_id - 1].seats[seat_num - 1].is_booked = 0;
    printf("Seat %d cancelled successfully!\n", seat_num);
}

void generate_ticket() {
    int bus_id, seat_num;
    printf("Enter Bus ID (1-%d): ", MAX_BUSES);
    scanf("%d", &bus_id);
    printf("Enter Seat Number (1-%d): ", MAX_SEATS);
    scanf("%d", &seat_num);
    if (seat_num < 1 || seat_num > MAX_SEATS || !buses[bus_id - 1].seats[seat_num - 1].is_booked) {
        printf("Invalid or Unbooked Seat!\n");
        return;
    }
    printf("\nTicket:\nBus %d (%s)\nSeat %d: %s\n", bus_id, buses[bus_id - 1].route,
           seat_num, buses[bus_id - 1].seats[seat_num - 1].passenger_name);
}

int main() {
    int choice;
    initialize_buses();
    while (1) {
        printf("\n1. Book Seat\n2. Cancel Reservation\n3. Display Seats\n4. Generate Ticket\n5. Exit\nChoice: ");
        scanf("%d", &choice);
        if (choice == 5) break;
        switch (choice) {
            case 1: book_seat(); break;
            case 2: cancel_seat(); break;
            case 3: {
                int bus_id;
                printf("Enter Bus ID (1-%d): ", MAX_BUSES);
                scanf("%d", &bus_id);
                if (bus_id < 1 || bus_id > MAX_BUSES) { printf("Invalid Bus ID!\n"); break; }
                display_seats(bus_id);
                break;
            }
            case 4: generate_ticket(); break;
            default: printf("Invalid choice!\n");
        }
    }
    return 0;
}