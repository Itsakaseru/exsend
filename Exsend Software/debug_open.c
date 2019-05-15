///////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////                     EXSend Software                     /////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////
/// For more information check EXSend Software Documentation

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>
#include <windows.h>

///-----------------------------------------Global Variabel-----------------------------------------///

// Struct Declare
struct route {
	char location_route[1][999];
	struct route *next, *prev;
};

// Variable Declare
int choices;
int global_id;

double graph_check = 0;
double graph_count = 0;

// User Input
int input_check = 0;

int user_privelege = 0;
char input_user[1][999];
char input_password[1][999];
char input_sender_name[1][999];
char input_sender_address[1][999];
char input_sender_location[1][999];
char input_receiver_name[1][999];
char input_receiver_address[1][999];
char input_receiver_location[1][999];
int input_price = 0;

// User Info
int login_check = 0;
int user_count = 0;
int user_id[999];
int privilege[999];

char user[999][999];
char password[999][999];

// Order Info
int order_count = 0;
int user_order_count = 0;
int user_order_id[1][999];
int order_id[999];
char order_status[999][999];
int node_count = 0;
int source = 0;
int destination = 0;
int graph[999][999];
int price_info[999];
char sender_name[999][999];
char receiver_name[999][999];
char sender_address[999][999];
char pickup_location[999][999];
char receiver_address[999][999];
char receiver_location[999][999];

// Location Info
int location_count = 0;
int sord = 0;
int location_id[999];
char location[999][999];

// Dijkstra Info
int d_count = 0;
int p_count = 0;
int length[999];
int distance[999];
int route[999][999];
char route_conv[999][999];

///---------------------------------------------Startup---------------------------------------------///

/// Load Database to Memory
void load_database()
{
    // Clear Screen
    clrscr();

	// Database File
	FILE *user_db;		// User Database
	FILE *order_db;	// order Database
	FILE *location_db;		// location Name Database
	FILE *graph_db;		// Distance Graph Database

	//Declare Variable
	int counter_x = 0;
	int counter_y = 0;

	// Set file loader
	user_db = fopen("user.db", "r");
	order_db = fopen("order.db", "r");
	location_db = fopen("location.db", "r");
	graph_db = fopen("graph.db", "r");

///-------------------------------Check for file availability-------------------------------///

	// Check for user.db availability
	if (user_db == NULL)
	{
		printf("\n");
		printf("Error while opening user.db!");
		printf("\n");
		exit(5);
	}

	// Check for order.db availability
	if (order_db == NULL)
	{
		printf("\n");
		printf("Error while opening order.db!");
		printf("\n");
		exit(5);
	}

	// Check for location.db availability
	if (location_db == NULL)
	{
		printf("\n");
		printf("Error while opening location.db!");
		printf("\n");
		exit(5);
	}

	// Check for graph.db availability
	if (graph_db == NULL)
	{
		printf("\n");
		printf("Error while opening graph.db!");
		printf("\n");
		exit(5);
	}

///-----------------------------------Read File to Memory-----------------------------------///

	// Read User Database to Memory
	while ((fscanf(user_db, "%d#%[^\#]#%[^\#]#%d", &user_id[user_count], &user[user_count], &password[user_count], &privilege[user_count])) != EOF)
	{
		user_count++;
	}

	// Read order Database to Memory
	while ((fscanf(order_db, "%d#%[^\#]#%[^\#]#%[^\#]#%[^\#]#%[^\#]#%[^\#]#%[^\#]#%d",
		&order_id[order_count], &order_status[order_count], &sender_name[order_count], &receiver_name[order_count], &sender_address[order_count], &pickup_location[order_count], &receiver_address[order_count], &receiver_location[order_count], &price_info[order_count])) != EOF)
	{
		order_count++;
	}

	// Read Location Database to Memory
	while ((fscanf(location_db, "%d-%[^\n]", &location_id[location_count], &location[location_count])) != EOF)
	{
		location_count++;
		node_count++;
	}

	// Read Distance Graph Database to Memory
	while ((fscanf(graph_db, "%d ", &graph[counter_y][counter_x])) != EOF)
	{
		counter_x++;
		graph_count++;
		if (counter_x > location_count - 1)
		{
			counter_y++;
			counter_x = 0;
		}
	}

/// Checker to make sure the number of location in a file corresponding to the number of nodes in graph
    graph_check += sqrt(graph_count);

    if(graph_check != location_count)
    {
        printf("Invalid graph or location database!");
        printf("\n");
        exit(6);
    }
    if(counter_y != location_count)
    {
        printf("Invalid graph or location database!");
        printf("\n");
        exit(6);
    }

    // Close file
    fclose(user_db);
    fclose(order_db);
    fclose(location_db);
    fclose(graph_db);

	///DEBUG

	printf("Database Load Success!"); printf("\n");
	printf("There are %d Nodes", node_count);
    getch();

	/*
	for (int i = 0; i < user_count; i++)
	{
		printf("ID : %d", user_id[i]); printf("\n");
		printf("User : %s", user[i]); printf("\n");
		printf("Password : %s", password[i]); printf("\n");
	}

	for (int i = 0; i < location_count; i++)
	{
		printf("ID : %d", i); printf("\n");
		printf("%s \n", location[i]);
	}

	for(int i = 0; i < location_count; i++)
	{
		for(int j = 0; j < location_count; j++)
		{
			printf("%d ", graph[i][j]);
		}
		printf("\n");
	}

	for (int i = 0; i < order_count; i++)
	{
		printf("ID : %d", order_id[i]); printf("\n");
		printf("Status : %s", order_status[i]); printf("\n");
		printf("Sender Name : %s", sender_name[i]); printf("\n");
		printf("Receiver Name : %s", receiver_name[i]); printf("\n");
		printf("Sender Address : %s", sender_address[i]); printf("\n");
		printf("Pickup location Location : %s", pickup_location[i]); printf("\n");
		printf("Receiver Address : %s", receiver_address[i]); printf("\n");
		printf("Receiver location Location : %s", receiver_location[i]); printf("\n");
		printf("Price : %d", price_info[i]); printf("\n");
	}*/

}

void splash()
{
    // Print EXSend Logo
	printf("########################################################################################################################");
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
    printf("########################################################################################################################");
}

void banner()
{
    // Print banner
	printf("======================================================================================================================="); printf("\n");
	printf("\n");
	printf("#######################################################################################################################"); printf("\n");
	printf("##############################      ####  ###  ####     ####      ####  ####  ####     ################################"); printf("\n");
	printf("############################## ##########  #  #### ######### #########   ###  #### #### ###############################"); printf("\n");
	printf("##############################     #######  #######     ####     #####  # ##  #### #### ###############################"); printf("\n");
	printf("############################## ##########  #  #########  ### #########  ## #  #### #### ###############################"); printf("\n");
	printf("##############################      ####  ###  ####     ####      ####  ###   ####     ################################"); printf("\n");
	printf("#######################################################################################################################"); printf("\n");
	printf("\n");
	printf("======================================================================================================================="); printf("\n");
	printf("\n");
}

void login()
{
    // Variable Set
    global_id = 1;
    login_check = 0;

    // Clear Screen
    clrscr();

    // Show banner
	banner();

	// Print Login Menu
	printf("\t\t\t\t\t\t"); printf("Username : ");				scanf("%[^\n]", &input_user);		getchar();
	printf("\t\t\t\t\t\t"); printf("Password : ");				scanf("%[^\n]", &input_password);	getchar();

	/// Check Username and Password
	binary_search(input_user);

    if(login_check == 1)
    {
        global_id = 2;
        login_check = 0;
        binary_search(input_password);
    }

    // If Username or Password is incorrect
    if(login_check == 0)
    {
        printf("\t\t\t\t\t"); printf("Incorrect Username or Password!");	            printf("\n");
        printf("\t\t\t\t\t"); printf("Press any key to continue...");		            printf("\n");
        getch();
        login();
    }

    // If Username and Password is correct
    if(login_check == 1){
        printf("\t\t\t\t\t"); printf("Welcome back %s!", input_user);                   printf("\n");
        printf("\t\t\t\t\t"); printf("Press any key to continue...", input_user);       getch();
        main_menu();
    }

}

void main_menu()
{
    // Variable Set
    global_id = 3;

    // Clear Screen
    clrscr();

    // Show banner
    banner();

    // Print Menu
	printf("\t\t\t\t\t"); printf("1) Customer        (Sending Packages)");			 printf("\n");
	if(user_privelege == 2)
    {
        printf("\t\t\t\t\t"); printf("2) EXSend Courier  (Delivering Packages)");	 printf("\n");
    }
	printf("\t\t\t\t\t"); printf("0) Exit");									     printf("\n");
	printf("\n");
	printf("\t\t\t\t\t"); printf("Enter choice : ");							     scanf("%d", &choices); getchar();

	// Check for user choices
	switch(choices)
	{
        case 1 :
        {
            menu_customer();
            break;
        }

        case 2 :
        {
            if(user_privelege == 2)
            {
                menu_courier();
            }
            else
            {
                invalid();
                main_menu();
            }
            break;
        }

        case 0 :
        {
            exit(0);
        }
	}
}

void menu_customer()
{
    // Variable Set
    global_id = 4;

    // Clear Screen
    clrscr();

    // Show banner
	banner();

	// Show Menu
	printf("\t\t\t\t\t"); printf("1) EXSend Delivery");				        printf("\n");
	printf("\t\t\t\t\t"); printf("2) Delivery status check");				printf("\n");
	printf("\t\t\t\t\t"); printf("0) Back");				                printf("\n");
	printf("\n");
	printf("\t\t\t\t\t"); printf("Enter choice : ");				        scanf("%d", &choices); getchar();

	// Check for user choices
	switch(choices)
	{
        case 1 :
        {
            customer_delivery();
            break;
        }

        case 2 :
        {
            menu_ustatus();
            break;
        }

        case 0 :
        {
            main_menu();
            break;
        }
	}
}

void customer_delivery()
{
    global_id = 41;

    // Clear Screen
    clrscr();

    // Show banner
	banner();

	/// Input Check
	if(input_check >= 5)
    {
        printf("Ready to run dijkstra algorithm"); printf("\n");
        getch();
        dijkstra();
        input_price = ( distance[destination] * 1000 );
    }

	printf("\t\t\t\t"); printf("1) Sender's name                : %s", user);                        printf("\n");
	printf("\t\t\t\t"); printf("2) Sender's pick up location    : %s", input_sender_location);       printf("\n");
	printf("\t\t\t\t"); printf("3) Sender's address             : %s", input_sender_address);        printf("\n");
	printf("\n");
	printf("\t\t\t\t"); printf("4) Receiver's name              : %s", input_receiver_name);         printf("\n");
	printf("\t\t\t\t"); printf("5) Receiver's delivery location : %s", input_receiver_location);     printf("\n");
	printf("\t\t\t\t"); printf("6) Receiver's address           : %s", input_receiver_address);      printf("\n");

	printf("\n");

	printf("\t\t\t\t"); printf("Delivery fees                   : Rp %d", input_price);              printf("\n");

	// Print Confirm Order if users filled in the data
	if(input_check >= 5)
    {
        printf("\n");
        printf("\t\t\t\t\t\t\t"); printf("7) Confirm Order");
    }

    printf("\n");
    printf("\t\t\t\t\t\t\t"); printf("0) Back to menu");                                                   printf("\n");

    printf("\n");

	printf("\t\t\t\t\t\t"); printf("Enter choice : ");				                                 scanf("%d", &choices); getchar();

	if(input_check >= 5)
    {
        if(choices == 7)
        {
            export_tofile();
            reset();
            load_database();
            menu_customer();
        }
    }

	switch(choices)
	{
        case 1 :
        {
            delivery_name();
            break;
        }

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
            menu_customer();
        }
	}

}

void delivery_name()
{
    global_id = 411;

    switch(choices)
    {
        case 4 :
        {
            // Clear Screen
            clrscr();

            // Show banner
            banner();

            printf("\t\t\t\t\t"); printf("Receiver's name                : ");  scanf("%[^\n]", input_receiver_name); getchar();

            // Back to delivery menu
            input_check++;
            customer_delivery();
            break;
        }
    }

}

void delivery_location()
{
    global_id = 412;

    int count;

    switch(choices)
    {
        case 2 :
        {
            // Clear Screen
            clrscr();

            // Show banner
            banner();

            // Print all available location
            for(count = 0; count < location_count; count++)
            {
                printf("\t\t\t\t\t"); printf("%d) %s", count+1, location[count]);     printf("\n");
            }

            printf("\n");
            printf("\t\t\t\t\t"); printf("Choose pick up location : ");               scanf("%d", &choices);  getchar();

            /// Check if pickup and receive location is the same
            /*if( strcmpi(input_receiver_location, input_sender_location) == 0 )
            {
                printf("printf("\t\t\t\t\t"); printf("Choose pick up location : ");               scanf("%d", &choices);  getchar();");
            }*/

            // Choices to IDs converter
            choices--;
            strcpy(input_sender_location, location[choices]);

            // Set source to user_input
            source = choices;

            // Back to delivery menu
            input_check++;
            customer_delivery();
            break;
        }

        case 5 :
        {
            // Clear Screen
            clrscr();

            // Show banner
            banner();

            // Print all available location
            for(count = 0; count < location_count; count++)
            {
                printf("\t\t\t\t\t"); printf("%d) %s", count+1, location[count]);     printf("\n");
            }

            printf("\n");
            printf("\t\t\t\t\t"); printf("Choose receiver's location : ");            scanf("%d", &choices);  getchar();

            /// Check if pickup and receive location is the same
            /*if( strcmpi(input_receiver_location, input_sender_location) == 0 )
            {
                printf("printf("\t\t\t\t\t"); printf("Choose pick up location : ");               scanf("%d", &choices);  getchar();");
            }*/

            // Choices to IDs converter
            choices--;
            strcpy(input_receiver_location, location[choices]);

            // Set destination to user_input
            destination = choices;

            // Back to delivery menu
            input_check++;
            customer_delivery();
            break;
        }
    }


}

void delivery_address()
{
    global_id = 413;

    switch(choices)
    {
        case 3 :
        {
            // Clear Screen
            clrscr();

            // Show banner
            banner();

            printf("\t\t\t\t"); printf("Sender's Address                : ");  scanf("%[^\n]", input_sender_address); getchar();

            // Back to delivery menu
            input_check++;
            customer_delivery();
            break;
        }

        case 6 :
        {
            // Clear Screen
            clrscr();

            // Show banner
            banner();

            printf("\t\t\t\t"); printf("Receiver's Address                : ");  scanf("%[^\n]", input_receiver_address); getchar();

            // Back to delivery menu
            input_check++;
            customer_delivery();
            break;
        }
    }
}

void menu_ustatus()
{
    // Variable Set
    global_id = 42;

    // Clear Screen
    clrscr();

    // Print Banner
    banner();

    // Print Menu
	printf("\t\t\t\t\t\t\t"); printf("Order List");		 printf("\n");

	printf("\n");

    binary_search(user);

    printf("\n");
    printf("\t\t\t\t\t\t\t");      printf("0) Exit");                                 printf("\n");

    user_order_count = 0;

    printf("\n");
    printf("\t\t\t\t\t\t\t"); printf("Choices : ");       scanf("%d", &choices);

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
    printf("\t\t\t\t\t\t\t"); printf("Order #%d", choices);				                        printf("\n");

    printf("\n");

    printf("\t\t\t\t"); printf("Sender's name                : %s", sender_name[id]);           printf("\n");
	printf("\t\t\t\t"); printf("Sender's pick up location    : %s", pickup_location[id]);       printf("\n");
	printf("\t\t\t\t"); printf("Sender's address             : %s", sender_address[id]);        printf("\n");
	printf("\n");
	printf("\t\t\t\t"); printf("Receiver's name              : %s", receiver_name[id]);         printf("\n");
	printf("\t\t\t\t"); printf("Receiver's delivery location : %s", receiver_location[id]);     printf("\n");
	printf("\t\t\t\t"); printf("Receiver's address           : %s", receiver_address[id]);      printf("\n");

	printf("\n");

	printf("\t\t\t\t"); printf("Delivery fees                : Rp %d", price_info[id]);         printf("\n");
	printf("\t\t\t\t"); printf("Status                       : %s", order_status[id]);          printf("\n");

	printf("\t\t\t\t"); printf("Press any key to go back...");                                  getch();
	menu_ustatus();

}

void menu_courier()
{
    // Variable Set and Declare
    int counter;
    global_id = 5;

    // Clear Screen
    clrscr();

    // Show banner
    banner();

    // Print Menu
	printf("\t\t\t\t\t\t\t"); printf("Order List");				               printf("\n");
	printf("\n");

	for(counter = 0; counter < order_count; counter++)
    {
        printf("\t\t\t\t\t\t"); printf("%d) %s | %s", counter+1, sender_name[counter], order_status[counter]); printf("\n");
    }

    printf("\n");
	printf("\t\t\t\t\t\t"); printf("0) Exit");								   printf("\n");
	printf("\n");
	printf("\t\t\t\t\t\t"); printf("Enter choice : ");						   scanf("%d", &choices); getchar();

	// Check for user choices
    delivery_show();
}

void delivery_show()
{
    // Declare variable and set
    int input;
    global_id = 51;
    input = choices;
    input--;

    // Clear Screen
    clrscr();

    // Show banner
    banner();

    // Export route to linked list
    //export_tolist();

    // Print Order Information
    printf("\t\t\t\t\t\t\t"); printf("Order #%d", input+1);				                           printf("\n");

    printf("\n");

    printf("\t\t\t\t"); printf("Sender's name                : %s", sender_name[input]);           printf("\n");
	printf("\t\t\t\t"); printf("Sender's pick up location    : %s", pickup_location[input]);       printf("\n");
	printf("\t\t\t\t"); printf("Sender's address             : %s", sender_address[input]);        printf("\n");
	printf("\n");
	printf("\t\t\t\t"); printf("Receiver's name              : %s", receiver_name[input]);         printf("\n");
	printf("\t\t\t\t"); printf("Receiver's delivery location : %s", receiver_location[input]);     printf("\n");
	printf("\t\t\t\t"); printf("Receiver's address           : %s", receiver_address[input]);      printf("\n");

	printf("\n");

	printf("\t\t\t\t"); printf("Delivery fees                : Rp %d", price_info[input]);         printf("\n");
	printf("\t\t\t\t"); printf("Status                       : %s", order_status[input]);          printf("\n");

	printf("\n");

	printf("\t\t\t\t\t\t\t"); printf("1) Change Status");                                          printf("\n");
	printf("\t\t\t\t\t\t\t"); printf("2) Directions");                                             printf("\n");

	printf("\n");

	printf("\t\t\t\t\t\t\t"); printf("Choices : ");                                                scanf("%d", &choices);

	switch(choices)
	{
        case 1 :
        {
            menu_cstatus(input);
        }
        case 2 :
        {
            show_direction(input);
        }
	}

}

void menu_cstatus(int *input)
{
    // Declare variable and set
    global_id = 511;
    int id;

    id = input;
    id++;

    // Clear Screen
    clrscr();

    // Show banner
    banner();

    printf("\t\t\t\t\t\t\t");     printf("Order #%d", id);				                       printf("\n");
    printf("\t\t\t\t\t\t      "); printf("Change Status");				                       printf("\n");

    printf("\n");

    printf("\t\t\t\t\t\t     "); printf("1) Pending");				                           printf("\n");
    printf("\t\t\t\t\t\t     "); printf("2) Delivered");				                       printf("\n");

    for(int count = 0; count < node_count; count++)
    {
        printf("\t\t\t\t\t\t     "); printf("%d) %s", count+3, location[count]);			   printf("\n");
    }

    printf("\n");

    printf("\t\t\t\t\t\t\t"); printf("Choices : ");			                                   scanf("%d", &choices); getchar();

    id--;
    modify_memory(id);

    menu_courier();
}

void binary_search(char *search)
{
	// Declare variable
	int mid, low, high;
	low = 0;
	int counter = 0;

	if(global_id == 1)
    {
        high = user_count - 1;
    }

    if(global_id == 2)
    {
        high = user_count - 1;
    }

	if(global_id == 51)
    {
        high = location_count - 1;
    }

	/// Binary Search
	switch(global_id)
	{
        case 1 :
        {
            while (low <= high)
            {
                mid = (low + high) / 2;
                if (strcmp(search, user[mid]) == 0)
                {
                    login_check = 1;
                }
                if (strcmpi(search, user[mid] < 0))
                {
                    high = mid - 1;
                }
                else
                {
                    low = mid + 1;
                }
            }
            break;
        }

        case 2 :
        {
            while (low <= high)
                {
                    mid = (low + high) / 2;
                    if (strcmp(search, password[mid]) == 0)
                    {
                        login_check = 1;
                        user_privelege = privilege[mid];
                    }
                    if (strcmpi(search, password[mid] < 0))
                    {
                        high = mid - 1;
                    }
                    else
                    {
                        low = mid + 1;
                    }
                }
            break;
        }

        case 51 :
        {
            while (low <= high)
                {
                    mid = (low + high) / 2;
                    if (strcmpi(search, location[mid]) == 0)
                    {
                        if(sord == 0)
                        {
                            source = mid;
                        }
                        if(sord == 1)
                        {
                            destination = mid;
                        }
                    }
                    if (strcmpi(search, location[mid] < 0))
                    {
                        high = mid - 1;
                    }
                    else
                    {
                        low = mid + 1;
                    }
                }
            break;
        }

        case 42 :
        {
            for(counter = 0; counter < order_count; counter++)
            {
                if (strcmpi(search, sender_name[counter]) == 0)
                    {
                        user_order_id[1][user_order_count] = counter;
						user_order_count++;
                        printf("\t\t\t\t\t"); printf("%d) %s | %s | %s", user_order_count, order_status[counter], receiver_name[counter], receiver_location[counter]); printf("\n");
                    }
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
    // Base Case : If j is source
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
    // The output array. dist[i]
    // will hold the shortest
    // distance from src to i
    int dist[node_count];

    // sptSet[i] will true if vertex
    // i is included / in shortest
    // path tree or shortest distance
    // from src to i is finalized
    bool sptSet[node_count];

    // Parent array to store
    // shortest path tree
    int parent[node_count];

    // Initialize all distances as
    // INFINITE and stpSet[] as false
    for (int i = 0; i < node_count; i++)
    {
        parent[source] = -1;
        dist[i] = INT_MAX;
        sptSet[i] = false;
    }

    // Distance of source vertex
    // from itself is always 0
    dist[source] = 0;

    // Find shortest path
    // for all vertices
    for (int count = 0; count < node_count - 1; count++)
    {
        // Pick the minimum distance
        // vertex from the set of
        // vertices not yet processed.
        // u is always equal to src
        // in first iteration.
        int u = minDistance(dist, sptSet);

        // Mark the picked vertex
        // as processed
        sptSet[u] = true;

        // Update dist value of the
        // adjacent vertices of the
        // picked vertex.
        for (int v = 0; v < node_count; v++)

            // Update dist[v] only if is
            // not in sptSet, there is
            // an edge from u to v, and
            // total weight of path from
            // src to v through u is smaller
            // than current value of
            // dist[v]
            if (!sptSet[v] && graph[u][v] &&
                dist[u] + graph[u][v] < dist[v])
            {
                parent[v] = u;
                dist[v] = dist[u] + graph[u][v];
            }
    }

    // print the constructed
    // distance array
    export_dijkstra(dist, node_count, parent);
}

void modify_memory(int *id)
{
    // Declare and set variable
    int local_id;
    local_id = id;

    printf("%s", order_status[local_id]);
    switch(global_id)
    {
        case 511 :
        {
            if(choices == 1)
            {
                strcpy(order_status[local_id], "Pending");
            }
            if(choices == 2)
            {
                strcpy(order_status[local_id], "Delivered");
            }
            else
            {
                choices = choices - 3;
                strcpy(order_status[local_id], location[choices]);
            }
            break;
        }
    }
    overwrite_tofile();
}

void export_tofile()
{
	// Database File
	FILE *user_db;		// User Database
	FILE *order_db;	// order Database
	FILE *location_db;		// location Name Database
	FILE *graph_db;		// Distance Graph Database

	// Set file loader
	user_db = fopen("user.db", "a");
	order_db = fopen("order.db", "a");
	location_db = fopen("location.db", "a");
	graph_db = fopen("graph.db", "a");

    switch(global_id)
    {
        case 41 :
        {
            fprintf(order_db, "\n%d#Pending#%s#%s#%s#%s#%s#%s#%d",
                    order_count, user, input_receiver_name, input_sender_address, input_sender_location, input_receiver_address, input_receiver_location, input_price);
            break;
        }
    }

    printf("DATA SUCCESFULLY EXPORTED TO DATABASE!");
    getch();

    // Close file
    fclose(user_db);
    fclose(order_db);
    fclose(location_db);
    fclose(graph_db);
}

void overwrite_tofile()
{
    // Declare variable
    int counter;

    // Database File
	FILE *user_db;		// User Database
	FILE *order_db;	    // order Database
	FILE *location_db;  // location Name Database
	FILE *graph_db;		// Distance Graph Database

	// Set file loader

    if(global_id == 511)
    {
        order_db = fopen("order.db", "w");
    }

	switch(global_id)
	{
        case 511 :
        {
            for(counter = 0; counter < order_count; counter++)
            {
                fprintf(order_db, "%d#%s#%s#%s#%s#%s#%s#%s#%d\n",
                    order_id[counter], order_status[counter], sender_name[counter], receiver_name[counter], sender_address[counter], pickup_location[counter], receiver_address[counter], receiver_location[counter], price_info[counter]);
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
    int local_input;
    int counter = 0;
    int insert = 0;
    int page = 1;
    sord = 0;
    local_input = input;
    struct route *head, *node, *tail, *curr;

    head = NULL;

    // Read Array to determine source and destination
    binary_search(pickup_location[local_input]);
    sord++;
    binary_search(receiver_location[local_input]);

    dijkstra();

    // Export to linked-list
    free(head);

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

    curr = head;

    // Print Direction
    while(1)
    {
        // Clear Screen
        clrscr();

        // Show banner
        banner();

        printf("\t\t\t\t\t\t    ");    printf("=== Order #%d ===", local_input+1);	     printf("\n");
        printf("\n");
        printf("\t\t\t\t\t\t      ");  printf("Direction #1", local_input+1);	          printf("\n");
        printf("\n");
        printf("\t\t\t\t\t\t       "); printf("%s", curr->location_route);                printf("\n");

        printf("\n");

        printf("\t\t\t\t      ");      printf("1) Previous Direction"); printf("      "); printf("2) Next Direction"); printf("\n");
        printf("\n");
        printf("\t\t\t\t\t\t\t");      printf("0) Exit");                                 printf("\n");
        printf("\n");
        printf("\t\t\t\t\t\t       "); printf("Choices : "); scanf("%d", &choices);       getchar();

        if(choices == 2)
        {
            if(curr->next == NULL)
            {
                printf("\t\t\t\t\t    "); printf("Already at the final destination");
                getch();
            }
            else
            {
                curr = curr->next;
            }
        }
        else if(choices == 1)
        {
            if(curr->prev == NULL)
            {
                printf("\t\t\t\t\t "); printf("Already at the start of the destination");
                getch();
            }
            else
            {
                curr = curr->prev;
            }
        }
        else if(choices == 0)
        {
            menu_courier();
        }
    }
}

int main()
{
    set_color();
	load_database();

	// Clear Screen
	clrscr();
	splash();
	Sleep(1000);

    clrscr();
    login();

	main_menu();
}

void reset()
{
    // Reset Variable
    input_check = 0;
    user_count = 0;
    order_count = 0;
    location_count = 0;
    node_count = 0;
    graph_count = 0;
    graph_check = 0;
}

void set_color()
{
    system("COLOR 0B");
}

void invalid()
{
    // Print invalid input to users
    printf("\t\t\t\t\t\t"); printf("Invalid Input!");	            printf("\n");
    printf("\t\t\t\t\t\t"); printf("Press any key to continue...");	getch();
}

void clrscr()
{
	system("cls");
}
