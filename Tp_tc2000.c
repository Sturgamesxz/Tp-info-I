#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

struct Pilotos
{
    char nom[41];
    char ap[41];
    char marca[41];
    int num_auto;
};

struct Tiempos
{
    int num_auto;
    int vueltasCompletas;
    float seg;
    int numeroCarrera;
    char etapa[41];
};

struct unaCarrera
{
    int num_auto;
    int vueltasCompletas;
    float tiempo;
    int carre;
};

void inicializador(struct unaCarrera carrera[60]) 
{
    for (int j=0; j<60; j++) 
    {
        carrera[j].tiempo = 99999.999;
    }
    
}
void CargadatosPilotos(struct Pilotos pi[60]) // Función pa?ra cargar pilotos.txt
{ 
    setlocale(LC_ALL, "");

    int num_auto, edad;
    char nom[41], ap[41], ciudad[41], marca[41], equipo[41];

    FILE *ArchivoPilotos; // Declaro primer archivo
    ArchivoPilotos = fopen("pilotos.txt", "r"); // Abro archivo

    if (ArchivoPilotos == NULL) // Compruebo si lo puede abrir
    {   printf("Error: no se pudo abrir el archivo pilotos.txt.\n");
        exit(1);
    }

    int i = 0;

    fscanf(ArchivoPilotos,"%d %s %s %d %s %s %s",&num_auto, nom, ap, &edad, ciudad, marca, equipo);

    while (!(feof(ArchivoPilotos))) 
    {
        pi[i].num_auto=num_auto;
        strcpy(pi[i].nom,nom);
        strcpy(pi[i].ap,ap);
        strcpy(pi[i].marca,marca);

        fscanf(ArchivoPilotos,"%d %s %s %d %s %s %s",&num_auto, nom, ap, &edad, ciudad, marca, equipo);
        i++;
    }

    fclose(ArchivoPilotos); // Cierro archivo
}

void CargarDatosTiempos(struct Tiempos tiempo[180]) 
{
    FILE *ArchivoTiempos;
    ArchivoTiempos = fopen("tiempos.txt", "r");

    if (ArchivoTiempos == NULL) 
    {
        printf("Error: no se pudo abrir el archivo tiempos.txt.\n");
        exit(1);
    }

    int num_auto;
    int vueltas;
    int min;
    float seg;
    int ncarrera;
    char etapa[14];

    int i = 0;

    fscanf(ArchivoTiempos, "%d %d %d %f %d %s", &num_auto, &vueltas, &min, &seg, &ncarrera, etapa);

    while (!(feof(ArchivoTiempos))) 
    {
        if ((strcmp(etapa, "final") == 0 && vueltas==25) || (strcmp(etapa, "clasificacion") == 0 && vueltas !=0))
        {
            tiempo[i].num_auto= num_auto;
            tiempo[i].vueltasCompletas = vueltas;
            tiempo[i].seg = (min*60)+seg;
            tiempo[i].numeroCarrera = ncarrera;
            strcpy(tiempo[i].etapa, etapa);
            i++;
        }
        fscanf(ArchivoTiempos, "%d %d %d %f %d %s", &num_auto, &vueltas, &min, &seg, &ncarrera, etapa);
    }

    for (int j = 0; j < i; j++) 
    {
        printf("piloto: %d\t %d\t %d\t %f\t  %d\t %s\t \n", j, tiempo[j].num_auto, tiempo[j].vueltasCompletas,  tiempo[j].seg, tiempo[j].numeroCarrera, tiempo[j].etapa);
    }

    fclose(ArchivoTiempos);
}

void datosCarrera(struct Tiempos tiempo[180], int nCarrera, struct unaCarrera carrera[60])
{
    int j=0;

    for (int i = 0; i < 180; i++) 
    {
        if (tiempo[i].numeroCarrera == nCarrera) 
        {
            carrera[j].num_auto = tiempo[i].num_auto;
            carrera[j].vueltasCompletas = tiempo[i].vueltasCompletas;
            carrera[j].tiempo = tiempo[i].seg;
            carrera[j].carre = tiempo[i].numeroCarrera;
            j++;
        }
    }

    for (int i = 0; i < j; i++) 
    {
        printf("%d\t %d\t %f\t %d\n", carrera[i].num_auto, carrera[i].vueltasCompletas,  carrera[i].tiempo, carrera[i].carre);
    }
}

int ACTCTC2024(struct Tiempos tiempo[180]){ //Función del menú 1

    int rta;

    printf("ACTC TC 2024\n");
    printf("\n  1-Pole Position Carrera\n");
    printf("\n  2-Podio Carrera\n");
    printf("\n  3-Salir\n");
    printf("\n  Opcion:");
    scanf("%d",&rta);

    while(rta>3||rta<1){//Validacion
        printf("Opcion invalida, por favor ingrese una opcion valida: ");
        scanf("%d",&rta);
    }

    printf("\n");

    return rta;
}

int MenuCarrera(struct Tiempos tiempo[180], struct unaCarrera carrera[60])//Función del menú 2
{
    int rta;

    printf("\n\nCarrera: \n");
    printf("\n  1-El calafate\n");
    printf("\n  2-Viedma\n");
    printf("\n  3-Neuquen\n");
    printf("\n  Opcion:");
    scanf("%d",&rta);

    while(rta>3||rta<1)//Validacion
    {
        printf("Opcion invalida, por favor ingrese una opcion valida: ");
        scanf("%d",&rta);
    }
    printf("\n");

    datosCarrera(tiempo, rta, carrera);

    return rta;
}

int main()
{
    struct Pilotos pilotos[60];
    struct Tiempos tiempo[180];
    struct unaCarrera carrera[60];
    int opcion;

    CargadatosPilotos(pilotos);
    CargarDatosTiempos(tiempo);
    opcion = ACTCTC2024(tiempo);

    while(opcion!=3) //Inicia ambos menues hasta que se desee salir  
    {
        inicializador(carrera);
        MenuCarrera(tiempo, carrera);
        opcion = ACTCTC2024(tiempo);
        
    }


    return 0;
}