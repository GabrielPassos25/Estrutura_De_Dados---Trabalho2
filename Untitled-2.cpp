#include <new>
#include <iostream>

using std::cout;
using std::nothrow;

struct SimulAloc
{
    struct Noh
    {
        int ini, tam; Noh *prox;
    };
    Noh *prim;

    bool inicializar(int ini, int tam){
        Noh *n = new(nothrow) Noh;
        if(n==nullptr) return true;
        (*n).ini = ini; (*n).tam = tam; (*n).prox = nullptr;
        prim = n;
        return false;
    }

    int alocar(int tam){
        int ini;   
        if(tam<=(*prim).tam){
            (*prim).tam -= tam;
            ini = (*prim).ini + (*prim).tam;
            if((*prim).tam == 0) prim = (*prim).prox; 
            return ini;
        } else {
            Noh *n = prim;
            do
            {
                n = (*n).prox;
                if(tam<=(*n).tam){
                    (*n).tam -= tam;
                    ini = (*n).ini + (*n).tam;
                    if((*n).tam == 0) delete n; 
                    return ini;
                }
            } while ((*n).prox != nullptr);
        }
        return -1;
    }

    bool desalocar(int ini, int tam){
        if((*prim).ini + (*prim).tam == ini){    
            (*prim).tam += tam;
            if((*prim).prox != nullptr){
                Noh *n = (*prim).prox;
                if((*n).ini == (*prim).ini+(*prim).tam){
                    (*prim).tam += (*n).tam; (*prim).prox = (*n).prox;
                    delete n;
                }
            }
            return false;

        } else if((*prim).prox!=nullptr){
            Noh *p = (*prim).prox;
            if((*prim).ini+(*prim).tam < ini && (*p).ini > ini) {
                Noh *h = (*prim).prox;
                (*h).ini = ini; 
                (*h).tam += tam;
                return false;
            }
            
            do {               
                if((*p).ini + (*p).tam == ini){    
                    (*p).tam += tam;
                    if((*p).prox != nullptr){
                        Noh *n = (*p).prox;
                        if((*n).ini == (*p).ini+(*p).tam){
                            (*p).tam += (*n).tam; (*p).prox = (*n).prox;
                            delete n;
                        }
                    }
                }
                p = (*p).prox;
            } while ((*p).prox != nullptr);
        return false;
        }
        Noh *n = new(nothrow) Noh;
        if(n == nullptr) return true;
        (*n).ini = ini; (*n).tam = tam;
        (*n).prox = nullptr; (*prim).prox = n;
        return false;
    }

    void terminar(){
        while((*prim).prox != nullptr){
            Noh *n = (*prim).prox;
            (*prim).prox = (*n).prox;
            delete n;
        }
    }
};