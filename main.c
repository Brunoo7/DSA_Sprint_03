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
    float tarifa_por_kwh;
    int horario_sessao;
} Sessao;

void exibir_iguais();
void titulo(char *palavra);
void menu_inicial();
float conversao_para_kwh(float bateria_inicial, float capacidade_bateria);
int porcentagem_invalida(Sessao *sessoes, int quantidadeSessoes);
int capacidade_bateria_invalida(float capacidade_bateria);
int horario_invalido(int horario_sessao);
float calcular_tempo_recarga(float energia_necessaria);
float calcular_valor_total(float energia_necessaria, Sessao *sessao, int quantidadeSessoes);
int nao_ha_sessoes_cadastradas(int quantidadeSessoes);
void relatorio_sessao(Sessao *sessao, int i);
void listar_sessoes(Sessao *sessoes, int quantidadeSessoes);
void buscar_sessao_por_id(int idBusca, Sessao *sessoes, int quantidadeSessoes);
void ordenar_sessoes(Sessao *sessoes, int quantidadeSessoes);
void exibir_estatisticas(Sessao *sessao, int quantidadeSessoes);
float calcular_media_energia_necessaria(Sessao *sessao, int quantidadeSessoes);
float calcular_media_valor_total(Sessao *sessao, int quantidadeSessoes);
float calcular_media_bateria_inicial(Sessao *sessao, int quantidadeSessoes);
int calcular_media_tempo_recarga(Sessao *sessao, int quantidadeSessoes);
int todas_faixas_iguais(
    int qtd_primeira_faixa_horario,
    int qtd_segunda_faixa_horario,
    int qtd_terceira_faixa_horario
);
void calcular_media_faixa_horario_sessoa(Sessao *sessao, int quantidadeSessoes);
void sair_programa();

int main()
{
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

                if (capacidade_bateria_invalida(capacidade_bateria))
                {
                    printf("\nCapacidade da bateria inválida!\n\n");
                    break;
                }

                printf("Digite a bateria inicial (%%): ");
                scanf("%f",
                      &sessoes[quantidadeSessoes].bateria_inicial);

                if (porcentagem_invalida(sessoes, quantidadeSessoes))
                {
                    printf("\nBateria inválida!\n\n");
                    break;
                }

                printf("Digite o horário da sessão (0h-23h): ");
                scanf("%d", &sessoes[quantidadeSessoes].horario_sessao);

                if (horario_invalido(sessoes[quantidadeSessoes].horario_sessao))
                {
                    printf("\nHorário inválido!\n\n");
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
                    calcular_tempo_recarga(energia_necessaria);

                sessoes[quantidadeSessoes].custo =
                    calcular_valor_total(
                        energia_necessaria,
                        sessoes,
                        quantidadeSessoes
                    );

                sessoes[quantidadeSessoes].bateria_final = 100;

                quantidadeSessoes++;

                printf("\nSessão cadastrada com sucesso!\n\n");

                menu_inicial();

                break;

            case 2:

                if (nao_ha_sessoes_cadastradas(quantidadeSessoes))
                {
                    printf("\nNenhuma sessão cadastrada.\n\n");
                    break;
                }

                printf("\n");
                titulo("LISTAR SESSÕES DE RECARGA");
                printf("\n");

                listar_sessoes(sessoes, quantidadeSessoes);

                printf("\n");

                menu_inicial();

                break;

            case 3:

                if (nao_ha_sessoes_cadastradas(quantidadeSessoes))
                {
                    printf("\nNenhuma sessão cadastrada.\n\n");
                    break;
                }

                int idBusca;

                printf("\n--- BUSCAR SESSÃO ---\n");
                printf("Digite o ID da sessão: ");
                scanf("%d", &idBusca);

                buscar_sessao_por_id(
                    idBusca,
                    sessoes,
                    quantidadeSessoes
                );

                menu_inicial();

                break;

            case 4:

                if (nao_ha_sessoes_cadastradas(quantidadeSessoes))
                {
                    printf("\nNenhuma sessão cadastrada.\n\n");
                    break;
                }

                ordenar_sessoes(sessoes, quantidadeSessoes);

                menu_inicial();

                break;

            case 5:

                if (nao_ha_sessoes_cadastradas(quantidadeSessoes))
                {
                    printf("\nNenhuma sessão cadastrada para calcular as estatísticas.\n\n");
                    break;
                }

                exibir_estatisticas(sessoes, quantidadeSessoes);

                menu_inicial();

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

void exibir_iguais()
{
    for (int i = 0; i < 40; i++)
    {
        printf("=");
    }
}

void titulo(char *palavra)
{
    exibir_iguais();
    printf("\n");
    printf("          ");
    printf("%s\n", palavra);
    exibir_iguais();
}

void menu_inicial()
{
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

float conversao_para_kwh(float bateria_inicial, float capacidade_bateria)
{
    return (bateria_inicial / 100) * capacidade_bateria;
}

int porcentagem_invalida(Sessao *sessoes, int quantidadeSessoes)
{
    return sessoes[quantidadeSessoes].bateria_inicial < 0 ||
           sessoes[quantidadeSessoes].bateria_inicial > 100;
}

int capacidade_bateria_invalida(float capacidade_bateria)
{
    return capacidade_bateria <= 0;
}

int horario_invalido(int horario_sessao)
{
    return horario_sessao < 0 || horario_sessao > 23;
}

float calcular_tempo_recarga(float energia_necessaria)
{
    int potencia_carregador = 75;
    int segundos_para_minutos = 60;

    return (energia_necessaria / potencia_carregador) *
           segundos_para_minutos;
}

float calcular_valor_total(
    float energia_necessaria,
    Sessao *sessao,
    int quantidadeSessoes
)
{
    float tarifa_por_kwh;
    int horario_sessao =
        sessao[quantidadeSessoes].horario_sessao;

    if (horario_sessao <= 6)
    {
        tarifa_por_kwh = 0.5;
    }
    else if (horario_sessao < 18)
    {
        tarifa_por_kwh = 0.8;
    }
    else
    {
        tarifa_por_kwh = 1.2;
    }

    sessao[quantidadeSessoes].tarifa_por_kwh =
        tarifa_por_kwh;

    return energia_necessaria * tarifa_por_kwh;
}

int nao_ha_sessoes_cadastradas(int quantidadeSessoes)
{
    return quantidadeSessoes == 0;
}

void relatorio_sessao(Sessao *sessao, int i)
{
    printf("Sessão: %d\n", sessao[i].id);

    printf("Carga inicial: %.2f%%\n",
           sessao[i].bateria_inicial);

    printf("Carga final: %.2f%%\n",
           sessao[i].bateria_final);

    printf("Energia adicionada: %.2f kW\n",
           sessao[i].energia);

    printf("Horário da sessão: %dh\n",
           sessao[i].horario_sessao);

    printf("Tarifa por kwh: R$%.2f\n",
           sessao[i].tarifa_por_kwh);

    printf("Custo: R$ %.2f\n",
           sessao[i].custo);

    printf("Tempo estimado: %.0f minutos\n",
           sessao[i].tempo);
}

void listar_sessoes(Sessao *sessoes, int quantidadeSessoes)
{
    for (int i = 0; i < quantidadeSessoes; i++)
    {
        printf("\n");

        relatorio_sessao(sessoes, i);

        printf("----------------------------------------\n");
    }
}

void buscar_sessao_por_id(
    int idBusca,
    Sessao *sessoes,
    int quantidadeSessoes
)
{
    int encontrada = 0; 
    // O(1) - declaração e inicialização da variável

    // O(n) - no pior caso, o laço percorre todas as sessões
    for (int i = 0; i < quantidadeSessoes; i++)
    {
        // O(1) - acesso ao elemento do vetor e comparação do ID
        if (sessoes[i].id == idBusca)
        {
            printf("\n"); 
            // O(1) - impressão na tela

            printf("=============================================\n");
            // O(1) - impressão na tela

            printf("             RELATÓRIO DA SESSÃO\n");
            // O(1) - impressão na tela

            printf("=============================================\n");
            // O(1) - impressão na tela

            relatorio_sessao(sessoes, i);
            // O(1) - exibe os dados da sessão encontrada

            printf("=============================================\n");
            // O(1) - impressão na tela

            encontrada = 1;
            // O(1) - altera o valor da variável

            break;
            // O(1) - encerra o laço imediatamente
        }
    }

    // O(1) - verifica se nenhuma sessão foi encontrada
    if (encontrada == 0)
    {
        printf("\nSessão não encontrada.\n\n");
        // O(1) - impressão na tela
    }
    
    // Complexidade final:
    // O(n), pois no pior caso todas as n sessões são verificadas.
}

void ordenar_sessoes(
    Sessao *sessoes,
    int quantidadeSessoes
)
{
    int criterio;
    // O(1) - declaração da variável

    int ordem;
    // O(1) - declaração da variável

    printf("\n--- ORDENAR SESSÕES ---\n");
    // O(1) - impressão na tela

    printf("1 - ID\n");
    // O(1) - impressão na tela

    printf("2 - Energia\n");
    // O(1) - impressão na tela

    printf("3 - Custo\n");
    // O(1) - impressão na tela

    printf("4 - Tempo\n");
    // O(1) - impressão na tela

    printf("5 - Bateria inicial\n");
    // O(1) - impressão na tela

    printf("Digite o critério: ");
    // O(1) - impressão na tela

    scanf("%d", &criterio);
    // O(1) - leitura da opção escolhida

    // O(1) - verifica se o critério está dentro das opções
    if (criterio < 1 || criterio > 5)
    {
        printf("\nCritério inválido!\n\n");
        // O(1) - impressão na tela

        return;
        // O(1) - encerra a função
    }

    printf("\n1 - Crescente\n");
    // O(1) - impressão na tela

    printf("2 - Decrescente\n");
    // O(1) - impressão na tela

    printf("Digite a ordem: ");
    // O(1) - impressão na tela

    scanf("%d", &ordem);
    // O(1) - leitura da opção escolhida

    // O(1) - verifica se a ordem é válida
    if (ordem != 1 && ordem != 2)
    {
        printf("\nOrdem inválida!\n\n");
        // O(1) - impressão na tela

        return;
        // O(1) - encerra a função
    }

    // O(n) - o primeiro laço percorre aproximadamente n posições
    for (int i = 0; i < quantidadeSessoes - 1; i++)
    {
        // O(n) - para cada posição de i,
        // o segundo laço percorre as posições restantes
        for (int j = 0; j < quantidadeSessoes - 1 - i; j++)
        {
            int trocar = 0;
            // O(1) - inicialização da variável

            // O(1) - verifica se o critério escolhido é ID
            if (criterio == 1)
            {
                // O(1) - compara dois IDs
                if (ordem == 1 &&
                    sessoes[j].id > sessoes[j + 1].id)
                {
                    trocar = 1;
                    // O(1) - indica que haverá troca
                }

                // O(1) - compara dois IDs
                else if (ordem == 2 &&
                         sessoes[j].id < sessoes[j + 1].id)
                {
                    trocar = 1;
                    // O(1) - indica que haverá troca
                }
            }

            // O(1) - verifica se o critério escolhido é energia
            else if (criterio == 2)
            {
                // O(1) - compara duas energias
                if (ordem == 1 &&
                    sessoes[j].energia > sessoes[j + 1].energia)
                {
                    trocar = 1;
                    // O(1) - indica que haverá troca
                }

                // O(1) - compara duas energias
                else if (ordem == 2 &&
                         sessoes[j].energia < sessoes[j + 1].energia)
                {
                    trocar = 1;
                    // O(1) - indica que haverá troca
                }
            }

            // O(1) - verifica se o critério escolhido é custo
            else if (criterio == 3)
            {
                // O(1) - compara dois custos
                if (ordem == 1 &&
                    sessoes[j].custo > sessoes[j + 1].custo)
                {
                    trocar = 1;
                    // O(1) - indica que haverá troca
                }

                // O(1) - compara dois custos
                else if (ordem == 2 &&
                         sessoes[j].custo < sessoes[j + 1].custo)
                {
                    trocar = 1;
                    // O(1) - indica que haverá troca
                }
            }

            // O(1) - verifica se o critério escolhido é tempo
            else if (criterio == 4)
            {
                // O(1) - compara dois tempos
                if (ordem == 1 &&
                    sessoes[j].tempo > sessoes[j + 1].tempo)
                {
                    trocar = 1;
                    // O(1) - indica que haverá troca
                }

                // O(1) - compara dois tempos
                else if (ordem == 2 &&
                         sessoes[j].tempo < sessoes[j + 1].tempo)
                {
                    trocar = 1;
                    // O(1) - indica que haverá troca
                }
            }

            // O(1) - verifica se o critério escolhido é bateria inicial
            else if (criterio == 5)
            {
                // O(1) - compara duas baterias iniciais
                if (ordem == 1 &&
                    sessoes[j].bateria_inicial >
                    sessoes[j + 1].bateria_inicial)
                {
                    trocar = 1;
                    // O(1) - indica que haverá troca
                }

                // O(1) - compara duas baterias iniciais
                else if (ordem == 2 &&
                         sessoes[j].bateria_inicial <
                         sessoes[j + 1].bateria_inicial)
                {
                    trocar = 1;
                    // O(1) - indica que haverá troca
                }
            }

            // O(1) - verifica se a troca foi necessária
            if (trocar)
            {
                Sessao temporaria = sessoes[j];
                // O(1) - copia uma struct para uma variável temporária

                sessoes[j] = sessoes[j + 1];
                // O(1) - coloca a próxima sessão na posição atual

                sessoes[j + 1] = temporaria;
                // O(1) - coloca a sessão temporária na próxima posição
            }
        }
    }

    printf("\nSessões ordenadas com sucesso!\n\n");
    // O(1) - impressão na tela

    listar_sessoes(sessoes, quantidadeSessoes);
    // O(n) - percorre todas as sessões para exibi-las

    // Complexidade final:
    // O(n²), pois existem dois laços de repetição aninhados.
    // O(n) × O(n) = O(n²).
    //
    // A função listar_sessoes() possui O(n), mas:
    // O(n²) + O(n) = O(n²).
}

void exibir_estatisticas(
    Sessao *sessao,
    int quantidadeSessoes
)
{
    float media_energia_necessaria =
        calcular_media_energia_necessaria(
            sessao,
            quantidadeSessoes
        );

    float media_valor_total =
        calcular_media_valor_total(
            sessao,
            quantidadeSessoes
        );

    float media_bateria_inicial =
        calcular_media_bateria_inicial(
            sessao,
            quantidadeSessoes
        );

    int media_tempo_recarga =
        calcular_media_tempo_recarga(
            sessao,
            quantidadeSessoes
        );

    printf("\n");
    titulo("ESTATÍSTICAS");
    printf("\n\n");

    printf(
        "Média de energia necessária: %.2f Kw\n",
        media_energia_necessaria
    );

    printf(
        "Média de valor total: R$%.2f\n",
        media_valor_total
    );

    printf(
        "Média de bateria inicial: %.2f%%\n",
        media_bateria_inicial
    );

    printf(
        "Média de tempo de recarga: %d minutos\n",
        media_tempo_recarga
    );

    printf("\n");
    printf("FAIXA DE HORÁRIO DAS RECARGAS\n");
    printf("--------------------------------------\n");

    calcular_media_faixa_horario_sessoa(
        sessao,
        quantidadeSessoes
    );

    printf("\n");
}

float calcular_media_energia_necessaria(
    Sessao *sessao,
    int quantidadeSessoes
)
{
    float soma_energia = 0;

    for (int i = 0; i < quantidadeSessoes; i++)
    {
        soma_energia += sessao[i].energia;
    }

    return soma_energia / quantidadeSessoes;
}

float calcular_media_valor_total(
    Sessao *sessao,
    int quantidadeSessoes
)
{
    float soma_custo = 0;

    for (int i = 0; i < quantidadeSessoes; i++)
    {
        soma_custo += sessao[i].custo;
    }

    return soma_custo / quantidadeSessoes;
}

int calcular_media_tempo_recarga(
    Sessao *sessao,
    int quantidadeSessoes
)
{
    int soma_tempo = 0;

    for (int i = 0; i < quantidadeSessoes; i++)
    {
        soma_tempo += sessao[i].tempo;
    }

    return soma_tempo / quantidadeSessoes;
}

float calcular_media_bateria_inicial(
    Sessao *sessao,
    int quantidadeSessoes
)
{
    float soma_bateria_inicial = 0;

    for (int i = 0; i < quantidadeSessoes; i++)
    {
        soma_bateria_inicial +=
            sessao[i].bateria_inicial;
    }

    return soma_bateria_inicial / quantidadeSessoes;
}

int todas_faixas_iguais(
    int qtd_primeira_faixa_horario,
    int qtd_segunda_faixa_horario,
    int qtd_terceira_faixa_horario
)
{
    return qtd_primeira_faixa_horario ==
               qtd_segunda_faixa_horario &&
           qtd_primeira_faixa_horario ==
               qtd_terceira_faixa_horario &&
           qtd_segunda_faixa_horario ==
               qtd_terceira_faixa_horario;
}

void calcular_media_faixa_horario_sessoa(
    Sessao *sessao,
    int quantidadeSessoes
)
{
    int qtd_primeira_faixa_horario = 0;
    int qtd_segunda_faixa_horario = 0;
    int qtd_terceira_faixa_horario = 0;

    for (int i = 0; i < quantidadeSessoes; i++)
    {
        if (sessao[i].horario_sessao <= 6)
        {
            qtd_primeira_faixa_horario++;
        }
        else if (sessao[i].horario_sessao < 18)
        {
            qtd_segunda_faixa_horario++;
        }
        else
        {
            qtd_terceira_faixa_horario++;
        }
    }

    if (qtd_primeira_faixa_horario >
            qtd_segunda_faixa_horario &&
        qtd_primeira_faixa_horario >
            qtd_terceira_faixa_horario)
    {
        printf(
            "Faixa de hórario com mais recargas: 0h-6h | Quantidade de recargas: %d",
            qtd_primeira_faixa_horario
        );
    }

    else if (qtd_segunda_faixa_horario >
                 qtd_primeira_faixa_horario &&
             qtd_segunda_faixa_horario >
                 qtd_terceira_faixa_horario)
    {
        printf(
            "Faixa de hórario com mais recargas: 7h-17h | Quantidade de recargas: %d",
            qtd_segunda_faixa_horario
        );
    }

    else if (qtd_terceira_faixa_horario >
                 qtd_primeira_faixa_horario &&
             qtd_terceira_faixa_horario >
                 qtd_segunda_faixa_horario)
    {
        printf(
            "Faixa de hórario com mais recargas: 18h-23h | Quantidade de recargas: %d",
            qtd_terceira_faixa_horario
        );
    }

    else if (
        todas_faixas_iguais(
            qtd_primeira_faixa_horario,
            qtd_segunda_faixa_horario,
            qtd_terceira_faixa_horario
        )
    )
    {
        printf(
            "Todas as faixas de horário tiveram a mesma quantidade de recargas:\n"
            "- Quantidade de recargas (0h-6h): %d\n"
            "- Quantidade de recargas (7h-17h): %d\n"
            "- Quantidade de recargas (18h-23h): %d\n",
            qtd_primeira_faixa_horario,
            qtd_segunda_faixa_horario,
            qtd_terceira_faixa_horario
        );
    }

    else if (
        qtd_primeira_faixa_horario ==
        qtd_segunda_faixa_horario
    )
    {
        printf(
            "Duas faixas de horário tiveram a mesma quantidade de recargas:\n"
            "- Quantidade de recargas (0h-6h): %d\n"
            "- Quantidade de recargas (7h-17h): %d\n",
            qtd_primeira_faixa_horario,
            qtd_segunda_faixa_horario
        );
    }

    else if (
        qtd_primeira_faixa_horario ==
        qtd_terceira_faixa_horario
    )
    {
        printf(
            "Duas faixas de horário tiveram a mesma quantidade de recargas:\n"
            "- Quantidade de recargas (0h-6h): %d\n"
            "- Quantidade de recargas (18h-23h): %d\n",
            qtd_primeira_faixa_horario,
            qtd_terceira_faixa_horario
        );
    }

    else
    {
        printf(
            "Duas faixas de horário tiveram a mesma quantidade de recargas:\n"
            "- Quantidade de recargas (7h-17h): %d\n"
            "- Quantidade de recargas (18h-23h): %d\n",
            qtd_segunda_faixa_horario,
            qtd_terceira_faixa_horario
        );
    }
}

void sair_programa()
{
    printf("\n\nPrograma Encerrado!!!\n");
    exit(EXIT_SUCCESS);
}