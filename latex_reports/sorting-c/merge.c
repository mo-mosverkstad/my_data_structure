void merge(int * org, int * aux, unsigned int lo, unsigned int mid, unsigned int hi) {
    unsigned int i = lo;
    unsigned int j = mid + 1;
    for (unsigned int k = lo; k <= hi; k++) {
        if (i > mid)
            org[k] = aux[j++];
        else if (j > hi)
            org[k] = aux[i++];
        else if (aux[i] <= aux[j])
            org[k] = aux[i++];
        else
            org[k] = aux[j++];
    }
}