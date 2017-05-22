#include <iostream>
#include <queue>
#include <cassert>


template<class T>
struct Node {
    T elem;
    int height = 1;
    int nodes_num = 1;
    Node *left = nullptr;
    Node *right = nullptr;

    Node( T elem ) : elem( elem ) {};
};

template<class T>
class AVLTree {
public:
    AVLTree() = default;

    ~AVLTree();

    void remove_from_pos( const int position );

    int insert( const T &value );;

private:
    Node<T> *root = nullptr;

    Node<T> *rotate_left( Node<T> *node );

    Node<T> *rotate_right( Node<T> *node );

    Node<T> *balance( Node<T> *node );

    Node<T> *insert( Node<T> *node, const T &value, int &position );

    Node<T> *remove( Node<T> *node, const T &value );

    void fix_height( Node<T> *node );

    void fix_nodes_num( Node<T> *node );

    int balance_factor( Node<T> *node ) { return ( height( node->right ) - height( node->left ) ); }

    int height( Node<T> *node ) { return node ? node->height : 0; }

    int nodes_num( Node<T> *node ) { return node ? node->nodes_num : 0; }

    Node<T> *find_min_elem( Node<T> *node );

};


template<class T>
AVLTree<T>::~AVLTree() {
    std::queue<Node<T> *> queue;
    if ( root != nullptr ) {
        queue.push( root );
    }
    while ( !queue.empty() ) {
        Node<T> *current = queue.front();
        if ( current->right != nullptr ) {
            queue.push( current->right );
        }
        if ( current->left != nullptr ) {
            queue.push( current->left );
        }

        delete current;
        queue.pop();
    }
}

template<class T>
int AVLTree<T>::insert( const T &value ) {
    int position = 0;
    root = insert( root, value, position );
    return position;
}

template<class T>
Node<T> *AVLTree<T>::rotate_right( Node<T> *node ) {

    Node<T> *left_child = node->left;
    node->left = left_child->right;
    left_child->right = node;
    fix_height( node );
    fix_nodes_num( node );
    fix_height( left_child );
    fix_nodes_num( left_child );
    return left_child;
}

template<class T>
Node<T> *AVLTree<T>::rotate_left( Node<T> *node ) {
    Node<T> *right_child = node->right;
    node->right = right_child->left;
    right_child->left = node;
    fix_height( node );
    fix_nodes_num( node );
    fix_height( right_child );
    fix_nodes_num( right_child );
    return right_child;
}


template<class T>
Node<T> *AVLTree<T>::balance( Node<T> *node ) {
    fix_height( node );
    fix_nodes_num( node );
    if ( balance_factor( node ) == 2 ) {
        if ( balance_factor( node->right ) < 0 )
            node->right = rotate_right( node->right );
        return rotate_left( node );
    }
    if ( balance_factor( node ) == -2 ) {
        if ( balance_factor( node->left ) > 0 )
            node->left = rotate_left( node->left );
        return rotate_right( node );
    }
    return node;
}


template<class T>
Node<T> *AVLTree<T>::insert( Node<T> *node, const T &value, int &position ) {
    if ( node == nullptr ) {
        return new Node<T>( value );
    }

    node->nodes_num++;
    if ( value < node->elem ) {
        position += nodes_num( node->right ) + 1;
        node->left = insert( node->left, value, position );
    } else {
        node->right = insert( node->right, value, position );
    }
    return balance( node );
}


template<class T>
Node<T> *AVLTree<T>::remove( Node<T> *node, const T &value ) {
    if ( node == nullptr ) {
        return nullptr;
    }

    if ( value < node->elem ) {
        node->left = remove( node->left, value );
    } else if ( value > node->elem ) {
        node->right = remove( node->right, value );
    } else {

        if ( node->left == nullptr && node->right == nullptr ) {
            delete node;
            return nullptr;
        }

        if ( node->right == nullptr ) {
            Node<T> *left = node->left;
            *node = *left;
            delete left;
            return node;
        }

        if ( node->left == nullptr ) {
            Node<T> *right = node->right;
            *node = *right;
            delete right;
            return node;
        }

        Node<T> *temp = find_min_elem( node->right );
        node->elem = temp->elem;
        node->right = remove( node->right, temp->elem );
    }

    return balance( node );
}


template<class T>
void AVLTree<T>::remove_from_pos( const int position ) {
    if(root == NULL)
        return;
    assert( position < root->nodes_num );
    Node<T> *node = root;

    int index = nodes_num( root->right );

    while ( index != position ) {
        if ( position > index ) {
            node = node->left;
            index += 1 + nodes_num( node->right );
        } else {
            node = node->right;
            index -= 1 + nodes_num( node->left );
        }
    }

    root = remove( root, node->elem );
}

template<class T>
void AVLTree<T>::fix_height( Node<T> *node ) {
    int height_left = height( node->right );
    int height_right = height( node->left );
    node->height = ( height_left > height_right ? height_left : height_right ) + 1;
}

template<class T>
Node<T> *AVLTree<T>::find_min_elem( Node<T> *node ) {
    return node->left == nullptr ? node : find_min_elem( node->left );
}

template<class T>
void AVLTree<T>::fix_nodes_num( Node<T> *node ) {
    int nodes_num_left = nodes_num( node->left );
    int nodes_num_right = nodes_num( node->right );
    node->nodes_num = nodes_num_left + nodes_num_right + 1;
}


int main() {
    int n = 0;
    std::cin >> n;
    assert( n > 0 );

    AVLTree<int> tree;

    for ( int i = 0; i < n; i++ ) {
        int command;
        int elem;

        std::cin >> command >> elem;

        switch ( command ) {
            case 1:
                std::cout << tree.insert( elem ) << std::endl;
                break;
            case 2:
                tree.remove_from_pos( elem );
                break;
            default:
                assert( false );
        }
    }
    return 0;
}