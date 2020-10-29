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
    //string palabras;
    char nomArchivo[100];
    //string nomArchivo;

} Index;

int main()
{
    int i = 1;
    multimap<string, string> mmIndexParaArchivo;

    //mmapOfPos.insert(std::pair<char, int>('t', 9));
    mmIndexParaArchivo.insert(std::pair<string,string>("hola", "texto1.txt"));
    mmIndexParaArchivo.insert(std::pair<string,string>("como", "texto2.txt"));
    mmIndexParaArchivo.insert(std::pair<string,string>("andas", "texto3.txt"));
    mmIndexParaArchivo.insert(std::pair<string,string>("que", "texto1.txt"));

    ofstream file("archiBin.dat", std::ios::binary|std::ios::ate);
    if (file.is_open()){

        multimap<std::string, std::string>::iterator it;
        for(it = mmIndexParaArchivo.begin(); it !=mmIndexParaArchivo.end(); ++it){
            Index I;
            I.indice = i;
            //I.palabras = it->first;
            strcpy(I.palabras, it->first.c_str());
            strcpy(I.nomArchivo, it->second.c_str());
            //cout << I.indice << " " << I.palabras << " " << I.nomArchivo << endl;

            file.write((char*)&I,sizeof(I));
            i++;
        }
    }

    file.close();


    ifstream file2 ("/home/exequiel/Escritorio/FolderConTextos/index.dat", std::ios::binary);
    Index I;
    if (file2.is_open()){
        while (!file2.eof()) {
            file2.read((char *)&I, sizeof(I));
            if (!file2.eof()){
                cout << "Linea ";
                cout << I.indice << " " << I.palabras << " " << I.nomArchivo << endl;
            }
        }
    }
    file2.close();


    return 0;
}
