#ifndef TWENTY_FOURTY_EIGHT_H
#define TWENTY_FOURTY_EIGHT_H

class TwentyFourtyEight {
    private:
        int score;

    public:
        TwentyFourtyEight();
        void print_vector();

        void random_placer();
        void move_up();
        void move_down();
        void move_left();
        void move_right();
};

#endif