
// Assume 1) probability of a successful search is equal to p (o less than or equal p less than or equal 1)
//        2) Probability of the first match occurring in the ith position is the same for every i
// With a successful search, the probability of the first match occurring in the ith position is p / n for every i
// With an unsuccessful search, the number of comparisons will be n, with the probability of such being 1 - p
// C avg(n) = [1 + p/n + 2p/n + ... + i*p/n + ... + n*p/n] + n(1-p)
// = p/n * [1 + 2 + ... + i + ... + n] + n(1-p)
int sequential_search(int array[], const int size, int key) {
    for (int i = 0; i < size; i++) {
        if (array[i] == key) {
            return i;
        }
    }
    return -1;
}

// Big O Def: O(g(n)) = { f(n): There exists positive constants c and n_0 such 
// that O less than equal f(n) less than equal c*g(n) for all n greater than equal to n_0}
// Omega(g(n)) = {f(n): there exists positive constants c and n_0 so that 0 less 
// than equal c*g(n) less than equal f(n) for all n greater than equal to n_0}
// Theta(g(n)) = {f(n): There exists positive constants c_1, c_2, and n_0 so that 0 less than equal 
// c1*g(n) less than equal f(n) less than equal c2*g(n) for all n greater than equal to n_0}