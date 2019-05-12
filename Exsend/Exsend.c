#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <stdbool.h>

/// Global Variable
int choices;
int global_counter = 0;

///---------------------------------------------Startup---------------------------------------------///

// Struct Declare
// (Linked List) Used for store readed city IDs and path

// File Read

void load_database()
{
	// Declare
	FILE *db;
	char city[999][999];

	db = fopen("city.db", "r");

	// Check for file availability
	if(db == NULL)
	{
		printf("\n");
		printf("Error while opening file.");
		printf("\n");
		exit(5);
	}

	// Read file and read to memory
	while( (fscanf(db, "")) != EOF )
	{
		global_counter++;
	}

}

void splash()
{
	
}

void banner()
{
    printf("========================================================================================================================"); printf("\n");
    printf("\n");
    printf("########################################################################################################################"); printf("\n");
    printf("###############################      ####  ###  ####     ####      ####  ####  ####     ################################"); printf("\n");
    printf("############################### ##########  #  #### ######### #########   ###  #### #### ###############################"); printf("\n");
    printf("###############################     #######  #######     ####     #####  # ##  #### #### ###############################"); printf("\n");
    printf("############################### ##########  #  #########  ### #########  ## #  #### #### ###############################"); printf("\n");
    printf("###############################      ####  ###  ####     ####      ####  ###   ####     ################################"); printf("\n");
    printf("########################################################################################################################"); printf("\n");
    printf("\n");
    printf("========================================================================================================================"); printf("\n");
    printf("\n");
}

void menu_awal()
{
    printf("                                      1) Customer         (Sending Packages)");     printf("\n");
    printf("                                      2) Go-Send Courier  (Delivering Packages)");  printf("\n");
    printf("                                      3) Exit");                                    printf("\n");
    printf("\n");
    printf("                                      Enter choice : ");
}

void menu_customer()
{
    banner();
    printf("                                      1) Go-Send order"); printf("\n");
    printf("                                      2) Delivery status check"); printf("\n");
    printf("\n");
    printf("                                      Enter choice : ");
}

void menu_courier()
{
    banner();
    printf("                                      1) Go-Send order"); printf("\n");
    printf("                                      2) Delivery status update"); printf("\n");
    printf("\n");
    printf("                                      Enter choice : ");
}

void menu_send()
{
    banner();
    printf("                                      1) Sender's name        : "); printf("\n");//ini nanti diisi sama scanf2 nya buat masukin data customer dll
    printf("                                      2) Pickup location      : "); printf("\n");
    printf("                                      3) Receiver's name      : "); printf("\n");
    printf("                                      4) Delivery address     : "); printf("\n");
    printf("\n");
    //nanti di sini mungkin pake function buat calculate price??
    printf("                                      Delivery fees : "); printf("\n");
    printf("                                      Delivery route  : "); printf("\n"); //ini kalau gamau gausah???
    printf("\n");
    system("pause"); //ini nanti tolong ilangin karena belom dimasukin scanf2 jd di pause dulu
}

void menu_delivery()
{
    banner();
    printf("                                      1) Sender's name        : "); printf("\n");//ini nanti diisi sama printf2 dari data yang telah diinput
    printf("                                      2) Pickup location      : "); printf("\n");
    printf("                                      3) Receiver's name      : "); printf("\n");
    printf("                                      4) Delivery address     : "); printf("\n");
    printf("\n");
    //nanti di sini mungkin pake function buat calculate price??
    printf("                                      Delivery fees : "); printf("\n");
    printf("                                      Delivery route  : "); printf("\n"); //ini kalau gamau gausah???
    printf("\n");
    system("pause"); //ini nanti tolong ilangin karena belom dimasukin scanf2 jd di pause dulu
}

int main()
{
    while(1){

        // Clear Screen
        clrscr();

        // Show Banner
        banner();

        // Show Main Menu
        menu_awal();
        scanf("%d", &choices); getchar();

        switch(pilihan){
            case 1 :
                system("cls");
                menu_customer();
                scanf("%d", &choices); fflush(stdin);
                switch(choices){
                    case 1 :
                        system("cls");
                        menu_send();
                        break;
                    case 2 :
                        //ini kalau mau pake status2an aja, kalo ga diilangin nanti
                        break;
                }
                break;
            case 2 :
                clrscr();
                menu_courier();
                scanf("%d", &choices); fflush(stdin);
                switch(choices){
                    case 1 :
                        system("cls");
                        menu_delivery();
                        break;
                    case 2 :
                        //ini kalau mau pake status2an aja, kalo ga diilangin nanti
                        break;
                }
                break;
                    case 3 :
                        exit(0);
        }
    }
    return 0;
}

void clrscr()
{
    system("cls");
}
