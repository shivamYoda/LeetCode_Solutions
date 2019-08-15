// Link to the problem : https://leetcode.com/problems/leaf-similar-trees/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

class InOrderIterator {
    public:
        TreeNode* currentLeaf;
        TreeNode* root;
        stack<TreeNode*> ancestors;
        
    InOrderIterator(TreeNode* root)  {
        this->root = root;
        this->currentLeaf = NULL;
    }
    
    TreeNode* nextLeaf() {
        
        if(this->currentLeaf == NULL) {
            this->currentLeaf = this->firstLeaf(this->root);
            return currentLeaf;
        }
        
        TreeNode* parent = firstParentWithRightSubTree(this->currentLeaf);
        if(parent != NULL)
        this->currentLeaf = this->firstLeaf(parent->right);
        else
        this->currentLeaf = this->firstLeaf(this->root);
        return currentLeaf;
    }
    
    private:
        TreeNode* firstLeaf(TreeNode* root) {

            if(root->left==NULL && root->right == NULL) {
                return root;
            }
            this->ancestors.push(root);
            if(root->left != NULL)
                return firstLeaf(root->left);
            if(root->right != NULL)
                return firstLeaf(root->right);
            
            return root;
        }
    
        TreeNode* firstParentWithRightSubTree(TreeNode* node) {
            
            if(this->ancestors.size() == 0) {
                return NULL;
            }
            
            TreeNode* parent = this->ancestors.top();
            if(parent == this->root) 
            {
                if(parent->right != NULL && parent->right != node)
                    return parent;
                else
                    return NULL;
            }
            
            if(parent->right == node) {
                this->ancestors.pop();
                return firstParentWithRightSubTree(parent);
            } else if(parent->left == node) {
                
                if(parent->right != NULL) {
                    return parent;
                } else {
                    this->ancestors.pop();
                    return firstParentWithRightSubTree(parent);
                }
            }
            return NULL;
        }
    
};

class Solution {
public:
    bool leafSimilar(TreeNode* root1, TreeNode* root2) {
        InOrderIterator *it1 =  new InOrderIterator(root1);
        InOrderIterator *it2 =  new InOrderIterator(root2);
        
        TreeNode* firstLeaf1 = it1->nextLeaf();
        TreeNode* firstLeaf2 = it2->nextLeaf();
        
        if(firstLeaf1->val != firstLeaf2->val) {
            return false;
        }
        
        
        while(it1->nextLeaf()->val == it2->nextLeaf()->val && it1->currentLeaf != firstLeaf1) {}
        
        if(it1->currentLeaf == firstLeaf1 && it2->currentLeaf->val == firstLeaf1->val) {
            return true;
        } else {
            return false;
        }
        
        
    }
};
