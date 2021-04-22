#include<iostream>
#include <string>
using namespace std;
//Dayevska Anabel Caceres Budiel
 
int const indice_abc=26;//53, 26original

//Salida, dependiendo del caso, el texto cifrado o el texto descifrado.

int fun(int a, int b){
	int r=a%b, q=a/b;
	if(r<0){ // 0 <= r < b
		int ar=r;
	    q=(a/b)-1;
	    r= b+ar;
	}
	return r;
}
class emisor{ //objeto emisor (encriptador )
	public:
	    int key; 
	    string msj;
		
	//contructor
	emisor(){
		cout << "Ingrese el mensaje: "; getline(cin,msj); 
		cout << "Ingrese clave: "; cin >> key; 
	}
	
	void encriptado(string abc, string msj, string &me){
		int indi;
		for (int i=0; i<msj.size(); i++){
			indi= (abc.find(msj[i])) + key;
		    if (indi>=abc.size()) indi= fun(indi, abc.size());
		    me+=abc[indi];
		}
	}

};
class receptor{// receptor (des encriptador)
	public:
	void desencriptado(string abc, string me, string &md, int key){
		int indi2;
		for (int i=0; i<me.size(); i++){
			indi2= (abc.find(me[i])) - key;
			if (indi2<0) indi2= fun(indi2, abc.size()); 
			md+=abc[indi2];
		}
	}

};

float findChars(string &me, char l){
	float num=0.0;
    for (int i=0; i<me.size();i++){
    	if (me[i]==l) {
    		num= num+1.0;
    		me[i]='�';
		}
    }
    return num;
}
void ordenar(float A[indice_abc], int indi_fre){
	int min=0, max=indi_fre-1, f_sw=0;//1=si hubo cambios, 0 no hay cambios entonces ya esta ordenada
    float temp;
	while(max>min){
		for (int piv=min; piv<max; piv++){//=>
		    if(A[piv]<A[piv+1]){
		    	temp= A[piv];
		    	A[piv] = A[piv+1];
		    	A[piv+1]= temp;
		    	f_sw=1;
			}
		}
		for (int piv=max; piv>min; piv--){//<=
		    if(A[piv]>A[piv-1]){
		    	temp= A[piv];
		    	A[piv] = A[piv-1];
		    	A[piv-1]= temp;
		    	f_sw=1;
			}
		}
		if (f_sw==0 ){break;}
		min++; max--;
	}
}
int findfloat(float frec_me[indice_abc] , float l, int indi_fre){//devuelve el indice 
    for (int i=0; i<indi_fre ;i++){
    	if (frec_me[i]==l) {frec_me[i]=0.0; return i;}
    }
}
bool lis_keys(int key[100], int l, int tam){
	for (int i=0; i<tam; i++){
		if (key[i]== l) return 0;// ya use esa clave, no la uses otra vez
	}
	return 1;//no la has usado, puedes usarla
}

void find_clave ( string abc,string me, float frecuencia[indice_abc], float frecuencia_ordenada[indice_abc] ){
	string me_contado, copy_me(me),pos_md;
    float frec_me[indice_abc], frec_me_ordenadas[indice_abc], copy_frec_me_des[indice_abc];
	int indi_fre=0, index_Frec, index_Frec_abc, i_char, i_abc, pos_key, key_usadas[100], indice_key=0;
    char frec_char, frec_abc;
    receptor persona;
    
	//hallo las frecuencia de las letras del msj encriptado
	for (int i=0; i<me.size();i++){
        if (copy_me[i]=='�') { ;  }
        else{
        	frec_me[indi_fre] = findChars(copy_me,copy_me[i]) / abc.size();
            indi_fre++;
            me_contado+=me[i]; 
		}
	}
	
	//hago copia de las frecuencias del mensaje y las ordendo de mayor a menor 
	for (int i=0; i<abc.size();i++){ frec_me_ordenadas[i]= frec_me[i]; }
	ordenar(frec_me_ordenadas,indi_fre);

    for (int j=0; j<indi_fre; j++){
	    // se hace copia de las frecuencias desordeandas para volver a intentarlo despues 
	    for (int i=0; i<abc.size();i++){  copy_frec_me_des[i]= frec_me[i]; }
	    
	    //devuelve los indices en el abecedario donde estan las letras con mayor frecuencia
    	index_Frec_abc= findfloat( frecuencia, frecuencia_ordenada[j],  indice_abc);
    	i_abc= abc.find(abc[index_Frec_abc]);
    
	    //las mayores frecuenciaa del abecedario se prueban con la mitad de las frecuencias del msj encriptado que tiene mayor probabilidad
        for (int i=0; i<5; i++){
		    index_Frec= findfloat( copy_frec_me_des, frec_me_ordenadas[i],  indi_fre);
    	    i_char= abc.find(me_contado[index_Frec]);
    	
    	    //ve la diferencia y prueba con esa clave
    	    i_char= abc.find(me_contado[index_Frec]);
    	    pos_key= i_abc- i_char;
    	    if (pos_key<0) pos_key= -pos_key;
    	    //si es que ya use esa clave ya no la vuelvo a usar
    	    if ( lis_keys( key_usadas, pos_key, indice_key) ){
    	    	persona.desencriptado(abc, me, pos_md, pos_key);
    	    	cout << "Posible calve: "<< pos_key<<endl;
	        	cout<<"Posible mensaje desencriptado: " << pos_md<< endl;
			}
	        
		    //limpio el mensaje para que al volver a probar con la proxima posible clave no se concatenara con el msj anterior 
	        pos_md.erase(0);
	        
	        //pongo las posibles claves porque si vuelve a salir la clave no se desperdicie tiepo y recursos volviendo a desencriptar con la misma clave
	        key_usadas[indice_key]= pos_key;
	        indice_key++;
	        if (indice_key==100){break;} //cantidad maxima de intentos con claves es 100
		}
    	if (indice_key==100){break;}
	}
	
}

void frec_abc_cualquiera(string abc_x, float frec_abc_guia[indice_abc], string abc, float frecuencia_guia[26]){
	int auX;
	//de un abecedario cualqiera busco las letras del abecedario espa�ol y pongo sus frecuencias
	for (int i=0; i<26;i++ ){
		auX = abc_x.find(abc[i]);
		if (auX>0){
			frec_abc_guia[auX]= frecuencia_guia[auX];
		}
	}
	//las letras o simbolos que no esten en mi abecedario espa�ol las relleno con 0.0 
	for (int i=0; i<indice_abc;i++ ){  if ( frec_abc_guia[i] <0.01){ frec_abc_guia[i]= 0.0; }	}
}

int main(){    
	string abc("abcdefghijklmnopqrstuvwxyz "); //size 26 letras abc 
	float frecuencia_ordenada[26]={14.13,9.57,9.19,8.94,7.82,6.17,5.58,5.39,4.86,4.51,3.77,3.18,3.12,2.43,1.86,1.73,1.08,1.07,0.94,0.8,0.64,0.41,0.18,0.17,0.03,0.01};	
    float frecuencia_guia[26]=    {14.13,1.86,5.58,3.77,9.57,1.07,1.73,1.08,7.82,0.64,0.03,4.86,3.18,6.17,8.94,2.43,0.41,9.19,4.51,5.39,3.12,0.94,0.01,0.17,0.18,0.80};
    //                               a    b    c    d    e    f    g    h    i    j    k    l    m    n    o    p    q    r    s    t    u    v    w    x    y    z 
	
    cout <<"no se olvide de cambiar (indice_abc), en la linea 6, con el tamanio del abecedario cambiado si usara un abecedario diferente "<<endl;
	//0. des encriptar (por frecuencia) con un abecedario diferente
	//1. des encriptar (por frecuencia) con el abecedario comun 
	//2. des encriptar (con fuerza buta) 
	//3. cifrar o des cifrar con Cesar utilizando una clave

    int decision=1; 
    
    string mEncrip;
    if (decision==0){//frecuencia con un abecedario diferente
        cout << "0. des encriptar (por frecuencia) con un abecedario diferente"<<endl;
		string abc_x("ABCDEFGHIJKLmnopqrstuvwxyz MNOPQRSTUVWXYZabcdefghijkl"); //abecedario cambiado
		float frec_abc_guia[indice_abc];
		cout <<"Ingrese mensaje cifrado: "; getline(cin,mEncrip);
	    frec_abc_cualquiera( abc_x, frec_abc_guia,  abc, frecuencia_guia );
		find_clave( abc_x, mEncrip, frec_abc_guia, frecuencia_ordenada);
    } 
    
    if (decision==1){//frecuencia con un abecedario comun
        cout <<"1. des encriptar (por frecuencia) con el abecedario comu"<<endl;
        cout <<"Ingrese mensaje cifrado: "; getline(cin,mEncrip);
    	find_clave( abc, mEncrip, frecuencia_guia, frecuencia_ordenada);
	}
	
	if (decision==2){ //des encriptar (con fuerza buta). Prueba todas las claves posibles, no es muy efectivo ya que se gasta tiempo y recursos sin necesidad  
		cout <<"2. des encriptar (con fuerza buta) "<<endl;
		string  md;
	    receptor persona2;
	    cout <<"Ingrese mensaje cifrado: "; getline(cin,mEncrip);
		for (int i=0; i<abc.size(); i++){
			persona2.desencriptado(abc, mEncrip, md, i);
			cout<<"Posible clave: " << i<< endl;
			cout<<"Posible mensaje desencriptado: " << md<< endl;
    	    md.erase(0);
		}
    }
	
	if (decision==3){//cifrar o des cifrar con Cesar utilizando una clave
	    cout<<"cifrar o des cifrar con Cesar utilizando una clave"<<endl;
	    emisor persona3;
	    receptor persona4;
	    string md,m_e;
    	persona3.encriptado(abc, persona3.msj, m_e);
    	persona4.desencriptado(abc, m_e, md, persona3.key);
		cout<<"Mensaje original: " << persona3.msj<< endl;
		cout<<"Mensaje encriptado: " << m_e<< endl;
		cout<<"Mensaje desencriptado: " << md<< endl;
    }
    
	return 0;
}
