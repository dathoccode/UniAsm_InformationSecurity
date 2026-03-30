int CircularIndex(int index, int min, int max){
    if (index < min) {
        return max - (min - index) % (max - min);
    } else {
        return min + (index - min) % (max - min);
    }
}