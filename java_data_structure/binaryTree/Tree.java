public class Tree <T> {
    public enum TraversalType {
        PRE_ORDER,
        IN_ORDER,
        POST_ORDER
    }

    private TreeNode <T> root = null;

    public void setRoot (TreeNode <T> root) {
        this.root = root;
    }

    public TreeNode <T> getRoot () {
        return root;
    }

    public String traversal(TraversalType traversalType) {
        String result = "";
        if (traversalType == TraversalType.PRE_ORDER) {
            result = preOrderTraversal(root);
        } else if (traversalType == TraversalType.IN_ORDER) {
            result = inOrderTraversal(root);
        } else if (traversalType == TraversalType.POST_ORDER) {
            result = postOrderTraversal(root);
        }
        return result;
    }
    private String preOrderTraversal(TreeNode<?> parentNode) {
        if (parentNode == null) {
            return "";
        }
        return parentNode.getVal()
            + formatString(preOrderTraversal(parentNode.getLeft()), true)
            + formatString(preOrderTraversal(parentNode.getRight()), true);
    }

    private String inOrderTraversal(TreeNode<?> parentNode) {
        if (parentNode == null) {
            return "";
        }
        
        return formatString(inOrderTraversal(parentNode.getLeft()), false)
            + parentNode.getVal().toString()
            + formatString(inOrderTraversal(parentNode.getRight()), true);
    }

    private String postOrderTraversal(TreeNode<?> parentNode) {
        if (parentNode == null) {
            return "";
        }
        return formatString(postOrderTraversal(parentNode.getLeft()), false)
            + formatString(postOrderTraversal(parentNode.getRight()), false)
            + parentNode.getVal().toString();
    }


    private String formatString (String str, boolean isPrefix) {
        return (str.isBlank() || str.isEmpty()) ? "" : isPrefix ? " " + str : str + " ";
    }

    @Override
    public String toString () {
        return root.toString();
    }
}
