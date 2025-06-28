bool isalpha(unsigned char c) {
    if ((c - 'a' >= 0 && c - 'a' <= 25) || (c - 'A' >= 0 && c - 'A' <= 25)) {
        return true;
    }
    else {
        return false;
    }
}

unsigned char tolower(unsigned char c) {
    if (c - 'A' >= 0 && c - 'A' <= 25) {
        return (char) ('a' + (c - 'A'));
    }
    else {
        return c;
    }
}
