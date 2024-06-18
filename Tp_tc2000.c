#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

// Definición de las estructuras
struct Pilotos {
    char nom[41];
    char ap[41];
    char marca[41];
    int num_auto;
};

struct Tiempos {
    int num_auto;
    float seg;
    int numeroCarrera;
    char etapa[14];
};

struct unaCarrera {
    int num_auto;
    float tiempo;
};

// Subrutina de validación
void validar(int *op) {
    while (*op > 3 || *op < 1) {
        printf("Opcion invalida, por favor ingrese una valida: ");
        scanf("%d", op);
    }
}

// Subrutina que inicializa los tiempos
void inicializador(struct unaCarrera carrera[60]) {
    for (int j = 0; j < 60; j++) {
        carrera[j].tiempo = ((99 * 60) + 99);
    }
}

// Subrutina para cargar datos de pilotos
void CargadatosPilotos(struct Pilotos pi[60]) {
    setlocale(LC_ALL, "");

    int num_auto, edad;
    char nom[41], ap[41], ciudad[41], marca[41], equipo[41];

    FILE *ArchivoPilotos;
    ArchivoPilotos = fopen("pilotos.txt", "r");

    if (ArchivoPilotos == NULL) {
        printf("Error: no se pudo abrir el archivo pilotos.txt.\n");
        exit(1);
    }

    int i = 0;
    fscanf(ArchivoPilotos, "%d %s %s %d %s %s %s", &num_auto, nom, ap, &edad, ciudad, marca, equipo);

    while (!(feof(ArchivoPilotos))) {
        pi[i].num_auto = num_auto;
        strcpy(pi[i].nom, nom);
        strcpy(pi[i].ap, ap);
        strcpy(pi[i].marca, marca);

        fscanf(ArchivoPilotos, "%d %s %s %d %s %s %s", &num_auto, nom, ap, &edad, ciudad, marca, equipo);
        i++;
    }
    fclose(ArchivoPilotos);
}

// Subrutina para cargar datos de tiempos
void CargarDatosTiempos(struct Tiempos tiempo[360]) {
    FILE *ArchivoTiempos;
    ArchivoTiempos = fopen("tiempos.txt", "r");

    if (ArchivoTiempos == NULL) {
        printf("Error: no se pudo abrir el archivo tiempos.txt.\n");
        exit(1);
    }

    int num_auto, vueltas, min, ncarrera;
    float seg;
    char etapa[14];
    int i = 0;

    fscanf(ArchivoTiempos, "%d %d %d %f %d %s", &num_auto, &vueltas, &min, &seg, &ncarrera, etapa);

    while (!(feof(ArchivoTiempos))) {
        if ((strcmp(etapa, "final") == 0 && vueltas == 25) || (strcmp(etapa, "clasificacion") == 0 && vueltas != 0)) {
            tiempo[i].num_auto = num_auto;
            tiempo[i].seg = (min * 60) + seg;
            tiempo[i].numeroCarrera = ncarrera;
            strcpy(tiempo[i].etapa, etapa);
            i++;
        }
        fscanf(ArchivoTiempos, "%d %d %d %f %d %s", &num_auto, &vueltas, &min, &seg, &ncarrera, etapa);
    }
    fclose(ArchivoTiempos);
}

// Subrutina que carga los datos de una carrera dado su número y etapa
void datosCarrera(struct Tiempos tiempo[360], int nCarrera, struct unaCarrera carrera[60], int etapa) {
    int j = 0;
    char eta[14];
    printf("etapa %d", etapa);
    if (etapa == 1) {
        strcpy(eta, "clasificacion");
    } else {
        strcpy(eta, "final");
    }

    for (int i = 0; i < 360; i++) {
        if (tiempo[i].numeroCarrera == nCarrera && strcmp(eta, tiempo[i].etapa) == 0) {
            carrera[j].num_auto = tiempo[i].num_auto;
            carrera[j].tiempo = tiempo[i].seg;
            j++;
        }
    }
}

// Subrutina que ordena struct unaCarrera carrera[60]
void ordenarSeleccion(struct unaCarrera carrera[60]) {
    float auxTiempo, auxNumAuto, min;
    int pos, minPiloto;

    for (int i = 0; i < 60; i++) {
        min = carrera[i].tiempo;
        pos = i;

        for (int j = i + 1; j < 60; j++) {
            if (min > carrera[j].tiempo) {
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

// Subrutina que obtiene y muestra los datos de los pilotos del podio de cada carrera
void podio(struct unaCarrera carrera[60], struct Pilotos pilotos[60]) {
    ordenarSeleccion(carrera);

    for (int j = 0; j < 3; j++) {
        for (int i = 0; i < 60; i++) {
            if (pilotos[i].num_auto == carrera[j].num_auto) {
                printf("La %d posicion: es %s %s de la marca %s \n", j + 1, pilotos[i].nom, pilotos[i].ap, pilotos[i].marca);
            }
        }
    }
}

// Función que devuelve el índice del piloto que obtuvo la pole position
int polepos(struct unaCarrera carrera[60], struct Pilotos pilotos[60]) {
    ordenarSeleccion(carrera);

    int pole;

    for (int i = 0; i < 60; i++) {
        if (pilotos[i].num_auto == carrera[0].num_auto) {
            pole = i;
            break;
        }
    }
    return pole;
}

// Función del menú 1
void ACTCTC2024() {
    printf("ACTC TC 2024\n");
    printf("\n  1-Pole Position Carrera\n");
    printf("\n  2-Podio Carrera\n");
    printf("\n  3-Salir\n");
    printf("\n  Opcion:");
}

// Función del menú 2
void MenuCarrera() {
    printf("\n\nCarrera: \n");
    printf("\n  1-El calafate\n");
    printf("\n  2-Viedma\n");
    printf("\n  3-Neuquen\n");
    printf("\n  Opcion:");
}

// Función principal
int main() {
    struct Pilotos pilotos[60];
    struct Tiempos tiempo[360];
    struct unaCarrera carrera[60];
    int opcion1, opcion2, pole;

    CargadatosPilotos(pilotos);
    CargarDatosTiempos(tiempo);

    ACTCTC2024();
    scanf("%d", &opcion1);
    validar(&opcion1);

    while (opcion1 != 3) { // Inicia ambos menús hasta que se desee salir
        inicializador(carrera);
        MenuCarrera();
        scanf("%d", &opcion2); // Recibe el número de la carrera que queremos saber el podio
        validar(&opcion2);

        switch (opcion1) {
            case 1:
                datosCarrera(tiempo, opcion2, carrera, opcion1);
                pole = polepos(carrera, pilotos);
                printf("\n\nLa pole position fue del piloto %s %s\n\n", pilotos[pole].nom, pilotos[pole].ap);
                break;
            case 2:        
                datosCarrera(tiempo, opcion2, carrera, opcion1);
                podio(carrera, pilotos);
                break;
            default:
                break;
        }
        ACTCTC2024();
        scanf("%d", &opcion1);
        validar(&opcion1);
    }
    return 0;
}
