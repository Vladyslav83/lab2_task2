#include <iostream>
#include <cstring>
using namespace std;

// Функція для обчислення біту парності
int calculate_parity(int value) {
    int parity = 0;
    while (value != 0) {
        parity ^= (value & 1); // XOR operation to count ones
        value >>= 1;
    }
    return parity;
}

int main() {
    char text[4][17];
    cout << "Enter text that consists of 4 lines of up to 16 characters per line:\n";
    for (int i = 0; i < 4; i++) {
        cin.getline(text[i], 17);
        int len = strlen(text[i]);
        for (int j = len; j < 16; j++) {
            text[i][j] = ' ';
        }
        text[i][16] = '\0';
    }

    // Шифрування тексту
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 16; j++) {
            int row_num = i;
            int ascii_high = (int)text[i][j] >> 4;
            int ascii_low = (int)text[i][j] & 15;
            int position = j;
            // Обчислюємо біти парності
            int parity_bit1 = calculate_parity(ascii_high);
            int parity_bit2 = calculate_parity((row_num << 4) | ascii_high);
            int parity_bit3 = calculate_parity((ascii_low << 4) | position);
            int byte1 = (row_num << 6) | (ascii_high << 2) | parity_bit1;
            int byte2 = (ascii_low << 4) | (position << 1) | parity_bit2;
            byte2 = byte2 | (parity_bit3 << 7);
            cout << byte1 << " " << byte2 << " ";
        }
        cout << endl;
    }

    return 0;
}