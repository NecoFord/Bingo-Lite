#include <stdio.h> 
#include <stdlib.h> 
#include <time.h> 
#include <string.h> 
// Foram incluídas bibliotecas extras para manipulação 
 
int venceu_ou_perdeu(int marcados[4][5], int usuario){ 
    int UsuarioVenceu = 1, completo; 
    // verifica se o usuario já sorteou todos os numeros 
    for (int i = 0; i < 5; i++){ 
        if (marcados[usuario - 1][i]==0){ //ainda não marcou todos 
            UsuarioVenceu = 0; 
            break; 
        } 
    } 
    if (UsuarioVenceu){ 
        return 0; //jagador venceu 
    } 
    for (int k = 0; k<4; ++k){ 
        if (k != usuario - 1){ 
            completo = 1; 
            for (int j = 0; j<5; ++j){ 
                if (marcados[k][j] == 0){ 
                    completo = 0; 
                    break; 
                } 
            } 
        if (completo) { return -1; } // outro "jogador" venceu antes 
        } 
    } 
    return 1; 
} 
int VerificadorSorteados(int vetor[], int i, int x){ 
    while (i--){ 
        if (vetor[i] == x) return 1;    //verifica se um numero sorteado é igual a 
algum numero 
    }                                   // na lista de numeros aleatorias 
    return 0; 
} 
 
int gerador_numero3000(int *sorteados, int *contador){ 
    int numero_sorteado; 
        do{ 
            numero_sorteado = 1+ (rand()%50); 
        } while (VerificadorSorteados(sorteados, *contador, numero_sorteado)); 
    sorteados[*contador] = numero_sorteado; //armazena o numero gerado 
para uma lista para que 
    (*contador)++;                          //nas proximas repetições o numero gerado 
não se repita 
    return numero_sorteado; 
} 
 
void print_numero_aleatorio(int sort){ // Exibe o número sorteado na tela 
    
printf("\n######################################################
#########\n"); 
    printf("#                    NÚMERO SORTEADO:  %d                     #\n", sort); 
    
printf("#######################################################
########\n"); 
} 
 
void Criador_de_Cartelas(int cartelas[4][50]){ 
    int totalLinhas = 0, r, repetido, escolhidas[4]; 
    char linha[100]; 
    FILE *file; 
    srand(time(NULL)); 
    file = fopen("cartelas.txt", "r"); 
    if (file == NULL) { 
        printf("Arquivo não encontrado\n"); 
        return; 
    } 
 
    while (fgets(linha, sizeof(linha), file) != NULL) { 
        totalLinhas++; //verifica quantas linhas tem no arquivo e atribui a um 
contador 
    } 
    fclose(file); 
    for (int i = 0; i < 4; i++) { 
        do { 
            r = rand() % totalLinhas; 
            repetido = 0; 
            for (int j = 0; j < i; j++) { 
                if (escolhidas[j] == r) repetido = 1; //não permite com que as linhas 
se repitam 
            } 
        } while (repetido); 
        escolhidas[i] = r; 
    } //esse loop pega 4 linhas distintas e atribui a posição da linha em um vetor 
     
     // Reabre arquivo e atribui os números às cartelas 
    file = fopen("cartelas.txt", "r"); 
    int linhaAtual = 0; 
    while (fgets(linha, sizeof(linha), file) != NULL) { 
        for (int i = 0; i < 4; i++) { 
            if (linhaAtual == escolhidas[i]) { 
                // Converte a linha lida em inteiros 
                sscanf(linha, "%d,%d,%d,%d,%d", 
                       &cartelas[i][0], &cartelas[i][1], &cartelas[i][2], 
                       &cartelas[i][3], &cartelas[i][4]); 
            } 
        } 
            linhaAtual++; 
    } 
    fclose(file); 
 
} 
 
void printCartelas(int cartelas[50], int quant_numeros, int num_cartela, int 
cartela_jogador) 
{ 
 
    printf("Cartela %d: |", num_cartela); 
 
    for (int i = 0; i < quant_numeros; i++) 
    { 
        printf(" %2d |", cartelas[i]); 
    } 
         
    if (cartela_jogador == num_cartela){  
        printf(" <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<"); // indica a 
cartela escolhida 
    }  
    printf("\n"); 
 
} 
 
int trocarCartela(int cartela_jogador){ 
    char resposta[10]; 
    int opcoes[3]; 
    int aux = 0; 
     
    // Define as opções de troca (exceto a cartela atual) 
    for (int i = 0; i < 4; i++) 
    {  
        if (aux == cartela_jogador-1){aux++;opcoes[i] = aux+1;} 
        else{opcoes[i] = aux+1;} 
        aux++; 
    } 
    printf("\n# SELECIONE OUTRA CARTELA (%d, %d ou %d) ou 
PRESSIONE ENTER PARA SORTEAR: __", opcoes[0], opcoes[1], 
opcoes[2]); 
    fgets(resposta, 10, stdin); 
    if (resposta[0] == '\n'){return 0;} // mantém cartela 
    else{int num = resposta[0] - '0'; return num;} // retorna cartela escolhida 
 
} 
 
// Marca os números sorteados dentro da cartela 
int marcador(int ctls[50], int quant_numeros, int sorteados, int marc[5]){ 
    int cont = 0; 
    for (int c = 0; c < quant_numeros; c++) 
    { 
        if (ctls[c] == sorteados && marc[c] != 1){ 
            marc[c] = 1; // marca número encontrado 
        } 
         
        if (marc[c] == 1){cont++;} // conta números marcados 
         
        if (cont == 5){return 1;} // cartela completa 
    } 
} 
 
void printRodadas(int marc[5], int quant_numeros, int cart, int ctls[50], int 
cartela_jogador) 
{ 
    char mr[6][20] = {{"           "},{"    "},{"    "},{"    "},{"    "},{"    "}}; 
    for (int u = 0; u < quant_numeros; u++) 
    { 
        if (marc[u] == 1) 
        { 
            strcpy(mr[u+1], "----"); 
        } 
    } 
     
    printf("\n"); 
    for (int i = 0; i < 6; i++) { 
        printf("%s ", mr[i]); 
    } 
    printf("\n"); 
     
    printCartelas(ctls, quant_numeros, (cart+1), cartela_jogador); 
     
 
    for (int i = 0; i < 6; i++) { 
        printf("%s ", mr[i]); 
    } 
     
 
} 
 
int main(){ 
    int tamanho = 50, sorteados[50], contador = 0, resultado; 
    int cartelas[5][50]; 
    int usuario = 1; // usuário começa com a cartela 1 
    int troca = 0; 
    char vencedor[50], tempo[100]; 
    FILE *arquivo; 
    time_t rawtime; 
    struct tm *info; 
    time(&rawtime); 
    info = localtime(&rawtime); 
    int marcados[4][5] = { // Marcações das cartelas (4 cartelas com 5 números 
cada) 
        {0, 0, 0, 0, 0}, 
        {0, 0, 0, 0, 0}, 
        {0, 0, 0, 0, 0}, 
        {0, 0, 0, 0, 0} 
    }; 
    int sort = 0; 
    int termino = 0; 
     
    Criador_de_Cartelas(cartelas); 
 
    while (termino != 1){ // Loop principal do jogo 
 
        sort = gerador_numero3000(sorteados, &contador); 
        print_numero_aleatorio(sort); 
        for (int p = 0; p < 4; p++){ 
            termino = marcador(cartelas[p], 5, sort, marcados[p]); 
            if (termino == 1){break;} // se alguma cartela foi completada, o jogo 
termina 
            printRodadas(marcados[p], 5, p, cartelas[p], usuario); 
        } 
         
        troca = trocarCartela(usuario); 
        if (troca != 0){usuario = troca;} 
         
 
         
    } 
    // Verifica o resultado da partida 
    resultado = venceu_ou_perdeu(marcados, usuario); 
     
    // Registra horário da vitória 
    strftime(tempo, sizeof(tempo), "%d/%m/%Y %H:%M:%S", info); 
    if (resultado){ 
     
        printf("# PARABÉNS! VOCÊ VENCEU!!!\n"); 
        printf("# Entre o seu nome para constar no rol de vencedores:"); 
        arquivo = fopen("vencedores.txt", "a"); // salva no histórico 
        fgets(vencedor, sizeof(vencedor), stdin); 
        vencedor[strcspn(vencedor, "\n")] = 0; 
        fprintf(arquivo, "%s ", vencedor); 
        fprintf(arquivo, "%s\n", tempo); 
        fclose(arquivo); 
     
    } else { 
        printf("# OUTRA CARTELA FOI COMPLETADA!\n"); 
        printf("# Melhor sorte na próxima vez!"); 
    } 
    return 0; 
} 