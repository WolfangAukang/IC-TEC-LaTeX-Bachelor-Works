#ifndef BSTREE_H
#define BSTREE_H
#include "BSTNode.h"
#include <stdexcept>

using namespace std;

template <typename Key, typename E>
class BSTree
{
private:
    BSTNode<Key, E>* root;

    // Funci�n auxiliar de inOrder()
    // Realiza un recorrido inOrder imprimiendo en consola
    void inOrderAux(BSTNode<Key, E>* pRoot) {
        if (pRoot == NULL) {
            return;
        }
        inOrderAux(pRoot->getLeft());
        cout << pRoot->getElement() << " ";
        inOrderAux(pRoot->getRight());
    }
    // Funci�n auxiliar de insert()
    // Inserta un nuevo par llave-valor en el �rbol.
    // Retorna un puntero al �rbol modificado.
    BSTNode<Key, E>* insertAux(BSTNode<Key, E>* pRoot, Key pKey, E pElement) {
        if (!pRoot)
            return pRoot = new BSTNode<Key, E> (pKey, pElement);
        if (pKey < pRoot->getKey()) {
            pRoot->setLeft(insertAux(pRoot->getLeft(), pKey, pElement));
            return pRoot;
        } else {
            pRoot->setRight(insertAux(pRoot->getRight(), pKey, pElement));
            return pRoot;
        }
    }
    // Funci�n auxiliar de find()
    // Busca el nodo con la llave indicada y retorna su valor.
    // Lanza una excepci�n si no se encuentra.
    E findAux(BSTNode<Key, E>* pRoot, Key pKey) throw (runtime_error) {
        if (!pRoot)
            throw runtime_error("Key not found.");
        if(pRoot->getKey() == pKey)
            return pRoot->getElement();
        if(pRoot->getKey() > pKey)
            return findAux(pRoot->getLeft(),pKey);
        if(pRoot->getKey() < pKey)
            return findAux(pRoot->getRight(),pKey);
    }
    // Funci�n auxiliar de remove()
    // Elimina el nodo con la llave indicada.
    // Lanza excepci�n si el nodo no se encuentra.
    BSTNode<Key, E>* removeAux(BSTNode<Key, E>* pRoot, Key pKey) throw (runtime_error) {
        if (!pRoot) {
            throw runtime_error("Key not found.");
        }
        if (pKey < pRoot->getKey()){
            pRoot->setLeft(removeAux(pRoot->getLeft(), pKey));
            return pRoot;
        }
        if (pKey > pRoot->getKey()) {
            pRoot->setRight(removeAux(pRoot->getRight(), pKey));
            return pRoot;
        } else {
            if (pRoot->isLeaf()) {
                return NULL;
            }
            if (pRoot->childrenCount() == 1) {
                return pRoot->getUniqueChild();
            } else {
                BSTNode<Key, E>* n = pRoot->getRight();
                BSTNode<Key, E>* tmp = n;
                while(tmp->getLeft())
                    tmp = tmp->getLeft();
                tmp->setLeft(pRoot->getLeft());
                return n;

            }
        }
    }
    // Intercambia la llave y elemento de dos nodos indicados.
    void swap(BSTNode<Key, E>* pNode1, BSTNode<Key, E>* pNode2) {
        Key tempK = pNode1->getKey();
        E tempE = pNode1->getElement();
        pNode1->setKey(pNode2->getKey());
        pNode1->setElement(pNode2->getElement());
        pNode2->setKey(tempK);
        pNode2->setElement(tempE);
    }

public:
    BSTree() {
        root = NULL;
    }
    // Inserta un nuevo par llave-valor en el �rbol.
    void insert(Key pKey, E pElement) {
        root = insertAux(root, pKey, pElement);
    }
    // Imprime el recorrido inOrder en la consola.
    void inOrder() {
        inOrderAux(root);
        cout << endl;
    }
    // Retorna el elemento asociado a la llave indicada.
    // Lanza excepci�n si no lo encuentra.
    E find(Key pKey) {
        return findAux(root, pKey);
    }
    // Elimina el elemento asociado a la llave indicada.
    // Lanza excepci�n si no lo encuentra.
    E remove(Key pKey) {
        E result = find(pKey);
        root = removeAux(root, pKey);
        return result;
    }
};

#endif // BSTREE_H
