#include <iostream>
#include <locale.h>
#include <conio.h>

using namespace std;

struct No{
    int e, k;
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

bool inserirLDE( LDE &lista, int constante, int expoente){
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

//Confere o expoente a partir do segundo item 
bool conferirExpoente( LDE lista, int expoente ){
    No *aux = lista.comeco->eloP;
    while( aux != NULL ){
        if( aux->e == expoente ) return true;
        aux = aux->eloP;
    }
    return false;
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

No *soma (int e1, int e2, int k1, int k2)
{
    //Verificação de expoente necessita ser enquanto se percorre a lista
    No* aux = new No;
    if(aux = NULL) return NULL;
    aux->k = k1 + k2;
    return aux;
}

void lerPolinomios(LDE &lista)
{
    char tecla;
    int k, e, cont;
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


//O problema está aqui - > antes de salvar mudei o tipo de retorno e com isso espero criar uma nova lista onde coloco os resultados.
LDE realizarOperacaoSoma(LDE lista)
{
    No* aux = new No;
    if (aux == NULL)
    {
        return;
    }
    aux = lista.comeco;
    while(aux->eloP != NULL)
    {
       if(conferirExpoente(lista, aux->e))
       {
        aux->eloP = soma(aux->e, aux->eloP->e, aux->k, aux->eloP->k);
        delete(lista.comeco);
        lista.comeco = aux->eloP;
       }
    }

}

int main(){
    setlocale(LC_ALL, "Portuguese");

    LDE lista1;
    inicializarLDE(lista1);
    lerPolinomios(lista1);
    //realizarOperacaoSoma(lista1);
    mostrarLDE(lista1, "Polinomio");

    return 0;
}
