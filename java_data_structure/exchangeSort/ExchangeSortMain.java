package exchangeSort;

import java.util.ArrayList;
import java.util.List;
import java.util.function.BiFunction;

public class ExchangeSortMain {
    public static void main (String[] args) {
        List<Integer> list = new ArrayList<>(List.of(238, 283, 938, 198, 483, 737, 746, 828, 128, 256));
        exchangeSort(list, (x, y) -> {return x - y;});
        System.out.println(list);
    }

    public static <T> List<T> exchangeSort(List<T> list, BiFunction<T, T, Integer> comparator){
        T anchorValue;
        T compareValue;
        for (int anchorIndex = 0; anchorIndex < list.size() - 1; anchorIndex ++){
            for (int compareIndex = anchorIndex + 1; compareIndex < list.size(); compareIndex ++){
                anchorValue = list.get(anchorIndex);
                compareValue = list.get(compareIndex);
                if (comparator.apply(anchorValue, compareValue) > 0){
                    list.set(anchorIndex, compareValue);
                    list.set(compareIndex, anchorValue);
                }
            }
        }
        return list;
    }
}
