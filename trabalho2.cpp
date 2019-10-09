 #include <iostream>
 #include <new>
 using namespace std;

 struct SimulAloc{
    struct Noh{
        int ini, tam; Noh* prox;
    };
    Noh *prim;
    bool inicializar(int ini,int tam){
        Noh *n = new(nothrow)Noh;
        if(n==nullptr){
            return true;
        }
        n->ini = ini;
        n->tam = tam;
        n->prox = nullptr;
        prim=n;
        return false; 
    }
int alocar(int tam) {
    Noh *i = prim;
    while (i != nullptr) {
      if ((*i).tam > tam) {
        cout << "Entrou aqui 1!\n";
        int ini = ((*i).ini + (*i).tam) - tam;
        (*i).tam -= tam;
        return ini;
      }

      if ((*i).tam == tam) {
        int ini = (*i).ini;
        (*i).tam = 0;
        delete i;
        Noh *j = prim;
        while(j != nullptr) {
          Noh *pr = (*j).prox;
          if (pr != nullptr) {
            if ((*pr).ini == 0) {
              (*j).prox = (*pr).prox;
              delete pr;
            }
          }

          j = (*j).prox;
        }
        return ini;
      }

      i = (*i).prox;
    }




    return -1;
  }
    int desalocar(int ini,int tam){
        if(prim->ini + prim->tam == ini){    
            prim->tam += tam;
            if(prim->prox != nullptr){
                Noh *n = prim->prox;
                if(n->ini == prim->ini+prim->tam){
                    prim->tam += n->tam;
                    prim->prox = n->prox;
                    delete n;
                }
            }
        return false;
        }
        else if(prim->prox!=nullptr){
            Noh *p = prim->prox;
            if(prim->ini+prim->tam < ini && p->ini > ini) {
                if(ini != p->ini - tam){
                            Noh *n = new(nothrow) Noh;
                            if(n==nullptr){
                                return true;
                            }
                            n->ini = ini;
                            n->tam = tam;
                            n->prox = prim->prox;
                            prim->prox = n; 
                            return false;
                        }

                p->ini = ini; 
                p->tam += tam;
                return false;
            }
            
            do {               
                if(p->ini + p->tam == ini){    
                    p->tam += tam;
                    if(p->prox != nullptr){
                        Noh *n = p->prox;
                        if(n->ini == p->ini+p->tam){
                            p->tam += n->tam;
                            p->prox = n->prox;
                            delete n;
                        }
                    }
                }
                p = p->prox;
            } while (p != nullptr);
        return false;
        }
        Noh *n = new(nothrow) Noh;
        if(n == nullptr) return true;
        n->ini = ini;
        n->tam = tam;
        n->prox = nullptr;
        prim->prox = n;
        return false;
    }
    void terminar(){
        while(prim->prox != nullptr){
            Noh *n = prim->prox;
            prim->prox = n->prox;
            delete n;
        }
    }
    void print(){
        Noh *n = prim;
        do{
            cout<< n->ini << "," << n->tam <<"\n"; 
            n = n->prox;
        }while(n!= nullptr);
    }
};
int main(){
    SimulAloc s;
  s.inicializar(858, 150);
  s.print();
  s.alocar(60);
  s.print();
  
  s.alocar(23);
  s.print();
 
  s.desalocar(925, 23);
  s.print();

  s.alocar(44);
  s.print();

  s.desalocar(904,44);
  s.print();
  s.alocar(79);
  s.print();

  s.alocar(8);
  s.print();


  s.alocar(3);
  s.print();

  s.terminar();

}