template<typename T>
class MyList{
    private:
        T* data;
        int length;
    public:
        MyList(){
            data = new T[0];
            length = 0;
        }
        MyList(const MyList& other){
            data = new T[other.length];
            for(int i = 0; i < other.length; i++){
                data[i] = other.data[i];
            }
            length = other.length;
        }
        Print(){
            for(int i = 0; i < length; i++){
                
            }
        }
}