package tournamentSort2;

import java.util.ArrayList;
import java.util.List;

public class TournamentArray <T extends Comparable <T>> {
    private List <ArrayElement <T>> elements = new ArrayList<>();
    private List <ArrayElement <T>> sortedElements = new ArrayList<>();
    private int listSize = 0;
    private int leafStartIndex = 0;
    private int leafEndIndex = 0;

    public TournamentArray (List<T> list) {
        buildElements(list);
        initElements();
    }

    private void buildElements (List<T> list) {
        listSize = list.size();
        int powerOfTwo = getPowerOfTwo(listSize);
        leafStartIndex = powerOfTwo - 1;
        leafEndIndex = leafStartIndex + listSize - 1;

        for (int i = 0; i < powerOfTwo - 1; i++) {
            elements.add(new ArrayElement<>(null, i));
        }
        for (int i = 0; i < listSize; i++) {
            elements.add(new ArrayElement<>(list.get(i), i + leafStartIndex));
        }

        for (int i = leafEndIndex + 1; i < powerOfTwo + leafStartIndex; i++) {
            elements.add(new ArrayElement<>(null, i));
        }

    }

    private int getPowerOfTwo (int number) {
        int result = 1;
        while (result < number) {
            result = result * 2;
        }
        return result;
    }

    private void initElements() {
        int start = leafStartIndex;
        int end = leafEndIndex;

        while (start > 0) {
            for (int i = start; i <= end; i = i + 2) {
                elements.get(getParentIndex(i)).copy(selectArrayElement(i));
            }
            end = start - 1;
            start = start / 2;
        }
    }

    public List<ArrayElement <T>> sort() {
        int index;
        int parentIndex;
        ArrayElement <T> selectedElement;

        while (sortedElements.size() < listSize) {
            
            index = getTopElementAndRemove();

            while (index != 0) {
                selectedElement = selectArrayElement(index);
                parentIndex = getParentIndex(index);
                elements.get(parentIndex).copy(selectedElement);
                index = parentIndex;
            }
        }

        return sortedElements;
    }

    private int getTopElementAndRemove () {
        ArrayElement <T> element = elements.get(0);
        int index = element.getIndex();
        sortedElements.add(new ArrayElement<>(element));
        remove(index);
        return index;
    }

    private ArrayElement<T> selectArrayElement (int arrayIndex) {
        if (isRoot(arrayIndex)) {
            return elements.get(arrayIndex);
        }
        int myIndex = arrayIndex;
        int brotherindex = getBrotherIndex(arrayIndex);
        ArrayElement <T> myArrayElement = elements.get(myIndex);
        ArrayElement <T> brotherArrayElement = elements.get(brotherindex);

        if (isRemoved(myIndex) && isRemoved(brotherindex)) {
            return new ArrayElement<>(null, myIndex);
        }
        if (isRemoved(myIndex) && !isRemoved(brotherindex)) {
            return brotherArrayElement;
        }
        if (isRemoved(brotherindex) && !isRemoved(myIndex)) {
            return myArrayElement;
        }
        if (!isRemoved(myIndex) && !isRemoved(brotherindex)) {
            if (myArrayElement.getVal().compareTo(brotherArrayElement.getVal()) < 0) {
                return myArrayElement;
            }
            return brotherArrayElement;
        }
        return null;
    }

    private boolean isLeft (int arrayIndex) {
        return arrayIndex % 2 == 1;
    }

    private int getBrotherIndex (int arrayIndex) {
        if (isLeft(arrayIndex)) {
            return arrayIndex + 1;
        }
        return arrayIndex - 1;
    }

    private int getParentIndex (int arrayIndex) {
        return (arrayIndex - 1) / 2;
    }

    private boolean isRoot (int arrayIndex) {
        return arrayIndex == 0;
    }

    private boolean isRemoved(int arrayIndex) {
        return elements.get(arrayIndex).getVal() == null;
    }

    private void remove(int arrayIndex) {
        if (isRemoved(arrayIndex)) {
            return;
        }
        elements.get(arrayIndex).setVal(null);
    }

    @Override
    public String toString () {
        return elements.toString();
    }
}
