#include<iostream>
#include <string>

using namespace std;
//Dayevska Anabel Caceres Budiel 
//el-mensaje-debe-ser-ingresado-sin-espacios-vacios 
class persona{
	public:
		int f,c;
	    string mEncrip="", mDes="", mensaje;
	//contructor
	persona(){
		cout << "Fila: "; cin >> f; 
		cout << "Columna: "; cin >> c; 
		cout << "Mensaje: "; cin>> mensaje; cout << endl;
	}
	//funciones
	void encriptar(){ //el emisor
		int P =0, k=0;
        while (P<c){
            for ( int i=0; i<f ; i++){
                mEncrip += mensaje[k];
                k=k+ c;
            }
            P++ ;
            k=P;
	    }
	}
	void desencriptar(){ // el receptor
		int P =0, k=0;
	    while (P<f){
    	    for ( int i=0; i<c; i++){
        	    mDes+= mEncrip [k];
            	k=k+ f;
        	}
    	    P++ ;
    	    k=P;
		}
	}
};

int main() {
	
	persona emisor;
	emisor.encriptar();
	emisor.desencriptar();
	cout << "Mensaje Encriptado: " << emisor.mEncrip << endl;
	cout << "Mensaje Desencriptado: " << emisor.mDes << endl;
	
	return 0;
}
