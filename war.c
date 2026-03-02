// bibliotecas necessárias para o funcionamento do jogo 

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>


// criação da estrutura para os territórios, contendo nome, cor do exército e número de tropas

struct Territorio {
    char nome[25];
    char cor[15];
    int tropas;
    int eliminarAlvo;
};

// função para limpar o buffer de entrada
void limparbuffer() {
    int c;
    while ((c = getchar ()) != '\n' && c != EOF);
}

// função para mostrar os territórios registrados
void mostrarTerritorios(struct Territorio * t, int n) {
    printf("======== TERRITORIOS REGISTRADOS ========\n");
    for (int i= 0; i < n; i++) {
        printf("%d.: %s    ||EXERCITO: %s    ||TROPAS: %d\n", i+1, t[i].nome, t[i].cor, t[i].tropas);
    }
}

// funcão para sortear uma missão aleatória para o jogador
void atribuirMissao(char* destino, char* missoes[], int totalMissoes) {
    int sorteio = rand() % totalMissoes;
    strcpy(destino, missoes[sorteio]);
}

// função para mostrar a missão sorteada
void exibirMissao(char* missao) {
    printf("\n===== SUA MISSÃO =====\n");
    printf("%s\n", missao);
    printf("======================\n\n");
}

    // função para verificar se a missão foi cumprida
    int verificarMissao(char * missao, struct Territorio* t, char* corJogador, int tamanho) {
        
        int territoriosPlayer = 0;
        int vermelhoExiste = 0;
        int amareloExiste = 0;

        for (int i = 0; i < tamanho; i++) {
            if (strcmp(t[i].cor, corJogador) == 0) {
                territoriosPlayer++;
             }

        if (strcmp(t[i].cor, "Amarelo") == 0) {
            amareloExiste = 1;
        }

        if (strcmp(t[i].cor, "Vermelho") == 0) {
            vermelhoExiste = 1;
        }
    }

    if (strcmp(missao, "Eliminar o exército Amarelo") == 0) {
        return !amareloExiste;
    } else if (strcmp(missao, "Eliminar o exército Vermelho") == 0) {
        return !vermelhoExiste;
    } else if (strcmp(missao, "Conquistar 3 territorios") == 0) {
        return territoriosPlayer >= 3;
    } else if (strcmp(missao, "Conquistar 2 territorios") == 0) {
        return territoriosPlayer >= 2;
    } else if (strcmp(missao, "Conquiste todos os territorios") == 0) {
        return territoriosPlayer == tamanho;
    }

    return 0;
}

// função para realizar o ataque entre dois territórios, comparando os dados sorteados e atualizando o número de tropas e a cor do território conquistado, se for o caso
void ataque(struct Territorio* atacante, struct Territorio* defensor) {
    if (atacante -> tropas <= 1)
    {
        printf("ESTE TERRITORIO NAO POSSUI TROPAS SUFICIENTES PARA ATACAR!\n");
        return;
    }

    int dadoAtacante = rand() % 6 + 1;
    int dadoDefensor = rand() % 6 + 1;

    printf("======== RESULTADO DOS DADOS ========\n");
    printf("DADO DO TERRITORIO ATACANTE: %d\n", dadoAtacante);
    printf("DADO DO TERRITORIO DEFENSOR: %d\n", dadoDefensor);

    if (dadoAtacante > dadoDefensor)
    {
        defensor -> tropas --;
        printf("O DEFENSOR PERDEU UMA TROPA!\n");
    } else {
        atacante -> tropas --;
        printf("O ATACANTE PERDEU UMA TROPA!\n");
    }
    
    if (defensor -> tropas == 0)
    {
        printf("O TERRITORIO %s FOI CONQUISTADO!\n", defensor -> nome);
        strcpy(defensor -> cor, atacante -> cor);
        
        int tropasmovidas = atacante -> tropas / 2;

        defensor -> tropas = tropasmovidas;
        atacante -> tropas -= tropasmovidas;
    }
    
    
}

// função para  liberar a memória alocada para os territórios e para missao
void liberarMemoria(struct Territorio* t, char *missao) {
    free(t);
    free(missao);
}

// Menu inicial

int main() {

// funcao para inicializar a semente de números aleatórios
    srand(time(NULL));

    printf("========================================\n");
    printf("======== BEM-VINDO AO JOGO WAR ========\n");
    printf("========================================\n");

    printf("\n");

    printf("    == PRESSIONE ENTER PARA ENTRAR ==\n");
    getchar();
 
    printf("         INICIANDO O JOGO...\n");

    printf("\n");

    printf("     QUANTOS TERRITÓRIOS VOCÊ QUER REGISTRAR?\n");

    // variável para armazenar o número de territórios a serem registrados
    int n;

    scanf("%d", &n);

    struct Territorio* t = malloc(n * sizeof(struct Territorio));

    // registro dos territórios (entrada de dados)

    for (int i = 0; i < n; i++)
    {
        printf("=============================\n");
        printf("TERRITORIO %d\n", i+1);
        printf("NOME:");
        scanf("%s", t[i].nome);
        printf("COR:");
        scanf("%s", t[i].cor);
        printf("TROPAS:");
        scanf("%d", &t[i].tropas);
        printf("=============================\n");
        limparbuffer(); 
    }


    printf("\n");

    printf("=========================================\n");

     char* missoesDisponiveis[] = {
        "Conquistar 3 territorios",
        "Conquistar 2 territorios",
        "Eliminar o exército Amarelo",
        "Conquistar todos os territorios",
        "Eliminar o exército Vermelho"
    };

    int totalMissoes = 5;

    char* missaoPlayer = malloc(100 * sizeof(char));

    atribuirMissao(missaoPlayer, missoesDisponiveis, totalMissoes);

    exibirMissao(missaoPlayer);


    int opcao;

    // laço principal do jogo, onde o jogador pode escolher atacar ou sair
    do
    {
        mostrarTerritorios(t, n);

        printf("====== HORA DE ATACAR! ======\n");
        printf("1. ATACAR\n");
        printf("2. VERIFICAR MISSÃO\n");
        printf("0. SAIR\n");
        printf("ESCOLHA UMA OPCAO: \n");
        scanf("%d", &opcao);

        if (opcao == 1)
        {
            int ata, def;

            printf("ESCOLHA O TERRITORIO ATACANTE (1-%d):\n", n);
            scanf("%d", &ata);
            printf("ESCOLHA O TERRITORIO DEFENSOR (1-%d): \n", n);
            scanf("%d", &def);
            
            if (ata < 1 || ata > n || def < 1 || def > n || ata == def)
            {
                printf("ESCOLHA INVALIDA\n");
            } else {
                ataque(&t[ata - 1], &t[def - 1]);
            }  
        }
        else if (opcao == 2)
        {
            if (verificarMissao(missaoPlayer, t, t[0].cor, n))
            {
                printf("PARABENS! VOCE CUMPRIU SUA MISSAO!\n");
                break;
            } else {
                printf("VOCE AINDA NAO CUMPRIU SUA MISSAO. CONTINUE JOGANDO!\n");
            }
        } else if (opcao == 0) {
            printf("ENCERRANDO O JOGO... OBRIGADO POR JOGAR!\n");
        } else {
            printf("OPCAO INVALIDA. TENTE NOVAMENTE.\n");
        }
    } while (opcao != 0);
  liberarMemoria(t, missaoPlayer);
    return 0;
}

