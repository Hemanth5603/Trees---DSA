



int height(TreeNode* node, int &diameter){
    if(!node) return 0;

    int lh = height(node->left, diameter);
    int rh = height(node->right, diameter);

    diameter = max(diameter,lh + rh);
    return 1+ max(lh, rh);
}