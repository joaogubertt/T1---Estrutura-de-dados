#include <iostream>
#include <locale.h>
#include <conio.h>
#include <string.h>
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

void inicializarLDE(LDE& lista) {
    lista.comeco = NULL;
    lista.fim = NULL;
}

// A vari�vel sentido pode ser C(crescente) ou D(decrescente)
void mostrarLDE(LDE lista, string frase)
{
    cout << frase << ": ";
    if (lista.comeco == NULL) cout << " vazia";

    No* aux = lista.fim;
    while (aux != NULL) {

    if(aux->k != 0)
    {
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

void lerPolinomios(LDE& lista) // Função que irá receber os valores da constante e do expoente e armazenará em uma LDE
{
    char tecla;
    int e, cont;
    float k;
    cont = 0;

    do {
        cout << "Digite a constante: ";
        cin >> k;

        cout << "Digite o expoente: ";
        cin >> e;

        inserirLDE(lista, k, e);

        cout << "Aperte Esc para sair ou qualquer outra tecla para continuar: " << endl;
        tecla = _getch();
        cont++;
    } while (tecla != 27); cout << cont;
}

LDE somaExp(LDE lista) {
    LDE novaLista;
    inicializarLDE(novaLista);

    No* aux1 = lista.comeco;
    No* aux2;

    while (aux1 != NULL) {
        aux2 = buscarLDE(novaLista, aux1->e);

        if (aux2 != NULL) {
            aux2->k += aux1->k;
        } else {
            inserirLDE(novaLista, aux1->k, aux1->e);
        }

        aux1 = aux1->eloP;
    }

    return novaLista;
}

LDE somaPolinomio(LDE lista1, LDE lista2) {
    LDE novaLista, resultado;
    inicializarLDE(novaLista);

    No* adicionarALista = lista2.comeco;
    while (adicionarALista != NULL)
    {
        inserirLDE(lista1, adicionarALista->k, adicionarALista->e);
        adicionarALista = adicionarALista->eloP;
    }

    No* aux = lista1.comeco;

    while (aux != NULL) {
        No* temp = buscarLDE(novaLista, aux->e);

        if (temp == NULL) {
            inserirLDE(novaLista, aux->k, aux->e);
        }
        else {
            temp->k = soma(temp->k, aux->k);
        }

        aux = aux->eloP;
    }

    resultado = somaExp(novaLista);
    return resultado;
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
        else if (aux1->e < aux2->e) { // Se o expoente da lista1 for maior que o da lista2 ele somente será inserido
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


int main() {
    setlocale(LC_ALL, "Portuguese");

    //Ainda falta utilizar um leitor de Polinomio diferente do meu, pois não funciona, nele deve haver a inicialização
    // da lista que for inserido, tudo isso para abstrair o máximo de linhas de código.

    LDE lista1, lista, listaSOMA, lista2, lista3, listaSUB;
    inicializarLDE(lista);
    inicializarLDE(lista1);
    inicializarLDE(lista2);
    inicializarLDE(lista3);
    cout << endl;
    //SOMA
    inserirLDE(lista, 2, 2);
    inserirLDE(lista, -3, 1);
    inserirLDE(lista, -1, 0);
    mostrarLDE(lista, "Polinomios a serem somados");
    inserirLDE(lista1, -3, 2);
    inserirLDE(lista1, 8, 1);
    inserirLDE(lista1, -6, 0);
    mostrarLDE(lista1, "Polinomios a serem somados");
    listaSOMA = somaPolinomio(lista1, lista);
    mostrarLDE(listaSOMA, "Polinomio Somado:");
    cout << endl;

    inserirLDE(lista2, 5, 2);
    inserirLDE(lista2, -9, 1);
    inserirLDE(lista2, -8, 0);
    inserirLDE(lista2, -3, 2);
    mostrarLDE(lista2, "1o Polinomio sub");
    inserirLDE(lista3, -3, 2);
    inserirLDE(lista3, 8, 1);
    inserirLDE(lista3, -6, 0);
    mostrarLDE(lista3, "2o Polinomio sub");
    listaSUB = subPolinomios(lista2, lista3);
    mostrarLDE(listaSUB, "Resultado subtraído");
    cout << endl;


    return 0;
}
