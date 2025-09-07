package tournamentSort;

import java.util.ArrayList;
import java.util.List;
import java.util.function.BiFunction;

public class TournamentSort {
    public static void main(String[] args) {
        List<Integer> list = List.of(4127, 6247, 1058, 4339, 1209, 6331, 7231, 7490, 2627, 7030, 9724, 4629, 4445, 1167, 3581, 8290, 1526, 4660, 9721, 6056, 2298, 7313, 9816, 7270, 6552, 2961, 1836, 4708, 5672, 6210, 5922, 7828, 1567, 5310, 7113, 8528, 1712, 2419, 5947, 9453, 4381, 1924, 1655, 1258, 6878, 6989, 2634, 9436, 4553, 6631, 9067, 4747, 9936, 7166, 4172, 6018, 7615, 8836, 5756, 6144, 8783, 8089, 9580, 4378, 6987, 4900, 5536, 5174, 1006, 5218, 9025, 3093, 8676, 1778, 8614, 5025, 8621, 2044, 9526, 1257, 4284, 6222, 7499, 7087, 2478, 5468, 2148, 7135, 4218, 9717, 1429, 8364, 2320, 3395, 9012, 4137, 8985, 2827, 1578, 5611);
        System.out.println(tournamentSort(list, (o1, o2) -> o1 - o2));
    }

    
    public static <T> ArrayList<T> tournamentSort(List<T> array, BiFunction<T, T, Integer> comparator) {
        int fitArraySize = nextPowerOfTwo(array.size());
        int fitArraySizeMinusOne = fitArraySize - 1;
        int size = fitArraySize + fitArraySizeMinusOne;
        ArrayList<T> binaryTreeArray = new ArrayList<>(size);
        ArrayList<Integer> indexArray = new ArrayList<>(fitArraySizeMinusOne);

        // Filling up the binary tree array
        for (int i = 0; i < fitArraySizeMinusOne; i++) {
            binaryTreeArray.add(null);
        }
        for (int i = 0; i < array.size(); i++){
            binaryTreeArray.add(array.get(i));
        }

        // Filling up the index array
        for (int i = 0; i < fitArraySizeMinusOne; i++) {
            indexArray.add(0);
        }

        // First traversal of the binary tree array
        int sortBound = fitArraySizeMinusOne - 1;
        for (int i = size - 1; i > sortBound; i = i - 2) {
            int leftIndex = i - 1;
            int rightIndex = i;
            int parentIndex = (i - 1) / 2;
            T left = leftIndex < binaryTreeArray.size() ? binaryTreeArray.get(leftIndex) : null;
            T right = rightIndex < binaryTreeArray.size() ? binaryTreeArray.get(rightIndex) : null;
            if (left != null && right != null) {
                if (comparator.apply(left, right) <= 0) {
                    binaryTreeArray.set(parentIndex, left);
                    indexArray.set(parentIndex, leftIndex);
                } else {
                    binaryTreeArray.set(parentIndex, right);
                    indexArray.set(parentIndex, rightIndex);
                }
            }
            else if (left != null) {
                binaryTreeArray.set(parentIndex, left);
                indexArray.set(parentIndex, leftIndex);
            }
            else if (right != null) {
                binaryTreeArray.set(parentIndex, right);
                indexArray.set(parentIndex, rightIndex);
            }
            else {
                binaryTreeArray.set(parentIndex, null);
            }
        }
        for (int i = sortBound; i > 0; i -= 2){
            int leftIndex = i - 1;
            int rightIndex = i;
            int parentIndex = (i - 1) / 2;
            T left = leftIndex < binaryTreeArray.size() ? binaryTreeArray.get(leftIndex) : null;
            T right = rightIndex < binaryTreeArray.size() ? binaryTreeArray.get(rightIndex) : null;
            if (left != null && right != null) {
                if (comparator.apply(left, right) <= 0) {
                    binaryTreeArray.set(parentIndex, left);
                    indexArray.set(parentIndex, indexArray.get(leftIndex));
                } else {
                    binaryTreeArray.set(parentIndex, right);
                    indexArray.set(parentIndex, indexArray.get(rightIndex));
                }
            }
            else if (left != null) {
                binaryTreeArray.set(parentIndex, left);
                indexArray.set(parentIndex, indexArray.get(leftIndex));
            }
            else if (right != null) {
                binaryTreeArray.set(parentIndex, right);
                indexArray.set(parentIndex, indexArray.get(rightIndex));
            }
            else {
                binaryTreeArray.set(parentIndex, null);
                indexArray.set(parentIndex, 0);
            }
        }

        ArrayList<T> result = new ArrayList<>();

        T lowest = binaryTreeArray.get(0);
        int lowestIndex = indexArray.get(0);

        int cycle = 0;
        while (lowestIndex != 0 && cycle < 1000){
            // Remove the lowest element and update the tree
            binaryTreeArray.set(lowestIndex, null);
            int lowestAdjacentIndex = lowestIndex % 2 == 0 ? lowestIndex - 1 : lowestIndex + 1;
            T lowestAdjacent = lowestAdjacentIndex < binaryTreeArray.size() ? binaryTreeArray.get(lowestAdjacentIndex) : null;
            int parentIndex = (lowestIndex - 1) / 2;
            binaryTreeArray.set(parentIndex, lowestAdjacent);
            indexArray.set(parentIndex, lowestAdjacentIndex);

            int index = parentIndex;
            T current = null;
            int currentIndex = 0;
            T adjacent = null;
            int adjacentIndex = 0;
            while (index > 0){
                current = binaryTreeArray.get(index);
                currentIndex = index;
                adjacentIndex = index % 2 == 0 ? index - 1 : index + 1;
                adjacent = binaryTreeArray.get(adjacentIndex);
                index = (index - 1) / 2;

                if (current != null && adjacent != null){
                    if (comparator.apply(current, adjacent) <= 0) {
                        binaryTreeArray.set(index, current);
                        indexArray.set(index, indexArray.get(currentIndex));
                    }
                    else{
                        binaryTreeArray.set(index, adjacent);
                        indexArray.set(index, indexArray.get(adjacentIndex));
                    }
                }
                else if (current != null) {
                    binaryTreeArray.set(index, current);
                    indexArray.set(index, indexArray.get(currentIndex));
                }
                else if (adjacent != null) {
                    binaryTreeArray.set(index, adjacent);
                    indexArray.set(index, indexArray.get(adjacentIndex));
                }
                else {
                    binaryTreeArray.set(index, null);
                    indexArray.set(index, 0);
                }
            }
            lowest = binaryTreeArray.get(0);
            lowestIndex = indexArray.get(0);

            if (lowest != null){
                result.add(lowest);
            }
            cycle++;
        }

        return result;
    }

    public static <T> void prettyPrint(ArrayList<T> binaryTreeArray){
        int index = 0;
        int count = 1;
        while (index < binaryTreeArray.size()){
            for (int i = index; i < index + count && i < binaryTreeArray.size(); i++){
                System.out.print(binaryTreeArray.get(i) + " ");
            }
            System.out.print('\n');
            index += count;
            count *= 2;
        }
    }

    public static int nextPowerOfTwo(int x) {
        if (x <= 0) return 1;
        x--;
        x |= x >> 1;
        x |= x >> 2;
        x |= x >> 4;
        x |= x >> 8;
        x |= x >> 16;
        return x + 1;
    }
}
