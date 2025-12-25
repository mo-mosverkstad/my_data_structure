public class TreeNode <T>{

    private static String TREE_FORMAT = "TreeNode{val=%s, left=%s, right=%s, parent=%s}";

    private T val = null;
    private TreeNode <T> left = null;
    private TreeNode <T> right = null;
    private TreeNode <T> parent = null;

    public TreeNode (T val) {
        this.val = val;
        this.left = null;
        this.right = null;
        this.parent = null;
    }

    public TreeNode (T val, TreeNode <T> left, TreeNode <T> right) {
        this.val = val;
        this.left = left;
        this.right = right;
        this.parent = null;
    }


    public void setVal (T val) {
        this.val = val;
    }

    public T getVal () {
        return val;
    }

    protected void setParent (TreeNode <T> parent) {
        this.parent = parent;
    }

    public TreeNode<T> getParent () {
        return parent;
    }

    public void setLeft (TreeNode <T> left) {
        if (left == null) {
            return;
        }
        left.setParent(this);
        this.left = left;
    }

    public void deleteLeft() {
        this.left = null;
    }

    public TreeNode <T> getLeft () {
        return left;
    }

    public void setRight (TreeNode <T> right) {
        if (right == null) {
            return;
        }
        right.setParent(this);
        this.right = right;
    }

    public void deleteRight() {
        this.right = null;
    }

    public TreeNode <T> getRight () {
        return right;
    }

    public boolean isLeftChild () {
        return parent != null && parent.getLeft() == this;
    }

    public boolean isRightChild () {
        return parent != null && parent.getRight() == this;
    }
    
    @Override
    public String toString() {
        return String.format(TREE_FORMAT, val, left, right, parent==null?"":parent.getVal());
    }
} 