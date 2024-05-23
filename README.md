#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

void Cargadatos(){//Funcion para cargar tiempos.txt y pilotos.txt

    setlocale(LC_ALL,"");

    int num_auto, edad;

    char nom[41], ap[41], ciudad[41], marca[41], equipo[41];

    FILE *ArchivoPilotos;//Declaro primer archivo
    FILE *ArchivoTiempos;//Declaro segundo archivo

    ArchivoTiempos=fopen("tiempos.txt","r");//Abro archivo
    ArchivoPilotos = fopen("pilotos.txt","r");//Abro archivo

    if (ArchivoTiempos == NULL) {//Compruebo si lo puede abrir
        printf("Error: no se pudo abrir el archivo tiempos.txt.-\n");
        exit(1);
    }
    if (ArchivoPilotos == NULL) {//Compruebo si lo puede abrir
        printf("Error: no se pudo abrir el archivo pilotos.txt.-\n");
        exit(1);
    }

    fscanf(ArchivoPilotos,"%d %s %s %d %s %s %s",&num_auto, nom, ap, &edad, ciudad, marca, equipo);  //lee la primera linea del archivo.
    while(!(feof(ArchivoPilotos))){
        printf("%d\t %s\t %s\t %d\t %s\t %s\t %s\t \n", num_auto, nom, ap, edad, ciudad, marca, equipo);
        fscanf(ArchivoPilotos,"%d %s %s %d %s %s %s",&num_auto, nom, ap, &edad, ciudad, marca, equipo);
    }


    printf("\n\n-----------------------------------\n\n");

    fscanf(ArchivoTiempos,"%d %s %s %d %s %s %s",&num_auto, nom, ap, &edad, ciudad, marca, equipo);       //lee la primera linea del archivo.
    while(!(feof(ArchivoTiempos))){
        printf("%d\t %s\t %s\t %d\t %s\t %s\t %s\t \n", num_auto, nom, ap, edad, ciudad, marca, equipo);
        fscanf(ArchivoTiempos,"%d %s %s %d %s %s %s",&num_auto, nom, ap, &edad, ciudad, marca, equipo);
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
    while(rta>3||rta<1){
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
    while(rta>3||rta<1){
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

