#include <iostream>
#include <locale.h>
#include <string.h>
#include <stdlib.h>
#include <Windows.h>
#include <math.h>
//Falta multiplicar por escalar e multiplicar pôlinomios
using namespace std;

struct No {
    int e;
    float k;
    No* eloA, * eloP;
};

struct LDE {
    No* comeco, * fim;
};

//Funções e definições

//Inicializa a lista setando os valores de lista.comeco e lista.fim
void inicializarLDE(LDE& lista);
// percorre a lista ao contrário para deixar o que for de maior grau pela frente
void mostrarLDE(LDE lista, string frase);
//Insere normalmente na LDE, só que insere dois insere dois índices, para a constante e outro para o expoente
bool inserirLDE(LDE& lista, float constante, int expoente);
//Retorna um nó onde o indice de expoente do parâmetro seja igual
No* buscarLDE(LDE lista, int expoente);
//retira o item da lista onde o expoente seja o desejado;
bool retirarLDE(LDE& lista, int expoente);
//Função simples de soma para utilizar nos indices K
float soma(float k1, float k2);
//Função simples de subtração para utilizar nos indices K
float sub(float k1, float k2);
// Função que executará o menu, dando opções ao usuário
void menu();
//potenciação simples
float exponenciacao(float base, int expoente);
//Multiplica os indices K por uma constante !IMPORTANTE, ALTERA A PRÓPRIA LISTA.
void multiplicarPorEscalar(LDE& lista, int x);
//Lê apenas uma lista de polinômios para soma, escalar e valor numérico
void lerPolinomioUmaLista(LDE& lista);
//Lê duas listas para qualquer outro tipo de operação - sub e multiplicação de polinomios
void lerPolinomioDuasListas(LDE& lista, LDE& lista1);
//Soma o indice K e mantem o E
LDE somaExp(LDE lista);
//Subtrai o indice K e mantem o E
LDE subPolinomios(LDE lista1, LDE lista2);
//SOMA DUAS LISTAS DE POLINOMIO
LDE somaPolinomios(LDE lista1, LDE lista2);
//multiplica um polinômio por outro
LDE produtoPolinomio(LDE lista1, LDE lista2);
//substitui o valor de x, potencia esse valor pelo indice e para depois multiplicar por E
float valorNumerico(LDE lista, float x);

int main() {
    setlocale(LC_ALL, "Portuguese");
    /*
    LDE lista1, lista, lista2, lista3, listaSUB;
    float valNum;
    //INICIALIZANDO TODAS AS LISTAS QUE NECESSITAM DE INICIALIZAÇÃO
    inicializarLDE(lista); inicializarLDE(lista1); inicializarLDE(lista2); inicializarLDE(lista3);
    //CHAMA FUNÇÃO QUE IRÁ INSERIR EM LISTA OS POLINÔMIOS - PARA SOMA
     //lerPolinomioUmaLista(lista); //descomentar
     //mostrarLDE(lista, "Polinomios a serem somados");
     //listaSOMA = somaExp(lista);
     //mostrarLDE(listaSOMA, "Polinomio Somado:");
    cout << endl;
    // multiplicarPorEscalar(lista, 2);
    mostrarLDE(lista, "Multiplicacao por escalar");
    //lerPolinomioDuasListas(lista2, lista3);
    mostrarLDE(lista2, "1o Polinomio sub");
    mostrarLDE(lista3, "2o Polinomio sub");
    //listaSUB = subPolinomios(lista2, lista3);
    listaSUB = produtoPolinomio(lista2, lista3);
    mostrarLDE(listaSUB, "Resultado subtraido");
    cout << endl;
    //valnum = valorNumerico(lista, 2.0);
    //cout << endl << "Valor numerico = " << valnum;
    inserirLDE(lista1, 2, 2);
    inserirLDE(lista1, 3, 3);
    valNum = valorNumerico(lista1, 2);
    cout << "Valor numérico do polinomio: " << valNum << endl; */
    menu();

    return 0;
}


//SOMA
//inserirLDE(lista, 2, 2);
//inserirLDE(lista, -3, 1);
//inserirLDE(lista, -1, 0);
//inserirLDE(lista, -3, 2);
//inserirLDE(lista, 8, 1);
//inserirLDE(lista, -6, 0);

/*SUB
inserirLDE(lista2, 5, 2);
inserirLDE(lista2, -9, 1);
inserirLDE(lista2, -8, 0);
inserirLDE(lista2, -3, 2);
inserirLDE(lista3, -3, 2);
inserirLDE(lista3, 8, 1);
inserirLDE(lista3, -6, 0);*/

void inicializarLDE(LDE& lista) {
    lista.comeco = NULL;
    lista.fim = NULL;
}

void mostrarLDE(LDE lista, string frase)
{
    cout << frase << ": ";
    if (lista.comeco == NULL) cout << " vazia";

    No* aux = lista.fim;
    while (aux != NULL) {

        if (aux->k != 0)
        {
            if( aux != lista.fim && aux->k > 0) cout << "+ ";
            if (aux->e == 0) cout << aux->k << " ";
            else if (aux->e == 1) cout << aux->k << "x ";
            else cout << aux->k << "x^" << aux->e << " ";
        }
        aux = aux->eloA;
    }
    cout << endl;
}

bool inserirLDE(LDE& lista, float constante, int expoente) {
    No* novo = new No;

    if (novo == NULL) return false;
    novo->e = expoente;
    novo->k = constante;
    novo->eloA = NULL;
    novo->eloP = NULL;

    // Inserir em lista vazia
    if (lista.comeco == NULL) {
        lista.comeco = novo;
        lista.fim = novo;
        return true;
    }

    // Inserir no inicio da lista
    if (novo->e < lista.comeco->e) {
        novo->eloP = lista.comeco;
        lista.comeco->eloA = novo;
        lista.comeco = novo;
        return true;
    }

    // Inserir no final da lista
    if (novo->e > lista.fim->e) {
        lista.fim->eloP = novo;
        novo->eloA = lista.fim;
        lista.fim = novo;
        return true;
    }

    // Inserir no meio da lista
    No* aux = lista.comeco;
    while (aux->e < expoente && aux->eloP->e < expoente)
        aux = aux->eloP;
    novo->eloP = aux->eloP;
    novo->eloA = aux;
    aux->eloP->eloA = novo;
    aux->eloP = novo;
    return true;
}

No* buscarLDE(LDE lista, int expoente) {
    No* aux = lista.comeco;
    while (aux != NULL) {
        if (aux->e == expoente) return aux;
        aux = aux->eloP;
    }
    return NULL;
}

bool retirarLDE(LDE& lista, int expoente) {
    No* pos;

    pos = buscarLDE(lista, expoente);
    if (pos == NULL) return false;  // Lista vazia ou valor n�o encontrado

    // Retirada no inicio da lista
    if (pos == lista.comeco) {
        No* prox = pos->eloP; // Pega o pr�ximo n�
        lista.comeco = prox;
        if (prox != NULL) prox->eloA = NULL;
        if (pos == lista.fim) lista.fim = NULL;
    }
    else {
        No* ant = pos->eloA; // Pega o n� anterior
        No* prox = pos->eloP; // Pega o n� seguinte
        if (ant != NULL) ant->eloP = prox;
        if (prox != NULL) prox->eloA = ant;
        if (pos == lista.fim) lista.fim = ant;
    }
    delete(pos);
    return true;
}

float soma(float k1, float k2)
{
    float aux;
    aux = k1 + k2;
    return aux;
}

float sub(float k1, float k2)
{
    float aux;
    aux = k1 - k2;
    return aux;
}

void menu()
{
    LDE lista1, lista2, listaOP;
    inicializarLDE(lista1); inicializarLDE(lista2);
    int escolha = 0, xEscalar = 0, desejo = 0;
    float valNum = 0, vNEscolha = 0;

    cout << "+-------------------------------------------------------------+" << endl;
    cout << "|                                                             |" << endl;
    cout << "|                                                             |" << endl;
    cout << "|                                                             |" << endl;
    cout << "|                  CALCULADORA DE POLINOMIOS                  |" << endl;
    cout << "|                       By: Jpg e Pz                          |" << endl;
    cout << "|                                                             |" << endl;
    cout << "|                                                             |" << endl;
    cout << "|                                                             |" << endl;
    cout << "+------------------------------------------------------------ +" << endl;
    Sleep(5000);
    system("cls");
    do
    {
        cout << "+-------------------------------------------------------------+" << endl;
        cout << "|                                                             |" << endl;
        cout << "|                  ESCOLHA A OPCAO DESEJADA:                  |" << endl;
        cout << "|                       1- SOMA                               |" << endl;
        cout << "|                      2- SUBTRACAO                           |" << endl;
        cout << "|                3- MULTIPLICACAO POR ESCALAR                 |" << endl;
        cout << "|                    4- VALOR NUMERICO                        |" << endl;
        cout << "|               5- MULTIPLICACAO DE POLINOMIO                 |" << endl;
        cout << "|                                                             |" << endl;
        cout << "+------------------------------------------------------------ +" << endl;
        cin >> escolha;
        system("cls");
    } while (escolha > 5 || escolha <= 0);

    switch (escolha)
    {
    case 1: //SOMA
        lerPolinomioDuasListas(lista1, lista2);
        mostrarLDE(lista1, "1o Polinomio soma");
        mostrarLDE(lista2, "2o Polinomio soma");
        listaOP = somaPolinomios(lista1, lista2);
        cout << endl;
        mostrarLDE(listaOP, "Resultado Soma");
        break;
    case 2: // SUB
        lerPolinomioDuasListas(lista1, lista2);
        mostrarLDE(lista1, "1o Polinomio sub");
        mostrarLDE(lista2, "2o Polinomio sub");
        cout << endl;
        listaOP = subPolinomios(lista1, lista2);
        mostrarLDE(listaOP, "Resultado Sub");
        break;
    case 3: //Escalar
        cout << "+-------------------------------------------------------------+" << endl;
        cout << "|                                                             |" << endl;
        cout << "|                                                             |" << endl;
        cout << "|                                                             |" << endl;
        cout << "|                  ENTRE COM UM VALOR PARA A                  |" << endl;
        cout << "|                       MULTIPLICACAO                         |" << endl;
        cout << "|                                                             |" << endl;
        cout << "|                                                             |" << endl;
        cout << "|                                                             |" << endl;
        cout << "+------------------------------------------------------------ +" << endl;
        cin >> xEscalar;
        system("cls");
        lerPolinomioUmaLista(lista1);
        mostrarLDE(lista1, "Polinomio a ser multiplicado");
        cout << "Escalar que irá multiplicar: " << xEscalar;
        multiplicarPorEscalar(lista1, xEscalar);
        cout << endl;
        mostrarLDE(lista1, "Resultado multiplicacao por escalar");
        break;
    case 4: // VALOR NUMERICO
        cout << "+-------------------------------------------------------------+" << endl;
        cout << "|                                                             |" << endl;
        cout << "|                                                             |" << endl;
        cout << "|                                                             |" << endl;
        cout << "|                  ENTRE COM UM VALOR PARA A                  |" << endl;
        cout << "|                        A VARIAVEL X                         |" << endl;
        cout << "|                                                             |" << endl;
        cout << "|                                                             |" << endl;
        cout << "|                                                             |" << endl;
        cout << "+------------------------------------------------------------ +" << endl;
        cin >> vNEscolha;
        system("cls");
        lerPolinomioUmaLista(lista1);
        mostrarLDE(lista1, "Polinomio recebido");
        cout << "Valor de X" << vNEscolha;
        valNum = valorNumerico(lista1, vNEscolha);
        cout << endl << "Valor numerico do polinomio eh igual a " << valNum;
        break;
    default: //MULTIPLICACAO DE POLINOMIO
        lerPolinomioDuasListas(lista1, lista2);
        mostrarLDE(lista1, "1o polinomio para multiplicacao");
        mostrarLDE(lista2, "2o polinomio para multiplicacao");
        listaOP = produtoPolinomio(lista1, lista2);
        mostrarLDE(listaOP, "Resultado produto dos polinomios");
        break;
    }
    Sleep(10000);
    system("cls");
    cout << "+-------------------------------------------------------------+" << endl;
    cout << "|                                                             |" << endl;
    cout << "|                                                             |" << endl;
    cout << "|                                                             |" << endl;
    cout << "|                DESEJA REALIZAR OUTRA CONTA?                 |" << endl;
    cout << "|                     1- Sim || 2 - Nao                       |" << endl;
    cout << "|                                                             |" << endl;
    cout << "|                                                             |" << endl;
    cout << "|                                                             |" << endl;
    cout << "+------------------------------------------------------------ +" << endl;
    cin >> desejo;
    if (desejo == 1)
    {
        system("cls");
        menu();
    }
}

float exponenciacao(float base, int expoente) {
    float resultado = 1;
    for (int i = 0; i < expoente; i++) {
        resultado *= base;
    }
    return resultado;
}

void multiplicarPorEscalar(LDE& lista, int x) {
    No* aux = lista.comeco;

    while (aux != NULL)
    {
        if (aux->e != 0)
        {
            aux->k *= x;
            aux = aux->eloP;
        }
    }
}

void lerPolinomioUmaLista(LDE& lista)
{
    int e, flag = 1, cont = 0;
    float k;

    do {

        if (cont == 0)
        {
            cout << "+-------------------------------------------------------------+" << endl;
            cout << "|                         Atencao!                            |" << endl;
            cout << "|        Coloque todos os monomios do Polinomio               |" << endl;
            cout << "|                         ou seja...                          |" << endl;
            cout << "|                                                             |" << endl;
            cout << "|            Insira todos os monomios, um de cada vez,        |" << endl;
            cout << "|         Insira todos os monomios, um de cada vez,           |" << endl;
            cout << "|              independente da ordem e sinal!                 |" << endl;
            cout << "+------------------------------------------------------------ +" << endl;
            Sleep(5000);
            system("cls");
        }

        cout << "+-------------------------------------------------------------+" << endl;
        cout << "|                                                             |" << endl;
        cout << "|                                                             |" << endl;
        cout << "|                                                             |" << endl;
        cout << "|                    Digite a constante:                      |" << endl;
        cout << "|                                                             |" << endl;
        cout << "|                                                             |" << endl;
        cout << "|                                                             |" << endl;
        cout << "|                                                             |" << endl;
        cout << "+------------------------------------------------------------ +" << endl;
        cin >> k;
        system("cls");

        cout << "+-------------------------------------------------------------+" << endl;
        cout << "|                                                             |" << endl;
        cout << "|                                                             |" << endl;
        cout << "|                                                             |" << endl;
        cout << "|                     Digite o expoente:                      |" << endl;
        cout << "|                                                             |" << endl;
        cout << "|                                                             |" << endl;
        cout << "|                                                             |" << endl;
        cout << "|                                                             |" << endl;
        cout << "+------------------------------------------------------------ +" << endl;
        cin >> e;
        system("cls");

        inserirLDE(lista, k, e);

        cout << "+-------------------------------------------------------------+" << endl;
        cout << "|                                                             |" << endl;
        cout << "|                                                             |" << endl;
        cout << "|                                                             |" << endl;
        cout << "|           Deseja inserir mais algum polinomio ?             |" << endl;
        cout << "|                   1 - Sim || 0 - Nao                        |" << endl;
        cout << "|                                                             |" << endl;
        cout << "|                                                             |" << endl;
        cout << "|                                                             |" << endl;
        cout << "+------------------------------------------------------------ +" << endl;
        cin >> flag;
        system("cls");
        if (cont == 0) cont++;
    } while (flag != 0);
}

void lerPolinomioDuasListas(LDE& lista, LDE& lista1)
{
    int e, flag = 1;
    float k;

    cout << "+-------------------------------------------------------------+" << endl;
    cout << "|                         Atencao!                            |" << endl;
    cout << "|     Coloque todos os monomios da lista que sera operada     |" << endl;
    cout << "|                         ou seja...                          |" << endl;
    cout << "|       Se voce deseja  utilizar os seguintes polinomios:     |" << endl;
    cout << "|              (7x^2 + 8^3 + 4)  ? (4x^2 + 2x^3 - 2)          |" << endl;
    cout << "|    Insira os monomios do primeiro polinomio, ou seja...     |" << endl;
    cout << "|                 7 e depois 2, 8 depois 3...                 |" << endl;
    cout << "+------------------------------------------------------------ +" << endl;
    Sleep(5000);
    system("cls");
    do
    {
        cout << "+-------------------------------------------------------------+" << endl;
        cout << "|                                                             |" << endl;
        cout << "|                                                             |" << endl;
        cout << "|                                                             |" << endl;
        cout << "|                    Digite a constante:                      |" << endl;
        cout << "|                                                             |" << endl;
        cout << "|                                                             |" << endl;
        cout << "|                                                             |" << endl;
        cout << "|                                                             |" << endl;
        cout << "+------------------------------------------------------------ +" << endl;
        cin >> k;
        system("cls");

        cout << "+-------------------------------------------------------------+" << endl;
        cout << "|                                                             |" << endl;
        cout << "|                                                             |" << endl;
        cout << "|                                                             |" << endl;
        cout << "|                     Digite o expoente:                      |" << endl;
        cout << "|                                                             |" << endl;
        cout << "|                                                             |" << endl;
        cout << "|                                                             |" << endl;
        cout << "|                                                             |" << endl;
        cout << "+------------------------------------------------------------ +" << endl;
        cin >> e;
        system("cls");

        inserirLDE(lista, k, e);

        cout << "+-------------------------------------------------------------+" << endl;
        cout << "|                                                             |" << endl;
        cout << "|                                                             |" << endl;
        cout << "|                                                             |" << endl;
        cout << "|           Deseja inserir mais algum polinomio ?             |" << endl;
        cout << "|                   1 - Sim || 0 - Nao                        |" << endl;
        cout << "|                                                             |" << endl;
        cout << "|                                                             |" << endl;
        cout << "|                                                             |" << endl;
        cout << "+------------------------------------------------------------ +" << endl;
        cin >> flag;
        system("cls");
    } while (flag != 0);

    flag = 1;


    cout << "+------------------------------------------------------------ +" << endl;
    cout << "|                         Atencao!                            |" << endl;
    cout << "|    Coloque todos os monomios da lista que sera operada      |" << endl;
    cout << "|                         ou seja...                          |" << endl;
    cout << "|       Se voce deseja  utilizar os seguintes polinomios:     |" << endl;
    cout << "|              (7x^2 + 8^3 + 4)  ? (4x^2 + 2x^3 - 2)          |" << endl;
    cout << "|    Insira os monomios do primeiro polinomio, ou seja...     |" << endl;
    cout << "|                 4 e depois 2, 2 depois 3...                 |" << endl;
    cout << "+------------------------------------------------------------ +" << endl;
    Sleep(5000);
    system("cls");

    do
    {
        cout << "+-------------------------------------------------------------+" << endl;
        cout << "|                                                             |" << endl;
        cout << "|                                                             |" << endl;
        cout << "|                                                             |" << endl;
        cout << "|                    Digite a constante:                      |" << endl;
        cout << "|                                                             |" << endl;
        cout << "|                                                             |" << endl;
        cout << "|                                                             |" << endl;
        cout << "|                                                             |" << endl;
        cout << "+------------------------------------------------------------ +" << endl;

        cin >> k;
        system("cls");

        cout << "+-------------------------------------------------------------+" << endl;
        cout << "|                                                             |" << endl;
        cout << "|                                                             |" << endl;
        cout << "|                                                             |" << endl;
        cout << "|                     Digite o expoente:                      |" << endl;
        cout << "|                                                             |" << endl;
        cout << "|                                                             |" << endl;
        cout << "|                                                             |" << endl;
        cout << "|                                                             |" << endl;
        cout << "+------------------------------------------------------------ +" << endl;
        cin >> e;
        system("cls");

        inserirLDE(lista1, k, e);

        cout << "+-------------------------------------------------------------+" << endl;
        cout << "|                                                             |" << endl;
        cout << "|                                                             |" << endl;
        cout << "|                                                             |" << endl;
        cout << "|           Deseja inserir mais algum polinomio ?             |" << endl;
        cout << "|                   1 - Sim || 0 - Nao                        |" << endl;
        cout << "|                                                             |" << endl;
        cout << "|                                                             |" << endl;
        cout << "|                                                             |" << endl;
        cout << "+------------------------------------------------------------ +" << endl;
        cin >> flag;
        system("cls");

    } while (flag != 0);

}

LDE somaExp(LDE lista) {
    LDE novaLista;
    inicializarLDE(novaLista);

    No* aux1 = lista.comeco;
    No* aux2;

    while (aux1 != NULL) {
        aux2 = buscarLDE(novaLista, aux1->e); // aux2 será justamente o outro Nó com o mesmo expoente.

        if (aux2 != NULL) {
            aux2->k += aux1->k; // aux2->k irá armazenar o valor de K até que não tenha mais nós com o mesmo expoente, aí sim inserir na função abaixo
        }
        else {
            inserirLDE(novaLista, aux1->k, aux1->e);
        }

        aux1 = aux1->eloP;
    }

    return novaLista;
}

LDE subPolinomios(LDE lista1, LDE lista2) {
    LDE resultado, lista1aux, lista2aux;
    inicializarLDE(resultado);

    lista1aux = somaExp(lista1);
    lista2aux = somaExp(lista2);

    No* aux1 = lista1aux.comeco;
    No* aux2 = lista2aux.comeco;

    while (aux1 != NULL && aux2 != NULL) { //percorrendo as duas listas simultaneamentes até que as duas estejam vazias
        if (aux1->e == aux2->e) { // se os expoentes em ambas listas forem iguais
            float novoK = sub(aux1->k, aux2->k); // as constantes serão subtraídas e armazenadas em novoK
            if (novoK != 0) {
                inserirLDE(resultado, novoK, aux1->e); //novoK é inserido como expoente na nova LDE
            }
            aux1 = aux1->eloP; // os auxiliares sempre e somente passarão para o eloP caso ocorra inserção na lista
            aux2 = aux2->eloP; // Neste caso ambos foram subtraidos e somados.
        }
        else if (aux1->e < aux2->e) { // Se o expoente da lista2 for maior que o da lista1 ele somente será inserido
            inserirLDE(resultado, aux1->k, aux1->e);
            aux1 = aux1->eloP;
        }
        else {
            float novoK = sub(0, aux2->k); // caso o expoente do item da lista 2 for maior o que será inserido, na prática, será o valor da lista 2 *-1
            if (novoK != 0) {
                inserirLDE(resultado, novoK, aux2->e);
            }
            aux2 = aux2->eloP;
        }
    }

    while (aux1 != NULL) {
        inserirLDE(resultado, aux1->k, aux1->e);
        aux1 = aux1->eloP;
    }

    while (aux2 != NULL) {
        float novoK = sub(0, aux2->k);
        if (novoK != 0) {
            inserirLDE(resultado, novoK, aux2->e);
        }
        aux2 = aux2->eloP;
    }

    return resultado;
}

LDE somaPolinomios(LDE lista1, LDE lista2) {
    LDE resultado, lista1aux, lista2aux;
    inicializarLDE(resultado);

    lista1aux = somaExp(lista1);
    lista2aux = somaExp(lista2);

    No* aux1 = lista1aux.comeco;
    No* aux2 = lista2aux.comeco;

    while (aux1 != NULL && aux2 != NULL) { //percorrendo as duas listas simultaneamentes até que as duas estejam vazias
        if (aux1->e == aux2->e) { // se os expoentes em ambas listas forem iguais
            float novoK = soma(aux1->k, aux2->k); // as constantes serão subtraídas e armazenadas em novoK
            if (novoK != 0) {
                inserirLDE(resultado, novoK, aux1->e); //novoK é inserido como expoente na nova LDE
            }
            aux1 = aux1->eloP; // os auxiliares sempre e somente passarão para o eloP caso ocorra inserção na lista
            aux2 = aux2->eloP; // Neste caso ambos foram subtraidos e somados.
        }
        else if (aux1->e < aux2->e) { // Se o expoente da lista2 for maior que o da lista1 ele somente será inserido
            inserirLDE(resultado, aux1->k, aux1->e);
            aux1 = aux1->eloP;
        }
        else {
            float novoK = soma(0, aux2->k); // caso o expoente do item da lista 2 for maior o que será inserido, na prática, será o valor da lista 2 *-1
            if (novoK != 0) {
                inserirLDE(resultado, novoK, aux2->e);
            }
            aux2 = aux2->eloP;
        }
    }

    while (aux1 != NULL) {
        inserirLDE(resultado, aux1->k, aux1->e);
        aux1 = aux1->eloP;
    }

    while (aux2 != NULL) {
        float novoK = soma(0, aux2->k);
        if (novoK != 0) {
            inserirLDE(resultado, novoK, aux2->e);
        }
        aux2 = aux2->eloP;
    }

    return resultado;
}


LDE produtoPolinomio(LDE lista1, LDE lista2) {
    LDE novaLista, lista1aux, lista2aux;

    lista1aux = somaExp(lista1);
    lista2aux = somaExp(lista2);
    inicializarLDE(novaLista);

    No* aux1 = lista1aux.comeco; //Variável utilizada como item da primeira lista que multiplicará a segunda, ou seja, o item que irá fazer o chuveirih9o

    while (aux1 != NULL) {
        No* aux2 = lista2aux.comeco; //Variável que será multiplicada

        while (aux2 != NULL) {
            float k = aux1->k * aux2->k;
            int e = aux1->e + aux2->e;

            No* noExistente = buscarLDE(novaLista, e);

            if (noExistente == NULL) {
                inserirLDE(novaLista, k, e);
            }
            else {
                noExistente->k = soma(noExistente->k, k);
            }

            aux2 = aux2->eloP;
        }

        aux1 = aux1->eloP;
    }

    return novaLista;
}

float valorNumerico(LDE lista, float x) {
    float valNum = 0, exp, k;
    No* aux = lista.comeco;
    while (aux != NULL) {
        exp = pow(x, aux->e);
        k = aux->k * exp;
        valNum += k;
        aux = aux->eloP;
    }

    return valNum;
}
