#ifndef TELEMETRIA_OBC_H
#define TELEMETRIA_OBC_H

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include <stdint.h>


typedef struct {
    float temp_sensores[8];// Reservacion para los 8 sensores de temperatura I2C
    uint16_t tamano_flash_kb;// capacidad total de Flash en la bluepill
    uint16_t free_heap_rtos;// RAM libre
    uint16_t watermark_obc_task;// marca de agua que deja la tarea en la memoria stacka lo largo de la tarea
    uint8_t  estado_flash_ext;// estado de la memoria flash externa SPI //(0=OK, 1=BUSY, 2=ERROR)
} FrameOBC_t;
//nota: extern sirve para que entiendan que esta variable esta en otro archivo
extern FrameOBC_t mi_telemetria;
extern QueueHandle_t ColaLecturaOBCHandle;

//declaracion de la task
void OBC_IniciarLectura(void *argument);

#endif
