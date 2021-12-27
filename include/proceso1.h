#ifndef PROCESO1_H
#define PROCESO1_H

#include <stdio.h>
#include <commons/log.h>
#include <stdbool.h>

#include<stdlib.h>
#include<commons/string.h>
#include<commons/config.h>
#include<readline/readline.h>
#include<pthread.h>

#include "utils.h"

int valorNumero;
t_log* iniciar_logger(void);
t_config* iniciar_config(void);
void leer_consola(t_log*);
void paquete(int);
void terminar_programa(int, t_log*, t_config*);

#endif