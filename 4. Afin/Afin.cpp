#include<iostream>
#include <string>
#include <stdlib.h>
#include <time.h>

#include"funciones matematicas.h"
using namespace std;
//Dayevska Anabel Caceres Budiel

string abc("abcdefghijklmnopqrstuvwxyz "); //ABCDEFGHIJKLMNOPQRSTUVWXYZ

int genera_a(){
	int a, aux_a ;
    srand((unsigned)time(NULL));
    a=rand()%abc.size()+0;
    aux_a = euclides(a,abc.size(),0,0);
    while (aux_a != 1){
        a=rand()%abc.size()+0;
        aux_a = euclides(a,abc.size(),0,0);
	}//si aux_1 ==1  "a" es primo relativo con el tamaño del abecedario 
	return a;
}

int inversa_a(int A){
	int rpta[3],x, q;
    eu_extendido(A, abc.size() , rpta);
    x= rpta[1];
    if (x<0  or   x>=abc.size()){ x=modulo(x,abc.size(),q);	}
    return x;
}
class emisor{
	private:
		int key_a,key_b;
	public:
		emisor(){
		    srand((unsigned)time(NULL));
		    key_a=genera_a() , key_b=rand()%abc.size()+0 ;
	    }
	    int get_key_a(){ return key_a;}
	    int get_key_b(){ return key_b;}
	    
	    string encriptado( string msj){
	    	string me;
	    	int indi, index,q;
	    	for (int i=0; i<msj.size(); i++){
	    		index= abc.find(msj[i]);
			    indi=  key_a*index;
			    if (indi<0 or indi>=abc.size() ) indi= modulo(indi, abc.size(),q);
			    indi= indi +key_b ;
			    if (indi<0   or   indi>=abc.size()) indi= modulo(indi, abc.size(),q);
			    me+=abc[indi];
		    }
		    return me;
	    }
};
class receptor{
	private: 
	    int key_a, key_b;
	public:
		receptor(int e_key_a, int e_key_b){
			key_b= e_key_b;
			key_a= inversa_a(e_key_a);
		}
	    int get_key_a(){ return key_a;}
	    int get_key_b(){ return key_b;}
	    
	    string desencriptado( string m_encriptado){
	    	string m_des;
	    	int indi, index,q;
	    	for (int i=0; i<m_encriptado.size(); i++){
	    		index= abc.find(m_encriptado[i]);
			    indi=  (index-key_b) ;
			    if (indi<0   or   indi>=abc.size()) indi= modulo(indi, abc.size(),q);
			    indi = indi *key_a ;
			    if (indi<0   or   indi>=abc.size()) indi= modulo(indi, abc.size(),q);
			    m_des+=abc[indi];
		    }
		    return m_des;
	    }
};




int main(){

	emisor E;
	int clave_a_E=E.get_key_a() , clave_b_E=E.get_key_b() ; // obtengo las clavez privadas que hiso el emisor 
	receptor R(clave_a_E, clave_b_E);
	
	string msj_enc;
	msj_enc = E.encriptado("como se llaman todos ustedes");
	
	cout << "encriptado: "<<msj_enc<<endl;
	cout << "desencriptado: "<< R.desencriptado(msj_enc) <<endl;  
   
	return 0;
	
}
