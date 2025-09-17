package mergeSort;

import java.util.ArrayList;
import java.util.List;
import java.util.function.BiFunction;

public class MergeSortMain {
    public static void main(String[] args){
        BiFunction<Integer, Integer, Integer> comparator = (x, y) -> {return x - y;};
        /*
        List<Integer> list1 = new ArrayList<>(){{add(1); add(2); add(7); add(11);}};
        List<Integer> list2 = new ArrayList<>(){{add(3); add(5); add(6); add(9); add(10); add(15);}};
        System.out.println(mergeSortedLists(list1, list2, comparator));
        */
        
        ArrayList<Integer> list = new ArrayList<>(List.of(238, 283, 938, 198, 483, 737, 746, 828, 128));
        System.out.println(mergeSort(list, comparator));
        
    }

    public static <T> List<T> mergeSort(List<T> list, BiFunction<T, T, Integer> comparator){
        int size = list.size();
        if (size <= 1){
            return list;
        }
        else if (size == 2){
            T value0 = list.get(0);
            T value1 = list.get(1);
            if (comparator.apply(value0, value1) > 0){
                list.set(0, value1);
                list.set(1, value0);
            }
            return list;
        }
        int halfSize = size / 2;
        List<T> list1 = list.subList(0, halfSize);
        List<T> list2 = list.subList(halfSize, size);
        return mergeSortedLists(mergeSort(list1, comparator), mergeSort(list2, comparator), comparator);
    }

    private static <T> List<T> mergeSortedLists(List<T> list1, List<T> list2, BiFunction<T, T, Integer> comparator){
        int list1size = list1.size();
        int list2size = list2.size();

        List<T> list = new ArrayList<>(list1size + list2size);
        int index1 = 0;
        int index2 = 0;

        while (index1 < list1size && index2 < list2size){
            T value1 = list1.get(index1);
            T value2 = list2.get(index2);
            if (comparator.apply(value1, value2) > 0){
                list.add(value2);
                index2++;
            }
            else{
                list.add(value1);
                index1++;
            }
        }
        while (index1 < list1size) {
            list.add(list1.get(index1));
            index1++;
        }
        while (index2 < list2size) {
            list.add(list2.get(index2));
            index2++;
        }
        return list;
    }
}
