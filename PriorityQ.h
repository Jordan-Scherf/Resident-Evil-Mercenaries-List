#include <vector>
#include <string>
#include <cmath>
#include <cstdlib>
#include <unordered_map>

template <class t1 , class t2 >
class priorityQ
{
public :
    priorityQ ();
    void push_back ( const t1 & , const t2 &);
    void pop_front ();
    void increaseKey ( const t1 & , const t2 &);
    t2 get_front_priority () const ;
    t1 get_front_key () const ;
    bool isEmpty () const ;
private :
    struct priorityType
    {
        t1 key ;
        t2 priority ;
    };
    void bubbleUp (std::size_t );
    void bubbleDown (std::size_t );
    std::vector <priorityType> heapArray ;
    std::unordered_map <t1 , std::size_t> itemToPQ ;
};

template <class t1, class t2>
priorityQ<t1, t2>::priorityQ(){

    heapArray.resize(1);
}

template <class t1, class t2>
void priorityQ<t1, t2>::push_back(const t1& key, const t2& value){

    priorityType item = {key, value};

    heapArray.push_back(item);
    itemToPQ[key] = heapArray.size()-1;

    bubbleUp( heapArray.size() - 1);
}

template<class t1, class t2>
void priorityQ<t1, t2>::increaseKey(const t1& key, const t2& value)
{
    std::size_t index = itemToPQ[key];
    heapArray[index].priority += value;
    bubbleUp(index);
}

template <class t1, class t2>
void priorityQ<t1, t2>::pop_front() {
    //need help
    heapArray[1] = heapArray.back();
    itemToPQ[heapArray[1].key] = 1;
    heapArray.pop_back();
    bubbleDown(1);

}
template <class t1, class t2>
t1 priorityQ<t1, t2>::get_front_key() const{
    return heapArray[1].key;
}

template <class t1, class t2>
bool priorityQ<t1, t2>::isEmpty() const{
    return heapArray.empty();
}

template <class t1, class t2>
t2 priorityQ<t1, t2>::get_front_priority() const{
    return heapArray[1].priority;
}


template<class t1, class t2>
void priorityQ<t1, t2>::bubbleUp(std::size_t index)
{
    std::size_t parent = index / 2;
    while (index > 1 && (heapArray[parent].priority < heapArray[index].priority))
    {
        std::swap(heapArray[index], heapArray[parent]);
        itemToPQ[heapArray[index].key] = index;
        itemToPQ[heapArray[parent].key] = parent;
        index = parent;
        parent = index / 2;
    }

}

template<class t1, class t2>
void priorityQ<t1, t2>::bubbleDown(std::size_t index){
    std::size_t leftChild = 2 * index;
    std::size_t rightChild = 2 * index + 1;
    std::size_t largest = index;

    if (leftChild < heapArray.size() &&
        heapArray[largest].priority < heapArray[leftChild].priority) {
        largest = leftChild;
    }

    if (rightChild < heapArray.size() &&
        heapArray[largest].priority < heapArray[rightChild].priority) {
        largest = rightChild;
    }

    if (largest != index) {
        std::swap(heapArray[index], heapArray[largest]);
        itemToPQ[heapArray[index].key] = index;
        itemToPQ[heapArray[largest].key] = largest;
        bubbleDown(largest);
    }
    return;
}