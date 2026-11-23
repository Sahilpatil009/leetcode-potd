class ProductOfNumbers {
public:
    vector<int> stream;
    ProductOfNumbers() {

    }
    
    void add(int num) {
        stream.push_back(num);
    }
    
    int getProduct(int k) {
        int prod=1;
        int n = stream.size();
        for(int i=n-1; i>=n-k; i--) {
            prod *= stream[i];
        }

        return prod;
    }
};

/**
 * Your ProductOfNumbers object will be instantiated and called as such:
 * ProductOfNumbers* obj = new ProductOfNumbers();
 * obj->add(num);
 * int param_2 = obj->getProduct(k);
 */