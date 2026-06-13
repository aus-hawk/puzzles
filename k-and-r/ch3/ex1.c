int binsearch(int x, int v[], int n) {
    int low, high, mid;

    low = 0;
    high = n - 1;
    // Make sure that mid isn't garbage.
    mid = (low + high) / 2;
    while (x != v[mid] && low <= high) {
        if (x < v[mid]) {
            high = mid - 1;
        } else {
            low = mid + 1;
        }
        mid = (low + high) / 2;
    }

    return (x == v[mid]) ? mid : -1;
}
