import java.util.List;

public class TreeTest <T extends Comparable<T>> {

    private BinarySortedTree <T> tree = new BinarySortedTree<>();

    public void buildTree(List<T> list) {
        tree.createSortedTree(list);
    }

    public boolean testTraversals(Tree.TraversalType traversalType, String expectedResult) {
        // System.out.println(tree.traversal(traversalType));
        // System.out.println(expectedResult);
        return tree.traversal(traversalType).equalsIgnoreCase(expectedResult);
    }

    public BinarySortedTree <T> getTree() {
        return tree;
    }
}
