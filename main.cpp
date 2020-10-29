#include <iostream>
#include <map>
#include <algorithm>
#include <cstring>
#include <fstream>
using namespace std;

typedef struct
{
    int indice;
    char palabras[100];
    char nomArchivo[100];


} Index;

int main()
{
    //LECTURA E INSERCION DE DATOS EN EL MULTIMAP
    std::multimap<std::string, std::string> mmIndexBuffer;
    std::ifstream file ("archivo.dat", std::ios::binary);
    Index I;
    if (file.is_open()){
        while (!file.eof()) {
            file.read((char *)&I, sizeof(I));
            if (!file.eof()){
                string palabra = I.palabras;
                string nomArchivo = I.nomArchivo;
                
                //agregamos lo del archivo en el multimap
                mmIndexBuffer.insert(std::pair<std::string, std::string>(palabra, nomArchivo)); 
            }
        }
    }
    file.close();

    //ESCRITURA DE DATOS EN EL ARCHIVO BINARIO ITERANDO UN MULTIMAP
    std::multimap<string, string> MM; //el multimap debe estar cargado con <string, string> en este caso
 
    int i = 1;
    std::ofstream file ("archivo.dat", std::ios::binary|std::ios::ate);
    if (file.is_open()){

        std::multimap<std::string, std::string>::iterator it;
        for(it = MM.begin(); it != MM.end(); ++it){
            Index I;
            
            I.indice = i;
            strcpy(I.palabras, it->first.c_str()); // it->first es string por eso se agrega .c_str()
            strcpy(I.nomArchivo, it->second.c_str());// it->second es string por eso se agrega .c_str()

            file.write((char*)&I,sizeof(I));
            i++;
        }
    }

    file.close();
    
    //La salida del archivo será
    // 1 string string

    return 0;
}
