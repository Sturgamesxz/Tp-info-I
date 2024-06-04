#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

struct Pilotos
{
    char nom[41];
    char ap[41];
    int num_auto;
    int edad;
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

int cargarLineas(const char *filename) {
    FILE *archivo = fopen(filename, "r");
    if (archivo == NULL) {
        printf("Error: no se pudo abrir el archivo %s.\n", filename);
        exit(1);
    }

    int numLines = 0;
    char ch;
    while (!feof(archivo)) {
        ch = fgetc(archivo);
        if (ch == '\n') {
            numLines++;
        }
    }
    fclose(archivo);
    rewind(archivo);

    return numLines;
}

void CargadatosPilotos(struct Pilotos *pi, const char *filename, int tamanoPilotos){//Funcion para cargar pilotos.txt
    FILE *ArchivoPilotos;//Declaro primer archivo

    int num_auto, edad;
    char nom[41], ap[41], ciudad[41], marca[41], equipo[41];

    ArchivoPilotos = fopen(filename,"r");//Abro archivo

    if (ArchivoPilotos == NULL) {//Compruebo si lo puede abrir
        printf("Error: no se pudo abrir el archivo pilotos.txt.-\n");
        exit(1);
    }

    int i = 0;

    while(i < tamanoPilotos){
        fscanf(ArchivoPilotos,"%d %s %s %d %s %s %s",&num_auto, ap, nom, &edad, ciudad, marca, equipo);
        pi[i].num_auto = num_auto;
        
        strncpy(pi[i].nom, nom, sizeof(pi[i].nom) - 1);
        pi[i].nom[sizeof(pi[i].nom) - 1] = '\0';  // Asegurar que la cadena esté terminada

        strncpy(pi[i].ap, ap, sizeof(pi[i].ap) - 1);
        pi[i].ap[sizeof(pi[i].ap) - 1] = '\0';  // Asegurar que la cadena esté terminada

        pi[i].edad = edad;
        i++;

    }
    fclose(ArchivoPilotos);
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

    int tamanoPilotos = cargarLineas("pilotos.txt");
    //printf("Numero de pilotos: %d\n", tamanoPilotos);

    int tamanoTiempos = cargarLineas("tiempos.txt");
    //printf("Numero de pilotos: %d\n", tamanoTiempos);

    struct Tiempos ti[tamanoTiempos];

    Cargadatostiempos(ti, "tiempos.txt", tamanoTiempos);

    for(int i=0;i<tamanoTiempos; i++)
    {
        printf("%d\t %d\t %d\t %.2f\t %d\t %s\n", ti[i].num_autoTiempo, ti[i].vueltasCompletas, ti[i].min, ti[i].seg, ti[i].numeroCarrera, ti[i].etapa);
    }

    struct Pilotos pi[tamanoPilotos];

    CargadatosPilotos(pi, "pilotos.txt", tamanoPilotos);

    for(int i=0;i<tamanoPilotos; i++)
    {
        printf("%d\t %s\t %s\t %d\n", pi[i].num_auto, pi[i].ap, pi[i].nom, pi[i].edad);
    }


    while(ACTCTC2024()!=3){//Inicia ambos menues hasta que se desee salir
        MenuCarrera();
    }

    return 0;
}


