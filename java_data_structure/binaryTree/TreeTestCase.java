import java.util.List;

public class TreeTestCase {
    private static final String TEST_RESULT_FORMAT = "%s: %b";

    public static boolean testIntegerTree() {
        TreeTest <Integer> test = new TreeTest<>();
        boolean result = true;
        // configure
        test.buildTree(List.of(388, 128, 727, 232, 29, 129, 321, 913, 232,383, 281, 828, 393, 482, 18));
        // test step 01: action, response, expected
        result &= test.testTraversals(Tree.TraversalType.IN_ORDER, "18 29 128 129 232 281 321 383 388 393 482 727 828 913");
        System.out.println(String.format(TEST_RESULT_FORMAT, "testIntegerTreeInOrderTraversal", result));

        // test step 02: action, response, expected
        result &= testDeleteInTree(test, 321, "18 29 128 129 232 281 383 388 393 482 727 828 913");

        // test step 03: action, response, expected
        result &= testDeleteInTree(test, 388, "18 29 128 129 232 281 383 393 482 727 828 913");

        // test step 04: action, response, expected
        result &= testDeleteInTree(test, 913, "18 29 128 129 232 281 383 393 482 727 828");

        // test step 05: action, response, expected
        result &= testDeleteInTree(test, 393, "18 29 128 129 232 281 383 482 727 828");

        // test step 06: action, response, expected
        result &= testDeleteInTree(test, 29, "18 128 129 232 281 383 482 727 828");

        // test step 06: action, response, expected
        result &= testDeleteInTree(test, 128, "18 129 232 281 383 482 727 828");

        // test step 06: action, response, expected
        result &= testDeleteInTree(test, 888, "18 129 232 281 383 482 727 828");

        // test step 06: action, response, expected
        result &= testDeleteInTree(test, 383, "18 129 232 281 482 727 828");

        return result;
    }

    private static boolean testDeleteInTree(TreeTest <Integer> test, Integer value, String expectedString) {
        test.getTree().deleteFromSortedTree(value);
        boolean result = test.testTraversals(Tree.TraversalType.IN_ORDER, expectedString);
        System.out.println(String.format(TEST_RESULT_FORMAT, "delete "+ value, result));
        return result;
    }

    public static boolean testStringTree() {
        TreeTest <String> test = new TreeTest<>();
        boolean result = true;
        // configure
        test.buildTree(List.of("grape", "banana", "apple", "fig", "apricot", "cherry", "plum", "orange", "kiwi", "pear"));
        // test step 01: action, response, expected
        result &= test.testTraversals(Tree.TraversalType.IN_ORDER, "apple apricot banana cherry fig grape kiwi orange pear plum");
        System.out.println(String.format(TEST_RESULT_FORMAT, "testStringTreeInOrderTraversal", result));
        return result;
    }
}
