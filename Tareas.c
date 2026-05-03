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
void ConsultarTareas(Nodo *TareasPendientes,Nodo *TareasRealizadas);
Nodo * BuscarPorId(Nodo *Tarea,int Id);
Nodo * BuscarPorPalabraClave(Nodo *Tarea,char *palabra);
void MostrarUnaTarea(Nodo *nodo);
void LiberarMemoria(Nodo *Tarea);
int main () {
    srand(time(NULL));
    Nodo * Tareaspendientes=CrearListaVacia(); //apunta a NULL
    Nodo * TareasRealizadas=CrearListaVacia(); //apunta a NULL
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
                if(NodoAmover!=NULL) {
                    /*SE INSERTA EL NODO SI Y SOLO SI EXISTE LA TAREA CON LA ID BUSCADA*/
                    InsertarNodo(&TareasRealizadas,NodoAmover);
                }
                else {
                    printf("No se encontro una tarea con el id buscado\n");
                }
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


    /*CONSULTA DE TAREAS POR ID Y PALABRA CLAVE*/
    ConsultarTareas(Tareaspendientes,TareasRealizadas);
    if(Tareaspendientes!=NULL) {
        LiberarMemoria(Tareaspendientes);
    }
    if(TareasRealizadas!=NULL) {
        LiberarMemoria(TareasRealizadas);
    }
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
        printf("\nLa lista esta vacia\n");
    }
    else {
        while(aux!=NULL) {
            printf("\nTarea Id:%d",aux->T.TareaID);
            printf("\nDescripcion:%s",aux->T.Descripcion);
            printf("\nDuracion:%d",aux->T.Duracion);
            aux=aux->Siguiente;
            printf("\n");
        }
    }
    
}
Nodo * BuscarPorId(Nodo *Tarea,int Id) {
    Nodo *aux=Tarea;
    while(aux!=NULL) {
        if(aux->T.TareaID==Id) {
            return aux;
        }
        aux=aux->Siguiente;
    }
    return NULL;
}
Nodo * BuscarPorPalabraClave(Nodo *Tarea,char *palabra){
    Nodo *aux=Tarea;
    //RECORDAR QUE strstr devuelve un puntero si encuentra la palabra dentro de la frase, caso contrario devuelve NULL
    while(aux!=NULL) {
        if(strstr(aux->T.Descripcion, palabra)!=NULL) {
            return aux;
        }
        aux=aux->Siguiente;
    }
    return NULL;
}
void MostrarUnaTarea(Nodo *nodo) {
    if (nodo != NULL) {
        printf("\n--- Tarea Encontrada ---");
        printf("\nID: %d", nodo->T.TareaID);
        printf("\nDescripcion: %s", nodo->T.Descripcion);
        printf("\nDuracion: %d\n", nodo->T.Duracion);
    }
}
void ConsultarTareas(Nodo *TareasPendientes,Nodo *TareasRealizadas) {
    int opcion;
    printf("Seleccionar el tipo de consulta(1:ID o 2:Palabra Clave):");
    scanf("%d",&opcion);
    getchar();
    switch(opcion) {
        case 1:
            /*BUSQUEDA POR ID*/
            int IDbuscada;
            printf("Ingresar la id buscada:");
            scanf("%d",&IDbuscada);
            getchar();
            /*PRIMERO BUSCO EN TAREAS PENDIENTES*/
            if(TareasPendientes!=NULL) {
                printf("Busco en Tareas Pendientes...\n");
                Nodo *Buscarid=BuscarPorId(TareasPendientes,IDbuscada);
                if(Buscarid!=NULL) {
                    printf("Mostrar NODO\n");
                    MostrarUnaTarea(Buscarid);
                }
                else {
                    printf("No hay coincidencia\n");
                }
            }
            /*BUSCO EN TAREAS REALIZADAS*/
            if(TareasRealizadas!=NULL) {
                printf("Busco en Tareas Realizadas...\n");
                Nodo *Buscarid=BuscarPorId(TareasRealizadas,IDbuscada);
                if(Buscarid!=NULL) {
                    printf("Mostrar NODO\n");
                    MostrarUnaTarea(Buscarid);
                }
                else{
                    printf("No hay coincidencia\n");
                }
            }
            if(TareasPendientes==NULL && TareasRealizadas==NULL) {
                printf("Las listas estan vacias");
            }
        break;
        case 2:
            /*BUSQUEDA POR PALABRA CLAVE*/
            char palabraclave[50];
            printf("Ingresar la palabra clave:");
            gets(palabraclave);
            /*PRIMERO BUSCO EN TAREAS PENDIENTES*/
            if(TareasPendientes!=NULL) {
                printf("Busco en Tareas Pendientes...\n");
                Nodo *BuscarPalabra=BuscarPorPalabraClave(TareasPendientes,palabraclave);
                if(BuscarPalabra!=NULL) {
                    printf("Mostrar NODO\n");
                    MostrarUnaTarea(BuscarPalabra);
                }
                else {
                    printf("No hay coincidencia\n");
                }
            }
            /*BUSCO EN TAREAS REALIZADAS*/
            if(TareasRealizadas!=NULL) {
                printf("Busco en Tareas Realizadas...\n");
                Nodo *BuscarPalabra=BuscarPorPalabraClave(TareasRealizadas,palabraclave);
                if(BuscarPalabra!=NULL) {
                    printf("Mostrar NODO\n");
                    MostrarUnaTarea(BuscarPalabra);
                }
                else {
                    printf("No hay coincidencia\n");
                }
            }
            if(TareasPendientes==NULL && TareasRealizadas==NULL) {
                printf("Las listas estan vacias");
            }
        break;
    }
}
void LiberarMemoria(Nodo *Tarea) {
    /*Genero un nodo auxiliar para poder recorrer toda la lista sin tener fuga de memoria*/
    Nodo *aux;
    while(Tarea!=NULL) {
        aux=Tarea; //guardo el nodo actual
        Tarea=Tarea->Siguiente;
        free(aux->T.Descripcion);
        free(aux);
    }
}