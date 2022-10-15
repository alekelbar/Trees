#include <iostream>
using namespace std;

class Node {
  int data;
  Node *right;
  Node *left;

  friend void insert(Node *&, int);
  friend void preorder(Node *);
  friend bool isLeaf(Node *);
  friend void remove(Node *, int);
};

void insert(Node *&tree, int value) {
  Node *padre = NULL;  /* (1) */
  Node *actual = tree; /* (2) */

  while (actual && value != actual->data) {
    padre = actual;
    // Decidir si derecha, o izquierda....
    if (value < actual->data)
      actual = actual->left;
    else if (value > actual->data)
      actual = actual->right;
  }

  // Si el actual no esta vacio, ya se encuentra en el arbol...
  if (actual)
    return;
  // El arbol esta vacio... El nuevo elemento será raíz.
  if (!padre) {
    tree = new Node();
    tree->data = value;
    tree->left = tree->right = NULL;

    // Si el valor del padre es menor, insertamos a la izq....
  } else if (value < padre->data) {
    actual = new Node();
    padre->left = actual;
    actual->data = value;
    actual->left = actual->right = NULL;

    // Si el valor del padre es mayor, insertamos a la der....
  } else if (value > padre->data) {
    actual = new Node();
    padre->right = actual;
    actual->data = value;
    actual->left = actual->right = NULL;
  }
}

void preorder(Node *node) {
  if (!node)
    return;
  cout << "preorder: " << node->data << endl;
  preorder(node->left);
  preorder(node->right);
}

bool isLeaf(Node *node) { return !node->right and !node->left; }

void remove(Node *tree, int value) {
  Node *padre = NULL;
  Node *actual = tree; // Del recorrido...
  Node *nodo;          // A insertar...
  int aux;             // Para intercambio...

  while (actual) {               /* Búsqueda (2) else implícito */
    if (value == actual->data) { /* (3) */
      if (isLeaf(actual)) {      /* (3-a) */
        if (padre)               /* (3-a-i caso else implícito) */
          if (padre->right == actual)
            padre->right = NULL;
          /* (3-a-ii) */
          else if (padre->left == actual)
            padre->left = NULL; /* (3-a-iii) */
        delete actual;          /* (3-a-iv) */
        actual = NULL;
        return;
      } else { /* (3-b) */
        /* Buscar nodo */
        padre = actual; /* (3-b-i) */
        if (actual->right) {
          nodo = actual->right;
          while (nodo->left) {
            padre = nodo;
            nodo = nodo->left;
          }
        } else {
          nodo = actual->left;
          while (nodo->right) {
            padre = nodo;
            nodo = nodo->right;
          }
        }
        /* Intercambio */
        aux = actual->data; /* (3-b-ii) */
        actual->data = nodo->data;
        nodo->data = aux;
        actual = nodo;
      }
    } else {
      padre = actual;
      if (value > actual->data)
        actual = actual->right; /* (4)
                                 */
      else if (value < actual->data)
        actual = actual->left;
      /* (5) */
    }
  }
}

int main() {
  // code
  Node *arbol = NULL;
  insert(arbol, 30);
  insert(arbol, 9);
  insert(arbol, 32);
  insert(arbol, 11);
  insert(arbol, 42);
  remove(arbol, 9);
  preorder(arbol);

  std::cout << "Hello Easy C++ project!" << std::endl;
}