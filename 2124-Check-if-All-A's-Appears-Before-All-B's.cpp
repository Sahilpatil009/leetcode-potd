class Solution {
public:
    bool checkString(string s) {
        bool seeB = false;

        for(char ch: s) {
            if(ch == 'b') {
                seeB = true;
            } else if(seeB) {
                return false;
            }
        }

        return true;
    }
};