#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int id;
    float energia;
    float tempo;
    float custo;
    float bateria_inicial;
    float bateria_final;
    int horario_sessao;
} Sessao;

void exibir_iguais();
void titulo(char *palavra);
void menu_inicial();
float conversao_para_kwh(float bateria_inicial, float capacidade_bateria);
void sair_programa();

int main() {
    int opcao;

    Sessao sessoes[100];
    int quantidadeSessoes = 0;

    float capacidade_bateria;
    float energia_necessaria;

    menu_inicial();
    
    while (1)
    {
        printf("Digite uma opção: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
            case 1:
                printf("\n--- NOVA SESSÃO ---\n");

                sessoes[quantidadeSessoes].id = quantidadeSessoes + 1;

                printf("Sessão: %d\n",
                       sessoes[quantidadeSessoes].id);

                printf("Digite a capacidade da bateria (kWh): ");
                scanf("%f", &capacidade_bateria);

                printf("Digite a bateria inicial (%%): ");
                scanf("%f",
                      &sessoes[quantidadeSessoes].bateria_inicial);

                if (sessoes[quantidadeSessoes].bateria_inicial < 0 ||
                    sessoes[quantidadeSessoes].bateria_inicial > 100)
                {
                    printf("\nBateria inválida!\n\n");
                    break;
                }

                if (capacidade_bateria <= 0)
                {
                    printf("\nCapacidade da bateria inválida!\n\n");
                    break;
                }

                energia_necessaria =
                    capacidade_bateria -
                    conversao_para_kwh(
                        sessoes[quantidadeSessoes].bateria_inicial,
                        capacidade_bateria
                    );

                sessoes[quantidadeSessoes].energia =
                    energia_necessaria;

                sessoes[quantidadeSessoes].tempo =
                    (energia_necessaria / 75) * 60;

                sessoes[quantidadeSessoes].custo =
                    energia_necessaria * 0.8;

                sessoes[quantidadeSessoes].bateria_final = 100;

                quantidadeSessoes++;

                printf("\nSessão cadastrada com sucesso!\n\n");

                menu_inicial();

                break;
            case 2:

                if (quantidadeSessoes == 0)
                {
                    printf("\nNenhuma sessão cadastrada.\n\n");
                    break;
                }

                printf("\n");
                titulo("LISTAR SESSÕES DE RECARGA");
                printf("\n");

                for (int i = 0; i < quantidadeSessoes; i++)
                {
                    printf("\n");
                    printf("Sessão: %d\n", sessoes[i].id);
                    printf("Carga inicial: %.2f%%\n",
                           sessoes[i].bateria_inicial);
                    printf("Carga final: %.2f%%\n",
                           sessoes[i].bateria_final);
                    printf("Energia adicionada: %.2f kWh\n",
                           sessoes[i].energia);
                    printf("Custo: R$ %.2f\n",
                           sessoes[i].custo);
                    printf("Tempo estimado: %.0f minutos\n",
                           sessoes[i].tempo);
                    printf("----------------------------------------\n");
                }

                printf("\n");

                menu_inicial();

                break;

            case 3:

                if (quantidadeSessoes == 0)
                {
                    printf("\nNenhuma sessão cadastrada.\n\n");
                    break;
                }

                int idBusca;
                int encontrada = 0;

                printf("\n--- BUSCAR SESSÃO ---\n");
                printf("Digite o ID da sessão: ");
                scanf("%d", &idBusca);

                for (int i = 0; i < quantidadeSessoes; i++)
                {
                    if (sessoes[i].id == idBusca)
                    {
                        printf("\n");
                        printf("=============================================\n");
                        printf("             RELATÓRIO DA SESSÃO\n");
                        printf("=============================================\n");
                        printf("Sessão: %d\n",
                               sessoes[i].id);
                        printf("Carga inicial: %.2f%%\n",
                               sessoes[i].bateria_inicial);
                        printf("Carga final: %.2f%%\n",
                               sessoes[i].bateria_final);
                        printf("Energia adicionada: %.2f kWh\n",
                               sessoes[i].energia);
                        printf("Preço da recarga: R$ %.2f\n",
                               sessoes[i].custo);
                        printf("Tempo estimado: %.0f minutos\n",
                               sessoes[i].tempo);
                        printf("=============================================\n");

                        encontrada = 1;
                        break;
                    }
                }

                if (encontrada == 0)
                {
                    printf("\nSessão não encontrada.\n\n");
                }

                menu_inicial();

                break;

            case 4:
                break;

            case 5:
                break;

            case 6:
                sair_programa();
                break;

            default:
                printf("\nOpção Inválida!\n");
                printf("Digite a opção novamente!\n\n");
                break;
        }
    }
    
    return 0;
}

void exibir_iguais() {
    for (int i = 0; i < 40; i++) {
        printf("=");
    }
}

void titulo(char *palavra) {
    exibir_iguais();
    printf("\n");
    printf("          ");
    printf("%s\n", palavra);
    exibir_iguais();
}

void menu_inicial() {
    printf("\n");
    titulo("ESTAÇÃO DE RECARGA");
    printf("\n\n");
    printf("1 - Nova sessão de recarga\n");
    printf("2 - Listar sessões\n");
    printf("3 - Buscar sessão\n");
    printf("4 - Ordenar Sessões\n");
    printf("5 - Estatísticas\n");
    printf("6 - Encerrar\n");
    printf("\n");
}

float conversao_para_kwh(float bateria_inicial, float capacidade_bateria) {
    return (bateria_inicial / 100) * capacidade_bateria;
}

void sair_programa() {
    printf("\n\nPrograma Encerrado!!!\n");
    exit(EXIT_SUCCESS);
}