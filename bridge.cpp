#include <iostream>
#include <vector>

typedef struct Point{
    int x;
    int y;
}Point;

class Drawing{
    public:
        virtual void DrawLine(Point p1, Point p2) const = 0;
        virtual void DrawCircle(Point center, int radius) const = 0;
        
};

class GS1{
    public:
        void draw_a_line(int x1, int x2, int y1, int y2){
            std::cout << "GS1 is drawing a line x1 = " << x1 << " x2 = " << x2
                    << " y1 = " << y1 << " y2 = " << y2 << std::endl;
        }
        void draw_a_circle(int x, int y, int r){
            std::cout << "GS1 is drawing a circle x = " << x << " y = " << y 
                    << " r = " << r << std::endl;
        }
};

class GS2{
    public:
        void DrawCircle(Point center, int radius){
            std::cout << "GS2 is drawing a a circle  center = (" << center.x <<
            ", " << center.y << ") r =  " << radius << std::endl;
                    
        }
        void DrawLine(Point p1, Point p2){
            std::cout << "GS2 is drawing a line p1 = (" << p1.x << ", " << p1.y
                    << ") p2 =(" << p2.x << ", " << p2.y << ") " << std::endl;
        }

};

class GS1Drawing: public Drawing{
    public:
        GS1Drawing(){
            gs = new GS1;}
        void DrawCircle(Point center, int radius)const {
            gs->draw_a_circle(center.x, center.y, radius);
        }
        void DrawLine(Point p1, Point p2)const {
            gs->draw_a_line(p1.x, p2.x, p1.y, p2.y);
        }
    private:
        GS1* gs;
};

class GS2Drawing: public Drawing{
    public:
        GS2Drawing(){
            gs = new GS2;}
        void DrawCircle(Point center, int radius)const {
            gs->DrawCircle(center, radius);
        }
        void DrawLine(Point p1, Point p2) const {
            gs->DrawLine(p1, p2);
        }
    private:
        GS2* gs;
};



class Shape{
    public:
        virtual void Draw() const = 0;
        Shape(Drawing *ds) : drawing_system(ds){};
    protected:
        Drawing *drawing_system;

};

class Circle : public Shape{
    public:
        Circle(Drawing *ds, Point center, int radius):Shape(ds), center(center), radius(radius){}
        
        void Draw() const {
            drawing_system->DrawCircle(center, radius);
        }
    private:
        Point center;
        int radius;

};

class Rectangle : public Shape{
    public:
        Rectangle(Drawing* ds, Point p1, Point p2,Point p3, Point p4):Shape(ds){
            points.push_back(p1);
            points.push_back(p2);
            points.push_back(p3);
            points.push_back(p4);
        }
        
        void Draw() const {
            for(int i = 0; i < 4; i++)
                drawing_system->DrawLine(points[i], points[(i + 1) % 4]);
            
        }
    private:
        std::vector<Point> points;
};



int main(){
    Point p1 = {0, 0}, p2 = {0, 1}, p3 = {1, 1}, p4 = {1, 0};
    Point center = {5, 5};
    int radius = 2;
    GS1Drawing* gs1 = new GS1Drawing();
    GS2Drawing* gs2 = new GS2Drawing();
    Circle c1(gs1, center, radius);
    Circle c2(gs2, center, radius);
    c1.Draw();
    c2.Draw();
    Rectangle r1(gs1, p1, p2, p3, p4);
    Rectangle r2(gs2, p1, p2, p3, p4);
    r1.Draw();
    r2.Draw();
    return 0;

}