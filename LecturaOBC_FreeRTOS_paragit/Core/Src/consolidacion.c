#include "consolidacion.h"
#include "main.h"

void OBC_IniciarConsolidacion(void *argument)
{
    TickType_t LastWakeTime = xTaskGetTickCount();
    const TickType_t intrv_70 = pdMS_TO_TICKS(70000); //los 70 segundos

    // Variable temporal para guardar el PUNTERO que sacaremos de la cola
    FrameOBC_t* ptr_recibido;

    for(;;)
    {

        //se pide leer la cola, como el dato era un puntero, se recibe uno. Si se tiene el puntero entra al if
        if(xQueueReceive(ColaLecturaOBCHandle, &ptr_recibido, 0) == pdPASS)//tiempo de espera 0
        {
            uint16_t flash_actual = ptr_recibido->tamano_flash_kb;
            uint16_t ram_actual = ptr_recibido->free_heap_rtos;
            uint16_t watermark = ptr_recibido->watermark_obc_task;
            float temp_0 = ptr_recibido->temp_sensores[0];

            //parpadeo de led para cnfirmar
            HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
        }

        // 4. DORMIR ESTRICTAMENTE 70 SEGUNDOS
        vTaskDelayUntil(&LastWakeTime, intrv_70);
    }
}
