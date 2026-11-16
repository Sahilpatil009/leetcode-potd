class Solution {
public:
    int sumOfD(string sumstr) {
        int ans = 0;

        for(char ch: sumstr) {
            ans += ch -'0';
        }
        return ans;
    }   

    string digitSum(string s, int k) {
        while(s.size() > k) {
            string temp = "";
            for(int i=0; i<s.size(); i+=k) {
                int sum = sumOfD(s.substr(i, k));
                temp+= to_string(sum);
            }

            s=temp;
        }

        return s;
    }
};