/* 
 * Simulação de Controle de Quadricóptero usando FreeRTOS
 * Curso: <nome do curso>
 * Estudantes: <nome do estudante>
 */

#include "FreeRTOS.h"
#include "task.h"
#include <stdio.h>

// Variáveis de velocidade dos motores
volatile int velocidade_motor[4] = {0, 0, 0, 0};

// Protótipos de funções
void tarefaArfagem(void *pvParametros);
void tarefaRolagem(void *pvParametros);
void tarefaGuinada(void *pvParametros);
void vImprimirString(const char *pcString);

// Função principal
int main(void)
{
    // Criar tarefas
    xTaskCreate(tarefaArfagem, "Arfagem", configMINIMAL_STACK_SIZE, (void*)"frente", 1, NULL);
    xTaskCreate(tarefaRolagem, "Rolagem", configMINIMAL_STACK_SIZE, (void*)"direita", 1, NULL);
    xTaskCreate(tarefaGuinada, "Guinada", configMINIMAL_STACK_SIZE, (void*)"horario", 1, NULL);

    // Iniciar o escalonador
    vTaskStartScheduler();

    // Nunca deve chegar aqui
    for (;;);
}

// Tarefa de controle de arfagem
void tarefaArfagem(void *pvParametros)
{
    char *direcao = (char*)pvParametros;
    for (;;)
    {
        vImprimirString("Manobra de arfagem: ");
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

        printf("Velocidades dos motores: %d, %d, %d, %d\n", velocidade_motor[0], velocidade_motor[1], velocidade_motor[2], velocidade_motor[3]);

        vTaskDelay(pdMS_TO_TICKS(40));
    }
    vTaskDelete(NULL);
}

// Tarefa de controle de rolagem
void tarefaRolagem(void *pvParametros)
{
    char *direcao = (char*)pvParametros;
    for (;;)
    {
        vImprimirString("Manobra de rolagem: ");
        vImprimirString(direcao);
        vImprimirString("\n");

        if (strcmp(direcao, "direita") == 0)
        {
            velocidade_motor[0] += 50;
            velocidade_motor[3] += 50;
            velocidade_motor[1] -= 50;
            velocidade_motor[2] -= 50;
        }
        else if (strcmp(direcao, "esquerda") == 0)
        {
            velocidade_motor[0] -= 50;
            velocidade_motor[3] -= 50;
            velocidade_motor[1] += 50;
            velocidade_motor[2] += 50;
        }

        printf("Velocidades dos motores: %d, %d, %d, %d\n", velocidade_motor[0], velocidade_motor[1], velocidade_motor[2], velocidade_motor[3]);

        vTaskDelay(pdMS_TO_TICKS(20));
    }
    vTaskDelete(NULL);
}

// Tarefa de controle de guinada
void tarefaGuinada(void *pvParametros)
{
    char *direcao = (char*)pvParametros;
    for (;;)
    {
        vImprimirString("Manobra de guinada: ");
        vImprimirString(direcao);
        vImprimirString("\n");

        if (strcmp(direcao, "horario") == 0)
        {
            velocidade_motor[0] += 100;
            velocidade_motor[2] += 100;
            velocidade_motor[1] -= 100;
            velocidade_motor[3] -= 100;
        }
        else if (strcmp(direcao, "antihorario") == 0)
        {
            velocidade_motor[0] -= 100;
            velocidade_motor[2] -= 100;
            velocidade_motor[1] += 100;
            velocidade_motor[3] += 100;
        }

        printf("Velocidades dos motores: %d, %d, %d, %d\n", velocidade_motor[0], velocidade_motor[1], velocidade_motor[2], velocidade_motor[3]);

        vTaskDelay(pdMS_TO_TICKS(10));
    }
    vTaskDelete(NULL);
}

// Função para imprimir strings (a implementação pode variar dependendo do sistema)
void vImprimirString(const char *pcString)
{
    // A implementação depende do método de saída do seu sistema
    printf("%s", pcString);
}
