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
    float seg;
    int numeroCarrera;
    char etapa[14];
};


struct unaCarrera
{
    int num_auto;
    float tiempo;
};


void validar(int *op)//Subrutina de validacion
{
    while(*op>4||*op<1)
    {
        printf("Opcion invalida, por favor ingrese una valida: ");
        scanf("%d",&*op);
    }
}


void inicializador(struct unaCarrera carrera[60])//Subrutina que inicializa los tiempos
{
    for (int j=0; j<60; j++)
    {
        carrera[j].tiempo = ((99*60)+99);
    }
}


void CargadatosPilotos(struct Pilotos pi[60]) //Subrutina para cargar pilotos.txt
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


void CargarDatosTiempos(struct Tiempos tiempo[360]) //Subrutina para cargar datos de tiempos.txt
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
            tiempo[i].seg = (min*60)+seg;
            tiempo[i].numeroCarrera = ncarrera;
            strcpy(tiempo[i].etapa, etapa);
            i++;
        }
        fscanf(ArchivoTiempos, "%d %d %d %f %d %s", &num_auto, &vueltas, &min, &seg, &ncarrera, etapa);
    }
    fclose(ArchivoTiempos);
}


void datosCarrera(struct Tiempos tiempo[360], int nCarrera, struct unaCarrera carrera[60], int etapa)//Subrutina que carga los datos que deseemos de una carrera dado su numero y etapa
{
    int j=0;
    char eta[14];


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


void ordenarSeleccion(struct unaCarrera carrera[60])//Subrutina que ordena struct unaCarrera carrera[60]
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


void podio(struct unaCarrera carrera[60], struct Pilotos pilotos[60])//Subrutina que obtiene y muestra los datos de los pilotos del podio de cada carrera
{
    ordenarSeleccion(carrera);

    for(int j=0;j<3;j++)
    {
        for(int i=0;i<60;i++)
        {
            if(pilotos[i].num_auto == carrera[j].num_auto)
            {
                printf("La %d posicion: es %s %s de la marca %s \n", j+1, pilotos[i].nom, pilotos[i].ap, pilotos[i].marca);
            }
        }
    }
}

void promedio(struct unaCarrera carrera[60]){

    int cant=0;
    float promedio, suma=0;

    for(int i =0; i<60; i++)
    {
        if(carrera[i].tiempo != (99*60)+99)
        {
            suma = suma + carrera[i].tiempo;
            cant++;
        }
    }
    promedio = suma/cant;

    printf("el promedio es %f \n",promedio);
}

int polepos(struct unaCarrera carrera[60], struct Pilotos pilotos[60])//Funcion que devuelve el indice del piloto que obtuvo la pole position
{
    ordenarSeleccion(carrera);

    int pole;

    for (int i = 0; i < 60; i++)
    {
        if (pilotos[i].num_auto == carrera[0].num_auto)
        {
            pole=i;
            break;
        }
    }
    return pole;
}

void ACTCTC2024() //Función del menú 1
{
    printf("ACTC TC 2024\n");
    printf("\n  1-Pole Position Carrera\n");
    printf("\n  2-Podio Carrera\n");
    printf("\n  3-Info particular\n");
    printf("\n  4-Salir\n");
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

int main(){
    struct Pilotos pilotos[60];
    struct Tiempos tiempo[360];
    struct unaCarrera carrera[60];
    int opcion1, opcion2, pole;

    CargadatosPilotos(pilotos);
    CargarDatosTiempos(tiempo);
   
    ACTCTC2024();
    scanf("%d",&opcion1);
    validar(&opcion1);

    while(opcion1!=4){ //Inicia ambos menues hasta que se desee salir
        inicializador(carrera);
        MenuCarrera();
        scanf("%d",&opcion2);//Recibe en numero de la carrera que queremos saber el podio
        validar(&opcion2);
        datosCarrera(tiempo, opcion2, carrera, opcion1);
        switch (opcion1)
        {
            case 1:
                pole=polepos(carrera, pilotos);
                printf("\n\nLa pole position fue del piloto %s %s\n\n",pilotos[pole].nom, pilotos[pole].ap);
                break;
            case 2:
                podio(carrera, pilotos);
                break;
            case 3:
                promedio(carrera);
                
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
