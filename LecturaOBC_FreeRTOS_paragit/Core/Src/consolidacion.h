#ifndef CONSOLIDACION_H
#define CONSOLIDACION_H

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "telemetria_obc.h"

void OBC_IniciarConsolidacion(void *argument);

#endif
