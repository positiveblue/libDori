
template<typename T>
class Hasher {

private:
    std::hash<T> hasher;
    
public:
    
    Hasher() {
        hasher = std::hash<T>();
    }

    size_t hash(T& value) {
        return hasher(value);
    }
};