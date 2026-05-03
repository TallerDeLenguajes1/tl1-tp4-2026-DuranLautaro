#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
typedef struct Tarea{
int TareaID;//Numérico autoincremental comenzando en 1000
char *Descripcion; //
int Duracion; // entre 10 – 100
} Tarea;
typedef struct Nodo{
    Tarea T;
    struct Nodo *Siguiente;
}Nodo;
Nodo * CrearListaVacia();
Nodo * CrearTarea(int valor);
void InsertarNodo(Nodo ** Tarea , Nodo *Nodo);
Nodo * QuitarTarea(Nodo ** Tarea, int idbuscado);
void MostrarTareas(Nodo *Tarea);
int main () {
    srand(time(NULL));
    Nodo * Tareaspendientes=CrearListaVacia(); //apunta a NULL
    Nodo * TareasRealizadas=CrearListaVacia();
    int id=1000;
    int seleccionar;
    /*----SOLICITUD DE TAREAS PENDIENTES*----*/

    do {
        printf("Desea ingresar una tarea?\n");
        printf("0:Finalizar la carga\n1:Cargar Tarea\nSeleccione:");
        scanf("%d",&seleccionar);
        getchar();
        switch(seleccionar) {
            case 1:
                Nodo * NuevaTarea=CrearTarea(id);
                InsertarNodo(&Tareaspendientes,NuevaTarea);
            break;
        }
        id++;
    }while(seleccionar!=0);


    /*----SOLICITUD DE TAREAS REALIZADAS----*/
    int seleccionar2,idbuscado;
    do {
        printf("Hay tareas realizada?\n");
        if(Tareaspendientes!=NULL) {
            printf("0:Finalizar la carga\n1:Cargar Tarea Realizada\nSeleccione:");
            scanf("%d",&seleccionar2);
            getchar();
            switch(seleccionar2) {
            case 1:
                printf("Ingresar la id de la tarea a buscar:\n");
                scanf("%d",&idbuscado);
                getchar();
                Nodo * NodoAmover=QuitarTarea(&Tareaspendientes,idbuscado);
                InsertarNodo(&TareasRealizadas,NodoAmover);

            break;
            }
        }
        else {
            printf("No hay mas tareas pendientes\n");
        }
    }while(seleccionar2!=0 && Tareaspendientes!=NULL);
    /*MOSTRAR TAREAS PENDIENTES Y REALIZADAS*/
    printf("---Lista de Tareas Pendientes---");
    MostrarTareas(Tareaspendientes);
    printf("---Lista de Tareas Realizadas---");
    MostrarTareas(TareasRealizadas);
    return 0;
}
Nodo * CrearListaVacia(){
    return NULL;
}
Nodo * CrearTarea(int valor)
{
Nodo * NNodo = (Nodo *) malloc (sizeof(Nodo));
    NNodo->T.TareaID=valor;
    char descripcion[50];
    int duracion;
    printf("Ingresar descripcion de tarea:");
    gets(descripcion);
    int longitud=strlen(descripcion);
    printf("Generando aleatoriamente la duracion de la tarea:");
    duracion=rand()%100+10;
    NNodo->T.Descripcion=(char *)malloc(longitud*sizeof(char)+1);
    strcpy(NNodo->T.Descripcion,descripcion);
    NNodo->T.Duracion=duracion;
    NNodo->Siguiente = NULL;
    return NNodo;
}
void InsertarNodo(Nodo ** Tarea , Nodo *Nodo)
{
    Nodo -> Siguiente = *Tarea;
    *Tarea = Nodo ;
}
Nodo * QuitarTarea(Nodo ** Tarea, int idbuscado)
{
    Nodo *aux = *Tarea;
    Nodo *anterior = NULL;

    while (aux != NULL && aux->T.TareaID != idbuscado) {
        anterior = aux;
        aux = aux->Siguiente;
    }

    if (aux != NULL) {
        if (anterior == NULL) {
            *Tarea=aux->Siguiente;
        } else {
            anterior->Siguiente = aux->Siguiente;
        }
        aux->Siguiente = NULL; 
    }
    return aux;
}

void MostrarTareas(Nodo *Tarea) {
    Nodo *aux=Tarea;
    if(aux==NULL) {
        printf("La lista esta vacia\n");
    }
    while(aux!=NULL) {
        printf("\nTarea Id:%d",aux->T.TareaID);
        printf("\nDescripcion:%s",aux->T.Descripcion);
        printf("\nDuracion:%d",aux->T.Duracion);
        aux=aux->Siguiente;
    }
}
