#ifndef BSNODE_H
#define BSNODE_H

#include <ostream>

template <typename T> 
class BSNode {
    public:
        //Miembros públicos
        
        //El elemento de tipo T almacenado en el nodo
        T elem;
        
        //Puntero al nodo sucesor izquierdo
        BSNode<T>* left;
        
        //Puntero al nodo sucesor derecho
        BSNode<T>* right;
        
        //Método constructor que crea un BSNode con el elemento elem y los punteros a los nodos sucesores left y  right proporcionados (nulos por defecto)
        BSNode(T elem, BSNode<T>* left=nullptr, BSNode<T>* right=nullptr){
        	this->elem = elem;
        	this->left = left;
        	this->right = right;
        }
        
        //Sobrecarga global del operador << para imprimir el nodo por pantalla. Por simplicidad, puedes limitarte a imprimir el atributo elem
        friend std::ostream& operator<<(std::ostream &out, const BSNode<T> &bsn){
        	out << "Elemento: " << bsn.elem << std::endl;
        	
        	return out;
        
        }
    
};

#endif
