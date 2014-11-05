#include "tree.hpp"

typedef tree::default_value_type value_type;

tree::__tree_node<value_type>* __test_create_tree(std::vector<value_type>& vec,
        tree::binary_tree_type treeType) {
    if (treeType == tree::BINARY_RANDOM_TREE) {
        return tree::create_tree(vec.begin(), vec.end());
    } else {
        tree::binary_search_tree_optioner<value_type> bst_picker;
        return tree::create_tree(vec.begin(), vec.end(), bst_picker);
    }
}

int main() {

    const int TEST_DATA_SIZE = 17;

    std::vector<value_type> vec;
    for (int i = 0; i < TEST_DATA_SIZE; ++i) {
        vec.push_back(tree::random_tree_value() + 1);
    }
    tree::__tree_node<value_type>* tree = __test_create_tree(vec,
            tree::BINARY_SEARCH_TREE);

    std::cout << "in order: "; in_order(tree); std::cout << "\n";
    std::cout << "pre order: "; pre_order(tree); std::cout << "\n";
    std::cout << "post order: "; post_order(tree); std::cout << "\n";
    std::cout << "level order: "; level_order(tree); std::cout << "\n";

    // test validate procedure
    if (validate_bst(tree, std::numeric_limits<unsigned>::min(),
            std::numeric_limits<unsigned>::max())) {
        std::cout << "tree is valid by valid_bst(node, min, max)\n";
    } else {
        std::cout << "tree is invalid by valid_bst(node, min, max)\n";
    }

    if (validate_bst(tree)) {
        std::cout << "tree is valid by validate_bst(node)\n";
    } else {
        std::cout << "tree is invalid by validate_bst(node)\n";
    }

    // test predecessor/successor
    tree::__tree_node<value_type> *pred, *succ;
    // ensure it's not in the tree
    vec.push_back(tree::random_tree_value() + tree::MAX_RAND_NUM);
    std::cout << "\nvalue\tpred\tsucc\n";
    for (std::vector<value_type>::iterator pos = vec.begin();
            pos != vec.end();
            ++pos) {
        pred = predecessor_in_bst(tree, *pos);
        succ = successor_in_bst(tree, *pos);
        std::cout << *pos << "\t"
                << (pred ? pred->value : -1) << "\t"
                << (succ ? succ->value : -1) << "\n";
    }

    tree::release_tree(tree);

    return 0;
}
