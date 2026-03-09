template<typename T1, typename T2>
class Pair{
    private:
        T1 first;
        T2 second;
    public:
        Pair(T1 first, T2 second){
            this->first = first;
            this->second = second;
        }
        T1 getFirst(){
            return first;
        }
}