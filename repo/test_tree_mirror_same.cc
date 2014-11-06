#include "tree.hpp"

typedef tree::default_value_type value_type;

int main() {

    const int TEST_DATA_SIZE = 17;

    std::vector<value_type> vec;
    for (int i = 0; i < TEST_DATA_SIZE; ++i) {
        vec.push_back(tree::random_tree_value() + 1);
    }

    tree::binary_search_tree_optioner<value_type> bst;
    tree::tree_node<value_type>* tree1 = tree::create_tree(vec.begin(), vec.end(), bst);
    std::cout << "in order   : ", tree::in_order(tree1),    std::cout << std::endl;
    std::cout << "pre order  : ", tree::pre_order(tree1),   std::cout << std::endl;
    std::cout << "post order : ", tree::post_order(tree1),  std::cout << std::endl;
    std::cout << "level order: ", tree::level_order(tree1), std::cout << std::endl;
    std::cout << std::endl;

    tree::tree_node<value_type>* tree2 = tree::create_mirror(tree1);
    std::cout << "in order   : ", tree::in_order(tree2),    std::cout << std::endl;
    std::cout << "pre order  : ", tree::pre_order(tree2),   std::cout << std::endl;
    std::cout << "post order : ", tree::post_order(tree2),  std::cout << std::endl;
    std::cout << "level order: ", tree::level_order(tree2), std::cout << std::endl;
    std::cout << std::endl;

    tree::tree_node<value_type>* tree3 = tree::create_mirror_iteratively(tree1);
    std::cout << "in order   : ", tree::in_order(tree3),    std::cout << std::endl;
    std::cout << "pre order  : ", tree::pre_order(tree3),   std::cout << std::endl;
    std::cout << "post order : ", tree::post_order(tree3),  std::cout << std::endl;
    std::cout << "level order: ", tree::level_order(tree3), std::cout << std::endl;
    std::cout << std::endl;

    std::cout << "tree1 and tree2 is " << (tree::is_mirror(tree1, tree2) ? "" : "not ")
            << "mirror\n";
    std::cout << "tree1 and tree3 is " << (tree::is_mirror_iterative(tree1, tree3) ? "" :
            "not ") << "mirror\n";

    std::cout << std::endl;
    std::cout << "tree1 and tree1 is " << (tree::is_same_tree(tree1, tree1) ? "" : "not ")
            << "same tree\n";
    std::cout << "tree1 and tree2 is " << (tree::is_same_tree(tree1, tree2) ? "" : "not ")
            << "same tree\n";
    std::cout << "tree1 and tree1 is "
            << (tree::is_same_tree_iterative(tree1, tree1) ? "" : "not ")
            << "same tree\n";

    release_tree(tree3);
    release_tree(tree2);
    release_tree(tree1);

    return 0;
}

