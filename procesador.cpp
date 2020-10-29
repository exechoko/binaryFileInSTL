#include "procesador.h"
#include <QDebug>

procesador::procesador()
{

}

std::multimap<int, string> procesador::getMapAlReves()
{
    return (this->mmGr);
}

std::vector<string> procesador::getV()
{
    return this->v;
}

std::vector<string> procesador::getVectorNomArchi()
{
    return this->vectorNombreArchivo;
}

void procesador::clearPorArchivo()
{
    this->v.clear();
    this->mmIndex.clear();
}

void procesador::clearParaIndex()
{
    this->v.clear();
}

void procesador::clearParaBusqueda()
{
    this->mmGr.clear();
}

void procesador::setMapaFiltrado(std::multimap<int, string> mapita)
{
    this->mmGr = mapita;
}


void procesador::leer(std::string nomArchi)
{
    std::ifstream archi;
    archi.open(nomArchi.c_str(), std::ios::in);

    //Guarda cada palabra en el vector v
    copy(std::istream_iterator<std::string>(archi), std::istream_iterator<std::string>(), back_inserter(this->v));

}
//map<vector(string),string> vector de palabras, nombre del archivo
void procesador::indexar(std::vector<std::string> vec, std::string nombreArchivo)
{

    //se inserta el vector v en el multimap mm <key: palabra,valor: nombreArchivo>
    for(size_t i=0; i < vec.size(); ++i){
       this->mmIndex.insert(pair<string,string>(vec[i],nombreArchivo));
    }
}

void procesador::insertarEnMapGrande(int cant, std::string nomArchi)
{
    this->mmGr.insert(std::pair<int,std::string> (cant, nomArchi));
}

void procesador::eliminarPreposiciones()
{
    //abrir archivo de texto que contiene las palabras a eliminar
    //CAMBIAR UBICACIÓN PARA PROBAR
    std::ifstream archiConOcurrencias;
    archiConOcurrencias.open("/home/exequiel/Escritorio/archivoConPreposiciones.txt", std::ios::in);
    std::vector<std::string> vectorConPreposiciones;
    //Guarda cada palabra en el vector v
    copy(std::istream_iterator<std::string>(archiConOcurrencias), std::istream_iterator<std::string>(), back_inserter(vectorConPreposiciones));

    for(int i = 0; i < vectorConPreposiciones.size(); i++){
        this->mmIndex.erase(vectorConPreposiciones[i]);
    }

}

int procesador::cantVecesQueEsta(std::string key)
{
    //cuenta las veces que aparece la key
    return this->mmIndex.count(key);
}

std::multimap<string, string> procesador::getMultimapComplete()
{
    return (this->mmIndex);
}

void procesador::escribirIndex(string nombreArchi, std::multimap<string, string> mmIndexParaArchivo)
{
    std::multimap<string, string> MM = mmIndexParaArchivo;

    //int tamanio = sizeof (Index);
    int i = 1;
    std::ofstream file (nombreArchi, std::ios::binary|std::ios::ate);
    if (file.is_open()){

        std::multimap<std::string, std::string>::iterator it;
        for(it = MM.begin(); it != MM.end(); ++it){
            Index I;
            I.indice = i;
            //I.palabras = it->first;
            strcpy(I.palabras, it->first.c_str());
            strcpy(I.nomArchivo, it->second.c_str());

            file.write((char*)&I,sizeof(I));
            i++;
        }
    }

    file.close();

}

void procesador::leerIndex(std::string nombreArchi)
{
    std::multimap<std::string, std::string> mmIndexBuffer;
    std::ifstream file (nombreArchi, std::ios::binary);
    Index I;
    if (file.is_open()){
        while (!file.eof()) {
            file.read((char *)&I, sizeof(I));
            if (!file.eof()){
                string palabra = I.palabras;
                string nomArchivo = I.nomArchivo;

                mmIndexBuffer.insert(std::pair<std::string, std::string>(palabra, nomArchivo)); //agregamos lo del archivo en el multimap sin filtrar

            }
        }
    }
    file.close();

    this->mmIndex = mmIndexBuffer;

}

void procesador::actualizarIndex(string nombreArchi, std::multimap<string, string> mmIndexParaArchivo)
{
    std::multimap<string, string> MM = mmIndexParaArchivo;
    int i = 1;
    std::ofstream file (nombreArchi);

    if (file.is_open()){

        std::multimap<std::string, std::string>::iterator it;
        for(it = MM.begin(); it != MM.end(); ++it){
            Index I;
            I.indice = i;
            strcpy(I.palabras, it->first.c_str());
            strcpy(I.nomArchivo, it->second.c_str());

            file.write((char*)&I,sizeof(I));
            i++;
        }
    }

    file.close();

}




