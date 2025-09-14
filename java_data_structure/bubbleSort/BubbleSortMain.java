package bubbleSort;

import java.util.ArrayList;
import java.util.List;
import java.util.function.BiFunction;

public class BubbleSortMain {
    public static void main (String[] args) {
        List<Integer> list = new ArrayList<>(List.of(238, 283, 938, 198, 483, 737, 746, 828, 128, 256));
        bubbleSort(list, (x, y) -> {return x - y;});
        System.out.println(list);
    }

    public static <T> List<T> bubbleSort(List<T> list, BiFunction<T, T, Integer> comparator){
        T first;
        T second;
        for (int endIndex = 0; endIndex < list.size() - 1; endIndex ++){
            for (int startIndex = list.size() - 1; startIndex > endIndex; startIndex--){
                first = list.get(startIndex);
                second = list.get(startIndex - 1);
                if (comparator.apply(first, second) < 0){
                    list.set(startIndex, second);
                    list.set(startIndex - 1, first);
                }
            }
        }
        return list;
    }
}
