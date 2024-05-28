#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

struct Pilotos
{
    int *num_auto;
    char (*nom)[41];
    char (*ap)[41];
    int *edad;
};

struct Tiempos
{
    int *num_autoTiempo;
    int *vueltasCompletas;
    int *min;
    float *seg;
    int *numeroCarrera;
    char (*etapa)[41];  
};

void Cargadatos(){//Funcion para cargar tiempos.txt y pilotos.txt
    setlocale(LC_ALL,"");

    int num_auto, edad;
    char nom[41], ap[41], ciudad[41], marca[41], equipo[41];
    int numLines = 0;

    FILE *ArchivoPilotos;//Declaro primer archivo

    ArchivoPilotos = fopen("pilotos.txt","r");//Abro archivo

    if (ArchivoPilotos == NULL) {//Compruebo si lo puede abrir
        printf("Error: no se pudo abrir el archivo pilotos.txt.-\n");
        exit(1);
    }

    struct Pilotos pi;

    char ch;
    while (!feof(ArchivoPilotos)) {
        ch = fgetc(ArchivoPilotos);
        if (ch == '\n') {
            numLines++;
        }
    }
    rewind(ArchivoPilotos); // Volver al principio del archivo


    int i = 0;

    pi.nom = (char (*)[41])malloc(numLines * sizeof(*pi.nom));     
    pi.ap = (char (*)[41])malloc(numLines * sizeof(*pi.ap));     
    pi.num_auto = (int *)malloc(numLines * sizeof(int));
    pi.edad = (int *)malloc(numLines * sizeof(int));

    while(fscanf(ArchivoPilotos,"%d %s %s %d %s %s %s",&num_auto, ap, nom, &edad, ciudad, marca, equipo) == 7)
    {
        pi.num_auto[i] = num_auto;
        
        strncpy(pi.nom[i], nom, sizeof(pi.nom[i]) - 1);
        pi.nom[i][sizeof(pi.nom[i]) - 1] = '\0';  // Asegurar que la cadena esté terminada

        strncpy(pi.ap[i], ap, sizeof(pi.ap[i]) - 1);
        pi.ap[i][sizeof(pi.ap[i]) - 1] = '\0';  // Asegurar que la cadena esté terminada

        pi.edad[i] = edad;

        //printf("%d\t %s\t %s\t %d\t  \n", num_auto, nom, ap, edad);
        
        i++;
    }
    fclose(ArchivoPilotos);

    // for (int j = 0; j < i; j++)
    // {
    //     printf("auto: %d \n",pi.num_auto[j]);
    //     printf("nombre: %s \n",pi.nom[j]);
    //     printf("apellido: %s \n",pi.ap[j]);
    //     printf("edad: %d \n",pi.edad[j]);
    // }
    
    printf("\n\n-----------------------------------\n\n");

    int q=0;

    FILE *ArchivoTiempos;//Declaro segundo archivo
    ArchivoTiempos = fopen("tiempos.txt","r");//Abro archivo
    
    numLines = 0;
    
    char ch1;
    while (!feof(ArchivoTiempos)) {
        ch1 = fgetc(ArchivoTiempos);
        if (ch1 == '\n') {
            numLines++;
        }
    }
    rewind(ArchivoTiempos); // Volver al principio del archivo

    struct Tiempos ti;

    int num_autoTiempo, vueltasCompletas, min, numeroCarrera;
    char etapa[41];
    float seg;
    
    ti.num_autoTiempo = (int *)malloc(numLines * sizeof(int));
    ti.vueltasCompletas = (int *)malloc(numLines * sizeof(int));
    ti.min = (int *)malloc(numLines * sizeof(int));
    ti.seg = (float *)malloc(numLines * sizeof(float));
    ti.numeroCarrera = (int *)malloc(numLines * sizeof(int));
    ti.etapa = (char (*)[41])malloc(numLines * sizeof(*ti.etapa)); 

    if (ArchivoTiempos == NULL) {//Compruebo si lo puede abrir
        printf("Error: no se pudo abrir el archivo tiempos.txt.-\n");
        exit(1);
    }

    while(fscanf(ArchivoTiempos, "%d %d %d %f %d %s", &num_autoTiempo, &vueltasCompletas, &min, &seg, &numeroCarrera, etapa)==6) 
    {
        ti.num_autoTiempo[q]= num_autoTiempo;
        ti.vueltasCompletas[q] = vueltasCompletas;
        ti.min[q] = min;
        ti.seg[q] = seg;
        ti.numeroCarrera[q] = numeroCarrera;

        strncpy(ti.etapa[q], etapa, sizeof(ti.etapa[q]) - 1);
        ti.etapa[q][sizeof(ti.etapa[q]) - 1] = '\0';  // Asegurar que la cadena esté terminada

        //printf("%d\t %d\t %d\t %f\t %d\t %s\t\n", num_autoTiempo, vueltasCompletas, min, seg,numeroCarrera, etapa);
        
        q++;

        //printf("q es %d \n",q);

    }
    fclose(ArchivoPilotos);

    // for (int j = 0; j < 10; j++)
    // {
    //     printf("num_autoTiempo: %d \n",ti.num_autoTiempo[j]);
    //     printf("vueltasCompletas: %d \n",ti.vueltasCompletas[j]);
    //     printf("min: %d \n",ti.min[j]);
    //     printf("seg: %f \n",ti.seg[j]);
    //     printf("numeroCarrera: %d \n",ti.numeroCarrera[j]);
    //     printf("etapa: %s \n",ti.etapa[j]);
    // }

    free(pi.num_auto);
    free(pi.nom);
    free(pi.ap);
    free(pi.edad);

    free(ti.num_autoTiempo);
    free(ti.vueltasCompletas);
    free(ti.min);
    free(ti.seg);
    free(ti.numeroCarrera);
    free(ti.etapa);
    for (int j = 0; j < 10; j++)
    {
        printf("Segnunfa");

        printf("num_autoTiempo: %d \n",ti.num_autoTiempo[j]);
        printf("vueltasCompletas: %d \n",ti.vueltasCompletas[j]);
        printf("min: %d \n",ti.min[j]);
        printf("seg: %f \n",ti.seg[j]);
        printf("numeroCarrera: %d \n",ti.numeroCarrera[j]);
        printf("etapa: %s \n",ti.etapa[j]);
    }
    
}
int ACTCTC2024(){ //Función del menú 1

    int rta;

    printf("ACTC TC 2024\n");
    printf("\n  1-Pole Position Carrera\n");
    printf("\n  2-Podio Carrera\n");
    printf("\n  3-Salir\n");
    printf("\n  Opcion:");
    scanf("%d",&rta);
    while(rta>3||rta<1){//vValidacion
        printf("Opcion invalida, por favor ingrese una opcion valida: ");
        scanf("%d",&rta);
   }
    printf("\n");

    return rta;

}
int MenuCarrera(){//Función del menú 2

    int rta;

    printf("\n\nCarrera: \n");
    printf("\n  1-El calafate\n");
    printf("\n  2-Viedma\n");
    printf("\n  3-Neuquen\n");
    printf("\n  Opcion:");
    scanf("%d",&rta);
    while(rta>3||rta<1){//7Validacion
        printf("Opcion invalida, por favor ingrese una opcion valida: ");
        scanf("%d",&rta);
   }
    printf("\n");


    return rta;
}
int main()
{
    Cargadatos();//Carga y muestra en pantalla ambos archivos

    while(ACTCTC2024()!=3){//Inicia ambos menues hasta que se desee salir
    MenuCarrera();
    }

    return 0;
}


