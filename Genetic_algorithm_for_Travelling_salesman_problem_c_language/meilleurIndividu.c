#include "meilleurIndividu.h"


void meilleurIndividu(long* classementDistances, long nbIndividu, long* meilleurIndiv){

    //On stocke l'indice du meilleur individus.
    *meilleurIndiv = *(classementDistances+nbIndividu-1);
}
