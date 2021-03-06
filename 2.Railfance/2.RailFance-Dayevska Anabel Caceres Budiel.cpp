#include<iostream>
#include <string>

using namespace std;
//Dayevska Anabel Caceres Budiel 
//el-mensaje-debe-ser-ingresado-sin-espacios-vacios 
class persona{
	public:
		int f, count=0, countdes=0;//count sera el tama?o del msj, countdes el tama?o del msj des encriptado 
	    string em="", md="", msj;
	//contructor
	persona(){
		cout << "Clave: "; cin >> f; 
		cout << "Mensaje: "; cin>> msj; cout << endl;
	}
	//funciones
	void encriptar(){ 
        int  ks, kb, i=0, P=0;
        while (P<f){
            ks=(2*(f-(P+2)))+2;
            kb=(2*(P-1))+2;
            if (P==0){ //solo subida ya que no puede bajar
                while (i<msj.size()){
            	    count++; em+=msj[i];
                    i+= ks;
               }  
            }
            if (P==f-1){ // solo bajada porque no puede subir 
                while (i<msj.size()){
            	    count++; em+=msj[i];
                    i+= kb;
               } 
            }
            else{ //subida, bajada, subida, bajad?
                while (i<msj.size()){
            	    count++; em+=msj[i];
                    i+= ks;
                    if(i>=msj.size()){break;}
                	count++; em+=msj[i];
                    i+= kb;
                }     
            }
            P++;
            i=P;
        }
	}
	
	void desencriptar(){ 
	    int M=1,less=1,P=0,i=0,indi=0,n=0,ks,kb;
        int memory[f];
        while (P<f){//obtengo la memoria de los indices principales y concateno los primerlos indices
            ks=(2*(f-(P+2)))+2;
            kb=(2*(P-1))+2;   
            if (P==0){ 
                while (i<msj.size()){//recorro todo el mensaje con el proposito de hallar cuantas veces hay una subida en el caso de estar en la fila 0
                    i+= ks;
                    n++;
                }  
            }
		    if (P==f-1){//recorro todo el mensaje con el proposito de hallar cuantas veces hay una bajada en el caso de estar en la ultima fila
                while (i<msj.size()){
                    i+= kb;
                    n++;
                } 
            }
            else{//recorro todo el mensaje con el proposito de hallar cuantas veces hay subida y bajada 
                while (i<msj.size()){
                    i+= ks;
                    n++;
                    if (i<msj.size()){//si exedo el tama?o del mensaje me dentendo 
                        i+= kb;
                        n++;
                    }
                } 
            }
            memory[P]=indi;//almaceno la pocision de los indices principales
            md+=em[indi];
            countdes++;// sumo para saber el tama?o del msj desencripatdo para usarlo como metodo de parada (while) mas adelante
            indi+=n;
            n=0;
            P++;
            i=P;
        }
        for (int i=f-2; i>=0; i--){ //derecha a izquierda(<=) la 1ra vez que se recorre el ultimo indice no nesecita restarse
            indi= memory[i]+M;
            md+=em[indi];
            countdes++;
        }
        M++;
		while(countdes<count){//en un inico intente con"while(em.size()!=msj.size())" pero no acepta operaciones logicas con tama?os de strings, por eso anteriormente sume sus tama?os en variable independientes 
            for (int i=1; i<f; i++){ //izquierda a derecha(=>)
                if(countdes>=count){break; }
                if(i==f-1){  indi= memory[i]+M-less;}
                else{   indi= memory[i]+M;}
                countdes++; md+=em[indi];
            }
            if(countdes>=count){break; }
            M++;
            for (int i=f-2; i>=0; i--){ //derecha a izquierda(<=)
                if(countdes>=count){ break; }
                if(i==0){  indi= memory[i]+M-less;}
                else{   indi= memory[i]+M;}          
                countdes++; md+=em[indi];
            }
            M++;less++;
        }
	}
};

int main() {
    persona emisor;
	emisor.encriptar();
	emisor.desencriptar();
	cout << "Mensaje Encriptado: " << emisor.em << endl;
	cout << "Mensaje Desencriptado: " << emisor.md << endl; 
}
