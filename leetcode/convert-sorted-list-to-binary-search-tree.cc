class Solution {
public:
    TreeNode* sortedListToBST(ListNode* head) {
        if (head == NULL) {
            return NULL;
        }

        int length = 0;
        ListNode* curr = head;
        while (curr) {
            ++length;
            curr = curr->next;
        }

        return sortedListToBST(head, length);
    }
private:
    TreeNode* sortedListToBST(ListNode* head, int length) {
        if (head == NULL || length == 0) {
            return NULL;
        }
        if (length == 1) {
            return new TreeNode(head->val);
        }

        int i = 0, half = length >> 1;
        ListNode* middle = head;
        while (i < half) {
            ++i;
            middle = middle->next;
        }

        TreeNode* root = new TreeNode(middle->val);
        root->left  = sortedListToBST(head, half);
        root->right = sortedListToBST(middle->next, length - half - 1);
        return root;
    }
};

