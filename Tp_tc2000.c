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
    char etapa[14];
};

struct unaCarrera
{
    int num_auto;
    float tiempo;
};

void validar(int *op)
{
    while(*op>3||*op<1)
    {
        printf("Opcion invalida, por favor ingrese una valida: ");
        scanf("%d",&*op);
    }
}

void inicializador(struct unaCarrera carrera[60])
{
    for (int j=0; j<60; j++)
    {
        carrera[j].tiempo = 9999,999;
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

void CargarDatosTiempos(struct Tiempos tiempo[360])
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

    // for (int j = 0; j < i; j++)
    // {
    //     printf("piloto: %d\t %d\t %d\t %f\t  %d\t %s\t \n", j, tiempo[j].num_auto, tiempo[j].vueltasCompletas,  tiempo[j].seg, tiempo[j].numeroCarrera, tiempo[j].etapa);
    // }

    fclose(ArchivoTiempos);
}

void datosCarrera(struct Tiempos tiempo[360], int nCarrera, struct unaCarrera carrera[60], int etapa)
{
    int j=0;
    char eta[14];

    inicializador(carrera);//Esto no sabemos por que lo hacemos, a veces cuando corriamos el menu varias veces nos desordenaba todo

    if(etapa ==1)
    {
        strcpy(eta, "clasificacion");
    }
    else
    {
        strcpy(eta, "final");
    }

    for (int i = 0; i < 360; i++)
    {
        if (tiempo[i].numeroCarrera == nCarrera && strcmp(eta,tiempo[i].etapa)==0)
        {
            carrera[j].num_auto = tiempo[i].num_auto;
            carrera[j].tiempo = tiempo[i].seg;
            j++;
        }
    }
}

void ordenarSeleccion(struct unaCarrera carrera[60])//Subrutina que ordena de menor a mayor (por selección)
{
    float auxTiempo, auxNumAuto, min;
    int pos, minPiloto;

    for (int i = 0; i < 60 ; i++)
    {
        min=carrera[i].tiempo;
        pos=i;

        for (int j = i + 1; j < 60; j++)
        {
            if (min > carrera[j].tiempo)
            {
                min = carrera[j].tiempo;
                pos = j;
            }
        }

        auxTiempo = carrera[i].tiempo;
        carrera[i].tiempo = carrera[pos].tiempo;
        carrera[pos].tiempo = auxTiempo;

        auxNumAuto = carrera[i].num_auto;
        carrera[i].num_auto = carrera[pos].num_auto;
        carrera[pos].num_auto = auxNumAuto;
    }
}

void podio(struct unaCarrera carrera[60], struct Pilotos pilotos[60])
{
    ordenarSeleccion(carrera);

   /* for(int i =0; i<60; i++)
    {
        printf("%d\t %f\t\n", carrera[i].num_auto,  carrera[i].tiempo);
    }
*/
    for(int j=0;j<3;j++)
    {
        for(int i=0;i<60;i++)
        {
            if(pilotos[i].num_auto == carrera[j].num_auto)
            {
                printf("  La %d posicion: es %s %s numero %d con un %s \n", j+1, pilotos[i].nom, pilotos[i].ap,pilotos[i].num_auto, pilotos[i].marca);
            }
        }
    }
    printf("\n");
}

void ACTCTC2024(){ //Función del menú 1

    printf("ACTC TC 2024\n");
    printf("\n  1-Pole Position Carrera\n");
    printf("\n  2-Podio Carrera\n");
    printf("\n  3-Salir\n");
    printf("\n  Opcion:");

}

void MenuCarrera()//Función del menú 2
{
    printf("\n\nCarrera: \n");
    printf("\n  1-El calafate\n");
    printf("\n  2-Viedma\n");
    printf("\n  3-Neuquen\n");
    printf("\n  Opcion:");
}
int main()
{
    struct Pilotos pilotos[60];
    struct Tiempos tiempo[360];
    struct unaCarrera carrera[60];

    int opcion1,opcion2,pole;

    CargadatosPilotos(pilotos);//Carga todos los datos de los pilotos
    CargarDatosTiempos(tiempo);//Carta todos los datos validos de los pilotos de clasificacion y final
    inicializador(carrera);//Inicializa el struct con tiempos 99999 para luego ordenar

    ACTCTC2024();
    scanf("%d",&opcion1);
    validar(&opcion1);


    while(opcion1!=3){ //Inicia ambos menues hasta que se desee salir
        switch (opcion1)
        {
            case 1://En caso que se quiera saber pole position
                    MenuCarrera();
                    scanf("%d",&opcion2);//Recibe en numero de la carrera que queremos saber el podio
                    validar(&opcion2);

                    datosCarrera(tiempo, opcion2, carrera, opcion1);
                    ordenarSeleccion(carrera);

                    pole=carrera[0].num_auto;

                    for(int i=0;i<60;i++)
                    {
                        if(pilotos[i].num_auto == carrera[0].num_auto)
                        {
                            printf("\n  La pole position fue de %s %s con un %s numero: %d\n\n", pilotos[i].nom, pilotos[i].ap, pilotos[i].marca,pole);
                        }
                    }
                break;

            case 2://En caso que se quiera saber podio

                   MenuCarrera();
                   scanf("%d",&opcion2);//Recibe en numero de la carrera que queremos saber el podio
                   validar(&opcion2);
                   printf("\n");

                    datosCarrera(tiempo, opcion2, carrera, opcion1);

                    podio(carrera, pilotos);

                break;
            default:
                break;
        }
        ACTCTC2024();
        scanf("%d",&opcion1);
        validar(&opcion1);
    }
    return 0;
}
