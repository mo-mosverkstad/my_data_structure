import java.util.List;

public class BinaryTreeMain {
    public static void main(String[] args) {
        /*
        Tree <Integer> tree = generateTree();
        System.out.println(tree);

        Tree <String> tree2 = generateTree2();
        
        System.out.println(Tree.preOrderTraversal(tree2.getRoot()));
        System.out.println(Tree.preOrderTraversal(tree2.getRoot()).equals("A B D I J E K C F H"));
        System.out.println(Tree.inOrderTraversal(tree2.getRoot()));
        System.out.println(Tree.inOrderTraversal(tree2.getRoot()).equals("I D J B K E A F C H"));
        System.out.println(Tree.postOrderTraversal(tree2.getRoot()));
        System.out.println(Tree.postOrderTraversal(tree2.getRoot()).equals("I J D K E B F H C A"));
        */
        List <Integer> integerList = List.of(18, 29, 129, 232, 321, 913, 232, 388, 383, 281, 128, 828, 727, 393, 482);
        Tree <Integer> sortedIntegerTree = Tree.createSortedTree(integerList, (a, b) -> a - b);
        System.out.println(Tree.inOrderTraversal(sortedIntegerTree.getRoot()));

        List<String> stringList = List.of("grape", "banana", "apple", "fig", "apricot", "cherry", "plum", "orange", "kiwi", "pear");
        Tree<String> sortedStringTree = Tree.createSortedTree(stringList, (a, b) -> a.compareTo(b));
        System.out.println(Tree.inOrderTraversal(sortedStringTree.getRoot()));

    }

    private static Tree <Integer> generateTree() {
        Tree <Integer> tree = new Tree <Integer> ();
        tree.setRoot(new TreeNode <Integer> (1));
        tree.getRoot().setLeft(new TreeNode <Integer> (2));
        tree.getRoot().setRight(new TreeNode <Integer> (3));
        tree.getRoot().getLeft().setLeft(new TreeNode <Integer> (4));
        tree.getRoot().getLeft().setRight(new TreeNode <Integer> (5));
        tree.getRoot().getRight().setLeft(new TreeNode <Integer> (6));
        tree.getRoot().getRight().setRight(new TreeNode <Integer> (7));
        return tree;
    }

    private static Tree <String> generateTree2() {
        Tree <String> tree = new Tree <String> ();
        tree.setRoot(new TreeNode <String> ("A"));
        tree.getRoot().setLeft(new TreeNode <String> ("B"));
        tree.getRoot().setRight(new TreeNode <String> ("C"));
        tree.getRoot().getLeft().setLeft(new TreeNode <String> ("D"));
        tree.getRoot().getLeft().setRight(new TreeNode <String> ("E"));
        tree.getRoot().getLeft().getLeft().setLeft(new TreeNode <String> ("I"));
        tree.getRoot().getLeft().getLeft().setRight(new TreeNode <String> ("J"));
        tree.getRoot().getLeft().getRight().setLeft(new TreeNode <String> ("K"));

        tree.getRoot().getRight().setLeft(new TreeNode <String> ("F"));
        tree.getRoot().getRight().setRight(new TreeNode <String> ("H"));
        return tree;
    }
}
