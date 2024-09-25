/* 
 * Simulação de Controle de Quadricóptero usando FreeRTOS
 * Estudantes: Eduardo Silva Contin, Andressa Aparecida, Anabelly
 */

#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Variáveis de velocidade dos motores
volatile int velocidade_motor[4] = {0, 0, 0, 0};

// Variáveis globais para direções de manobra
volatile char sentido[10] = "horario";
volatile char direcao[10] = "frente";
volatile char orientacao[10] = "direita";

// Semáforo binário
SemaphoreHandle_t xSemaphore = NULL;

// Protótipos de funções
void tarefaArfagem(void *pvParametros);
void tarefaRolagem(void *pvParametros);
void tarefaGuinada(void *pvParametros);
void tarefaRadioFrequencia(void *pvParametros);
void vImprimirString(const char *pcString);

// Função principal
int main(void)
{
    // Criar semáforo binário
    xSemaphore = xSemaphoreCreateBinary();
    if (xSemaphore == NULL) {
        printf("Erro ao criar semáforo\n");
        return 1;
    }
    xSemaphoreGive(xSemaphore);

    // Criar tarefas
    xTaskCreate(tarefaArfagem, "Arfagem", 1000, NULL, 2, NULL);
    xTaskCreate(tarefaRolagem, "Rolagem", 1000, NULL, 2, NULL);
    xTaskCreate(tarefaGuinada, "Guinada", 1000, NULL, 2, NULL);
    xTaskCreate(tarefaRadioFrequencia, "RadioFreq", 1000, NULL, 1, NULL);

    // Iniciar o escalonador
    vTaskStartScheduler();

    // Nunca deve chegar aqui
    for (;;);
}

// Tarefa de controle de arfagem
void tarefaArfagem(void *pvParametros)
{
    for (;;)
    {
        if (xSemaphoreTake(xSemaphore, portMAX_DELAY) == pdTRUE)
        {
            vImprimirString("[+] Manobra de arfagem: ");
            vImprimirString(direcao);
            vImprimirString("\n");

            if (strcmp(direcao, "frente") == 0)
            {
                velocidade_motor[2] += 25;
                velocidade_motor[3] += 25;
                velocidade_motor[0] -= 25;
                velocidade_motor[1] -= 25;
            }
            else if (strcmp(direcao, "tras") == 0)
            {
                velocidade_motor[2] -= 25;
                velocidade_motor[3] -= 25;
                velocidade_motor[0] += 25;
                velocidade_motor[1] += 25;
            }

            printf("[+] Velocidades dos motores: %d, %d, %d, %d\n", velocidade_motor[0], velocidade_motor[1], velocidade_motor[2], velocidade_motor[3]);

            xSemaphoreGive(xSemaphore);
        }

        vTaskDelay(pdMS_TO_TICKS(40));
    }
}

// Tarefa de controle de rolagem
void tarefaRolagem(void *pvParametros)
{
    for (;;)
    {
        if (xSemaphoreTake(xSemaphore, portMAX_DELAY) == pdTRUE)
        {
            vImprimirString("[+] Manobra de rolagem: ");
            vImprimirString(orientacao);
            vImprimirString("\n");

            if (strcmp(orientacao, "direita") == 0)
            {
                velocidade_motor[0] += 50;
                velocidade_motor[3] += 50;
                velocidade_motor[1] -= 50;
                velocidade_motor[2] -= 50;
            }
            else if (strcmp(orientacao, "esquerda") == 0)
            {
                velocidade_motor[0] -= 50;
                velocidade_motor[3] -= 50;
                velocidade_motor[1] += 50;
                velocidade_motor[2] += 50;
            }

            printf("[+] Velocidades dos motores: %d, %d, %d, %d\n", velocidade_motor[0], velocidade_motor[1], velocidade_motor[2], velocidade_motor[3]);

            xSemaphoreGive(xSemaphore);
        }

        vTaskDelay(pdMS_TO_TICKS(20));
    }
}

// Tarefa de controle de guinada
void tarefaGuinada(void *pvParametros)
{
    for (;;)
    {
        if (xSemaphoreTake(xSemaphore, portMAX_DELAY) == pdTRUE)
        {
            vImprimirString("[+] Manobra de guinada: ");
            vImprimirString(sentido);
            vImprimirString("\n");

            if (strcmp(sentido, "horario") == 0)
            {
                velocidade_motor[0] += 100;
                velocidade_motor[2] += 100;
                velocidade_motor[1] -= 100;
                velocidade_motor[3] -= 100;
            }
            else if (strcmp(sentido, "antihorario") == 0)
            {
                velocidade_motor[0] -= 100;
                velocidade_motor[2] -= 100;
                velocidade_motor[1] += 100;
                velocidade_motor[3] += 100;
            }

            printf("[+] Velocidades dos motores: %d, %d, %d, %d\n", velocidade_motor[0], velocidade_motor[1], velocidade_motor[2], velocidade_motor[3]);

            xSemaphoreGive(xSemaphore);
        }

        vTaskDelay(pdMS_TO_TICKS(10));
    }
}

// Nova tarefa de rádio frequência
void tarefaRadioFrequencia(void *pvParametros)
{
    for (;;)
    {
        if (xSemaphoreTake(xSemaphore, portMAX_DELAY) == pdTRUE)
        {
            int num_sentido = rand() % 100;
            int num_direcao = rand() % 100;
            int num_orientacao = rand() % 100;

            sprintf((char*)sentido, (num_sentido % 2 == 0) ? "horario" : "antihorario");
            sprintf((char*)direcao, (num_direcao % 2 == 0) ? "frente" : "tras");
            sprintf((char*)orientacao, (num_orientacao % 2 == 0) ? "direita" : "esquerda");

            printf("[+] Novas manobras: Sentido=%s, Direção=%s, Orientação=%s\n", sentido, direcao, orientacao);

            xSemaphoreGive(xSemaphore);
        }

        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

void vImprimirString(const char *pcString)
{
    printf("%s", pcString);
}
