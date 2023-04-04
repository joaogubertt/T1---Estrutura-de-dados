#include <iostream>
#include <locale.h>
#include <conio.h>
#include <string.h>

using namespace std;

struct No{
    int e;
    float k;
    No *eloA, *eloP;
};

struct LDE{
    No *comeco, *fim;
};

void inicializarLDE(LDE &lista){
    lista.comeco = NULL;
    lista.fim = NULL;
}

// A vari�vel sentido pode ser C(crescente) ou D(decrescente)
void mostrarLDE(LDE lista, char frase[]){
    cout << frase << ": ";
    if( lista.comeco == NULL ) cout << " vazia";

    No *aux = lista.fim;
    while( aux != NULL ){

        if(aux->e == 0) cout << aux->k << " ";
        else if(aux->e == 1) cout << aux-> k << "x ";
        else cout << aux->k << "x^" << aux->e << " ";

        aux = aux->eloA;
    }
    cout << endl;
}

bool inserirLDE( LDE &lista, float constante, int expoente){
    No *novo = new No;

    if( novo == NULL ) return false;
    novo->e = expoente;
    novo->k = constante;
    novo->eloA = NULL;
    novo->eloP = NULL;

    // Inserir em lista vazia
    if( lista.comeco == NULL ){
        lista.comeco = novo;
        lista.fim = novo;
        return true;
    }

    // Inserir no inicio da lista
    if( novo->e < lista.comeco->e ){
        novo->eloP = lista.comeco;
        lista.comeco->eloA = novo;
        lista.comeco = novo;
        return true;
    }

    // Inserir no final da lista
    if( novo->e > lista.fim->e ){
        lista.fim->eloP = novo;
        novo->eloA = lista.fim;
        lista.fim = novo;
        return true;
    }

    // Inserir no meio da lista
    No *aux = lista.comeco;
    while( aux->e < expoente && aux->eloP->e < expoente )
        aux = aux->eloP;
    novo->eloP = aux->eloP;
    novo->eloA = aux;
    aux->eloP->eloA = novo;
    aux->eloP = novo;
    return true;
}

No *buscarLDE( LDE lista, int expoente ){
    No *aux = lista.comeco;
    while( aux != NULL ){
        if( aux->e == expoente ) return aux;
        aux = aux->eloP;
    }
    return NULL;
}

bool retirarLDE( LDE &lista, int expoente ){
    No *pos;

    pos = buscarLDE(lista, expoente);
    if( pos == NULL ) return false;  // Lista vazia ou valor n�o encontrado

    // Retirada no inicio da lista
    if( pos == lista.comeco ){
        No *prox = pos->eloP; // Pega o pr�ximo n�
        lista.comeco = prox;
        if( prox != NULL ) prox->eloA = NULL;
        if( pos == lista.fim ) lista.fim = NULL;
    }
    else{
        No *ant = pos->eloA; // Pega o n� anterior
        No *prox = pos->eloP; // Pega o n� seguinte
        if( ant != NULL ) ant->eloP = prox;
        if( prox != NULL ) prox->eloA = ant;
        if( pos == lista.fim ) lista.fim = ant;
    }
    delete( pos );
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

void lerPolinomios(LDE &lista) // Função que irá receber os valores da constante e do expoente e armazenará em uma LDE
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
    tecla = getch();
    cont++;
    } while(tecla != 27); cout << cont;
}

bool realizarOperacaoSoma(LDE lista, LDE& resultado)
{
    inicializarLDE(resultado);
    No* aux = lista.comeco;
    while (aux != NULL) {
        if (buscarLDE(lista, aux->e) != NULL) {
            No* aux1 = new No;
            if (aux1 == NULL) return false;
            aux1->e = aux->e;
            aux1->k = 0;
            No* aux2 = buscarLDE(lista, aux->e);
            while (aux2 != NULL) {
                aux1->k += soma(aux2->k, aux2->eloP->k);
                aux2 = aux2->eloP->eloP; // atualiza o ponteiro para o próximo nó com o mesmo expoente
            }
            inserirLDE(resultado, aux1->k, aux1->e);
            delete aux1;
        }
        aux = aux->eloP; // atualiza o ponteiro para o próximo nó fora do loop interno
    }
    return true;
}

int main(){
    setlocale(LC_ALL, "Portuguese");

    LDE lista1, listaOP;
    inicializarLDE(lista1);
    //lerPolinomios(lista1); 
    inserirLDE(lista1, 2, 4);
    inserirLDE(lista1, 2, 3);
    inserirLDE(lista1, 2, 6);
    inserirLDE(lista1, 3, 2);
    inserirLDE(lista1, 4, 2);
    inserirLDE(lista1, 2, 4);
    realizarOperacaoSoma(lista1, listaOP);
    mostrarLDE(lista1, "Polinomio");
    mostrarLDE(listaOP, "Polinomios Soma");
    return 0;
}
