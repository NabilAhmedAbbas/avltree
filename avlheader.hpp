#ifndef AVL_TREE_HPP
#define AVL_TREE_HPP

// #include <iostream>
template<typename T>
struct avlNode
{
  T data;
  avlNode* left;
  avlNode* right;
  int height;
};

int max(int a, int b)
{
  return (a>b) ? a : b;
}

template<typename T>
class avltree
{
private:
  avlNode<T> *root=nullptr;
  void insert(avlNode<T> *&, T);
  bool search(avlNode<T> *&, T &);
  void balance(avlNode<T> *&);
  void rightrotate(avlNode<T> *&);
  void leftrotate(avlNode<T> *&);
  void rightleftrotation(avlNode<T>*&);
  void leftrightrotation(avlNode<T>*&);
  void remove(avlNode<T> *&, T );
  avlNode<T> *findmin(avlNode<T> *&);
  avlNode<T> *findmax(avlNode<T> *&);

public:
  avltree();
  void insert(T );
  bool search(T &&) ;
  int Height(avlNode<T> *&);
  void remove(T data);
  T get_max();
  T get_min();
  void print_tree(T );

};
//--------------implementation---------
template<typename T>
avltree<T>::avltree()
{

}
template<typename T>
void avltree<T>::insert(avlNode<T> *&node, T data)
{

  if (node == nullptr)
    node = new avlNode<T>{data, nullptr, nullptr, 0};


  else if (data > node->data)
    insert(node->right, data);

  else
    insert(node->left, data);

  
  balance(node);
}

template<typename T>
void avltree<T>::insert(T data)
{
  insert(root, data);
}

template<typename T>
bool avltree<T>::search(avlNode<T> *&node, T &data)
{
  if (node == nullptr)
    return false;
  if (data == node->data)
    return true;
  if ( data > node->data)
    return search(node->right, data);
  else
    return search(node->left, data);


}

template<typename T>
bool avltree<T>::search(T &&data)
{
  return search(root, data);

}

template<typename T>
int avltree<T>::Height(avlNode<T> *&node)
{
  return (node == nullptr) ? 0 : node->height;
}

template<typename T>
void avltree<T>::balance(avlNode<T> *&node)
{

  if (node == nullptr)
    return;

  if ((Height(node->left) - Height(node->right)) > 1)
    {

      if (Height(node->left->left) >= Height(node->left->right))
        rightrotate(node);
      else
        rightleftrotation(node);
    }

   else if ((Height(node->right) - Height(node->left)) > 1)
    {

    if ((Height(node->right->right) >= Height(node->right->left)))
      leftrotate(node);
    else
        leftrightrotation(node);
    }
    else
    {}

  node->height = max(Height(node->left), Height(node->right)) + 1;
}

template<typename T>
void avltree<T>::rightrotate(avlNode<T> *&node)
{
  avlNode<T> *temp = node->left;
  node->left = temp->right;
  temp->right = node;

  node->height = max(Height(node->left), Height(node->right)) + 1;
  temp->height = max(Height(node->left), node->height)+ 1;

  node = temp;

}

template<typename T>
void avltree<T>::leftrotate(avlNode<T> *&node)
{
  avlNode<T> *temp = node->right;
  node->right = temp->left;
  temp->left = node;

  node->height = max(Height(node->left), Height(node->right))+1;
  temp->height = max(Height(temp->right), node->height)+1;

  node = temp;
}

template<typename T>
void avltree<T>::rightleftrotation(avlNode<T> *&node)
{
  rightrotate(node->right);
  leftrotate(node);

}

template<typename T>
void avltree<T>::leftrightrotation(avlNode<T> *&node)
{
  leftrotate(node->left);
  rightrotate(node);
}
template<typename T>
void avltree<T>::remove(T data)
{
  remove(root, data);
}

template<typename T>
void avltree<T>::remove(avlNode<T> *&node, T data)
{
  if (node == nullptr)
    return;
  if (data > node->data)
    remove(node->right, data);
  else if (data < node-> data)
    remove(node->left, data);
  else if (node->left != nullptr && node->right != nullptr)
    {
      node->data = findmin(node->right)->data;
      remove(node->right, node->data); 
    }
    else
    {
        avlNode<T> *temp = node;
        node = (node->left != nullptr) ? node->left : node->right;
        // std::cout<<"node=====>:"<<node<<std::endl;
        delete temp;
    }

    balance(node);

}
template<typename T>
avlNode<T>* avltree<T>::findmax(avlNode<T> *& node)
{
  if (node == nullptr)
    return nullptr;
  if (node->right == nullptr)
    return node;
  return findmax(node->right);
}

template<typename T>
avlNode<T>* avltree<T>::findmin(avlNode<T> *& node)
{
  if (node == nullptr)
    return nullptr;
  if (node->left == nullptr)
    return node;
  return findmin(node->left);
}
template<typename T>
T avltree<T>::get_max()
{
  return findmax(root)->data;

}
template<typename T>
T avltree<T>::get_min()
{
  return findmin(root)->data;
}
template<typename T>
void avltree<T>::print_tree(T data)
{
  avlNode<T> *temp = root;
  std::cout<<root->data<<"from root   "<<std::endl;
  if (temp == nullptr)
    return;

  while(true)
  {
    if (temp == nullptr)
      break;
    std::cout<<temp->data<<"-- ";
    if (data > temp->data)
        temp = temp->right;
    else if (data < temp->data)
      temp = temp->left;

     else break;

  }

}

#endif
