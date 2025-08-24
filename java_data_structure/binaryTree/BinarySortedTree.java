import java.util.List;
import java.util.Optional;

public class BinarySortedTree <T extends Comparable<T>> extends Tree <T>{

    public void createSortedTree(List<T> list) {
        if (list.isEmpty()){
            return;
        }
        TreeNode<T> rootNode = new TreeNode<>(list.get(0));
        setRoot(rootNode);
        for (int i = 1; i < list.size(); i++){
            insertIntoSortedTree(list.get(i));
        }
    }

    private Optional<TreeNode<T>> searchInSortedTree(TreeNode<T> rootNode, T value) {
        TreeNode<T> currentTreeNode = rootNode;
        TreeNode<T> foundTreeNode = null;
        boolean notfinished = true;
        while (notfinished){
            if (value.compareTo(currentTreeNode.getVal()) < 0) {
                if (currentTreeNode.getLeft() == null){
                    foundTreeNode = currentTreeNode;
                    notfinished = false;
                } else {
                    currentTreeNode = currentTreeNode.getLeft();
                }
                }
            else if (value.compareTo(currentTreeNode.getVal()) > 0) {
                if (currentTreeNode.getRight() == null){
                    foundTreeNode = currentTreeNode;
                    notfinished = false;
                } else {
                    currentTreeNode = currentTreeNode.getRight();
                }
            } else {
                foundTreeNode = currentTreeNode;
                notfinished = false;
            }
        }
        return Optional.of(foundTreeNode);
    }

    public Optional<TreeNode<T>> findInSortedTree(T value) {
        Optional<TreeNode<T>> foundTreeNode = searchInSortedTree(getRoot(), value);
        if (foundTreeNode.isPresent() && value.compareTo(foundTreeNode.get().getVal()) == 0) {
            return foundTreeNode;
        }
        return Optional.empty();
    }

    public void insertIntoSortedTree(T value) {
        Optional<TreeNode<T>> parentTreeNodeOptional = searchInSortedTree(getRoot(), value);
        if (parentTreeNodeOptional.isEmpty()) {
            setRoot(new TreeNode<>(value));
        } else {
            TreeNode<T> parentTreeNode = parentTreeNodeOptional.get();
            TreeNode<T> newNode = new TreeNode<>(value);
            if (value.compareTo(parentTreeNode.getVal()) < 0) {
                parentTreeNode.setLeft(newNode);
            } else if (value.compareTo(parentTreeNode.getVal()) > 0){
                parentTreeNode.setRight(newNode);
            }
        }
    }

    public void deleteFromSortedTree(T value) {
        Optional<TreeNode<T>> treeNodeOptional = findInSortedTree(value);
        if (treeNodeOptional.isEmpty()) {
            return;
        }
        TreeNode<T> treeNode = treeNodeOptional.get();
        TreeNode<T> parentTreeNode = treeNode.getParent();
        
        if (treeNode.getLeft() == null && treeNode.getRight() == null){
            if (parentTreeNode == null){
                setRoot(new TreeNode<T>(null));
            }
            else{
                if (parentTreeNode.getLeft() == treeNode) {
                    parentTreeNode.deleteLeft();
                } else if (parentTreeNode.getRight() == treeNode){
                    parentTreeNode.deleteRight();
                }
            }
        }
        else if (treeNode.getLeft() != null && treeNode.getRight() == null){
            TreeNode<T> replaceTreeNode = treeNode.getLeft();
            treeNode.deleteLeft();
            if (parentTreeNode == null) {
                setRoot(replaceTreeNode);
            }
            else{
                if (parentTreeNode.getLeft() == treeNode) {
                    parentTreeNode.setLeft(replaceTreeNode);
                }
                else if (parentTreeNode.getRight() == treeNode){
                    parentTreeNode.setRight(replaceTreeNode);
                }
            }
        }
        else if (treeNode.getLeft() == null && treeNode.getRight() != null){
            TreeNode<T> replaceTreeNode = treeNode.getRight();
            treeNode.deleteRight();
            // System.out.println(treeNode);
            if (parentTreeNode == null) {
                setRoot(replaceTreeNode);
            }
            else{
                if (parentTreeNode.getLeft() == treeNode) {
                    parentTreeNode.setLeft(replaceTreeNode);
                }
                else if (parentTreeNode.getRight() == treeNode){
                    parentTreeNode.setRight(replaceTreeNode);
                }
            }
        }
        else if (treeNode.getLeft() != null && treeNode.getRight() != null){
            TreeNode<T> replaceTreeNode = treeNode.getLeft();
            while (replaceTreeNode.getRight() != null) {
                replaceTreeNode = replaceTreeNode.getRight();
            }
            if (replaceTreeNode.getLeft() != null){
                TreeNode<T> subReplaceTreeNode = replaceTreeNode.getLeft();
                replaceTreeNode.deleteLeft();
                replaceTreeNode.getParent().setRight(subReplaceTreeNode);
            }
            TreeNode<T> replaceTreeNodeParent = replaceTreeNode.getParent();
            if (replaceTreeNodeParent.getLeft() == replaceTreeNode) {
                replaceTreeNodeParent.deleteLeft();
            }
            else if (replaceTreeNodeParent.getRight() == replaceTreeNode){
                replaceTreeNodeParent.deleteRight();
            }
            treeNode.setVal(replaceTreeNode.getVal());
        }
    }

}
