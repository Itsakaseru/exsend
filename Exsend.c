#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void banner_exsend(){
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

void menu_awal(){
    printf("                                      1) Customer         (Sending Packages)"); printf("\n");
    printf("                                      2) Go-Send Courier  (Delivering Packages)"); printf("\n");
    printf("                                      3) Exit"); printf("\n");
    printf("\n");
    printf("                                      Enter choice : ");
}

void menu_customer(){
    banner_exsend();
    printf("                                      1) Go-Send order"); printf("\n");
    printf("                                      2) Delivery status check"); printf("\n");
    printf("\n");
    printf("                                      Enter choice : ");
}

void menu_courier(){
    banner_exsend();
    printf("                                      1) Go-Send order"); printf("\n");
    printf("                                      2) Delivery status update"); printf("\n");
    printf("\n");
    printf("                                      Enter choice : ");
}

void menu_send(){
    banner_exsend();
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

void menu_delivery(){
    banner_exsend();
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

int main(){
    int pilihan_utama, pilihan_customer, pilihan_courier;
    while(1){
        system("cls");
        banner_exsend();
        menu_awal();
        scanf("%d", &pilihan_utama); fflush(stdin);
        switch(pilihan_utama){
            case 1 :
                system("cls");
                menu_customer();
                scanf("%d", &pilihan_customer); fflush(stdin);
                switch(pilihan_customer){
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
                system("cls");
                menu_courier();
                scanf("%d", &pilihan_courier); fflush(stdin);
                switch(pilihan_courier){
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
