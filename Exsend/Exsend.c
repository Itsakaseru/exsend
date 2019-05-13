#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <stdbool.h>

///-----------------------------------------Global Variabel-----------------------------------------///
int choices;
int global_counter = 0;

// User Info
int user_count = 0;
int user_id[999];
char user[999][999];
char password[999][999];

// Delivery Info
int delivery_id[999];
int delivery_status[999];

// Distance Info
int graph[999][999];
int order_id[999];
int price_info[999][999];
char sender_name[999][999];
char receiver_name[999][999];
char sender_address[999][999];
char pickup_city[999][999];
char receive_address[999][999];
char receive_city[999][999];

// City Info
int city_id[999];
char city[999][999];

///---------------------------------------------Startup---------------------------------------------///

// Struct Declare
// (Linked List) Used for store readed city IDs and path

// File Read

void load_database()
{
	// Database File
	FILE *user_db;		// User Database
	FILE *delivery_db;	// Delivery Database
	FILE *city_db;		// City Name Database
	FILE *graph_db;		// Distance Graph Database


	//Declare Variable

	int counter_x = 0;
	int counter_y = 0;

	user_db = fopen("user.db", "r");
	delivery_db = fopen("delivery.db", "r");
	city_db = fopen("city.db", "r");
	graph_db = fopen("graph.db", "r");


	///-------------------------------Check for file availability-------------------------------///

	if(user_db == NULL)
	{
		printf("\n");
		printf("Error while opening user.db!");
		printf("\n");
		exit(5);
	}

	if(delivery_db == NULL)
	{
		printf("\n");
		printf("Error while opening delivery.db!");
		printf("\n");
		exit(5);
	}

	if(city_db == NULL)
	{
		printf("\n");
		printf("Error while opening city.db!");
		printf("\n");
		exit(5);
	}

	if(graph_db == NULL)
	{
		printf("\n");
		printf("Error while opening graph.db!");
		printf("\n");
		exit(5);
	}

	///-----------------------------------Read File to Memory-----------------------------------///

	// Read User Database to Memory
	while( (fscanf(user_db, "%d#%[^\#]#%[^\n]", &user_id, &user, &password)) != EOF )
	{
		user_count++;
	}

	// Read City Database to Memory
	while( (fscanf(city_db, "%d-%[^\n]", &city_id, &city[global_counter])) != EOF )
	{
		global_counter++;
	}

	// Read Distance Graph Database to Memory
	while( (fscanf(graph_db, "%d ", &graph[counter_y][counter_x])) != EOF )
	{
	    printf("[%d][%d] = %d", counter_y, counter_x, graph[counter_y][counter_x]); printf("\n");
		counter_x++;
		if(counter_x > global_counter-1)
		{
			counter_y++;
			counter_x = 0;
		}
	}

						///DEBUG
						for(int i = 0; i < user_count; i++)
						{
							printf("ID : %d", user_id[i]); printf("\n");
							printf("User : %s", user[i]); printf("\n");
							printf("Password : %s", password[i]); printf("\n");
						}

						for(int i = 0; i < global_counter; i++)
						{
							printf("ID : %d", i); printf("\n");
						    printf("%s \n", city[i]);
						}
						/*
						for(int i = 0; i < global_counter; i++)
						{
							for(int j = 0; j < global_counter; j++)
							{
						        printf("%d ", graph[i][j]);
							}
							printf("\n");
						}
						*/

}

void splash()
{
    printf("");
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
    load_database();
    /*while(1){

        // Clear Screen
        clrscr();

        // Show Banner
        banner();

        // Show Main Menu
        //menu_awal();
        //scanf("%d", &choices); getchar();

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
    return 0;*/
}

void clrscr()
{
    system("cls");
}
