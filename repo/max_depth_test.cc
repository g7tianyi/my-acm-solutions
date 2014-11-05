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

    const int TEST_DATA_SIZE = 97;

    std::vector<value_type> vec;
    for (int i = 0; i < TEST_DATA_SIZE; ++i) {
        vec.push_back(tree::random_tree_value());
    }

    tree::__tree_node<value_type>* tree = __test_create_tree(vec,
            tree::BINARY_RANDOM_TREE);

    std::cout << tree::max_depth(tree) << std::endl;
    std::cout << tree::max_depth_iteration(tree) << std::endl;

    tree::release_tree(tree);

    return 0;
}


