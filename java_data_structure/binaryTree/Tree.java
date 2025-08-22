import java.util.List;
import java.util.function.BiFunction;
import java.util.function.BiPredicate;

public class Tree <T> {
    private TreeNode <T> root;

    public void setRoot (TreeNode <T> root) {
        this.root = root;
    }

    public TreeNode <T> getRoot () {
        return root;
    }

    public static String preOrderTraversal(TreeNode<?> parentNode) {
        if (parentNode == null) {
            return "";
        }
        return parentNode.getVal()
            + formatString(preOrderTraversal(parentNode.getLeft()), true)
            + formatString(preOrderTraversal(parentNode.getRight()), true);
    }

    public static String inOrderTraversal(TreeNode<?> parentNode) {
        if (parentNode == null) {
            return "";
        }
        
        return formatString(inOrderTraversal(parentNode.getLeft()), false)
            + parentNode.getVal().toString()
            + formatString(inOrderTraversal(parentNode.getRight()), true);
    }

    public static String postOrderTraversal(TreeNode<?> parentNode) {
        if (parentNode == null) {
            return "";
        }
        return formatString(postOrderTraversal(parentNode.getLeft()), false)
            + formatString(postOrderTraversal(parentNode.getRight()), false)
            + parentNode.getVal().toString();
    }

    public static <U> Tree<U> createSortedTree(List<U> list, BiFunction<U, U, Integer> comparator) {
        if (list.isEmpty()){
            return null;
        }
        Tree<U> tree = new Tree<>();
        TreeNode<U> rootNode = new TreeNode<>(list.get(0));
        tree.setRoot(rootNode);
        for (int i = 1; i < list.size(); i++){
            TreeNode<U> insertionTreeNode = new TreeNode<>(list.get(i));
            U insertionTreeNodeValue = insertionTreeNode.getVal();
            TreeNode<U> currentTreeNode = rootNode;
            U currentTreeNodeValue = rootNode.getVal();
            boolean notfinished = true;
            while (notfinished){
                
                if (comparator.apply(insertionTreeNodeValue, currentTreeNodeValue) < 0){
                    if (currentTreeNode.getLeft() == null){
                        currentTreeNode.setLeft(insertionTreeNode);
                        notfinished = false;
                    } else {
                        currentTreeNode = currentTreeNode.getLeft();
                        currentTreeNodeValue = currentTreeNode.getVal();
                    }
                }
                else{
                    if (currentTreeNode.getRight() == null){
                        currentTreeNode.setRight(insertionTreeNode);
                        notfinished = false;
                    } else {
                        currentTreeNode = currentTreeNode.getRight();
                        currentTreeNodeValue = currentTreeNode.getVal();
                    }
                }
            }
        }
        return tree;
    }

    public static <U> void insertIntoSortedTree() {
        
    }

    private static String formatString (String str, boolean isPrefix) {
        return (str.isBlank() || str.isEmpty()) ? "" : isPrefix ? " " + str : str + " ";
    }

    @Override
    public String toString () {
        return root.toString();
    }
}
