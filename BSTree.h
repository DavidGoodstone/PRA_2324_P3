#ifndef BSTREE_H
#define BSTREE_H

#include <ostream>
#include <stdexcept>
#include "BSNode.h"

template <typename T> 
class BSTree {
    private:
        //Miembros privados
        
        //Número de elementos almacenados en el ABB
        int nelem;
        
        //Nodo raíz del ABB
        BSNode<T> *root;
        
        //Método recursivo para la búsqueda elementos en el ABB. Busca y devuelve el elemento e de tipo T si se encuentra en el (sub-)árbol cuya raíz es n, de lo contrario lanza una std::runtime_error
        BSNode<T>* search(BSNode<T>* n, T e) const {
        	if (n == nullptr) {  //Si no existe el elemento, imprimimos un error
			throw std::runtime_error("El elemento no existe.");
		} else if (n->elem < e) {  //Mientras que el elemento a buscar sea mayor al elemento del ABB, buscaremos por la derecha
			return search(n->right, e);
		} else if (n->elem > e) {  //Mientras que el elemento a buscar sea menor al elemento del ABB, buscaremos por la izquierda
			return search(n->left, e);
		} else {  //Mientras que el elemento a buscar sea igual al elemento del ABB, devolvemos el valor del elemento
			return n;
		}
        }
        
        //Método recursivo para la inserción ordenada de elementos. Inserta el elemento e de tipo T de manera ordenada en el (sub-)árbol cuya raíz es n. Devuelve el nodo que encabeza dicho (sub-)árbol 		  modificado. Si el elemento e ya existe, lanza un std::runtime_error
        BSNode<T>* insert(BSNode<T>* n, T e){
        	if (n == nullptr) {  //Si no existe el nodo, lo insertamos
            		nelem++;
            		return new BSNode<T>(e);
        	} else if (n->elem == e) {  //Si el elemento a insertar es igual al elemento del ABB, imprimimos un error
            		throw std::runtime_error("El elemento ya existe.");
        	} else if (n->elem < e) {  //Mientras que el elemento a insertar sea mayor al elemento del ABB, nos desplazaremos por la derecha
            		n->right = insert(n->right, e);
        	} else {  //Mientras que el elemento a insertar sea menor al elemento del ABB, nos desplazaremos por la izquierda
            		n->left = insert(n->left, e);
        	}
        	
        	return n;  //Devolvemos el elemento insertado
        }
        
        //Recorrido inorden o simétrico del (sub-)árbol cuya raíz es n para mostrar a través de out los elementos ordenados de menor a mayor
        void print_inorder(std::ostream &out, BSNode<T>* n) const{
		if (n != nullptr) {  //(Sacado de la teoría)
			print_inorder(out, n->left);  //Imprimimos la rama izquierda
			
			out << n->elem << " ";  //Imprimimos el elemento
			
			print_inorder(out, n->right);  //Imprimimos la rama derecha
		}
        }
        
        //Método recursivo para la eliminación de elementos. Elimina el elemento e del (sub-)árbol cuya raíz es n. Devuelve el nodo que encabeza dicho (sub-)árbol modificado. En caso de eliminar un nodo con 		  dos sucesores (izquierdo y derecho), aplicará la politica de reemplazo por el elemento máximo del subárbol izquierdo. Para ello, se apoyará en los métodos privados auxiliares max() y remove_max(). 		  Si el elemento e no existe, lanza un std::runtime_error
        BSNode<T>* remove(BSNode<T>* n, T e){
		if (n == nullptr) {  //Si el elemento a eliminar no existe, imprimimos un error
        		throw std::runtime_error("El elemento no existe.");
    		} else if (n->elem < e) {  //Mientras que el elemento a eliminar sea mayor al elemento del ABB, nos desplazaremos por la derecha
        		n->right = remove(n->right, e);
    		} else if (n->elem > e) {  //Mientras que el elemento a eliminar sea menor al elemento del ABB, nos desplazaremos por la izquierda
       		n->left = remove(n->left, e);
    		} else {
        		// Nodo encontrado, procedemos a la eliminación
        		if (n->right != nullptr && n->left != nullptr) {  //Si la rama izquierda y derecha no están vacías, el hermano del elemento a eliminar del ABB obtendrá el valor del elemento a 										     eliminar, y el hijo pasará a ser hijo del hermano del elemento a eliminar del ABB
            			n->elem = max(n->left);
				n->left = remove_max(n->left);
        		} else {  //Si la rama izquierda no está vacía, se desplazará hacia la izquierda, sino, hacia la derecha
            			n = (n->left != nullptr)? n->left: n->right;
        		}
        		
        		nelem--;
	    	}

	    	return n;  //Devolvemos el elemento eliminado
        }
        
        //Método recursivo que devuelve el elemento de máximo valor contenido en el (sub-)árbol cuya raíz es n
        T max(BSNode<T>* n) const{
        	if (n == nullptr) {  //Si el elemento máximo no existe, imprimimos un error
        		throw std::runtime_error("El elemento máximo no existe.");
    		} else if (n->right != nullptr) {  //Si el desplazamiento hacia a la derecha no llega a su límite, continuamos desplazándonos hacia la derecha
        		return max(n->right);
    		} else {  //Si el desplazamiento hacia a la derecha llega a su límite, devolvemos el valor máximo
    			return n->elem;
    		}
        }
        
        //Método recursivo que elimina el elemento de máximo valor contenido en el (sub-)árbol cuya raíz es n
        BSNode<T>* remove_max(BSNode<T>* n){
        	if (n->right == nullptr) {  //Si no existe ningún nodo hacia la derecha, devolvemos el nodo de la izquierda (valor máximo)
        		return n->left;
    		} else {  //Si existe algún nodo hacia la derecha, nos desplazamos hacia la derecha
       		n->right = remove_max(n->right);
        		return n;
    		}
        }
        
        //Método recursivo para liberación de la memoria dinámica ocupada por los objetos de tipo BSNode<T> que conforman el (sub-)árbol cuya raíz es n
        void delete_cascade(BSNode<T>* n){
        	if (n != nullptr) {  //Eliminamos las ramas izquierdas y derechas y sus nodos
        		delete_cascade(n->left);
        		delete_cascade(n->right);
        		delete n;
    		}
        }
        
        
        
    public:
        //Miembros públicos
    	
    	//Método constructor. Crea un ABB vacío
    	BSTree() {
    		root = nullptr;
    		nelem = 0;
    	}
    	
    	//Devuelve el número de elementos nelem del ABB
    	int size() const{
    		return nelem;
    	}
    	
    	//Busca y devuelve el elemento  e de tipo T en el ABB.  Actúa como método lanzadera del método privado recursivo search(BSNode<T>* n, T e).  Notar que deberá devolver el elemento contenido por el 	  nodo devuelto por el método privado
    	T search(T e) const{
    		return search(root, e)->elem;	
    	}
    	
    	//Sobrecarga del operador[]. Actúa como interfaz al método search(T e)
    	T operator[](T e) const{
    		return search(e);
    	}
    	
    	//Inserta el elemento e de tipo T de manera ordenada en el  ABB. Actúa como método lanzadera del método privado recursivo insert(BSNode<T>* n, T e)
    	void insert(T e){
    		root = insert(root, e);
    	}
    	
    	//Sobrecarga del operador << para mostrar a través de out los contenidos del ABB bst, realizando un recorrido inorden o simétrico del árbol para mostrar los elementos ordenados de menor a mayor. 		  Delega en el método privado recursivo print_inorder()
    	friend std::ostream& operator<<(std::ostream &out, const BSTree<T> &bst){
    		bst.print_inorder(out, bst.root);
    		
    		return out;
    	}
    	
    	//Elimina el elemento e de tipo T del ABB. Actúa como método lanzadera del método privado recursivo remove(BSNode<T>* n, T e)
    	void remove(T e){
    		root = remove(root, e);
    	}
    	
    	//Método destructor. Delega en el método privado recursivo delete_cascade()
    	~BSTree(){
    		delete_cascade(root);
    	}
};

#endif
