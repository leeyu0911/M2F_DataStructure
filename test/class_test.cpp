template <class Type> BstNode <Type>* BST <Type>::Search(const Element<Type>& x)
/* Search the binary search tree (*this) for an element with key x. If such an element
is found, return a pointer to the node that contains it. */
{
    return Search(root, x);
}
template <class Type> //Workhorse
BstNode <Type>* BST
        <Type>::Search(BstNode<Type>*b, const Element <Type>&x)
{
    if(!b) return 0;
    if(x.key == b->data.key) return b;
    if(x.key < b->data.key) return Search(b->LeftChild, x);
    return Search(b->RightChild, x);
}

template <class Type>
BstNode <Type>* BST<Type>::Search(int k)
// Search the binary search tree for the kth smallest element
{

    BstNode<Type> *t = root;
    while(t)

    {

        if (k == t->LeftSize) return t;
        if (k < t->LeftSize) t = t->LeftChild;
        else {
            k -=t-> LeftSize;
            t = t->RightChild;

        }

    }

    return 0;

}