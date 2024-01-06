#ifndef BSTREEDICT_H
#define BSTREEDICT_H
#include <ostream>
#include <stdexcept>
#include "Dict.h"
#include "BSTree.h"
#include "TableEntry.h"

template <typename V>
class BSTreeDict: public Dict<V> {

    private:
        //ABB con elementos de tipo TableEntry<V> para gestionar los elementos de un diccionario
        BSTree<TableEntry<V>>* tree;

    public:
        //Constructor. Crea un ABB vacío con memoria dinámica
        BSTreeDict(){
        	this->tree = new BSTree<TableEntry<V>>();
        }
        
        //Método destructor. Se encargará de liberar la memoria dinámica ocupada por el ABB tree
        ~BSTreeDict(){
        	delete tree;
        }
        
        	//Métodos públicos abstractos heredados de la interfaz Dict.h
        	void insert(std::string key, V value) override{
			TableEntry<V> *aux = new TableEntry<V>(key, value);  //Genera un elemento aux de tipo V
			
			tree->insert(*aux);  //Llamada al método público insert de BSTree.h para que en el método privado de insert introduzca dicho nodo
			
			delete aux;  //Eliminamos el elemento auxiliar
		}
		
		V search(std::string key) override{
			return (tree->search(key)).value;  //Llamada al método público search de BSTree.h para que en el método privado de search devuelva el valor dicho nodo
		}
		
		V remove(std::string key) override{
			V valor = search(key);  //Llamada al método público search de BSTree.h para que en el método privado de search devuelva el valor dicho nodo
			
			tree->remove(key);  //Llamada al método público remove de BSTree.h para que en el método privado de remove elimine dicho nodo
		       
			return valor;  //Devuelve el valor del nodo eliminado
		}
		
		int entries() override{
			return tree->size();  //Llamada al método público size de BSTree.h para que devuelva el número de elementos del ABB
		}
        
        //Sobrecarga global del operador << para imprimir el contenido del Diccionario por pantalla
        friend std::ostream& operator<<(std::ostream &out, const BSTreeDict<V> &bs){
        	 out << *(bs.tree);
        	 
                return out;
        }
        
        //Sobrecarga del operador[]. Actúa como interfaz al método de interfaz heredado search(std::string key)
        V operator[](std::string key){
        	return search(key);
        }
        
};

#endif
