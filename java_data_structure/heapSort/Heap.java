package heapSort;

import java.util.ArrayList;
import java.util.List;
import java.util.function.BiFunction;

public class Heap<T> {
    private static final int ROOT_NODE_INDEX = 0;
    private ArrayList<T> heap;
    private BiFunction <T, T, Integer> comparator;

    // Creating empty heap
    public Heap(Integer heapSize, BiFunction<T, T, Integer> comparator){
        this.comparator = comparator;
        heap = new ArrayList<>(heapSize);
    }

    // Heapifization
    public Heap(List<T> list, BiFunction<T, T, Integer> comparator){
        this.comparator = comparator;
        int heapSize = list.size();
        heap = new ArrayList<>(heapSize);
        for (T value: list){
            heap.add(value);
        }

        for (int i = heapSize / 2 - 1; i >= 0; i--){
            filterDown(i);
        }
    }

    public T getRoot(){
        return heap.isEmpty() ? null : heap.get(ROOT_NODE_INDEX);
    }

    public void insert(T value){
        int insertionIndex = heap.size();
        heap.add(value);
        filterUp(insertionIndex);
    }

    public void deleteRoot(){
        T lastNode = heap.removeLast();
        if (heap.isEmpty()) return;
        heap.set(ROOT_NODE_INDEX, lastNode);
        filterDown(ROOT_NODE_INDEX);
    }

    private void filterDown(int currentIndex){
        int heapSize = heap.size();
        if (heapSize <= 1){
            return;
        }

        boolean continueFilterDown = true;
        while (continueFilterDown){
            continueFilterDown = false;
            int leftChildIndex = 2 * currentIndex + 1;
            int rightChildIndex = 2 * currentIndex + 2;
            T current = heap.get(currentIndex);
            T leftChild = heap.get(leftChildIndex);
            T rightChild = rightChildIndex < heapSize ? heap.get(rightChildIndex) : null;

            int smallestChildIndex;
            T smallestChild;
            if (rightChild == null){
                smallestChildIndex = leftChildIndex;
                smallestChild = leftChild;
            }
            else{
                if (comparator.apply(leftChild, rightChild) > 0){
                    smallestChildIndex = rightChildIndex;
                    smallestChild = rightChild;
                }
                else{
                    smallestChildIndex = leftChildIndex;
                    smallestChild = leftChild;
                }
            }
            
            if (comparator.apply(current, smallestChild) > 0){
                heap.set(currentIndex, smallestChild);
                heap.set(smallestChildIndex, current);
                currentIndex = smallestChildIndex;
                continueFilterDown = 2 * currentIndex + 1 < heapSize;
            }
        }
    }

    private void filterUp(int currentIndex){
        T current = heap.get(currentIndex);
        int parentIndex = (currentIndex - 1) / 2;
        T parent = heap.get(parentIndex);
        while (currentIndex != parentIndex && comparator.apply(current, parent) < 0){
            heap.set(currentIndex, parent);
            heap.set(parentIndex, current);
            currentIndex = parentIndex;
            current = heap.get(currentIndex);
            parentIndex = (currentIndex - 1) / 2;
            parent = heap.get(parentIndex);
        }
    }

    public String toString(){
        StringBuilder stringBuilder = new StringBuilder();
        int index = 0;
        int count = 1;
        while (index < heap.size()){
            for (int i = index; i < index + count && i < heap.size(); i++){
                stringBuilder.append(heap.get(i) + " ");
            }
            stringBuilder.append('\n');
            index += count;
            count *= 2;
        }
        return stringBuilder.toString();
    }
}
