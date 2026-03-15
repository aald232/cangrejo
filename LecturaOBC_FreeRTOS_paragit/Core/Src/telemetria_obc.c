#include "telemetria_obc.h"
#include "main.h"

FrameOBC_t mi_telemetria;

void OBC_IniciarLectura(void *argument)
{
    TickType_t LastWakeTime = xTaskGetTickCount();//nota :Su función es almacenar un número exacto: el momento cronológico preciso en que la tarea inició.
    const TickType_t intrv_20 = pdMS_TO_TICKS(20000); // los 20 segundos

    FrameOBC_t* ptr_datos = &mi_telemetria;// puntero donde se esta guardando mi_telemetria

    for(;;)
    {
        // placeholder para los sensores
        /*for(int i=0; i<8; i++){
            mi_telemetria.temp_sensores[i] = 0.0f; // aca va el código de los sensores I2C
        }
        */
        //se lee el registro que tiene por defecto la bluepill para el tamaño de la flash
        mi_telemetria.tamano_flash_kb = *((uint16_t*)0x1FFFF7E0);
        //se cuenta cuantos de los 10KB en el heap estan libres
        mi_telemetria.free_heap_rtos = xPortGetFreeHeapSize();
        //se lee el minimo de espacio libre que tuvo la task desde que se encendio (ojo se mide en words)
        mi_telemetria.watermark_obc_task = uxTaskGetStackHighWaterMark(NULL);//word = 4bytes

        //Apartado para la flash externa SPI
        mi_telemetria.estado_flash_ext = 0; //estoy asumiendo OK
        xQueueOverwrite(ColaLecturaOBCHandle, &ptr_datos);//(ojo)

        //sleep
        vTaskDelayUntil(&LastWakeTime, intrv_20);
    }
}
