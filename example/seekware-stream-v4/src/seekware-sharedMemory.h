typedef struct sPoint{
    int x;
    int y;
}seek_p;

typedef struct shardMemory{
    float max_t;   //max temp
    seek_p max_p;    //max temp point
    float min_t;   //min temp
    seek_p min_p;    //min temp point
    int mode_set;  //thermal camera mode
}sSharedMemory;
