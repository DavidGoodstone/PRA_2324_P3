#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <ostream>
#include "Dict.h"
#include "TableEntry.h"

#include "/home/alumno.upv.es/dpiegar/W/PRA/P1/src/ListLinked.h"  //¡¡¡¡MODIFICADO!!!!

template <typename V>
class HashTable: public Dict<V> {

    private:
    	//Número de elementos almacenados actualmente en la tabla hash
        int n;
        
        //Tamaño de la tabla hash (número total de cubetas)
        int max;
        
        //Tabla de cubetas, representada por un array de punteros a listas enlazadas (tipo ListLinked<T>) que almacenan pares clave→valor (tipo TableEntry<V>)
        ListLinked<TableEntry<V>>* table;
        
        //Función hash que devuelve la posición (cubeta) en la tabla hash de key. Se calculará como el resto de la divisón entre la suma de los valores ASCII numéricos de los caracteres de la clave y el 	  		  tamaño de la tabla hash
        int h(std::string key){
        	
        //Opción 1 (letras)
        	int sum = -(int)'0'* key.length();
        	
 		for (char c : key) {
   			sum += (int)c;
   		}
   		
   		int res = sum % max;
   		
 		return res;
 		
 	/*Opción 2 (números)
 		int factor = key.length();
 		
 		int sum = 0;
 		
 		for(char c : key){
 			sum = (sum * factor + c) % max;
 		}
 		
 		return sum;
 	*/
 		
        }

    public:
    		//Dict.h
    		
    		//Inserta el par key->value en el diccionario. Si key ya existe en el diccionario, lanza una excepción std::runtime_error
		void insert(std::string key, V value) override {
			int index = h(key);  //Defino la posición en el vector table con el método hash
			TableEntry<V> entradaI(key, value);
			int result = table[index].search(entradaI);  //Busco si existe la clave (entrada) en la posición (index)

	   		if (result >= 0) {
       			throw std::runtime_error("Ya existe una clave.");
   			} else {
       			table[index].prepend(entradaI);
   			}
		}

		//Busca el valor correspondiente a key. Devuelve el valor value asociado si key está en el diccionario. Si no se encuentra, lanza una excepción std::runtime_error
		V search(const std::string key) override {
		      	int index = h(key);  //Defino la posición en el vector table con el método hash
			TableEntry<V> entradaS(key);
   			int result = table[index].search(entradaS);  //Busco si existe la clave (entrada) en la posición (index)

   			if (result >= 0) {
       			return table[index].get(result).value;
   			} else {
       			throw std::runtime_error("Clave no encontrada.");
   			}
		}

		//Elimina el par key->value si se encuentra en el diccionario. Si no se encuentra, lanza una excepción std::runtime_error
		V remove(const std::string key) override {
		      	int index = h(key);  //Defino la posición en el vector table con el método hash
		      	TableEntry<V> entradaR(key);  //Creo el nodo con el valor key pasado con el método hash
   			int result = table[index].search(entradaR);  //Busco si existe la clave (entrada) en la posición (index)

   			if (result >= 0) {
       			n--;
       			return table[index].remove(result).value;
   			} else {
       			throw std::runtime_error("Clave no encontrada.");
   			}
		}

		//Devuelve el número de elementos que tiene el Diccionario
		int entries() override {			
			return n;
		}
    
    	//Método constructor que eservará memoria dinámica para crear una tabla table de tamaño size, e inicializará los atributos n y max de la clase
        HashTable(int size){
        	table = new ListLinked<TableEntry<V>>[size];
        	n = 0;
        	max = size;
        }
        
        //Método destructor que se encargará de liberar la memoria dinámica reservada al crear la tabla table
        ~HashTable(){
        	delete[] table;
        }
        
        //Devuelve el número total de cubetas de la tabla
        int capacity(){
        	return max;
        }
        
        //Sobrecarga global del operador << para imprimir el contenido de la tabla hash por pantalla
        friend std::ostream& operator << (std::ostream &out, const HashTable<V> &th){
        	for (int i = 0; i < th.max; ++i) {
       			out << "Cubeta " << i << ": " << th.table[i] << std::endl;
   		}
   		
   		return out;
        }
        
        //Sobrecarga del operador[]. Devuelve el valor correspondiente a key. Si no existe, lanza la excepción std::runtime_error.
        V operator[](std::string key){
        	return search(key);  //Función search de TableHash
        }
        
        
};

#endif
