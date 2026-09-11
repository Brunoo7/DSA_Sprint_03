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
float calcular_energia_total(Sessao *sessao, int quantidadeSessoes);
float calcular_faturamento_total(Sessao *sessao, int quantidadeSessoes);
float calcular_maior_consumo(Sessao *sessao, int quantidadeSessoes);
float calcular_menor_consumo(Sessao *sessao, int quantidadeSessoes);
float calcular_media_energia_necessaria(Sessao *sessao, int quantidadeSessoes);
float calcular_media_valor_total(Sessao *sessao, int quantidadeSessoes);
float calcular_media_bateria_inicial(Sessao *sessao, int quantidadeSessoes);
float calcular_media_tempo_recarga(Sessao *sessao, int quantidadeSessoes);
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
                if (quantidadeSessoes >= 100)
                {
                    printf("\nLimite máximo de 100 sessões atingido.\n\n");
                    break;
                }

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

    printf("Energia adicionada: %.2f kWh\n",
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
    // O(1): declaração e inicialização da variável.

    // O(n): o laço pode percorrer todas as sessões no pior caso.
    for (int i = 0; i < quantidadeSessoes; i++)
    {
        // O(1): acesso ao elemento atual do vetor.
        // O(1): comparação entre o ID atual e o ID procurado.
        if (sessoes[i].id == idBusca)
        {
            // O(1): quebra de linha.
            printf("\n");

            // O(1): impressão do separador.
            printf("=============================================\n");

            // O(1): impressão do título.
            printf("             RELATÓRIO DA SESSÃO\n");

            // O(1): impressão do separador.
            printf("=============================================\n");

            // O(1): chamada da função para exibir os dados da sessão.
            relatorio_sessao(sessoes, i);

            // O(1): impressão do separador.
            printf("=============================================\n");

            // O(1): altera a variável para indicar que encontrou.
            encontrada = 1;

            // O(1): encerra o laço após encontrar a sessão.
            break;
        }
    }

    // O(1): comparação para verificar se a sessão não foi encontrada.
    if (encontrada == 0)
    {
        // O(1): impressão da mensagem.
        printf("\nSessão não encontrada.\n\n");
    }

    /*
    Complexidade:
    Inicialização: O(1)
    Laço de busca: O(n)
    Operações dentro do laço: O(1)

    Portanto:
    O(1) + O(n) * O(1) = O(n)

    Complexidade final da busca: O(n)
    */
}

void ordenar_sessoes(
    Sessao *sessoes,
    int quantidadeSessoes
)
{
    // O(1): declaração da variável.
    int criterio;

    // O(1): declaração da variável.
    int ordem;

    // O(1): impressão na tela.
    printf("\n--- ORDENAR SESSÕES ---\n");

    // O(1): impressão na tela.
    printf("1 - ID\n");

    // O(1): impressão na tela.
    printf("2 - Energia\n");

    // O(1): impressão na tela.
    printf("3 - Custo\n");

    // O(1): impressão na tela.
    printf("4 - Tempo\n");

    // O(1): impressão na tela.
    printf("5 - Bateria inicial\n");

    // O(1): impressão na tela.
    printf("Digite o critério: ");

    // O(1): leitura do critério escolhido.
    scanf("%d", &criterio);

    // O(1): verifica se o critério é válido.
    if (criterio < 1 || criterio > 5)
    {
        // O(1): impressão da mensagem.
        printf("\nCritério inválido!\n\n");

        // O(1): encerra a função.
        return;
    }

    // O(1): impressão na tela.
    printf("\n1 - Crescente\n");

    // O(1): impressão na tela.
    printf("2 - Decrescente\n");

    // O(1): impressão na tela.
    printf("Digite a ordem: ");

    // O(1): leitura da ordem escolhida.
    scanf("%d", &ordem);

    // O(1): verifica se a ordem é válida.
    if (ordem != 1 && ordem != 2)
    {
        // O(1): impressão da mensagem.
        printf("\nOrdem inválida!\n\n");

        // O(1): encerra a função.
        return;
    }

    // O(n): o primeiro laço executa aproximadamente n vezes.
    for (int i = 0; i < quantidadeSessoes - 1; i++)
    {
        // O(n): para cada execução do primeiro laço,
        // o segundo laço percorre parte do vetor.
        for (int j = 0; j < quantidadeSessoes - 1 - i; j++)
        {
            // O(1): declaração e inicialização da variável.
            int trocar = 0;

            // O(1): verifica o critério escolhido.
            if (criterio == 1)
            {
                // O(1): comparação dos IDs.
                if (ordem == 1 &&
                    sessoes[j].id > sessoes[j + 1].id)
                {
                    // O(1): define que haverá troca.
                    trocar = 1;
                }

                // O(1): comparação dos IDs.
                else if (ordem == 2 &&
                         sessoes[j].id < sessoes[j + 1].id)
                {
                    // O(1): define que haverá troca.
                    trocar = 1;
                }
            }

            // O(1): verifica o critério escolhido.
            else if (criterio == 2)
            {
                // O(1): comparação das energias.
                if (ordem == 1 &&
                    sessoes[j].energia > sessoes[j + 1].energia)
                {
                    // O(1): define que haverá troca.
                    trocar = 1;
                }

                // O(1): comparação das energias.
                else if (ordem == 2 &&
                         sessoes[j].energia < sessoes[j + 1].energia)
                {
                    // O(1): define que haverá troca.
                    trocar = 1;
                }
            }

            // O(1): verifica o critério escolhido.
            else if (criterio == 3)
            {
                // O(1): comparação dos custos.
                if (ordem == 1 &&
                    sessoes[j].custo > sessoes[j + 1].custo)
                {
                    // O(1): define que haverá troca.
                    trocar = 1;
                }

                // O(1): comparação dos custos.
                else if (ordem == 2 &&
                         sessoes[j].custo < sessoes[j + 1].custo)
                {
                    // O(1): define que haverá troca.
                    trocar = 1;
                }
            }

            // O(1): verifica o critério escolhido.
            else if (criterio == 4)
            {
                // O(1): comparação dos tempos.
                if (ordem == 1 &&
                    sessoes[j].tempo > sessoes[j + 1].tempo)
                {
                    // O(1): define que haverá troca.
                    trocar = 1;
                }

                // O(1): comparação dos tempos.
                else if (ordem == 2 &&
                         sessoes[j].tempo < sessoes[j + 1].tempo)
                {
                    // O(1): define que haverá troca.
                    trocar = 1;
                }
            }

            // O(1): verifica o critério escolhido.
            else if (criterio == 5)
            {
                // O(1): comparação das baterias iniciais.
                if (ordem == 1 &&
                    sessoes[j].bateria_inicial >
                    sessoes[j + 1].bateria_inicial)
                {
                    // O(1): define que haverá troca.
                    trocar = 1;
                }

                // O(1): comparação das baterias iniciais.
                else if (ordem == 2 &&
                         sessoes[j].bateria_inicial <
                         sessoes[j + 1].bateria_inicial)
                {
                    // O(1): define que haverá troca.
                    trocar = 1;
                }
            }

            // O(1): verifica se os elementos precisam ser trocados.
            if (trocar)
            {
                // O(1): copia uma struct para uma variável temporária.
                Sessao temporaria = sessoes[j];

                // O(1): copia a próxima struct para a posição atual.
                sessoes[j] = sessoes[j + 1];

                // O(1): copia a struct temporária para a próxima posição.
                sessoes[j + 1] = temporaria;
            }
        }
    }

    // O(1): impressão da mensagem.
    printf("\nSessões ordenadas com sucesso!\n\n");

    // O(n): percorre todas as sessões para exibi-las.
    listar_sessoes(sessoes, quantidadeSessoes);

    /*
    Complexidade:

    Primeiro for:
    O(n)

    Segundo for:
    O(n) para cada execução do primeiro.

    Operações dentro dos dois laços:
    O(1)

    Portanto:

    O(n) * O(n) * O(1) = O(n²)

    A chamada listar_sessoes() possui O(n), mas:

    O(n²) + O(n) = O(n²)

    Complexidade final da ordenação: O(n²)
    */
}

float calcular_energia_total(
    Sessao *sessao,
    int quantidadeSessoes
)
{
    float soma_energia = 0;

    for (int i = 0; i < quantidadeSessoes; i++)
    {
        soma_energia += sessao[i].energia;
    }

    return soma_energia;
}

float calcular_faturamento_total(
    Sessao *sessao,
    int quantidadeSessoes
)
{
    float soma_custo = 0;

    for (int i = 0; i < quantidadeSessoes; i++)
    {
        soma_custo += sessao[i].custo;
    }

    return soma_custo;
}

float calcular_maior_consumo(
    Sessao *sessao,
    int quantidadeSessoes
)
{
    float maior_consumo = sessao[0].energia;

    for (int i = 1; i < quantidadeSessoes; i++)
    {
        if (sessao[i].energia > maior_consumo)
        {
            maior_consumo = sessao[i].energia;
        }
    }

    return maior_consumo;
}

float calcular_menor_consumo(
    Sessao *sessao,
    int quantidadeSessoes
)
{
    float menor_consumo = sessao[0].energia;

    for (int i = 1; i < quantidadeSessoes; i++)
    {
        if (sessao[i].energia < menor_consumo)
        {
            menor_consumo = sessao[i].energia;
        }
    }

    return menor_consumo;
}

void exibir_estatisticas(
    Sessao *sessao,
    int quantidadeSessoes
)
{
    float energia_total =
        calcular_energia_total(
            sessao,
            quantidadeSessoes
        );

    float faturamento_total =
        calcular_faturamento_total(
            sessao,
            quantidadeSessoes
        );

    float maior_consumo =
        calcular_maior_consumo(
            sessao,
            quantidadeSessoes
        );

    float menor_consumo =
        calcular_menor_consumo(
            sessao,
            quantidadeSessoes
        );

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

    float media_tempo_recarga =
        calcular_media_tempo_recarga(
            sessao,
            quantidadeSessoes
        );

    printf("\n");
    titulo("ESTATÍSTICAS");
    printf("\n\n");

    printf(
        "Quantidade total de sessões: %d\n",
        quantidadeSessoes
    );

    printf(
        "Energia total fornecida: %.2f kWh\n",
        energia_total
    );

    printf(
        "Faturamento total: R$%.2f\n",
        faturamento_total
    );

    printf(
        "Custo médio das sessões: R$%.2f\n",
        media_valor_total
    );

    printf(
        "Maior consumo: %.2f kWh\n",
        maior_consumo
    );

    printf(
        "Menor consumo: %.2f kWh\n",
        menor_consumo
    );

    printf("\n");

    printf(
        "Média de energia necessária: %.2f kWh\n",
        media_energia_necessaria
    );

    printf(
        "Média de bateria inicial: %.2f%%\n",
        media_bateria_inicial
    );

    printf(
        "Média de tempo de recarga: %.2f minutos\n",
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

float calcular_media_tempo_recarga(
    Sessao *sessao,
    int quantidadeSessoes
)
{
    float soma_tempo = 0;

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