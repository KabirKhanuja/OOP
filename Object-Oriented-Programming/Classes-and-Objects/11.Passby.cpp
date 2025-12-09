
// pass by value 
void fun(Point p) {   // p is a COPY
    p.x = 10;         // original not affected
}

// pass by reference 
void fun(Point &p) {  // p is original
    p.x = 10;         // original gets changed
}

// pass by pointer
void fun(Point* p) { 
    p->x = 10;        // original gets changed
}