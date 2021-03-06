#include <cassert>
#include <cstdlib>
#include <iostream>
#include <vector>

using namespace std;

void prt(vector<int>& v) {
    for(auto& x: v)
        cout << x  << " ";
    cout << endl;
}

void selection_sort(vector<int>& v) {
    // select the min and put to current position
    for(int i = 0; i < v.size(); i++) {
        int min = i;
        for(int j = i+1; j < v.size(); j++) {
            if(v[j] < v[min]) {
                min = j;
            }
        }
        swap(v[min], v[i]);
    }
}

void insertion_sort(vector<int>& v) {
    // compare to sorted, swap when less than the sorted one
    for(int i = 1; i < v.size(); i++) {
        for(int j = i; j > 0; j--) {
            if(v[j] < v[j-1]) {
                swap(v[j], v[j-1]);
            }
        }
    }
}

int quick_sort_partition(vector<int>& v, int l, int h) {
    // choose l as pivot
    int i = l, j = h, p = v[l];
    while(i < j) {
        // find Vj < p
        while(i < j && v[j] >= p) j--;
        // assign to Vi to put to left, now Vj is empty
        v[i] = v[j];
        // find Vi > p
        while(i < j && v[i] <= p) i++;
        // assign  to Vj to put to right, now Vi is empty
        v[j] = v[i];
    }
    // now i == j, everything is done
    // fix the last empty Vi with p
    v[i] = p;
    return i;
}

void quick_sort_dac(vector<int>& v, int l, int h) {
    if(l >= h) {
        return;
    }
    int m = quick_sort_partition(v, l, h);
    prt(v);
    quick_sort_dac(v, l, m-1);
    quick_sort_dac(v, m+1, h);
}

void shuffle(vector<int>& v) {
    unsigned short xsubi[3];
    for(int i = 0; i < v.size(); i++) {
        // [0, i], including i
        int j = nrand48(xsubi) % (i+1);
        swap(v[j], v[i]);
    }
}

void quick_sort(vector<int>& v) {
    if(v.empty()) {
        return;
    }
    shuffle(v);
    prt(v);
    quick_sort_dac(v, 0, v.size()-1);
}

// need an i to swap eq
// [p <   |     =   |------|   >        ]
//        ^         ^      ^ 
//        lt        i      gt
void quicksort_3way(vector<int>& v, int l, int h) {
    int lt = l, gt = h, i = l+1;
    int p = v[l];
    if(l >= h) {
        return;
    }
    while(i <= gt) {
        if(v[i] < p) swap(v[i++], v[lt++]); // v[lt] is eq to p, replaced by the smaller one, and advanced
        else if(v[i] > p) swap(v[i], v[gt--]); // put bigger to gt and put the under one to current i
        else i++; // just advance
    }
    // [l,lt) is < v
    // [lt,gt] is = v
    // (gt,h] is > v
    cout << "p: " << p << ", ";
    prt(v);
    quicksort_3way(v, l, lt-1);
    quicksort_3way(v, gt+1, h);
}

// when k is 0, means the first
// v is unsorted
// the time complexity is O(N)! better than O(NlogN) and O(NLogK) <- heap
int select_kth_smallest(vector<int>& v, int k) {
    assert(! v.empty());
    int l = 0, h = v.size() - 1;
    while(l <= h) {
        int j = quick_sort_partition(v, l, h);
        if(j == k) { // found!
            return v[k];
        } else if (k < j) {
            h = j-1;
        } else { // k > j
            l = j+1;
        }
    }
    return v[k];
}
 

// max-heap
// k start from 1, k is the node to sink
void heap_sink(vector<int>& v, int k, int N) {
    assert(k <= N);
    // get the one before, we will use index start from 1 to n
    int* A = v.data() - 1;
    int c;
    while(k * 2 <= N) {
        c = k * 2;
        if(c + 1 <= N && A[c + 1] > A[c]) {
            c++;
        }
        if(A[c] > A[k]) {
            swap(A[c], A[k]);
        } else {
            break;
        }
        k = c;
    }
}

void heap_make(vector<int>& v) {
    // get the one before, we will use index start from 1 to n
    int* A = v.data() - 1;
    int N = v.size();
    int k = N / 2;
    while(k >= 1) {
        heap_sink(v, k, N);
        k--;
    }
}

void heap_sort(vector<int>& v) {
    int N = v.size();
    heap_make(v);
    while(--N) {
        // swap max to last
        swap(v[0], v[N]);
        // sink the root
        heap_sink(v, 1, N);
    }
}


int main() {
    vector<int> a = {1,2,4,5,7,2,54,2,712,2,4,6,1};
    
    vector<int> b = a, c = a, d = a, e = a, f = a, g = a;

    cout << "selection sort" << endl;
    selection_sort(b);
    prt(b);

    cout << "insertion sort" << endl;
    insertion_sort(c);
    prt(c);

    cout << "quick sort" << endl;
    prt(d);
    quick_sort(d);
    prt(d);

    cout << "heap sort" << endl;
    heap_sort(f);
    prt(f);

    cout << "select 5th smallest: " << select_kth_smallest(e, 5) << endl;
    prt(e);

    cout << "quicksort 3way" << endl;
    quicksort_3way(g, 0, g.size()-1);
    prt(g);

    return 0;
}
