#include<iostream>
#include<cstring>

#define CAPACITY 2

class Fridge{
    public:

    int id;
    float outdoor_temp;
    float indoor_temp;

    Fridge(int id, float outdoor_temp, float indoor_temp):
        id(id), outdoor_temp(outdoor_temp), indoor_temp(indoor_temp){
            std::cout<<"CTOR: Fridge"<<std::endl;
        }
    
    ~Fridge(){
        std::cout<<"DTOR: Fridge"<<std::endl;
    }

};

// first allocate and then construct
class ArenaAllocator {
    public:

    int count = 0;
    // raw memory for fridge class
    // char buffer that stores, last and previous value
    // alignas will be size of largest member in struct
    alignas(Fridge) char arena_buff[sizeof(Fridge) * CAPACITY];

    Fridge* emplace(int id, float out, float in) {

        if (count > CAPACITY) {
            std::cout<<"Arena is full"<<std::endl;
            return nullptr;
        }

        // get the byte address of next location to construct object
        void* slot = arena_buff + (count) * sizeof(Fridge);
        Fridge* obj = new (slot) Fridge(id, out, in);
        count++;

        return obj;

    }

    void destroy(Fridge* obj){
        obj->~Fridge();

        // memset is plain C style
        memset(obj, 0, sizeof(Fridge)); // or std::fill()
        
        // count--;  // decrement count when object is destroyed
    }

    void reset_all(){
        
        if ((count - 1) < 0 ) {
            std::cout<<"Empty buffer. Nothing to reset"<<std::endl;
            return;
        }

        // delete in reverse order
        for(int i = count-1; i>=0; i--) {

            // get the object
            Fridge* obj = reinterpret_cast<Fridge*>(arena_buff + i * sizeof(Fridge));
            obj->~Fridge();
        }

        count = 0;
        std::cout<<"ArenAllocator reset successfull"<<std::endl;
    }

    void read_arena(){

        if (count == 0) {
            std::cout<<"Empty buffer"<<std::endl;
            return;
        }

        int index = count;
        while(index > 0) {
            // print in reverse order
            Fridge* obj = reinterpret_cast<Fridge*>(arena_buff + (index-1) * sizeof(Fridge));
            //if (index - 1 != 0) {
                std::cout<<"Current temperature settings: fid: "<<obj->id<<" indoor temp: "<<obj->indoor_temp<<" outdoor temp: "<<obj->outdoor_temp<<std::endl;
            //} else {
            //    std::cout<<"Previous temperature settings: fid: "<<obj->id<<" indoor temp: "<<obj->indoor_temp<<" outdoor temp: "<<obj->outdoor_temp<<std::endl;
            //}
            index--;
        }
    }
};

int main() {

    ArenaAllocator aa;

    std::cout<<"Address of arena buffer: "<<(void*)aa.arena_buff<<std::endl;
    std::cout<<"Size of Arena Allocator: "<<sizeof(Fridge)<<std::endl;


    Fridge* f1 = aa.emplace(1, 10.4, 8.2);
    Fridge* f2 = aa.emplace(1, 12.1, 10.1);

    aa.read_arena();

    aa.destroy(f1);
    aa.read_arena();
}