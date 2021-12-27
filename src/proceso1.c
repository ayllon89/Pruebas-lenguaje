#include "proceso1.h"
#include <semaphore.h>

void funcion(void)
{
t_log* logger;
//sleep(1);
logger = iniciar_logger();
log_info(logger,"estoy logueando dentro de la funcion");

}

/*struct estructura 
{
	int valor1;
	int valor2;
};  luego dentro del main haces: struct estructura e;e.valor1=2;e->valor2=3; */

/*
typedef struct estructura 
{
	int valor1;
	int valor2;
} estruc; esto es para definir tus tipos de datos, aca lo que haces es crear el tipo de dato "estruc" luego dentro del main haces:estruc e;e.valor1=2;e.valor2=3;*/

typedef struct estructura 
{
	int valor1;
	int valor2;
} estruc;

estruc* funcion2(void)
{
	estruc* v=malloc(sizeof(estruc));
	return v;
}


int main(){

estruc* e;
//(*e).valor1=1; //la otra forma es hacer e->valor1=1;  recorda que esta notacion es solo para punteros a estructuras!!, si es estructura comun ahi solo funciona el operador punto
e->valor1=5;
funcion();

printf("el valor dentro de proceso 1 es: %d\n",e->valor1);

//funcion3();


	/*t_log* logger = log_create("./cfg/proceso1.log", "PROCESO1", true, LOG_LEVEL_INFO);
    log_info(logger, "Soy el proceso 1! %s", mi_funcion_compartida());
    log_destroy(logger);

char* arrayPunteros[10]; //es un array de punteros, osea cada elemento es un puntero

int* p = malloc(sizeof(int) * 2);

p[70]=1;


int lista[3];

lista[0]=20;
lista[1]=30;
lista[2]=40;

//recorda que tanto en los arrays o punteros vos pasas como argumento la direccion
funcion(p+1);

//%p es para ver la direccion

printf("%d",p[70]);*/

//int un_nro; // Variable entera
//int *int_ptr; // Puntero a entero
//un_nro = 2;
//int_ptr = &un_nro;
//printf("int_ptr = %p\n",int_ptr); // Por pantalla se visualizará la posición de memoria de la variable un_nro, dado que eso apunta nuestro puntero.
//printf("*int_ptr=%d\n",*int_ptr); // Por pantalla se visualizará "lo que tiene dentro" nuestro puntero, es decir, el valor 2
//printf("&int_ptr=%p\n",&int_ptr);  // Por pantalla se visualizará la dirección de memoria de nuestro puntero

//double * p;

pthread_t hilo;
printf("empiezo a ejecutar el hilo \n");
pthread_create(&hilo,NULL,(void*)funcion,NULL); //el segundo argumento esta relacionado al stack del hilo, el cuarto argumento seria el argumento
//que llevaria tu funcion, si tu fucion lleva mucho argumentos lo mejor es manejarlo con un struct (un solo arugmento pero adentro podes agregar mas cosas)
//o tambien un puntero a un array


//pthread_join(hilo,NULL); //esto hace que se trunque ahi hasta que termine de ejecutar el hilo
//pthread_detach(hilo); //el detach no trunca ahi sigue a la linea que sigue, lo unico que haces ahi es que si el programa principal sigue ejecutnado 
//a ese hilo le indicias que cuando termine libere sus recursos, eso si si el programa que llamo al hilo puede terminar antes de que termine al hilo
//provovando que el hilo no termine de ejecutarse,esto sirve para no truncar el programa en ese instruccion y continue ejecutandose
printf("termine de ejecutar el hilo \n");


sem_t semaforo;
sem_init(&semaforo,0,1); //inicio el semaforo en 1
sem_wait(&semaforo);
sem_post(&semaforo);



/*pthread_mutex_t semaforo;   //este semaforo solo sirve para mutua exclusion no es un semaforo contador
pthread_mutex_init(&semaforo,NULL);
pthread_mutex_lock(&semaforo);
pthread_mutex_unlock(&semaforo);*/

	/*---------------------------------------------------PARTE 2-------------------------------------------------------------*/

	int conexion;
	char* ip;
	char* puerto;
	char* valor;

	t_log* logger;
	t_config* config;

	/* ---------------- LOGGING ---------------- */

	logger = iniciar_logger();
	log_info(logger,"estoy logueando!");


	// Usando el logger creado previamente
	// Escribi: "Hola! Soy un log"


	/* ---------------- ARCHIVOS DE CONFIGURACION ---------------- */

	config = iniciar_config();
	ip=config_get_string_value(config,"ip");
	puerto=config_get_string_value(config,"puerto");
	log_info(logger,"lei la ip:%s y el puerto:%s\n",ip,puerto);

	// Usando el config creado previamente, leemos los valores del config y los 
	// dejamos en las variables 'ip', 'puerto' y 'valor'

	// Loggeamos el valor de config


	/* ---------------- LEER DE CONSOLA ---------------- */

	leer_consola(logger);

	/*---------------------------------------------------PARTE 3-------------------------------------------------------------*/

	// ADVERTENCIA: Antes de continuar, tenemos que asegurarnos que el servidor esté corriendo para poder conectarnos a él

	// Creamos una conexión hacia el servidor
	conexion = crear_conexion(ip, puerto);

	// Enviamos al servidor el valor de CLAVE como mensaje

	// Armamos y enviamos el paquete
	paquete(conexion);

	terminar_programa(conexion, logger, config);

	/*---------------------------------------------------PARTE 5-------------------------------------------------------------*/
	// Proximamente
}

t_log* iniciar_logger(void)
{
	t_log* nuevo_logger;
	if ((nuevo_logger=log_create("tp0.log","tp0",1,LOG_LEVEL_INFO))==NULL)  //el primer argumento indicas el nombre del archivo, el segundo es el nombre de la linea de log
	{
		printf("no se pudo iniciar el logger");
		exit(1);
	}
	return nuevo_logger;
}


t_config* iniciar_config(void)
{
	t_config* nuevo_config;

	if((nuevo_config=config_create("./tp0.config"))==NULL)
	{
		printf("no se puede crear el config");
		exit(2);
	}
	return nuevo_config;
}

void leer_consola(t_log* logger)
{
	char* leido;

	// La primera te la dejo de yapa
	leido = readline(">ingresar linea:");

	while(strcmp(leido,"") != 0)  //me fijo que lo que ingreso el usuario no sea vacio, si es vacio salgo del while
	{
		log_info(logger,leido);
		free(leido);
		leido = readline(">ingresar linea:");
	}

	/*while(leido[0]!='\0')  //otra forma de hacerlo
	{
		log_info(logger,leido);
		free(leido);
		leido = readline(">ingresar linea:");
	}*/ 

	// El resto, las vamos leyendo y logueando hasta recibir un string vacío

	// ¡No te olvides de liberar las lineas antes de regresar!
	free(leido);

}

void paquete(int conexion)
{
	// Ahora toca lo divertido!
	char* leido;
	t_paquete* paquete;

	// Leemos y esta vez agregamos las lineas al paquete


	// ¡No te olvides de liberar las líneas y el paquete antes de regresar!
	
}

void terminar_programa(int conexion, t_log* logger, t_config* config)
{
	/* Y por ultimo, hay que liberar lo que utilizamos (conexion, log y config) 
	  con las funciones de las commons y del TP mencionadas en el enunciado */
	  if(logger!=NULL)
	  {
		log_destroy(logger);
	  }
	  if(config!=NULL)
	  {
		config_destroy(config);
	  }
}
