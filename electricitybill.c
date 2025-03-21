#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void generateBill(const char *name, const char *address, int meterno, int prevread, int curread, const char *email) {
    int units = curread - prevread;
    float amount = (units > 300) ? units * 3.50 :
                   (units > 200) ? units * 3.00 :
                   (units > 100) ? units * 2.50 : units * 2.00;

    // Get current month and calculate payment deadline (10th of next month)
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    
    char month[20];
    char next_month[20];
    char *months[] = {"January", "February", "March", "April", "May", "June", 
                      "July", "August", "September", "October", "November", "December"};

    int current_month = tm.tm_mon;  // 0-indexed (January = 0)
    int next_month_index = (current_month + 1) % 12;

    sprintf(month, "%s", months[current_month]);
    sprintf(next_month, "%s", months[next_month_index]);

    // Save bill to a file
    FILE *fp = fopen("bill.txt", "w");
    fprintf(fp, "                Electricity Bill - %s                \n", month);
    fprintf(fp, "----------------------------------------------------\n");
    fprintf(fp, "Name: %s\nAddress: %s\n", name, address);
    fprintf(fp, "Meter No: %d\nPrevious Reading: %d\nCurrent Reading: %d\n", meterno, prevread, curread);
    fprintf(fp, "Units Consumed: %d\nTotal Amount: ₹%.2f\n", units, amount);
    fprintf(fp, "Payment Due Date: 10th %s\n", next_month);
    fprintf(fp, "----------------------------------------------------\n");
    fclose(fp);

    // Email Body Content
    char body[600];
    sprintf(body, "Name: %s\\nAddress: %s\\nMeter No: %d\\nMonth: %s\\nPrevious Reading: %d\\nCurrent Reading: %d\\nUnits Consumed: %d\\nTotal Amount: ₹%.2f\\nPayment Due Date: 10th %s\\n",
            name, address, meterno, month, prevread, curread, units, amount, next_month);

    // Command to run Python script for sending email
    char command[700];
    sprintf(command, "python mail.py %s \"Your Electricity Bill - %s\" \"%s\"", email, month, body);
    system(command);

    printf("\nBill for %s generated and sent to %s!\n", month, email);
}

int main() {
    char name[50], address[100], email[100];
    int meterno, prevread, curread;

    // Get customer details
    printf("                Electricity Bill Generator                \n");
    printf("----------------------------------------------------\n");
    printf("Enter Name: ");
    scanf(" %[^\n]", name);
    printf("Enter Address: ");
    scanf(" %[^\n]", address);
    printf("Enter Meter Number: ");
    scanf("%d", &meterno);
    printf("Enter Previous Reading: ");
    scanf("%d", &prevread);
    printf("Enter Current Reading: ");
    scanf("%d", &curread);
    printf("Enter Email: ");
    scanf("%s", email);

    generateBill(name, address, meterno, prevread, curread, email);
    return 0;
}
