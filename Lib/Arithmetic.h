int CircularIndex(int index, int min, int max){
    int range = max - min + 1;
    return min + ((index - min) % range + range) % range;
}