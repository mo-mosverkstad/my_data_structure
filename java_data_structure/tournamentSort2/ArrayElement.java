package tournamentSort2;

public class ArrayElement <T extends Comparable<T>> {
    private T val;
    private int index;

    public ArrayElement (T val, int index) {
        this.val = val;
        this.index = index;
    }

    public ArrayElement (ArrayElement <T> element) {
        this.val = element.getVal();
        this.index = element.getIndex();
    }
    
    public T getVal () {
        return val;
    }

    public int getIndex () {
        return index;
    }

    public void setVal (T val) {
        this.val = val;
    }

    public void setIndex (int index) {
        this.index = index;
    }

    public void copy (ArrayElement <T> element) {
        this.val = element.getVal();
        this.index = element.getIndex();
    }

    @Override
    public String toString () {
        return String.format("(%d, %d)", val, index);
    }
}
