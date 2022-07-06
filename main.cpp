#include <queue>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include "Dynamic_Array.hpp"
#include "Dynamic_Array.cpp"


using namespace std;


struct Data
{
    double HP_capacity;     //3 priority
    int damage;             //4 priority
    double HP_level;        //2 priority
    string enemy_name;      //6 priority
    bool in_affected_area;  //1 priority
    int player_skill;       //5 priority
    
    string random_names[6] = {"aboba", "jackson228", "killer307", "winter_sakura", "rigur", "LLL"};
    bool randomBool[2] = {true, false};
    
    Data()
    {
        HP_capacity = rand() % 1001 / 100.0 + 10;
        damage = rand() % 501 + 1;
        HP_level = rand() % 1001 / 100.0 + 1;
        enemy_name = random_names[rand() % 6];
        in_affected_area = rand() > (RAND_MAX / 2);
        in_affected_area = randomBool[rand() % 2];
        player_skill = rand() % 101;
    }
    
    Data(double HP_capacity, int damage, double HP_level, string enemy_name, bool in_affected_area, int player_skill)
    {
        this->HP_capacity = HP_capacity;
        this->damage = damage;
        this->HP_level = HP_level;
        this->enemy_name = enemy_name;
        this->in_affected_area = in_affected_area;
        this->player_skill = player_skill;
    }
    
    friend bool operator== (const Data& enemy1, const Data& enemy2);
    friend bool operator< (const Data& enemy1, const Data& enemy2);
};


struct PriorityQueue
{
private:
    
    DynamicArray<Data> heap;
    Data none = Data(0, 0, 0, "", false, 0);
    
public:
    
    // moving through binary tree
    int getParent(int index)
    {
        return (index - 1) / 2;
    }
    
    int getLeftChild(int index)
    {
        return index * 2 + 1;
    }
    
    int getRightChild(int index)
    {
        return index * 2 + 2;
    }
       
    
    // max-heap
    void siftUp(int index)
    {
        while (heap.array[getParent(index)] < heap.array[index])
        {
            swap(heap.array[index], heap.array[getParent(index)]);
            index = getParent(index);
        }
    }
    
    void siftDown(int index)
    {
        while (getLeftChild(index) < heap.size() - 1)
        {
            int leftIndex = getLeftChild(index);
            int rightIndex = getRightChild(index);
            
            int maxChild = getLeftChild(index);
            
            if (rightIndex < heap.size() && heap.array[leftIndex] < heap.array[rightIndex])
            {
                maxChild = rightIndex;
            }
            
            if (heap.array[maxChild] < heap.array[index] || heap.array[maxChild] == heap.array[index])
            {
                break;
            }
            else
            {
                swap(heap.array[index], heap.array[maxChild]);
                index = maxChild;
            }
        }
    }
    
    
    // main methods
    void push(Data object)
    {
        heap.push_back(object);
        siftUp(heap.size() - 1);
    }
    
    Data top()
    {
        if (heap.size() == 0)
        {
            return none;
        }
        else
        {
            return heap.array[0];
        }
    }
    
    void pop()
    {
        if (heap.size() == 0)
        {
            cout << "ERROR: HEAP IS EMPTY" << endl;
        }
        else
        {
            swap(heap.array[0], heap.array[heap.size() - 1]);
            heap.pop_back();
            siftDown(0);
        }
    }
    
    int size()
    {
        return heap.size();
    }
    
    bool empty()
    {
        if (heap.size() == 0)
            return true;
        else
        {
            return false;
        }
    }
};


bool operator==(const Data& enemy1, const Data& enemy2)
{
    return (enemy1.HP_capacity == enemy2.HP_capacity &&
            enemy1.damage == enemy2.damage &&
            enemy1.HP_level == enemy2.HP_level &&
            enemy1.enemy_name == enemy2.enemy_name &&
            enemy1.in_affected_area == enemy2.in_affected_area &&
            enemy1.player_skill == enemy2.player_skill);
}


bool operator<(const Data& enemy1, const Data& enemy2)
{
    if ((enemy2.in_affected_area == false) && (enemy1.in_affected_area == true)) { return false; }
    if (enemy2.in_affected_area  == enemy1.in_affected_area)
    {
        if (enemy1.HP_level < enemy2.HP_level) { return false; }
        if (enemy1.HP_level == enemy2.HP_level)
        {
            if (enemy1.HP_capacity < enemy2.HP_capacity) { return false; }
            if (enemy1.HP_capacity == enemy2.HP_capacity)
            {
                if (enemy1.damage > enemy2.damage) { return false; }
                if (enemy1.damage == enemy2.damage)
                {
                    if (enemy1.player_skill < enemy2.player_skill) { return false; }
                    if (enemy2.player_skill == enemy1.player_skill)
                    {
                        if (enemy1.enemy_name >= enemy2.enemy_name) { return false; }
                    }
                }
            }
        }
    }
    
    return true;
}


template <typename T>
float testPriorityQueueSpeed(T&& priorityQueue)
{
    const int iters = 100000;
    clock_t timeStart = clock();
    for (int i = 0; i < iters; i++)
    {
        int insertDataAmount = rand() % 6 + 5;
        for (int j = 0; j < insertDataAmount; j++)
        {
            priorityQueue.push(Data());
        }
        priorityQueue.top();
        priorityQueue.pop();
    }
    clock_t timeEnd = clock();
    float time = (float(timeEnd - timeStart)) / CLOCKS_PER_SEC;
    return time;
}

bool testPriorityQueue()
{
    srand((unsigned int)time(NULL));
    const int iters = 20000;
    PriorityQueue myPriorQueue;
    priority_queue<Data> stlPriorQueue;
    bool isDataEqual = true;
    for (int i = 0; i < iters; i++)
    {
        int insertDataAmount = rand() % 6 + 5;
        for (int j = 0; j < insertDataAmount; j++)
        {
            Data randData = Data();
            stlPriorQueue.push(randData);
            myPriorQueue.push(randData);
        }
        if (!(myPriorQueue.top() == stlPriorQueue.top()))
        {
            isDataEqual = false;
            cerr << "Comparing failed on iteration " << i << endl << endl; break;
        }
        int removeDataAmount = rand() % insertDataAmount;
        for (int j = 0; j < removeDataAmount; j++)
        {
            myPriorQueue.pop();
            stlPriorQueue.pop();
        }
    }
    int myQueueSize = myPriorQueue.size();
    int stlQueueSize = (int)stlPriorQueue.size();
    float stlTime = testPriorityQueueSpeed<priority_queue<Data>>(priority_queue<Data>());
    float myTime = testPriorityQueueSpeed<PriorityQueue>(PriorityQueue());
    cout << "My PriorityQueue:" << endl;
    cout << "Time: " << myTime << ", size: " << myQueueSize << endl;
    cout << "STL priority_queue:" << endl;
    cout << "Time: " << stlTime << ", size: " << stlQueueSize << endl << endl;
    if (isDataEqual && myQueueSize == stlQueueSize)
    {
        cout << "The lab is completed" << endl << endl;
        return true;
    }
    cerr << ":(" << endl << endl;
    return false;
}


int main()
{
    testPriorityQueue();
}
