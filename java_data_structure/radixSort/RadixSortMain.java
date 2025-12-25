package radixSort;

public class RadixSortMain {
    public static void main (String[] args) {
        int[] array = new int[]{238, 283, 938, 198, 483, 737, 746, 828, 128, 256};
        printArray(radixSort(array));
    }

    public static int[] radixSort(int[] array){
        int size = array.length;
        int maxValue = max(array);

        int[] output = new int[size];
        int[] count = new int[10];
        for (int exp = 1; maxValue / exp > 0; exp *= 10){
            for (int i = 0; i < count.length; i++){
                count[i] = 0;
            }

            for (int number : array){
                int digit = (number / exp) % 10;
                count[digit]++;
            }

            for (int i = 1; i < 10; i++){
                count[i] += count[i-1];
            }

            for (int i = size - 1; i >= 0; i--){
                int digit = (array[i] / exp) % 10;
                output[count[digit] - 1] = array[i];
                count[digit]--;
            }
            System.arraycopy(output, 0, array, 0, size);
        }
        return array;
    }

    public static int max(int[] list){
        if (list.length == 0){
            return 0;
        }
        int maxValue = list[0];
        for (int i = 1; i < list.length; i++){
            int current = list[i];
            if (current > maxValue){
                maxValue = current;
            }
        }
        return maxValue;
    }

    public static void printArray(int[] array){
        System.out.print("new int[");
        System.out.print(array.length);
        System.out.print("]{");
        int lastIndex = array.length - 1;
        for (int i = 0; i < lastIndex; i++){
            System.out.print(array[i]);
            System.out.print(", ");
        }
        System.out.print(array[lastIndex]);
        System.out.println("}");
    }
}
