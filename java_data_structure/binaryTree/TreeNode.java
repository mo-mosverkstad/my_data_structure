public class TreeNode <T>{

    private static String TREE_FORMAT = "TreeNode{val=%s, left=%s, right=%s}";

    public T val;
    public TreeNode <T> left;
    public TreeNode <T> right;

    public TreeNode (T val) {
        this.val = val;
        this.left = null;
        this.right = null;
    }

    public TreeNode (T val, TreeNode <T> left, TreeNode <T> right) {
        this.val = val;
        this.left = left;
        this.right = right;
    }

    public void setVal (T val) {
        this.val = val;
    }

    public T getVal () {
        return val;
    }

    public void setLeft (TreeNode <T> left) {
        this.left = left;
    }

    public void setRight (TreeNode <T> right) {
        this.right = right;
    }

    public TreeNode <T> getLeft () {
        return left;
    }

    public TreeNode <T> getRight () {
        return right;
    }

    @Override
    public String toString() {
        return String.format(TREE_FORMAT, val, left, right);
    }
} 