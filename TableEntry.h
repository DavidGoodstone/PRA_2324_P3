#ifndef TABLEENTRY_H
#define TABLEENTRY_H

#include <string>
#include <ostream>

template <typename V> 
class TableEntry{
    public:
	//Miembros públicos
        std::string key;
        V value;
        
        //Contructor con clave y valor
        TableEntry(std::string key, V value){
        	this->key = key;
        	this->value = value;
        }
        
	//Contructor con clave y sin valor
        TableEntry(std::string key){
        	this->key = key;
        }
        
      	//Contructor sin clave y sin valor
        TableEntry(){
        	key = "";
        }
        
        //Sobrecarga global del operador == para determinar que dos instancias de TableEntry son iguales solo si comparten la misma clave (con independencia del valor)
        friend bool operator == (const TableEntry<V> &te1, const TableEntry<V> &te2){
        	return te1.key == te2.key;	
        }
        
        //Sobrecarga global del operador != para determinar que dos instancias de TableEntry son diferentes solo si sus claves son distintas (con independencia del valor)
        friend bool operator != (const TableEntry<V> &te1, const TableEntry<V> &te2){
        	return te1.key != te2.key;
        }
        
        //Sobrecarga global del operador << para imprimir el contenido de la entrada (par clave->valor) por pantalla
        friend std::ostream& operator << (std::ostream &out, const TableEntry<V> &te){
        	out << "Key: " << te.key << ", Value: " << te.value;
       	return out;
        }
        
		//SBTreeDict.h
		friend bool operator<(const TableEntry<V> &te1, const TableEntry<V> &te2){
			return te1.key < te2.key;
		}
		
		friend bool operator>(const TableEntry<V> &te1, const TableEntry<V> &te2){
			return te1.key > te2.key;
		}
};

#endif
