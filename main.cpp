#include <iostream>
#include <vector>

using namespace std;


class Point2D{

public:
    int x;
    int y;
    Point2D(int x0,int y0);
    Point2D(): x(0), y(0) {}
};



Point2D::Point2D(int x0, int y0){
    x = x0;
    y = y0;
}


typedef vector<Point2D> vecP2D;


bool doesRightTurn(Point2D p1, Point2D p2, Point2D p3){

    double v1x = p2.x - p1.x;
    double v1y = p2.y - p1.y;
    double v2x = p3.x - p2.x;
    double v2y = p3.y - p2.y;

    double crossP = v1x*v2y - v2x*v1y;

    return crossP < 0 ? true:false;


}



int solutionNotGoodEnough(vector<Point2D> &A) {


    vecP2D Ap; //plus

    Ap.assign(A.begin(),A.end());
    Ap.push_back(A[0]);
    Ap.push_back(A[1]);



    for (unsigned int i=0; i<Ap.size()-2; i++){

        if( !doesRightTurn(Ap[i],Ap[i+1],Ap[i+2])  )
            return i+2;


    }

    return -1;

}


void bubblesort(vector<Point2D> &A){

    Point2D temp;
    int n=A.size();
    for(int i=1; i<n; i++){

        for(int k=n-1; k>=i; k--){

            if(A[k].x<A[k-1].x){

                temp = A[k];
                A[k] = A[k-1];
                A[k-1] = temp;

            }
            else if(A[k].x == A[k-1].x && A[k].y < A[k-1].y){

                temp = A[k];
                A[k] = A[k-1];
                A[k-1] = temp;
            }
        }
    }
}


void computeConvexHull(vector<Point2D> &A){

    vecP2D As;
    As = A;

    bubblesort(As);



    vecP2D U,L;
    unsigned int n = As.size();


    for(unsigned int i=0; i<n; i++){

        while(U.size() > 2 && !doesRightTurn(U[i-2],U[i-1],As[i])){
            U.erase(U.end());
        }

        U.push_back(As[i]);

    }


    for(unsigned int i=n; i--;){

        while(L.size() > 2 && !doesRightTurn(As[i],L[i+1],L[i+2])){
            L.erase(L.end());
        }

        L.push_back(As[i]);

    }


    U.erase(U.end());
    L.erase(L.end());



    vecP2D C;
    C.reserve(L.size() + U.size());
    C.insert(C.end(),U.begin(),U.end());
    C.insert(C.end(),L.begin(),L.end());


}




int solution(vector<Point2D>& A){


    int lowerPointInd = 0;
    int lowerPoint_y = A[0].y;
    for(unsigned int i=0; i<A.size(); i++){

        if(A[i].y < lowerPoint_y) {
            lowerPoint_y = A[i].y;
            lowerPointInd = i;
        }
    }


    vector<Point2D> rA;

    rA.insert(rA.end(),A.begin()+lowerPointInd,A.end());
    rA.insert(rA.end(),A.begin(),A.begin()+lowerPointInd);


    int dir = doesRightTurn(A[A.size()-1],A[0],A[1]) ? -1:1;

    rA.push_back(rA[0]);
    rA.push_back(rA[1]);

    for(unsigned int i=0; i<A.size(); i++){

        int turn = doesRightTurn(rA[i],rA[i+1],rA[i+2]) ? -1:1;

        if (turn * dir < 0) {
            return (lowerPointInd + 1 + i)%A.size();
        }
    }


    return -1;

}






int main()
{

    Point2D p1(-1,3);
    Point2D p2(3,1);
    Point2D p3(0,-1);
    Point2D p4(-2,1);
    Point2D p5(0,0);





    vector<Point2D> A = {p1,p5,p2,p3,p4};




    cout<<"sol= "<<solution(A)<<endl;



    return 0;
}
