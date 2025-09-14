package heapSort;
import java.util.ArrayList;
import java.util.List;
import java.util.function.BiFunction;

public class HeapSortMain {
    public static void main(String[] args){
        heapTest();
    }

    public static void heapTest(){
        List<Integer> list = new ArrayList<>(List.of(238, 283, 938, 198, 483, 737, 746, 828, 128, 256));
        Heap<Integer> heap = new Heap<>(list, (x, y) -> {return x - y;});
        heap.insert(138);
        heap.insert(532);
        heap.insert(711);
        heap.deleteRoot();
        System.out.println(heap);
    }

    public static void heapSortTest(){
        List<Integer> list = new ArrayList<>(List.of(238, 283, 938, 198, 483, 737, 746, 828, 128, 256));
        heapSort(list, (x, y) -> {return x - y;});
        System.out.println(list);
    }

    public static <T> List<T> heapSort(List<T> list, BiFunction<T, T, Integer> comparator){
        Heap<T> heap = new Heap<>(list, comparator);
        list.clear();
        T root = heap.getRoot();
        while (root != null){
            list.add(root);
            heap.deleteRoot();
            root = heap.getRoot();
        }
        return list;
    }
}
