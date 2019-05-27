///////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////                     EXSend Software   v2.0                  ///////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>
#include <windows.h>

///------------------------------------------------------------------ Global Variabel ------------------------------------------------------------------///

// Struct Declare
// Used to store directions to reach destination
struct route {
	char location_route[1][999];
	struct route *next, *prev;
};

// Variable Declare
int choices;                            // Store users choices
int corrupt;                            // For error checking by detecting infinite loop
int global_id;                          // Store IDs that indicate users location in program interaction
int search_check;                       // Use To check if the result of the search is either found or not found

double graph_check = 0;                 // For error checking graph database
double graph_count = 0;                 // For error checking graph database

// User Input
int input_check = 0;                    // Use to validate users total input in delivery form
int user_privelege = 0;                 // Use to indicate users privelege ( 0 = normal users, 1 = courier )

char input_user[1][999];                // Store users username input
char input_phone[1][999];               // Store users phone number input
char input_password[1][999];            // Store users password input

char input_sender_name[1][999];         // Store users sender name input
char input_receiver_name[1][999];       // Store users receiver name input
char input_sender_address[1][999];      // Store users sender address input
char input_sender_location[1][999];     // Store users sender location input
char input_receiver_address[1][999];    // Store users receiver address input
char input_receiver_location[1][999];   // Store users receiver location input

// User Info
int login_check = 0;                    // Use to validate user login information
int user_count = 0;                     // Use to count how many users are in the user database

int user_id[999];                       // Store users IDs from user database
int privelege[999];                     // Store users privelege from user database
char phone[999][999];                   // Store users phone number from user database

char user[999][999];                    // Store username information from user database
char password[999][999];                // Store password information from user database

// Order Info
int order_count = 0;                    // Use to count how many orders from order database
int input_price = 0;                    // Store price result from price algorithm after dijkstra algorithm
int location_check1 = 0;                // To keep track of data in new delivery input
int location_check2 = 0;                // To keep track of data in new delivery input
int user_order_count = 0;               // Use to count how many user order found in order database
int courier_order_count = 0;            // Use to count how many courier order found in order database

int order_id[999];                      // Store order IDs from order database
int graph[999][999];                    // Store graph information from graph database
int price_info[999];                    // Store prices from order database
int user_order_id[1][999];              // Store users order IDs, used as a pointer to point from normal printing number to database's actual IDs
int courier_order_id[1][999];           // Store courier order IDs, used as a pointer to point from normal printing number to database's actual IDs

char sender_name[999][999];             // Store sender name from order database
char order_status[999][999];            // Store orders status from order database
char order_assign[999][999];            // Store order assignment for courier from order database
char receiver_name[999][999];           // Store receiver's name from order database
char sender_address[999][999];          // Store sender address from order database
char pickup_location[999][999];         // Store sender pickup location from order database
char receiver_address[999][999];        // Store receiver's address from order database
char receiver_location[999][999];       // Store receiver's location from order database


// Location Info
int sord = 0;                           // Used for search algorithm to determine which's source or destination that need to be set
int page = 0;                           // Used for page counter
int page_check = 1;                     // Shows what page are user's in
int location_count = 0;                 // Used to count how many location from location database

int location_id[999];                   // Store location IDs from location database
char location[999][999];                // Store location name from location database

// Dijkstra Info
int node_count = 0;                     // Use to count how many location are in database
int source = 0;                         // Use to store source, used for dijkstra algorithm
int destination = 0;                    // Use to store destination, used for dijkstra algorithm
int d_count = 0;                        // Used for direction counter
int p_count = 0;                        // Used for direction path counter

int length[999];                        // Store how much path to reach the destination
int distance[999];                      // Store distance from own location(source) to destination
int route[999][999];                    // Store the direction to reach the destination
char route_conv[999][999];              // Use to read route IDs from route array to string into linked list

///---------------------------------------------------------------------- Startup ----------------------------------------------------------------------///

/// Load Database to Memory
void load_database()
{
	// Database File
	FILE *user_db;		// User Database
	FILE *order_db;	    // Order Database
	FILE *location_db;	// Location Name Database
	FILE *graph_db;		// Distance Graph Database

	//Declare Variable
	int counter_x = 0;
	int counter_y = 0;

	// Set file loader
	user_db     = fopen("user.txt", "r");
	order_db    = fopen("order.txt", "r");
	location_db = fopen("location.txt", "r");
	graph_db    = fopen("graph.txt", "r");

///------------------------------------------------------------ Check for file availability ------------------------------------------------------------///

	// Check for user.txt availability
	if (user_db == NULL)
	{
	    // Clear Screen
	    clrscr();

	    //Print Error
		printf("\n");
		printf("Error while opening user.txt!");
		printf("\n");
		system("pause");
		exit(5);
	}

	// Check for order.txt availability
	if (order_db == NULL)
	{
	    // Clear Screen
	    clrscr();

	    //Print Error
		printf("\n");
		printf("Error while opening order.txt!");
		printf("\n");
		system("pause");
		exit(5);
	}

	// Check for location.txt availability
	if (location_db == NULL)
	{
	    // Clear Screen
	    clrscr();

	    //Print Error
		printf("\n");
		printf("Error while opening location.txt!");
		printf("\n");
		system("pause");
		exit(5);
	}

	// Check for graph.txt availability
	if (graph_db == NULL)
	{
	    // Clear Screen
	    clrscr();

	    //Print Error
		printf("\n");
		printf("Error while opening graph.txt!");
		printf("\n");
		system("pause");
		exit(5);
	}

///----------------------------------------------------------------- Read File to Memory ----------------------------------------------------------------///

    // Variable set
    corrupt = 0;

	// Read User Database to Memory
	while ((fscanf(user_db, "%d#%[^\#]#%[^\#]#%[^\#]#%d", &user_id[user_count],
                &user[user_count], &password[user_count], &phone[user_count], &privelege[user_count])) != EOF)
	{
	    corrupt++;
		user_count++;

		// Error checking by detecting infinite loop
		if(corrupt > 999)
        {
            // Clear Screen
            clrscr();

            // Print Error
            printf("Invalid user database!");
            printf("\n");
            system("pause");
            exit(6);
        }
	}

	// Reset corrupt
	corrupt = 0;

	// Read order Database to Memory
	while ((fscanf(order_db, "%d#%[^\#]#%[^\#]#%[^\#]#%[^\#]#%[^\#]#%[^\#]#%[^\#]#%d#%[^\n]",
		&order_id[order_count], &order_status[order_count], &sender_name[order_count],
		&receiver_name[order_count], &sender_address[order_count], &pickup_location[order_count],
		&receiver_address[order_count], &receiver_location[order_count], &price_info[order_count], &order_assign[order_count])) != EOF)
	{
	    corrupt++;
		order_count++;

		// Error checking by detecting infinite loop
		if(corrupt > 999)
        {
            // Clear Screen
            clrscr();

            // Print Error
            printf("Invalid order database!");
            printf("\n");
            system("pause");
            exit(6);
        }
	}

	// Reset corrupt
	corrupt = 0;

	// Read Location Database to Memory
	while ((fscanf(location_db, "%d-%[^\n]", &location_id[location_count], &location[location_count])) != EOF)
	{
	    corrupt++;
		location_count++;
		node_count++;

		// Error checking by detecting infinite loop
		if(corrupt > 999)
        {
            // Clear Screen
            clrscr();

            // Print Error
            printf("Invalid user database!");
            printf("\n");
            system("pause");
            exit(6);
        }
	}

	// Reset corrupt
	corrupt = 0;

	// Read Distance Graph Database to Memory
	while ((fscanf(graph_db, "%d ", &graph[counter_y][counter_x])) != EOF)
	{
	    // Count until max counted location
		counter_x++;

		// count total integer that are scanned
		graph_count++;

		// Count
		if (counter_x > location_count - 1)
		{
		    // To count how many lines are in database
			counter_y++;

			// Reset x counter as max counter reached(max counted location)
			counter_x = 0;
		}
	}

    // Checker to make sure the number of location in a file corresponding to the number of nodes in graph
    // find how much nodes (root)
    graph_check += sqrt(graph_count);

    // Print error if result root from graph is not the same as counted location
    if(graph_check != location_count)
    {
        // Clear Screen
        clrscr();

        // Print Error
        printf("Invalid graph or location database!");
        printf("\n");
        system("pause");
        exit(6);
    }

    // Print error if total lines doesn't match the counted location
    if(counter_y != location_count)
    {
        // Clear Screen
        clrscr();

        // Print Error
        printf("Invalid graph or location database!");
        printf("\n");
        system("pause");
        exit(6);
    }

    // Database loaded
    // Close file
    fclose(user_db);
    fclose(order_db);
    fclose(location_db);
    fclose(graph_db);

}

void start_software()
{
    // Print EXSend Logo
    printf("########################################################################################################################");
    printf("########################################################################################################################");
    printf("################################# #################################      ###############################################");
    printf("#################################  ###############################      ################################################");
    printf("#################################    ############################      ### #############################################");
    printf("#################################      #########################      ###  #############################################");
    printf("#################################        ######        ########      ###   #############################################");
    printf("###################################        ######        #####      ###    #############################################");
    printf("#####################################        ######       ###      ###    ##############################################");
    printf("#######################################        ######      #      ###    ###############################################");
    printf("########################################         ######          ###     ###############################################");
    printf("##########################################         ######       ###     ################################################");
    printf("############################################         #####    ###      #################################################");
    printf("#############################################       ##############       ###############################################");
    printf("###########################################       #####   ##########       #############################################");
    printf("#########################################       #####        #########       ###########################################");
    printf("#######################################       #####     #      #########       #########################################");
    printf("#####################################       #####      ###       #########       #######################################");
    printf("#####################################     #####       #####        #########       #####################################");
    printf("#####################################   #####       ########         #########       ###################################");
    printf("##################################### #####       ######################################################################");
    printf("#########################################        #######################################################################");
    printf("########################################        ########################################################################");
    printf("######################################        ##########################################################################");
    printf("########################################################################################################################");
    printf("########################################################################################################################");
    printf("\n");
    printf("%*s", 75, "EXSend Delivery Software v2.0"); printf("\n");
    printf("\n");

    // Boot Animation with pre-determined delay
    Sleep(250);
    system("COLOR 09");
    printf("[=====================");
    Sleep(400);
    printf("===========================================");
    system("COLOR 03");

    // Load Database
    load_database();

    Sleep(150);
    printf("==============");
    Sleep(600);
    printf("==========");
    Sleep(500);
    system("COLOR 0B");
    printf("==============================]");
    Sleep(150);
}

void banner()
{
    // Print EXSend banner
	printf("=======================================================================================================================");  printf("\n");
	printf("\n");
	printf("#######################################################################################################################");  printf("\n");
	printf("##############################      ####  ###  ####     ####      ####  ####  ####     ################################");  printf("\n");
	printf("############################## ##########  #  #### ######### #########   ###  #### #### ###############################");  printf("\n");
	printf("##############################     #######  #######     ####     #####  # ##  #### #### ###############################");  printf("\n");
	printf("############################## ##########  #  #########  ### #########  ## #  #### #### ###############################");  printf("\n");
	printf("##############################      ####  ###  ####     ####      ####  ###   ####     ################################");  printf("\n");
	printf("#######################################################################################################################");  printf("\n");
	printf("%*s", 88, "\"Benar - benar yakin esok sampai\"");                                                                           printf("\n");
	printf("=======================================================================================================================");  printf("\n");
	printf("\n");
}

void start()
{
    // Variable Set
    global_id = -1;     // Indicated that users are in the start menu option screen

    // Clear Screen
    clrscr();

    //Show banner
    banner();

    // Print start menu
    printf("%*s", 72, "EXSend Delivery Software");  printf("\n");
    printf("\n");
    printf("%*s", 65, "1) Login  ");                printf("\n");
    printf("%*s", 65, "2) Sign Up");                printf("\n");
    printf("\n");
    printf("%*s", 65, "0) Exit   ");                printf("\n");
    printf("\n");
    printf("%*s", 64, "Choices : ");                scanf("%d", &choices);

    switch(choices)
    {
        case 1 :
        {
            // Go to Sign In screen
            login();
            break;
        }

        case 2 :
        {
            // Go to Registration Screen
            signup();
            break;
        }

        case 0 :
        {
            // Quit program
            exit(0);
            break;
        }

        default :
        {
            // Print invalid message
            invalid();

            // Recursive
            start();
            break;
        }
    }
}

void signup()
{
    // Variable Set
    global_id = 0;      // Indicates that user are in registration process

    // Clear Screen
    clrscr();

    //Show banner
    banner();

    printf("%*s", 64, "Sign Up");           printf("\n");
    printf("\n");

    fflush(stdin);
    printf("%*s", 61, "Username : ");       scanf("%[^\n]", &input_user);
	printf("%*s", 61, "Password : ");       scanf(" %[^\n]", &input_password);
	printf("%*s", 65, "Phone Number : ");   scanf("  %[^\n]", &input_phone);
	printf("\n");

	// Export data to file
	export_tofile();

	// Reload Database
	reset();
	load_database();

	// Print success message
    printf("%*s", 76, "You have successfully registered!");
    Sleep(1500);

    // Back to start menu screen
    start();
}

void login()
{
    // Variable Set
    global_id = 1;      // Indicated that user are in login validation screen
    login_check = 0;

    // Clear Screen
    clrscr();

    // Show banner
	banner();

	// Print Login Menu
    printf("%*s", 64, "Sign In");                                           printf("\n");
    printf("\n");

	fflush(stdin);
	printf("%*s", 60, "Username : ");   scanf("%[^\n]", &input_user);       getchar();
	printf("%*s", 60, "Password : ");   scanf("%[^\n]", &input_password);   getchar();

	/// Check Username and Password
	search(input_user);

    // If Username or Password are incorrect
    if(login_check == 0)
    {
        // Print error message
        printf("\n");
        printf("%*s", 76, "Incorrect Username or Password!");               printf("\n");
        Sleep(1000);
        start();
    }

    // If Username and Password are correct
    if(login_check == 1)
    {
        // Greets the user
        printf("\n");
        printf("%*s %s!", 62, "Welcome back", input_user);                  printf("\n");
        Sleep(1000);
        check_menu();
    }

}

void check_menu()
{
    // If Users show normal menu
    if(user_privelege == 1)
    {
        // Go to customer menu
        menu_customer();
    }

	//If Courier show courier menu
	if(user_privelege == 2)
    {
        // Got to courier menu
        menu_courier();
    }
}

void menu_customer()
{
    // Variable Set
    global_id = 4;      // Indicated user are in customer main menu

    // Clear Screen
    clrscr();

    // Show banner
	banner();

	// Show Menu
    printf("%*s", 72, "EXSend Delivery Software");  printf("\n");
    printf("\n");
	printf("%*s", 72, "1) EXSend Delivery      ");  printf("\n");
	printf("%*s", 72, "2) Delivery status check");  printf("\n");
	printf("%*s", 72, "0) Exit                 ");  printf("\n");
	printf("\n");
	printf("%*s", 65, "Choices : ");                scanf("%d", &choices);  getchar();

	// Check for user choices
	switch(choices)
	{
        case 1 :
        {
            // Go to EXSsend Delivery menu
            customer_delivery();
            break;
        }

        case 2 :
        {
            // Go to EXSend user delivery status check
            menu_ustatus();
            break;
        }

        case 0 :
        {
            // Quit the program
            exit(0);
            break;
        }

        default :
        {
            // Print invalid message
            invalid();
            menu_customer;
            break;
        }
	}
}

void customer_delivery()
{
    // Set Global ID
    global_id = 41;     // Indicates that user are in new delivery input screen

    // Clear Screen
    clrscr();

    // Show banner
	banner();

	// To make sure that users need to fill all data before dijkstra algorithm run
	if(location_check1 == 1 && location_check2 == 1 && input_check > 2)
    {
        input_check += 2;
    }

	if(input_check >= 5)
    {
        /// Run Dijkstra
        dijkstra();

        /// Calculate estimated price
        input_price = ( distance[destination] * 1000 );
    }

    // Print form
    printf("%*s", 68,"Delivery Request");                                               printf("\n");
    printf("\n");

    printf("%*s %s", 70, "1) Sender's name                : ", input_user);             printf("\n");
    printf("%*s %s", 70, "2) Sender's pick up location    : ", input_sender_location);  printf("\n");
    printf("%*s %s", 70, "3) Sender's address             : ", input_sender_address);   printf("\n");
	printf("\n");
	printf("%*s %s", 70, "4) Receiver's name              : ", input_receiver_name);    printf("\n");
	printf("%*s %s", 70, "5) Receiver's delivery location : ", input_receiver_location);printf("\n");
    printf("%*s %s", 70, "6) Receiver's address           : ", input_receiver_address); printf("\n");

	printf("\n");

	printf("%*s Rp %d", 70, "Estimated Delivery fees         : ", input_price);         printf("\n");

	// Print Confirm Order if users filled in the necessary data
	if(input_check >= 5)
    {
        printf("\n");
        printf("%*s", 80, "7) Confirm Order         0) Back to menu");                  printf("\n");
    }

    // Print only back to menu if users hadn't filled in all the necessary data
    if(input_check < 5)
    {
        printf("\n");
        printf("%*s", 68, "0) Back to menu");                                           printf("\n");
    }

    printf("\n");

    // Demand user input
    printf("%*s", 65, "Choices : ");                                                    scanf("%d", &choices);  getchar();

	// If user decided to confirm and to make sure users are not able to choose 7 before filling all the necessary data
	if(input_check >= 5)
    {
        if(choices == 7)
        {
            // Check if pickup location the same as receive location
            // To make sure that users doesn't input the same location
            if(strcmp(input_sender_location, input_receiver_location) == 0)
            {
                // Clear Screen
                clrscr();

                // Show banner
                banner();

                // Print invalid input to user
                printf("\n\n\n");
                printf("%*s", 88, "Pickup location can't be the same as receiver location!");   printf("\n");
                Sleep(1000);

                // Go back to new delivery input screen
                customer_delivery();
            }

            // Export to file
            export_tofile();

            // Reset variable
            reset();

            // Reset all input
            strcpy(input_sender_address, " ");
            strcpy(input_sender_location, " ");
            strcpy(input_receiver_name, " ");
            strcpy(input_receiver_location, " ");
            strcpy(input_receiver_address, " ");
            input_price = 0;
            input_check = 0;
            location_check1 = 0;
            location_check2 = 0;

            // Reload database
            load_database();

            // Clear Screen
            clrscr();

            // Show banner
            banner();

            // Show users that the order has been placed
            printf("\n\n");
            printf("%*s", 75, "Your order has been recorded!");             printf("\n");
            printf("%*s", 79, "We will notify you when we are ready.");     printf("\n");
            getch();

            // Back to menu
            menu_customer();
        }
    }

    // Go to menu according to users choices
	switch(choices)
	{
        case 2 :
        {
            delivery_location();
            break;
        }

        case 3 :
        {
            delivery_address();
            break;
        }

        case 4 :
        {
            delivery_name();
            break;
        }

        case 5 :
        {
            delivery_location();
            break;
        }

        case 6 :
        {
            delivery_address();
            break;
        }

        case 0 :
        {
            // Reset all input
            strcpy(input_sender_address, " ");
            strcpy(input_sender_location, " ");
            strcpy(input_receiver_name, " ");
            strcpy(input_receiver_location, " ");
            strcpy(input_receiver_address, " ");
            input_price = 0;
            input_check = 0;
            location_check1 = 0;
            location_check2 = 0;
            menu_customer();
            break;
        }

        default :
        {
            // Print invalid message
            invalid();
            customer_delivery();
            break;
        }
	}

}

void delivery_name()
{
    global_id = 411;        // Indicates that user are inputing receiver's name

    switch(choices)
    {
        case 4 :
        {
            // Clear Screen
            clrscr();

            // Show banner
            banner();

            // Demand user input
            printf("\n\n\n");
            printf("%*s", 68, "Receiver's name                : "); scanf("%[^\n]", input_receiver_name);   getchar();

            // Check if users input is not empty
            if(strlen(input_receiver_name) != 0)
            {
                input_check++;
            }

            // Back to delivery menu
            customer_delivery();
            break;
        }
    }

}

void delivery_location()
{
    global_id = 412;        // Indicates that user are in location picker screen

    // Reset
    reset();

    // Reload Database
    load_database();

    int count;
    int local_choices;
    int local_count = 0;
    int total_page = 1;

    // Seek how many page are needed
    for(count = 1; count < location_count; count++)
    {
        if(count >= 5*total_page)
        {
            total_page++;
        }
    }

    switch(choices)
    {
        case 2 :
        {
            // Clear Screen
            clrscr();

            // Show banner
            banner();

            printf("%*s", 68, "Pickup Location");                       printf("\n");
            printf("\n");

            // Print all available location
            for(count = 0+(page*5); count < location_count; count++)
            {
                if(count >= page_check*5)
                {
                    local_count = 0;
                    break;
                }

                printf("%*d) %s", 55, local_count+1, location[count]);  printf("\n");
                local_count++;
            }

            // Demand user input
            printf("\n");
            printf("%*d/%d", 60, page_check, total_page);               printf("\n");
            printf("\n");
            printf("%*s", 78, "6) Previous Page        7) Next Page");  printf("\n");
            printf("\n");
            fflush(stdin);
            printf("%*s", 73, "Choose pickup location : ");             scanf("%d", &local_choices);    getchar();

            if(local_choices == 6)
            {
                if(page_check != 1)
                {
                    page--;
                    page_check--;
                    delivery_location();
                }
                else
                {
                    delivery_location();
                }
            }
            if(local_choices == 7)
            {
                if(page_check < total_page)
                {
                    page++;
                    page_check++;
                    delivery_location();
                }
                else
                {
                    delivery_location();
                }
            }

            // Seek choices according to local_choices and page
            choices = local_choices+(page*5);

            // Choices to IDs converter
            choices--;
            strcpy(input_sender_location, location[choices]);

            // Set source to user_input
            source = choices;

            // Back to delivery menu
            page_check = 1;
            page = 0;
            location_check1 = 1;
            customer_delivery();
            break;
        }

        case 5 :
        {
            // Clear Screen
            clrscr();

            // Show banner
            banner();

            printf("%*s", 70, "Receiver's Location");                   printf("\n");
            printf("\n");

            // Print all available location
            for(count = 0+(page*5); count < location_count; count++)
            {
                if(count >= page_check*5)
                {
                    local_count = 0;
                    break;
                }

                printf("%*d) %s", 55, local_count+1, location[count]);  printf("\n");
                local_count++;
            }

            // Demand user input
            printf("\n");
            printf("%*d/%d", 60, page_check, total_page);               printf("\n");
            printf("\n");
            printf("%*s", 78, "6) Previous Page        7) Next Page");  printf("\n");
            printf("\n");
            fflush(stdin);
            printf("%*s", 73, "Choose receiver's location : ");         scanf("%d", &local_choices);    getchar();

            if(local_choices == 6)
            {
                if(page_check != 1)
                {
                    page--;
                    page_check--;
                    delivery_location();
                }
                else
                {
                    delivery_location();
                }
            }
            if(local_choices == 7)
            {
                if(page_check < total_page)
                {
                    page++;
                    page_check++;
                    delivery_location();
                }
                else
                {
                    delivery_location();
                }
            }

            // Seek choices according to local_choices and page
            choices = local_choices+(page*5);

            // Choices to IDs converter
            choices--;
            strcpy(input_receiver_location, location[choices]);

            // Set destination to user_input
            destination = choices;

            // Back to delivery menu
            page_check = 1;
            page = 0;
            location_check2 = 1;
            customer_delivery();
            break;
        }
    }
}

void delivery_address()
{
    global_id = 413;        // Indicates that user are in address input screen

    switch(choices)
    {
        case 3 :
        {
            // Clear Screen
            clrscr();

            // Show banner
            banner();

            // Demand user input
            printf("\n\n\n");
            printf("%*s", 68, "Sender's address                  : ");      scanf("%[^\n]", input_sender_address);      getchar();

            // Check if users input is not empty
            if(strlen(input_sender_address) != 0)
            {
                input_check++;
            }

            // Back to delivery menu
            customer_delivery();
            break;
        }

        case 6 :
        {
            // Clear Screen
            clrscr();

            // Show banner
            banner();

            // Demand user input
            printf("\n\n\n");
            printf("%*s", 68, "Receiver's address                  : ");    scanf("%[^\n]", input_receiver_address);    getchar();

            // Check if users input is not empty
            if(strlen(input_receiver_address) != 0)
            {
                input_check++;
            }

            // Back to delivery menu
            customer_delivery();
            break;
        }
    }
}

void menu_ustatus()
{
    // Variable Set
    global_id = 42;     // Indicates that user are in status check screen

    // Clear Screen
    clrscr();

    // Print Banner
    banner();

    // Print Menu
    printf("%*s", 66, "Order  List");   printf("\n");
	printf("\n");

    // Show only users order
    search(input_user);

    // Print Exit option
    printf("\n");
    printf("%*s", 64, "0) Exit");
    printf("\n");

    // Demand input
    printf("\n");
    printf("%*s", 65, "Choices : ");   scanf("%d", &choices); getchar();

    if(choices > user_order_count)
    {
        // Print invalid message
        invalid();

        // Reset order_count
        user_order_count = 0;

        menu_ustatus();
    }

    // Reset order_count
    user_order_count = 0;
    printf("\n");

    order_show();
}

void order_show()
{
    // Declare
    int id = choices-1;

    // Clear Screen
    clrscr();

    // Print Banner
    banner();

    // Convert choices to order IDs
    id = user_order_id[1][id];

    // Back to menu
    if(choices == 0)
    {
        menu_customer();
    }

    // Print Order Information
    printf("%*s #%d", 62, "Order", choices);                                             printf("\n");
    printf("\n");

    printf("%*s %s", 65, "1) Sender's name                : ", sender_name[id]);        printf("\n");
    printf("%*s %s", 65, "2) Sender's pick up location    : ", pickup_location[id]);    printf("\n");
    printf("%*s %s", 65, "3) Sender's address             : ", sender_address[id]);     printf("\n");
	printf("\n");
	printf("%*s %s", 65, "4) Receiver's name              : ", receiver_name[id]);      printf("\n");
	printf("%*s %s", 65, "5) Receiver's delivery location : ", receiver_location[id]);  printf("\n");
    printf("%*s %s", 65, "6) Receiver's address           : ", receiver_address[id]);   printf("\n");

	printf("\n");

	printf("%*s Rp %d", 65, "Estimated Delivery fees         : ", price_info[id]);      printf("\n");
	printf("%*s %s", 65, "Status                          : ", order_status[id]);       printf("\n");
	printf("\n");
	printf("%*s", 74, "Press any key to got back...");                                  getch();

	// Back to user order status
	menu_ustatus();
}

void menu_courier()
{
    // Variable Set
    global_id = 42;     // Indicates that courier are in main menu screen
    int counter;        // Local counter variable

    // Clear Screen
    clrscr();

    // Print Banner
    banner();

    // Print Menu
    printf("%*s", 66, "Order  List");                       printf("\n");
    printf("\n");

    printf("%*s", 70, "1) Pending ( Assigned )");           printf("\n");
    printf("%*s", 72, "2) Delivered ( Assigned )");         printf("\n");
    printf("\n");
    printf("%*s", 72, "3) Show All Pending Order");         printf("\n");
    printf("%*s", 73, "4) Show All Delivery Order");        printf("\n");
    printf("\n");
    printf("%*s", 54, "0) Exit");                           printf("\n");
    printf("\n");

    printf("%*s", 65, "Choices : ");scanf("%d", &choices);  getchar();

    switch(choices)
    {
        case 1 :
        {
            global_id = 421;
            order_list_pending();
            break;
        }

        case 2 :
        {
            global_id = 422;
            order_list_delivered();
            break;
        }

        case 3 :
        {
            global_id = 423;
            order_list_pending();
            break;
        }
        case 4 :
        {
            global_id = 424;
            order_list();
            break;
        }

        case 0 :
        {
            exit(0);
            break;
        }

        default :
        {
            // Print error message
            invalid();
            menu_courier();
            break;
        }
    }
}

void order_list_pending()
{
    // Clear Screen
    clrscr();

    // Print Banner
    banner();

    if(global_id == 421)
    {
        // Print Menu
        printf("%*s", 70, "Assigned Order  List");      printf("\n");
        printf("%*s", 65, "(Pending)");                 printf("\n");
        search(input_user);
    }

    if(global_id == 423)
    {
        // Print Menu
        printf("%*s", 66, "Order  List");               printf("\n");
        printf("%*s", 65, "(Pending)");               printf("\n");
        search(input_user);
    }

    // Print Exit option
    printf("\n");
    printf("%*s", 68, "0) Back to menu");
    printf("\n");

    // Demand input
    printf("\n");
    printf("%*s", 65, "Choices : ");                scanf("%d", &choices);  getchar();

    if(choices == 0)
    {
        // Back to main menu
        menu_courier();
    }
    if(choices > courier_order_count)
    {
        invalid();
        courier_order_count = 0;
        menu_courier();
    }

    // Reset order count
    courier_order_count = 0;

    printf("\n");

    // Show delivery information according to user choices
    delivery_show();
}

void order_list_delivered()
{
    // Clear Screen
    clrscr();

    // Print Banner
    banner();

    if(global_id == 422)
    {
        // Print Menu
        printf("%*s", 70, "Assigned Order  List");      printf("\n");
        printf("%*s", 66, "(Delivered)");               printf("\n");
        search(input_user);
    }

    if(global_id == 424)
    {
        // Print Menu
        printf("%*s", 66, "Order  List");               printf("\n");
        printf("%*s", 66, "(Delivered)");               printf("\n");
        search(input_user);
    }

    // Print Exit option
    printf("\n");
    printf("%*s", 68, "0) Back to menu");
    printf("\n");

    // Demand input
    printf("\n");
    printf("%*s", 65, "Choices : ");                scanf("%d", &choices);  getchar();

    if(choices == 0)
    {
        // Back to main menu
        menu_courier();
    }
    if(choices > courier_order_count)
    {
        invalid();
        courier_order_count = 0;
        menu_courier();
    }

    // Reset order count
    courier_order_count = 0;

    printf("\n");

    // Show delivery information according to user choices
    delivery_show();
}

void order_list()
{
    // Variable Set and Declare
    int counter;
    global_id = 5;      // Indicates that user are viewing all orders

    // Clear Screen
    clrscr();

    // Show banner
    banner();

    // Print Menu
    printf("%*s", 66, "Order  List");   printf("\n");
    printf("%*s", 63, "(All)");         printf("\n");

    // Print formatting
    printf("\t\t\t\t   ");
    printf("----------------------------------------------------"); printf("\n\t\t\t\t   ");
    printf("| ID  |        Name        |        Status         |"); printf("\n\t\t\t\t   ");
    printf("----------------------------------------------------"); printf("\n");

	for(counter = 0; counter < order_count; counter++)
    {
        printf("\t\t\t\t   ");
        printf("| %03d | %-18s | %-21s |", counter+1, sender_name[counter], order_status[counter]); printf("\n");
    }
    printf("\t\t\t\t   ");
    printf("----------------------------------------------------");
    printf("\n");

    // Print exit option
    printf("%*s", 64, "0) Exit");                                   printf("\n");
	printf("\n");

	// Demand user input
	fflush(stdin);
	printf("%*s", 65, "Choices : ");                                scanf("%d", &choices);          getchar();

	// Exit to main menu
	if(choices == 0)
    {
        menu_courier();
    }

    if(choices > order_count)
    {
        invalid();
        menu_courier();
    }

	// Check for user choices
    delivery_show();
}

void delivery_show()
{
    // Declare variable and set
    int id;
    id = choices-1;

    // Clear Screen
    clrscr();

    // Show banner
    banner();

    // Convert choices to order IDs
    if(global_id != 5)
    {
        // Use pointer to determine IDs
        id = courier_order_id[1][id];
    }

    if(choices == 0)
    {
        // Back to menu
        menu_courier();
    }

    // Print Order Information
    printf("%*s #%d", 62, "Order", choices); printf("\n");
    printf("\n");

    printf("%*s %s", 65, "1) Sender's name                : ", sender_name[id]);        printf("\n");
    printf("%*s %s", 65, "2) Sender's pick up location    : ", pickup_location[id]);    printf("\n");
    printf("%*s %s", 65, "3) Sender's address             : ", sender_address[id]);     printf("\n");
	printf("\n");
	printf("%*s %s", 65, "4) Receiver's name              : ", receiver_name[id]);      printf("\n");
	printf("%*s %s", 65, "5) Receiver's delivery location : ", receiver_location[id]);  printf("\n");
    printf("%*s %s", 65, "6) Receiver's address           : ", receiver_address[id]);   printf("\n");

	printf("\n");

	printf("%*s Rp %d", 65, "Estimated Delivery fees         : ", price_info[id]);      printf("\n");
	printf("%*s %s", 65, "Status                          : ", order_status[id]);       printf("\n");
	printf("\n");

	printf("%*s", 68, "1) Change Status"); printf("\n");
	printf("%*s", 65, "2) Directions"); printf("\n");

	if(strcmp(input_user, order_assign[id]) != 0)
    {
        printf("%*s", 63, "3) Take Job"); printf("\n");
    }
	printf("%*s", 67, "0) Back to menu"); printf("\n");

    printf("%*s", 65, "Choices : "); scanf("%d", &choices);

	switch(choices)
	{
        case 1 :
        {
            // Go to courier change status menu
            menu_cstatus(id);
            break;
        }
        case 2 :
        {
            // Reset variable
            p_count = 0;
            d_count = 0;

            // Go to directions info
            show_direction(id);
            break;
        }
        case 3 :
        {
            // Make sure that courier hasn't take this job
            if(strcmp(input_user, order_assign[id]) != 0)
            {
                // Set global id
                global_id= 510;     // Indicates that taking job process started
                modify_memory(id);  // Modify memory
                reset();            // Reset variable
                load_database();    // Reload database
                menu_courier();     // Go back to courier main menu
            }
            break;
        }
        case 0 :
        {
            // Go back to courier main menu
            menu_courier();
            break;
        }

        default :
        {
            // Print invalid message
            invalid();
            menu_courier();
            break;
        }
	}

}

void menu_cstatus(int *input)
{
    // Declare variable and set
    global_id = 511;        // Indicates that user are in change status screen
    int id;

    id = input;
    id++;

    // Clear Screen
    clrscr();

    // Show banner
    banner();

    // Print Order Information
    printf("%*s #%d", 62, "Order", id); printf("\n");
    printf("\n");

    printf("%*s", 67, "Change Status"); printf("\n");
    printf("\n");

    printf("%*s", 63, "1) Pending"); printf("\n");
    printf("%*s", 65, "2) Delivered"); printf("\n");

    // Print available location
    for(int count = 0; count < node_count; count++)
    {
        printf("%*d) %s", 54, count+3, location[count]); printf("\n");
    }

    printf("\n");
    printf("%*s", 64, "0) Exit"); printf("\n");
	printf("\n");

	printf("%*s", 65, "Choices : "); scanf("%d", &choices); getchar();

	if (choices == 0)
	{
	    // Go back to menu
		menu_courier();
	}

	// Modify IDs variable to match the IDs in memory
    id--;

    // Modify corresponding data in memory
    modify_memory(id);

    // Back to courier menu
    menu_courier();
}

void search(char *search)
{
	// Declare variable
    int counter;            // Local counter
	int local_check = 0;    // Check users input
	int local_choices;      // Store user choices locally
    int total_page = 1;     // Set total page to 1

	/// Sequential Search
	switch(global_id)
	{
	    // Searching for username and password
        case 1 :
        {
            for(counter = 0; counter < user_count; counter++)
            {
                if (strcmp(search, user[counter]) == 0 && strcmp(input_password, password[counter]) == 0)
                    {
                         login_check = 1;
                         user_privelege = privelege[counter];
                    }
            }
            break;
        }

        // Searching for source and destination
        case 512 :
        {
            for(counter = 0; counter < location_count; counter++)
            {
                if (strcmpi(search, location[counter]) == 0)
                    {
                         if(sord == 0)
                         {
                             source = counter;
                         }
                         if(sord == 1)
                         {
                             destination = counter;
                         }
                    }
            }
            break;
        }

        // Searching for orders with certain criteria
        case 42 :
        {
            // Print Formatting
            printf("\t\t     ");
            printf("--------------------------------------------------------------------------------"); printf("\n\t\t     ");
            printf("| ID  |         Status         |       Name       |         Destination        |"); printf("\n\t\t     ");
            printf("--------------------------------------------------------------------------------"); printf("\n");
            for(counter = 0; counter < order_count; counter++)
            {
                if (strcmp(search, sender_name[counter]) == 0)
                    {
                        local_check = 1;
                        user_order_id[1][user_order_count] = counter;
						user_order_count++;
						printf("\t\t     ");
						printf("| %03d | %-22s | %-16s | %-26s |", user_order_count, order_status[counter],
                                receiver_name[counter], receiver_location[counter]); printf("\n");
                    }
            }
            printf("\t\t     ");
            printf("--------------------------------------------------------------------------------"); printf("\n");

            // Check if users order list is empty
            if(local_check == 0)
            {
                printf("\n");
                printf("%*s", 73, "Your order list is empty!");
                printf("\n");
            }
            break;
        }

        // Searching for orders with certain criteria
        case 421 :
        {
            // Print formatting
            printf("\t\t\t\t   ");
            printf("----------------------------------------------------"); printf("\n\t\t\t\t   ");
            printf("| ID  |        Name        |        Status         |"); printf("\n\t\t\t\t   ");
            printf("----------------------------------------------------"); printf("\n");
            for(counter = 0; counter < order_count; counter++)
            {
                if (strcmp(search, order_assign[counter]) == 0 && strcmp(order_status[counter], "Delivered") != 0)
                    {
                        local_check = 1;
                        courier_order_id[1][courier_order_count] = counter;
						courier_order_count++;
						printf("\t\t\t\t   ");
						printf("| %03d | %-18s | %-21s |", courier_order_count, sender_name[counter], order_status[counter]); printf("\n");
                    }
            }
            printf("\t\t\t\t   ");
            printf("----------------------------------------------------"); printf("\n");

            // Check if users order list is empty
            if(local_check == 0)
            {
                printf("\n");
                printf("%*s", 82, "There are no pending order assigned for you!");
                printf("\n");
            }


            break;
        }

        // Searching for orders with certain criteria
        case 422 :
        {
            // Print formatting
            printf("\t\t\t\t   ");
            printf("----------------------------------------------------"); printf("\n\t\t\t\t   ");
            printf("| ID  |        Name        |        Status         |"); printf("\n\t\t\t\t   ");
            printf("----------------------------------------------------"); printf("\n");
            for(counter = 0; counter < order_count; counter++)
            {
                if (strcmp(search, order_assign[counter]) == 0 && strcmp(order_status[counter], "Delivered") == 0)
                    {
                        local_check = 1;
                        courier_order_id[1][courier_order_count] = counter;
						courier_order_count++;
						printf("\t\t\t\t   ");
						printf("| %03d | %-18s | %-21s |", courier_order_count, sender_name[counter], order_status[counter]); printf("\n");
                    }
            }
            printf("\t\t\t\t   ");
            printf("----------------------------------------------------"); printf("\n");

            // Check if users order list is empty
            if(local_check == 0)
            {
                printf("\n");
                printf("%*s", 78, "No assigned delivered order found!");
                printf("\n");
            }
            break;
        }

        // Searching for orders with certain criteria
        case 423 :
        {
            // Print formatting
            printf("\t\t\t\t   ");
            printf("----------------------------------------------------"); printf("\n\t\t\t\t   ");
            printf("| ID  |        Name        |        Status         |"); printf("\n\t\t\t\t   ");
            printf("----------------------------------------------------"); printf("\n");
            for(counter = 0; counter < order_count; counter++)
            {
                if (strcmp(order_status[counter], "Pending") == 0 && strcmp(order_assign[counter], "none") == 0 || strcmp(order_status[counter], "Delivered") != 0 && strcmp(order_assign[counter], "none") == 0 )
                    {
                        local_check = 1;
                        courier_order_id[1][courier_order_count] = counter;
						courier_order_count++;
						printf("\t\t\t\t   ");
						printf("| %03d | %-18s | %-21s |", courier_order_count, sender_name[counter], order_status[counter]); printf("\n");
                    }
            }
            printf("\t\t\t\t   ");
            printf("----------------------------------------------------"); printf("\n");

            // Check if users order list is empty
            if(local_check == 0)
            {
                printf("\n");
                printf("%*s", 78, "No assigned pending order found!");
                printf("\n");
            }
            break;
        }

        // Searching for orders with certain criteria
        case 424 :
        {
            // Print formatting
            printf("\t\t\t\t   ");
            printf("----------------------------------------------------"); printf("\n\t\t\t\t   ");
            printf("| ID  |        Name        |        Status         |"); printf("\n\t\t\t\t   ");
            printf("----------------------------------------------------"); printf("\n");
            for(counter = 0; counter < order_count; counter++)
            {
                if (strcmp(order_status[counter], "Delivered") == 0)
                    {
                        local_check = 1;
                        courier_order_id[1][courier_order_count] = counter;
						courier_order_count++;
						printf("\t\t\t\t   ");
						printf("| %03d | %-18s | %-21s |", courier_order_count, sender_name[counter], order_status[counter]); printf("\n");
                    }
            }
            printf("\t\t\t\t   ");
            printf("----------------------------------------------------"); printf("\n");

            // Check if users order list is empty
            if(local_check == 0)
            {
                printf("\n");
                printf("%*s", 78, "No delivered order found!");
                printf("\n");
            }
            break;
        }
    }
}

/// Dijkstra Algorithm
int minDistance(int dist[],bool sptSet[])
{
    // Initialize min value
    int min = INT_MAX, min_index;

    for (int v = 0; v < node_count; v++)
        if (sptSet[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;

    return min_index;
}

void export_route(int parent[], int j)
{
    if (parent[j] == - 1)
    {
        return;
    }

    // Recursive
    export_route(parent, parent[j]);

    // Store path to memory
    route[d_count][p_count] = j;

    // Counter
    p_count++;

}

int export_dijkstra(int dist[], int n, int parent[])
{
    for (int i = 0; i < node_count; i++)
    {
        // Store distance to memory
        distance[i] = dist[i];

        // Add Source to path
        route[d_count][p_count] = source;
        p_count++;

        // Store how much path are in memory
        length[i] = p_count;

        // Export path to memory
        export_route(parent, i);

        // Store how much path are in memory
        length[i] = p_count;

        // Reset and counter
        p_count = 0;
        d_count++;
    }
}

void dijkstra()
{
    // store shortest distance
    int dist[node_count];

    // Declare sptSet
    bool sptSet[node_count];

    // Store shortest path tree
    int parent[node_count];

    // Initialize all distances as infinite and set sptSet to false
    for (int i = 0; i < node_count; i++)
    {
        parent[source] = -1;
        dist[i] = INT_MAX;
        sptSet[i] = false;
    }

    // Set distance from source to source is 0
    dist[source] = 0;

    // Find shortest path from all vertex
    for (int count = 0; count < node_count - 1; count++)
    {
        // Choose minimum distance
        int u = minDistance(dist, sptSet);

        // Set the chosen vertex to true
        sptSet[u] = true;

        // Update distance value
        for (int v = 0; v < node_count; v++)

            // Update if not in sptSet
            if (!sptSet[v] && graph[u][v] &&
                dist[u] + graph[u][v] < dist[v])
            {
                parent[v] = u;
                dist[v] = dist[u] + graph[u][v];
            }
    }

    // Export result to memory
    export_dijkstra(dist, node_count, parent);
}

void modify_memory(int *id)
{
    // Declare and set variable
    int local_id;
    local_id = id;

    switch(global_id)
    {
        // Change status
        case 511 :
        {
            if(choices == 1)
            {
                strcpy(order_status[local_id], "Pending");
                break;
            }
            if(choices == 2)
            {
                strcpy(order_status[local_id], "Delivered");
                break;
            }
            else
            {
                choices = choices - 3;
                strcpy(order_status[local_id], location[choices]);
                break;
            }
            break;
        }

        // Set order assignment
        case 510 :
        {
            strcpy(order_assign[local_id], input_user);
            break;
        }
    }

    // Overwrite database from memory
    overwrite_tofile();
}

void export_tofile()
{
	// Database File
	FILE *user_db;		// User Database
	FILE *order_db;	    // Order Database
	FILE *location_db;  // Location Name Database
	FILE *graph_db;		// Distance Graph Database

	// Set file loader and open file
	user_db     = fopen("user.txt", "a");
	order_db    = fopen("order.txt", "a");
	location_db = fopen("location.txt", "a");
	graph_db    = fopen("graph.txt", "a");

    switch(global_id)
    {
        // Export user new delivery order
        case 41 :
        {
            fprintf(order_db, "\n%d#Pending#%s#%s#%s#%s#%s#%s#%d#none",
                    order_count, input_user, input_receiver_name, input_sender_address,
                    input_sender_location, input_receiver_address, input_receiver_location, input_price);
            break;
        }

        // Export new user information
        case 0 :
        {
            user_count++;

            fprintf(user_db, "\n%d#%s#%s#%s#1",
                    user_count, input_user, input_password, input_phone);
            break;
        }

    }

    // Close file
    fclose(user_db);
    fclose(order_db);
    fclose(location_db);
    fclose(graph_db);
}

void overwrite_tofile()
{
    // Declare variable
    int counter;        // Local counter

    // Database File
	FILE *user_db;		// User Database
	FILE *order_db;	    // Order Database
	FILE *location_db;  // Location Name Database
	FILE *graph_db;		// Distance Graph Database

	// Set file loader
    if(global_id == 511 || 510)
    {
        order_db = fopen("order.txt", "w");
    }

    // Overwrite database from memory
	switch(global_id)
	{
	    // Rewrite all memory data to order database(Change status)
        case 511 :
        {
            for(counter = 0; counter < order_count; counter++)
            {
                fprintf(order_db, "%d#%s#%s#%s#%s#%s#%s#%s#%d#%s\n",
                    order_id[counter], order_status[counter], sender_name[counter],
                    receiver_name[counter], sender_address[counter], pickup_location[counter],
                    receiver_address[counter], receiver_location[counter], price_info[counter], order_assign[counter]);
            }
            break;
        }

        // Rewrite all memory data to order database(change order assignment)
        case 510 :
        {
            for(counter = 0; counter < order_count; counter++)
            {
                fprintf(order_db, "%d#%s#%s#%s#%s#%s#%s#%s#%d#%s\n",
                    order_id[counter], order_status[counter], sender_name[counter],
                    receiver_name[counter], sender_address[counter], pickup_location[counter],
                    receiver_address[counter], receiver_location[counter], price_info[counter], order_assign[counter]);
            }
            break;
        }
	}

    // Close file
    fclose(order_db);
}

void show_direction(int *input)
{
    // Declare Variable
    global_id = 512;        // Indicates that courier is in directions information screen

    int local_input;
    int local_count = 0;    // Local counter
    int counter = 0;        // Local additional counter
    int insert = 0;         // Use for linked list
    int page = 1;           // Set to page 1
    sord = 0;               // 0 = Set to source || 1 = Set to destination (Used to set source and destination variable)

    local_input = input;

    // Declare struct
    struct route *head, *node, *tail, *curr;

    // Set head to NULL
    head = NULL;

    /// Read Array and do search determine source and destination
    search(pickup_location[local_input]);
    sord++;
    search(receiver_location[local_input]);

    /// Run Dijkstra Algorithm
    dijkstra();

    /// Add Linked List
    for(counter = 0; counter < length[destination]; counter++)
    {
        node = (struct route*) malloc(sizeof(struct route));
        node->next = NULL;
        node->prev = NULL;

        insert =  route[destination][counter];
        strcpy(node->location_route, location[insert]);

        if(head == NULL)
        {
            head = node;
            tail = node;
        }
        else{
            tail->next = node;
            node->prev = tail;
            tail = node;
        }
    }

    // Set curr to head, for printing/showing data purpose
    curr = head;

    // Print Directions
    while(1)
    {
        // Clear Screen
        clrscr();

        // Show banner
        banner();
        printf("%*s", 68, "================");                  printf("\n");
        printf("%*s   #%03d |", 59, "| Order", local_input+1);  printf("\n");
        printf("%*s", 68, "================");                  printf("\n");
        printf("\n");
        printf("%*s #%03d", 62, "Direction", local_count+1);    printf("\n");
        printf("\n");

        // To make set text alignment to middle by calculate from total width and total character
        int count;  // Local counter
        count = ((120-strlen(curr->location_route)) / 2 + strlen(curr->location_route));
        printf("%*s", count, curr->location_route);             printf("\n");

        printf("\n");

        printf("%*s", 82,"1) Previous Direction      2) Next Direction");                printf("\n");
        printf("\n");
        printf("%*s", 64,"0) Exit");                            printf("\n");

        printf("\n");
        printf("%*s", 65, "Choices : ");                        scanf("%d", &choices);   getchar();

        if(choices == 2)
        {
            if(curr->next == NULL)
            {
                // Print message error message indicates
                // That this is the final linked list
                printf("%*s", 76, "Already at the final destination");
                getch();
            }
            else
            {
                // Next directions
                local_count++;
                curr = curr->next;
            }
        }
        else if(choices == 1)
        {
            if(curr->prev == NULL)
            {
                // Print message error message indicates
                // That this is the first linked list
                printf("%*s", 76, "Already at the first destination");
                getch();
            }
            else
            {
                // Next directions
                local_count--;
                curr = curr->prev;
            }
        }
        else if(choices == 0 || choices > 2 || choices < 0)
        {
            // Clear Linked List
            while(head != NULL)
            {
                curr = head;
                head = head->next;
                free(curr);
            }
            // Exit to courier menu
            menu_courier();
        }
    }
}

int main()
{
    // Set color to default, resize console, and enable custom buffer size
    system("MODE 120, 30, 1");
    set_color();

    // Clear Screen
    clrscr();

    // Load database
	start_software();

	// Go to start menu
    start();
}

void reset()
{
    // Reset all necessary Variable
    user_count = 0;
    order_count = 0;
    location_count = 0;
    node_count = 0;
    graph_count = 0;
    graph_check = 0;
    d_count = 0;
    p_count = 0;
}

void set_color()
{
    // Black Background and white text
    system("COLOR 0F");
}

void invalid()
{
    // Clear Screen
    clrscr();

    // Show banner
    banner();

    printf("\n\n\n");
    // Print invalid input to users
    printf("%*s", 67, "Invalid Input!");                printf("\n");
    printf("%*s", 74, "Press any key to continue...");  printf("\n");
    getch();
}

void clrscr()
{
	// Clear screen
	system("cls");
}
