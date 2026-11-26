class Solution {
public:
    bool canAliceWin(int n) {
        int stones = n;
        int remove = 10;

        bool aliceTurn = true;

        while (stones >= remove) {
            stones -= remove;
            remove--;

            aliceTurn = !aliceTurn;
        }

        // Alice wins if it is Bob's turn
        return !aliceTurn;   
    }
};