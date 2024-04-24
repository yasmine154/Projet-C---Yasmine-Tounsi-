#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_BUSES 100
#define MAX_RESERVATIONS 100
#define MAX_NAME_LENGTH 20

struct Bus
{
    int busNumber;
    char destination[20];
    int totalSeats;
    int availableSeats;
    int day;
    int month;
    char time[6];
};

struct Reservation
{
    int reservationNumber;
    int busNumber;
    char passengerName[MAX_NAME_LENGTH];
    int day;
    int month;
    char time[6];
};

struct Traveler
{
    char travelermdp[20];
    char username[MAX_NAME_LENGTH];
};
void CreateNewTraveler(struct Traveler Travelers[], int *numTravelers);
void createNewReservation(struct Reservation reservations[], int *numReservations, struct Bus Buses[], int *numBuses);
void loadBusDataFromFile(struct Bus buses[], int *numBuses);
void loadReservationDataFromFile(struct Reservation reservations[], int *numReservations);
void saveReservationDataToFile(struct Reservation reservations[], int *numReservations);
void saveBusDataToFile(struct Bus buses[], int *numBuses);
void loadTravelers(struct Traveler travelers[], int *numTravelers);
void saveTavelersToFile(struct Traveler travelers[], int *numTravelers);
void Menu();
void connexion(struct Traveler travelers[], int *numTravelers);
void displayBusDetails(struct Bus buses[], int *numBuses);
void detailsReservation(struct Reservation reservations[], int *numReservations);
void modifierReservation(struct Reservation reservations[], int *numReservations, struct Bus buses[], int *numBuses);
void detailsBus(struct Bus buses[], int *numBuses);

void detailsBus(struct Bus buses[], int *numBuses)
{
    printf("Entrer le numero du bus : ");
    int nb = 0;
    scanf("%d", &nb);
    int test = 0;
    for (int i = 0; i < *numBuses; i++)
    {
        if (buses[i].busNumber == nb)
        {
            test = 1;
            printf("Destination : %-20s \n", buses[i].destination);
            printf("Total de places : %d \n", buses[i].totalSeats);
            printf("Nombre de places disponibles : %d \n", buses[i].availableSeats);
            printf("Date : %d / %d *** heure : %-12s \n\n", buses[i].day, buses[i].month, buses[i].time);
            break;
        }
    }
    if (test == 0)
    {
        printf("Ce bus n'existe pas ");
    }
}

void modifierReservation(struct Reservation reservations[], int *numReservations, struct Bus buses[], int *numBuses)
{
    printf("Entrer le numero de reservation : ");
    int nb = 0;
    scanf("%d", &nb);
    int test = 0;
    for (int i = 0; i < *numReservations; i++)
    {
        if (reservations[i].reservationNumber == nb)
        {
            test = 1;
            for (int j = i; j < *numReservations; j++)
            {
                reservations[j] = reservations[j + 1];
            }
            *numReservations--;
            createNewReservation(reservations, numReservations, buses, numBuses);
            break;
        }
    }
    if (test == 0)
    {
        printf("Cette reservation n'existe pas");
    }
}

void detailsReservation(struct Reservation reservations[], int *numReservations)
{
    printf("saisir le numero de reservation : ");
    int r;
    scanf("%d", &r);

    for (int i = 0; i < *numReservations; i++)
    {
        if (reservations[i].reservationNumber == r)
        {
            printf("Numero de reservation : %d \n", reservations[i].reservationNumber);
            printf("Numero du bus : %d \n", reservations[i].busNumber);
            printf("username : %-21s \n", reservations[i].passengerName);
            printf("Date : %d / %d *** heure : %-12s \n\n", reservations[i].day, reservations[i].month, reservations[i].time);

            break;
        }
    }
}

void displayBusDetails(struct Bus buses[], int *numBuses)
{
    printf("Tapez votre destination ");
    char d[20];
    scanf("%20s", &d);
    for (int i = 0; i < *numBuses; i++)
    {

        if (strcmp(d, buses[i].destination) == 0)
        {
            printf("Nombre du Bus : %d \n", buses[i].busNumber);
            printf("Destination : %-20s \n", buses[i].destination);
            printf("Total de places : %d \n", buses[i].totalSeats);
            printf("Nombre de places disponibles : %d \n", buses[i].availableSeats);
            printf("Date : %d / %d *** heure : %-12s \n\n", buses[i].day, buses[i].month, buses[i].time);
        }
    }
}

void createNewReservation(struct Reservation reservations[], int *numReservations, struct Bus buses[], int *numBuses)
{
    displayBusDetails(buses, numBuses);
    printf("Entrer votre username : ");
    char u[20];
    scanf("%21s", u);

    printf("Entrez le numero de Bus : ");
    int nb;
    scanf("%d", &nb);
    reservations[*numReservations].busNumber = nb;

    printf("\nReservation du bus %d faite avec succes! \n", nb);
    reservations[*numReservations].reservationNumber = (*numReservations + 1);

    for (int i = 0; i < sizeof(u); i++)
    {
        reservations[*numReservations].passengerName[i] = u[i];
    }

    for (int i = 0; i < *numBuses; i++)
    {
        if (buses[i].busNumber == nb)
        {
            reservations[*numReservations].day = buses[i].day;
            reservations[*numReservations].month = buses[i].month;
            for (int j = 0; j < sizeof(buses[i].time); j++)
            {

                reservations[*numReservations].time[j] = buses[i].time[j];
            }

            buses[i].availableSeats--;
            if (buses[i].availableSeats == 0)
            {
                for (int j = i; j < *numBuses; j++)
                {
                    buses[j] = buses[j + 1];
                    (*numBuses)--;
                }
            }
            break;
        }
    }

    (*numReservations)++;
    printf("le numero de votre reservation est : %d \n\n", *numReservations);
    int gift = rand() % 101; // Tirage au sort grace au numéo de reservation : si le numéro de reservation est égal au numéro aléatoire, le voyage sera gratuit!
    if (gift == *numReservations)
    {
        printf("Félicitations! Ce voyage sera gratuit, offre de la part de E-bus");
    }
}

void Menu()
{
    printf("           *** Agence de voyage E-BUS - TUNIS *** \n\n");

    printf("1. Creer un nouveau compte voyageur \n");
    printf("2. J'ai deja un compte voyageur\n");
    fflush(stdout);
}
void connexion(struct Traveler travelers[], int *numTravelers)
{

    int verif = 0;
    while (verif == 0)
    {
        int r;
        scanf("%d", &r);
        if (r == 1)
        {
            CreateNewTraveler(travelers, numTravelers);
            verif = 1;
        }
        if (r == 2)
        {

            printf("username: ");
            char u[MAX_NAME_LENGTH];
            char m[20];
            scanf("%s", u);
            printf("Mot de passe: ");
            scanf("%s", m);
            int i = 0;
            while (i <= *numTravelers && !verif)
            {
                if (strcmp(travelers[i].username, u) == 0 && strcmp(travelers[i].travelermdp, m) == 0)
                {
                    verif = 1;
                }
                i++;
            }
            if (verif)
                printf("connecte avec succes\n");
            else
            {
                printf("ce compte est inexistant\n");
                Menu();
            }
        }
    }
}

void CreateNewTraveler(struct Traveler Travelers[], int *numTravelers)
{
    printf("Entrez votre nom d'utilisateur : \n");
    scanf("%s", Travelers[*numTravelers].username);

    printf("Entrez un mot de passe (ne depasse pas 20 caracteres) : \n");
    scanf("%20s", Travelers[*numTravelers].travelermdp);
    (*numTravelers)++;
    printf("Compte voyageur cree avec succes!\n\n");
}

// Fonction pour charger les informations des bus à partir d'un fichier
void loadBusDataFromFile(struct Bus buses[], int *numBuses)
{
    FILE *file = fopen("bus_data.txt", "r");
    if (file == NULL)
    {
        perror("Erreur lors de l'ouverture du fichier");
        exit(EXIT_FAILURE);
    }

    while (fscanf(file, "%d %s %d %d %d %d %s", &buses[*numBuses].busNumber, buses[*numBuses].destination,
                  &buses[*numBuses].totalSeats, &buses[*numBuses].availableSeats, &buses[*numBuses].day, &buses[*numBuses].month, &buses[*numBuses].time) == 7)
    {
        (*numBuses)++;
    }

    fclose(file);
}

// Fonction pour charger les informations des réservations à partir d'un fichier
void loadReservationDataFromFile(struct Reservation reservations[], int *numReservations)
{
    FILE *file = fopen("reservation_data.txt", "r");
    if (file == NULL)
    {
        perror("Erreur lors de l'ouverture du fichier");
        exit(EXIT_FAILURE);
    }

    while (fscanf(file, "%d %d %19s %d %d %6s", &reservations[*numReservations].reservationNumber,
                  &reservations[*numReservations].busNumber, reservations[*numReservations].passengerName,
                  &reservations[*numReservations].day, &reservations[*numReservations].month,
                  reservations[*numReservations].time) == 6)
    {
        (*numReservations)++;
    }

    fclose(file);
}

// Fonction pour sauvegarder les informations des réservations dans un fichier
void saveReservationDataToFile(struct Reservation reservations[], int *numReservations)
{
    FILE *file = fopen("reservation_data.txt", "w");
    if (file == NULL)
    {
        perror("Erreur lors de l'ouverture du fichier");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < *numReservations; ++i)
    {
        fprintf(file, "%d %d %s %d %d %s \n", reservations[i].reservationNumber, reservations[i].busNumber,
                reservations[i].passengerName, reservations[i].day, reservations[i].month,
                reservations[i].time);
    }

    fclose(file);
}

// Fonction pour sauvegarder les informations des bus dans un fichier
void saveBusDataToFile(struct Bus buses[], int *numBuses)
{
    FILE *file = fopen("bus_data.txt", "w");
    if (file == NULL)
    {
        perror("Erreur lors de l'ouverture du fichier");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < *numBuses; ++i)
    {
        fprintf(file, "%d %s %d %d %d %d %s \n", buses[i].busNumber, buses[i].destination,
                buses[i].totalSeats, buses[i].availableSeats, buses[i].day, buses[i].month, buses[i].time);
    }

    fclose(file);
}

void loadTravelers(struct Traveler travelers[], int *numTravelers)
{
    FILE *file = fopen("travelers.txt", "r");
    if (file == NULL)
    {
        perror("Erreur lors de l'ouverture du fichier");
        exit(EXIT_FAILURE);
    }

    while (fscanf(file, "%21s %50s", &travelers[*numTravelers].travelermdp, &travelers[*numTravelers].username) == 2)
    {
        (*numTravelers)++;
    }

    fclose(file);
}

void saveTavelersToFile(struct Traveler travelers[], int *numTravelers)
{
    FILE *file = fopen("travelers.txt", "w");
    if (file == NULL)
    {
        perror("Erreur lors de l'ouverture du fichier");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < *numTravelers; ++i)
    {
        fprintf(file, "%s %s \n", travelers[i].travelermdp, travelers[i].username);
    }

    fclose(file);
}

int main()
{
    struct Bus buses[MAX_BUSES];
    int numBuses = 0;
    loadBusDataFromFile(buses, &numBuses);

    struct Reservation reservations[MAX_RESERVATIONS];
    int numReservations = 0;
    loadReservationDataFromFile(reservations, &numReservations);

    struct Traveler travelers[MAX_RESERVATIONS];
    int numTravelers = 0;
    loadTravelers(travelers, &numTravelers);

    Menu();
    connexion(travelers, &numTravelers);

    int choice;
    do
    {
        printf("1.Creer une nouvelle reservation\n");
        printf("2.Details de la reservation\n");
        printf("3.Modifier une reservation\n");
        printf("4.Details du bus\n");
        printf("5.Quitter\n");
        printf("Saisissez votre choix : ");
        scanf("%d", &choice);
        switch (choice)
        {

        case 1:
            createNewReservation(reservations, &numReservations, buses, &numBuses);
            break;

        case 2:
            detailsReservation(reservations, &numReservations);
            break;

        case 3:
            modifierReservation(reservations, &numReservations, buses, &numBuses);
            break;

        case 4:
            detailsBus(buses, &numBuses);
            break;

        case 5:
            break;
        }
    } while (choice != 5);
    printf("Au revoir !");
    saveBusDataToFile(buses, &numBuses);
    saveReservationDataToFile(reservations, &numReservations);
    saveTavelersToFile(travelers, &numTravelers);

    return 0;
}
