#include "rb_tree.h"

void print_space(int n) {
    while (n--) printf(" ");
}
//for debugging
void print_preorder_with_tab(ptr_rbnode node, int depth) {
    if (node == NULL) return;

    print_space(depth);
    printf("%d %s\n",
           node->val,
           node->nil ? "NIL" : (node->color == RED ?
                                "R" : "B")
    );
    if (node->left) print_preorder_with_tab(node->left, depth + 1);
    if (node->right) print_preorder_with_tab(node->right, depth + 1);
}
//for debugging
void print_inorder(ptr_rbnode node) {
    if (node->nil) return;
    print_inorder(node->left);
    printf("%d ", node->val);
    print_inorder(node->right);
}

void print_levelbylevel(ptr_rbnode root) {
    CircularQueue *cq;
    cq_init(cq, ELEMENT_MAX);

    cq_push(cq, root);
    int depth_cnt = -1;
    while ((depth_cnt = cq->capacity)) {

        while (depth_cnt--) {
            cq_element_t current_node = cq_front(cq);
            cq_pop(cq);
            if (current_node->nil) {
                printf("N ");
            }
            else {
                printf("%d%s ", current_node->val, current_node->color ? "(B)" : "(R)");
                cq_push(cq, current_node->left);
                cq_push(cq, current_node->right);
            }
        }
        printf("\n");
    }
    cq_destroy(cq);
}
ptr_rbnode get_grandparent(ptr_rbnode node) {
    if (node && node->parent) return node->parent->parent;
    else return NULL;
}
ptr_rbnode get_uncle(ptr_rbnode node) {
    ptr_rbnode g = get_grandparent(node);
    if (g) {
        if (g->left == node->parent) {
            return g->right;
        }
        else if (g->right == node->parent) {
            return g->left;
        }
        else {
            assert(0 && "Tree Collapsed");
        }
    }
    else
        return NULL;
}
ptr_rbnode get_sibiling(ptr_rbnode node) {
    if (node && node->parent) {
        if (node->parent->left == node) return node->parent->right;
        else if (node->parent->right == node) return node->parent->left;
        else
            assert(0 && "Tree Collpased");
    }
    else
        return NULL;
}
void rotate_left(ptr_rbnode node) {
    assert(node->right);
    ptr_rbnode p = node->parent, right_child = node->right;

    node->right = right_child->left;
    node->right->parent = node;
    right_child->left = node;
    right_child->left->parent = right_child;
    if (p) {
        if (p->left == node) {
            p->left = right_child;
            p->left->parent = p;
        }
        else {
            p->right = right_child;
            p->right->parent = p;
        }
    }
    else {
        right_child->parent = p;
    }
}
void rotate_right(ptr_rbnode node) {
    assert(node->left);
    ptr_rbnode p = node->parent, left_child = node->left;

    node->left = left_child->right;
    node->left->parent = node;
    left_child->right = node;
    left_child->right->parent = left_child;
    if (p) {
        if (p->left == node) {
            p->left = left_child;
            p->left->parent = p;
        }
        else {
            p->right = left_child;
            p->right->parent = p;
        }
    }
    else {
        left_child->parent = p; //null
    }
}
void make_balance_after_insert(ptr_rbnode node) {
    //case 1 : root node
    if (node->parent == NULL) {
        node->color = BLACK;
        return;
    }
    //case 2 : parent is black
    if (node->parent->color == BLACK) {
        return; //nothing to do
    }
    //now it is guaranteed that node has grandparent
    //case 3 : p and u = red, g = black
    ptr_rbnode g = get_grandparent(node), u = get_uncle(node), p = node->parent;
    assert(g);
    if (p->color == RED && u->color == RED && g->color == BLACK) {
        p->color = BLACK; u->color = BLACK; g->color = RED;
        make_balance_after_insert(g);
        /* this recursive operation will take O(log N) in worst case and O(1) in average case
        because the time complexity distribution would have a form of geometric distribution. */
        return;
    }

    //case 4,5 : p = red, u = black, g = black; -> guaranteed
    //if node, p and g is not on a line, rotate
    //case 4 would be changed into case 5
    assert(p->color == RED && u->color == BLACK && g->color == BLACK);
    if (g->left == p && p->right == node) {
        rotate_left(p);
        node = node->left;
        //for case 5
        g = get_grandparent(node), u = get_uncle(node), p = node->parent;
    }

    else if (g->right == p && p->left == node) {
        rotate_right(p);
        // for case 5
        g = get_grandparent(node), u = get_uncle(node), p = node->parent;
        node = node->right;
    }
    g = get_grandparent(node), u = get_uncle(node), p = node->parent;
    //case 5
    assert((p->left == node && g->left == p)
           || (p->right == node && g->right == p));
    p->color = BLACK;
    g->color = RED;

    if (p->left == node) {
        rotate_right(g);
    }
    else {
        rotate_left(g);
    }
}

ptr_rbnode find_node(ptr_rbnode node, rbtree_element_type_t val) {
    if (node) {
        while (!node->nil) {
            if (node->val > val) {
                node = node->left;
            }
            else if (node->val < val) {
                node = node->right;
            }
            else {
                return node;
            }
        }
    }

    return NULL;
}
//returns changed root node
ptr_rbnode insert_node(ptr_rbnode root, rbtree_element_type_t val, int logging) {

    ptr_rbnode node = root;
    while (!node->nil) {
        if (node->val > val) {
            node = node->left;
        }
        else if (node->val < val) {
            node = node->right;
        }
        else {
            if (logging) printf("%d is already in the tree! \n", val);
            return root;
        }
    }
    node->val = val;
    node->nil = 0;
    node->color = RED;
    node->left = (ptr_rbnode)malloc(sizeof(rbnode));
    node->right = (ptr_rbnode)malloc(sizeof(rbnode));
    node->left->parent = node;
    node->right->parent = node;
    node->left->nil = 1;
    node->right->nil = 1;
    node->left->color = BLACK;
    node->right->color = BLACK;
    node->left->left = node->left->right = node->right->left = node->right->right = NULL;
    make_balance_after_insert(node);

    while (root->parent) root = root->parent;

    return root;
}

ptr_rbnode init_rbtree() {
    ptr_rbnode root = (ptr_rbnode)malloc(sizeof(rbnode));
    root->nil = 1;
    root->color = BLACK;
    root->parent = NULL;
    root->left = NULL;
    root->right = NULL;
    return root;
}

ptr_rbnode find_max_node(ptr_rbnode node) {
    if (node && !node->nil) {
        while (!node->right->nil) {
            node = node->right;
        }
    }
    return node;
}
//returns root
ptr_rbnode replace_node(ptr_rbnode root, ptr_rbnode src, ptr_rbnode dst) {
    if (dst->parent == NULL) {
        root = src;
    }
    else {

        if (dst->parent->left == dst) {
            dst->parent->left = src;
        }
        else {
            dst->parent->right = src;
        }
    }
    src->parent = dst->parent;
    return root;
}
void delete_one_child(ptr_rbnode node) {
    ptr_rbnode s = get_sibiling(node), p = node->parent;
    if (p) {
        if (s->color == RED) {
            p->color = RED; s->color = BLACK;

            if (p->left == node) {
                rotate_left(p);
            }
            else {
                rotate_right(p);
            }
        }

        s = get_sibiling(node), p = node->parent;
        if (s->color == BLACK && s->left->color == BLACK && s->right->color == BLACK) {
            if (p->color == BLACK) {
                s->color = RED;
                delete_one_child(p);
            }
            else {
                s->color = RED;
                p->color = BLACK;
            }
        }
        else {
            if (node->parent->left == node && s->right->color == RED) {
                s->color = p->color; p->color = BLACK; s->right->color = BLACK;
                rotate_left(p);
            }
            else if (node->parent->left == node && s->left->color == RED) {
                s->left->color = p->color; p->color = BLACK;
                rotate_right(s);
                rotate_left(s->parent->parent);
            }
            else if (node->parent->right == node && s->left->color == RED) {
                s->color = p->color; p->color = BLACK; s->left->color = BLACK;
                rotate_right(p);
            }
            else if (node->parent->right == node && s->right->color == RED) {
                s->right->color = p->color; p->color = BLACK;
                rotate_left(s);
                rotate_right(s->parent->parent);
            }
            else
                assert(0 && "balance error");
        }

    }
}

void destroy_tree(ptr_rbnode root) {
    if (root == NULL) {
        return;
    }
    destroy_tree(root->left); destroy_tree(root->right);
    free(root);
}

int is_leaf(ptr_rbnode node) {
    assert(node);
    return node->nil == 0 &&
           (!(node->left->nil == 1 && node->left->nil == 1));
}
ptr_rbnode delete_node(ptr_rbnode root, rbtree_element_type_t val, int logging) {
    ptr_rbnode node = find_node(root, val);
    if (node) {
        ptr_rbnode left_max_node = NULL;
        if (node->left->nil == 0 && node->right->nil == 0) {
            left_max_node = find_max_node(node->left);
            node->val = left_max_node->val;
            node = left_max_node;
        }
        ptr_rbnode child = node->right->nil == 1 ? node->left : node->right;
        if (node->color == BLACK) {
            node->color = child->color;
            delete_one_child(node);
        }
        root = replace_node(root, child, node);
        free(node);
        return root;
    }
    else {
        if (logging) printf("%d is not in the tree\n", val);
        return root;
    }

}

//for debugging . returns black_height
int assert_tree(ptr_rbnode node) {
    if (node == NULL) return 0;
    if (node->parent) {
        assert(!(
                (node->color == RED) && (node->parent->color == RED)
        ));
    }

    int left_bh = 0, right_bh = 0;
    if (node->left) left_bh = assert_tree(node->left);
    if (node->right) right_bh = assert_tree(node->right);

    assert(left_bh == right_bh);
    return left_bh + (node->color == BLACK ? 1 : 0);
}
