//funciones matemaicas.h
//header file
#include<iostream>
#include <string>

using namespace std;
//Dayevska Anabel Caceres Budiel


void eu_extendido(int a, int b, int rpta[3]){ //la respuesta esta en (rold_r, (old_s,old_t))
	int  s = 0, old_s = 1, t = 1, old_t = 0, r = b, old_r = a,  p,q;
    while(r != 0){
        q = old_r / r;
        p = r;
        r = old_r-q*r;
        old_r = p;
        p = s;
        s = old_s-q*s;
        old_s = p;
        p = t;
        t = old_t-q*t;
        old_t = p;
    }
	rpta[0]=old_r;
	rpta[1]=old_s;
	rpta[2]=old_t;
}
int modulo(int a, int b, int &q){
	q= a/b;
	int r= a%b;
	if(a<0){
		int ar=r;
	    q=(a/b)-1;
	    r= b+ar;
	}
	return r;
}

int euclides(int a, int b, int r, int q ){
	if (b<=0) return a; //caso base
	else{
		r= modulo(a,b,q);
	    return (euclides(b,r,r,q));
	}
}

