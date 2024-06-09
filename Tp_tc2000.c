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
    int num_autoTiempo;
    int vueltasCompletas;
    int min;
    float seg;
    int numeroCarrera;
    char etapa[41];
};

void CargadatosPilotos(struct Pilotos pi[60]) { // Función para cargar pilotos.txt

    setlocale(LC_ALL, "");

    int num_auto, edad;
    char nom[41], ap[41], ciudad[41], marca[41], equipo[41];

    FILE *ArchivoPilotos; // Declaro primer archivo
    ArchivoPilotos = fopen("pilotos.txt", "r"); // Abro archivo

    if (ArchivoPilotos == NULL) { // Compruebo si lo puede abrir
        printf("Error: no se pudo abrir el archivo pilotos.txt.\n");
        exit(1);
    }

    int i = 0;


    fscanf(ArchivoPilotos,"%d %s %s %d %s %s %s",&num_auto, nom, ap, &edad, ciudad, marca, equipo);

    while (!(feof(ArchivoPilotos))) {

        pi[i].num_auto=num_auto;
        strcpy(pi[i].nom,nom);
        strcpy(pi[i].ap,ap);
        strcpy(pi[i].marca,marca);

        fscanf(ArchivoPilotos,"%d %s %s %d %s %s %s",&num_auto, nom, ap, &edad, ciudad, marca, equipo);
        i++;
    }

    printf("\n\n\n\n\n\n\n");

    for(int i=0;i<60;i++){//muestreo de prueba

         printf("%d\t %s\t %s\t  %s\t \n\n", pi[i].num_auto, pi[i].nom, pi[i].ap, pi[i].marca);
    }



    fclose(ArchivoPilotos); // Cierro archivo
}
void Cargadatostiempos(struct Tiempos *ti, const char *filename, int tamanoTiempos){//Funcion para cargar tiempos.txt
    setlocale(LC_ALL,"");

    FILE *ArchivoTiempos;//Declaro primer archivo

    ArchivoTiempos = fopen(filename,"r");//Abro archivo

    if (ArchivoTiempos == NULL) {//Compruebo si lo puede abrir
        printf("Error: no se pudo abrir el archivo pilotos.txt.-\n");
        exit(1);
    }

    int i=0;
    while (i < tamanoTiempos) {
        fscanf(ArchivoTiempos, "%d %d %d %f %d %s", &ti[i].num_autoTiempo, &ti[i].vueltasCompletas, &ti[i].min, &ti[i].seg, &ti[i].numeroCarrera, ti[i].etapa);
        // printf("%d\t %d\t %d\t %.2f\t %d\t %s\n", ti[i].num_autoTiempo, ti[i].vueltasCompletas, ti[i].min, ti[i].seg, ti[i].numeroCarrera, ti[i].etapa);
        i++;
    }
    fclose(ArchivoTiempos);
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
   struct Pilotos pi[59];

    CargadatosPilotos(pi);

    while(ACTCTC2024()!=3){//Inicia ambos menues hasta que se desee salir
        MenuCarrera();
    }

    return 0;
}
